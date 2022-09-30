#include "catch2/catch.hpp"
#include "compiler/multifile_compiler.h"
#include "file_formats/tokens_file.h"
#include "tokenizer/tokenizer.h"
#include <string>
using namespace yaksha;
#define TEST_FILE(A, B, C)                                                     \
  do {                                                                         \
    multifile_compiler mc{};                                                   \
    auto result = mc.compile(A);                                               \
    REQUIRE(result.failed_ == false);                                          \
    tokenizer c_code{"output.c", result.code_};                                \
    c_code.tokenize();                                                         \
    auto token_snapshot = yaksha::load_token_dump(C);                          \
    yaksha::save_token_dump(C, c_code.tokens_);                                \
    std::string c_code_file{A};                                                \
    c_code_file += ".output.c";                                                \
    std::ofstream save_file(c_code_file);                                      \
    REQUIRE(save_file.is_open() == true);                                      \
    save_file << result.code_;                                                 \
    REQUIRE(c_code.tokens_.size() == token_snapshot.size());                   \
    for (int i = 0; i < token_snapshot.size(); i++) {                          \
      auto parsed = c_code.tokens_[i];                                         \
      auto snapshot = token_snapshot[i];                                       \
      REQUIRE(parsed.file_ == snapshot.file_);                                 \
      REQUIRE(parsed.line_ == snapshot.line_);                                 \
      REQUIRE(parsed.pos_ == snapshot.pos_);                                   \
      REQUIRE(parsed.token_ == snapshot.token_);                               \
      REQUIRE(parsed.type_ == snapshot.type_);                                 \
    }                                                                          \
  } while (0)
TEST_CASE("compiler: Hello World") {
  TEST_FILE("../test_data/compiler_tests/test1.yaka", "test1.yaka",
            "../test_data/compiler_tests/test1.tokens");
}
TEST_CASE("compiler: Defer") {
  TEST_FILE("../test_data/compiler_tests/test2.yaka", "test2.yaka",
            "../test_data/compiler_tests/test2.tokens");
}
TEST_CASE("compiler: Class support") {
  TEST_FILE("../test_data/compiler_tests/test3.yaka", "test3.yaka",
            "../test_data/compiler_tests/test3.tokens");
}
TEST_CASE("compiler: Create object from class") {
  TEST_FILE("../test_data/compiler_tests/test4.yaka", "test4.yaka",
            "../test_data/compiler_tests/test4.tokens");
}
TEST_CASE("compiler: Object members") {
  TEST_FILE("../test_data/compiler_tests/test5.yaka", "test5.yaka",
            "../test_data/compiler_tests/test5.tokens");
}
TEST_CASE("compiler: Array access") {
  TEST_FILE("../test_data/compiler_tests/test6.yaka", "test6.yaka",
            "../test_data/compiler_tests/test6.tokens");
}
TEST_CASE("compiler: Nested array access") {
  TEST_FILE("../test_data/compiler_tests/test7.yaka", "test7.yaka",
            "../test_data/compiler_tests/test7.tokens");
}
TEST_CASE("compiler: Void function") {
  TEST_FILE("../test_data/compiler_tests/voidfunc.yaka", "voidfunc.yaka",
            "../test_data/compiler_tests/voidfunc.tokens");
}
TEST_CASE("compiler: Native functions") {
  TEST_FILE("../test_data/compiler_tests/nativefunc.yaka", "nativefunc.yaka",
            "../test_data/compiler_tests/nativefunc.tokens");
}
TEST_CASE("compiler: Imports") {
  TEST_FILE("../test_data/import_tests/main.yaka", "main.yaka",
            "../test_data/import_tests/main.tokens");
}
TEST_CASE("compiler: Native functions in imports") {
  TEST_FILE("../test_data/compiler_tests/io_module_test/main.yaka", "main.yaka",
            "../test_data/compiler_tests/io_module_test/main.tokens");
}
TEST_CASE("compiler: Array methods") {
  TEST_FILE("../test_data/compiler_tests/arrstack.yaka", "arrstack.yaka",
            "../test_data/compiler_tests/arrstack.tokens");
}
TEST_CASE("compiler: Native defines") {
  TEST_FILE("../test_data/byol/lisp.yaka", "lisp.yaka",
            "../test_data/byol/lisp.tokens");
}
TEST_CASE("compiler: Do not copy str for getref") {
  TEST_FILE("../test_data/compiler_tests/do_not_copy_str_getref.yaka",
            "do_not_copy_str_getref.yaka",
            "../test_data/compiler_tests/do_not_copy_str_getref.tokens");
}
TEST_CASE("compiler: Str unref and getref hacks!") {
  TEST_FILE("../test_data/compiler_tests/str_getref_unref.yaka",
            "str_getref_unref.yaka",
            "../test_data/compiler_tests/str_getref_unref.tokens");
}
TEST_CASE("compiler: Test automatic generation for string hashes!") {
  TEST_FILE("../test_data/compiler_tests/string_hash.yaka", "string_hash.yaka",
            "../test_data/compiler_tests/string_hash.tokens");
}
TEST_CASE("compiler: Test return calls a function with defer deleted stuff !") {
  TEST_FILE("../test_data/compiler_tests/defer_return.yaka",
            "defer_return.yaka",
            "../test_data/compiler_tests/defer_return.tokens");
}
TEST_CASE("compiler: All @native stuff !") {
  TEST_FILE("../test_data/compiler_tests/native_function_type_tests.yaka",
            "native_function_type_tests.yaka",
            "../test_data/compiler_tests/native_function_type_tests.tokens");
}
TEST_CASE("compiler: Test elif") {
  TEST_FILE("../test_data/compiler_tests/elif_testing.yaka",
            "elif_testing.yaka",
            "../test_data/compiler_tests/elif_testing.tokens");
}
TEST_CASE("compiler: Casting") {
  TEST_FILE("../test_data/compiler_tests/casting_test.yaka",
            "casting_test.yaka",
            "../test_data/compiler_tests/casting_test.tokens");
}
TEST_CASE("compiler: Basic function pointer") {
  TEST_FILE("../test_data/compiler_tests/function_datatype_test.yaka",
            "function_datatype_test.yaka",
            "../test_data/compiler_tests/function_datatype_test.tokens");
}
TEST_CASE("compiler: Function pointer passing & calling") {
  TEST_FILE(
      "../test_data/compiler_tests/function_datatype_passing_calling_test.yaka",
      "function_datatype_passing_calling_test.yaka",
      "../test_data/compiler_tests/"
      "function_datatype_passing_calling_test.tokens");
}
TEST_CASE("compiler: Test automatic generation for normal hashes!") {
  TEST_FILE("../test_data/compiler_tests/normal_hash_map.yaka",
            "normal_hash_map.yaka",
            "../test_data/compiler_tests/normal_hash_map.tokens");
}
TEST_CASE("compiler: Test sorting functionality using qsort() !") {
  TEST_FILE("../test_data/compiler_tests/sort_test.yaka", "sort_test.yaka",
            "../test_data/compiler_tests/sort_test.tokens");
}
TEST_CASE("compiler: Test arrnew() !") {
  TEST_FILE("../test_data/compiler_tests/arrnew_test.yaka", "arrnew_test.yaka",
            "../test_data/compiler_tests/arrnew_test.tokens");
}
TEST_CASE("compiler: Test array() !") {
  TEST_FILE("../test_data/compiler_tests/array_test.yaka", "array_test.yaka",
            "../test_data/compiler_tests/array_test.tokens");
}
TEST_CASE("compiler: Test sorting with @native functions") {
  TEST_FILE("../test_data/compiler_tests/native_func_sort.yaka",
            "native_func_sort.yaka",
            "../test_data/compiler_tests/native_func_sort.tokens");
}
TEST_CASE("compiler: Test iif() builtin") {
  TEST_FILE("../test_data/compiler_tests/iif_test.yaka", "iif_test.yaka",
            "../test_data/compiler_tests/iif_test.tokens");
}
TEST_CASE("compiler: Test foreach() builtin") {
  TEST_FILE("../test_data/compiler_tests/functional_test_foreach.yaka",
            "functional_test_foreach.yaka",
            "../test_data/compiler_tests/functional_test_foreach.tokens");
}
TEST_CASE("compiler: Test countif() builtin") {
  TEST_FILE("../test_data/compiler_tests/functional_test_countif.yaka",
            "functional_test_countif.yaka",
            "../test_data/compiler_tests/functional_test_countif.tokens");
}
TEST_CASE("compiler: Test map() builtin") {
  TEST_FILE("../test_data/compiler_tests/functional_test_map.yaka",
            "functional_test_map.yaka",
            "../test_data/compiler_tests/functional_test_maph.tokens");
}
TEST_CASE("compiler: Test filter() builtin") {
  TEST_FILE("../test_data/compiler_tests/functional_test_filter.yaka",
            "functional_test_filter.yaka",
            "../test_data/compiler_tests/functional_test_filter.tokens");
}
TEST_CASE("compiler: Tuple data type") {
  TEST_FILE("../test_data/compiler_tests/tuple_test.yaka",
            "tuple_test.yaka",
            "../test_data/compiler_tests/tuple_test.tokens");
}
TEST_CASE("compiler: Number literals") {
  TEST_FILE("../test_data/compiler_tests/all_integers.yaka",
            "all_integers.yaka",
            "../test_data/compiler_tests/all_integers.tokens");
}