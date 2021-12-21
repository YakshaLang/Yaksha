#!/usr/bin/env python
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
    os.chdir(os.path.dirname(os.path.dirname(__file__)))
    main()
