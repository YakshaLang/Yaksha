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
LICENSE = \
    """ ============================================================================================== 
     ╦  ┬┌─┐┌─┐┌┐┌┌─┐┌─┐    Yaksha Programming Language
     ║  ││  ├┤ │││└─┐├┤     is Licensed with GPLv3 + extra terms. Please see below.
     ╩═╝┴└─┘└─┘┘└┘└─┘└─┘    
                            Note: libs - MIT license, runtime/3rd - various
    ==============================================================================================  
    GPLv3:
     
    Yaksha - Programming Language. 
    Copyright (C) 2020 - 2023 Bhathiya Perera
    
    This program is free software: you can redistribute it and/or modify it under the terms
    of the GNU General Public License as published by the Free Software Foundation,
    either version 3 of the License, or (at your option) any later version.
    
    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
    or FITNESS FOR A PARTICULAR PURPOSE. 
    See the GNU General Public License for more details.
    
    You should have received a copy of the GNU General Public License along with this program.
    If not, see https://www.gnu.org/licenses/.
     
    ==============================================================================================
    Additional Terms:
     
    Please note that any commercial use of the programming language's compiler source code
    (everything except compiler/runtime, compiler/libs and compiler/3rd) require a written agreement
    with author of the language (Bhathiya Perera).
    
    If you are using it for an open source project, please give credits.
    Your own project must use GPLv3 license with these additional terms.
    
    You may use programs written in Yaksha/YakshaLisp for any legal purpose
    (commercial, open-source, closed-source, etc) as long as it agrees
    to the licenses of linked runtime libraries (see compiler/runtime/README.md).
 
     ==============================================================================================""".splitlines(
        keepends=False)

import glob
import os
import os.path

LICENSE = [x.strip() for x in LICENSE]

EXCLUDED = {"runtime", "libs", "test_data", "test_libs", "bin", "3rd", "comp_output_test", "cmake-build-debug",
            "cmake-build-debug-coverage", ".idea", ".git"}

COMMENT = {".h": "//", ".cpp": "//", ".yaka": "#", ".py": "#"}

COMPILER_ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))


def first_line(fp: str) -> str:
    with open(os.path.join(COMPILER_ROOT, fp), "r+", encoding="utf-8") as h:
        return h.readline().strip()


def add_license(fp: str, ext):
    with open(os.path.join(COMPILER_ROOT, fp), "r+", encoding="utf-8") as h:
        text = h.read()
    cmt = COMMENT[ext] + " "
    license = os.linesep.join([cmt + x for x in LICENSE])
    with open(os.path.join(COMPILER_ROOT, fp), "w+", encoding="utf-8") as h:
        h.write(license + os.linesep + text)


def main():
    for f in glob.glob(COMPILER_ROOT + "/**/*.*", recursive=True):
        fp = os.path.relpath(f, COMPILER_ROOT).replace("\\", "/")
        try:
            base, fx = fp.split('/', 1)
        except ValueError:
            continue
        if base in EXCLUDED or os.path.basename(fp).startswith("prelude_"):
            continue
        _, ext = os.path.splitext(fx)
        if ext in COMMENT and COMMENT[ext] + " " + LICENSE[0] != first_line(fp):
            print("updated: ", fp)
            add_license(fp, ext)


if __name__ == "__main__":
    main()
