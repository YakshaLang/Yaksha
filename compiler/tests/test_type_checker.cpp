// ==============================================================================================
// ╦  ┬┌─┐┌─┐┌┐┌┌─┐┌─┐    Yaksha Programming Language
// ║  ││  ├┤ │││└─┐├┤     is Licensed with GPLv3 + extra terms. Please see below.
// ╩═╝┴└─┘└─┘┘└┘└─┘└─┘
// Note: libs - MIT license, runtime/3rd - various
// ==============================================================================================
// GPLv3:
//
// Yaksha - Programming Language.
// Copyright (C) 2020 - 2024 Bhathiya Perera
//
// This program is free software: you can redistribute it and/or modify it under the terms
// of the GNU General Public License as published by the Free Software Foundation,
// either version 3 of the License, or (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
// or FITNESS FOR A PARTICULAR PURPOSE.
// See the GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License along with this program.
// If not, see https://www.gnu.org/licenses/.
//
// ==============================================================================================
// Additional Terms:
//
// Please note that any commercial use of the programming language's compiler source code
// (everything except compiler/runtime, compiler/libs and compiler/3rd) require a written agreement
// with author of the language (Bhathiya Perera).
//
// If you are using it for an open source project, please give credits.
// Your own project must use GPLv3 license with these additional terms.
//
// You may use programs written in Yaksha/YakshaLisp for any legal purpose
// (commercial, open-source, closed-source, etc) as long as it agrees
// to the licenses of linked runtime libraries (see compiler/runtime/README.md).
//
// ==============================================================================================
#include "catch2/catch.hpp"
#include "compiler/codegen_c.h"
#include "compiler/multifile_compiler.h"
#include "utilities/error_printer.h"
#include <string>
using namespace yaksha;
static void test_typechecker_yaka_file(const std::string &A,
                                       const std::string &E) {
  multifile_compiler mc{};
  codegen_c cg{};
  auto result = mc.compile(A, &cg);
  REQUIRE(result.failed_ == true);
  REQUIRE(mc.error_printer_.has_any_error());
  REQUIRE(mc.error_printer_.has_error(E));
}
static void test_typechecker_ok_yaka_file(const std::string &A) {
  multifile_compiler mc{};
  codegen_c cg{};
  auto result = mc.compile(A, &cg);
  REQUIRE(result.failed_ == false);
  REQUIRE(mc.error_printer_.has_no_errors());
}
static void test_typechecker_snippet(const std::string &S,
                                     const std::string &E) {
  multifile_compiler mc{};
  codegen_c cg{};
  std::string xa = "def main() -> int:\n";
  xa += "    ";
  xa += (S);
  xa += "\n"
        "    return 0";
  std::filesystem::path code_file_path =
      std::filesystem::absolute(std::filesystem::path{"dummy.yaka"});
  auto result = mc.compile(xa, true, code_file_path.string(), "../libs", &cg);
  REQUIRE(result.failed_ == true);
  REQUIRE(mc.error_printer_.has_any_error());
  REQUIRE(mc.error_printer_.has_error(E));
}
static void test_typechecker_snippet_ok(const std::string &S) {
  multifile_compiler mc{};
  codegen_c cg{};
  std::string xa = "def main() -> int:\n";
  xa += "    ";
  xa += (S);
  xa += "\n"
        "    return 0";
  std::filesystem::path code_file_path =
      std::filesystem::absolute(std::filesystem::path{"dummy.yaka"});
  auto result = mc.compile(xa, true, code_file_path.string(), "../libs", &cg);
  REQUIRE(result.failed_ == false);
  REQUIRE(mc.error_printer_.has_no_errors());
}
static void test_typechecker_snippet_full(const std::string &S,
                                          const std::string &E) {
  multifile_compiler mc{};
  codegen_c cg{};
  const std::string &xa = S;
  std::filesystem::path code_file_path =
      std::filesystem::absolute(std::filesystem::path{"dummy.yaka"});
  auto result = mc.compile(xa, true, code_file_path.string(), "../libs", &cg);
  REQUIRE(result.failed_ == true);
  REQUIRE(mc.error_printer_.has_any_error());
  REQUIRE(mc.error_printer_.has_error(E));
}
static void test_typechecker_snippet_full_ok(const std::string &S) {
  multifile_compiler mc{};
  codegen_c cg{};
  const std::string &xa = S;
  std::filesystem::path code_file_path =
      std::filesystem::absolute(std::filesystem::path{"dummy.yaka"});
  auto result = mc.compile(xa, true, code_file_path.string(), "../libs", &cg);
  REQUIRE(result.failed_ == false);
  REQUIRE(mc.error_printer_.has_no_errors());
}
TEST_CASE("type checker: Bad function for qsort") {
  test_typechecker_yaka_file(
      "../test_data/bad_inputs/bad_input_sort_with_wrong_args.yaka",
      "Comparison must match with "
      "Function[In[Const[AnyPtrToConst],Const[AnyPtrToConst]],Out[int]]");
}
TEST_CASE("type checker: Passing a map to arrput") {
  test_typechecker_yaka_file("../test_data/bad_inputs/arrput_map.yaka",
                             "arrput() does not work with maps");
}
TEST_CASE("type checker: Passing a map to arrpop") {
  test_typechecker_yaka_file("../test_data/bad_inputs/arrpop_map.yaka",
                             "arrpop() does not work with maps");
}
TEST_CASE("type checker: Builtin arrnew invalid arg count") {
  test_typechecker_snippet(
      "a: Array[int] = arrnew()",
      "Two arguments must be provided for arrnew() builtin");
}
TEST_CASE(
    "type checker: First argument must be a string literal for arrnew()") {
  test_typechecker_snippet(
      "a: Array[int] = arrnew(1, 10)",
      "First argument to arrnew() must be a string literal");
}
TEST_CASE("type checker: First argument must be a string literal for arrnew(). "
          "Does not "
          "work with variables") {
  test_typechecker_snippet(
      "b: str = \"str\"\n    a: Array[int] = arrnew(b, 10)",
      "First argument to arrnew() must be a string literal");
}
TEST_CASE("type checker: Second argument must be int for arrnew()") {
  // Note: see here that the second arg is a string literal "10"
  test_typechecker_snippet(R"(a: Array[int] = arrnew("int", "10"))",
                           "Second argument to arrnew() must be an int");
}
TEST_CASE("type checker: Must assign to proper data structure for arrnew()") {
  test_typechecker_snippet("a: Array[str] = arrnew(\"int\", 10)",
                           "Cannot assign between 2 different data types. lhs: "
                           "Array[str], rhs: Array[int]");
}
TEST_CASE("type checker: Builtin array() invalid arg count") {
  test_typechecker_snippet("a: Array[int] = array()",
                           "array() builtin expects >= 1 arguments");
}
TEST_CASE("type checker: First argument must be a string literal for array()") {
  test_typechecker_snippet(
      "a: Array[int] = array(\"str\", 1)",
      "All arguments must match with data type passed to first "
      "argument for array() builtin");
}
TEST_CASE("type checker: First argument must be a string literal for array(). "
          "Does not "
          "work with variables") {
  test_typechecker_snippet(
      "b: str = \"str\"\n    a: Array[int] = array(b, 10)",
      "First argument to array() must be a string literal");
}
TEST_CASE("type checker: Second argument must be int for array()") {
  // Note: we are looking at integer type values, but we get a "10" string literal
  test_typechecker_snippet(
      "a: Array[int] = array(\"int\", \"10\")",
      "All arguments must match with data type passed to first "
      "argument for array() builtin");
}
TEST_CASE("type checker: Must assign to proper data structure for array()") {
  test_typechecker_snippet("a: Array[str] = array(\"int\", 10)",
                           "Cannot assign between 2 different data types. lhs: "
                           "Array[str], rhs: Array[int]");
}
TEST_CASE("type checker: Different type assignment using iif") {
  test_typechecker_snippet("a: bool = iif(True, False, 1)",
                           "Second and third arguments to iif() data type "
                           "mismatch. Expected: bool, Provided: int");
}
TEST_CASE(
    "type checker: Different type assignment using iif bigger type on lhs") {
  test_typechecker_snippet_ok("a: int = iif(True, 1, 1i8)");
}
TEST_CASE("type checker: Different type func assignment using iif") {
  test_typechecker_snippet_full(
      "def f1(x: int) -> None:\n"
      "    pass\n"
      "def f2(y: int, z: int) -> None:\n"
      "    pass\n"
      "def main() -> int:\n"
      "    a: Function[In[int],Out] = iif(True, f1, f2)\n"
      "    return 0",
      "Second and third arguments to iif() data type mismatch. Expected: "
      "Function[In[int], Out], Provided: Function[In[int, int], Out]");
}
TEST_CASE("type checker: iif using 4 args") {
  test_typechecker_snippet("a: bool = iif(True, False, True, 2)",
                           "iif() builtin expects 3 arguments");
}
TEST_CASE("type checker: iif using no arguments") {
  test_typechecker_snippet("a: bool = iif()",
                           "iif() builtin expects 3 arguments");
}
TEST_CASE("type checker: Object creation with argument not allowed") {
  test_typechecker_snippet_full(
      "class A:\n"
      "    a: int\n"
      "def main() -> int:\n"
      "    a: A = A(1)\n"
      "    return 0",
      "Arguments for object creation is not supported");
}
TEST_CASE("type checker: assignment without definition is allowed") {
  test_typechecker_snippet_ok("a = 1");
}
TEST_CASE(
    "type checker: Binary operation between two different data types (meta)") {
  test_typechecker_snippet_full(
      "class A:\n"
      "    a: int\n"
      "def main() -> int:\n"
      "    a: int = 1\n"
      "    b: bool = a == A\n"
      "    return 0",
      "Binary operation between two different data types are not supported");
}
TEST_CASE("type checker: str constants are not supported") {
  test_typechecker_snippet_full("A:Const[str] = \"hello\"\n"
                                "def main() -> int:\n"
                                "    a: int = 1\n"
                                "    b: bool = a == A\n"
                                "    return 0",
                                "Only number/bool/sr constants are supported.");
}
TEST_CASE("type checker: two different enums cannot be compared") {
  test_typechecker_snippet_full("enum A:\n"
                                "    a\n"
                                "enum B:\n"
                                "    b\n"
                                "def main() -> int:\n"
                                "    c: bool = A.a == B.b\n"
                                "    0\n",
                                "Cannot compare between two data types");
}
TEST_CASE("type checker: enum cannot be compared with integer") {
  test_typechecker_snippet_full("enum A:\n"
                                "    a\n"
                                "def main() -> int:\n"
                                "    c: bool = A.a == 0\n"
                                "    0\n",
                                "Cannot compare between two data types");
}
TEST_CASE("type checker: different enums cannot be assigned") {
  test_typechecker_snippet_full(
      "enum A:\n"
      "    a\n"
      "enum B:\n"
      "    b\n"
      "def main() -> int:\n"
      "    a: A = A.a\n"
      "    a = B.b\n"
      "    0\n",
      "Cannot assign between 2 different data types. lhs: A, rhs: B");
}
TEST_CASE(
    "type checker: different enums cannot be assigned ('a' basic inference)") {
  test_typechecker_snippet_full(
      "enum A:\n"
      "    a\n"
      "enum B:\n"
      "    b\n"
      "def main() -> int:\n"
      "    a = A.a\n"
      "    a = B.b\n"
      "    0\n",
      "Cannot assign between 2 different data types. lhs: A, rhs: B");
}
TEST_CASE("type checker: compare inferred enums") {
  test_typechecker_snippet_full("enum A:\n"
                                "    a\n"
                                "enum B:\n"
                                "    b\n"
                                "def main() -> int:\n"
                                "    a = A.a\n"
                                "    b = B.b\n"
                                "    iif(a == b, 0, 1)\n",
                                "Cannot compare between two data types");
}
TEST_CASE("type checker: duplicated enum values") {
  test_typechecker_snippet_full("enum A:\n"
                                "    a\n"
                                "    a\n"
                                "def main() -> int:\n"
                                "    a = A.a\n"
                                "    iif(a == A.a, 0, 1)\n",
                                "Duplicate enum value 'a' in enum 'A'");
}
TEST_CASE("type checker: duplicate class fields") {
  test_typechecker_snippet_full(
      "class A:\n"
      "    a: int\n"
      "    a: int\n"
      "def main() -> int:\n"
      "    a = A{a: 1}\n"
      "    iif(a.a == 1, 0, 1)\n",
      "Duplicate member name: 'a' in class/struct: 'A'");
}
TEST_CASE("type checker: duplicate function parameters") {
  // Both errors should be raised
  test_typechecker_snippet_full("def fnc(a: int, a: int) -> None:\n"
                                "    pass\n"
                                "def main() -> int:\n"
                                "    fnc(1, 2)\n"
                                "    0\n",
                                "Parameter redefinition is not allowed: 'a'");
  test_typechecker_snippet_full("def fnc(b: int, b: int) -> None:\n"
                                "    pass\n"
                                "def main() -> int:\n"
                                "    fnc(1, 2)\n"
                                "    0\n",
                                "Parameter shadows outer scope name: b");
}
TEST_CASE("type checker: duplicate name and value for an enum") {
  test_typechecker_snippet_full_ok("enum A:\n"
                                   "    A\n"
                                   "def main() -> int:\n"
                                   "    iif(A.A == A.A, 0, 1)\n");
}
TEST_CASE("type checker: duplicate name and value for class field") {
  test_typechecker_snippet_full_ok("class A:\n"
                                   "    A: int\n"
                                   "def main() -> int:\n"
                                   "    a = A{A: 1}\n"
                                   "    iif(a.A == 1, 0, 1)\n");
}
TEST_CASE("type checker: duplicate name and parameter name for function") {
  test_typechecker_snippet_full("def fnc(fnc: int) -> None:\n"
                                "    pass\n"
                                "def main() -> int:\n"
                                "    fnc(1)\n"
                                "    0\n",
                                "Parameter shadows outer scope name: fnc");
}
TEST_CASE("type checker: function name is same as class member") {
  test_typechecker_snippet_full_ok("class A:\n"
                                   "    a: int\n"
                                   "def a(b: int) -> None:\n"
                                   "    pass\n"
                                   "def main() -> int:\n"
                                   "    a0 = A{a: 1}\n"
                                   "    0\n");
}
TEST_CASE("type checker: sr constants are supported") {
  test_typechecker_snippet_full_ok("A:Const[sr] = \"hello\"\n"
                                   "def main() -> int:\n"
                                   "    return 0");
}
TEST_CASE("type checker: different type of numbers used in operators bitwise") {
  test_typechecker_snippet(
      "a: int = 1\n"
      "    b: i8 = a & 1i8\n",
      "Cannot assign between 2 different data types. lhs: i8, rhs: int");
}
TEST_CASE(
    "type checker: different type of numbers used in operators mul/div/rem") {
  test_typechecker_snippet(
      "a: int = 1\n"
      "    b: i8 = a * 1i8\n",
      "Cannot assign between 2 different data types. lhs: i8, rhs: int");
}
TEST_CASE(
    "type checker: different type of numbers used in operators comparison") {
  test_typechecker_snippet_ok("a: i8 = 1i8\n"
                              "    b: bool = a <= 77346\n");
  test_typechecker_snippet_ok("a: int = 1\n"
                              "    b: bool = a <= 1i8\n");
  test_typechecker_snippet("a: int = 1\n"
                           "    b: bool = a <= \"gah\"\n",
                           "< > <= >= operators work only for numbers");
}
TEST_CASE("type checker: + operator with just 2 booleans") {
  test_typechecker_snippet(
      "a: bool = True\n"
      "    b: bool = a + False\n",
      "+ operator works only for numbers of same type or strings,"
      " (widening may occur between smaller to larger numbers, and this is not "
      "a valid case of auto widening)");
}
TEST_CASE("type checker: + operator with just 2 booleans (one is const)") {
  test_typechecker_snippet(
      "a: Const[bool] = True\n"
      "    b: bool = a + False\n",
      "+ operator works only for numbers of same type or strings,"
      " (widening may occur between smaller to larger numbers, and this is not "
      "a valid case of auto widening)");
}
TEST_CASE("type checker: + operator with just 2 booleans (both are const)") {
  test_typechecker_snippet(
      "a: Const[bool] = True\n"
      "    b: Const[bool] = False\n"
      "    c: Const[bool] = a + b\n",
      "+ operator works only for numbers of same type or strings,"
      " (widening may occur between smaller to larger numbers, and this is not "
      "a valid case of auto widening)");
}
TEST_CASE("type checker: cannot compare tuples with ==") {
  test_typechecker_snippet(
      "a: Tuple[int]\n"
      "    b: Tuple[int]\n"
      "    c: bool = a == b\n",
      "MEntry/SMEntry/Tuple cannot be compared with == or != operator");
}
TEST_CASE("type checker: cannot compare mentry with ==") {
  test_typechecker_snippet(
      "a: MEntry[int,int]\n"
      "    b: MEntry[int,int]\n"
      "    c: bool = a == b\n",
      "MEntry/SMEntry/Tuple cannot be compared with == or != operator");
}
TEST_CASE("type checker: cannot compare smentry with !=") {
  test_typechecker_snippet(
      "a: SMEntry[int]\n"
      "    b: SMEntry[int]\n"
      "    c: bool = a != b\n",
      "MEntry/SMEntry/Tuple cannot be compared with == or != operator");
}
TEST_CASE("type checker: cannot compare tuple vs smentry with !=") {
  test_typechecker_snippet(
      "a: Tuple[int]\n"
      "    b: SMEntry[int]\n"
      "    c: bool = a != b\n",
      "MEntry/SMEntry/Tuple cannot be compared with == or != operator");
}
TEST_CASE("type checker: cannot compare integers with None") {
  test_typechecker_snippet("a: int = 1\n"
                           "    c: bool = a != None\n",
                           "Datatype cannot be compared with None");
}
TEST_CASE("type checker: cannot compare booleans with None") {
  test_typechecker_snippet("a: bool = False\n"
                           "    c: bool = a != None\n",
                           "Datatype cannot be compared with None");
}
TEST_CASE(
    "type checker: cannot compare two different kinds of integers with ==") {
  test_typechecker_snippet("a: int = 1\n"
                           "    c: bool = 1 == 1i8\n",
                           "Cannot compare between two data types");
}
TEST_CASE(
    "type checker: cannot compare two different kinds of integers with !=") {
  test_typechecker_snippet("a: int = 1\n"
                           "    c: bool = 1 != 1i8\n",
                           "Cannot compare between two data types");
}
TEST_CASE("type checker: func call too few arguments") {
  test_typechecker_snippet_full(
      "def fnc(a: int, b: int) -> None:\n"
      "    pass\n"
      "def main() -> int:\n"
      "    fnc(1)\n"
      "    return 0",
      "Too few or too much arguments for function call");
}
TEST_CASE("type checker: func call too much arguments") {
  test_typechecker_snippet_full(
      "def fnc(a: int, b: int) -> None:\n"
      "    pass\n"
      "def main() -> int:\n"
      "    fnc(1, 2, 3, 4)\n"
      "    return 0",
      "Too few or too much arguments for function call");
}
TEST_CASE("type checker: func call parameter and argument mismatches") {
  test_typechecker_snippet_full_ok("def fnc(a: int, b: int) -> None:\n"
                                   "    pass\n"
                                   "def main() -> int:\n"
                                   "    fnc(1, False)\n"
                                   "    return 0");
  test_typechecker_snippet_full(
      "def fnc(a: i8, b: int) -> None:\n"
      "    pass\n"
      "def main() -> int:\n"
      "    fnc(1i32, False)\n"
      "    return 0",
      "Parameter & argument 1 mismatches. Expected: i8 Provided: int");
  test_typechecker_snippet_full(
      "def fnc(a: int, b: i8) -> None:\n"
      "    pass\n"
      "def main() -> int:\n"
      "    fnc(1i32, 10)\n"
      "    return 0",
      "Parameter & argument 2 mismatches. Expected: i8 Provided: int");
}
TEST_CASE("type checker: func call parameter and argument mismatches first "
          "argument") {
  test_typechecker_snippet_full_ok("def fnc(a: int, b: int) -> None:\n"
                                   "    pass\n"
                                   "def main() -> int:\n"
                                   "    fnc(False, 3)\n"
                                   "    return 0");
  test_typechecker_snippet_full(
      "def fnc(a: i8, b: int) -> None:\n"
      "    pass\n"
      "def main() -> int:\n"
      "    fnc(1340, 3)\n"
      "    return 0",
      "Parameter & argument 1 mismatches. Expected: i8 Provided: int");
}
TEST_CASE(
    "type checker: func call parameter and argument mismatches for varargs") {
  test_typechecker_snippet_full_ok("@nativedefine(\"test\")\n"
                                   "@varargs\n"
                                   "def fnc(a: int, b: int) -> None:\n"
                                   "    pass\n"
                                   "def main() -> int:\n"
                                   "    fnc(1, 3, 2, 3, False)\n"
                                   "    return 0");
  test_typechecker_snippet_full(
      "@nativedefine(\"test\")\n"
      "@varargs\n"
      "def fnc(a: int, b: int) -> None:\n"
      "    pass\n"
      "def main() -> int:\n"
      "    fnc(1, 3, 2, 3, 12i64)\n"
      "    return 0",
      "Variable argument: 5 mismatches. Expected: int Provided: i64");
}
TEST_CASE("type checker: pass in a non constant structure to a const") {
  test_typechecker_snippet_full_ok("class A:\n"
                                   "    a: int\n"
                                   "def afunc(a: Const[A]) -> None:\n"
                                   "    pass\n"
                                   "def main() -> int:\n"
                                   "    myobj = A{a: 1}\n"
                                   "    afunc(myobj)\n"
                                   "    return 0");
}
TEST_CASE("type checker: pass in a constant structure object to a non const") {
  test_typechecker_snippet_full(
      "class A:\n"
      "    a: int\n"
      "def afunc(a: A) -> None:\n"
      "    pass\n"
      "def main() -> int:\n"
      "    myobj: Const[A] = A{a: 1}\n"
      "    afunc(myobj)\n"
      "    return 0",
      "Parameter & argument 1 mismatches. Expected: A Provided: Const[A]");
}
TEST_CASE("type checker: func ptr call parameter and argument mismatches") {
  test_typechecker_snippet_full_ok("def fnc(a: int, b: int) -> None:\n"
                                   "    pass\n"
                                   "def main() -> int:\n"
                                   "    f1: Function[In[int,int],Out] = fnc\n"
                                   "    f1(1, False)\n"
                                   "    return 0");
  test_typechecker_snippet_full(
      "def fnc(a: int, b: i8) -> None:\n"
      "    pass\n"
      "def main() -> int:\n"
      "    f1: Function[In[int,int],Out] = fnc\n"
      "    f1(1, 2)\n"
      "    return 0",
      "You can only assign a matching function. lhs: Function[In[int, int], "
      "Out], rhs: Function[In[int, i8], Out]");
}
TEST_CASE("type checker: do not allow to return a constant as a non constant") {
  test_typechecker_snippet_full(
      "class A:\n"
      "    a: int\n"
      "def fnc(r: Const[A]) -> A:\n"
      "    r\n"
      "def main() -> int:\n"
      "    a0: Const[A] = A{a: 1}\n"
      "    a: A = fnc(a0)\n"
      "    0",
      "Invalid return data type. Expected: A, Provided: Const[A]");
}
TEST_CASE("type checker: for primitives it is allowed to remove const-ness") {
  // It does not matter that this is done, as integer is copied and is a primitive
  test_typechecker_snippet_full_ok("def fnc(r: Const[int]) -> int:\n"
                                   "    r\n"
                                   "def main() -> int:\n"
                                   "    a0: Const[int] = 90\n"
                                   "    a: int = fnc(a0)\n"
                                   "    0");
}
TEST_CASE("type checker: remove const-ness and also autocast") {
  test_typechecker_snippet_full_ok("def fnc(r: Const[i8]) -> int:\n"
                                   "    r\n"
                                   "def main() -> int:\n"
                                   "    a0: Const[i8] = 5i8\n"
                                   "    a: int = fnc(a0)\n"
                                   "    0");
}
TEST_CASE("type checker: func ptr call parameter and argument mismatches first "
          "argument") {
  test_typechecker_snippet_full_ok("def fnc(a: int, b: int) -> None:\n"
                                   "    pass\n"
                                   "def main() -> int:\n"
                                   "    f1: Function[In[int,int],Out] = fnc\n"
                                   "    f1(False, 1)\n"
                                   "    return 0");
  test_typechecker_snippet_full("def fnc(a: i8, b: int) -> None:\n"
                                "    pass\n"
                                "def main() -> int:\n"
                                "    f1: Function[In[i8,int],Out] = fnc\n"
                                "    f1(1000, 1)\n"
                                "    return 0",
                                "Function[] call parameter & argument 1 "
                                "mismatches. Expected: i8, Provided: int");
}
TEST_CASE("type checker: func ptr call too much arguments") {
  test_typechecker_snippet_full("def fnc(a: int, b: int) -> None:\n"
                                "    pass\n"
                                "def main() -> int:\n"
                                "    f1: Function[In[int,int],Out] = fnc\n"
                                "    f1(1, 1, 1, 2)\n"
                                "    return 0",
                                "Too few or too much arguments for function "
                                "call. Expected: 2, Provided: 4");
}
TEST_CASE("type checker: func ptr call too few arguments") {
  test_typechecker_snippet_full("def fnc(a: int, b: int) -> None:\n"
                                "    pass\n"
                                "def main() -> int:\n"
                                "    f1: Function[In[int,int],Out] = fnc\n"
                                "    f1(1)\n"
                                "    return 0",
                                "Too few or too much arguments for function "
                                "call. Expected: 2, Provided: 1");
}
TEST_CASE("type checker: func ptr call output type mismatches") {
  test_typechecker_snippet_full(
      "def fnc(a: int, b: int) -> int:\n"
      "    return a + b\n"
      "def main() -> int:\n"
      "    f1: Function[In[int,int],Out[int]] = fnc\n"
      "    a: bool = f1(1, 2)\n"
      "    return 0",
      "Cannot assign between 2 different data types. lhs: bool, rhs: int");
}
TEST_CASE("type checker: calling a non callable") {
  test_typechecker_snippet_full(
      "def main() -> int:\n"
      "    a: bool = False\n"
      "    b: bool = a(1, 2)\n"
      "    return 0",
      "Calling a non callable or a non existing function with name: 'a' is not "
      "allowed. datatype: bool");
}
TEST_CASE("type checker: logical or needs two booleans") {
  test_typechecker_snippet("a: bool = False or 1\n",
                           "Both LHS and RHS of logical operator need to be "
                           "boolean. LHS: bool, RHS: int");
}
TEST_CASE("type checker: logical or needs two booleans swapped") {
  test_typechecker_snippet("a: bool = 1 or False\n",
                           "Both LHS and RHS of logical operator need to be "
                           "boolean. LHS: int, RHS: bool");
}
TEST_CASE("type checker: logical and needs two booleans") {
  test_typechecker_snippet("a: bool = True and 1\n",
                           "Both LHS and RHS of logical operator need to be "
                           "boolean. LHS: bool, RHS: int");
}
TEST_CASE("type checker: not must follow a boolean") {
  test_typechecker_snippet("a: bool = not 1\n",
                           "Invalid unary operation. Not operator must follow "
                           "a boolean. Provided: int");
}
TEST_CASE("type checker: not must follow a boolean (str used)") {
  test_typechecker_snippet(
      "a: bool = not \"False\"\n",
      "Unary operator is not supported for data type: :s:");
}
TEST_CASE("type checker: ~ must follow an integer") {
  test_typechecker_snippet(
      "a: int = ~False\n",
      "Bitwise not (~) is only supported for integers. Provided: bool");
}
TEST_CASE("type checker: ~ must follow an integer (f64 used)") {
  test_typechecker_snippet(
      "a: int = ~1.0\n",
      "Bitwise not (~) is only supported for integers. Provided: f64");
}
TEST_CASE("type checker: ~ must follow an integer (str used)") {
  // String literal has a special datatype ':s:'
  test_typechecker_snippet(
      "a: int = ~\"Hello\"\n",
      "Unary operator is not supported for data type: :s:");
}
TEST_CASE("type checker: access non defined variable") {
  test_typechecker_snippet("a: int = ~1 + b\n", "Undefined name: 'b'");
}
TEST_CASE("type checker: delete an integer") {
  test_typechecker_snippet("del 1u8",
                           "Invalid delete statement used on primitives");
}
TEST_CASE("type checker: delete a float") {
  test_typechecker_snippet("del 1.0f",
                           "Invalid delete statement used on primitives");
}
TEST_CASE("type checker: delete a bool") {
  test_typechecker_snippet("del False",
                           "Invalid delete statement used on primitives");
}
TEST_CASE("type checker: delete a tuple") {
  test_typechecker_snippet_full(
      "def main() -> int:\n"
      "    a: Tuple[int]\n"
      "    del a\n"
      "    return 0",
      "Invalid delete statement used on Tuple/MEntry/SMEntry/Function");
}
TEST_CASE("type checker: delete MEntry") {
  test_typechecker_snippet_full(
      "def main() -> int:\n"
      "    a: MEntry[int, int]\n"
      "    del a\n"
      "    return 0",
      "Invalid delete statement used on Tuple/MEntry/SMEntry/Function");
}
TEST_CASE("type checker: delete SMEntry") {
  test_typechecker_snippet_full(
      "def main() -> int:\n"
      "    a: SMEntry[int]\n"
      "    del a\n"
      "    return 0",
      "Invalid delete statement used on Tuple/MEntry/SMEntry/Function");
}
TEST_CASE("type checker: delete Function") {
  test_typechecker_snippet_full(
      "def main() -> int:\n"
      "    a: Function[In[int],Out]\n"
      "    del a\n"
      "    return 0",
      "Invalid delete statement used on Tuple/MEntry/SMEntry/Function");
}
TEST_CASE("type checker: delete Function main()") {
  test_typechecker_snippet_full(
      "def main() -> int:\n"
      "    del main\n"
      "    return 0",
      "Invalid delete statement used on Tuple/MEntry/SMEntry/Function");
}
TEST_CASE("type checker: tuple [] access must use literal") {
  test_typechecker_snippet_full(
      "def main() -> int:\n"
      "    a: Tuple[int]\n"
      "    b: int = 0\n"
      "    c: int = a[b]\n"
      "    return 0",
      "Must use a literal for accessing tuple elements");
}
TEST_CASE("type checker: tuple [] access must use integer literal") {
  test_typechecker_snippet_full(
      "def main() -> int:\n"
      "    a: Tuple[int]\n"
      "    println(a[0.0])\n"
      "    return 0",
      "Invalid index expression, must be of a valid integer");
}
TEST_CASE(
    "type checker: tuple [] access must use integer literal used non decimal") {
  test_typechecker_snippet_full(
      "def main() -> int:\n"
      "    a: Tuple[int]\n"
      "    println(a[0x0])\n"
      "    return 0",
      "Must use a integer decimal literal for accessing tuple elements");
}
TEST_CASE("type checker: tuple [] access tuple index out of bounds") {
  test_typechecker_snippet_full("def main() -> int:\n"
                                "    a: Tuple[int]\n"
                                "    println(a[1])\n"
                                "    return 0",
                                "Tuple index out of bounds");
}
TEST_CASE("type checker: array [] access non integer") {
  test_typechecker_snippet_full(
      "def main() -> int:\n"
      "    a: Array[int]\n"
      "    println(a[1.0])\n"
      "    return 0",
      "Invalid index expression, must be of a valid integer");
}
TEST_CASE("type checker: [] access non array/tuple") {
  test_typechecker_snippet_full("def main() -> int:\n"
                                "    a: int = 1\n"
                                "    println(a[1])\n"
                                "    return 0",
                                "Not an array");
}
TEST_CASE("type checker: dot operator from primitive") {
  test_typechecker_snippet_full(
      "def main() -> int:\n"
      "    a: int = 1\n"
      "    println(a.item)\n"
      "    return 0",
      "Invalid dot operator, LHS need to be an object");
}
TEST_CASE("type checker: dot operator from class") {
  test_typechecker_snippet_full(
      "class A:\n"
      "    a: int\n"
      "def main() -> int:\n"
      "    println(A.a)\n"
      "    return 0",
      "Invalid dot operator, LHS need to be an object");
}
TEST_CASE("type checker: member not found from imported module") {
  test_typechecker_snippet_full(
      "import libs.c\n"
      "def main() -> int:\n"
      "    println(c.Cos)\n"
      "    return 0",
      "Member not found. Perhaps 'cos' is what you meant?");
}
TEST_CASE("type checker: non existent type access") {
  test_typechecker_snippet_full("def main() -> int:\n"
                                "    c: A\n"
                                "    println(c.C)\n"
                                "    return 0",
                                "Cannot find data type of LHS");
}
TEST_CASE("type checker: non existent element access") {
  test_typechecker_snippet_full(
      "class A:\n"
      "    b: int\n"
      "def main() -> int:\n"
      "    c: A\n"
      "    println(c.B)\n"
      "    return 0",
      "Member not found. Perhaps 'b' is what you meant?");
}
TEST_CASE("type checker: ccode statement used outside non native function") {
  test_typechecker_snippet_full(
      "def main() -> int:\n"
      "    ccode \"\"\"int a = 1;\"\"\"\n"
      "    return 0",
      "Invalid use of ccode statement outside non native function");
}
TEST_CASE("type checker: argument must be a string literal for binarydata()") {
  test_typechecker_snippet("a: Ptr[Const[u8]] = binarydata(1)",
                           "Argument to binarydata() must be a str literal");
}
TEST_CASE("type checker: only 1 argument is allowed for binarydata()") {
  test_typechecker_snippet("a: Ptr[Const[u8]] = binarydata(1, 2, 3)",
                           "binarydata() builtin expects 1 argument");
}
TEST_CASE(
    "type checker: Redefining variables in a function different data types") {
  test_typechecker_yaka_file("../test_data/bug_fixes/redefining_vars.yaka",
                             "Redefining a variable is not allowed: 'b'");
}
TEST_CASE("type checker: Redefining variables in a function - params") {
  test_typechecker_yaka_file(
      "../test_data/bug_fixes/redefining_vars_params.yaka",
      "Redefining a variable is not allowed: 'b'");
}
TEST_CASE("type checker: Const assignment should work as expected") {
  test_typechecker_ok_yaka_file("../test_data/bug_fixes/assign_const.yaka");
}
TEST_CASE("type checker: Test multiple assignment failure") {
  test_typechecker_yaka_file(
      "../test_data/compiler_tests/multi_assign.yaka",
      "Cannot assign between 2 different data types. lhs: sr, rhs: int");
}
TEST_CASE("type checker: Import shadows a foreach variable") {
  test_typechecker_yaka_file(
      "../test_data/compiler_tests/import_for_each_shadow.yaka",
      "Foreach: shadows outer scope name: 'c'");
}
TEST_CASE("type checker: Create a primitive using {} init") {
  test_typechecker_snippet("a = int{x: 0}",
                           "Invalid datatype for {} initialization");
}
TEST_CASE("type checker: Invalid fields in struct") {
  test_typechecker_snippet_full("struct P:\n"
                                "    x: int\n\n"
                                "def main() -> int:\n"
                                "    a = P{k: 0}\n"
                                "    return 0\n",
                                "Member 'k' not found in class/struct 'P'. "
                                "Perhaps 'x' is what you meant?");
}
TEST_CASE("type checker: Duplicate fields in {} init (struct)") {
  test_typechecker_snippet_full("struct P:\n"
                                "    x: int\n\n"
                                "def main() -> int:\n"
                                "    a = P{x: 0, x: 1}\n"
                                "    return 0\n",
                                "Duplicate field 'x' in class/struct literal.");
}
TEST_CASE("type checker: Duplicate fields in {} init (class)") {
  test_typechecker_snippet_full("class P:\n"
                                "    x: int\n\n"
                                "def main() -> int:\n"
                                "    a = P{x: 0, x: 1}\n"
                                "    defer del a\n"
                                "    return 0\n",
                                "Duplicate field 'x' in class/struct literal.");
}
TEST_CASE("type checker: Certain comparisons are not allowed") {
  test_typechecker_snippet_full("def main() -> int:\n"
                                "    b: str = \"\"\n"
                                "    c: str = \"xxx\"\n"
                                "    for (x = 0; b != c + \"x\"; x += 1):\n"
                                "        b += \"x\"\n"
                                "        println(b)\n"
                                "    return 0\n",
                                "Failed to compile c like for loop, this "
                                "comparison expression cannot be used here.");
}
TEST_CASE("type checker: Widening u8 + i8 cannot happen") {
  test_typechecker_snippet(
      "a = 1i8 + 2u8",
      "+ operator works only for numbers of same type or strings, (widening "
      "may occur between smaller to larger numbers, and this is not a valid "
      "case of auto widening)");
}
TEST_CASE("type checker: Widening u8 + i16 can happen") {
  test_typechecker_snippet_ok("a: i16 = 2u8 + 1i16");
}
TEST_CASE("type checker: Widening u8 + i32 can happen") {
  test_typechecker_snippet_ok("a: i32 = 2u8 + 1i32");
}
TEST_CASE("type checker: Widening u8 + i64 can happen") {
  test_typechecker_snippet_ok("a = 2u8 + 1i64");
}
TEST_CASE("type checker: Widening u16 + i8 cannot happen") {
  test_typechecker_snippet(
      "a = 2u16 + 1i8",
      "+ operator works only for numbers of same type or strings, (widening "
      "may occur between smaller to larger numbers, and this is not a valid "
      "case of auto widening)");
}
TEST_CASE("type checker: Widening u16 + i16 cannot happen") {
  test_typechecker_snippet(
      "a = 2u16 + 1i16",
      "+ operator works only for numbers of same type or strings, (widening "
      "may occur between smaller to larger numbers, and this is not a valid "
      "case of auto widening)");
}
TEST_CASE("type checker: Widening u16 + i32 can happen") {
  test_typechecker_snippet_ok("a = 2u16 + 1i32");
}
TEST_CASE("type checker: Widening u16 + i64 can happen") {
  test_typechecker_snippet_ok("a: i64 = 2u16 + 1i64");
}
