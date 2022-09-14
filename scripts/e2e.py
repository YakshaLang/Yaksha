import json
import os
import re
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


BAD_STARTS = ["command := ", "native := ", "runtime_features := ", "Failed to execute: ", "----"]


def bad_start(s) -> bool:
    for st in BAD_STARTS:
        if s.startswith(st):
            return True
    return False


def clean_line(s: str) -> str:
    match = re.match(r"^([\\a-zA-Z0-9/:_.]+) (.+)$", s)
    if match:
        f = match.group(1)
        e = match.group(2)
        path_items = f.split(":")
        path_items[0] = os.path.basename(path_items[0])
        f = ":".join(path_items)
        text = f + " " + e
        return text.rstrip()
    return s.rstrip()


def get_cleaned_output(sout: str, serr: str) -> str:
    text = sout + "\n" + serr
    text = text.strip()
    lines = text.splitlines()
    output_lines = []
    for line in lines:
        if bad_start(line):
            continue
        output_lines.append(clean_line(line))
    return "\n".join(output_lines).strip()


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
            filename_base, _ = os.path.splitext(filename)
            os.chdir(parent)
            preserve_unix_bin = os.path.exists(filename_base)
            preserve_win_bin = os.path.exists(filename_base + ".exe")
            preserve_c_out = os.path.exists(filename_base + ".c")
            commandline = [CARPNTR, "-RS", filename]
            print(Colors.warning("Executing:"))
            print(Colors.blue("- dir:"), Colors.cyan(parent))
            print(Colors.blue("- cmd:"), Colors.cyan(commandline))
            so, se, ret = execute(commandline)
            output = get_cleaned_output(so, se)
            print(Colors.fail("-" * 40))
            print(output)
            print(Colors.fail("-" * 40))
            results[path.strip()] = {"o": output, "ret": ret}
            if not preserve_unix_bin:
                try:
                    os.unlink(filename_base)
                except OSError:
                    pass
            if not preserve_win_bin:
                try:
                    os.unlink(filename_base + ".exe")
                except OSError:
                    pass
            if not preserve_c_out:
                try:
                    os.unlink(filename_base + ".c")
                except OSError:
                    pass
    with open(OUTPUT, "w+", encoding="utf-8") as h:
        h.write(json.dumps(results))
    return EXIT_SUCCESS


if __name__ == "__main__":
    quit(main())
