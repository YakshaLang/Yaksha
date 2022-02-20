import argparse
import os
import webbrowser

from compiler_tester import eprint, execute
from kabaraya import Colors

EXIT_FAILURE = 1
SCRIPT_DIR = os.path.abspath(os.path.dirname(__file__))
BIN_DIR = os.path.join(os.path.dirname(SCRIPT_DIR), "bin")
VZ_BIN = os.path.join(BIN_DIR, "yakshavz")
MAX_EXECUTION_TIME_SEC = 2
TEST_DIR = os.path.join(os.path.dirname(SCRIPT_DIR), "comp_output_test")


def main():
    parser = argparse.ArgumentParser(
        "viz.py",
        description="Visualize AST")
    parser.add_argument("code", help="Code file", type=str)
    args = parser.parse_args()
    code_file = os.path.abspath(args.code)
    print(Colors.green("Program: ") + Colors.cyan(os.path.basename(code_file)))
    code, err, ret = execute(" ".join([VZ_BIN, code_file]))
    if ret != 0:
        print(Colors.cyan("--Parser--"))
        if code:
            eprint(Colors.fail(code))
        if err:
            eprint(Colors.fail(err))
        print(Colors.cyan("----"))
        quit(EXIT_FAILURE)
    os.chdir(TEST_DIR)
    with open("out.html", "w+") as h:
        h.write(code)
    fpath = os.path.abspath("out.html")
    if os.name == 'nt':
        fpath = fpath.replace("\\", "/")
        fpath += "/"
    fpath = "file://" + fpath
    print(fpath)
    webbrowser.open_new_tab(fpath)


if __name__ == "__main__":
    main()
