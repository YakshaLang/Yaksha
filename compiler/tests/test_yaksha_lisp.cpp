// ==============================================================================================
// ╦  ┬┌─┐┌─┐┌┐┌┌─┐┌─┐    Yaksha Programming Language
// ║  ││  ├┤ │││└─┐├┤     is Licensed with GPLv3 + exta terms. Please see below.
// ╩═╝┴└─┘└─┘┘└┘└─┘└─┘
// Note: libs - MIT license, runtime/3rd - various
// ==============================================================================================
// GPLv3:
//
// Yaksha - Programming Language.
// Copyright (C) 2020 - 2023 Bhathiya Perera
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
#include "ast/parser.h"
#include "catch2/catch.hpp"
#include "utilities/cpp_util.h"
#define private public
#include "yaksha_lisp/yaksha_lisp.h"
#undef private
#include "tokenizer/block_analyzer.h"
#include "tokenizer/tokenizer.h"
#include <string>
#include <utility>
using namespace yaksha;
#ifdef YAKSHA_DEBUG
#define DISPLAY_AST
#endif
void test_parsing(std::string code) {
  auto yaksha_lisp_m = yaksha_macros{};
  auto dt = yaksha_lisp_tokenizer{&yaksha_lisp_m};
  auto parser = yaksha_lisp_parser{&dt, &yaksha_lisp_m};
  dt.tokenize("test.macro", std::move(code), yaksha_lisp_m.get_yk_token_pool());
  REQUIRE(dt.errors_.empty());
  parser.parse();
  REQUIRE(parser.errors_.empty());
#ifdef DISPLAY_AST
  parser.print();
#endif
}
void test_snippet_execute(std::string code) {
  auto yaksha_lisp_m = yaksha_macros{};
  auto dt = yaksha_lisp_m.create_tokenizer();
  auto parser = yaksha_lisp_m.create_parser(dt);
  dt->tokenize("test.macro", std::move(code),
               yaksha_lisp_m.get_yk_token_pool());
  REQUIRE(dt->errors_.empty());
  parser->parse();
  REQUIRE(parser->errors_.empty());
  auto env = yaksha_lisp_m.create_env();
  env->setup_builtins();
  if (env->builtins_created_) { env->setup_prelude(); }
  yaksha_lisp_m.builtins_root_ = env;
  yaksha_lisp_m.enable_gc();
  env->unlock();// unlock as we do not create 2nd env
  try {
    env->eval(parser->exprs_);
  } catch (const parsing_error &e) { FAIL(e.message_); }
  auto success_v = env->get("success");
  auto success = success_v != nullptr &&
                 success_v->type_ == yaksha_lisp_value_type::NUMBER &&
                 success_v->num_ == 1;
  REQUIRE(success);
}
void yaksha_macro_preprocess_happy_path(std::string code) {
  yaksha_macros yaksha_lisp_m{};
  try {
    ykdt_pool datatypes{};
    tokenizer t{"test", code, yaksha_lisp_m.get_yk_token_pool()};
    t.tokenize();
    block_analyzer ba{t.tokens_, yaksha_lisp_m.get_yk_token_pool()};
    ba.analyze();
    parser p{"test", ba.tokens_, &datatypes};
    p.preprocess(&yaksha_lisp_m, yaksha_lisp_m.get_yk_token_pool());
    p.parse();
    REQUIRE(p.errors_.empty());
  } catch (const parsing_error &e) { FAIL(e.message_); }
  REQUIRE(yaksha_lisp_m.roots_["test"]->symbols_["success"]->num_ == 1);
}
void test_snippet_execute_unhappy(std::string code,
                                  const std::string &error_message) {
  auto yaksha_lisp_m = yaksha_macros{};
  bool success = true;
  auto dt = yaksha_lisp_tokenizer{&yaksha_lisp_m};
  auto parser = yaksha_lisp_parser{&dt, &yaksha_lisp_m};
  dt.tokenize("test.macro", std::move(code), yaksha_lisp_m.get_yk_token_pool());
  if (!dt.errors_.empty()) {
    for (auto &e : dt.errors_) {
      if (e.message_ == error_message) {
        success = false;
        break;
      }
    }
    REQUIRE(!success);
    return;
  }
  parser.parse();
  if (!parser.errors_.empty()) {
    for (auto &e : parser.errors_) {
      if (e.message_ == error_message) {
        success = false;
        break;
      }
    }
    REQUIRE(!success);
    return;
  }
  auto env = yaksha_envmap{&yaksha_lisp_m};
  env.setup_builtins();
  try {
    env.eval(parser.exprs_);
  } catch (const parsing_error &e) {
    success = false;
    REQUIRE(e.message_ == error_message);
  }
  REQUIRE(!success);
}
void no_crash_test(std::string text) {
  REQUIRE(!text.empty());
  try {
    auto yaksha_lisp_m = yaksha_macros{};
    auto dt = yaksha_lisp_tokenizer{&yaksha_lisp_m};
    dt.tokenize("test.macro", std::move(text),
                yaksha_lisp_m.get_yk_token_pool());
    if (!dt.errors_.empty()) return;
    auto parser = yaksha_lisp_parser{&dt, &yaksha_lisp_m};
    parser.parse();
    if (!parser.errors_.empty()) return;
    auto env = yaksha_envmap{&yaksha_lisp_m};
    env.setup_builtins();
    env.eval(parser.exprs_);
  } catch (const parsing_error &ex) {
    // ignore
  }
}
TEST_CASE("yaksha_lisp: expected ')'") {
  test_snippet_execute_unhappy("(+ 1 2", "Expected a terminal");
}
TEST_CASE("yaksha_lisp: expected '('") {
  test_snippet_execute_unhappy("+ 1 2)", "Expected a terminal");
}
TEST_CASE("yaksha_lisp: define things") {
  test_parsing(R"(
    (def nil {})
    (def true 1)
    (def false 0)
    )");
}
TEST_CASE("yaksha_lisp: simple math") {
  test_snippet_execute(R"(
    (print (+ 1 2))
    (= success 1i32)
    )");
}
TEST_CASE("yaksha_lisp: if expression") {
  test_snippet_execute(R"(
    (if (== 1 1) (print "one is one") (print "one is not one"))
    (= success 1)
    )");
}
TEST_CASE("yaksha_lisp: if expression without else branch") {
  test_snippet_execute(R"(
    (if (== 1 1) (= success 1))
    )");
}
TEST_CASE("yaksha_lisp: if expression with else branch") {
  test_snippet_execute(R"(
    (if (== 1 2) (= success 0) (= success 1))
    )");
}
TEST_CASE("yaksha_lisp: if expression with else branch and else if") {
  test_snippet_execute(R"(
    (if (== 1 2) (= success 0) (if (== 1 1) (= success 1)))
    )");
}
TEST_CASE("yaksha_lisp: simple defun") {
  test_snippet_execute(R"(
    (defun add (a b) (println "add called") (+ a b))
    (if (== 3 (add 1 2)) (= success 1))
    (println (add 1 2))
    )");
}
TEST_CASE("yaksha_lisp: simple defun with if") {
  test_snippet_execute(R"(
    (defun x012 (n) (if (== n 0) 0 (if (== n 1) 1 2)))
    (if (== 1 (x012 1)) (= success 1))
    )");
}
TEST_CASE("yaksha_lisp: fibonacci recursive function") {
  test_snippet_execute(R"(
    (defun fib (n) (if (== n 0) 0 (if (== n 1) 1 (+ (fib (- n 1)) (fib (- n 2))))))
    (if (== 55 (fib 10)) (= success 1))
    )");
}
TEST_CASE("yaksha_lisp: create a list") {
  test_snippet_execute(R"(
    (def l (list 1 2 3))
    (if (== 3 (len l)) (= success 1))
    )");
}
TEST_CASE("yaksha_lisp: add to a list") {
  test_snippet_execute(R"(
    (def l (list 1 2 3))
    (push 4 l) # TODO see if this is valid in other languages
    (if (== 4 (len l)) (= success 1))
    )");
}
TEST_CASE("yaksha_lisp: head of a list") {
  test_snippet_execute(R"(
    (def l (list 1 2 3))
    (if (== 1 (head l)) (= success 1))
    )");
}
TEST_CASE("yaksha_lisp: tail of a list") {
  test_snippet_execute(R"(
    (def l (list 1 2 3))
    (if (== 2 (head (tail l))) (= success 1))
    )");
}
TEST_CASE("yaksha_lisp: use setq to change a value") {
  test_snippet_execute(R"(
    (def a 1)
    (setq a 2)
    (if (== 2 a) (= success 1))
    )");
}
TEST_CASE("yaksha_lisp: combine lists using +") {
  test_snippet_execute(R"(
    (def l1 (list 1 2 3))
    (def l2 (list 4 5 6))
    (def l3 (+ l1 l2))
    (if (== 6 (len l3)) (= success 1))
    )");
}
TEST_CASE("yaksha_lisp: list == check") {
  test_snippet_execute(R"(
    (def l1 (quote 1 2 3))
    (def l2 {1 2 3})
    (if (== l1 l2) (= success 1))
    )");
}
TEST_CASE("yaksha_lisp: test nil") {
  test_snippet_execute(R"(
    (if (== nil {}) (= success 1))
    )");
}
TEST_CASE("yaksha_lisp: test true") {
  test_snippet_execute(R"(
    (if (== true 1) (= success 1))
    )");
}
TEST_CASE("yaksha_lisp: test false") {
  test_snippet_execute(R"(
    (if (== false 0) (= success 1))
    )");
}
TEST_CASE("yaksha_lisp: test newline") {
  test_snippet_execute(R"(
    (if (or (== newline "\n") (== newline "\r\n")) (= success 1))
    )");
}
TEST_CASE("yaksha_lisp: test +") {
  test_snippet_execute(R"(
    (if (== 10 (+ 1 2 3 4)) (= success 1))
    )");
}
TEST_CASE("yaksha_lisp: test -") {
  test_snippet_execute(R"(
    (if (and (== 15 (- 20 5)) (== 1 (- -1 -2))) (= success 1))
    )");
}
TEST_CASE("yaksha_lisp: test *") {
  test_snippet_execute(R"(
    (if (== 24 (* 2 3 4)) (= success 1))
    )");
}
TEST_CASE("yaksha_lisp: test /") {
  test_snippet_execute(R"(
    (if (== 6 (/ 12 2)) (= success 1))
    )");
}
TEST_CASE("yaksha_lisp: test mod") {
  test_snippet_execute(R"(
    (if (== 1 (modulo 5 2)) (= success 1))
    )");
}
TEST_CASE("yaksha_lisp: test ==") {
  test_snippet_execute(R"(
    (if (== true (== 1 1)) (= success 1))
    )");
}
TEST_CASE("yaksha_lisp: test !=") {
  test_snippet_execute(R"(
    (if (== true (!= 1 2)) (= success 1))
    )");
}
TEST_CASE("yaksha_lisp: test <") {
  test_snippet_execute(R"(
    (if (== true (< 1 2)) (= success 1))
    )");
}
TEST_CASE("yaksha_lisp: test >") {
  test_snippet_execute(R"(
    (if (== true (> 2 1)) (= success 1))
    )");
}
TEST_CASE("yaksha_lisp: test <=") {
  test_snippet_execute(R"(
    (if (== true (<= 1 1)) (= success 1))
    )");
}
TEST_CASE("yaksha_lisp: test >=") {
  test_snippet_execute(R"(
    (if (== true (>= 1 1)) (= success 1))
    )");
}
TEST_CASE("yaksha_lisp: test and") {
  test_snippet_execute(R"(
    (if (== true (and true true)) (= success 1))
    )");
}
TEST_CASE("yaksha_lisp: test or") {
  test_snippet_execute(R"(
    (if (== true (or false true)) (= success 1))
    )");
}
TEST_CASE("yaksha_lisp: test not") {
  test_snippet_execute(R"(
    (if (== true (not false)) (= success 1))
    )");
}
TEST_CASE("yaksha_lisp: test if") {
  test_snippet_execute(R"(
    (if (== true (if true true false)) (= success 1))
    )");
}
TEST_CASE("yaksha_lisp: test def") {
  test_snippet_execute(R"(
    (def x 1)
    (if (== true (== x 1)) (= success 1))
    )");
}
TEST_CASE("yaksha_lisp: test =") {
  test_snippet_execute(R"(
    (= x 1)
    (if (== true (== x 1)) (= success 1))
    )");
}
TEST_CASE("yaksha_lisp: test do") {
  test_snippet_execute(R"(
    (do (def x 1) (if (== true (== x 1)) (= success 1)))
    )");
}
TEST_CASE("yaksha_lisp: test scope") {
  test_snippet_execute(R"(
    (= success 0)
    (= x 0)
    (scope (def x 1) (if (== true (== x 1)) (= success 1)))
    )");
}
TEST_CASE("yaksha_lisp: test quote") {
  test_snippet_execute(R"(
    (if (== (quote 1 2 3) (+ (quote 1) (quote 2) (quote 3))) (= success 1))
    )");
}
TEST_CASE("yaksha_lisp: test range") {
  test_snippet_execute(R"(
    (if (== true (== (range 1 5) (list 1 2 3 4))) (= success 1))
    )");
}
TEST_CASE("yaksha_lisp: test head") {
  test_snippet_execute(R"(
    (if (== true (== (head (list 1 2 3)) 1)) (= success 1))
    )");
}
TEST_CASE("yaksha_lisp: test tail") {
  test_snippet_execute(R"(
    (if (== (tail (list 1 2 3)) (list 2 3)) (= success 1))
    )");
}
TEST_CASE("yaksha_lisp: test cons") {
  test_snippet_execute(R"(
    (if (== (cons 1 (list 2 3)) (list 1 2 3)) (= success 1))
    )");
}
TEST_CASE("yaksha_lisp: test len") {
  test_snippet_execute(R"(
    (if (== (len (list 1 2 3)) 3) (= success 1))
    )");
}
TEST_CASE("yaksha_lisp: test push") {
  test_snippet_execute(R"(
    (define x (list 2 3))
    (push 1 x)
    (if (== x (list 2 3 1)) (= success 1))
    )");
}
TEST_CASE("yaksha_lisp: test pop") {
  test_snippet_execute(R"(
    (define x (list 1 2 3))
    (if (and (== (pop x) 3) (== x (list 1 2))) (= success 1))
    )");
}
TEST_CASE("yaksha_lisp: test lambda") {
  test_snippet_execute(R"(
    (if (== ((lambda (x) (+ x 1)) 1) 2) (= success 1))
    )");
}
TEST_CASE("yaksha_lisp: test print") {
  test_snippet_execute(R"(
    (print "hello")
    (= success 1)
    )");
}
TEST_CASE("yaksha_lisp: test println") {
  test_snippet_execute(R"(
    (println "hello")
    (= success 1)
    )");
}
TEST_CASE("yaksha_lisp: test try") {
  test_snippet_execute(R"(
    (try (raise_error "error"))
    (= success 1)
    )");
}
TEST_CASE("yaksha_lisp: test try_catch") {
  test_snippet_execute(R"(
    (= success 0)
    (try_catch ex (raise_error "error") (if (== ex "error") (= success 1)))
    )");
}
TEST_CASE("yaksha_lisp: test is_list") {
  test_snippet_execute(R"(
    (if (is_list (list 1 2 3)) (= success 1))
    )");
}
TEST_CASE("yaksha_lisp: test is_string") {
  test_snippet_execute(R"(
    (if (is_string "hello") (= success 1))
    )");
}
TEST_CASE("yaksha_lisp: test is_int") {
  test_snippet_execute(R"(
    (if (is_int 1) (= success 1))
    )");
}
TEST_CASE("yaksha_lisp: test is_truthy") {
  test_snippet_execute(R"(
    (if (is_truthy 1) (= success 1))
    )");
}
TEST_CASE("yaksha_lisp: test is_callable") {
  test_snippet_execute(R"(
    (if (is_callable (lambda (x) (+ x 1))) (= success 1))
    )");
}
TEST_CASE("yaksha_lisp: test is_nil") {
  test_snippet_execute(R"(
    (if (is_nil nil) (= success 1))
    )");
}
TEST_CASE("yaksha_lisp: test filter") {
  test_snippet_execute(R"(
    (if (== (filter (lambda (x) (== x 1)) (list 1 2 3)) (list 1)) (= success 1))
    )");
}
TEST_CASE("yaksha_lisp: test map") {
  test_snippet_execute(R"(
    (if (== (map (lambda (x) (+ x 1)) (list 1 2 3)) (list 2 3 4)) (= success 1))
    )");
}
TEST_CASE("yaksha_lisp: test reduce") {
  test_snippet_execute(R"(
    (if (== (reduce (lambda (x y) (+ x y)) (list 1 2 3)) 6) (= success 1))
    )");
}
TEST_CASE("yaksha_lisp: test to_string") {
  test_snippet_execute(R"(
    (if (== (to_string 1) "1") (= success 1))
    )");
}
TEST_CASE("yaksha_lisp: test to_int") {
  test_snippet_execute(R"(
    (if (== (to_int "1") 1) (= success 1))
    )");
}
TEST_CASE("yaksha_lisp: test io_read_file") {
  test_snippet_execute(R"(
    (if (== (io_read_file "test.txt") "hello") (= success 1))
    )");
}
TEST_CASE("yaksha_lisp: test io_write_file") {
  test_snippet_execute(R"(
    (io_write_file "test.txt" "hello")
    (= success 1)
    )");
}
TEST_CASE("yaksha_lisp: test random") {
  test_snippet_execute(R"(
    (if (and (>= (random 0 10) 0) (<= (random 0 10) 10)) (= success 1))
    )");
}
TEST_CASE("yaksha_lisp: test time") {
  test_snippet_execute(R"(
    (if (>= (time) 0) (= success 1))
    )");
}
TEST_CASE("yaksha_lisp: test insert") {
  test_snippet_execute(R"(
    (if (== (insert (list 1 2 3) 1 4) (list 1 4 2 3)) (= success 1))
    )");
}
TEST_CASE("yaksha_lisp: test remove") {
  test_snippet_execute(R"(
    (if (== (remove (list 1 2 3) 1) (list 1 3)) (= success 1))
    )");
}
TEST_CASE("yaksha_lisp: test parse") {
  test_snippet_execute(R"(
        (if (== (parse "1 2") {1 2}) (= success 1))
        )");
}
TEST_CASE("yaksha_lisp: test eval") {
  test_snippet_execute(R"(
        (if (== (eval (parse "1")) 1) (= success 1))
        )");
}
TEST_CASE("yaksha_lisp: test bitwise_and") {
  test_snippet_execute(R"(
    (if (== (bitwise_and 1 1) 1) (= success 1))
    )");
}
TEST_CASE("yaksha_lisp: test bitwise_or") {
  test_snippet_execute(R"(
    (if (== (bitwise_or 1 0) 1) (= success 1))
    )");
}
TEST_CASE("yaksha_lisp: test bitwise_xor") {
  test_snippet_execute(R"(
    (if (== (bitwise_xor 1 1) 0) (= success 1))
    )");
}
TEST_CASE("yaksha_lisp: test bitwise_not") {
  test_snippet_execute(R"(
    (if (== (bitwise_not 1) -2) (= success 1))
    )");
}
TEST_CASE("yaksha_lisp: test bitwise_left_shift") {
  test_snippet_execute(R"(
    (if (== (bitwise_left_shift 1 1) 2) (= success 1))
    )");
}
TEST_CASE("yaksha_lisp: test bitwise_right_shift") {
  test_snippet_execute(R"(
    (if (== (bitwise_right_shift 2 1) 1) (= success 1))
    )");
}
TEST_CASE("yaksha_lisp: test set") {
  test_snippet_execute(R"(
    (def a 2)
    (setq a 1)
    (if (== a 1) (= success 1))
    )");
}
TEST_CASE("yaksha_lisp: map literal") {
  test_parsing(R"(
    (def m @{a: 1, b: 2})
    )");
}
TEST_CASE("yaksha_lisp: map usage") {
  test_snippet_execute(R"(
        (def x 1)
        (def m @{a: (+ 1 1 2), "b": 2, 2: 3, x})
        (def m2 @{})
        (if (== (map_get m "a") 4) (= success 1))
        )");
}
TEST_CASE("yaksha_lisp: map_set, map_get, map_has") {
  test_snippet_execute(R"(
        (def m @{})
        (map_set m "a" 1)
        (def x 0)
        (if (== (map_get m "a") 1) (= x (+ x 1)))
        (if (map_has m "a") (= x (+ x 1)))
        (if (map_has m "b") (= x (- x 1)))
        (if (== x 2) (= success 1))
        )");
}
TEST_CASE("yaksha_lisp: for loop iterate a list") {
  test_snippet_execute(R"(
        (def x 0)
        (for i (list 1 2 3) (= x (+ x i)))
        (if (== x 6) (= success 1))
        )");
}
TEST_CASE("yaksha_lisp: for loop iterate a range") {
  test_snippet_execute(R"(
        (def x 0)
        (for i (range 1 4) (= x (+ x i)))
        (if (== x 6) (= success 1))
        )");
}
TEST_CASE("yaksha_lisp: while loop simple") {
  test_snippet_execute(R"(
        (def x 0)
        (while (< x 3) (= x (+ x 1)))
        (if (== x 3) (= success 1))
        )");
}

TEST_CASE("yaksha_lisp: map_keys, map_values, map_remove") {
  test_snippet_execute(R"(
        (def m @{a: 1, b: 2, c: 3})
        (def x 0)
        (def keys (map_keys m))
        (def values (map_values m))
        (if (== (len keys) 3) (= x (+ x 1)))
        (if (== (len values) 3) (= x (+ x 1)))
        (map_remove m "a")
        (if (== (len (map_keys m)) 2) (= x (+ x 1)))
        (if (== (len (map_values m)) 2) (= x (+ x 1)))
        (if (== x 4) (= success 1))
        )");
}
TEST_CASE("yaksha_lisp: random string test") {
  for (int rounds = 0; rounds < 100; rounds++) {
    std::string random_code = "(";
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, 5);
    std::vector<std::string> keywords = {
        "if", "def", "define", "defun", "setq", "print", "=", "!=", "==",
        "<",  "<=",  ">=",     "+",     "-",    "*",     "/", "%"};
    std::uniform_int_distribution<> dis_keywords(
        0, static_cast<int>(keywords.size() - 1));
    for (int i = 0; i < 100; ++i) {
      int r = dis(gen);
      if (r == 0) {
        random_code += " ";
      } else if (r == 1) {
        random_code += "(";
      } else if (r == 2) {
        random_code += ")";
      } else if (r == 3) {
        random_code += "{";
      } else if (r == 4) {
        random_code += "}";
      } else {
        random_code += keywords[dis_keywords(gen)];
      }
    }
    random_code += ")";
    no_crash_test(random_code);
  }
}
TEST_CASE("yaksha_lisp: random s-expression test with keywords") {
  for (int rounds = 0; rounds < 300; rounds++) {
    std::string random_code = "(";
    std::vector<std::string> keywords = {
        "if", "def", "define", "defun", "setq", "print", "=", "!=", "==",
        "<",  "<=",  ">=",     "+",     "-",    "*",     "/", "%"};
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, 5);
    std::uniform_int_distribution<> code_size_dis(30, 100);
    std::uniform_int_distribution<> dis_keywords(
        0, static_cast<int>(keywords.size() - 1));
    int num_open_parens = 1;
    int max_size = code_size_dis(gen);
    for (int i = 0; i < max_size; ++i) {
      int r = dis(gen);
      if (num_open_parens == 0 || r == 0) {
        random_code += "(";
        num_open_parens++;
      } else if (r == 1) {
        random_code += " ";
      } else if (r == 2) {
        random_code += ")";
        num_open_parens--;
      } else {
        random_code += keywords[dis_keywords(gen)];
        random_code += " ";
      }
    }
    while (num_open_parens > 0) {
      random_code += ")";
      num_open_parens--;
    }
    no_crash_test(random_code);
  }
}
TEST_CASE("yaksha_lisp: test builtin this") {
  test_snippet_execute(R"(
    (= x 0)
    (if (== (this) (this)) (= x (+ x 1)))
    (if (map_has (this) "map_has") (= x (+ x 1)))
    (if (== x 2) (= success 1))
    )");
}
TEST_CASE("yaksha_lisp: test builtin parent") {
  test_snippet_execute(R"(
    (if (== (parent) {}) (= success 1))
    )");
}
TEST_CASE("yaksha_lisp: test builtin repr") {
  test_snippet_execute(R"(
    (= x 0)
    (if (== (repr 1) "1") (= x (+ x 1)))
    (if (== (repr "5") "\"5\"") (= x (+ x 1)))
    (if (== (repr (list 1 2 3)) "{1 2 3}") (= x (+ x 1)))
    (if (== (repr @{a: 1}) "@{a: 1}") (= x (+ x 1)))
    (if (== x 4) (= success 1))
    )");
}
TEST_CASE("yaksha_lisp: single line stuff") {
  test_snippet_execute(R"((println "Hello World") (= success 1))");
}
TEST_CASE("yaksha_lisp: execute non existing element") {
  test_snippet_execute_unhappy(R"((echo "Hello World"))",
                               "unknown symbol: echo");
}
TEST_CASE("yaksha_lisp: execute non callable") {
  test_snippet_execute_unhappy(R"((3 "Hello World"))",
                               "calling a non callable (nor metamacro): 3");
}
TEST_CASE("yaksha_lisp: metamacro support") {
  test_snippet_execute(R"(
    (metamacro twice (x) (+ (list x) (list x)))
    (= value 1)
    (twice (= value (+ value 1)))
    (if (== value 3) (= success 1))
    )");
}
TEST_CASE("yaksha_lisp: metamacro support and is_metamacro") {
  test_snippet_execute(R"(
    (metamacro twice (x) (+ (list x) (list x)))
    (if (is_metamacro twice) (= success 1))
    )");
}
TEST_CASE("yaksha_lisp: metamacro support twice twice") {
  test_snippet_execute(R"(
    (metamacro twice (x) (+ (list x) (list x)))
    (= value 1)
    (twice (twice (= value (+ value 1))))
    (if (== value 5) (= success 1))
    )");
}
TEST_CASE("yaksha_lisp: '::' syntax sugar to get from map") {
  test_snippet_execute(R"(
    (= my_map @{a: 1})
    (= success my_map::a)
    )");
}
TEST_CASE("yaksha_lisp: os_exec test") {
std::stringstream ss{};
ss << "(system_enable_print)";
#if defined(YAKSHA_OS_WINDOWS)
  ss << R"((print (os_exec "cmd" "/C" "echo hello")))";
#else
  ss << R"((print (os_exec "sh" "-c" "echo hello")))";
#endif
  ss << "(= success 1)";
  test_snippet_execute(ss.str());
}
TEST_CASE("yaksha_lisp: os_shell test") {
  test_snippet_execute(R"((system_enable_print)
      (print "hello")
      (os_shell "echo off")
      (= success 1))");
}
TEST_CASE("yaksha_macro_support: macros!{}") {
  // ----------
  yaksha_macro_preprocess_happy_path(R"**(
macros! { # Comment here
    (system_enable_print)
    (println "// Oi, macros can print stuff")
    (= board_game_addict 1)
    (= success (== board_game_addict 1)) # Ha!
}
)**");
  // --------
}
TEST_CASE("yaksha_macro_support: macros!{} prelude is included") {
  // ----------
  yaksha_macro_preprocess_happy_path(R"**(macros! {
    (if (== 1 YK_PRELUDE_INCLUDED) (= success 1))
}
def main() -> int:
    return 0)**");
  // --------
}
TEST_CASE("yaksha_macro_support: dsl!{} simple macro") {
  // ----------
  yaksha_macro_preprocess_happy_path(R"**(macros! {
    # Get an integer_decimal token 7
    (defun ymacro_get () (list (ykt_integer_decimal 7)))
    # create a DSL macro named get! that executes above (defun ymacro_get...) function
    (yk_register {dsl get ymacro_get})
    # success happens here --
    (= success 1)
}

def main() -> int:
    e1: Array[int] = array("int", 1, 2, 3)
    e2 = array("int", 4, 5, 6, get!{})
    for i: int in e1:
        for j in e2:
            print(i)
            print(" - ")
            println(j)
    del e1
    del e2
    return 0)**");
  // --------
}
TEST_CASE("yaksha_macro_support: list builtins") {
  // ----------
  yaksha_macro_preprocess_happy_path(
      R"**(# In order to print a list of builtins in YakshaLisp
#   just run this!
macros! {
    (system_enable_print)
    (= all_builtins (map_keys (parent)))
    (= all_builtins (reversed (sorted (map repr all_builtins))))
    (defun comma (x y) (+ x ", " y))
    (= all_builtins (reduce comma all_builtins))
    (println "Builtins:")
    (println all_builtins)
    (= success 1)
}

def main() -> int:
    return 0
)**");
  // --------
}
