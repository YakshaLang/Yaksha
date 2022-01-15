import os
import subprocess
import sys

ROOT = os.path.dirname(os.path.dirname(__file__))
COMPILER = os.path.join(ROOT, "bin", "yakshac")
TEMP_DIR = os.path.join(ROOT, "comp_output_test")
TEMP = os.path.join(TEMP_DIR, "test.c")
BINARY = os.path.join(TEMP_DIR, "a.out")


def main():
    if len(sys.argv) < 2:
        print("Usage compiler_check.py code.yaka")
        quit(1)
    os.chdir(ROOT)
    code: str = sys.argv[1]
    c_code: str = subprocess.check_output(
        [COMPILER, os.path.abspath(code)],
        encoding="utf-8", universal_newlines=True, stderr=subprocess.STDOUT)
    with open(TEMP, "w+", encoding="utf-8") as h:
        h.write(c_code)
    try:
        os.unlink(BINARY)
    except OSError:
        pass
    os.chdir(TEMP_DIR)
    print("--gcc output--")
    print(subprocess.check_output(
        ["gcc", "-I" + TEMP_DIR,
         "-fsanitize=address", "-ggdb", "-g", "-O0", TEMP],
        encoding="utf-8", universal_newlines=True,
        stderr=subprocess.STDOUT))
    print("--output--")
    print(subprocess.check_output(
        [BINARY],
        encoding="utf-8", universal_newlines=True, stderr=subprocess.STDOUT))


if __name__ == "__main__":
    main()
