#include "ast/interpreter.h"
#include "ast/parser.h"
#include "catch2/catch.hpp"
#include "file_formats/tokens_file.h"
#include "tokenizer/block_analyzer.h"
using namespace yaksha;
TEST_CASE("interpreter: 1 + 2 * 3 + 4 / (2 + 2) * 10 - 2 --> 15") {
  ykdt_pool dt_pool{};
  tokenizer t{"code.py", "1 + 2 * 3 + 4 / (2 + 2) * 10 - 2"};
  t.tokenize();
  parser p{"code.py", t.tokens_, &dt_pool};
  auto expression = p.parse();
  if (!expression.empty()) {
    interpreter ip{&dt_pool};
    ip.calculate(expression);
    auto result = ip.result();
    REQUIRE(result->integer_val_ == 15);
    REQUIRE(result->is_primitive_or_obj());
    REQUIRE(result->datatype_->is_int());
  } else {
    FAIL("Must parse the expression");
  }
}
TEST_CASE("interpreter: 10 / 0 (div by zero)") {
  ykdt_pool dt_pool{};
  tokenizer t{"code.py", "10 / 0"};
  t.tokenize();
  parser p{"code.py", t.tokens_, &dt_pool};
  auto expression = p.parse();
  if (!expression.empty()) {
    interpreter ip{&dt_pool};
    ip.calculate(expression);
    auto result = ip.result();
    REQUIRE(result->string_val_.find("Integer division by zero") !=
            std::string::npos);
    REQUIRE(result->object_type_ == yaksha::object_type::RUNTIME_ERROR);
  } else {
    FAIL("Must parse the expression");
  }
}
TEST_CASE("interpreter: 1 + 2 != 3") {
  ykdt_pool dt_pool{};
  tokenizer t{"code.py", "1 + 2 != 3"};
  t.tokenize();
  parser p{"code.py", t.tokens_, &dt_pool};
  auto expression = p.parse();
  if (!expression.empty()) {
    interpreter ip{&dt_pool};
    ip.calculate(expression);
    auto result = ip.result();
    REQUIRE(!result->bool_val_);
    REQUIRE(result->is_primitive_or_obj());
    REQUIRE(result->datatype_->is_bool());
  } else {
    FAIL("Must parse the expression");
  }
}
TEST_CASE("interpreter: 1.0 + 2 (different data types cannot be added)") {
  ykdt_pool dt_pool{};
  tokenizer t{"code.py", "1.0 + 2"};
  t.tokenize();
  parser p{"code.py", t.tokens_, &dt_pool};
  auto expression = p.parse();
  if (!expression.empty()) {
    interpreter ip{&dt_pool};
    ip.calculate(expression);
    auto result = ip.result();
    REQUIRE(result->string_val_.find("Different data types..?") !=
            std::string::npos);
    REQUIRE(result->object_type_ == yaksha::object_type::RUNTIME_ERROR);
  } else {
    FAIL("Must parse the expression");
  }
}
TEST_CASE("interpreter: None != None is False") {
  ykdt_pool dt_pool{};
  tokenizer t{"code.py", "None != None"};
  t.tokenize();
  parser p{"code.py", t.tokens_, &dt_pool};
  auto expression = p.parse();
  if (!expression.empty()) {
    interpreter ip{&dt_pool};
    ip.calculate(expression);
    auto result = ip.result();
    REQUIRE(!result->bool_val_);
    REQUIRE(result->is_primitive_or_obj());
    REQUIRE(result->datatype_->is_bool());
  } else {
    FAIL("Must parse the expression");
  }
}
TEST_CASE("interpreter: None == None is True") {
  ykdt_pool dt_pool{};
  tokenizer t{"code.py", "None == None"};
  t.tokenize();
  parser p{"code.py", t.tokens_, &dt_pool};
  auto expression = p.parse();
  if (!expression.empty()) {
    interpreter ip{&dt_pool};
    ip.calculate(expression);
    auto result = ip.result();
    REQUIRE(result->bool_val_);
    REQUIRE(result->is_primitive_or_obj());
    REQUIRE(result->datatype_->is_bool());
  } else {
    FAIL("Must parse the expression");
  }
}
TEST_CASE("interpreter: Too big a float") {
  ykdt_pool dt_pool{};
  tokenizer t{"code.py", "3213211e32132\n"};
  t.tokenize();
  parser p{"code.py", t.tokens_, &dt_pool};
  auto expression = p.parse();
  if (!expression.empty()) {
    interpreter ip{&dt_pool};
    ip.calculate(expression);
    auto result = ip.result();
    REQUIRE(
        result->string_val_ ==
        "\ncode.py:1:1 at \"3213211e32132\" --> Double number out of range");
    REQUIRE(result->object_type_ == object_type::RUNTIME_ERROR);
  } else {
    FAIL("Must parse the expression");
  }
}
TEST_CASE("interpreter: a == 1 and a == 2 is False") {
  ykdt_pool dt_pool{};
  tokenizer t{"code.py", "a: int = 1\na == 1 and a == 2\n"};
  t.tokenize();
  parser p{"code.py", t.tokens_, &dt_pool};
  auto expression = p.parse();
  if (!expression.empty()) {
    interpreter ip{&dt_pool};
    ip.calculate(expression);
    auto result = ip.result();
    REQUIRE(!result->bool_val_);
    REQUIRE(result->is_primitive_or_obj());
    REQUIRE(result->datatype_->is_bool());
  } else {
    FAIL("Must parse the expression");
  }
}
TEST_CASE("interpreter: a == 1 or a == 2 is True") {
  ykdt_pool dt_pool{};
  tokenizer t{"code.py", "a: int = 1\na == 1 or a == 2\n"};
  t.tokenize();
  parser p{"code.py", t.tokens_, &dt_pool};
  auto expression = p.parse();
  if (!expression.empty()) {
    interpreter ip{&dt_pool};
    ip.calculate(expression);
    auto result = ip.result();
    REQUIRE(result->bool_val_);
    REQUIRE(result->is_primitive_or_obj());
    REQUIRE(result->datatype_->is_bool());
  } else {
    FAIL("Must parse the expression");
  }
}
TEST_CASE("interpreter: if and pass") {
  ykdt_pool dt_pool{};
  auto code = "# Hello World 123\n"
              "a: int = 10\n"
              "if a == 10:\n"
              "    print(\"a is \")\n"
              "    print(a)\n"
              "    print(\"\\n\")\n"
              "else:\n"
              "    pass\n"
              "1 + 2\n";// If this line is removed, result is 10
  tokenizer t{"code.py", code};
  t.tokenize();
  // Why? this is needed as we got blocks here
  // Blocks need to be analyzed before parsing!
  block_analyzer b{t.tokens_};
  b.analyze();
  parser p{"code.py", b.tokens_, &dt_pool};
  auto expression = p.parse();
  if (!expression.empty()) {
    interpreter ip{&dt_pool};
    ip.calculate(expression);
    auto result = ip.result();
    REQUIRE(result->integer_val_ == 3);
    REQUIRE(result->is_primitive_or_obj());
    REQUIRE(result->datatype_->is_int());
  } else {
    FAIL("Must parse the expression");
  }
}
TEST_CASE("interpreter: call a function") {
  ykdt_pool dt_pool{};
  auto code = "# Comment here\n"
              "def my_fun(p: int) -> int:\n"
              "    return p * 2 + 10\n"
              "\n"
              "\n"
              "a: int = 4\n"
              "while a > 0:\n"
              "    print(my_fun(a))\n"
              "    a = a - 1";
  tokenizer t{"code.py", code};
  t.tokenize();
  // Why? this is needed as we got blocks here
  // Blocks need to be analyzed before parsing!
  block_analyzer b{t.tokens_};
  b.analyze();
  parser p{"code.py", b.tokens_, &dt_pool};
  auto expression = p.parse();
  if (!expression.empty()) {
    interpreter ip{&dt_pool};
    ip.calculate(expression);
    auto result = ip.result();
    REQUIRE(result->bool_val_ == false);
    REQUIRE(result->is_primitive_or_obj());
    REQUIRE(result->datatype_->is_bool());
  } else {
    FAIL("Must parse the expression");
  }
}
TEST_CASE("interpreter: call a function recursive") {
  ykdt_pool dt_pool{};
  auto code = "# Recursion\n"
              "def f(v: int) -> int:\n"
              "    if v <= 0:\n"
              "        return 1\n"
              "    return v * f(v - 1)\n"
              "\n"
              "\n"
              "print(f(5))";
  tokenizer t{"code.py", code};
  t.tokenize();
  // Why? this is needed as we got blocks here
  // Blocks need to be analyzed before parsing!
  block_analyzer b{t.tokens_};
  b.analyze();
  parser p{"code.py", b.tokens_, &dt_pool};
  auto expression = p.parse();
  if (!expression.empty()) {
    interpreter ip{&dt_pool};
    ip.calculate(expression);
    auto result = ip.result();
    REQUIRE(result->integer_val_ == 120);// 5!
    REQUIRE(result->is_primitive_or_obj());
    REQUIRE(result->datatype_->is_int());
  } else {
    FAIL("Must parse the expression");
  }
}
TEST_CASE("interpreter: not a callable") {
  ykdt_pool dt_pool{};
  auto code = "# Bad function call\n"
              "\"Hello\"(123)\n";
  tokenizer t{"code.py", code};
  t.tokenize();
  // Why? this is needed as we got blocks here
  // Blocks need to be analyzed before parsing!
  block_analyzer b{t.tokens_};
  b.analyze();
  parser p{"code.py", b.tokens_, &dt_pool};
  auto expression = p.parse();
  if (!expression.empty()) {
    interpreter ip{&dt_pool};
    ip.calculate(expression);
    auto result = ip.result();
    REQUIRE(result->string_val_ ==
            "\ncode.py:2:12 at \")\" --> Not a callable");
    REQUIRE(result->object_type_ == object_type::RUNTIME_ERROR);
  } else {
    FAIL("Must parse the expression");
  }
}
TEST_CASE("interpreter: count to 10") {
  ykdt_pool dt_pool{};
  auto code = "a: int = 1\n"
              "while a != 11:\n"
              "    print(a)\n"
              "    print(\"\\n\")\n"
              "    a = a + 1\n";
  tokenizer t{"code.py", code};
  t.tokenize();
  block_analyzer b{t.tokens_};
  b.analyze();
  parser p{"code.py", b.tokens_, &dt_pool};
  auto expression = p.parse();
  if (!expression.empty()) {
    interpreter ip{&dt_pool};
    ip.calculate(expression);
    auto result = ip.result();
    // Why? Last thing that is in the stack is false
    //  before interpreter exits from the loop
    REQUIRE(!result->bool_val_);
    REQUIRE(result->is_primitive_or_obj());
    REQUIRE(result->datatype_->is_bool());
  } else {
    FAIL("Must parse the expression");
  }
}