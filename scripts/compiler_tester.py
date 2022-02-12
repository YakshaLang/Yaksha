import argparse
import os
import subprocess

SCRIPT_DIR = os.path.abspath(os.path.dirname(__file__))
BIN_DIR = os.path.join(os.path.dirname(SCRIPT_DIR), "bin")
COMPILER = os.path.join(BIN_DIR, "yakshac")


def main():
    parser = argparse.ArgumentParser("compiler_tester.py",
                                     description="Test Yaksha Compiler with a given code file")
    parser.add_argument("code", help="Code file", type=str)
    args = parser.parse_args()
    code_file = os.path.abspath(args.code)
    code = subprocess.check_output([COMPILER, code_file])
    os.chdir(SCRIPT_DIR)
    with open("test.c", "wb+") as h:
        h.write(code)
    subprocess.check_call("gcc -I. -fsanitize=address -ggdb -g -O0 test.c", shell=True)
    print("Program: " + os.path.basename(code_file))
    print("<<------>>")
    print(subprocess.check_output(["./a.out"], encoding="utf-8"))
    print("<<------>>")


if __name__ == "__main__":
    main()
