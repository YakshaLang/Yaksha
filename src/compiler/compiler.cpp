// compiler.cpp
#include "compiler.h"
using namespace yaksha;
compiler::compiler(def_class_visitor &defs_classes, ykdt_pool *pool)
    : defs_classes_(defs_classes), scope_(pool), dt_pool(pool),
      builtins_(pool) {
  forward_declarations_ << "#include \"yk__lib.h\"\n";
  forward_declarations_ << "// --forward declaration section-- \n";
  body_ << "// --body section-- \n";
  for (const auto &name : defs_classes.class_names_) {
    forward_declarations_ << "struct " << name << ";\n";
  }
};
compiler::~compiler() = default;
void compiler::visit_assign_expr(assign_expr *obj) {
  obj->right_->accept(this);
  auto name = prefix(obj->name_->token_);
  auto rhs = pop();
  write_indent(body_);
  if (rhs.second.is_primitive_or_obj() && rhs.second.datatype_->is_str()) {
    // free current value.
    body_ << "yk__sdsfree(" << name << ")";
    write_end_statement(body_);
    // duplicate the input.
    // do assignment of the duplicate
    write_indent(body_);
    body_ << name << " = yk__sdsdup(" << rhs.first << ")";
  } else {
    body_ << name << " = " << rhs.first;
  }
  write_end_statement(body_);
}
void compiler::visit_binary_expr(binary_expr *obj) {
  // Vist left side of the binary expression and right side.
  // This should give us the data types from the 2 stacks we maintain.
  obj->left_->accept(this);
  auto lhs = pop();
  obj->right_->accept(this);
  auto rhs = pop();
  // Note: we are assuming data type to be same as first,
  // Since this will be type checked using type_checker.
  auto data_type = lhs.second;
  if (data_type.is_primitive_or_obj() && data_type.datatype_->is_str()) {
    if (obj->opr_->type_ == token_type::EQ_EQ) {
      push("(yk__sdscmp(" + lhs.first + " , " + rhs.first + ") == 0)",
           data_type);
    } else if (obj->opr_->type_ == token_type::NOT_EQ) {
      push("(yk__sdscmp(" + lhs.first + " , " + rhs.first + ") != 0)",
           data_type);
    } else {// String concat using + operator
      // new temp needs to be created
      auto temporary_string = temp();
      // put the temp to the deletions stack
      deletions_.push(temporary_string,
                      "yk__sdsfree(" + temporary_string + ")");
      // duplicate lhs
      // call sdscatsds
      // assign to the temp
      write_indent(body_);
      body_ << "yk__sds " << temporary_string << " = yk__sdscatsds(yk__sdsdup("
            << lhs.first << "), " << rhs.first << ")";
      write_end_statement(body_);
      // push the temp
      push(temporary_string, data_type);
    }
  } else {// Assume it is int
    push("(" + lhs.first + " " + obj->opr_->token_ + " " + rhs.first + ")",
         data_type);
  }
}
void compiler::visit_fncall_expr(fncall_expr *obj) {
  obj->name_->accept(this);
  auto name_pair = pop();
  auto name = name_pair.first;
  std::stringstream code{};
  // Depending on the fact that this is a function or class, we will call or create object
  if (name_pair.second.object_type_ == object_type::BUILTIN_FUNCTION) {
    std::vector<std::pair<std::string, ykobject>> args{};
    for (auto arg : obj->args_) {
      arg->accept(this);
      args.emplace_back(pop());
    }
    auto result = builtins_.compile(name, args);
    push(result.first, result.second);
  } else if (defs_classes_.has_function(name)) {
    // Note: no need to check here as type_checker & def_class_visitor ensure this is present.
    code << name << "(";
    bool first = true;
    for (auto arg : obj->args_) {
      arg->accept(this);
      auto arg_val = pop();
      if (!first) {
        code << ", ";
      } else {
        first = false;
      }
      if (arg_val.second.is_primitive_or_obj() &&
          arg_val.second.datatype_->is_str()) {
        code << "yk__sdsdup(" << arg_val.first << ")";
      } else {
        code << arg_val.first;
      }
    }
    code << ")";
    auto fn_def = defs_classes_.get_function(name);
    auto return_type = fn_def->return_type_;
    if (return_type->is_str()) {
      auto temp_name = temp();
      write_indent(body_);
      body_ << "yk__sds " << temp_name << " = " << code.str();
      write_end_statement(body_);
      deletions_.push(temp_name, "yk__sdsfree(" + temp_name + ")");
      push("(" + temp_name + ")", ykobject(return_type));
    } else {
      push(code.str(), ykobject(return_type));
    }
  } else if (defs_classes_.has_class(name)) {
    code << "calloc(1, sizeof(struct " << name << "))";
    auto data = ykobject(dt_pool->create(name));
    push(code.str(), data);
  }
}
void compiler::visit_grouping_expr(grouping_expr *obj) {
  obj->expression_->accept(this);
  auto exp = pop();
  push("(" + exp.first + ")", exp.second);
}
void compiler::visit_literal_expr(literal_expr *obj) {
  auto data_type_tok = obj->literal_token_->type_;
  if (data_type_tok == token_type::STRING ||
      data_type_tok == token_type::THREE_QUOTE_STRING) {
    // Do nothing for now.
    auto temp_name = temp();
    write_indent(body_);
    body_ << "yk__sds " << temp_name;
    if (obj->literal_token_->token_.empty()) {
      body_ << " = yk__sdsempty()";
    } else {
      body_ << " = yk__sdsnew(\"" << obj->literal_token_->token_ << "\")";
    }
    write_end_statement(body_);
    deletions_.push(temp_name, "yk__sdsfree(" + temp_name + ")");
    push(temp_name, ykobject(std::string{"str"},
                             dt_pool));// Note: dummy value for ykobject
  } else {                             // Assume this is int for now
    // TODO support for other data types
    push(obj->literal_token_->token_,
         ykobject(0, dt_pool));// Note dummy value for ykobject
  }
}
void compiler::visit_logical_expr(logical_expr *obj) {
  obj->left_->accept(this);
  auto lhs = pop();
  obj->right_->accept(this);
  auto rhs = pop();
  std::string operator_token;
  if (obj->opr_->type_ == token_type::KEYWORD_AND) {
    operator_token = " && ";
  } else {
    operator_token = " || ";
  }
  // Note: dummy value is placed inside ykobject
  push("(" + lhs.first + operator_token + rhs.first + ")",
       ykobject(true, dt_pool));
}
void compiler::visit_unary_expr(unary_expr *obj) {
  // Note: this is not supported by strings only numbers/floats
  // Type checker should find an error if we use unary with a string.
  obj->right_->accept(this);
  auto rhs = pop();
  std::string operator_token = obj->opr_->token_;
  if (obj->opr_->type_ == token_type::KEYWORD_NOT) { operator_token = "!"; }
  push("(" + operator_token + " (" + rhs.first + "))", rhs.second);
}
void compiler::visit_variable_expr(variable_expr *obj) {
  // Compiler is visiting a variable, can get data type from scope_
  auto name = prefix(obj->name_->token_);
  if (builtins::has_builtin(name)) {
    auto b = ykobject(dt_pool);
    b.object_type_ = object_type::BUILTIN_FUNCTION;
    push(name, b);
    return;
  }
  auto object = scope_.get(name);
  push(name, object);
}
void compiler::visit_block_stmt(block_stmt *obj) {
  // block will be compiled to '{' + statements + '}'
  body_ << "\n";
  write_prev_indent(body_);
  body_ << "{\n";
  for (auto st : obj->statements_) { st->accept(this); }
  // Clean out what we create inside while scope or if scope blocks
  // For defs, deletion happen before return
  if (peek_scope_type() == ast_type::STMT_WHILE ||
      peek_scope_type() == ast_type::STMT_IF) {
    defers_.write_one(this);
    deletions_.write_one(body_, indent_);
  }
  write_prev_indent(body_);
  body_ << "}\n";
}
void compiler::visit_break_stmt(break_stmt *obj) {
  write_indent(body_);
  body_ << "break";
  write_end_statement(body_);
}
void compiler::visit_continue_stmt(continue_stmt *obj) {
  write_indent(body_);
  body_ << "continue";
  write_end_statement(body_);
}
void compiler::visit_def_stmt(def_stmt *obj) {
  auto name = prefix(obj->name_->token_);
  bool first = false;
  // ::================================::
  // Compile @nativemacro if present
  // ::================================::
  if (obj->annotations_.native_macro_) {
    forward_declarations_ << "#define " << name << "(";
    first = true;
    for (auto para : obj->params_) {
      if (!first) {
        forward_declarations_ << ", ";
      } else {
        first = false;
      }
      forward_declarations_ << prefix(para.name_->token_);
    }
    forward_declarations_ << ") ";
    if (obj->annotations_.native_macro_arg_.empty()) {
      // #define yy__name ccode..
      auto b = dynamic_cast<block_stmt *>(obj->function_body_);
      auto st = b->statements_[0];
      auto stn = dynamic_cast<ccode_stmt *>(st);
      forward_declarations_ << ::string_utils::unescape(stn->code_str_->token_);
    } else {
      // #define yy__name arg
      forward_declarations_ << obj->annotations_.native_macro_arg_;
    }
    forward_declarations_ << "\n";
    return;
  }
  // ::================================::
  // Create declaration in header section
  // ::================================::
  auto return_type = convert_dt(obj->return_type_);
  forward_declarations_ << return_type << " " << name << "(";
  first = true;
  for (auto para : obj->params_) {
    if (!first) {
      forward_declarations_ << ", ";
    } else {
      first = false;
    }
    forward_declarations_ << convert_dt(para.data_type_);
  }
  forward_declarations_ << ")";
  write_end_statement(forward_declarations_);
  // ::================================::
  // Create first part of method body
  //       datatype name (..params..)
  // ::================================::
  body_ << return_type << " " << name << "(";
  first = true;
  for (auto para : obj->params_) {
    if (!first) {
      body_ << ", ";
    } else {
      first = false;
    }
    body_ << convert_dt(para.data_type_) << " " << prefix(para.name_->token_);
  }
  body_ << ") ";
  // ::================================::
  // Create @native code
  // ::================================::
  if (obj->annotations_.native_ && !obj->annotations_.native_arg_.empty()) {
    body_ << "{ ";
    if (!obj->return_type_->is_none()) { body_ << "return "; }
    body_ << obj->annotations_.native_arg_ << "(";
    first = true;
    for (auto para : obj->params_) {
      if (!first) {
        body_ << ", ";
      } else {
        first = false;
      }
      body_ << prefix(para.name_->token_);
    }
    body_ << "); }\n";
    return;
  }
  // ::================================::
  // Create code body
  // ::================================::
  // Define parameters in nested scope for function
  ykobject func_placeholder{dt_pool};
  func_placeholder.object_type_ = object_type::FUNCTION;
  scope_.define_global(name, func_placeholder);
  scope_.push();
  auto function_def = defs_classes_.get_function(name);
  for (auto param : function_def->params_) {
    auto placeholder = ykobject(param.data_type_);
    scope_.define(prefix(param.name_->token_), placeholder);
  }
  indent();
  // ::================================::
  // Visit function body
  //       {
  //            ..
  //       }
  // ::================================::
  push_scope_type(ast_type::STMT_DEF);
  deletions_.push_delete_stack();
  defers_.push_defer_stack();
  // Schedule string argument deletions.
  for (auto param : function_def->params_) {
    if (param.data_type_->is_str()) {
      auto to_delete = prefix(param.name_->token_);
      deletions_.push(to_delete, "yk__sdsfree(" + to_delete + ")");
    }
  }
  obj->function_body_->accept(this);
  defers_.pop_defer_stack();
  deletions_.pop_delete_stack();
  dedent();
  scope_.pop();
  pop_scope_type();
}
void compiler::visit_expression_stmt(expression_stmt *obj) {
  obj->expression_->accept(this);
  if (expr_stack_.empty()) { return; }
  auto exp = pop();
  write_indent(body_);
  body_ << exp.first;
  write_end_statement(body_);
}
void compiler::visit_if_stmt(if_stmt *obj) {
  // if () -> block
  obj->expression_->accept(this);
  auto if_expr = pop();
  write_indent(body_);
  body_ << "if (" << if_expr.first << ")";
  scope_.push();
  deletions_.push_delete_stack();
  defers_.push_defer_stack();
  push_scope_type(ast_type::STMT_IF);
  indent();
  obj->if_branch_->accept(this);
  dedent();
  pop_scope_type();
  defers_.pop_defer_stack();
  deletions_.pop_delete_stack();
  scope_.pop();
  if (obj->else_branch_ != nullptr) {
    write_indent(body_);
    body_ << "else";
    scope_.push();
    deletions_.push_delete_stack();
    defers_.push_defer_stack();
    push_scope_type(ast_type::STMT_IF);
    indent();
    obj->else_branch_->accept(this);
    dedent();
    pop_scope_type();
    defers_.pop_defer_stack();
    deletions_.pop_delete_stack();
    scope_.pop();
  }
}
void compiler::visit_let_stmt(let_stmt *obj) {
  auto name = prefix(obj->name_->token_);
  auto object = ykobject(dt_pool);
  if (obj->data_type_->is_str()) {
    object = ykobject(std::string("str"), dt_pool);
    if (obj->expression_ != nullptr) {
      obj->expression_->accept(this);
      auto exp = pop();
      write_indent(body_);
      body_ << "yk__sds " << name << " = "
            << "yk__sdsdup(" << exp.first << ")";
    } else {
      write_indent(body_);
      body_ << "yk__sds " << name << " = "
            << "yk__sdsempty()";
    }
    // If there is an expression, go to that, pop(), duplicate and assign.
    // If there is not an expression, assign yk__sdsempty()
    // Add to deletions
    deletions_.push(name, "yk__sdsfree(" + name + ")");
  } else if (obj->data_type_->is_an_array()) {
    write_indent(body_);
    object = ykobject(obj->data_type_);
    body_ << convert_dt(obj->data_type_) << " " << name;
    if (obj->expression_ != nullptr) {
      obj->expression_->accept(this);
      auto exp = pop();
      body_ << " = " << exp.first;
    } else {
      body_ << " = NULL";
    }
  } else {
    write_indent(body_);
    object = ykobject(obj->data_type_);
    body_ << convert_dt(obj->data_type_) << " " << name;
    if (obj->expression_ != nullptr) {
      obj->expression_->accept(this);
      auto exp = pop();
      body_ << " = " << exp.first;
    }
  }
  write_end_statement(body_);
  scope_.define(name, object);
}
void compiler::visit_pass_stmt(pass_stmt *obj) {
  write_indent(body_);
  body_ << "// pass";
  write_end_statement(body_);
}
void compiler::visit_print_stmt(print_stmt *obj) {
  obj->expression_->accept(this);
  auto rhs = pop();
  // TODO check in type checker since we only support printing primitives
  if (rhs.second.is_primitive_or_obj() && rhs.second.datatype_->is_int()) {
    write_indent(body_);
    body_ << "printf(\"%d\", (" << rhs.first << "))";
    write_end_statement(body_);
  } else if (rhs.second.is_primitive_or_obj() &&
             rhs.second.datatype_->is_str()) {
    // TODO do not assume it's all ascii, and works fine :p
    write_indent(body_);
    body_ << "printf(\"%s\", (" << rhs.first << "))";
    write_end_statement(body_);
  }
}
void compiler::visit_return_stmt(return_stmt *obj) {
  if (obj->expression_ != nullptr) {
    obj->expression_->accept(this);
    auto rhs = pop();
    defers_.write_one(this);
    deletions_.write(body_, indent_, rhs.first);
    write_indent(body_);
    body_ << "return " << rhs.first;
    write_end_statement(body_);
  } else {
    defers_.write_one(this);
    deletions_.write(body_, indent_, "");
    write_indent(body_);
    body_ << "return";
    write_end_statement(body_);
  }
}
void compiler::visit_while_stmt(while_stmt *obj) {
  //  while (1) {
  //    if (!((yy__a > 0))) { break; } // expression
  //    { // block
  //    }
  //  }
  write_indent(body_);
  body_ << "while (1) {\n";
  obj->expression_->accept(this);
  auto code = pop();
  push_scope_type(ast_type::STMT_WHILE);
  scope_.push();
  deletions_.push_delete_stack();
  defers_.push_defer_stack();
  indent();
  indent();
  write_prev_indent(body_);
  // TODO if we allocate memory expression we need to free it.
  // TODO Extra string objects need to be freed here.
  body_ << "if (!(" << code.first << ")) { break; } // Check\n";
  write_prev_indent(body_);
  body_ << "// Body of while loop\n";
  obj->while_body_->accept(this);
  dedent();
  dedent();
  write_indent(body_);
  body_ << "}\n";
  pop_scope_type();
  scope_.pop();
  defers_.pop_defer_stack();
  deletions_.pop_delete_stack();
}
void compiler::write_indent(std::stringstream &where) const {
  ::write_indent(where, indent_);
}
void compiler::write_end_statement(std::stringstream &where) { where << ";\n"; }
void compiler::indent() { indent_++; }
void compiler::dedent() {
  if (indent_ == 0) { return; }
  indent_--;
}
std::string compiler::temp() {
  // temp names will start with t__, so they will look like t__0, t__1, ...
  std::string name = "t__";
  name += std::to_string(temp_);
  temp_++;
  return name;
}
std::string compiler::convert_dt(ykdatatype *basic_dt) {
  if (basic_dt->is_an_array()) {
    // int32_t*, yk__sds*, etc
    return convert_dt(basic_dt->args_[0]) + "*";
  }
  auto dt = basic_dt->token_->token_;
  if (defs_classes_.has_class(dt)) { return "struct " + dt + "*"; }
  if (basic_dt->is_str()) {
    return "yk__sds";
  } else if (basic_dt->is_i8()) {
    return "int8_t";
  } else if (basic_dt->is_i16()) {
    return "int16_t";
  } else if (basic_dt->is_int() || basic_dt->is_i32()) {
    return "int32_t";
  } else if (basic_dt->is_i64()) {
    return "int64_t";
  } else if (basic_dt->is_u8()) {
    return "uint8_t";
  } else if (basic_dt->is_u16()) {
    return "uint16_t";
  } else if (basic_dt->is_u32()) {
    return "uint32_t";
  } else if (basic_dt->is_u64()) {
    return "uint64_t";
  } else if (basic_dt->is_bool()) {
    return "bool";
  }
  return "void";
}
std::string compiler::compile(const std::vector<stmt *> &statements) {
  for (auto st : statements) { st->accept(this); }
  std::stringstream code{};
  code << forward_declarations_.str();
  code << body_.str();
  // Need to call yy__main from `C` main.
  // TODO Handle arguments
  code << "int main(void) { return yy__main(); }";
  return code.str();
}
void compiler::push(const std::string &expr, const ykobject &data_type) {
  expr_stack_.push_back(expr);
  type_stack_.push_back(data_type);
}
std::pair<std::string, ykobject> compiler::pop() {
  auto p = std::make_pair(expr_stack_.back(), type_stack_.back());
  expr_stack_.pop_back();
  type_stack_.pop_back();
  return p;
}
void compiler::write_prev_indent(std::stringstream &where) const {
  auto indent = indent_ - 1;
  ::write_indent(where, indent);
}
void compiler::push_scope_type(ast_type scope_type) {
  this->scope_type_stack_.emplace_back(scope_type);
}
ast_type compiler::peek_scope_type() {
  if (this->scope_type_stack_.empty()) {
    return ast_type::STMT_PASS;// Pass is used for unknown
  }
  return this->scope_type_stack_.back();
}
void compiler::pop_scope_type() {
  if (this->scope_type_stack_.empty()) { return; }
  this->scope_type_stack_.pop_back();
}
void compiler::visit_defer_stmt(defer_stmt *obj) { defers_.push(obj); }
void compiler::visit_class_stmt(class_stmt *obj) {
  /**
   *    struct foo {
   *       int abc;
   *    };
   */
  auto name = prefix(obj->name_->token_);
  write_indent(body_);
  body_ << "struct " << name << " {\n";
  indent();
  //
  for (auto member : obj->members_) {
    write_indent(body_);
    auto member_name = prefix(member.name_->token_);
    auto dt = convert_dt(member.data_type_);
    body_ << dt << " " << member_name;
    write_end_statement(body_);
  }
  //
  dedent();
  write_indent(body_);
  body_ << "}";
  write_end_statement(body_);
}
void compiler::visit_del_stmt(del_stmt *obj) {
  obj->expression_->accept(this);
  auto name = pop();
  if (name.second.is_primitive_or_obj() &&
      name.second.datatype_->is_primitive() &&
      !name.second.datatype_->is_str()) {
    return;
  }
  write_indent(body_);
  if (name.second.datatype_->is_an_array()) {
    body_ << "yk__arrfree(" << name.first << ")";
  } else if (name.second.is_primitive_or_obj() &&
             name.second.datatype_->is_str()) {
    body_ << "yk__sdsfree(" << name.first << ")";
  } else {
    body_ << "free(" << name.first << ")";
  }
  write_end_statement(body_);
}
void compiler::visit_get_expr(get_expr *obj) {
  obj->lhs_->accept(this);
  auto lhs = pop();
  auto item = prefix(obj->item_->token_);
  auto user_defined_type = lhs.second.datatype_->type_;
  auto class_ = defs_classes_.get_class(user_defined_type);
  for (const auto &member : class_->members_) {
    if (item == prefix(member.name_->token_)) {
      auto placeholder = ykobject(dt_pool);
      placeholder.datatype_ = member.data_type_;
      push(lhs.first + "->" + item, placeholder);
      return;
    }
  }
}
void compiler::visit_set_expr(set_expr *obj) {
  obj->lhs_->accept(this);
  auto lhs = pop();
  auto item = prefix(obj->item_->token_);
  auto user_defined_type = lhs.second.datatype_->type_;
  auto class_ = defs_classes_.get_class(user_defined_type);
  for (const auto &member : class_->members_) {
    if (item == prefix(member.name_->token_)) {
      auto placeholder = ykobject(dt_pool);
      placeholder.datatype_ = member.data_type_;
      push(lhs.first + "->" + item, placeholder);
      return;
    }
  }
}
void compiler::visit_assign_member_expr(assign_member_expr *obj) {
  obj->set_oper_->accept(this);// before  a.b, after a->b
  auto lhs = pop();
  obj->right_->accept(this);
  auto rhs = pop();
  write_indent(body_);
  if (rhs.second.is_primitive_or_obj() && rhs.second.datatype_->is_str()) {
    // free current value.
    body_ << "yk__sdsfree(" << lhs.first << ")";
    write_end_statement(body_);
    // duplicate the input.
    // do assignment of the duplicate
    write_indent(body_);
    body_ << lhs.first << " = yk__sdsdup(" << rhs.first << ")";
  } else {
    body_ << lhs.first << " = " << rhs.first;
  }
  write_end_statement(body_);
}
void compiler::visit_square_bracket_access_expr(
    square_bracket_access_expr *obj) {
  obj->name_->accept(this);
  auto lhs = pop();
  obj->index_expr_->accept(this);
  auto rhs = pop();
  auto b = ykobject(lhs.second.datatype_->args_[0]);
  push(lhs.first + "[" + rhs.first + "]", b);
}
void compiler::visit_square_bracket_set_expr(square_bracket_set_expr *obj) {
  obj->name_->accept(this);
  auto lhs = pop();
  obj->index_expr_->accept(this);
  auto rhs = pop();
  auto b = ykobject(lhs.second.datatype_->args_[0]);
  push(lhs.first + "[" + rhs.first + "]", b);
}
void compiler::visit_assign_arr_expr(assign_arr_expr *obj) {
  obj->assign_oper_->accept(this);
  auto lhs = pop();
  obj->right_->accept(this);
  auto rhs = pop();
  write_indent(body_);
  if (rhs.second.is_primitive_or_obj() && rhs.second.datatype_->is_str()) {
    // free current value.
    body_ << "yk__sdsfree(" << lhs.first << ")";
    write_end_statement(body_);
    // duplicate the input.
    // do assignment of the duplicate
    write_indent(body_);
    body_ << lhs.first << " = yk__sdsdup(" << rhs.first << ")";
  } else {
    body_ << lhs.first << " = " << rhs.first;
  }
  write_end_statement(body_);
}
void compiler::visit_ccode_stmt(ccode_stmt *obj) {
  write_indent(body_);
  body_ << ::string_utils::unescape(obj->code_str_->token_);
  write_end_statement(body_);
}
