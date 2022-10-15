#!/usr/bin/env python

import difflib
import glob
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
OUTPUT = os.path.join(SCRIPT_DIR, "e2e_snapshot.json")
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


def clean_line_c_compiler_paths(s: str) -> str:
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


def clean_line_invalid_data_type_path(s: str) -> str:
    compiler_error = "Failed to compile data type:"
    if s.startswith(compiler_error):
        return compiler_error
    return s


def clean_line(s: str) -> str:
    return clean_line_invalid_data_type_path(clean_line_c_compiler_paths(s))


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


def generic_tokenize(s: str) -> List[str]:
    result = s.splitlines(keepends=False)
    result = "\n".join(result)
    return result.splitlines(keepends=True)


def colour_diff(s: str) -> str:
    if s.startswith("---") or s.startswith("+++"):
        return Colors.blue(s)
    if s.startswith("+"):
        return Colors.green(s)
    if s.startswith("-"):
        return Colors.fail(s)  # fail is red
    return s


def perform_test(current: str, snapshot: str, path: str) -> bool:
    ct = generic_tokenize(current)
    snapt = generic_tokenize(snapshot)
    any_mismatches = False
    if len(ct) == len(snapt):
        for c, s in zip(ct, snapt):
            if c != s:
                any_mismatches = True
                break
    else:
        any_mismatches = True
    print(Colors.blue("Test:"), Colors.cyan(path))
    if any_mismatches:
        print("-", Colors.fail("failed"))
        difference = difflib.unified_diff(snapt, ct, fromfile='snapshot', tofile='current', lineterm="\n")
        difference = "".join([" " + colour_diff(str(x)) for x in difference])
        print(difference)
    else:
        print("-", Colors.green("passed"))
    return not any_mismatches


def main(test_mode: bool) -> int:
    print(Colors.cyan("""    
███████ ██████  ███████ 
██           ██ ██      
█████    █████  █████   
██      ██      ██      
███████ ███████ ███████ 
------ Tester ---------"""))
    results = {}
    print(Colors.warning("Generating new snapshot..."))
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
            print(Colors.warning("Executing:"), path.strip())
            so, se, ret = execute(commandline)
            output = get_cleaned_output(so, se)
            results[path.strip()] = output + "\n\nreturn := " + str(ret)
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
            for object_file in glob.glob("*.o"):
                try:
                    os.unlink(object_file)
                except OSError:
                    pass
    print(Colors.blue("Done."))

    print(Colors.warning("Testing..."))
    success = True
    if test_mode:
        try:
            with open(OUTPUT, "r+", encoding="utf-8") as h:
                original_snapshot = json.load(h)
        except OSError:
            original_snapshot = {}
        passed = True

        tests = sorted(list(results.keys()))
        for k in tests:
            v = results[k]
            original = str(original_snapshot.get(k, ""))
            try:
                del original_snapshot[k]
            except (ValueError, KeyError) as _:
                pass
            passed = perform_test(v, original, k) and passed

        tests = sorted(list(original_snapshot.keys()))
        for ok in tests:
            ov = original_snapshot[ok]
            current = ""
            passed = perform_test(current, ov, ok) and passed
        success = passed

    if success:
        print(Colors.warning("Testing:"), Colors.green("------> All passed"))
    else:
        print(Colors.warning("Testing:"), Colors.fail("------> Failed."))

    print(Colors.warning("Writing new snapshot.."))
    with open(OUTPUT, "w+", encoding="utf-8") as h:
        h.write(json.dumps(results, indent="  ", sort_keys=True))
    print(Colors.blue("Done."))
    return EXIT_SUCCESS if success else EXIT_FAILURE


if __name__ == "__main__":
    mode = None
    if len(sys.argv) == 1:
        mode = "test"
    if len(sys.argv) == 2:
        mode = sys.argv[1]
    if not mode or (mode != "test" and mode != "snapshot"):
        print("Invalid mode")
        print("Usage: python e2e.py test | python e2e.py snapshot")
        quit(EXIT_FAILURE)
    quit(main(mode == "test"))
