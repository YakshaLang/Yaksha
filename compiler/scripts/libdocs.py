# ==============================================================================================
# ╦  ┬┌─┐┌─┐┌┐┌┌─┐┌─┐    Yaksha Programming Language
# ║  ││  ├┤ │││└─┐├┤     is Licensed with GPLv3 + extra terms. Please see below.
# ╩═╝┴└─┘└─┘┘└┘└─┘└─┘
# Note: libs - MIT license, runtime/3rd - various
# ==============================================================================================
# GPLv3:
#
# Yaksha - Programming Language.
# Copyright (C) 2020 - 2024 Bhathiya Perera
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
import glob
import json
import os
import re
import subprocess
import sys
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
    macro_env = sorted([(x["name"], x) for x in structure["macro_env"]], key=lambda x: x[0])
    del structure["macro_env"]
    dsl_prefix = "yaksha#macro#dsl#"
    meta_prefix = "metadata#" + dsl_prefix
    macro_comments = {x[0][len(meta_prefix):]: x[1]["comment"] for x in macro_env if x[0].startswith(meta_prefix)}
    macros = [x[0][len(dsl_prefix):] for x in macro_env if x[0].startswith(dsl_prefix)]
    structure["macros"] = [{"name": x + "!", "comment": macro_comments.get(x, "")} for x in macros]

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
            buf.append_yellow("#")
            buf.append_yellow(single_comment)


def display_param(buf: Buf, param: dict):
    buf.append(param["name"])
    buf.append_red(": ")
    display_datatype(buf, param["datatype"])


def display_mac(buf: Buf, mac: dict):
    buf.append_green("macro ")
    buf.append_cyan(mac["name"])


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

PREFIXES = {
    "## libs": """---
layout: '../layouts/LibsLayout.astro'
---

import Note from '../components/Note.astro';


# Core
Core library can be accessed by importing `libs`.

<Note> This import name is subject to change.  </Note>

""",
    "## raylib": """
# Raylib
Raylib can be accessed by importing `raylib`.
<Note>raylib is created by Ramon Santamaria and contributors.</Note>
<Note>Yaksha wraps raylib using a generator script.</Note>

""",
    "## w4": """
# WASM4
Support for WASM4 fantasy console. 
Additionally following function in `libs` work.
* `libs.random.random_u64`
* `libs.random.set_seed`

<Note>wasm4 is created by Bruno Garcia and contributors.</Note>
<Note>Yaksha wraps `wasm4.h`.</Note>

"""
}


def main():
    structures = {}
    files = []
    # Scan
    for mod_full_filepath in glob.glob(os.path.join(LIBS_DIR, '**', '*.yaka'), recursive=True):
        # print("<!-- parsing", Colors.cyan(mod_full_filepath), "-->")
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
    for yaksha_mod, mod_full_filepath in files:
        header = "## " + yaksha_mod
        if header in PREFIXES:
            print(PREFIXES[header])
        print(Colors.cyan("## ") + Colors.blue(yaksha_mod))
        print("```yaksha")

        for f in structures[yaksha_mod]["macros"]:
            buf = Buf()
            display_mac(buf, f)
            display_comment(buf, f)
            print(buf.build_color())

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
        print()

if __name__ == "__main__":
    main()
