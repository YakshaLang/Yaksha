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
