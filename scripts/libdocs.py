import json
import os
import re
import subprocess
import sys
import glob
from typing import Mapping

from generate_raylib import Colors

EXIT_FAILURE = 1
SCRIPT_DIR = os.path.abspath(os.path.dirname(__file__))
BIN_DIR = os.path.join(os.path.dirname(SCRIPT_DIR), "bin")
LIBS_DIR = os.path.abspath(os.path.join(os.path.dirname(SCRIPT_DIR), "libs"))
DUMPER = os.path.join(BIN_DIR, "yakshadmp")
MAX_EXECUTION_TIME_SEC = 30
OUTPUT_DIR = os.path.join(os.path.dirname(SCRIPT_DIR), "comp_output_test")


def execute(arg: str) -> (str, str, int):
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


def eprint(*args, **kwargs):
    print(*args, file=sys.stderr, **kwargs)


def as_full_mod(mod_path: str) -> str:
    parts = mod_path.split(os.path.sep)
    filename = parts[-1]
    f, _ = os.path.splitext(filename)
    parts[-1] = f
    return ".".join(parts)


def is_single_name(t: str) -> bool:
    return bool(re.fullmatch("[A-Za-z][a-zA-Z0-9_]*", t))


def import_to_name(imp: dict) -> str:
    """
    :param imp: import information dictionary
    :return: dotted path of import
    """
    return ".".join(imp["path"])


def cleanup_datatype(dt: dict, mod_name: str, imports: Mapping[str, dict]) -> dict:
    """
    Clean up modules of a data type
    :param dt: data type to consider
    :param mod_name: module name for current file
    :param imports: all imports of this current file
    :return: cleaned up data type (also clean up args for data type)
    """
    if "module" in dt:
        mod = dt["module"]
        if is_single_name(mod) and mod in imports:
            dt["module"] = import_to_name(imports[mod])
        else:
            # filename is used
            # dt["module"] = mod_name
            del dt["module"]
    if "arguments" in dt:
        dt["arguments"] = [cleanup_datatype(x, mod_name, imports) for x in dt["arguments"]]
    return dt


def cleanup_parameter(prm: dict, mod_name: str, imports: dict) -> dict:
    prm["datatype"] = cleanup_datatype(prm["datatype"], mod_name, imports)
    return prm


def cleanup_function(fnc: dict, mod_name: str, imports: dict) -> dict:
    fnc["return_type"] = cleanup_datatype(fnc["return_type"], mod_name, imports)
    fnc["parameters"] = [cleanup_parameter(x, mod_name, imports) for x in fnc["parameters"]]
    return fnc


def cleanup_class(clss: dict, mod_name: str, imports: dict) -> dict:
    clss["members"] = [cleanup_parameter(x, mod_name, imports) for x in clss["members"]]
    return clss


def cleanup_structure(structure: dict, mod_name: str) -> dict:
    imports = {x["alias"]: x for x in structure["imports"]}
    structure["functions"] = sorted([cleanup_function(x, mod_name, imports) for x in structure["functions"]],
                                    key=lambda x: x["name"])
    structure["global_consts"] = sorted(
        [cleanup_parameter(x, mod_name, imports) for x in structure["global_consts"]], key=lambda x: x["name"])
    structure["classes"] = sorted([cleanup_class(x, mod_name, imports) for x in structure["classes"]],
                                  key=lambda x: x["name"])

    return structure


#####################################
#      ╔╦╗┬┌─┐┌─┐┬  ┌─┐┬ ┬
#       ║║│└─┐├─┘│  ├─┤└┬┘
#      ═╩╝┴└─┘┴  ┴─┘┴ ┴ ┴
#####################################

class Buf:
    def __init__(self):
        self.buffer = []
        self.color_text = []

    def append(self, text: str) -> 'Buf':
        self.buffer.append(text)
        self.color_text.append(text)
        return self

    def append_to_normal_and_color_texts(self, normal: str, color_text: str) -> 'Buf':
        self.buffer.append(normal)
        self.color_text.append(color_text)
        return self

    def append_cyan(self, text: str) -> 'Buf':
        self.buffer.append(text)
        self.color_text.append(Colors.cyan(text))
        return self

    def append_blue(self, text: str) -> 'Buf':
        self.buffer.append(text)
        self.color_text.append(Colors.blue(text))
        return self

    def append_green(self, text: str) -> 'Buf':
        self.buffer.append(text)
        self.color_text.append(Colors.green(text))
        return self

    def append_yellow(self, text: str) -> 'Buf':
        self.buffer.append(text)
        self.color_text.append(Colors.warning(text))
        return self

    def append_red(self, text: str) -> 'Buf':
        self.buffer.append(text)
        self.color_text.append(Colors.fail(text))
        return self

    def build(self) -> str:
        return "".join(self.buffer)

    def build_color(self) -> str:
        return "".join(self.color_text)


def display_datatype(buf: Buf, dt: dict):
    if "module" in dt and dt["module"]:
        buf.append_blue(dt["module"])
        buf.append_blue(".")
    buf.append_blue(dt["type"])
    if "arguments" in dt and dt["arguments"]:
        buf.append_red("[")
        for i, arg in enumerate(dt["arguments"]):
            if i != 0:
                buf.append_red(", ")
            display_datatype(buf, arg)
        buf.append_red("]")


def display_comment(buf: Buf, element: dict):
    if "comment" in element and element["comment"]:
        comment: str = element["comment"]
        comment_lines = comment.splitlines(keepends=False)
        for single_comment in comment_lines:
            buf.append('\n')
            buf.append_yellow("# ")
            buf.append_yellow(single_comment)


def display_param(buf: Buf, param: dict):
    buf.append(param["name"])
    buf.append_red(": ")
    display_datatype(buf, param["datatype"])


def display_function(buf: Buf, fnc: dict):
    buf.append_green("def ")
    buf.append(fnc["name"])
    buf.append_red("(")
    for i, arg in enumerate(fnc["parameters"]):
        if i != 0:
            buf.append_red(", ")
        display_param(buf, arg)
    buf.append_red(") -> ")
    display_datatype(buf, fnc["return_type"])
    display_comment(buf, fnc)


def display_class(buf: Buf, fnc: dict):
    buf.append_green("class ")
    buf.append_blue(fnc["name"])
    display_comment(buf, fnc)
    if fnc["members"]:
        buf.append_red(": ")
        buf.append('\n')
        for i, arg in enumerate(fnc["members"]):
            if i != 0:
                buf.append_red('\n')
            buf.append("    ")
            display_param(buf, arg)


#####################################

def main():
    structures = {}
    files = []
    # Scan
    for mod_full_filepath in glob.glob(os.path.join(LIBS_DIR, '**', '*.yaka'), recursive=True):
        print("!!!<!-- parsing", Colors.cyan(mod_full_filepath), "-->")
        yaksha_mod = as_full_mod(mod_full_filepath.replace(LIBS_DIR, "")[1:])
        sout, serr, ret = execute(DUMPER + " \"" + mod_full_filepath + "\"")
        if ret != 0:
            eprint(Colors.fail("Failed to parse ") + yaksha_mod)
            eprint()
            eprint(Colors.fail(sout + serr))
            return

        try:
            structures[yaksha_mod] = cleanup_structure(json.loads(sout), yaksha_mod)
        except json.decoder.JSONDecodeError:
            print(Colors.fail(sout))
            raise
        files.append((yaksha_mod, mod_full_filepath))

    with open(os.path.join(OUTPUT_DIR, "docs.json"), "w+", encoding="utf-8") as h:
        json.dump(structures, h, indent="  ", sort_keys=True)

    # Sort
    files = sorted(files, key=lambda x: x[0])
    # Display
    print("---")
    for yaksha_mod, mod_full_filepath in files:
        print(Colors.cyan("## ") + Colors.blue(yaksha_mod))
        print("---")
        print("```yaksha")
        for f in structures[yaksha_mod]["global_consts"]:
            buf = Buf()
            display_param(buf, f)
            display_comment(buf, f)
            print(buf.build_color())

        for f in structures[yaksha_mod]["classes"]:
            buf = Buf()
            display_class(buf, f)
            print(buf.build_color())

        for f in structures[yaksha_mod]["functions"]:
            buf = Buf()
            display_function(buf, f)
            print(buf.build_color())

        print("```")
        print("---")


if __name__ == "__main__":
    main()
