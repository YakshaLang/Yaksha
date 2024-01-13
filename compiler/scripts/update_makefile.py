# ==============================================================================================
# ╦  ┬┌─┐┌─┐┌┐┌┌─┐┌─┐    Yaksha Programming Language
# ║  ││  ├┤ │││└─┐├┤     is Licensed with GPLv3 + exta terms. Please see below.
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
# !/usr/bin/env python
"""
When you run this script this will -
Update CMakeLists.txt with .cpp & .h files.
"""
import os.path
from typing import List, Tuple

IGNORE = ["main.cpp", "test_main.cpp", "fuzz_main.cpp", "viz_main.cpp",
          "ast_json.cpp", "utf8proc_data.c", "print_str.c", "dump.cpp",
          "comp_main.cpp", "reloader.cpp", "reloader_alt.cpp", "yk__wasm4_libc.c",
          "yk__fake_whereami.c", "yk.cpp", "carpntr_wrapper.cpp", "lisp_main.cpp",
          "html_gen.cpp", "_include_io.c", "_include_mman_win.c", "_include_bstr.c"]


def get_immediate_sub_dirs(directory: str) -> List[str]:
    return [os.path.join(directory, x) for x in os.listdir("./" + directory)
            if x not in IGNORE and os.path.isdir(os.path.join(directory, x))]


def find_files_(directory: str) -> Tuple[List[str], List[str], List[str]]:
    files = [x for x in os.listdir("./" + directory)
             if x not in IGNORE and os.path.isfile(os.path.join(directory, x))]
    cpp_files = sorted([x for x in files if x.endswith(".cpp") or x.endswith(".c")])
    objects = sorted([x.replace(".cpp", ".o").replace(".c", ".o") for x in cpp_files])
    objects = [os.path.join("build", x) for x in objects]
    headers = sorted([x for x in files if x.endswith(".h")])
    headers = [os.path.join(directory, x) for x in headers]
    cpp_files = [os.path.join(directory, x) for x in cpp_files]
    return cpp_files, headers, objects


def sort_and_standardize(files: List[str]) -> List[str]:
    """
    Sort given file paths and replace path chars to standard
    :param files: list of files
    :return: list of files
    """
    return sorted([x.replace("\\", "/") for x in files])


def find_files_2_levels(directory: str) -> Tuple[List[str], List[str], List[str]]:
    sub = get_immediate_sub_dirs(directory)
    level2 = [get_immediate_sub_dirs(x) for x in sub]
    for dirs in level2:
        sub += dirs
    cpp_files = []
    headers = []
    objects = []
    for dir_ in [directory] + sub:
        c, h, o = find_files_(dir_)
        cpp_files += c
        headers += h
        objects += o
    return sort_and_standardize(cpp_files), sort_and_standardize(headers), sort_and_standardize(objects)


def update_cmake_file(headers: List[str], cpp_files: List[str], marker: str):
    fmt = "        {files}) " + marker
    with open("CMakeLists.txt") as h:
        cmake_file = h.read()
    lines = []
    for line in cmake_file.splitlines():
        if marker in line:
            sources = headers + cpp_files
            replacement = " ".join(sources)
            replacement = replacement.replace("\\", "/")
            lines.append(fmt.format(files=replacement))
        else:
            lines.append(line)
    with open("CMakeLists.txt", "w+") as h:
        h.write('\n'.join(lines) + '\n')


def update_hammer_file(cpp, marker):
    fmt = "sources={files}" + marker
    with open("hammer.toml") as h:
        cmake_file = h.read()
    lines = []
    for line in cmake_file.splitlines():
        if marker in line:
            sources = ['"' + x + '"' for x in cpp]
            replacement = ", ".join(sources)
            replacement = "[" + replacement + "]"
            replacement = replacement.replace("\\", "/")
            lines.append(fmt.format(files=replacement))
        else:
            lines.append(line)
    with open("hammer.toml", "w+") as h:
        h.write('\n'.join(lines) + '\n')


def main():
    # Look for given markers in CMakeLists.txt and update with files.
    location_markers = (("src", "# update_makefile.py SRC"),
                        ("tests", "# update_makefile.py TESTS"),
                        )
    for directory, marker in location_markers:
        cpp_files, headers, _ = find_files_2_levels(directory)
        update_cmake_file(headers, cpp_files, marker)

    # Only 1 level directory scanning, so we do not scan raylib stuff
    directory, marker = "runtime", "# update_makefile.py YK_RUNTIME"
    cpp_files, headers, _ = find_files_(directory)
    update_cmake_file(headers, cpp_files, marker)
    # Update hammer.toml
    files = find_files_2_levels("src")[0]
    update_hammer_file(files, " # update_makefile.py HAMMER_CPP")


if __name__ == "__main__":
    # Set work directory to be that of project root.
    os.chdir(os.path.dirname(os.path.dirname(__file__)))
    main()
