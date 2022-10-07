// compiler.cpp
#include "compiler.h"
#include "ast/parser.h"
#include <cinttypes>
using namespace yaksha;
compiler::compiler(def_class_visitor &defs_classes, ykdt_pool *pool,
                   entry_struct_func_compiler *esc)
    : defs_classes_(defs_classes), scope_(pool), dt_pool(pool), builtins_(pool),
      esc_(esc) {
  ast_pool_ = new ast_pool();
}
compiler::~compiler() { delete ast_pool_; }
void compiler::visit_assign_expr(assign_expr *obj) {
  obj->right_->accept(this);
  auto name = prefix(obj->name_->token_, prefix_val_);
  auto rhs = pop();
  token_type operator_type = obj->opr_->type_;
  write_indent(body_);
  if (rhs.second.is_primitive_or_obj() && rhs.second.datatype_->is_str() &&
      operator_type == token_type::EQ) {
    // -- str =
    // free current value.
    body_ << "yk__sdsfree(" << name << ")";
    write_end_statement(body_);
    // duplicate the input.
    // do assignment of the duplicate
    write_indent(body_);
    body_ << name << " = yk__sdsdup(" << rhs.first << ")";
  } else if (rhs.second.is_primitive_or_obj() &&
             rhs.second.datatype_->is_str() &&
             operator_type == token_type::PLUS_EQ) {
    // -- str +=
    body_ << name << " = yk__sdscatsds(" << name << ", " << rhs.first << ")";
  } else if (rhs.second.is_a_function()) {
    body_ << name << " = " << prefix_function_arg(rhs);
  } else if (rhs.second.is_primitive_or_obj() &&
             operator_type == token_type::MOD_EQ &&
             rhs.second.datatype_->is_f32()) {
    // f32 %=
    body_ << name << " = "
          << "remainderf(" << name + ", " + rhs.first + ")";
  } else if (rhs.second.is_primitive_or_obj() &&
             operator_type == token_type::MOD_EQ &&
             rhs.second.datatype_->is_f64()) {
    // f64 %=
    body_ << name << " = "
          << "remainder(" << name + ", " + rhs.first + ")";
  } else {// usual case
    body_ << name << " " << obj->opr_->token_ << " " << rhs.first;
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
  token_type operator_type = obj->opr_->type_;
  auto data_type = lhs.second;
  if (lhs.second.datatype_->is_none() || rhs.second.datatype_->is_none()) {
    // both null
    if (lhs.second.datatype_->is_none() && rhs.second.datatype_->is_none()) {
      if (operator_type == token_type::EQ_EQ) {
        push("true", ykobject(dt_pool->create("bool")));// None == None -> True
      } else {
        push("false",
             ykobject(dt_pool->create("bool")));// None != None -> False
      }
    } else if (lhs.second.datatype_->is_none()) {
      push("(NULL " + obj->opr_->token_ + " " + rhs.first + ")", ykobject(dt_pool->create("bool")));
    } else {
      push("(" + lhs.first + " " + obj->opr_->token_ + " NULL)", ykobject(dt_pool->create("bool")));
    }
  } else if (data_type.is_primitive_or_obj() && data_type.datatype_->is_str()) {
    if (obj->opr_->type_ == token_type::EQ_EQ) {
      push("(yk__sdscmp(" + lhs.first + " , " + rhs.first + ") == 0)",
           ykobject(dt_pool->create("bool")));
    } else if (obj->opr_->type_ == token_type::NOT_EQ) {
      push("(yk__sdscmp(" + lhs.first + " , " + rhs.first + ") != 0)",
           ykobject(dt_pool->create("bool")));
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
  } else if (data_type.is_primitive_or_obj() && data_type.datatype_->is_f32() &&
             obj->opr_->type_ == token_type::MOD) {// Float %
    push("remainderf(" + lhs.first + ", " + rhs.first + ")", data_type);
  } else if (data_type.is_primitive_or_obj() && data_type.datatype_->is_f64() &&
             obj->opr_->type_ == token_type::MOD) {// Double %
    push("remainder(" + lhs.first + ", " + rhs.first + ")", data_type);
  } else if (operator_type == token_type::LESS ||
             operator_type == token_type::LESS_EQ ||
             operator_type == token_type::GREAT ||
             operator_type == token_type::GREAT_EQ ||
             operator_type == token_type::NOT_EQ ||
             operator_type == token_type::EQ_EQ) {
    push("(" + lhs.first + " " + obj->opr_->token_ + " " + rhs.first + ")",
         ykobject(dt_pool->create("bool")));
  } else {// Other number stuff
    push("(" + lhs.first + " " + obj->opr_->token_ + " " + rhs.first + ")",
         data_type);
  }
  // Note: type checker prevents compiler coming here with non integer data types
}
void compiler::visit_fncall_expr(fncall_expr *obj) {
  obj->name_->accept(this);
  auto name_pair = pop();
  auto name = name_pair.first;
  std::stringstream code{};
  // Depending on the fact that this is a function or class, we will call or create object
  if (name_pair.second.object_type_ == object_type::BUILTIN_FUNCTION) {
    std::vector<std::pair<std::string, ykobject>> args{};
    int i = 0;
    for (auto arg : obj->args_) {
      if (builtins_.should_compile_argument(name, i, arg)) {
        arg->accept(this);
        auto val = pop();
        if (val.second.is_a_function()) {
          args.emplace_back(std::pair<std::string, ykobject>{
              prefix_function_arg(val), val.second});
        } else {
          args.emplace_back(val);
        }
      } else {
        args.emplace_back(
            std::pair<std::string, ykobject>{"", ykobject(dt_pool)});
      }
      i++;
    }
    auto result = builtins_.compile(name, args, obj->args_, this,
                                    import_stmts_alias_, filepath_, this, this);
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
  } else if (name_pair.second.datatype_->is_function()) {
    auto ret_type = name_pair.second.datatype_->args_[1];
    ykdatatype *return_type;
    if (ret_type->args_.empty()) {
      return_type = dt_pool->create("None");
    } else {
      return_type = ret_type->args_[0];
    }
    compile_function_call(obj, prefix(name, prefix_val_), code, return_type);
  } else {
    // TODO Generate an error here and push it to compiler time error
    std::cerr << "<><>";
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
    } else if (arg_val.second.is_a_function()) {
      code << prefix_function_arg(arg_val);
      ;
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
std::string
compiler::prefix_function_arg(const std::pair<std::string, ykobject> &arg_val) {
  if (arg_val.second.object_type_ == object_type::MODULE_FUNCTION) {
    auto module_file = arg_val.second.module_file_;
    auto module_fn = arg_val.second.string_val_;
    auto module_info = cf_->get(module_file);
    auto module_prefix = module_info->prefix_;
    return prefix(module_fn, module_prefix);
  } else {
    return prefix(arg_val.first, prefix_val_);
  }
}
void compiler::visit_grouping_expr(grouping_expr *obj) {
  obj->expression_->accept(this);
  auto exp = pop();
  if (exp.second.is_a_function()) {
    push("(" + prefix_function_arg(exp) + ")", exp.second);
  } else {
    push("(" + exp.first + ")", exp.second);
  }
}
std::string conv_integer_literal(token_type token_type_val,
                                 std::string &integer_value) {
  switch (token_type_val) {
    case token_type::INTEGER_DECIMAL:
    case token_type::INTEGER_HEX:
    case token_type::INTEGER_DECIMAL_8:
    case token_type::INTEGER_HEX_8:
    case token_type::INTEGER_DECIMAL_16:
    case token_type::INTEGER_HEX_16:
    case token_type::INTEGER_DECIMAL_64:
    case token_type::INTEGER_HEX_64:
    case token_type::UINTEGER_DECIMAL:
    case token_type::UINTEGER_HEX:
    case token_type::UINTEGER_DECIMAL_8:
    case token_type::UINTEGER_HEX_8:
    case token_type::UINTEGER_DECIMAL_16:
    case token_type::UINTEGER_HEX_16:
    case token_type::UINTEGER_DECIMAL_64:
    case token_type::UINTEGER_HEX_64:
      return integer_value;// no need to modify
    case token_type::INTEGER_BIN:
    case token_type::INTEGER_BIN_8:
    case token_type::INTEGER_BIN_16:
    case token_type::INTEGER_BIN_64: {
      std::string part = integer_value.substr(2);
      std::intmax_t number = std::strtoimax(part.c_str(), nullptr, 2);
      return std::to_string(number);
    }
    case token_type::UINTEGER_BIN:
    case token_type::UINTEGER_BIN_8:
    case token_type::UINTEGER_BIN_16:
    case token_type::UINTEGER_BIN_64: {
      std::string part = integer_value.substr(2);
      std::uintmax_t number = std::strtoumax(part.c_str(), nullptr, 2);
      return std::to_string(number);
    }
    case token_type::INTEGER_OCT:
    case token_type::INTEGER_OCT_8:
    case token_type::INTEGER_OCT_16:
    case token_type::INTEGER_OCT_64: {
      std::string part = integer_value.substr(2);
      std::intmax_t number = std::strtoimax(part.c_str(), nullptr, 8);
      return std::to_string(number);
    }
    case token_type::UINTEGER_OCT:
    case token_type::UINTEGER_OCT_8:
    case token_type::UINTEGER_OCT_16:
    case token_type::UINTEGER_OCT_64: {
      std::string part = integer_value.substr(2);
      std::uintmax_t number = std::strtoumax(part.c_str(), nullptr, 8);
      return std::to_string(number);
    }
    default:
      // Cannot happen
      return "<><>";
  }
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
    push("NULL", ykobject(dt_pool));
  } else if (data_type_tok == token_type::INTEGER_BIN ||
             data_type_tok == token_type::INTEGER_DECIMAL ||
             data_type_tok == token_type::INTEGER_OCT ||
             data_type_tok == token_type::INTEGER_HEX) {
    push("INT32_C(" +
             conv_integer_literal(data_type_tok, obj->literal_token_->token_) +
             ")",
         ykobject(dt_pool->create("int")));
  } else if (data_type_tok == token_type::INTEGER_BIN_8 ||
             data_type_tok == token_type::INTEGER_DECIMAL_8 ||
             data_type_tok == token_type::INTEGER_OCT_8 ||
             data_type_tok == token_type::INTEGER_HEX_8) {
    push("INT8_C(" +
             conv_integer_literal(data_type_tok, obj->literal_token_->token_) +
             ")",
         ykobject(dt_pool->create("i8")));
  } else if (data_type_tok == token_type::INTEGER_BIN_16 ||
             data_type_tok == token_type::INTEGER_DECIMAL_16 ||
             data_type_tok == token_type::INTEGER_OCT_16 ||
             data_type_tok == token_type::INTEGER_HEX_16) {
    push("INT16_C(" +
             conv_integer_literal(data_type_tok, obj->literal_token_->token_) +
             ")",
         ykobject(dt_pool->create("i16")));
  } else if (data_type_tok == token_type::INTEGER_BIN_64 ||
             data_type_tok == token_type::INTEGER_DECIMAL_64 ||
             data_type_tok == token_type::INTEGER_OCT_64 ||
             data_type_tok == token_type::INTEGER_HEX_64) {
    push("INT64_C(" +
             conv_integer_literal(data_type_tok, obj->literal_token_->token_) +
             ")",
         ykobject(dt_pool->create("i64")));
  } else if (data_type_tok == token_type::UINTEGER_BIN ||
             data_type_tok == token_type::UINTEGER_DECIMAL ||
             data_type_tok == token_type::UINTEGER_OCT ||
             data_type_tok == token_type::UINTEGER_HEX) {
    push("UINT32_C(" +
             conv_integer_literal(data_type_tok, obj->literal_token_->token_) +
             ")",
         ykobject(dt_pool->create("u32")));
  } else if (data_type_tok == token_type::UINTEGER_BIN_8 ||
             data_type_tok == token_type::UINTEGER_DECIMAL_8 ||
             data_type_tok == token_type::UINTEGER_OCT_8 ||
             data_type_tok == token_type::UINTEGER_HEX_8) {
    push("UINT8_C(" +
             conv_integer_literal(data_type_tok, obj->literal_token_->token_) +
             ")",
         ykobject(dt_pool->create("i8")));
  } else if (data_type_tok == token_type::UINTEGER_BIN_16 ||
             data_type_tok == token_type::UINTEGER_DECIMAL_16 ||
             data_type_tok == token_type::UINTEGER_OCT_16 ||
             data_type_tok == token_type::UINTEGER_HEX_16) {
    push("UINT16_C(" +
             conv_integer_literal(data_type_tok, obj->literal_token_->token_) +
             ")",
         ykobject(dt_pool->create("i16")));
  } else if (data_type_tok == token_type::UINTEGER_BIN_64 ||
             data_type_tok == token_type::UINTEGER_DECIMAL_64 ||
             data_type_tok == token_type::UINTEGER_OCT_64 ||
             data_type_tok == token_type::UINTEGER_HEX_64) {
    push("UINT64_C(" +
             conv_integer_literal(data_type_tok, obj->literal_token_->token_) +
             ")",
         ykobject(dt_pool->create("i64")));
  } else if (data_type_tok == token_type::FLOAT_NUMBER) {
    push(obj->literal_token_->token_, ykobject(dt_pool->create("float")));
  } else if (data_type_tok == token_type::DOUBLE_NUMBER) {
    push(obj->literal_token_->token_, ykobject(dt_pool->create("f64")));
  } else {
    push("<><>", ykobject(dt_pool));
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
  if (builtins_.has_builtin(obj->name_->token_)) {
    auto b = ykobject(dt_pool);
    b.object_type_ = object_type::BUILTIN_FUNCTION;
    push(obj->name_->token_, b);
    return;
  } else if (defs_classes_.has_function(obj->name_->token_)) {
    auto b = ykobject(dt_pool);
    b.object_type_ = object_type::FUNCTION;
    b.string_val_ = obj->name_->token_;
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
  defers_.write_upto_loop(this);
  deletions_.write_upto_loop(body_, indent_);
  write_indent(body_);
  body_ << "break";
  write_end_statement(body_);
}
void compiler::visit_continue_stmt(continue_stmt *obj) {
  defers_.write_upto_loop(this);
  deletions_.write_upto_loop(body_, indent_);
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
  deletions_.push_delete_stack(ast_type::STMT_DEF);
  defers_.push_defer_stack(ast_type::STMT_DEF);
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
  deletions_.push_delete_stack(ast_type::STMT_IF);
  defers_.push_defer_stack(ast_type::STMT_IF);
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
    deletions_.push_delete_stack(ast_type::STMT_IF);
    defers_.push_defer_stack(ast_type::STMT_IF);
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
      if (exp.second.is_a_function()) {
        body_ << " = " << prefix_function_arg(exp);
      } else {
        body_ << " = " << exp.first;
      }
    } else {
      write_indent(body_);
      body_ << convert_dt(obj->data_type_) << " " << name;
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
    std::string return_val = rhs.first;
    // Literals are safe to return as it is
    if (obj->expression_->get_type() != ast_type::EXPR_LITERAL) {
      // First we assign return value to a temp variable
      std::string temp_name = temp();
      write_indent(body_);
      body_ << convert_dt(rhs.second.datatype_) << " " << temp_name << " = "
            << rhs.first;
      write_end_statement(body_);
      return_val = temp_name;
    }
    // Do the deletions, defers
    defers_.write(this);
    deletions_.write(body_, indent_, rhs.first);
    // Now we return the temp value
    write_indent(body_);
    body_ << "return " << return_val;
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
  deletions_.push_delete_stack(ast_type::STMT_WHILE);
  defers_.push_defer_stack(ast_type::STMT_WHILE);
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
  if (basic_dt->is_an_array() || basic_dt->is_a_pointer()) {
    // int32_t*, yk__sds*, etc
    return convert_dt(basic_dt->args_[0]) + "*";
  } else if (basic_dt->is_const()) {
    return convert_dt(basic_dt->args_[0]) + " const ";
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
  } else if (basic_dt->is_float() || basic_dt->is_f32()) {
    return "float";
  } else if (basic_dt->is_f64()) {
    return "double";
  } else if (basic_dt->is_any_ptr()) {
    return "void*";
  } else if (basic_dt->is_any_ptr_to_const()) {
    return "void const*";
  } else if (basic_dt->is_sm_entry() || basic_dt->is_m_entry()) {
    // Handle SMEntry and Entry
    return esc_->compile(basic_dt, this);
  } else if (basic_dt->is_function()) {
    return esc_->compile_function_dt(basic_dt, this);
  } else if (basic_dt->is_tuple()) {
    return esc_->compile_tuple(basic_dt, this);
  }
  auto dt = basic_dt->token_->token_;
  if (!basic_dt->module_.empty() && cf_ != nullptr) {
    auto module = cf_->get(basic_dt->module_);
    auto imported_module_prefix = module->prefix_;
    auto class_info = module->data_->dsv_->get_class(dt);
    if (class_info != nullptr) {
      auto class_name = prefix(dt, imported_module_prefix);
      if (class_info->annotations_.native_define_) { return class_name; }
      return "struct " + class_name + "*";
    }
  }
  if (defs_classes_.has_class(dt)) {
    auto class_info = defs_classes_.get_class(dt);
    auto class_name = prefix(dt, prefix_val_);
    if (class_info->annotations_.native_define_) { return class_name; }
    return "struct " + class_name + "*";
  }
  return "<data type unknown>";
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
  // Create a copy of import information
  import_stmts_alias_ = fi->data_->parser_->import_stmts_alias_;
  filepath_ = fi->filepath_.string();
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
    if (name.second.datatype_->args_[0]->is_sm_entry()) {
      body_ << "yk__shfree(" << name.first << ")";
    } else if (name.second.datatype_->args_[0]->is_m_entry()) {
      body_ << "yk__hmfree(" << name.first << ")";
    } else {
      body_ << "yk__arrfree(" << name.first << ")";
    }
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
      auto module_info = cf_->get(mod_obj.module_file_);
      auto prefixed_name = prefix(mod_obj.string_val_, module_info->prefix_);
      push(prefixed_name, mod_obj);
      return;
    }
    // TODO generate a compiler error if this happens
    push("<><>", mod_obj);
    return;
  }
  auto item = obj->item_->token_;
  auto user_defined_type = lhs.second.datatype_->type_;
  auto module_file = lhs.second.datatype_->module_;
  class_stmt *class_;
  std::string item_prefix = prefix_val_;
  std::string access_ = "->";
  if (module_file.empty()) {
    class_ = defs_classes_.get_class(user_defined_type);
  } else {
    file_info *module_info = cf_->get(module_file);
    class_ = module_info->data_->dsv_->get_class(user_defined_type);
    item_prefix = module_info->prefix_;
  }
  if (class_->annotations_.native_define_) { item_prefix = ""; }
  if (class_->annotations_.dot_access_) { access_ = "."; }
  for (const auto &member : class_->members_) {
    if (item == member.name_->token_) {
      auto placeholder = ykobject(dt_pool);
      placeholder.datatype_ = member.data_type_;
      push(lhs.first + access_ + prefix(item, item_prefix), placeholder);
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
  std::string access_ = "->";
  if (module_file.empty()) {
    class_ = defs_classes_.get_class(user_defined_type);
  } else {
    file_info *module_info = cf_->get(module_file);
    class_ = module_info->data_->dsv_->get_class(user_defined_type);
    item_prefix = module_info->prefix_;
  }
  if (class_->annotations_.native_define_) { item_prefix = ""; }
  if (class_->annotations_.dot_access_) { access_ = "."; }
  for (const auto &member : class_->members_) {
    if (item == member.name_->token_) {
      auto placeholder = ykobject(dt_pool);
      placeholder.datatype_ = member.data_type_;
      push(lhs.first + access_ + prefix(item, item_prefix), placeholder);
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
  obj->index_expr_->accept(this);
  auto rhs = pop();
  obj->name_->accept(this);
  auto lhs = pop();
  if (lhs.second.datatype_->is_an_array()) {
    auto b = ykobject(lhs.second.datatype_->args_[0]);
    push(lhs.first + "[" + rhs.first + "]", b);
  } else if (lhs.second.datatype_->is_tuple()) {
    auto int_expr = dynamic_cast<literal_expr *>(obj->index_expr_);
    auto index = std::stoi(int_expr->literal_token_->token_);
    auto b = ykobject(lhs.second.datatype_->args_[index]);
    push(lhs.first + ".e" + int_expr->literal_token_->token_, b);
  } else {
    // TODO Generate a comp time error if this happens
    push("<><>", ykobject(dt_pool));
  }
}
void compiler::visit_square_bracket_set_expr(square_bracket_set_expr *obj) {
  obj->index_expr_->accept(this);
  auto rhs = pop();
  obj->name_->accept(this);
  auto lhs = pop();
  if (lhs.second.datatype_->is_an_array()) {
    auto b = ykobject(lhs.second.datatype_->args_[0]);
    push(lhs.first + "[" + rhs.first + "]", b);
  } else if (lhs.second.datatype_->is_tuple()) {
    auto int_expr = dynamic_cast<literal_expr *>(obj->index_expr_);
    auto index = std::stoi(int_expr->literal_token_->token_);
    auto b = ykobject(lhs.second.datatype_->args_[index]);
    push(lhs.first + ".e" + int_expr->literal_token_->token_, b);
  } else {
    // TODO generate a comp time error if this happens
    push("<><>", ykobject(dt_pool));
  }
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
    literal_expression->accept(this);
    auto exp = pop();
    global_constants_ << this->convert_dt(obj->data_type_) << " " << name
                      << " = " << exp.first;
    write_end_statement(global_constants_);
  } else {// Compile as you would compile a let statement
    auto let_stmt_obj =
        ast_pool_->c_let_stmt(obj->name_, obj->data_type_, obj->expression_);
    let_stmt_obj->accept(this);
  }
}
void compiler::write_statement(std::string code_line) {
  write_indent(body_);
  body_ << code_line;
  write_end_statement(body_);
}
void compiler::write_statement_no_end(std::string code_line) {
  write_indent(body_);
  body_ << code_line << "\n";
}
void compiler::visit_runtimefeature_stmt(runtimefeature_stmt *obj) {}
ykdatatype *compiler::function_to_datatype(const ykobject &arg) {
  def_stmt *funct;
  if (arg.object_type_ == object_type::FUNCTION) {
    funct = defs_classes_.get_function(arg.string_val_);
  } else {
    auto imp = cf_->get(arg.module_file_);
    funct = imp->data_->dsv_->get_function(arg.string_val_);
  }
  if (funct->annotations_.varargs_) { return nullptr; }
  if (funct->annotations_.native_macro_ || funct->annotations_.native_define_) {
    return nullptr;
  }
  // Create datatype out of function
  ykdatatype *fnc = dt_pool->create("Function");
  ykdatatype *fin = dt_pool->create("In");
  ykdatatype *fout = dt_pool->create("Out");
  fnc->args_.emplace_back(fin);
  fnc->args_.emplace_back(fout);
  for (auto current_param : funct->params_) {
    fin->args_.emplace_back(current_param.data_type_);
  }
  if (!funct->return_type_->is_none()) {
    fout->args_.emplace_back(funct->return_type_);
  }
  // Compare now
  return fnc;
}
