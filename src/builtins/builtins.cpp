// builtins.cpp
#include "builtins.h"
#include "ast/parser.h"
#include "tokenizer/tokenizer.h"
#include <sstream>
#include <utility>
using namespace yaksha;
//
// ┌─┐┬─┐┬─┐┌─┐┬ ┬┌┬┐
// ├─┤├┬┘├┬┘├─┘│ │ │
// ┴ ┴┴└─┴└─┴  └─┘ ┴
//
struct builtin_arrput : builtin {
  ykobject
  verify(const std::vector<ykobject> &args,
         const std::vector<expr *> &arg_expressions, datatype_parser *dt_parser,
         ykdt_pool *dt_pool,
         const std::unordered_map<std::string, import_stmt *> &import_aliases,
         const std::string &filepath, slot_matcher *dt_slot_matcher) override {
    auto o = ykobject(dt_pool);
    if (args.size() != 2) {
      o.string_val_ = "Two arguments must be provided for arrput() builtin";
    } else if (!args[0].datatype_->is_an_array()) {
      o.string_val_ = "First argument to arrput() must be an Array[?]";
    } else if (*(args[0].datatype_->args_[0]) != *args[1].datatype_) {
      o.string_val_ = "Second argument to arrput() must match with Array[?]";
    } else if (args[0].datatype_->args_[0]->is_m_entry() || args[0].datatype_->args_[0]->is_sm_entry()) {
      o.string_val_ = "arrput() does not work with maps";
    } else {
      return o;
    }
    o.object_type_ = object_type::RUNTIME_ERROR;
    return o;
  }
  bool should_compile_argument(int arg_index, expr *arg_expression) override {
    return true;
  }
  std::pair<std::string, ykobject>
  compile(const std::vector<std::pair<std::string, ykobject>> &args,
          const std::vector<expr *> &arg_expressions,
          datatype_compiler *dt_compiler, datatype_parser *dt_parser,
          ykdt_pool *dt_pool,
          const std::unordered_map<std::string, import_stmt *> &import_aliases,
          const std::string &filepath) override {
    auto o = ykobject(dt_pool);
    std::stringstream code{};
    if (args[1].second.datatype_->is_str()) {
      code << "yk__arrput(" << args[0].first << ", yk__sdsdup(" << args[1].first
           << "))";
    } else {
      code << "yk__arrput(" << args[0].first << ", " << args[1].first << ")";
    }
    return {code.str(), o};
  }
};
//
// ┌─┐┬─┐┬─┐┌─┐┌─┐┌─┐
// ├─┤├┬┘├┬┘├─┘│ │├─┘
// ┴ ┴┴└─┴└─┴  └─┘┴
//
struct builtin_arrpop : builtin {
  ykobject
  verify(const std::vector<ykobject> &args,
         const std::vector<expr *> &arg_expressions, datatype_parser *dt_parser,
         ykdt_pool *dt_pool,
         const std::unordered_map<std::string, import_stmt *> &import_aliases,
         const std::string &filepath, slot_matcher *dt_slot_matcher) override {
    auto o = ykobject(dt_pool);
    if (args.size() != 1) {
      o.string_val_ = "One argument must be provided for arrpop() builtin";
    } else if (!args[0].datatype_->is_an_array()) {
      o.string_val_ = "Argument to arrpop() must be an Array[?]";
    } else if (args[0].datatype_->args_[0]->is_m_entry() || args[0].datatype_->args_[0]->is_sm_entry()) {
      o.string_val_ = "arrpop() does not work with maps";
    } else {
      return ykobject(args[0].datatype_->args_[0]);
    }
    o.object_type_ = object_type::RUNTIME_ERROR;
    return o;
  }
  bool should_compile_argument(int arg_index, expr *arg_expression) override {
    return true;
  }
  std::pair<std::string, ykobject>
  compile(const std::vector<std::pair<std::string, ykobject>> &args,
          const std::vector<expr *> &arg_expressions,
          datatype_compiler *dt_compiler, datatype_parser *dt_parser,
          ykdt_pool *dt_pool,
          const std::unordered_map<std::string, import_stmt *> &import_aliases,
          const std::string &filepath) override {
    auto o = ykobject(dt_pool);
    std::stringstream code{};
    o = ykobject(args[0].second.datatype_->args_[0]);
    code << "yk__arrpop(" << args[0].first << ")";
    return {code.str(), o};
  }
};
//
// ┌─┐┬─┐┬┌┐┌┌┬┐
// ├─┘├┬┘││││ │
// ┴  ┴└─┴┘└┘ ┴
//
struct builtin_print : builtin {
  ykobject
  verify(const std::vector<ykobject> &args,
         const std::vector<expr *> &arg_expressions, datatype_parser *dt_parser,
         ykdt_pool *dt_pool,
         const std::unordered_map<std::string, import_stmt *> &import_aliases,
         const std::string &filepath, slot_matcher *dt_slot_matcher) override {
    auto o = ykobject(dt_pool);
    if (args.size() != 1) {
      o.string_val_ = "One argument must be provided for print() builtin";
    } else if (!args[0].is_primitive_or_obj() ||
               !args[0].datatype_->is_primitive()) {
      o.string_val_ = "Argument to print() must be a primitive";
    } else {
      return o;
    }
    o.object_type_ = object_type::RUNTIME_ERROR;
    return o;
  }
  bool should_compile_argument(int arg_index, expr *arg_expression) override {
    return true;
  }
  std::pair<std::string, ykobject>
  compile(const std::vector<std::pair<std::string, ykobject>> &args,
          const std::vector<expr *> &arg_expressions,
          datatype_compiler *dt_compiler, datatype_parser *dt_parser,
          ykdt_pool *dt_pool,
          const std::unordered_map<std::string, import_stmt *> &import_aliases,
          const std::string &filepath) override {
    auto o = ykobject(dt_pool);
    std::stringstream code{};
    auto rhs = args[0];
    if (rhs.second.datatype_->is_a_signed_integer()) {
      code << "yk__printint(((intmax_t)" << rhs.first << "))";
    } else if (rhs.second.datatype_->is_an_unsigned_integer()) {
      code << "yk__printuint(((uintmax_t)" << rhs.first << "))";
    } else if (rhs.second.datatype_->is_str()) {
      code << "yk__printstr((" << rhs.first << "))";
    } else if (rhs.second.datatype_->is_a_float()) {
      code << "yk__printdbl((" << rhs.first << "))";
    }
    return {code.str(), o};
  }
};
//
// ┌─┐┬─┐┬┌┐┌┌┬┐┬  ┌┐┌
// ├─┘├┬┘││││ │ │  │││
// ┴  ┴└─┴┘└┘ ┴ ┴─┘┘└┘
//
struct builtin_println : builtin {
  ykobject
  verify(const std::vector<ykobject> &args,
         const std::vector<expr *> &arg_expressions, datatype_parser *dt_parser,
         ykdt_pool *dt_pool,
         const std::unordered_map<std::string, import_stmt *> &import_aliases,
         const std::string &filepath, slot_matcher *dt_slot_matcher) override {
    auto o = ykobject(dt_pool);
    if (args.size() != 1) {
      o.string_val_ = "One argument must be provided for println() builtin";
    } else if (!args[0].is_primitive_or_obj() ||
               !args[0].datatype_->is_primitive()) {
      o.string_val_ = "Argument to println() must be a primitive";
    } else {
      return o;
    }
    o.object_type_ = object_type::RUNTIME_ERROR;
    return o;
  }
  bool should_compile_argument(int arg_index, expr *arg_expression) override {
    return true;
  }
  std::pair<std::string, ykobject>
  compile(const std::vector<std::pair<std::string, ykobject>> &args,
          const std::vector<expr *> &arg_expressions,
          datatype_compiler *dt_compiler, datatype_parser *dt_parser,
          ykdt_pool *dt_pool,
          const std::unordered_map<std::string, import_stmt *> &import_aliases,
          const std::string &filepath) override {
    auto o = ykobject(dt_pool);
    std::stringstream code{};
    auto rhs = args[0];
    if (rhs.second.datatype_->is_a_signed_integer()) {
      code << "yk__printlnint(((intmax_t)" << rhs.first << "))";
    } else if (rhs.second.datatype_->is_an_unsigned_integer()) {
      code << "yk__printlnuint(((uintmax_t)" << rhs.first << "))";
    } else if (rhs.second.datatype_->is_str()) {
      code << "yk__printlnstr((" << rhs.first << "))";
    } else if (rhs.second.datatype_->is_a_float()) {
      code << "yk__printlndbl((" << rhs.first << "))";
    }
    return {code.str(), o};
  }
};
//
// ┬  ┌─┐┌┐┌
// │  ├┤ │││
// ┴─┘└─┘┘└┘
//
struct builtin_len : builtin {
  ykobject
  verify(const std::vector<ykobject> &args,
         const std::vector<expr *> &arg_expressions, datatype_parser *dt_parser,
         ykdt_pool *dt_pool,
         const std::unordered_map<std::string, import_stmt *> &import_aliases,
         const std::string &filepath, slot_matcher *dt_slot_matcher) override {
    auto o = ykobject(dt_pool);
    if (args.size() != 1) {
      o.string_val_ = "One argument must be provided for len() builtin";
    } else if (!args[0].datatype_->is_an_array() &&
               !args[0].datatype_->is_str()) {
      o.string_val_ = "Argument to len() must be an Array or a str";
    } else {
      return ykobject(dt_pool->create("int"));
    }
    o.object_type_ = object_type::RUNTIME_ERROR;
    return o;
  }
  bool should_compile_argument(int arg_index, expr *arg_expression) override {
    return true;
  }
  std::pair<std::string, ykobject>
  compile(const std::vector<std::pair<std::string, ykobject>> &args,
          const std::vector<expr *> &arg_expressions,
          datatype_compiler *dt_compiler, datatype_parser *dt_parser,
          ykdt_pool *dt_pool,
          const std::unordered_map<std::string, import_stmt *> &import_aliases,
          const std::string &filepath) override {
    auto o = ykobject(dt_pool);
    std::stringstream code{};
    if (args[0].second.datatype_->is_str()) {
      code << "yk__sdslen(" << args[0].first << ")";
    } else if (args[0].second.datatype_->is_an_array() &&
               args[0].second.datatype_->args_[0]->is_sm_entry()) {
      // Array[SMEntry[V]]
      code << "yk__shlen(" << args[0].first << ")";
    } else if (args[0].second.datatype_->is_an_array() &&
               args[0].second.datatype_->args_[0]->is_m_entry()) {
      // Array[MEntry[K,V]]
      code << "yk__hmlen(" << args[0].first << ")";
    } else {
      code << "yk__arrlen(" << args[0].first << ")";
    }
    o = ykobject(dt_pool->create("int"));
    return {code.str(), o};
  }
};
//
// ┌─┐┬ ┬┌─┐┬─┐┌─┐┌┬┐
// │  ├─┤├─┤├┬┘├─┤ │
// └─┘┴ ┴┴ ┴┴└─┴ ┴ ┴
//
struct builtin_charat : builtin {
  ykobject
  verify(const std::vector<ykobject> &args,
         const std::vector<expr *> &arg_expressions, datatype_parser *dt_parser,
         ykdt_pool *dt_pool,
         const std::unordered_map<std::string, import_stmt *> &import_aliases,
         const std::string &filepath, slot_matcher *dt_slot_matcher) override {
    auto o = ykobject(dt_pool);
    if (args.size() != 2) {
      o.string_val_ = "Two arguments must be provided for charat() builtin";
    } else if (!args[0].datatype_->is_str()) {
      o.string_val_ = "Fist argument to charat() must be a str";
    } else if (!args[1].datatype_->is_an_integer()) {
      o.string_val_ = "Second argument to charat() must be an integer";
    } else {
      return ykobject(dt_pool->create("int"));
    }
    o.object_type_ = object_type::RUNTIME_ERROR;
    return o;
  }
  bool should_compile_argument(int arg_index, expr *arg_expression) override {
    return true;
  }
  std::pair<std::string, ykobject>
  compile(const std::vector<std::pair<std::string, ykobject>> &args,
          const std::vector<expr *> &arg_expressions,
          datatype_compiler *dt_compiler, datatype_parser *dt_parser,
          ykdt_pool *dt_pool,
          const std::unordered_map<std::string, import_stmt *> &import_aliases,
          const std::string &filepath) override {
    auto o = ykobject(dt_pool);
    std::stringstream code{};
    code << "(" << args[0].first << "[" << args[1].first << "])";
    o = ykobject(dt_pool->create("int"));
    return {code.str(), o};
  }
};
//
// ┌─┐┌─┐┌┬┐┬─┐┌─┐┌─┐
// │ ┬├┤  │ ├┬┘├┤ ├┤
// └─┘└─┘ ┴ ┴└─└─┘└
//
struct builtin_getref : builtin {
  ykobject
  verify(const std::vector<ykobject> &args,
         const std::vector<expr *> &arg_expressions, datatype_parser *dt_parser,
         ykdt_pool *dt_pool,
         const std::unordered_map<std::string, import_stmt *> &import_aliases,
         const std::string &filepath, slot_matcher *dt_slot_matcher) override {
    auto o = ykobject(dt_pool);
    if (args.size() != 1) {
      o.string_val_ = "One argument must be provided for getref() builtin";
    } else if (!args[0].is_primitive_or_obj()) {
      o.string_val_ = "Argument to getref() must be an object or primitive";
    } else if (arg_expressions[0]->get_type() !=
               yaksha::ast_type::EXPR_VARIABLE) {
      o.string_val_ = "Argument to getref() must be a named variable";
    } else {
      ykdatatype *dt = dt_pool->create("Ptr");
      dt->args_.emplace_back(args[0].datatype_);
      return ykobject(dt);
    }
    o.object_type_ = object_type::RUNTIME_ERROR;
    return o;
  }
  bool should_compile_argument(int arg_index, expr *arg_expression) override {
    return true;
  }
  std::pair<std::string, ykobject>
  compile(const std::vector<std::pair<std::string, ykobject>> &args,
          const std::vector<expr *> &arg_expressions,
          datatype_compiler *dt_compiler, datatype_parser *dt_parser,
          ykdt_pool *dt_pool,
          const std::unordered_map<std::string, import_stmt *> &import_aliases,
          const std::string &filepath) override {
    auto o = ykobject(dt_pool);
    std::stringstream code{};
    code << "(&(" << args[0].first << "))";
    ykdatatype *dt = dt_pool->create("Ptr");
    dt->args_.emplace_back(args[0].second.datatype_);
    o = ykobject(dt);
    return {code.str(), o};
  }
};
//
// ┬ ┬┌┐┌┬─┐┌─┐┌─┐
// │ ││││├┬┘├┤ ├┤
// └─┘┘└┘┴└─└─┘└
//
struct builtin_unref : builtin {
  ykobject
  verify(const std::vector<ykobject> &args,
         const std::vector<expr *> &arg_expressions, datatype_parser *dt_parser,
         ykdt_pool *dt_pool,
         const std::unordered_map<std::string, import_stmt *> &import_aliases,
         const std::string &filepath, slot_matcher *dt_slot_matcher) override {
    auto o = ykobject(dt_pool);
    if (args.size() != 1) {
      o.string_val_ = "One argument must be provided for unref() builtin";
    } else if (!args[0].datatype_->is_a_pointer()) {
      o.string_val_ = "Argument to unref() must be a Ptr[?]";
    } else {
      return ykobject(args[0].datatype_->args_[0]);
    }
    o.object_type_ = object_type::RUNTIME_ERROR;
    return o;
  }
  bool should_compile_argument(int arg_index, expr *arg_expression) override {
    return true;
  }
  std::pair<std::string, ykobject>
  compile(const std::vector<std::pair<std::string, ykobject>> &args,
          const std::vector<expr *> &arg_expressions,
          datatype_compiler *dt_compiler, datatype_parser *dt_parser,
          ykdt_pool *dt_pool,
          const std::unordered_map<std::string, import_stmt *> &import_aliases,
          const std::string &filepath) override {
    auto o = ykobject(dt_pool);
    std::stringstream code{};
    code << "(*(" << args[0].first << "))";
    o = ykobject(args[0].second.datatype_->args_[0]);
    return {code.str(), o};
  }
};
//
// ┌─┐┬ ┬┌┐┌┌─┐┬ ┬
// └─┐├─┤│││├┤ │││
// └─┘┴ ┴┘└┘└─┘└┴┘
//
struct builtin_shnew : builtin {
  ykobject
  verify(const std::vector<ykobject> &args,
         const std::vector<expr *> &arg_expressions, datatype_parser *dt_parser,
         ykdt_pool *dt_pool,
         const std::unordered_map<std::string, import_stmt *> &import_aliases,
         const std::string &filepath, slot_matcher *dt_slot_matcher) override {
    auto o = ykobject(dt_pool);
    if (args.size() != 1) {
      o.string_val_ = "One argument must be provided for shnew() builtin";
    } else if (!args[0].datatype_->is_an_array() ||
               !args[0].datatype_->args_[0]->is_sm_entry()) {
      o.string_val_ = "Argument to shnew() must match with Array[SMEntry[?]]";
    } else {
      return o;
    }
    o.object_type_ = object_type::RUNTIME_ERROR;
    return o;
  }
  bool should_compile_argument(int arg_index, expr *arg_expression) override {
    return true;
  }
  std::pair<std::string, ykobject>
  compile(const std::vector<std::pair<std::string, ykobject>> &args,
          const std::vector<expr *> &arg_expressions,
          datatype_compiler *dt_compiler, datatype_parser *dt_parser,
          ykdt_pool *dt_pool,
          const std::unordered_map<std::string, import_stmt *> &import_aliases,
          const std::string &filepath) override {
    auto o = ykobject(dt_pool);
    std::stringstream code{};
    code << "yk__sh_new_strdup(" << args[0].first << ")";
    return {code.str(), o};
  }
};
//
// ┌─┐┬ ┬┌─┐┌─┐┌┬┐
// └─┐├─┤│ ┬├┤  │
// └─┘┴ ┴└─┘└─┘ ┴
//
struct builtin_shget : builtin {
  ykobject
  verify(const std::vector<ykobject> &args,
         const std::vector<expr *> &arg_expressions, datatype_parser *dt_parser,
         ykdt_pool *dt_pool,
         const std::unordered_map<std::string, import_stmt *> &import_aliases,
         const std::string &filepath, slot_matcher *dt_slot_matcher) override {
    auto o = ykobject(dt_pool);
    if (args.size() != 2) {
      o.string_val_ = "Two arguments must be provided for shget() builtin";
    } else if (!args[0].datatype_->is_an_array() ||
               !args[0].datatype_->args_[0]->is_sm_entry()) {
      o.string_val_ =
          "First argument to shget() must match with Array[SMEntry[?]]";
    } else if (!args[1].datatype_->is_str()) {
      o.string_val_ = "Second argument to shget() must be a str";
    } else {
      return ykobject(args[0].datatype_->args_[0]->args_[0]);
    }
    o.object_type_ = object_type::RUNTIME_ERROR;
    return o;
  }
  bool should_compile_argument(int arg_index, expr *arg_expression) override {
    return true;
  }
  std::pair<std::string, ykobject>
  compile(const std::vector<std::pair<std::string, ykobject>> &args,
          const std::vector<expr *> &arg_expressions,
          datatype_compiler *dt_compiler, datatype_parser *dt_parser,
          ykdt_pool *dt_pool,
          const std::unordered_map<std::string, import_stmt *> &import_aliases,
          const std::string &filepath) override {
    auto o = ykobject(dt_pool);
    std::stringstream code{};
    code << "yk__shget(" << args[0].first << ", " << args[1].first << ")";
    o = ykobject(args[0].second.datatype_->args_[0]->args_[0]);
    return {code.str(), o};
  }
};
//
// ┌─┐┬ ┬┌─┐┌─┐┌┬┐┬
// └─┐├─┤│ ┬├┤  │ │
// └─┘┴ ┴└─┘└─┘ ┴ ┴
//
struct builtin_shgeti : builtin {
  ykobject
  verify(const std::vector<ykobject> &args,
         const std::vector<expr *> &arg_expressions, datatype_parser *dt_parser,
         ykdt_pool *dt_pool,
         const std::unordered_map<std::string, import_stmt *> &import_aliases,
         const std::string &filepath, slot_matcher *dt_slot_matcher) override {
    auto o = ykobject(dt_pool);
    if (args.size() != 2) {
      o.string_val_ = "Two arguments must be provided for shgeti() builtin";
    } else if (!args[0].datatype_->is_an_array() ||
               !args[0].datatype_->args_[0]->is_sm_entry()) {
      o.string_val_ =
          "First argument to shgeti() must match with Array[SMEntry[?]]";
    } else if (!args[1].datatype_->is_str()) {
      o.string_val_ = "Second argument to shgeti() must be a str";
    } else {
      return ykobject(dt_pool->create("int"));
    }
    o.object_type_ = object_type::RUNTIME_ERROR;
    return o;
  }
  bool should_compile_argument(int arg_index, expr *arg_expression) override {
    return true;
  }
  std::pair<std::string, ykobject>
  compile(const std::vector<std::pair<std::string, ykobject>> &args,
          const std::vector<expr *> &arg_expressions,
          datatype_compiler *dt_compiler, datatype_parser *dt_parser,
          ykdt_pool *dt_pool,
          const std::unordered_map<std::string, import_stmt *> &import_aliases,
          const std::string &filepath) override {
    auto o = ykobject(dt_pool);
    std::stringstream code{};
    code << "yk__shgeti(" << args[0].first << ", " << args[1].first << ")";
    o = ykobject(dt_pool->create("int"));
    return {code.str(), o};
  }
};
//
// ┌─┐┬ ┬┌─┐┬ ┬┌┬┐
// └─┐├─┤├─┘│ │ │
// └─┘┴ ┴┴  └─┘ ┴
//
struct builtin_shput : builtin {
  ykobject
  verify(const std::vector<ykobject> &args,
         const std::vector<expr *> &arg_expressions, datatype_parser *dt_parser,
         ykdt_pool *dt_pool,
         const std::unordered_map<std::string, import_stmt *> &import_aliases,
         const std::string &filepath, slot_matcher *dt_slot_matcher) override {
    auto o = ykobject(dt_pool);
    if (args.size() != 3) {
      o.string_val_ = "Three arguments must be provided for shput() builtin";
    } else if (!args[0].datatype_->is_an_array() ||
               !args[0].datatype_->args_[0]->is_sm_entry()) {
      o.string_val_ =
          "First argument to shput() must match with Array[SMEntry[?]]";
    } else if (!args[1].datatype_->is_str()) {
      o.string_val_ = "Second argument to shput() must be a str";
    } else if (!(*args[2].datatype_ ==
                 *args[0].datatype_->args_[0]->args_[0])) {
      o.string_val_ = "Third argument to shput() must match provided map";
    } else {
      return o;
    }
    o.object_type_ = object_type::RUNTIME_ERROR;
    return o;
  }
  bool should_compile_argument(int arg_index, expr *arg_expression) override {
    return true;
  }
  std::pair<std::string, ykobject>
  compile(const std::vector<std::pair<std::string, ykobject>> &args,
          const std::vector<expr *> &arg_expressions,
          datatype_compiler *dt_compiler, datatype_parser *dt_parser,
          ykdt_pool *dt_pool,
          const std::unordered_map<std::string, import_stmt *> &import_aliases,
          const std::string &filepath) override {
    auto o = ykobject(dt_pool);
    std::stringstream code{};
    code << "yk__shput(" << args[0].first << ", " << args[1].first << ", "
         << args[2].first << ")";
    return {code.str(), o};
  }
};
//
// ┌─┐┌─┐┌─┐┌┬┐
// │  ├─┤└─┐ │
// └─┘┴ ┴└─┘ ┴
//
struct builtin_cast : builtin {
  ykobject
  verify(const std::vector<ykobject> &args,
         const std::vector<expr *> &arg_expressions, datatype_parser *dt_parser,
         ykdt_pool *dt_pool,
         const std::unordered_map<std::string, import_stmt *> &import_aliases,
         const std::string &filepath, slot_matcher *dt_slot_matcher) override {
    auto o = ykobject(dt_pool);
    if (args.size() != 2) {
      o.string_val_ = "Two arguments must be provided for cast() builtin";
    } else if (!args[0].datatype_->is_str() ||
               arg_expressions[0]->get_type() != ast_type::EXPR_LITERAL) {
      o.string_val_ = "First argument to cast() must be a literal.";
    } else if (!args[1].is_primitive_or_obj()) {
      o.string_val_ = "Second argument to cast() must be an object/primitive";
    } else {
      auto *lit = dynamic_cast<literal_expr *>(arg_expressions[0]);
      if (lit->literal_token_->type_ != token_type::STRING &&
          lit->literal_token_->type_ != token_type::THREE_QUOTE_STRING) {
        o.string_val_ = "First argument to cast() must be a string literal.";
      } else {
        auto data_type = lit->literal_token_->token_;
        ykdatatype *parsed_dt =
            dt_parser->parse(data_type, import_aliases, filepath);
        if (parsed_dt == nullptr) {
          o.string_val_ = "Invalid data type provided to cast()";
        } else {
          return ykobject(parsed_dt);
        }
      }
    }
    o.object_type_ = object_type::RUNTIME_ERROR;
    return o;
  }
  bool should_compile_argument(int arg_index, expr *arg_expression) override {
    if (arg_index == 0) { return false; }
    return true;
  }
  std::pair<std::string, ykobject>
  compile(const std::vector<std::pair<std::string, ykobject>> &args,
          const std::vector<expr *> &arg_expressions,
          datatype_compiler *dt_compiler, datatype_parser *dt_parser,
          ykdt_pool *dt_pool,
          const std::unordered_map<std::string, import_stmt *> &import_aliases,
          const std::string &filepath) override {
    auto o = ykobject(dt_pool);
    std::stringstream code{};
    auto dt = dynamic_cast<literal_expr *>(arg_expressions[0]);
    auto out_dt =
        dt_parser->parse(dt->literal_token_->token_, import_aliases, filepath);
    code << "((" << dt_compiler->convert_dt(out_dt) << ")" << args[1].first
         << ")";
    o = ykobject(out_dt);
    return {code.str(), o};
  }
};
//
// ┬ ┬┌┬┐┌┐┌┌─┐┬ ┬
// ├─┤││││││├┤ │││
// ┴ ┴┴ ┴┘└┘└─┘└┴┘
//
struct builtin_hmnew : builtin {
  ykobject
  verify(const std::vector<ykobject> &args,
         const std::vector<expr *> &arg_expressions, datatype_parser *dt_parser,
         ykdt_pool *dt_pool,
         const std::unordered_map<std::string, import_stmt *> &import_aliases,
         const std::string &filepath, slot_matcher *dt_slot_matcher) override {
    auto o = ykobject(dt_pool);
    if (args.size() != 1) {
      o.string_val_ = "One argument must be provided for hmnew() builtin";
    } else if (!args[0].datatype_->is_an_array() ||
               !args[0].datatype_->args_[0]->is_m_entry()) {
      o.string_val_ = "Argument to hmnew() must match with Array[MEntry[K,V]]";
    } else {
      return o;
    }
    o.object_type_ = object_type::RUNTIME_ERROR;
    return o;
  }
  bool should_compile_argument(int arg_index, expr *arg_expression) override {
    return true;
  }
  std::pair<std::string, ykobject>
  compile(const std::vector<std::pair<std::string, ykobject>> &args,
          const std::vector<expr *> &arg_expressions,
          datatype_compiler *dt_compiler, datatype_parser *dt_parser,
          ykdt_pool *dt_pool,
          const std::unordered_map<std::string, import_stmt *> &import_aliases,
          const std::string &filepath) override {
    auto o = ykobject(dt_pool);
    return {"", o};
  }
};
//
// ┬ ┬┌┬┐┌─┐┌─┐┌┬┐
// ├─┤││││ ┬├┤  │
// ┴ ┴┴ ┴└─┘└─┘ ┴
//
struct builtin_hmget : builtin {
  ykobject
  verify(const std::vector<ykobject> &args,
         const std::vector<expr *> &arg_expressions, datatype_parser *dt_parser,
         ykdt_pool *dt_pool,
         const std::unordered_map<std::string, import_stmt *> &import_aliases,
         const std::string &filepath, slot_matcher *dt_slot_matcher) override {
    auto o = ykobject(dt_pool);
    if (args.size() != 2) {
      o.string_val_ = "Two arguments must be provided for hmget() builtin";
    } else if (!args[0].datatype_->is_an_array() ||
               !args[0].datatype_->args_[0]->is_m_entry()) {
      o.string_val_ =
          "First argument to hmget() must match with Array[MEntry[K,V]]";
    } else if (*(args[0].datatype_->args_[0]->args_[0]) !=
               *(args[1].datatype_)) {
      o.string_val_ = "Second argument to hmget() must be a valid key matching "
                      "with Array[MEntry[K,V]]";
    } else {
      return ykobject(args[0].datatype_->args_[0]->args_[1]);
    }
    o.object_type_ = object_type::RUNTIME_ERROR;
    return o;
  }
  bool should_compile_argument(int arg_index, expr *arg_expression) override {
    return true;
  }
  std::pair<std::string, ykobject>
  compile(const std::vector<std::pair<std::string, ykobject>> &args,
          const std::vector<expr *> &arg_expressions,
          datatype_compiler *dt_compiler, datatype_parser *dt_parser,
          ykdt_pool *dt_pool,
          const std::unordered_map<std::string, import_stmt *> &import_aliases,
          const std::string &filepath) override {
    auto o = ykobject(dt_pool);
    std::stringstream code{};
    code << "yk__hmget(" << args[0].first << ", " << args[1].first << ")";
    o = ykobject(args[0].second.datatype_->args_[0]->args_[0]);
    return {code.str(), o};
  }
};
//
// ┬ ┬┌┬┐┌─┐┌─┐┌┬┐┬
// ├─┤││││ ┬├┤  │ │
// ┴ ┴┴ ┴└─┘└─┘ ┴ ┴
//
struct builtin_hmgeti : builtin {
  ykobject
  verify(const std::vector<ykobject> &args,
         const std::vector<expr *> &arg_expressions, datatype_parser *dt_parser,
         ykdt_pool *dt_pool,
         const std::unordered_map<std::string, import_stmt *> &import_aliases,
         const std::string &filepath, slot_matcher *dt_slot_matcher) override {
    auto o = ykobject(dt_pool);
    if (args.size() != 2) {
      o.string_val_ = "Two arguments must be provided for hmgeti() builtin";
    } else if (!args[0].datatype_->is_an_array() ||
               !args[0].datatype_->args_[0]->is_m_entry()) {
      o.string_val_ =
          "First argument to hmgeti() must match with Array[MEntry[K,V]]";
    } else if (*(args[0].datatype_->args_[0]->args_[0]) !=
               *(args[1].datatype_)) {
      o.string_val_ = "Second argument to hmget() must be a valid key matching "
                      "with Array[MEntry[K,V]]";
    } else {
      return ykobject(dt_pool->create("int"));
    }
    o.object_type_ = object_type::RUNTIME_ERROR;
    return o;
  }
  bool should_compile_argument(int arg_index, expr *arg_expression) override {
    return true;
  }
  std::pair<std::string, ykobject>
  compile(const std::vector<std::pair<std::string, ykobject>> &args,
          const std::vector<expr *> &arg_expressions,
          datatype_compiler *dt_compiler, datatype_parser *dt_parser,
          ykdt_pool *dt_pool,
          const std::unordered_map<std::string, import_stmt *> &import_aliases,
          const std::string &filepath) override {
    auto o = ykobject(dt_pool);
    std::stringstream code{};
    code << "yk__hmgeti(" << args[0].first << ", " << args[1].first << ")";
    o = ykobject(dt_pool->create("int"));
    return {code.str(), o};
  }
};
//
// ┬ ┬┌┬┐┌─┐┬ ┬┌┬┐
// ├─┤│││├─┘│ │ │
// ┴ ┴┴ ┴┴  └─┘ ┴
//
struct builtin_hmput : builtin {
  ykobject
  verify(const std::vector<ykobject> &args,
         const std::vector<expr *> &arg_expressions, datatype_parser *dt_parser,
         ykdt_pool *dt_pool,
         const std::unordered_map<std::string, import_stmt *> &import_aliases,
         const std::string &filepath, slot_matcher *dt_slot_matcher) override {
    auto o = ykobject(dt_pool);
    if (args.size() != 3) {
      o.string_val_ = "Three arguments must be provided for hmput() builtin";
    } else if (!args[0].datatype_->is_an_array() ||
               !args[0].datatype_->args_[0]->is_m_entry()) {
      o.string_val_ =
          "First argument to hmput() must match with Array[MEntry[K,V]]";
    } else if (*(args[0].datatype_->args_[0]->args_[0]) !=
               *(args[1].datatype_)) {
      o.string_val_ = "Second argument to hmput() must be a valid key matching "
                      "with Array[MEntry[K,V]]";
    } else if (*(args[0].datatype_->args_[0]->args_[1]) !=
               *(args[2].datatype_)) {
      o.string_val_ = "Third argument to hmput() must be a valid value "
                      "matching with Array[MEntry[K,V]]";
    } else {
      return o;
    }
    o.object_type_ = object_type::RUNTIME_ERROR;
    return o;
  }
  bool should_compile_argument(int arg_index, expr *arg_expression) override {
    return true;
  }
  std::pair<std::string, ykobject>
  compile(const std::vector<std::pair<std::string, ykobject>> &args,
          const std::vector<expr *> &arg_expressions,
          datatype_compiler *dt_compiler, datatype_parser *dt_parser,
          ykdt_pool *dt_pool,
          const std::unordered_map<std::string, import_stmt *> &import_aliases,
          const std::string &filepath) override {
    auto o = ykobject(dt_pool);
    std::stringstream code{};
    code << "yk__hmput(" << args[0].first << ", " << args[1].first << ", "
         << args[2].first << ")";
    return {code.str(), o};
  }
};
//
// ┌─┐ ┌─┐┌─┐┬─┐┌┬┐
// │─┼┐└─┐│ │├┬┘ │
// └─┘└└─┘└─┘┴└─ ┴
//
struct builtin_qsort : builtin {
  ykobject
  verify(const std::vector<ykobject> &args,
         const std::vector<expr *> &arg_expressions, datatype_parser *dt_parser,
         ykdt_pool *dt_pool,
         const std::unordered_map<std::string, import_stmt *> &import_aliases,
         const std::string &filepath, slot_matcher *dt_slot_matcher) override {
    auto o = ykobject(dt_pool);
    if (args.size() != 2) {
      o.string_val_ = "Two arguments must be provided for sort() builtin";
    } else if (!args[0].datatype_->is_an_array()) {
      o.string_val_ = "First argument to sort() must be an Array[T]";
    } else if (!(args[1].object_type_ == yaksha::object_type::FUNCTION ||
                 args[1].object_type_ == yaksha::object_type::MODULE_FUNCTION ||
                 args[1].datatype_->is_function())) {
      o.string_val_ = "Second argument to sort() must be a Function";
    } else {
      auto func = dt_pool->create("Function");
      auto func_in = dt_pool->create("In");
      auto func_out = dt_pool->create("Out");
      func->args_.emplace_back(func_in);
      func->args_.emplace_back(func_out);
      func_out->args_.emplace_back(dt_pool->create("int"));
      auto const_arg1 = dt_pool->create("Const");
      const_arg1->args_.emplace_back(dt_pool->create("AnyArg"));
      auto const_arg2 = dt_pool->create("Const");
      const_arg2->args_.emplace_back(dt_pool->create("AnyArg"));
      func_in->args_.emplace_back(const_arg1);
      func_in->args_.emplace_back(const_arg2);
      // func -> Function[In[Const[AnyArg],Const[AnyArg]],Out[int]]
      if (dt_slot_matcher->slot_match(args[1], func)) {
        return ykobject(dt_pool->create("bool"));
      } else {
        o.string_val_ = "Comparison must match with "
                        "Function[In[Const[AnyArg],Const[AnyArg]],Out[int]]";
      }
    }
    o.object_type_ = object_type::RUNTIME_ERROR;
    return o;
  }
  bool should_compile_argument(int arg_index, expr *arg_expression) override {
    return true;
  }
  std::pair<std::string, ykobject>
  compile(const std::vector<std::pair<std::string, ykobject>> &args,
          const std::vector<expr *> &arg_expressions,
          datatype_compiler *dt_compiler, datatype_parser *dt_parser,
          ykdt_pool *dt_pool,
          const std::unordered_map<std::string, import_stmt *> &import_aliases,
          const std::string &filepath) override {
    auto o = ykobject(dt_pool);
    std::stringstream code{};
    o = ykobject(args[0].second.datatype_->args_[0]);
    code << "(yk__quicksort(" << args[0].first << ",sizeof("
         << dt_compiler->convert_dt(args[0].second.datatype_->args_[0]) << ")"
         << ",yk__arrlenu(" << args[0].first << ")," << args[1].first << ") == 0)";
    return {code.str(), o};
  }
};
//=======================================
builtins::builtins(ykdt_pool *dt_pool) : dt_pool_{dt_pool}, builtins_{} {
  builtins_.insert({"arrput", new builtin_arrput{}});
  builtins_.insert({"arrpop", new builtin_arrpop{}});
  builtins_.insert({"print", new builtin_print{}});
  builtins_.insert({"println", new builtin_println{}});
  builtins_.insert({"len", new builtin_len{}});
  builtins_.insert({"charat", new builtin_charat{}});
  builtins_.insert({"getref", new builtin_getref{}});
  builtins_.insert({"unref", new builtin_unref{}});
  builtins_.insert({"shnew", new builtin_shnew{}});
  builtins_.insert({"shget", new builtin_shget{}});
  builtins_.insert({"shgeti", new builtin_shgeti{}});
  builtins_.insert({"shput", new builtin_shput{}});
  builtins_.insert({"cast", new builtin_cast{}});
  builtins_.insert({"hmnew", new builtin_hmnew{}});
  builtins_.insert({"hmget", new builtin_hmget{}});
  builtins_.insert({"hmgeti", new builtin_hmgeti{}});
  builtins_.insert({"hmput", new builtin_hmput{}});
  builtins_.insert({"qsort", new builtin_qsort{}});
}
builtins::~builtins() {
  for (auto &i : builtins_) { delete i.second; }
  builtins_.clear();
};
bool builtins::has_builtin(const std::string &name) {
  return builtins_.find(name) != builtins_.end();
}
ykobject builtins::verify(
    const std::string &name, const std::vector<ykobject> &args,
    const std::vector<expr *> &arg_expressions,
    const std::unordered_map<std::string, import_stmt *> &import_aliases,
    const std::string &filepath, slot_matcher *dt_slot_matcher) {
  return builtins_[name]->verify(args, arg_expressions, this, dt_pool_,
                                 import_aliases, filepath, dt_slot_matcher);
}
std::pair<std::string, ykobject> builtins::compile(
    const std::string &name,
    const std::vector<std::pair<std::string, ykobject>> &args,
    const std::vector<expr *> &arg_expressions, datatype_compiler *dt_compiler,
    const std::unordered_map<std::string, import_stmt *> &import_aliases,
    const std::string &filepath) {
  return builtins_[name]->compile(args, arg_expressions, dt_compiler, this,
                                  dt_pool_, import_aliases, filepath);
}
bool builtins::should_compile_argument(const std::string &name, int arg_index,
                                       expr *arg_expression) {
  return builtins_[name]->should_compile_argument(arg_index, arg_expression);
}
ykdatatype *builtins::parse(
    std::string data_type_str,
    const std::unordered_map<std::string, import_stmt *> &import_aliases,
    const std::string &filepath) {
  auto t = tokenizer{filepath, std::move(data_type_str)};
  t.tokenize();
  if (!t.errors_.empty()) { return nullptr; }
  auto p = parser{filepath, t.tokens_, dt_pool_};
  p.import_stmts_alias_ = import_aliases;
  ykdatatype *dt;
  try {
    dt = p.parse_datatype();
  } catch (parsing_error &ignored) { return nullptr; }
  if (!p.errors_.empty()) { return nullptr; }
  p.rescan_datatypes();
  return dt;
}
