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
import os
import os.path

CPP_TEMPLATE = r"""
#ifndef YAKSHA_LISP_PRELUDE_H
#define YAKSHA_LISP_PRELUDE_H
#include <string>
const std::string YAKSHA_LISP_PRELUDE = R"<><><><>(
$CONTENT$
)<><><><>";
#endif
""".strip()


def get_middle_text(s, start, end):
    # https://stackoverflow.com/a/18790509/
    return s[s.find(start) + len(start):s.rfind(end)]


def main():
    os.chdir(os.path.dirname(os.path.dirname(__file__)))
    with open(os.path.join(".", "src", "yaksha_lisp", "prelude_template.yaka"), "r") as template_f:
        template = get_middle_text(template_f.read(), "# _ START _ #", "# _ END _ #")
    with open(os.path.join(".", "src", "yaksha_lisp", "prelude_tokens.yaka"), "r") as tokens_f:
        tokens = tokens_f.read()
    with open(os.path.join(".", "src", "yaksha_lisp", "prelude_token_gen.yaka"), "r") as tg:
        token_gen = tg.read()
    with open(os.path.join(".", "src", "yaksha_lisp", "prelude.h"), "w+") as prelude_f:
        prelude_code = template.replace("    # $TOKEN_CONSTS$", tokens)
        prelude_code = prelude_code.replace("    # $TOKEN_GENERATION$ #", token_gen)
        prelude_f.write(CPP_TEMPLATE.replace("$CONTENT$", prelude_code))


if __name__ == "__main__":
    main()
