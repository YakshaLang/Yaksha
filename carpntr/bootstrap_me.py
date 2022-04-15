# Bootstrap carpntr builder
# ------------------------
# This python script builds carpntr, and then you can use carpntr to build itself
import ast
import configparser
import os
import os.path as paths
import subprocess
import sys
from typing import List, Tuple

SCRIPT_DIR = paths.abspath(paths.dirname(__file__))
BIN_DIR = paths.join(paths.dirname(SCRIPT_DIR), "bin")
COMPILER = paths.join(BIN_DIR, "yakshac")
RUNTIME_DIR = paths.abspath(paths.join(paths.dirname(BIN_DIR), "runtime"))
LIBS_PARENT_DIR = paths.abspath(paths.join(paths.dirname(BIN_DIR), "libs"))
MAX_EXECUTION_TIME_SEC = 2
C_COMPILER = "zig cc"
if C_COMPILER == "clang":
    ARGS = "-fsanitize=address,undefined,leak -ggdb -g -std=c99 -pedantic -Wall -Wno-newline-eof"
else:
    ARGS = "-Oz -std=c99 -pedantic -Wall -Wno-newline-eof"
DEFAULT_compiler_defines = ["UTF8PROC_STATIC"]
DEFAULT_includes = ["whereami.h", "yk__system.h", "utf8proc.h", "yk__utf8iter.h", "toml.h",
                    "yk__console.h", "mpc.h",
                    "yk__arrayutils.h", "yk__process.h"]
DEFAULT_c_code = ["whereami.c", "yk__system.c", "utf8proc.c", "toml.c", "mpc.c",
                  "yk__console.c", "yk__arrayutils.c", "yk__process.c"]
DEFAULT_c_code = [paths.join(RUNTIME_DIR, x) for x in DEFAULT_c_code]
DEFAULT_include_paths = [RUNTIME_DIR, "build"]


class CCode:
    include_paths: List[str]
    defines: List[str]
    compiler_defines: List[str]
    includes: List[str]
    system_includes: List[str]
    c_code: List[str]
    cpp_code: List[str]


class Project:
    main: str
    name: str
    author: str


class Compilation:
    override_alloc: bool
    only_ccode: bool
    libc: str
    compiler: str
    targets: List[str]


class Config:
    ccode: CCode
    project: Project
    compilation: Compilation


def execute(arg: str) -> Tuple[str, str, int]:
    proc = subprocess.Popen(
        arg,
        stdout=subprocess.PIPE,
        stderr=subprocess.PIPE,
        encoding="utf-8",
        universal_newlines=True,
        shell=True)
    try:
        so, se = proc.communicate(timeout=MAX_EXECUTION_TIME_SEC)
        return_value = proc.returncode
    except subprocess.TimeoutExpired:
        proc.kill()
        proc.communicate()
        return "", "", -1

    return so.strip(), se.strip(), return_value


def read_config_string(obj, section, prop, default_val) -> str:
    try:
        s = str(obj.get(section, prop))
        if s.startswith("\""):
            return ast.literal_eval(s)
        else:
            return s
    except:
        return str(default_val)


def read_config_string_array(obj, section, prop) -> List[str]:
    return ast.literal_eval(read_config_string(obj, section, prop, "[]"))


def read_config_bool(obj, section, prop) -> bool:
    return read_config_string(obj, section, prop, "false").lower() == "true"


def get_config() -> Config:
    config = configparser.ConfigParser()
    config.read('yaksha.toml')

    ccode = CCode()
    ccode.include_paths = DEFAULT_include_paths + read_config_string_array(config, "ccode", "include_paths")
    ccode.defines = read_config_string_array(config, "ccode", "defines")
    ccode.compiler_defines = DEFAULT_compiler_defines + read_config_string_array(config, "ccode", "compiler_defines")
    ccode.includes = DEFAULT_includes + read_config_string_array(config, "ccode", "includes")
    ccode.system_includes = read_config_string_array(config, "ccode", "system_includes")
    ccode.c_code = DEFAULT_c_code + read_config_string_array(config, "ccode", "c_code")
    ccode.cpp_code = read_config_string_array(config, "ccode", "cpp_code")

    project = Project()
    project.main = read_config_string(config, "project", "main", "")
    project.name = read_config_string(config, "project", "name", "")
    project.author = read_config_string(config, "project", "author", "")

    comp = Compilation()
    comp.override_alloc = read_config_bool(config, "compilation", "override_alloc")
    comp.only_ccode = read_config_bool(config, "compilation", "only_ccode")
    comp.libc = read_config_string(config, "compilation", "libc", "try_musl")
    comp.compiler = read_config_string(config, "compilation", "compiler", "zig")
    comp.targets = read_config_string_array(config, "compilation", "targets")

    conf = Config()
    conf.ccode = ccode
    conf.project = project
    conf.compilation = comp
    return conf


def panic(message: str):
    print(message)
    sys.exit(-1)


def compile_(conf: Config):
    try:
        os.mkdir("build")
    except:
        if not os.path.isdir("build"):
            panic("Failed to create build dir")
    cmd = "{} {} {}".format(COMPILER, conf.project.main, LIBS_PARENT_DIR)
    print(cmd)
    code, errors, ret = execute(cmd)
    if ret != 0:
        if code:
            print(code)
        if errors:
            print(errors)
        panic("--Failed to run yaksha compiler--")

    conf.ccode.defines = conf.ccode.defines
    with open("build/program_code.c", "w+", encoding="utf-8") as w:
        for define in conf.ccode.defines:
            w.write("#define " + define + "\n")
        for inc in conf.ccode.system_includes:
            w.write("#include <" + inc + ">" + "\n")
        for inc in conf.ccode.includes:
            w.write('#include "' + inc + '"' + "\n")
        w.write("\n".join(code.splitlines()))
        w.write("\n")  # nice ending new line
    includes = conf.ccode.include_paths
    includes = ["-I" + x for x in includes]
    conf.project.name = "bootstrapped-" + conf.project.name
    if os.name == 'nt':
        native_binary = conf.project.name + ".exe"
    else:
        native_binary = conf.project.name
    ccodes = " ".join(conf.ccode.c_code)
    comp_defines = "".join(["-D " + x for x in conf.ccode.compiler_defines])
    c_args = ARGS
    if sys.platform != "darwin":
        c_args = c_args + " -flto=full"
    binary_main = paths.join(RUNTIME_DIR, "yk__main.c")
    cmd = "{} {} {} {} {} build/program_code.c runtime/yk__main.c -o build/{}".format(
        C_COMPILER, c_args, " ".join(includes), comp_defines, ccodes, native_binary) \
        .replace("runtime/yk__main.c", binary_main)
    print(cmd)
    os.system(cmd)
    if C_COMPILER != "clang":
        for target in conf.compilation.targets:
            if "windows" in target:
                name = conf.project.name + "-" + target + ".exe"
            else:
                name = conf.project.name + "-" + target
            c_args = ARGS
            if "macos" not in target:
                c_args = c_args + " -flto=full"
            cmd = "{} {} {} {} {} build/program_code.c runtime/yk__main.c -o build/{} -target {}".format(
                C_COMPILER, c_args, " ".join(includes), comp_defines, ccodes, name, target) \
                .replace("runtime/yk__main.c", binary_main)
            os.system(cmd)
    cmd = paths.join("build", native_binary)
    print("-- end of bootstrap --")
    if C_COMPILER != "clang":
        os.system(cmd)
    else:
        os.system("ASAN_OPTIONS=detect_leaks=1 " + cmd)


def main() -> int:
    print("LIBS=", LIBS_PARENT_DIR)
    print("RUNTIME=", RUNTIME_DIR)
    compile_(get_config())
    return 0


if __name__ == "__main__":
    os.chdir(paths.dirname(paths.abspath(__file__)))
    main()
