import configparser
import os
import ast
import subprocess
import urllib.request
import shutil

from hashlib import sha256
from typing import List

from scripts.generate_raylib import Colors

ROOT = os.path.realpath(os.path.dirname(os.path.dirname(os.path.abspath(__file__))))
MAX_EXECUTION_TIME_SEC = 60 * 4


class Section:
    def __init__(self, obj, parent):
        self._obj = obj
        self.zig = str(self._obj["zig"]).strip()
        self.zig_sha256 = str(self._obj["zig_sha256"]).strip()
        self.zig_sub = str(self._obj["zig_subfolder"]).strip()
        self.exe_suffix = str(self._obj["exe_suffix"]).strip()
        self.binaries: List[str] = ast.literal_eval(str(self._obj["binaries"]).strip())
        self.folders: List[str] = ast.literal_eval(str(parent["common"]["folders"]).strip())
        self.files: List[str] = ast.literal_eval(str(parent["common"]["files"]).strip())

    def bin(self, name: str) -> List[str]:
        return ast.literal_eval(self._obj["bin__" + name])


class Config:
    def __init__(self):
        self._configuration = configparser.ConfigParser()
        self._configuration.read(os.path.join(ROOT, "scripts/release.ini"))
        self.version = str(self._configuration["main"]["version"]).strip()
        self.temp = os.path.join(ROOT, str(self._configuration["main"]["temp"])).strip()
        self.releases = ast.literal_eval(str(self._configuration["main"]["releases"]).strip())

    def section(self, name) -> Section:
        return Section(self._configuration[name], self._configuration)


CONFIG = Config()


def in_root(s: str) -> str:
    return os.path.join(ROOT, s)


def in_temp(s: str) -> str:
    return os.path.join(ROOT, CONFIG.temp, s)


def hash_sha256(b: bytes) -> str:
    return str(sha256(b).hexdigest())


def download(url: str, sha256_hash: str) -> (bool, str):
    filename = os.path.basename(url)
    target = in_temp(filename)
    if os.path.isfile(target):
        with open(target, "rb+") as h:
            file_hash = hash_sha256(h.read())
            if file_hash == sha256_hash:
                print(filename, "✔️ already downloaded. It will be used for packaging.")
                return True, target
    with urllib.request.urlopen(url) as f:
        with open(target, "wb+") as t:
            print("downloading:", filename, "...")
            t.write(f.read())
    with open(target, "rb+") as h:
        file_hash = hash_sha256(h.read())
        success = file_hash == sha256_hash
        if success:
            print(filename, "✔️")
        else:
            print(filename, "❌")
        return success, target


def execute(args: list):
    fuzz_process = subprocess.Popen(args, stdout=subprocess.PIPE, stderr=subprocess.PIPE, encoding="utf-8",
                                    universal_newlines=True)
    try:
        so, se = fuzz_process.communicate(timeout=MAX_EXECUTION_TIME_SEC)
        return_value = fuzz_process.returncode
    except subprocess.TimeoutExpired:
        fuzz_process.kill()
        fuzz_process.communicate()
        print("Timed out - ", Colors.fail(repr(args)))
        return -1
    if return_value != 0:
        print("Found fuzz error", Colors.fail(repr(args)))
        print(so)
        print(se)
    return return_value


def make_directory(name: str):
    dir_name = in_temp("yaksha_" + name)
    if os.path.isdir(dir_name):
        shutil.rmtree(dir_name)
    if not os.path.isdir(dir_name):
        os.mkdir(dir_name)
    return dir_name


def extract(arch: str, directory: str):
    extract_once(arch, directory)
    if arch.endswith(".tar.xz"):
        tarfile_ = os.path.join(directory, os.path.basename(arch[:-3]))
        extract_once(tarfile_, directory)
        os.unlink(tarfile_)


def extract_once(arch, directory):
    print(Colors.cyan("extracting"), os.path.basename(arch), "...")
    os.chdir(ROOT)
    os.chdir(directory)
    args = ["7z", "x", arch]
    execute(args)
    os.chdir(ROOT)


def package(arch: str, directory: str):
    print(Colors.cyan("packaging"), os.path.basename(arch), "...")
    args = ["7z", "a", "-mx9", arch, directory]
    execute(args)


def copy_binaries(section: Section, target_location):
    binaries = section.binaries
    suffix = section.exe_suffix
    for bin_name in binaries:
        locations = section.bin(bin_name)
        for location in locations:
            possible_bin = os.path.join(ROOT, location)
            if os.path.isfile(possible_bin):
                shutil.copyfile(possible_bin, os.path.join(target_location, bin_name + suffix))
                print(bin_name, "✔️")
                break
        else:
            print(bin_name, "❌")


def build_release(name: str):
    print(Colors.cyan("building"), "yaksha_" + name, "😎", "...")
    print("-" * 40)
    sec = CONFIG.section(name)
    success, zig = download(sec.zig, sec.zig_sha256)
    if not success:
        return
    directory = make_directory(name)
    temp = make_directory(name + "_temp")
    extract(zig, temp)
    shutil.move(os.path.join(temp, sec.zig_sub), os.path.join(directory, "bin"))
    print(Colors.blue("zig"), "✔️")
    copy_binaries(sec, os.path.join(directory, "bin"))
    for folder in sec.folders:
        shutil.copytree(in_root(folder), os.path.join(directory, folder))
        print(Colors.blue(folder), "✔️")
    for single_file in sec.files:
        shutil.copyfile(in_root(single_file), os.path.join(directory, single_file))
        print(Colors.blue(single_file), "✔️")
    # rename zig license
    shutil.move(os.path.join(directory, "bin", "LICENSE"), os.path.join(directory, "bin", "doc", "ZIG_LICENSE"))
    # final archive
    archive = in_temp("yaksha_v" + CONFIG.version + "_" + name + ".7z")
    if os.path.isfile(archive):
        os.unlink(archive)
    package(in_temp(archive), directory)
    print(Colors.blue(os.path.basename(archive)), "✔️")
    # clean up
    shutil.rmtree(directory)
    shutil.rmtree(temp)
    # final message
    print(Colors.green("all done."), "🎉")


def main():
    for release in CONFIG.releases:
        build_release(release)


if __name__ == "__main__":
    # Set work directory to be that of project root.
    os.chdir(ROOT)
    main()
