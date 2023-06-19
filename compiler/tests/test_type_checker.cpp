#include "catch2/catch.hpp"
#include "compiler/multifile_compiler.h"
#include "utilities/error_printer.h"
#include <string>
using namespace yaksha;
#define TEST_FILE(A, E)                                                        \
  do {                                                                         \
    multifile_compiler mc{};                                                   \
    auto result = mc.compile(A);                                               \
    REQUIRE(result.failed_ == true);                                           \
    REQUIRE(!yaksha::errors::error_capture.empty());                           \
    REQUIRE(yaksha::errors::has_error(E));                                     \
  } while (0)
#define TEST_SNIPPET(S, E)                                                     \
  do {                                                                         \
    multifile_compiler mc{};                                                   \
    std::string xa = "def main() -> int:\n";                                   \
    xa += "    ";                                                              \
    xa += (S);                                                                 \
    xa += "\n"                                                                 \
          "    return 0";                                                      \
    auto result = mc.compile(xa, true, "dummy.yaka", "../libs");               \
    REQUIRE(result.failed_ == true);                                           \
    REQUIRE(!yaksha::errors::error_capture.empty());                           \
    REQUIRE(yaksha::errors::has_error(E));                                     \
  } while (0)
#define TEST_SNIPPET_FULL(S, E)                                                \
  do {                                                                         \
    multifile_compiler mc{};                                                   \
    std::string xa = (S);                                                      \
    auto result = mc.compile(xa, true, "dummy.yaka", "../libs");               \
    REQUIRE(result.failed_ == true);                                           \
    REQUIRE(!yaksha::errors::error_capture.empty());                           \
    REQUIRE(yaksha::errors::has_error(E));                                     \
  } while (0)
TEST_CASE("type checker: Bad function for qsort") {
  TEST_FILE("../test_data/bad_inputs/bad_input_sort_with_wrong_args.yaka",
            "Comparison must match with "
            "Function[In[Const[AnyPtrToConst],Const[AnyPtrToConst]],Out[int]]");
}
TEST_CASE("type checker: Passing a map to arrput") {
  TEST_FILE("../test_data/bad_inputs/arrput_map.yaka",
            "arrput() does not work with maps");
}
TEST_CASE("type checker: Passing a map to arrpop") {
  TEST_FILE("../test_data/bad_inputs/arrpop_map.yaka",
            "arrpop() does not work with maps");
}
TEST_CASE("type checker: Builtin arrnew invalid arg count") {
  TEST_SNIPPET("a: Array[int] = arrnew()",
               "Two arguments must be provided for arrnew() builtin");
}
TEST_CASE(
    "type checker: First argument must be a string literal for arrnew()") {
  TEST_SNIPPET("a: Array[int] = arrnew(1, 10)",
               "First argument to arrnew() must be a string literal");
}
TEST_CASE("type checker: First argument must be a string literal for arrnew(). "
          "Does not "
          "work with variables") {
  TEST_SNIPPET("b: str = \"str\"\n    a: Array[int] = arrnew(b, 10)",
               "First argument to arrnew() must be a string literal");
}
TEST_CASE("type checker: Second argument must be int for arrnew()") {
  TEST_SNIPPET("a: Array[int] = arrnew(\"int\", \"10\")",
               "Second argument to arrnew() must be an int");
}
TEST_CASE("type checker: Must assign to proper data structure for arrnew()") {
  TEST_SNIPPET("a: Array[str] = arrnew(\"int\", 10)",
               "Cannot assign between 2 different data types.");
}
TEST_CASE("type checker: Builtin array() invalid arg count") {
  TEST_SNIPPET("a: Array[int] = array()",
               "array() builtin expects >= 1 arguments");
}
TEST_CASE("type checker: First argument must be a string literal for array()") {
  TEST_SNIPPET("a: Array[int] = array(\"str\", 1)",
               "All arguments must match with data type passed to first "
               "argument for array() builtin");
}
TEST_CASE("type checker: First argument must be a string literal for array(). "
          "Does not "
          "work with variables") {
  TEST_SNIPPET("b: str = \"str\"\n    a: Array[int] = array(b, 10)",
               "First argument to array() must be a string literal");
}
TEST_CASE("type checker: Second argument must be int for array()") {
  TEST_SNIPPET("a: Array[int] = array(\"int\", \"10\")",
               "All arguments must match with data type passed to first "
               "argument for array() builtin");
}
TEST_CASE("type checker: Must assign to proper data structure for array()") {
  TEST_SNIPPET("a: Array[str] = array(\"int\", 10)",
               "Cannot assign between 2 different data types.");
}
TEST_CASE("type checker: Different type assignment using iif") {
  TEST_SNIPPET("a: bool = iif(True, False, 1)",
               "Second and third argument to iif() must be of same type");
}
TEST_CASE("type checker: Different type func assignment using iif") {
  TEST_SNIPPET_FULL("def f1(x: int) -> None:\n"
                    "    pass\n"
                    "def f2(y: int, z: int) -> None:\n"
                    "    pass\n"
                    "def main() -> int:\n"
                    "    a: Function[In[int],Out] = iif(True, f1, f2)\n"
                    "    return 0",
                    "You must use functions of same type for iif() builtin");
}
TEST_CASE("type checker: iif using 4 args") {
  TEST_SNIPPET("a: bool = iif(True, False, True, 2)",
               "iif() builtin expects 3 arguments");
}
TEST_CASE("type checker: iif using no arguments") {
  TEST_SNIPPET("a: bool = iif()", "iif() builtin expects 3 arguments");
}
TEST_CASE("type checker: Object creation with argument not allowed") {
  TEST_SNIPPET_FULL("class A:\n"
                    "    a: int\n"
                    "def main() -> int:\n"
                    "    a: A = A(1)\n"
                    "    return 0",
                    "Arguments for object creation is not supported");
}
TEST_CASE("type checker: assignment without definition") {
  TEST_SNIPPET("a = 1", "Assignment without definition");
}
TEST_CASE(
    "type checker: Binary operation between two different data types (meta)") {
  TEST_SNIPPET_FULL(
      "class A:\n"
      "    a: int\n"
      "def main() -> int:\n"
      "    a: int = 1\n"
      "    b: bool = a == A\n"
      "    return 0",
      "Binary operation between two different data types are not supported");
}
TEST_CASE("type checker: different type of numbers used in operators bitwise") {
  TEST_SNIPPET("a: int = 1\n"
               "    b: i8 = a & 1i8\n",
               "^ & | << >> operators work only for integers of same type");
}
TEST_CASE(
    "type checker: different type of numbers used in operators mul/div/rem") {
  TEST_SNIPPET("a: int = 1\n"
               "    b: i8 = a * 1i8\n",
               "% - * / operators work only for numbers of same type");
}
TEST_CASE(
    "type checker: different type of numbers used in operators comparison") {
  TEST_SNIPPET("a: int = 1\n"
               "    b: bool = a <= 1i8\n",
               "< > <= >= operators work only for numbers of same type");
}
TEST_CASE("type checker: + operator does not work for anything other than "
          "numbers and str") {
  TEST_SNIPPET("a: bool = True\n"
               "    b: bool = a + False\n",
               "+ operator works only for numbers of same type or strings");
}
TEST_CASE("type checker: cannot compare tuples with ==") {
  TEST_SNIPPET(
      "a: Tuple[int]\n"
      "    b: Tuple[int]\n"
      "    c: bool = a == b\n",
      "MEntry/SMEntry/Tuple cannot be compared with == or != operator");
}
TEST_CASE("type checker: cannot compare mentry with ==") {
  TEST_SNIPPET(
      "a: MEntry[int,int]\n"
      "    b: MEntry[int,int]\n"
      "    c: bool = a == b\n",
      "MEntry/SMEntry/Tuple cannot be compared with == or != operator");
}
TEST_CASE("type checker: cannot compare smentry with !=") {
  TEST_SNIPPET(
      "a: SMEntry[int]\n"
      "    b: SMEntry[int]\n"
      "    c: bool = a != b\n",
      "MEntry/SMEntry/Tuple cannot be compared with == or != operator");
}
TEST_CASE("type checker: cannot compare tuple vs smentry with !=") {
  TEST_SNIPPET(
      "a: Tuple[int]\n"
      "    b: SMEntry[int]\n"
      "    c: bool = a != b\n",
      "MEntry/SMEntry/Tuple cannot be compared with == or != operator");
}
TEST_CASE("type checker: cannot compare integers with None") {
  TEST_SNIPPET("a: int = 1\n"
               "    c: bool = a != None\n",
               "Datatype cannot be compared with None");
}
TEST_CASE("type checker: cannot compare booleans with None") {
  TEST_SNIPPET("a: bool = False\n"
               "    c: bool = a != None\n",
               "Datatype cannot be compared with None");
}
TEST_CASE(
    "type checker: cannot compare two different kinds of integers with ==") {
  TEST_SNIPPET("a: int = 1\n"
               "    c: bool = 1 == 1i8\n",
               "Cannot compare between two data types");
}
TEST_CASE(
    "type checker: cannot compare two different kinds of integers with !=") {
  TEST_SNIPPET("a: int = 1\n"
               "    c: bool = 1 != 1i8\n",
               "Cannot compare between two data types");
}
TEST_CASE("type checker: func call too few arguments") {
  TEST_SNIPPET_FULL("def fnc(a: int, b: int) -> None:\n"
                    "    pass\n"
                    "def main() -> int:\n"
                    "    fnc(1)\n"
                    "    return 0",
                    "Too few or too much arguments for function call");
}
TEST_CASE("type checker: func call too much arguments") {
  TEST_SNIPPET_FULL("def fnc(a: int, b: int) -> None:\n"
                    "    pass\n"
                    "def main() -> int:\n"
                    "    fnc(1, 2, 3, 4)\n"
                    "    return 0",
                    "Too few or too much arguments for function call");
}
TEST_CASE("type checker: func call parameter and argument mismatches") {
  TEST_SNIPPET_FULL("def fnc(a: int, b: int) -> None:\n"
                    "    pass\n"
                    "def main() -> int:\n"
                    "    fnc(1, False)\n"
                    "    return 0",
                    "Parameter & argument 2 mismatches");
}
TEST_CASE("type checker: func call parameter and argument mismatches first "
          "argument") {
  TEST_SNIPPET_FULL("def fnc(a: int, b: int) -> None:\n"
                    "    pass\n"
                    "def main() -> int:\n"
                    "    fnc(False, 3)\n"
                    "    return 0",
                    "Parameter & argument 1 mismatches");
}
TEST_CASE(
    "type checker: func call parameter and argument mismatches for varargs") {
  TEST_SNIPPET_FULL("@nativedefine(\"test\")\n"
                    "@varargs\n"
                    "def fnc(a: int, b: int) -> None:\n"
                    "    pass\n"
                    "def main() -> int:\n"
                    "    fnc(1, 3, 2, 3, False)\n"
                    "    return 0",
                    "Variable argument: 5 mismatches");
}
TEST_CASE("type checker: func ptr call parameter and argument mismatches") {
  TEST_SNIPPET_FULL("def fnc(a: int, b: int) -> None:\n"
                    "    pass\n"
                    "def main() -> int:\n"
                    "    f1: Function[In[int,int],Out] = fnc\n"
                    "    f1(1, False)\n"
                    "    return 0",
                    "Function[] call parameter & argument 2 mismatches");
}
TEST_CASE("type checker: func ptr call parameter and argument mismatches first "
          "argument") {
  TEST_SNIPPET_FULL("def fnc(a: int, b: int) -> None:\n"
                    "    pass\n"
                    "def main() -> int:\n"
                    "    f1: Function[In[int,int],Out] = fnc\n"
                    "    f1(False, 1)\n"
                    "    return 0",
                    "Function[] call parameter & argument 1 mismatches");
}
TEST_CASE("type checker: func ptr call too much arguments") {
  TEST_SNIPPET_FULL("def fnc(a: int, b: int) -> None:\n"
                    "    pass\n"
                    "def main() -> int:\n"
                    "    f1: Function[In[int,int],Out] = fnc\n"
                    "    f1(1, 1, 1, 2)\n"
                    "    return 0",
                    "Too few or too much arguments for function call");
}
TEST_CASE("type checker: func ptr call too few arguments") {
  TEST_SNIPPET_FULL("def fnc(a: int, b: int) -> None:\n"
                    "    pass\n"
                    "def main() -> int:\n"
                    "    f1: Function[In[int,int],Out] = fnc\n"
                    "    f1(1)\n"
                    "    return 0",
                    "Too few or too much arguments for function call");
}
TEST_CASE("type checker: func ptr call output type mismatches") {
  TEST_SNIPPET_FULL("def fnc(a: int, b: int) -> int:\n"
                    "    return a + b\n"
                    "def main() -> int:\n"
                    "    f1: Function[In[int,int],Out[int]] = fnc\n"
                    "    a: bool = f1(1, 2)\n"
                    "    return 0",
                    "Cannot assign between 2 different data types.");
}
TEST_CASE("type checker: calling a non callable") {
  TEST_SNIPPET_FULL("def main() -> int:\n"
                    "    a: bool = False\n"
                    "    b: bool = a(1, 2)\n"
                    "    return 0",
                    "Calling a non callable or a non existing function");
}
TEST_CASE("type checker: logical or needs two booleans") {
  TEST_SNIPPET("a: bool = False or 1\n",
               "Both LHS and RHS of logical operator need to be boolean");
}
TEST_CASE("type checker: logical and needs two booleans") {
  TEST_SNIPPET("a: bool = True and 1\n",
               "Both LHS and RHS of logical operator need to be boolean");
}
TEST_CASE("type checker: not must follow a boolean") {
  TEST_SNIPPET("a: bool = not 1\n",
               "Invalid unary operation. Not operator must follow a boolean.");
}
TEST_CASE("type checker: not must follow a boolean (str used)") {
  TEST_SNIPPET("a: bool = not \"False\"\n", "Invalid unary operation");
}
TEST_CASE("type checker: ~ must follow an integer") {
  TEST_SNIPPET("a: int = ~False\n",
               "Bitwise not (~) is only supported for integers");
}
TEST_CASE("type checker: ~ must follow an integer (f64 used)") {
  TEST_SNIPPET("a: int = ~1.0\n",
               "Bitwise not (~) is only supported for integers");
}
TEST_CASE("type checker: ~ must follow an integer (str used)") {
  TEST_SNIPPET("a: int = ~\"Hello\"\n", "Invalid unary operation");
}
TEST_CASE("type checker: access non defined variable") {
  TEST_SNIPPET("a: int = ~1 + b\n", "Undefined name");
}
TEST_CASE("type checker: delete an integer") {
  TEST_SNIPPET("del 1u8", "Invalid delete statement used on primitives");
}
TEST_CASE("type checker: delete a float") {
  TEST_SNIPPET("del 1.0f", "Invalid delete statement used on primitives");
}
TEST_CASE("type checker: delete a bool") {
  TEST_SNIPPET("del False", "Invalid delete statement used on primitives");
}
TEST_CASE("type checker: delete a tuple") {
  TEST_SNIPPET_FULL(
      "def main() -> int:\n"
      "    a: Tuple[int]\n"
      "    del a\n"
      "    return 0",
      "Invalid delete statement used on Tuple/MEntry/SMEntry/Function");
}
TEST_CASE("type checker: delete MEntry") {
  TEST_SNIPPET_FULL(
      "def main() -> int:\n"
      "    a: MEntry[int, int]\n"
      "    del a\n"
      "    return 0",
      "Invalid delete statement used on Tuple/MEntry/SMEntry/Function");
}
TEST_CASE("type checker: delete SMEntry") {
  TEST_SNIPPET_FULL(
      "def main() -> int:\n"
      "    a: SMEntry[int]\n"
      "    del a\n"
      "    return 0",
      "Invalid delete statement used on Tuple/MEntry/SMEntry/Function");
}
TEST_CASE("type checker: delete Function") {
  TEST_SNIPPET_FULL(
      "def main() -> int:\n"
      "    a: Function[In[int],Out]\n"
      "    del a\n"
      "    return 0",
      "Invalid delete statement used on Tuple/MEntry/SMEntry/Function");
}
TEST_CASE("type checker: delete Function main()") {
  TEST_SNIPPET_FULL(
      "def main() -> int:\n"
      "    del main\n"
      "    return 0",
      "Invalid delete statement used on Tuple/MEntry/SMEntry/Function");
}
TEST_CASE("type checker: tuple [] access must use literal") {
  TEST_SNIPPET_FULL("def main() -> int:\n"
                    "    a: Tuple[int]\n"
                    "    b: int = 0\n"
                    "    c: int = a[b]\n"
                    "    return 0",
                    "Must use a literal for accessing tuple elements");
}
TEST_CASE("type checker: tuple [] access must use integer literal") {
  TEST_SNIPPET_FULL("def main() -> int:\n"
                    "    a: Tuple[int]\n"
                    "    println(a[0.0])\n"
                    "    return 0",
                    "Invalid index expression, must be of a valid integer");
}
TEST_CASE(
    "type checker: tuple [] access must use integer literal used non decimal") {
  TEST_SNIPPET_FULL(
      "def main() -> int:\n"
      "    a: Tuple[int]\n"
      "    println(a[0x0])\n"
      "    return 0",
      "Must use a integer decimal literal for accessing tuple elements");
}
TEST_CASE("type checker: tuple [] access tuple index out of bounds") {
  TEST_SNIPPET_FULL("def main() -> int:\n"
                    "    a: Tuple[int]\n"
                    "    println(a[1])\n"
                    "    return 0",
                    "Tuple index out of bounds");
}
TEST_CASE("type checker: array [] access non integer") {
  TEST_SNIPPET_FULL("def main() -> int:\n"
                    "    a: Array[int]\n"
                    "    println(a[1.0])\n"
                    "    return 0",
                    "Invalid index expression, must be of a valid integer");
}
TEST_CASE("type checker: [] access non array/tuple") {
  TEST_SNIPPET_FULL("def main() -> int:\n"
                    "    a: int = 1\n"
                    "    println(a[1])\n"
                    "    return 0",
                    "Not an array");
}
TEST_CASE("type checker: dot operator from primitive") {
  TEST_SNIPPET_FULL("def main() -> int:\n"
                    "    a: int = 1\n"
                    "    println(a.item)\n"
                    "    return 0",
                    "Invalid dot operator, LHS need to be an object");
}
TEST_CASE("type checker: dot operator from class") {
  TEST_SNIPPET_FULL("class A:\n"
                    "    a: int\n"
                    "def main() -> int:\n"
                    "    println(A.a)\n"
                    "    return 0",
                    "Invalid dot operator, LHS need to be an object");
}
TEST_CASE("type checker: member not found from imported module") {
  TEST_SNIPPET_FULL("import libs.c\n"
                    "def main() -> int:\n"
                    "    println(c.A)\n"
                    "    return 0",
                    "Member not found");
}
TEST_CASE("type checker: non existent type access") {
  TEST_SNIPPET_FULL("def main() -> int:\n"
                    "    c: A\n"
                    "    println(c.C)\n"
                    "    return 0",
                    "Cannot find data type of LHS");
}
TEST_CASE("type checker: non existent element access") {
  TEST_SNIPPET_FULL("class A:\n"
                    "    b: int\n"
                    "def main() -> int:\n"
                    "    c: A\n"
                    "    println(c.B)\n"
                    "    return 0",
                    "Cannot find data type of LHS");
}
TEST_CASE("type checker: ccode statement used outside non native function") {
  TEST_SNIPPET_FULL("def main() -> int:\n"
                    "    ccode \"\"\"int a = 1;\"\"\"\n"
                    "    return 0",
                    "Invalid use of ccode statement outside non native function");
}
TEST_CASE(
    "type checker: argument must be a string literal for binarydata()") {
  TEST_SNIPPET("a: Ptr[Const[u8]] = binarydata(1)",
               "Argument to binarydata() must be a str literal");
}
TEST_CASE(
    "type checker: only 1 argument is allowed for binarydata()") {
  TEST_SNIPPET("a: Ptr[Const[u8]] = binarydata(1, 2, 3)",
               "binarydata() builtin expects 1 argument");
}
TEST_CASE("type checker: Redefining variables in a function different data types") {
  TEST_FILE("../test_data/bug_fixes/redefining_vars.yaka",
            "Redefining a variable is not allowed");
}
TEST_CASE("type checker: Redefining variables in a function - params") {
  TEST_FILE("../test_data/bug_fixes/redefining_vars_params.yaka",
            "Redefining a variable is not allowed");
}