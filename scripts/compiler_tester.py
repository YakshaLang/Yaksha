import argparse
import os
import subprocess
import sys

from scripts.kabaraya import Colors

EXIT_FAILURE = 1
SCRIPT_DIR = os.path.abspath(os.path.dirname(__file__))
BIN_DIR = os.path.join(os.path.dirname(SCRIPT_DIR), "bin")
COMPILER = os.path.join(BIN_DIR, "yakshac")
MAX_EXECUTION_TIME_SEC = 2
TEST_DIR = os.path.join(os.path.dirname(SCRIPT_DIR), "comp_output_test")


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


def main():
    parser = argparse.ArgumentParser(
        "compiler_tester.py",
        description="Test Yaksha Compiler with a given code file")
    parser.add_argument("code", help="Code file", type=str)
    args = parser.parse_args()
    code_file = os.path.abspath(args.code)
    print(Colors.green("Program: ") + Colors.cyan(os.path.basename(code_file)))
    code, err, ret = execute(" ".join([COMPILER, code_file]))
    if ret != 0:
        print(Colors.cyan("--Yaksha Compiler--"))
        if code:
            eprint(Colors.fail(code))
        if err:
            eprint(Colors.fail(err))
        print(Colors.cyan("----"))
        quit(EXIT_FAILURE)
    os.chdir(TEST_DIR)
    with open("test.c", "w+") as h:
        h.write(code)
    _, err, ret = execute("gcc -I. -fsanitize=address -ggdb -g -O0 test.c")
    if ret != 0:
        print(Colors.cyan("--GCC--"))
        if err:
            eprint(Colors.fail(err))
        print(Colors.cyan("----"))
        quit(EXIT_FAILURE)
    print(Colors.cyan("<<------>>"))
    out, err, ret = execute("./a.out")
    if out:
        print(out)
    if err:
        eprint(err)
    print(Colors.cyan("<<------>>"))
    if ret == 0:
        print(Colors.cyan("ret ="), Colors.green(ret))
    else:
        print(Colors.cyan("ret ="), Colors.fail(ret))


if __name__ == "__main__":
    main()
