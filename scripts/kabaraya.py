#!/usr/bin/env python
"""
Kabaraya - Fuzzy input generator
======================================
What does this do?
* Given a folder use all files inside the folder to generate random content
* Execute a binary (YakshaFuzz) with generated file as an argument
* Detect issues
    * See if binary executes and returns zero
    * Runs too long!
* This is meant to be executed by `cov` script.
* What is `uni.txt` -> this is bunch of random unicode lines.
"""
import glob
import itertools
import multiprocessing
import os.path
import random
import shutil
import subprocess
import traceback
from typing import List


class Colors:
    HEADER = '\033[95m'
    OKBLUE = '\033[94m'
    OKCYAN = '\033[96m'
    OKGREEN = '\033[92m'
    WARNING = '\033[93m'
    FAIL = '\033[91m'
    ENDC = '\033[0m'
    BOLD = '\033[1m'
    UNDERLINE = '\033[4m'

    @staticmethod
    def blue(text):
        return Colors.OKBLUE + str(text) + Colors.ENDC

    @staticmethod
    def cyan(text):
        return Colors.OKCYAN + str(text) + Colors.ENDC

    @staticmethod
    def green(text):
        return Colors.OKGREEN + str(text) + Colors.ENDC

    @staticmethod
    def warning(text):
        return Colors.WARNING + str(text) + Colors.ENDC

    @staticmethod
    def fail(text):
        return Colors.FAIL + str(text) + Colors.ENDC


SUCCESS = 1
EXCEPTION = 2
FAILED = 3
# Ensure that we are not running an endless loop? or something crazy like that
# If the parser itself goes to an endless loop we need to know as well
MAX_EXECUTION_TIME_SEC = 5
ROOT = os.path.dirname(os.path.dirname(__file__))
PROCESSES = max(1, multiprocessing.cpu_count() - 1)
INPUT_FILES = glob.glob(os.path.join(ROOT, 'test_data/**/*'), recursive=True)
TEMP = os.path.join(ROOT, "bin/fuzz")
OUTPUT_PATH = "/fuzz"
if os.name == 'nt':
    BINARY = os.path.join(ROOT, "bin\\YakshaFuzz.exe")
else:
    BINARY = os.path.join(ROOT, "./bin/YakshaFuzz")
# --- additions ---
with open(os.path.join(ROOT, "scripts", "uni.txt"), encoding="utf-8") as h:
    UNI = [x for x in h.read().split(os.linesep) if x]
    UNI = [x.split() for x in UNI]
    UNI = [x for x in itertools.chain(*UNI) if x]

KEYWORDS = ["False", "else", "import", "pass",
            "None", "break",
            "True", "class", "return",
            "and", "continue", "for", "try",
            "as", "def", "from", "while",
            "assert", "del", "not",
            "elif", "if", "or", "await", "except", "raise",
            "finally", "lambda", "nonlocal", "global", "with", "async",
            "yield", "in", "is"]

OPERATORS = "+ - * ** / // % @ << >> & | ^ ~ := < > <= >= == != ( ) " \
            "[ ] { } , : . ; @ = -> += -= *= /= //= %= @= &= |= ^= >>= <<= **=".split(" ")

INPUT_DATA = []
for i in INPUT_FILES:
    if os.path.isfile(i):
        with open(i, encoding="utf-8") as h:
            try:
                INPUT_DATA.append(h.read().splitlines())
            except UnicodeDecodeError:
                print(Colors.blue(i), "Failed to load as input")
                pass


def random_pos(item, must_have_content=False, max_iterations=100) -> int:
    try:
        x = random.choice(range(len(item)))
        if must_have_content:
            for _ in range(max_iterations):
                if item[x]:
                    return x
                else:
                    x = random.choice(range(len(item)))
            return 0
        else:
            return x
    except IndexError:
        return 0


def insert_str(string: str, str_to_insert: str, index: int) -> str:
    return string[:index] + str_to_insert + string[index:]


# --- mutators ----
def text_adder(item_list: List[str]):
    def add_stuff(input_text: List[str], _: List[List[str]]) -> List[str]:
        ch = random.choice(item_list)
        if not input_text:
            return [ch]
        copy = input_text[:]
        add_space = " " if random.choice([True, False]) else ""
        pos: int = random_pos(input_text)
        txt = input_text[pos]
        if not txt:
            copy[pos] += add_space + ch
        else:
            copy[pos] = insert_str(txt, add_space + ch, random_pos(txt))
        return copy

    return add_stuff


def add_line_from_other(input_text: List[str], input_list: List[List[str]]) -> List[str]:
    other_line = random.choice(random.choice(input_list))
    if not input_text:
        return [other_line]
    copy = input_text[:]
    pos: int = random_pos(input_text)
    copy = copy[pos:] + [other_line] + copy[pos:]
    return copy


def remove_line(input_text: List[str], _: List[List[str]]) -> List[str]:
    if not input_text:
        return input_text
    copy = input_text[:]
    pos: int = random_pos(input_text)
    del copy[pos]
    return copy


def remove_characters(input_text: List[str], _: List[List[str]]) -> List[str]:
    if not input_text:
        return input_text
    copy = input_text[:]
    pos: int = random_pos(input_text, must_have_content=True)
    txt = input_text[pos]
    if not txt:
        return copy
    p1 = random_pos(txt)
    p2 = random_pos(txt)
    start = min(p1, p2)
    end = max(p1, p2)
    txt = list(txt)
    del txt[start: end]
    copy[pos] = "".join(txt)
    return copy


def reverse_line(input_text: List[str], _: List[List[str]]) -> List[str]:
    if not input_text:
        return input_text
    copy = input_text[:]
    pos: int = random_pos(input_text, must_have_content=True)
    txt = input_text[pos]
    if not txt:
        return copy
    copy[pos] = txt[::-1]
    return copy


def shuffle_line(input_text: List[str], _: List[List[str]]) -> List[str]:
    if not input_text:
        return input_text
    copy = input_text[:]
    pos: int = random_pos(input_text, must_have_content=True)
    txt = input_text[pos]
    if not txt:
        return copy
    txt_lst = list(txt)
    random.shuffle(txt_lst)
    copy[pos] = "".join(txt_lst)
    return copy


def shuffle_lines(input_text: List[str], _: List[List[str]]) -> List[str]:
    if not input_text:
        return input_text
    copy = input_text[:]
    random.shuffle(copy)
    return copy


def add_random_indent(input_text: List[str], _: List[List[str]]) -> List[str]:
    if not input_text:
        return input_text
    copy = input_text[:]
    pos: int = random_pos(input_text)
    copy[pos] = random.choice([" ", " \t", "  ", "    ", "\t", "\t\t"]) + copy[pos]
    return copy


MUTATORS = [
    # Add random unicode to random line of input
    text_adder(UNI),
    # Add random operators to random line of input
    text_adder(OPERATORS),
    # Add keywords to random line of input
    text_adder(KEYWORDS),
    # Add new lines
    text_adder(["\r", "\r\n", "\n"]),
    # Add tabs or spaces to random line of input
    text_adder([" ", "\t"]),
    # Add empty values
    text_adder(["\"\"", "0", "[]", "{}", "()"]),
    # Add random letters
    text_adder(list("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789ea._-")),
    # Add partial operators to a random line
    text_adder(list(set(list("".join(OPERATORS))))),
    # Add line from another example
    add_line_from_other,
    # Remove a line
    remove_line,
    # Remove characters from a random line
    remove_characters,
    remove_characters,
    # Reverse a random line's chars
    reverse_line,
    # Jumble up input lines
    shuffle_line,
    shuffle_lines,
    # Insert a random indent, can be broken indents
    add_random_indent,
]


def execute(arg: str):
    args = [os.path.abspath(BINARY), os.path.abspath(arg)]
    fuzz_process = subprocess.Popen(args, stdout=subprocess.PIPE, stderr=subprocess.PIPE, encoding="utf-8",
                                    universal_newlines=True)
    so, se = "", ""
    try:
        so, se = fuzz_process.communicate(timeout=MAX_EXECUTION_TIME_SEC)
        return_value = fuzz_process.returncode
    except subprocess.TimeoutExpired:
        fuzz_process.kill()
        fuzz_process.communicate()
        print("Timed out - ", Colors.fail(arg))
        return -1
    if return_value != 0:
        print("Found fuzz error", Colors.fail(arg))
        print(so)
        print(se)
    return return_value


def run_mutant(idx: str):
    return run_fuzz(idx, create_mutant())


def run_fuzz(idx, mutated_data):
    fname = "fuzz_" + idx + ".input"
    fname = os.path.abspath(os.path.join(TEMP, fname))
    with open(fname, "w+", encoding="utf-8") as fuzz_file:
        fuzz_file.write("\n".join(mutated_data))
    if execute(fname) == 0:
        os.unlink(fname)
        return SUCCESS, "", mutated_data
    return FAILED, fname, mutated_data


def create_mutant():
    mutated_data = random.choice(INPUT_DATA)
    for _ in range(random.randint(0, 100)):
        mutator = random.choice(MUTATORS)
        try:
            mutated_data = mutator(mutated_data, INPUT_DATA)
        except IndexError:
            print(traceback.format_exc())
    return mutated_data


def prange(v):
    try:
        import tqdm
        return tqdm.tqdm(v, leave=False)
    except ImportError:
        return v


def progress(v: int):
    try:
        import tqdm
        return tqdm.tqdm(total=v, leave=False)
    except ImportError:
        return None


if __name__ == "__main__":
    print(Colors.blue("Kabaraya Fuzzer is running.. watch-out!"))
    os.chdir(ROOT)
    # Run without mutating as well.
    for int_id, non_mutant in enumerate(prange(INPUT_DATA)):
        r, f, d = run_fuzz("non_mutant." + str(int_id), non_mutant)
        if r == FAILED:
            print(Colors.fail("Crashed on - "), Colors.cyan(os.path.basename(f)))
            shutil.copyfile(f, os.path.join(OUTPUT_PATH, os.path.basename(f)))
    with multiprocessing.Pool(PROCESSES) as p:
        for outer in prange(range(100)):
            to_append = []
            multiplier = 2
            pr = progress(PROCESSES * multiplier)
            for r, f, d in p.imap_unordered(run_mutant, [str(outer) + "_" + str(x) for x in range(PROCESSES * multiplier)]):
                if pr:
                    pr.update()
                if r == FAILED:
                    print(Colors.fail("Crashed on - "), Colors.cyan(os.path.basename(f)))
                    shutil.copyfile(f, os.path.join(OUTPUT_PATH, os.path.basename(f)))
                if r != EXCEPTION:
                    to_append.append(d)
            if pr:
                pr.close()
            INPUT_DATA += to_append
            if len(INPUT_DATA) > 1000:
                INPUT_DATA = INPUT_DATA[-999:]
    print(Colors.cyan("Completed Kabaraya."))