import json
import os
import subprocess
import sys
from typing import Union, List

from generate_raylib import Colors

EXIT_FAILURE = 1
EXIT_SUCCESS = 0
SCRIPT_DIR = os.path.abspath(os.path.dirname(__file__))
LIBS_DIR = os.path.abspath(os.path.join(os.path.dirname(SCRIPT_DIR), "libs"))
CARPNTR = os.path.abspath(os.path.join(os.path.dirname(SCRIPT_DIR), "carpntr", "build", "carpntr"))
MAX_EXECUTION_TIME_SEC = 30
OUTPUT = os.path.join(os.path.dirname(SCRIPT_DIR), "comp_output_test", "e2e.json")
E2E_FILES = os.path.join(SCRIPT_DIR, "e2e_files")


def execute(arg: Union[str, List[str]]) -> (str, str, int):
    d = dict(os.environ)
    proc = subprocess.Popen(
        arg,
        stdout=subprocess.PIPE,
        stderr=subprocess.PIPE,
        encoding="utf-8",
        universal_newlines=True,
        # shell=True,
        env=d)
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


def main() -> int:
    print(Colors.cyan("""    
███████ ██████  ███████ 
██           ██ ██      
█████    █████  █████   
██      ██      ██      
███████ ███████ ███████ 
------ Testing --------
-- Snapshot Generator -
"""))
    results = {}
    with open(E2E_FILES, "r", encoding="utf=8") as h:
        for path in h:
            full_path = os.path.abspath(os.path.join(os.path.dirname(SCRIPT_DIR), path.strip()))
            parent = os.path.dirname(full_path)
            filename = os.path.basename(full_path)
            os.chdir(parent)
            commandline = [CARPNTR, "-R", filename]
            print(Colors.warning("Executing:"))
            print(Colors.blue("- dir:"), Colors.cyan(parent))
            print(Colors.blue("- cmd:"), Colors.cyan(commandline))
            so, se, ret = execute(commandline)
            print(Colors.fail("-" * 40))
            print(so)
            print(se)
            print(Colors.fail("-" * 40))
            results[path.strip()] = {"o": so, "e": se, "ret": ret}
    with open(OUTPUT, "w+", encoding="utf-8") as h:
        h.write(json.dumps(results))
    return EXIT_SUCCESS


if __name__ == "__main__":
    quit(main())
