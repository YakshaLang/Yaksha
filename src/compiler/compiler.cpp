// compiler.cpp
#include "compiler.h"
#include "ast/parser.h"
using namespace yaksha;
compiler::compiler(def_class_visitor &defs_classes, ykdt_pool *pool)
    : defs_classes_(defs_classes), scope_(pool), dt_pool(pool),
      builtins_(pool) {
  ast_pool_ = new ast_pool();
}
compiler::~compiler() { delete ast_pool_; }
void compiler::visit_assign_expr(assign_expr *obj) {
  obj->right_->accept(this);
  auto name = prefix(obj->name_->token_, prefix_val_);
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
  } else if (name_pair.second.object_type_ == object_type::MODULE_CLASS) {
    auto module_file = name_pair.second.module_file_;
    auto module_class = name_pair.second.string_val_;
    auto module_prefix = cf_->get(module_file)->prefix_;
    auto prefixed_class_name = prefix(module_class, module_prefix);
    compile_obj_creation(prefixed_class_name, code,
                         dt_pool->create(module_class, module_file));
  } else if (name_pair.second.object_type_ == object_type::MODULE_FUNCTION) {
    auto module_file = name_pair.second.module_file_;
    auto module_fn = name_pair.second.string_val_;
    auto module_info = cf_->get(module_file);
    auto module_prefix = module_info->prefix_;
    auto prefixed_fn_name = prefix(module_fn, module_prefix);
    auto fn_return =
        module_info->data_->dsv_->get_function(module_fn)->return_type_;
    compile_function_call(obj, prefixed_fn_name, code, fn_return);
  } else if (defs_classes_.has_function(name)) {
    auto fn_def = defs_classes_.get_function(name);
    auto return_type = fn_def->return_type_;
    compile_function_call(obj, prefix(name, prefix_val_), code, return_type);
  } else if (defs_classes_.has_class(name)) {
    compile_obj_creation(prefix(name, prefix_val_), code,
                         dt_pool->create(name));
  } else {
    std::cerr << "\n// Oh no!\n";
  }
}
void compiler::compile_obj_creation(const std::string &name,
                                    std::stringstream &code,
                                    ykdatatype *return_type) {
  code << "calloc(1, sizeof(struct " << name << "))";
  auto data = ykobject(return_type);
  push(code.str(), data);
}
void compiler::compile_function_call(fncall_expr *obj, const std::string &name,
                                     std::stringstream &code,
                                     ykdatatype *return_type) {
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
      body_ << " = yk__sdsnew(\""
            << string_utils::escape(
                   string_utils::unescape(obj->literal_token_->token_))
            << "\")";
    }
    write_end_statement(body_);
    deletions_.push(temp_name, "yk__sdsfree(" + temp_name + ")");
    push(temp_name, ykobject(std::string{"str"},
                             dt_pool));// Note: dummy value for ykobject
  } else if (obj->literal_token_->type_ == token_type::KEYWORD_TRUE) {
    push("true", ykobject(dt_pool->create("bool")));
  } else if (obj->literal_token_->type_ == token_type::KEYWORD_FALSE) {
    push("false", ykobject(dt_pool->create("bool")));
  } else if (obj->literal_token_->type_ == token_type::KEYWORD_NONE) {
    push("NULL", ykobject());
  } else {// Assume this is int for now
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
  auto name = prefix(obj->name_->token_, prefix_val_);
  if (builtins::has_builtin(obj->name_->token_)) {
    auto b = ykobject(dt_pool);
    b.object_type_ = object_type::BUILTIN_FUNCTION;
    push(obj->name_->token_, b);
    return;
  } else if (defs_classes_.has_function(obj->name_->token_)) {
    auto b = ykobject(dt_pool);
    b.object_type_ = object_type::FUNCTION;
    push(obj->name_->token_, b);
    return;
  } else if (defs_classes_.has_class(obj->name_->token_)) {
    auto b = ykobject(dt_pool);
    b.object_type_ = object_type::CLASS_ITSELF;
    push(obj->name_->token_, b);
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
  auto name = prefix(obj->name_->token_, prefix_val_);
  if (obj->annotations_.native_define_) {
    struct_forward_declarations_ << "#define " << name << " "
                                 << obj->annotations_.native_define_arg_
                                 << "\n";
    return;
  }
  bool first = false;
  // ::================================::
  // Compile @nativemacro if present
  // ::================================::
  if (obj->annotations_.native_macro_) {
    struct_forward_declarations_ << "#define " << name << "(";
    first = true;
    for (auto para : obj->params_) {
      if (!first) {
        struct_forward_declarations_ << ", ";
      } else {
        first = false;
      }
      struct_forward_declarations_ << prefix(para.name_->token_, "nn__");
    }
    struct_forward_declarations_ << ") ";
    if (obj->annotations_.native_macro_arg_.empty()) {
      // #define yy__name ccode..
      auto b = dynamic_cast<block_stmt *>(obj->function_body_);
      auto st = b->statements_[0];
      auto stn = dynamic_cast<ccode_stmt *>(st);
      struct_forward_declarations_
          << ::string_utils::unescape(stn->code_str_->token_);
    } else {
      // #define yy__name arg
      struct_forward_declarations_ << obj->annotations_.native_macro_arg_;
    }
    struct_forward_declarations_ << "\n";
    return;
  }
  // ::================================::
  // Create declaration in header section
  // ::================================::
  auto return_type = convert_dt(obj->return_type_);
  function_forward_declarations_ << return_type << " " << name << "(";
  first = true;
  for (auto para : obj->params_) {
    if (!first) {
      function_forward_declarations_ << ", ";
    } else {
      first = false;
    }
    function_forward_declarations_ << convert_dt(para.data_type_);
  }
  function_forward_declarations_ << ")";
  write_end_statement(function_forward_declarations_);
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
    body_ << convert_dt(para.data_type_) << " "
          << prefix(para.name_->token_,
                    obj->annotations_.native_ ? "nn__" : prefix_val_);
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
      body_ << prefix(para.name_->token_, "nn__");
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
  auto function_def = obj;
  for (auto param : function_def->params_) {
    auto placeholder = ykobject(param.data_type_);
    scope_.define(prefix(param.name_->token_, prefix_val_), placeholder);
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
      auto to_delete = prefix(param.name_->token_, prefix_val_);
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
  auto name = prefix(obj->name_->token_, prefix_val_);
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
    object = ykobject(obj->data_type_);
    if (obj->expression_ != nullptr) {
      obj->expression_->accept(this);
      auto exp = pop();
      write_indent(body_);
      body_ << convert_dt(obj->data_type_) << " " << name;
      body_ << " = " << exp.first;
    } else {
      write_indent(body_);
      body_ << convert_dt(obj->data_type_) << " " << name;
      body_ << " = NULL";
    }
  } else {
    object = ykobject(obj->data_type_);
    if (obj->expression_ != nullptr) {
      obj->expression_->accept(this);
      auto exp = pop();
      write_indent(body_);
      body_ << convert_dt(obj->data_type_) << " " << name;
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
void compiler::visit_return_stmt(return_stmt *obj) {
  if (obj->expression_ != nullptr) {
    obj->expression_->accept(this);
    auto rhs = pop();
    defers_.write(this);
    deletions_.write(body_, indent_, rhs.first);
    write_indent(body_);
    body_ << "return " << rhs.first;
    write_end_statement(body_);
  } else {
    defers_.write(this);
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
  } else if (basic_dt->is_const()) {
    return "const " + convert_dt(basic_dt->args_[0]);
  } else if (basic_dt->is_str()) {
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
  } else if (basic_dt->is_none()) {
    return "void";
  }
  auto dt = basic_dt->token_->token_;
  if (!basic_dt->module_.empty() && cf_ != nullptr) {
    auto module = cf_->get(basic_dt->module_);
    auto imported_module_prefix = module->prefix_;
    auto class_info = module->data_->dsv_->get_class(dt);
    auto class_name = prefix(dt, imported_module_prefix);
    if (class_info->annotations_.native_define_) { return class_name; }
    return "struct " + class_name + "*";
  }
  if (defs_classes_.has_class(dt)) {
    auto class_info = defs_classes_.get_class(dt);
    auto class_name = prefix(dt, prefix_val_);
    if (class_info->annotations_.native_define_) { return class_name; }
    return "struct " + class_name + "*";
  }
  return "void";
}
compiler_output compiler::compile(const std::vector<stmt *> &statements) {
  for (const auto &name : this->defs_classes_.class_names_) {
    auto cls = defs_classes_.get_class(name);
    if (!cls->annotations_.native_define_) {
      struct_forward_declarations_ << "struct " << prefix(name, prefix_val_)
                                   << ";\n";
    }
  }
  for (auto st : statements) { st->accept(this); }
  return {struct_forward_declarations_.str(),
          function_forward_declarations_.str(), classes_.str(), body_.str(),
          global_constants_.str()};
}
compiler_output compiler::compile(codefiles *cf, file_info *fi) {
  this->cf_ = cf;
  this->prefix_val_ = fi->prefix_;
  for (const auto &name : this->defs_classes_.class_names_) {
    auto cls = defs_classes_.get_class(name);
    if (!cls->annotations_.native_define_) {
      struct_forward_declarations_ << "struct " << prefix(name, prefix_val_)
                                   << ";\n";
    }
  }
  for (auto imp_st : fi->data_->parser_->import_stmts_) {
    auto obj = ykobject(dt_pool);
    obj.object_type_ = yaksha::object_type::MODULE;
    obj.string_val_ = imp_st->data_->filepath_.string();
    obj.module_file_ = imp_st->data_->filepath_.string();
    obj.module_name_ = imp_st->name_->token_;
    scope_.define_global(prefix(imp_st->name_->token_, prefix_val_), obj);
  }
  for (auto st : fi->data_->parser_->stmts_) { st->accept(this); }
  return {struct_forward_declarations_.str(),
          function_forward_declarations_.str(), classes_.str(), body_.str(),
          global_constants_.str()};
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
  auto name = prefix(obj->name_->token_, prefix_val_);
  if (obj->annotations_.native_define_) {
    struct_forward_declarations_ << "#define " << name << " "
                                 << obj->annotations_.native_define_arg_
                                 << "\n";
    return;
  }
  write_indent(classes_);
  classes_ << "struct " << name << " {\n";
  indent();
  //
  for (auto member : obj->members_) {
    write_indent(classes_);
    auto member_name = prefix(member.name_->token_, prefix_val_);
    auto dt = convert_dt(member.data_type_);
    classes_ << dt << " " << member_name;
    write_end_statement(classes_);
  }
  //
  dedent();
  write_indent(classes_);
  classes_ << "}";
  write_end_statement(classes_);
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
  if (lhs.second.object_type_ == object_type::MODULE) {
    auto member_item = obj->item_;
    auto imported = cf_->get(lhs.second.string_val_);
    bool has_func = imported->data_->dsv_->has_function(member_item->token_);
    bool has_class = imported->data_->dsv_->has_class(member_item->token_);
    bool has_const = imported->data_->dsv_->has_const(member_item->token_);
    auto mod_obj = ykobject(dt_pool);
    if (has_class) {
      mod_obj.object_type_ = object_type::MODULE_CLASS;
      /* for jungle.Banana */
      mod_obj.string_val_ = member_item->token_;      /* Banana */
      mod_obj.module_file_ = lhs.second.string_val_;  /* file path */
      mod_obj.module_name_ = lhs.second.module_name_; /* jungle */
    } else if (has_func) {
      mod_obj.object_type_ = object_type::MODULE_FUNCTION;
      mod_obj.string_val_ = member_item->token_;
      mod_obj.module_file_ = lhs.second.string_val_;
      mod_obj.module_name_ = lhs.second.module_name_;
    } else if (has_const) {
      auto glob = imported->data_->dsv_->get_const(member_item->token_);
      mod_obj.object_type_ = object_type::PRIMITIVE_OR_OBJ;
      mod_obj.datatype_ = glob->data_type_;
      mod_obj.string_val_ = member_item->token_;
      mod_obj.module_file_ = lhs.second.string_val_;
      mod_obj.module_name_ = lhs.second.module_name_;
      auto prefixed_name = prefix(mod_obj.string_val_, prefix(mod_obj.module_name_, "yy__") + "_");
      push(prefixed_name, mod_obj);
      return;
    }
    push("<>", mod_obj);
    return;
  }
  auto item = obj->item_->token_;
  auto user_defined_type = lhs.second.datatype_->type_;
  auto module_file = lhs.second.datatype_->module_;
  class_stmt *class_;
  std::string item_prefix = prefix_val_;
  if (module_file.empty()) {
    class_ = defs_classes_.get_class(user_defined_type);
  } else {
    file_info *module_info = cf_->get(module_file);
    class_ = module_info->data_->dsv_->get_class(user_defined_type);
    item_prefix = module_info->prefix_;
  }
  if (class_->annotations_.native_define_) { item_prefix = ""; }
  for (const auto &member : class_->members_) {
    if (item == member.name_->token_) {
      auto placeholder = ykobject(dt_pool);
      placeholder.datatype_ = member.data_type_;
      push(lhs.first + "->" + prefix(item, item_prefix), placeholder);
      return;
    }
  }
}
void compiler::visit_set_expr(set_expr *obj) {
  obj->lhs_->accept(this);
  auto lhs = pop();
  auto item = obj->item_->token_;
  auto user_defined_type = lhs.second.datatype_->type_;
  auto module_file = lhs.second.datatype_->module_;
  class_stmt *class_;
  std::string item_prefix = prefix_val_;
  if (module_file.empty()) {
    class_ = defs_classes_.get_class(user_defined_type);
  } else {
    file_info *module_info = cf_->get(module_file);
    class_ = module_info->data_->dsv_->get_class(user_defined_type);
    item_prefix = module_info->prefix_;
  }
  for (const auto &member : class_->members_) {
    if (item == member.name_->token_) {
      auto placeholder = ykobject(dt_pool);
      placeholder.datatype_ = member.data_type_;
      push(lhs.first + "->" + prefix(item, item_prefix), placeholder);
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
void compiler::visit_import_stmt(import_stmt *obj) {}
void compiler::visit_const_stmt(const_stmt *obj) {
  if (scope_.is_global_level()) {// constant is global
    auto name = prefix(obj->name_->token_, prefix_val_);
    auto *literal_expression = dynamic_cast<literal_expr *>(obj->expression_);
    global_constants_ << this->convert_dt(obj->data_type_) << " " << name
                      << " = " << literal_expression->literal_token_->token_;
    write_end_statement(global_constants_);
  } else {// Compile as you would compile a let statement
    auto let_stmt_obj =
        ast_pool_->c_let_stmt(obj->name_, obj->data_type_, obj->expression_);
    let_stmt_obj->accept(this);
  }
}
