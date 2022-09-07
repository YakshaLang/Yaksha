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
    REQUIRE(yaksha::errors::has_error(E));                                    \
  } while (0)
TEST_CASE("type checker: Bad function for qsort") {
  TEST_FILE("../test_data/bad_inputs/bad_input_sort_with_wrong_args.yaka",
            "Comparison must match with "
            "Function[In[Const[AnyArg],Const[AnyArg]],Out[int]]");
}
