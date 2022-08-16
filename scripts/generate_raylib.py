import json
import os
import re
import subprocess
import sys
from typing import List, Optional

EXIT_FAILURE = 1
SCRIPT_DIR = os.path.abspath(os.path.dirname(__file__))
BIN_DIR = os.path.join(os.path.dirname(SCRIPT_DIR), "bin")
LIBS_DIR = os.path.abspath(os.path.join(os.path.dirname(SCRIPT_DIR), "libs"))
RAYLIB_OUTPUT_MAIN = os.path.join(LIBS_DIR, "raylib.yaka")
RAYGUI_OUTPUT_MAIN = os.path.join(LIBS_DIR, "raylib", "gui.yaka")
RAYMATH_OUTPUT_MAIN = os.path.join(LIBS_DIR, "raylib", "math.yaka")
RAYGL_OUTPUT_MAIN = os.path.join(LIBS_DIR, "raylib", "gl.yaka")
RUNTIME_DIR = os.path.abspath(os.path.join(os.path.dirname(SCRIPT_DIR), "runtime"))
RAYLIB_HEADER = os.path.join(RUNTIME_DIR, "raylib", "src", "raylib.h")
RAYGUI_HEADER = os.path.join(RUNTIME_DIR, "raygui", "src", "raygui.h")
RAYMATH_HEADER = os.path.join(RUNTIME_DIR, "raylib", "src", "raymath.h")
RAYGL_HEADER = os.path.join(RUNTIME_DIR, "raylib", "src", "rlgl.h")
DUMPER = os.path.join(BIN_DIR, "raylib-parser")
if os.name == 'nt':
    DUMPER += ".exe"
MAX_EXECUTION_TIME_SEC = 3
OUTPUT_DIR = os.path.join(os.path.dirname(SCRIPT_DIR), "comp_output_test")
OUT = os.path.join(OUTPUT_DIR, "raylib.json")
PREFIX = ""

FILE_BEGIN = """
# -- Raylib Wrapper for Yaksha --- 
# This is generated with generate_raylib.py, Uses raylib_parser.c and raylib.h

import libs.c

$REPLACE_ME$

@nativedefine("char[32]")
class CChar32:
    pass

@nativedefine("float[2]")
class CFloat2:
    pass

@nativedefine("float[4]")
class CFloat4:
    pass

@nativedefine("Matrix[2]")
class DTMatrix2:
    pass

@nativedefine("rAudioBuffer *")
class RAudioBufferPtr:
    pass

@nativedefine("rAudioProcessor *")
class RAudioProcessorPtr:
    pass
""".strip() + "\n\n"


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


F_DT = {
    "const char *": {"t": "str", "del": "yk__sdsfree($)", "conv": None},
    "char *": {"t": "str", "del": "yk__sdsfree($)", "conv": None},
    "char": {"t": "int", "del": None, "conv": "(?)$"},
    "int": {"t": "int", "del": None, "conv": "(?)$"},
    "unsigned int": {"t": "u32", "del": None, "conv": "(?)$"},
    "unsigned char": {"t": "int", "del": None, "conv": "(?)$"},
    "long": {"t": "i64", "del": None, "conv": "(?)$"},
    "unsigned long": {"t": "u64", "del": None, "conv": "(?)$"},
    "short": {"t": "int", "del": None, "conv": "(?)$"},
    "unsigned short": {"t": "int", "del": None, "conv": "(?)$"},
    "float": {"t": "float", "del": None, "conv": None},
    "double": {"t": "f64", "del": None, "conv": None},
    "void *": {"t": "c.VoidPtr", "del": None, "conv": None},
    "bool": {"t": "bool", "del": None, "conv": None},
    "void": {"t": "None", "del": None, "conv": None},
}
R_DT = {
    "const char *": "Const[c.CStr]",
    "char *": "c.CStr",
}
S_DT = {
    "char": "c.CChar",
    "int": "c.CInt",
    "unsigned int": "c.CUInt",
    "unsigned char": "c.CUChar",
    "long": "c.CLong",
    "unsigned long": "c.CULong",
    "short": "c.CShort",
    "unsigned short": "c.CUShort",
    "void *": "c.VoidPtr",
    "char *": "c.CStr",
    "char **": "Ptr[Ptr[c.CChar]]",
    "const char **": "Const[Ptr[Ptr[c.CChar]]]",
    "bool": "bool",
    "float": "float",
    "float *": "Ptr[c.CFloat]",
    "int *": "Ptr[c.CInt]",
    "const int *": "Const[Ptr[c.CInt]]",
    "const void *": "Const[c.VoidPtr]",
    "unsigned char *": "Ptr[c.CUChar]",
    "const unsigned char *": "Const[Ptr[c.CUChar]]",
    "unsigned short *": "Ptr[c.CUShort]",
    "unsigned int *": "Ptr[c.CUInt]",
    "float[4]": "CFloat4",
    "float[2]": "CFloat2",
    "char[32]": "CChar32",
    "Matrix[2]": "DTMatrix2",
    "rAudioBuffer *": "RAudioBufferPtr",
    "rAudioProcessor *": "RAudioProcessorPtr",
    "double": "f64",
}
S_DT_MUST_PREFIX = {"CFloat4", "CFloat2", "CChar32", "DTMatrix2", "RAudioBufferPtr", "RAudioProcessorPtr"}

NAMESPACE = set()
KNOWN_STRUCTURES = set()
KNOWN_FUNCTIONS = set()
CANNOT_CONVERT = set()


class Code:
    def __init__(self):
        self.buf: List[str] = []
        self.indent_level = ""

    def extend(self, c: 'Code') -> 'Code':
        self.buf += c.buf
        return self

    def append(self, text, do_indent=True) -> 'Code':
        if self.indent_level and do_indent:
            self.buf.append(self.indent_level)
        self.buf.append(str(text))
        return self

    def newline(self) -> 'Code':
        self.buf.append("\n")
        return self

    def indent(self) -> 'Code':
        self.indent_level += "    "
        return self

    def dedent(self) -> 'Code':
        self.indent_level = self.indent_level[:-4]
        return self

    def comment(self, text) -> 'Code':
        self.append("# ")
        return self.append(str(text), do_indent=False)

    def as_text(self) -> str:
        return "".join(self.buf)


CODE = Code()


def underscore(word):
    # based on https://inflection.readthedocs.io/en/latest/_modules/inflection.html#underscore
    orig = word
    if orig.endswith("3D") or orig.endswith("2D"):
        word = word.replace("3D", "Thredez")
        word = word.replace("2D", "Twodez")
    word = re.sub(r"([A-Z]+)([A-Z][a-z])", r'\1_\2', word)
    word = re.sub(r"([a-z\d])([A-Z])", r'\1_\2', word)
    word = word.replace("-", "_")
    if orig.endswith("3D") or orig.endswith("2D"):
        word = word.replace("Thredez", "3d")
        word = word.replace("Twodez", "2d")
    word = word.lower()
    from update_tokens import KEYWORDS, RESERVED
    if word in KEYWORDS \
            or word in RESERVED \
            or word in ["arrput", "arrpop", "print", "println", "len", "charat", "getref"]:
        word = "p_" + word
    return word


def macro_field(f: dict) -> str:
    typ = f["type"]
    fname = underscore(f["name"])
    if fname in NAMESPACE:
        fname = "p_" + fname
    if typ not in F_DT:
        return "nn__" + fname
    conversion = F_DT[typ]
    if conversion["conv"]:
        return conversion["conv"].replace("?", typ).replace("$", "nn__" + fname)
    return "nn__" + fname


def create_macro_factory(s: dict) -> Optional[Code]:
    c = Code()
    name: str = s["name"]
    name = underscore(name)
    c.append("@nativemacro").newline()
    c.append("def ").append(name).append("(")
    for i, field in enumerate(s["fields"]):
        typ = field["type"]
        fname = underscore(field["name"])
        if fname in NAMESPACE:
            field["name"] = "p_" + fname
            fname = field["name"]
        if i != 0:
            c.append(", ")
        if typ in KNOWN_STRUCTURES or typ == s["name"]:
            c.append(fname).append(": ").append(PREFIX + typ)
        elif typ in F_DT:
            c.append(fname).append(": ").append(F_DT[typ]["t"])
        elif typ.endswith(" *") and typ[:-2] in KNOWN_STRUCTURES or typ[:-2] == name:
            # Pointer data type of something we know of
            c.append(fname).append(": ").append("Ptr[" + PREFIX + typ[:-2] + "]")
        else:
            print(Colors.fail(f"For factory -> {name}. Type {typ} was not convertable."))
            CANNOT_CONVERT.add(typ)
            return None
    c.append(") -> ").append(s["name"]).append(":").newline().indent()
    c.comment("Factory function for: " + s["name"]).newline()
    c.append("ccode").dedent().append(' """')
    c.append("(").append(s["name"]).append("){")
    for i, field in enumerate(s["fields"]):
        if i != 0:
            c.append(", ")
        c.append(macro_field(field))
    c.append("}").append('"""')
    c.newline()
    c.newline()
    NAMESPACE.add(name)
    KNOWN_FUNCTIONS.add(name)
    return c


def create_native_factory(_: dict) -> Optional[Code]:
    print(Colors.fail(f"Native factory not supported"))
    return None


def create_factory(s: dict) -> Optional[Code]:
    name: str = s["name"]
    name = underscore(name)
    if name in NAMESPACE:
        print(Colors.fail(f"{name} is redefined"))
        return None
    has_strings = False
    for field in s["fields"]:
        typ = field["type"]
        if typ in F_DT:
            if F_DT[typ]["t"] == "str":
                has_strings = True
                break
    if not has_strings:
        return create_macro_factory(s)
    return create_native_factory(s)


def convert_barebones_structure(s: dict) -> bool:
    c = Code()
    name = s["name"]
    if name in NAMESPACE:
        print(Colors.fail(f"{name} is redefined"))
        return False
    comment = s["description"]
    c.append("@nativedefine(\"").append(name).append("\")").newline()
    c.append("class ").append(name).append(":").newline().indent()
    if comment:
        c.comment(comment).newline()
    c.append("pass").dedent()
    c.newline()
    c.newline()
    CODE.extend(c)
    NAMESPACE.add(name)


def convert_structure(s: dict) -> bool:
    c = Code()
    name = s["name"]
    if name in NAMESPACE:
        print(Colors.fail(f"{name} is redefined"))
        return False
    comment = s["description"]
    c.append("@dotaccess").newline()
    c.append("@nativedefine(\"").append(name).append("\")").newline()
    c.append("class ").append(name).append(":").newline().indent()
    if comment:
        c.comment(comment).newline()
    for field in s["fields"]:
        typ = field["type"]
        fname = field["name"]
        # Add support for field comments later on
        c.append(fname).append(": ", do_indent=False)
        if typ in KNOWN_STRUCTURES or typ == name:
            c.append(PREFIX + typ, do_indent=False)
        elif typ in S_DT_MUST_PREFIX:
            c.append(PREFIX + S_DT[typ], do_indent=False)
        elif typ in S_DT:
            c.append(S_DT[typ], do_indent=False)
        elif typ.endswith(" *") and typ[:-2] in KNOWN_STRUCTURES or typ[:-2] == name:
            # Pointer data type of something we know of
            c.append("Ptr[", do_indent=False)
            c.append(PREFIX + typ[:-2], do_indent=False)
            c.append("]", do_indent=False)
        elif typ.endswith(" **") and typ[:-3] in KNOWN_STRUCTURES or typ[:-3] == name:
            # Pointer to Pointer data type of something we know of
            c.append("Ptr[Ptr[", do_indent=False)
            c.append(PREFIX + typ[:-2], do_indent=False)
            c.append("]]", do_indent=False)
        else:
            print(Colors.fail(f"For structure -> {name}. Type {typ} was not convertable."))
            CANNOT_CONVERT.add(typ)
            return False
        c.newline()
    c.newline()
    factory = create_factory(s)
    if not factory:
        return False
    c.extend(factory)
    KNOWN_STRUCTURES.add(name)
    NAMESPACE.add(name)
    CODE.extend(c)
    return True


def find_struct(name, data) -> Optional[dict]:
    for s in data["structs"]:
        if s["name"] == name:
            return dict(s)
    return None


def get_func_data_type(typ) -> Optional[str]:
    if typ in KNOWN_STRUCTURES:
        return PREFIX + typ
    elif typ in F_DT:
        return F_DT[typ]["t"]
    elif typ in S_DT_MUST_PREFIX:
        PREFIX + S_DT[typ]
    elif typ in S_DT:
        return S_DT[typ]
    elif typ.endswith(" *") and typ[:-2] in KNOWN_STRUCTURES:
        return "Ptr[" + PREFIX + typ[:-2] + "]"
    elif typ.endswith(" **") and typ[:-3] in KNOWN_STRUCTURES:
        return "Ptr[Ptr[" + PREFIX + typ[:-2] + "]]"
    elif typ.startswith("const ") and typ.endswith(" *") and typ[6:-2] in KNOWN_STRUCTURES:
        return "Const[Ptr[" + PREFIX + typ[6:-2] + "]]"
    elif typ.startswith("const ") and typ[6:] in KNOWN_STRUCTURES:
        return "Const[" + PREFIX + typ[6:] + "]"
    return None


def create_macro_function(s: dict) -> Optional[Code]:
    c = Code()
    name: str = s["name"]
    name = underscore(name)
    c.append("@nativemacro").newline()
    c.append("def ").append(name).append("(")
    rtype = get_func_data_type(s["returnType"])
    if not rtype:
        CANNOT_CONVERT.add(s["returnType"])
        return None
    for i, field in enumerate(s.get("params", [])):
        typ = field["type"]
        fname = underscore(field["name"])
        if fname in NAMESPACE:
            field["name"] = "p_" + fname
            fname = field["name"]
        if i != 0:
            c.append(", ")
        ftype = get_func_data_type(typ)
        if ftype:
            c.append(fname).append(": ").append(ftype)
        else:
            print(Colors.fail(f"For function -> {name}. Type {typ} was not convertable."))
            CANNOT_CONVERT.add(typ)
            return None
    c.append(") -> ").append(rtype).append(":").newline().indent()
    if s["description"]:
        c.comment(s["description"]).newline()
    c.append("ccode").dedent().append(' """')
    c.append(s["name"]).append("(")
    for i, field in enumerate(s.get("params", [])):
        if i != 0:
            c.append(", ")
        c.append(macro_field(field))
    c.append(")").append('"""')
    c.newline()
    c.newline()
    NAMESPACE.add(name)
    KNOWN_FUNCTIONS.add(name)
    return c


def create_native_function(s: dict) -> Optional[Code]:
    c = Code()
    name: str = s["name"]
    name = underscore(name)
    c.append("@native").newline()
    c.append("def ").append(name).append("(")
    rtype = get_func_data_type(s["returnType"])
    if not rtype:
        CANNOT_CONVERT.add(s["returnType"])
        return None
    actual_return_type = rtype
    if rtype == "str":
        actual_return_type = R_DT[s["returnType"]]
    for i, field in enumerate(s.get("params", [])):
        typ = field["type"]
        fname = underscore(field["name"])
        if fname in NAMESPACE:
            field["name"] = "p_" + fname
            fname = field["name"]
        if i != 0:
            c.append(", ")
        ftype = get_func_data_type(typ)
        if ftype:
            c.append(fname).append(": ").append(ftype)
        else:
            print(Colors.fail(f"For function -> {name}. Type {typ} was not convertable."))
            CANNOT_CONVERT.add(typ)
            return None
    c.append(") -> ").append(actual_return_type).append(":").newline().indent()
    if s["description"]:
        c.comment(s["description"]).newline()
    c.append("ccode").append(' """', do_indent=False)
    if rtype != "None":
        c.append(s["returnType"], do_indent=False).append(" temp_rl = ", do_indent=False)
    c.append(s["name"], do_indent=False).append("(", do_indent=False)
    for i, field in enumerate(s.get("params", [])):
        if i != 0:
            c.append(", ", do_indent=False)
        c.append(macro_field(field), do_indent=False)
    c.append(");", do_indent=False).newline()
    # Delete all strings
    for i, field in enumerate(s.get("params", [])):
        fname = underscore(field["name"])
        if fname in NAMESPACE:
            fname = "p_" + fname
        typ = field["type"]
        if typ in F_DT:
            ptype = F_DT[typ]
            if not ptype["del"]:
                continue
            deletion = ptype["del"].replace("$", "nn__" + fname)
            c.append(deletion).append(";", do_indent=False).newline()
    if rtype != "None":
        c.append("return temp_rl")
        c.append('"""', do_indent=False)
    else:
        c.append('"""')
    c.newline()
    c.newline()
    NAMESPACE.add(name)
    KNOWN_FUNCTIONS.add(name)
    return c


def create_function(s: dict) -> bool:
    name: str = s["name"]
    name = underscore(name)
    if name in NAMESPACE:
        print(Colors.fail(f"{name} is redefined"))
        return None
    has_strings = False
    for field in s.get("params", []):
        typ = field["type"]
        if typ in F_DT:
            if F_DT[typ]["t"] == "str":
                has_strings = True
                break
    if s["returnType"] in F_DT and F_DT[s["returnType"]]["t"] == "str":
        has_strings = True
    if not has_strings:
        f = create_macro_function(s)
    else:
        f = create_native_function(s)
    if f:
        CODE.extend(f)
    return bool(f)


def convert_enum(ev: dict) -> bool:
    name = ev["name"]
    val = ev["value"]
    comment = ev["description"]
    if name in NAMESPACE:
        print(Colors.fail(f"{name} is redefined"))
        return False
    c = Code()
    c.append(name).append(": Const[int] = ").append(val).newline()
    if comment:
        c.comment(comment).newline()
    CODE.extend(c)
    NAMESPACE.add(name)
    return True


def build(header, target_file, define="RLAPI", add_base=False):
    print(Colors.green("==============="))
    print("Building:" + Colors.cyan(os.path.basename(target_file)))
    print(Colors.green("==============="))
    if not add_base:
        CODE.buf = ["import libs.c\nimport raylib as rl\n\n"]
    else:
        CODE.buf = []
    arg = DUMPER + " " + "--input \"" + header + "\"" + " --define " + define + " --output \"" + OUT + "\" --format JSON"
    _, _, ret = execute(arg)
    if ret != 0:
        eprint("Failed to run raylib-parser")
        print(arg)
        return
    with open(OUT, "r+") as h:
        data = json.load(h)
    for e in data["enums"]:
        for ev in e["values"]:
            if not convert_enum(ev):
                print(Colors.fail("Failed to convert enum-val: " + ev["name"]))
    if add_base:
        text = FILE_BEGIN.replace("$REPLACE_ME$", CODE.as_text())
        CODE.buf = [text]
    for s in data["structs"]:
        KNOWN_STRUCTURES.add(s["name"])
    for s in data["aliases"]:
        KNOWN_STRUCTURES.add(s["name"])

    # Convert structures and aliases!
    for s in data["structs"]:
        if not convert_structure(s):
            convert_barebones_structure(s)
    for a in data["aliases"]:
        s = find_struct(a["type"], data)
        if not s:
            print(Colors.fail(f"Cannot find structure {a['type']}."))
            convert_barebones_structure({"name": a["name"], "description": a["description"]})
            continue
        s["name"] = a["name"]
        s["description"] = a["description"]
        if not convert_structure(s):
            convert_barebones_structure(s)
    for f in data["functions"]:
        if not create_function(f):
            continue
    generated = CODE.as_text()
    with open(target_file, "w+", encoding="utf-8") as h:
        h.write(generated)


def main():
    global PREFIX
    build(RAYLIB_HEADER, RAYLIB_OUTPUT_MAIN, add_base=True)
    PREFIX = "rl."
    build(RAYGUI_HEADER, RAYGUI_OUTPUT_MAIN, define="RAYGUIAPI")
    build(RAYMATH_HEADER, RAYMATH_OUTPUT_MAIN, define="RMAPI")
    build(RAYGL_HEADER, RAYGL_OUTPUT_MAIN)


if __name__ == "__main__":
    main()
