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
import os
import sys

HEADER = \
    """
// {{name}}.h
#ifndef {{name_caps}}_H
#define {{name_caps}}_H
namespace yaksha {
    struct {{name}} {
        {{name}}();
        ~{{name}}();    
    private:
    };
}
#endif
"""

CPP = \
    """
// {{name}}.cpp
#include "{{name}}.h"
using namespace yaksha;
{{name}}::{{name}}() = default;
{{name}}::~{{name}}() = default;
"""


def apply_template(templ: str, name: str) -> str:
    name_caps = name.upper()
    t = templ.lstrip()
    t = t.replace("{{name}}", name)
    t = t.replace("{{name_caps}}", name_caps)
    return t


def main():
    args = sys.argv[1:]
    if not args:
        print("usage python create_struct.py my_fancy_struct another_one")
        quit()

    os.chdir("src")
    for name in sys.argv[1:]:
        if os.path.isfile(name + ".h") or os.path.isfile(name + ".cpp"):
            yn = input("Do you want to override (enter 'y' for yes)?").strip().lower()
            if not (yn == "y" or yn == "yes"):
                print("Did not write file(s) '{0}.h' and/or '{0}.cpp'".format(name))
                continue

        with open(name + ".h", "w+") as h:
            h.write(apply_template(HEADER, name))

        with open(name + ".cpp", "w+") as h:
            h.write(apply_template(CPP, name))

        print("#include \"{0}.h\"".format(name))


if __name__ == "__main__":
    os.chdir(os.path.dirname(os.path.dirname(os.path.abspath(__file__))))
    main()
