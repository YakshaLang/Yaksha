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
# Given a list of tokens generate placeholder code for tokenization
# Note: This is not a generator script. This simply generates code so you can order things!
def main():
    items = ["...", ">>=", "<<=", "+=", "-=", "*=", "/=", "%=", "&=", "^=", "|=", ">>", "<<", "++", "--", "->", "&&",
             "||",
             "<=", ">=", "==", "!=", ";", "{", "<%", "}", "%>", ",", ":", "=", "(", ")", "[", "<:", "]", ":>", ".", "&",
             "!", "~", "-", "+", "*", "/", "%", "<", ">", "^", "|", "?", "/*", "//", "#", "##"]

    items = sorted(items, key=lambda h: (h[0], -len(h)))

    x = ""
    for i, item in enumerate(items):
        if i != 0:
            x += "else "
        if len(item) == 3:
            x += f"if (current == '{item[0]}' && next == '{item[1]}' && after_next == '{item[2]}') {{ emit_tok(" \
                 f" \"{item}\", ic_token_type::TK_UNKNOWN_TOKEN_DETECTED); skip_2(); }}"
        if len(item) == 2:
            x += f"if (current == '{item[0]}' && next == '{item[1]}') {{ emit_tok(\"{item}\", " \
                 f"ic_token_type" \
                 f"::TK_UNKNOWN_TOKEN_DETECTED); skip_1(); }}"
        if len(item) == 1:
            x += f"if (current == '{item[0]}') {{ emit_tok(\"{item}\", ic_token_type" \
                 f"::TK_UNKNOWN_TOKEN_DETECTED); }}"
        x += "\n"
    print(x)


if __name__ == "__main__":
    main()
