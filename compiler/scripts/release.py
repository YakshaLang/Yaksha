# ==============================================================================================
# ╦  ┬┌─┐┌─┐┌┐┌┌─┐┌─┐    Yaksha Programming Language
# ║  ││  ├┤ │││└─┐├┤     is Licensed with GPLv3 + extra terms. Please see below.
# ╩═╝┴└─┘└─┘┘└┘└─┘└─┘
# Note: libs - MIT license, runtime/3rd - various
# ==============================================================================================
# GPLv3:
# 
# Yaksha - Programming Language.
# Copyright (C) 2020 - 2023 Bhathiya Perera
# 
# This program is free software: you can redistribute it and/or modify it under the terms
# of the GNU General Public License as published by the Free Software Foundation,
# either version 3 of the License, or (at your option) any later version.
# 
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
# or FITNESS FOR A PARTICULAR PURPOSE.
# See the GNU General Public License for more details.
# 
# You should have received a copy of the GNU General Public License along with this program.
# If not, see https://www.gnu.org/licenses/.
# 
# ==============================================================================================
# Additional Terms:
# 
# Please note that any commercial use of the programming language's compiler source code
# (everything except compiler/runtime, compiler/libs and compiler/3rd) require a written agreement
# with author of the language (Bhathiya Perera).
# 
# If you are using it for an open source project, please give credits.
# Your own project must use GPLv3 license with these additional terms.
# 
# You may use programs written in Yaksha/YakshaLisp for any legal purpose
# (commercial, open-source, closed-source, etc) as long as it agrees
# to the licenses of linked runtime libraries (see compiler/runtime/README.md).
# 
# ==============================================================================================
import ast
import configparser
import os
import platform
import shutil
import subprocess
import sys
import urllib.request
from contextlib import contextmanager
from hashlib import sha256
from typing import List

ROOT = os.path.realpath(os.path.dirname(os.path.dirname(os.path.abspath(__file__))))
MAX_EXECUTION_TIME_SEC = 60 * 60
PATHS = []

MACOS_RELEASE_FILTER = ["macos", "linux"]
WINDOWS_RELEASE_FILTER = ["windows"]

MAC_OS = sys.platform.startswith('darw')  # noqa
WINDOWS_OS = sys.platform.startswith('win')
ARM_CPU = platform.processor() == "arm"
ARCH = "aarch64" if ARM_CPU else "x86_64"
CURRENT_PLATFORM_KEY = f"linux-{ARCH}"
if WINDOWS_OS:
    CURRENT_PLATFORM_KEY = f"windows-{ARCH}"
if MAC_OS:
    CURRENT_PLATFORM_KEY = f"macos-{ARCH}"
BUNDLED_ZIG_VERSION = "0.9.1"
COMPILER_BINARIES = ["yaksha.exe", "yakshac.exe"] if WINDOWS_OS else ["yaksha", "yakshac"]
MUST_HAVE_BIN = set(["yaksha", "carpntr", "zig"])  # noqa
SCRIPT_STATUS = 0


@contextmanager
def updated_path():
    # ref: https://stackoverflow.com/a/69274881
    old_env = os.environ.copy()
    sep: str = os.pathsep
    path_var = old_env["PATH"] + sep + sep.join(PATHS)
    print("$PATH = ", path_var)
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


def contains_any(haystack: str, needles: List[str]) -> bool:
    for needle in needles:
        if needle in haystack:
            return True
    return False


def filter_releases(releases: List[str]) -> List[str]:
    filtered = releases
    if WINDOWS_OS:
        filtered = [r for r in releases if contains_any(r, WINDOWS_RELEASE_FILTER)]
    if MAC_OS:
        filtered = [r for r in releases if contains_any(r, MACOS_RELEASE_FILTER)]
    print(Colors.cyan("targets:"), releases, Colors.cyan("selected:"), filtered)
    print()
    return filtered


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
        self.releases = filter_releases(ast.literal_eval(str(self._configuration["main"]["releases"]).strip()))

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
    proc = subprocess.Popen(args, stdout=subprocess.PIPE, stderr=subprocess.PIPE, encoding="utf-8",
                            universal_newlines=True, env=dict(os.environ))
    try:
        so, se = proc.communicate(timeout=MAX_EXECUTION_TIME_SEC)
        return_value = proc.returncode
    except subprocess.TimeoutExpired:
        proc.kill()
        proc.communicate()
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
    global SCRIPT_STATUS
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
            # WHY:
            # If we do not have yaksha or carpntr binaries, it is a useless build
            if bin_name in MUST_HAVE_BIN:
                SCRIPT_STATUS = 1


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
    # clean up
    shutil.rmtree(directory)
    shutil.rmtree(temp)
    # final message
    if SCRIPT_STATUS == 0:
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
    zig_path = os.path.join(temp, "zig-" + CURRENT_PLATFORM_KEY + "-" + BUNDLED_ZIG_VERSION)
    if not WINDOWS_OS:
        command = "chmod +x " + os.path.join(zig_path, "zig")
        print("executing: ", command)
        execute(command.split(" "))
    PATHS.append(zig_path)
    print(PATHS)


def compile_carpntr():
    print(Colors.cyan("compiling"), "carpntr", "😎", "...")
    carpntr_path = os.path.join(ROOT, "carpntr")
    carpntr_build_path = os.path.join(ROOT, "carpntr", "build")
    with navigate(carpntr_path):
        with updated_path():
            execute([sys.executable, "bootstrap_me.py"])
    # WHY?
    # carpntr fails to build as native on Mac (M2 in my case)
    # so this fixes it in case that has happened
    if MAC_OS and not os.path.exists(os.path.join(carpntr_build_path, "bootstrapped-carpntr")):
        shutil.copyfile(os.path.join(carpntr_build_path, f"bootstrapped-carpntr-{ARCH}-macos-gnu"),
                        os.path.join(carpntr_build_path, "bootstrapped-carpntr"))
        execute(["chmod", "+x", os.path.join(carpntr_build_path, "bootstrapped-carpntr")])
        with navigate(carpntr_path):
            with updated_path():
                execute(["build/bootstrapped-carpntr"])
        shutil.copyfile(os.path.join(carpntr_build_path, f"carpntr-{ARCH}-macos-gnu"),
                        os.path.join(carpntr_build_path, "carpntr"))
        execute(["chmod", "+x", os.path.join(carpntr_build_path, "carpntr")])
    global PATHS
    PATHS.append(carpntr_build_path)


def compile_hammer():
    print(Colors.cyan("compiling"), "hammer", "😎", "...")
    hammer_path = os.path.join(ROOT, "hammer")
    hammer_build_path = os.path.join(ROOT, "hammer", "build")
    with navigate(hammer_path):
        with updated_path():
            execute(["carpntr"])
    # Workaround for native build issue on Mac M2 CPU
    if MAC_OS and not os.path.exists(os.path.join(hammer_build_path, "hammer")):
        shutil.copyfile(os.path.join(hammer_build_path, f"hammer-{ARCH}-macos-gnu"),
                        os.path.join(hammer_build_path, "hammer"))
        execute(["chmod", "+x", os.path.join(hammer_build_path, "hammer")])
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


def main():
    # Set work directory to be that of project root.
    os.chdir(ROOT)
    ensure_temp()
    compile_release()
    print("-" * 40)
    build_releases()
    if SCRIPT_STATUS != 0:
        print(Colors.red("Release failed 💀"))
    sys.exit(SCRIPT_STATUS)


if __name__ == "__main__":
    main()
