import configparser
import os
import ast
import subprocess
import sys
import urllib.request
import shutil
from contextlib import contextmanager
from hashlib import sha256
from typing import List

ROOT = os.path.realpath(os.path.dirname(os.path.dirname(os.path.abspath(__file__))))
MAX_EXECUTION_TIME_SEC = 60 * 4
PATHS = []

WINDOWS_OS = sys.platform.startswith('win')
CURRENT_PLATFORM_KEY = "windows_x86_64" if WINDOWS_OS else "linux_x86_64"
BUNDLED_ZIG_VERSION = "0.9.1"
COMPILER_BINARIES = ["yaksha.exe", "yakshac.exe"] if WINDOWS_OS else ["yaksha", "yakshac"]
@contextmanager
def updated_path():
    # ref: https://stackoverflow.com/a/69274881
    old_env = os.environ.copy()
    sep: str = os.pathsep
    path_var = old_env["PATH"] + sep + sep.join(PATHS)
    os.environ.update({"PATH": path_var})
    yield
    os.environ.clear()
    os.environ.update(old_env)


@contextmanager
def navigate(directory):
    os.chdir(directory)
    yield
    os.chdir(ROOT)


class Colors:
    HEADER = '\033[95m'
    OKBLUE = '\033[94m'
    OKCYAN = '\033[96m'
    OKGREEN = '\033[92m'
    WARNING = '\033[93m'
    FAIL = '\033[91m'
    ENDC = '\033[0m'
    BOLD = '\033[1m'
    UNDERLINE = '\033[4m'

    @staticmethod
    def blue(text):
        return Colors.OKBLUE + str(text) + Colors.ENDC

    @staticmethod
    def cyan(text):
        return Colors.OKCYAN + str(text) + Colors.ENDC

    @staticmethod
    def green(text):
        return Colors.OKGREEN + str(text) + Colors.ENDC

    @staticmethod
    def warning(text):
        return Colors.WARNING + str(text) + Colors.ENDC

    @staticmethod
    def fail(text):
        return Colors.FAIL + str(text) + Colors.ENDC

    @staticmethod
    def red(text):
        return Colors.FAIL + str(text) + Colors.ENDC


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
            if sha256_hash == "-" or file_hash == sha256_hash:
                print(filename, "✔️ already downloaded. It will be used for packaging.")
                if sha256_hash == "-":
                    print(filename, "hashed: ", file_hash)
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
                                    universal_newlines=True, env=dict(os.environ))
    try:
        so, se = fuzz_process.communicate(timeout=MAX_EXECUTION_TIME_SEC)
        return_value = fuzz_process.returncode
    except subprocess.TimeoutExpired:
        fuzz_process.kill()
        fuzz_process.communicate()
        print("Timed out - ", Colors.fail(repr(args)))
        return -1
    if return_value != 0:
        print("Execution failed", Colors.fail(repr(args)))
        print(so)
        print(se)
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
                print(Colors.red(bin_name), "✔️")
                break
        else:
            print(Colors.red(bin_name), "❌")


def create_package(directory, name, ext):
    archive = in_temp("yaksha_v" + CONFIG.version + "_" + name + ext)
    if os.path.isfile(archive):
        os.unlink(archive)
    package(in_temp(archive), directory)
    return archive


def build_release(name: str):
    print(Colors.cyan("building"), "yaksha_" + name, "😎", "...")
    sec = CONFIG.section(name)
    success, zig = download(sec.zig, sec.zig_sha256)
    if not success:
        return
    directory = make_directory(name)
    temp = make_directory(name + "_temp")
    extract(zig, temp)
    shutil.move(os.path.join(temp, sec.zig_sub), os.path.join(directory, "bin"))
    print(Colors.red("zig"), "✔️")
    copy_binaries(sec, os.path.join(directory, "bin"))
    for folder in sec.folders:
        shutil.copytree(in_root(folder), os.path.join(directory, folder))
        print(Colors.blue(folder), "✔️")
    for single_file in sec.files:
        shutil.copyfile(in_root(single_file), os.path.join(directory, single_file))
        print(Colors.blue(single_file), "✔️")
    # rename zig license
    shutil.move(os.path.join(directory, "bin", "LICENSE"), os.path.join(directory, "bin", "doc", "ZIG_LICENSE"))
    # create package .7z
    archive = create_package(directory, name, ".7z")
    print(Colors.blue(os.path.basename(archive)), "✔️")
    # create package .zip
    archive = create_package(directory, name, ".zip")
    print(Colors.blue(os.path.basename(archive)), "✔️")
    # clean up
    shutil.rmtree(directory)
    shutil.rmtree(temp)
    # final message
    print(Colors.green("all done."), "🎉")


def build_releases():
    for release in CONFIG.releases:
        build_release(release)


def compile_yaksha():
    print(Colors.cyan("compiling"), "yaksha", "😎", "...")
    release_dir = os.path.join(ROOT, "cmake-build-release")
    if not os.path.isdir(release_dir):
        os.mkdir(release_dir)
    if not os.path.isdir(release_dir):
        print(Colors.fail("Failed to create release dir"))
        return
    with navigate(release_dir):
        execute("cmake -S .. -B .".split(" "))
        execute("cmake --build . --config Release -j 2".split(" "))
    PATHS.append(os.path.join(ROOT, "bin", "Release"))
    PATHS.append(os.path.join(ROOT, "bin"))
    # Hack to copy binaries in Release directory
    for binary in COMPILER_BINARIES:
        try:
            shutil.copyfile(os.path.join(ROOT, "bin", "Release", binary), os.path.join(ROOT, "bin", binary))
        except FileNotFoundError:
            pass


def extract_zig_for_compilation():
    global PATHS
    name = CURRENT_PLATFORM_KEY
    sec = CONFIG.section(name)
    success, zig = download(sec.zig, sec.zig_sha256)
    temp = make_directory(name + "_temp")
    extract(zig, temp)
    PATHS.append(os.path.join(temp, CURRENT_PLATFORM_KEY + "-" + BUNDLED_ZIG_VERSION))


def compile_carpntr():
    print(Colors.cyan("compiling"), "carpntr", "😎", "...")
    carpntr_path = os.path.join(ROOT, "carpntr")
    carpntr_build_path = os.path.join(ROOT, "carpntr", "build")
    with navigate(carpntr_path):
        with updated_path():
            execute([sys.executable, "bootstrap_me.py"])
    global PATHS
    PATHS.append(carpntr_build_path)


def compile_hammer():
    print(Colors.cyan("compiling"), "hammer", "😎", "...")
    hammer_path = os.path.join(ROOT, "hammer")
    hammer_build_path = os.path.join(ROOT, "hammer", "build")
    with navigate(hammer_path):
        with updated_path():
            execute(["carpntr"])
    global PATHS
    PATHS.append(hammer_build_path)


def cross_compile_compiler():
    print(Colors.cyan("cross-compiling"), "yakasha", "😎", "...")
    with navigate(ROOT):
        with updated_path():
            execute(["hammer"])


def compile_release():
    compile_yaksha()
    extract_zig_for_compilation()
    compile_carpntr()
    compile_hammer()
    cross_compile_compiler()


def ensure_temp():
    temp_path = os.path.join(ROOT, CONFIG.temp)
    if os.path.isdir(temp_path):
        return
    os.mkdir(temp_path)
    if not os.path.isdir(temp_path):
        print(Colors.fail("Failed to create temp_path:"), temp_path)


if __name__ == "__main__":
    # Set work directory to be that of project root.
    os.chdir(ROOT)
    ensure_temp()
    compile_release()
    print("-" * 40)
    build_releases()
