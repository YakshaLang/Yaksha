// builtins.cpp
#include "compiler/builtins.h"
#include "ast/parser.h"
#include "tokenizer/tokenizer.h"
#include <sstream>
#include <utility>
using namespace yaksha;
builtins::builtins(ykdt_pool *dt_pool) : dt_pool_(dt_pool) {}
builtins::~builtins() = default;
bool builtins::has_builtin(const std::string &name) {
  if (name == "arrput") { return true; }
  if (name == "arrpop") { return true; }
  if (name == "print") { return true; }
  if (name == "println") { return true; }
  if (name == "len") { return true; }
  if (name == "charat") { return true; }
  if (name == "getref") { return true; }
  if (name == "unref") { return true; }
  if (name == "shnew") { return true; }
  if (name == "shput") { return true; }
  if (name == "shget") { return true; }
  if (name == "shgeti") { return true; }
  if (name == "cast") { return true; }
  return false;
}
ykobject builtins::verify(
    const std::string &name, const std::vector<ykobject> &args,
    const std::vector<expr *> &arg_expressions,
    const std::unordered_map<std::string, import_stmt *> &import_aliases,
    const std::string &filepath) {
  auto o = ykobject(dt_pool_);
  if (name == "arrput" && args.size() == 2 &&
      args[0].datatype_->is_an_array() &&
      *(args[0].datatype_->args_[0]) == *args[1].datatype_) {
    // verify arrput(Array[T], T)
    return o;
  } else if ((name == "print" || name == "println") && args.size() == 1 &&
             args[0].is_primitive_or_obj() &&
             args[0].datatype_->is_primitive()) {
    return o;
  } else if (name == "len" && args.size() == 1 &&
             (args[0].datatype_->is_an_array() ||
              args[0].datatype_->is_str())) {
    // verify len(Array[?])
    return ykobject(dt_pool_->create("int"));
  } else if (name == "arrpop" && args.size() == 1 &&
             args[0].datatype_->is_an_array()) {
    // arrpop(Array[T]) -> returns T
    return ykobject(args[0].datatype_->args_[0]);
  } else if (name == "charat" && args.size() == 2 &&
             args[0].datatype_->is_str() &&
             args[1].datatype_->is_an_integer()) {
    return ykobject(dt_pool_->create("int"));
  } else if (name == "getref" && args.size() == 1) {
    ykdatatype *dt = dt_pool_->create("Ptr");
    dt->args_.emplace_back(args[0].datatype_);
    return ykobject(dt);
  } else if (name == "unref" && args.size() == 1 &&
             args[0].datatype_->is_a_pointer()) {
    // Ptr[x] << access this x
    return ykobject(args[0].datatype_->args_[0]);
  } else if (name == "shnew" && args.size() == 1 &&
             args[0].datatype_->is_an_array() &&
             args[0].datatype_->args_[0]->is_sm_entry()) {
    // shnew(Array[SMEntry[T]])
    // Create a new string hash
    return o;// None returned
  } else if (name == "shget" && args.size() == 2 &&
             args[0].datatype_->is_an_array() &&
             args[0].datatype_->args_[0]->is_sm_entry() &&
             args[1].datatype_->is_str()) {
    // shget(Array[SMEntry[T]], str) -> T
    return ykobject(args[0].datatype_->args_[0]->args_[0]);
  } else if (name == "shgeti" && args.size() == 2 &&
             args[0].datatype_->is_an_array() &&
             args[0].datatype_->args_[0]->is_sm_entry() &&
             args[1].datatype_->is_str()) {
    // shgeti(Array[SMEntry[T]], str) -> int
    return ykobject(dt_pool_->create("int"));
  } else if (name == "shput" && args.size() == 3 &&
             args[0].datatype_->is_an_array() &&
             args[0].datatype_->args_[0]->is_sm_entry() &&
             args[1].datatype_->is_str() &&
             (*args[2].datatype_ == *args[0].datatype_->args_[0]->args_[0])) {
    // shput(Array[SMEntry[T]], str, T) -> None
    return o;
  } else if (name == "cast" && args.size() == 2 &&
             args[0].datatype_->is_str() &&
             arg_expressions[0]->get_type() == ast_type::EXPR_LITERAL) {
    // cast(str !! literal only, any)
    auto *lit = dynamic_cast<literal_expr *>(arg_expressions[0]);
    if (lit->literal_token_->type_ == token_type::STRING ||
        lit->literal_token_->type_ == token_type::THREE_QUOTE_STRING) {
      auto data_type = lit->literal_token_->token_;
      ykdatatype *parsed_dt = parse(data_type, import_aliases, filepath);
      if (parsed_dt != nullptr) { return ykobject(parsed_dt); }
    }
  }
  o.object_type_ = object_type::RUNTIME_ERROR;
  o.string_val_ = "Invalid arguments for builtin function";
  return o;
}
std::pair<std::string, ykobject> builtins::compile(
    const std::string &name,
    const std::vector<std::pair<std::string, ykobject>> &args,
    const std::vector<expr *> &arg_expressions, datatype_compiler *dt_compiler,
    const std::unordered_map<std::string, import_stmt *> &import_aliases,
    const std::string &filepath) {
  std::stringstream code{};
  auto o = ykobject(dt_pool_);
  if (name == "arrput") {
    if (args[1].second.datatype_->is_str()) {
      code << "yk__arrput(" << args[0].first << ", yk__sdsdup(" << args[1].first
           << "))";
    } else {
      code << "yk__arrput(" << args[0].first << ", " << args[1].first << ")";
    }
  } else if (name == "print") {
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
  } else if (name == "println") {
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
  } else if (name == "len") {
    if (args[0].second.datatype_->is_str()) {
      code << "yk__sdslen(" << args[0].first << ")";
    } else if (args[0].second.datatype_->is_an_array() &&
               args[0].second.datatype_->args_[0]->is_sm_entry()) {
      // Array[SMEntry[?]]
      code << "yk__shlen(" << args[0].first << ")";
    } else {
      code << "yk__arrlen(" << args[0].first << ")";
    }
    o = ykobject(dt_pool_->create("int"));
  } else if (name == "arrpop") {
    o = ykobject(args[0].second.datatype_->args_[0]);
    code << "yk__arrpop(" << args[0].first << ")";
  } else if (name == "charat") {
    code << "(" << args[0].first << "[" << args[1].first << "])";
    o = ykobject(dt_pool_->create("int"));
  } else if (name == "getref") {
    code << "(&(" << args[0].first << "))";
    ykdatatype *dt = dt_pool_->create("Ptr");
    dt->args_.emplace_back(args[0].second.datatype_);
    o = ykobject(dt);
  } else if (name == "unref") {
    code << "(*(" << args[0].first << "))";
    o = ykobject(args[0].second.datatype_->args_[0]);
  } else if (name == "shnew") {
    code << "yk__sh_new_strdup(" << args[0].first << ")";
  } else if (name == "shget") {
    code << "yk__shget(" << args[0].first << ", " << args[1].first << ")";
    o = ykobject(args[0].second.datatype_->args_[0]->args_[0]);
  } else if (name == "shgeti") {
    code << "yk__shgeti(" << args[0].first << ", " << args[1].first << ")";
    o = ykobject(dt_pool_->create("int"));
  } else if (name == "shput") {
    code << "yk__shput(" << args[0].first << ", " << args[1].first << ", "
         << args[2].first << ")";
  } else if (name == "cast") {
    auto dt = dynamic_cast<literal_expr *>(arg_expressions[0]);
    auto out_dt = parse(dt->literal_token_->token_, import_aliases, filepath);
    code << "((" << dt_compiler->convert_dt(out_dt) << ")" << args[1].first
         << ")";
    o = ykobject(out_dt);
  }
  return {code.str(), o};
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
  } catch (parsing_error &ignored) {
    return nullptr;
  }
  if (!p.errors_.empty()) {
    return nullptr;
  }
  p.rescan_datatypes();
  return dt;
}
bool builtins::should_compile_argument(const std::string &name, int arg_index) {
  if (name == "cast" && arg_index == 0) { return false; }
  return true;
}
