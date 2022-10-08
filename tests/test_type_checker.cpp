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
    auto result = mc.compile(xa, true, "dummy.yaka", ".");                     \
    REQUIRE(result.failed_ == true);                                           \
    REQUIRE(!yaksha::errors::error_capture.empty());                           \
    REQUIRE(yaksha::errors::has_error(E));                                     \
  } while (0)
#define TEST_SNIPPET_FULL(S, E)                                                \
  do {                                                                         \
    multifile_compiler mc{};                                                   \
    std::string xa = (S);                                                      \
    auto result = mc.compile(xa, true, "dummy.yaka", ".");                     \
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
                    "Arguments for object creation is not supported.");
}
