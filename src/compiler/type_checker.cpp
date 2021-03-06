// type_checker.cpp
#include "type_checker.h"
#include "compiler_utils.h"
#include "utilities/ykfunction.h"
#include <utility>
using namespace yaksha;
type_checker::type_checker(std::string filepath, codefiles *cf,
                           def_class_visitor *dcv, ykdt_pool *pool)
    : cf_(cf), dt_pool_(pool), scope_(pool), builtins_(pool),
      defs_classes_(dcv), filepath_(std::move(filepath)) {}
type_checker::~type_checker() = default;
void type_checker::visit_assign_expr(assign_expr *obj) {
  obj->right_->accept(this);
  auto rhs = pop();
  auto name = obj->name_->token_;
  if (!scope_.is_defined(name)) {
    error(obj->name_, "This is not defined");
    return;
  }
  auto object = scope_.get(name);
  handle_assigns(obj->opr_, object, rhs);
}
void type_checker::visit_binary_expr(binary_expr *obj) {
  auto oper = obj->opr_->type_;
  obj->left_->accept(this);
  auto lhs = pop();
  obj->right_->accept(this);
  auto rhs = pop();
  if (lhs.object_type_ != rhs.object_type_) {
    error(
        obj->opr_,
        "Binary operation between two different data types are not supported");
  }
  if ((oper == token_type::PLUS) &&
      !(rhs.is_primitive_or_obj() && rhs.datatype_->support_plus())) {
    error(obj->opr_, "Unsupported operation");
  }
  if ((oper == token_type::SUB || oper == token_type::MUL ||
       oper == token_type::DIV || oper == token_type::GREAT ||
       oper == token_type::GREAT_EQ || oper == token_type::LESS ||
       oper == token_type::LESS_EQ) &&
      (!rhs.is_primitive_or_obj() || !rhs.datatype_->is_a_number())) {
    error(obj->opr_, "Unsupported operation");
  }
  if (oper == token_type::EQ_EQ || oper == token_type::NOT_EQ ||
      oper == token_type::LESS_EQ || oper == token_type::GREAT_EQ ||
      oper == token_type::LESS || oper == token_type::GREAT) {
    push(ykobject(true, dt_pool_));
  } else {
    push(rhs);
  }
}
void type_checker::visit_fncall_expr(fncall_expr *obj) {
  obj->name_->accept(this);
  auto name = pop();
  if (name.object_type_ == object_type::CLASS_ITSELF ||
      name.object_type_ == object_type::MODULE_CLASS) {
    auto class_name = name.string_val_;
    ykobject data;
    if (name.object_type_ == object_type::CLASS_ITSELF) {
      data = ykobject(dt_pool_->create(class_name, filepath_));
    } else {
      data = ykobject(dt_pool_->create(name.string_val_, name.module_file_));
    }
    push(data);
    // Creating a custom object from user defined type / class;
    return;
  }
  if (name.object_type_ == object_type::FUNCTION ||
      name.object_type_ == object_type::MODULE_FUNCTION) {
    std::vector<ykobject> arguments{};
    for (auto arg : obj->args_) {
      arg->accept(this);
      arguments.push_back(pop());
    }
    def_stmt *funct;
    if (name.object_type_ == object_type::FUNCTION) {
      funct = defs_classes_->get_function(name.string_val_);
    } else {
      auto imp = cf_->get(name.module_file_);
      funct = imp->data_->dsv_->get_function(name.string_val_);
    }
    // check if it's same size
    if (funct->params_.size() != arguments.size() &&
        !funct->annotations_.varargs_) {
      error(obj->paren_token_, "Too few or too "
                               "much arguments for function call");
      push(ykobject(dt_pool_));// Push None here
      return;
    }
    auto last_param_index = funct->params_.size() - 1;
    for (auto i = 0; i < funct->params_.size(); i++) {
      auto param = funct->params_[i];
      if (i == last_param_index && funct->annotations_.varargs_) {
        for (auto j = i; j < arguments.size(); j++) {
          auto arg = arguments[j];
          if (!(arg.is_primitive_or_obj() &&
                *arg.datatype_ == *param.data_type_)) {
            std::stringstream message{};
            message << "Variable argument: " << (j + 1) << " mismatches";
            error(obj->paren_token_, message.str());
          }
        }
      } else {
        auto arg = arguments[i];
        if (!(arg.is_primitive_or_obj() &&
              *arg.datatype_ == *param.data_type_)) {
          std::stringstream message{};
          message << "Parameter & argument " << (i + 1) << " mismatches";
          error(obj->paren_token_, message.str());
        }
      }
    }
    auto data = ykobject(funct->return_type_);
    push(data);
    return;
  }
  if (name.object_type_ == object_type::BUILTIN_FUNCTION) {
    std::vector<ykobject> arguments{};
    for (auto arg : obj->args_) {
      arg->accept(this);
      arguments.push_back(pop());
    }
    auto result = builtins_.verify(name.string_val_, arguments);
    // Error when calling builtin, if so return None as data type
    if (result.object_type_ == object_type::RUNTIME_ERROR) {
      error(obj->paren_token_, result.string_val_);
      push(ykobject(dt_pool_));// Push None here
      return;
    }
    push(result);
    return;
  }
  error(obj->paren_token_, "Calling a non callable "
                           "or a non existing function");
  push(ykobject(dt_pool_));// Push None here
}
void type_checker::visit_grouping_expr(grouping_expr *obj) {
  obj->expression_->accept(this);
  auto inside = pop();
  push(inside);
}
void type_checker::visit_literal_expr(literal_expr *obj) {
  auto data = ykobject(dt_pool_);
  auto literal_type = obj->literal_token_->type_;
  if (literal_type == token_type::STRING ||
      literal_type == token_type::THREE_QUOTE_STRING) {
    data = ykobject(std::string{"str"}, dt_pool_);
  } else if (literal_type == token_type::KEYWORD_TRUE ||
             literal_type == token_type::KEYWORD_FALSE) {
    data = ykobject(true, dt_pool_);
  } else if (literal_type == token_type::INTEGER_BIN ||
             literal_type == token_type::INTEGER_OCT ||
             literal_type == token_type::INTEGER_DECIMAL ||
             literal_type == token_type::INTEGER_HEX) {
    data = ykobject(1, dt_pool_);
  } else if (literal_type == token_type::FLOAT_NUMBER) {
    data = ykobject(1.2, dt_pool_);
  }// else - none data type by default
  push(data);
}
void type_checker::visit_logical_expr(logical_expr *obj) {
  obj->left_->accept(this);
  auto lhs = pop();
  obj->right_->accept(this);
  auto rhs = pop();
  if (!(lhs.is_primitive_or_obj() && lhs.datatype_->is_bool() &&
        rhs.is_primitive_or_obj() && rhs.datatype_->is_bool())) {
    error(obj->opr_, "Both LHS and RHS of logical"
                     " operator need to be boolean");
  }
  push(rhs);
}
void type_checker::visit_unary_expr(unary_expr *obj) {
  // -5 - correct, -"some string" is not
  obj->right_->accept(this);
  auto rhs = pop();
  if (rhs.is_primitive_or_obj() &&
      (rhs.datatype_->is_a_number() || rhs.datatype_->is_bool())) {
    if (obj->opr_->type_ == token_type::KEYWORD_NOT &&
        !rhs.datatype_->is_bool()) {
      error(obj->opr_,
            "Invalid unary operation. Not operator must follow a boolean.");
    }
  } else {
    error(obj->opr_, "Invalid unary operation");
  }
  push(rhs);
}
void type_checker::visit_variable_expr(variable_expr *obj) {
  auto name = obj->name_->token_;
  if (builtins::has_builtin(name)) {
    auto b = ykobject(dt_pool_);
    b.object_type_ = object_type::BUILTIN_FUNCTION;
    b.string_val_ = name;
    push(b);
    return;
  }
  if (!scope_.is_defined(name)) {
    error(obj->name_, "Undefined name");
    push(ykobject(dt_pool_));
    return;
  }
  auto value = scope_.get(name);
  // Preserve function name so we can access it
  if (value.object_type_ == object_type::FUNCTION ||
      value.object_type_ == object_type::CLASS_ITSELF) {
    value.string_val_ = name;
  }
  push(value);
}
void type_checker::visit_block_stmt(block_stmt *obj) {
  for (auto stm : obj->statements_) { stm->accept(this); }
}
void type_checker::visit_break_stmt(break_stmt *obj) {
  if (peek_scope_type() != ast_type::STMT_WHILE) {
    error(obj->break_token_,
          "Invalid use of break statement outside of while statement.");
  }
}
void type_checker::visit_continue_stmt(continue_stmt *obj) {
  if (peek_scope_type() != ast_type::STMT_WHILE) {
    error(obj->continue_token_, "Invalid use of continue"
                                " statement outside of while statement.");
  }
}
void type_checker::visit_def_stmt(def_stmt *obj) {
  // WHY? This is so I can know I am in a function when I'm in a block statement
  push_scope_type(ast_type::STMT_DEF);
  push_function(obj->name_->token_);
  scope_.push();
  for (auto param : obj->params_) {
    auto name = param.name_->token_;
    if (scope_.is_defined(name)) {
      error(param.name_, "Parameter shadows outer scope name.");
    } else {
      auto data = ykobject(param.data_type_);
      scope_.define(name, data);
    }
  }
  if (obj->annotations_.native_ || obj->annotations_.native_macro_) {
    auto body = dynamic_cast<block_stmt *>(obj->function_body_);
    if (body->statements_.size() != 1) {
      error(obj->name_,
            "@native or @nativemacro function must have only 1 statement");
    } else {
      auto st = body->statements_[0]->get_type();
      if (st != ast_type::STMT_PASS && st != ast_type::STMT_CCODE) {
        error(obj->name_,
              "@native or @nativemacro function must have only 1 statement,"
              " which must be of type ccode or pass.");
      }
      if (obj->annotations_.native_ && st == ast_type::STMT_PASS &&
          obj->annotations_.native_arg_.empty()) {
        error("@native function must have a valid argument if pass is used as "
              "the statement");
      }
      if (obj->annotations_.native_macro_ && st == ast_type::STMT_PASS &&
          obj->annotations_.native_macro_arg_.empty()) {
        error("@nativemacro function must have a valid argument if pass is "
              "used as the statement");
      }
      if (obj->annotations_.native_ && st == ast_type::STMT_CCODE &&
          !obj->annotations_.native_arg_.empty()) {
        error("@native function must not have an argument if ccode is used");
      }
      if (obj->annotations_.native_macro_ && st == ast_type::STMT_CCODE &&
          !obj->annotations_.native_macro_arg_.empty()) {
        error(
            "@nativemacro function must not have an argument if ccode is used");
      }
    }
  } else {
    obj->function_body_->accept(this);
  }
  scope_.pop();
  pop_scope_type();
  pop_function();
}
void type_checker::visit_expression_stmt(expression_stmt *obj) {
  obj->expression_->accept(this);
}
void type_checker::visit_if_stmt(if_stmt *obj) {
  obj->expression_->accept(this);
  auto bool_expression = pop();
  if (!bool_expression.is_primitive_or_obj() ||
      !bool_expression.datatype_->is_bool()) {
    error(obj->if_keyword_, "Invalid boolean expression used");
  }
  scope_.push();
  obj->if_branch_->accept(this);
  scope_.pop();
  if (obj->else_branch_ != nullptr) {
    scope_.push();
    obj->else_branch_->accept(this);
    scope_.pop();
  }
}
void type_checker::visit_let_stmt(let_stmt *obj) {
  auto name = obj->name_->token_;
  auto placeholder = ykobject(obj->data_type_);
  if (obj->expression_ != nullptr) {
    obj->expression_->accept(this);
    auto expression_data = pop();
    if (expression_data.object_type_ != placeholder.object_type_) {
      error(obj->name_, "Data type mismatch in expression and declaration.");
    }
  }
  scope_.define(name, placeholder);
}
void type_checker::visit_pass_stmt(pass_stmt *obj) {
  // Nothing to do
}
void type_checker::visit_return_stmt(return_stmt *obj) {
  auto function_name = peek_function();
  ykobject return_data_type = ykobject(dt_pool_);
  if (obj->expression_ != nullptr) {
    obj->expression_->accept(this);
    return_data_type = pop();
  }
  if (function_name.empty() ||
      !this->defs_classes_->has_function(function_name)) {
    error(obj->return_keyword_, "Invalid use of return statement");
  } else {
    // func cannot be null here.
    auto func = this->defs_classes_->get_function(function_name);
    if (!(return_data_type.is_primitive_or_obj() &&
          *return_data_type.datatype_ == *func->return_type_)) {
      error(obj->return_keyword_, "Invalid return data type");
    }
  }
}
void type_checker::visit_while_stmt(while_stmt *obj) {
  obj->expression_->accept(this);
  auto exp = pop();
  if (!exp.is_primitive_or_obj() || !exp.datatype_->is_bool()) {
    error(obj->while_keyword_,
          "While statement expression need to be a boolean");
  }
  push_scope_type(ast_type::STMT_WHILE);
  scope_.push();
  obj->while_body_->accept(this);
  scope_.pop();
  pop_scope_type();
}
void type_checker::check(const std::vector<stmt *> &statements) {
  for (const auto &name : defs_classes_->function_names_) {
    auto function_definition = defs_classes_->get_function(name);
    if (function_definition->params_.size() > 100) {
      error(function_definition->name_,
            "Number of parameters cannot be larger than 100.");
    }
    auto function_placeholder_object = ykobject(dt_pool_);
    function_placeholder_object.object_type_ = object_type::FUNCTION;
    scope_.define_global(name, function_placeholder_object);
  }
  // Define classes
  for (const auto &class_name : defs_classes_->class_names_) {
    auto class_placeholder_object = ykobject(dt_pool_);
    class_placeholder_object.object_type_ = object_type::CLASS_ITSELF;
    scope_.define_global(class_name, class_placeholder_object);
  }
  // Define global constants
  for (const auto &constant_name : defs_classes_->global_const_names_) {
    auto constant_definition = defs_classes_->get_const(constant_name);
    auto placeholder_object = ykobject(constant_definition->data_type_);
    scope_.define_global(constant_name, placeholder_object);
  }
  // Visit all statements
  for (auto st : statements) { st->accept(this); }
}
void type_checker::error(token *tok, const std::string &message) {
  auto err = parsing_error{message, tok};
  errors_.emplace_back(err);
}
void type_checker::error(const std::string &message) {
  auto err = parsing_error{message, "", 0, 0};
  err.token_set_ = false;
  errors_.emplace_back(err);
}
void type_checker::push(const ykobject &data_type) {
  this->object_stack_.push_back(data_type);
}
ykobject type_checker::pop() {
  if (this->object_stack_.empty()) { return ykobject(dt_pool_); }
  auto back = object_stack_.back();
  object_stack_.pop_back();
  return back;
}
void type_checker::push_scope_type(ast_type scope_type) {
  this->scope_type_stack_.emplace_back(scope_type);
}
ast_type type_checker::peek_scope_type() {
  if (this->scope_type_stack_.empty()) {
    return ast_type::STMT_PASS;// Pass is used for unknown
  }
  return this->scope_type_stack_.back();
}
void type_checker::pop_scope_type() {
  if (this->scope_type_stack_.empty()) { return; }
  this->scope_type_stack_.pop_back();
}
void type_checker::push_function(const std::string &prefixed_name) {
  this->function_name_stack_.emplace_back(prefixed_name);
}
std::string type_checker::peek_function() {
  if (this->function_name_stack_.empty()) { return ""; }
  return this->function_name_stack_.back();
}
void type_checker::pop_function() {
  if (this->function_name_stack_.empty()) { return; }
  this->function_name_stack_.pop_back();
}
void type_checker::visit_defer_stmt(defer_stmt *obj) {
  if (obj->expression_ != nullptr) {
    auto st = expression_stmt{obj->expression_};
    this->visit_expression_stmt(&st);
  } else {
    obj->del_statement_->accept(this);
  }
}
void type_checker::visit_class_stmt(class_stmt *obj) {
  // TODO check validity of types
}
void type_checker::visit_del_stmt(del_stmt *obj) {
  auto st = expression_stmt{obj->expression_};
  this->visit_expression_stmt(&st);
}
void type_checker::visit_get_expr(get_expr *obj) {
  handle_dot_operator(obj->lhs_, obj->dot_, obj->item_);
}
void type_checker::handle_dot_operator(expr *lhs_expr, token *dot,
                                       token *member_item) {
  lhs_expr->accept(this);
  auto lhs = pop();
  if (lhs.object_type_ == object_type::MODULE) {
    auto imported = cf_->get(lhs.string_val_);
    bool has_func = imported->data_->dsv_->has_function(member_item->token_);
    bool has_class = imported->data_->dsv_->has_class(member_item->token_);
    bool has_const = imported->data_->dsv_->has_const(member_item->token_);
    auto obj = ykobject(dt_pool_);
    if (has_class) {
      obj.object_type_ = object_type::MODULE_CLASS;
      /* for io.open */
      obj.string_val_ = member_item->token_; /* open */
      obj.module_file_ = lhs.string_val_;    /* file path */
      obj.module_name_ = lhs.module_name_;   /* io */
    } else if (has_func) {
      obj.object_type_ = object_type::MODULE_FUNCTION;
      obj.string_val_ = member_item->token_;
      obj.module_file_ = lhs.string_val_;
      obj.module_name_ = lhs.module_name_;
    } else if (has_const) {
      auto glob = imported->data_->dsv_->get_const(member_item->token_);
      obj.object_type_ = object_type::PRIMITIVE_OR_OBJ;
      obj.datatype_ = glob->data_type_;
      obj.string_val_ = member_item->token_;
      obj.module_file_ = lhs.string_val_;
      obj.module_name_ = lhs.module_name_;
    } else {
      error(dot, "Member not found");
    }
    push(obj);
    return;
  }
  if (!lhs.is_primitive_or_obj() || lhs.datatype_->is_primitive()) {
    error(dot, "Invalid dot operator, LHS need to be an object");
    push(ykobject(dt_pool_));
    return;
  }
  auto item = member_item->token_;
  auto user_defined_type = lhs.datatype_->type_;
  if (!lhs.datatype_->module_.empty()) {
    auto mod_file_info = cf_->get(lhs.datatype_->module_);
    if (mod_file_info->data_->dsv_->has_class(lhs.datatype_->type_)) {
      auto class_ = mod_file_info->data_->dsv_->get_class(lhs.datatype_->type_);
      for (const auto &member : class_->members_) {
        if (item == member.name_->token_) {
          // Found the member
          auto placeholder = ykobject(dt_pool_);
          placeholder.datatype_ = member.data_type_;
          push(placeholder);
          return;
        }
      }
    }
  } else if (defs_classes_->has_class(user_defined_type)) {
    auto class_ = defs_classes_->get_class(user_defined_type);
    for (const auto &member : class_->members_) {
      if (item == member.name_->token_) {
        // Found the member
        auto placeholder = ykobject(dt_pool_);
        placeholder.datatype_ = member.data_type_;
        push(placeholder);
        return;
      }
    }
  }
  error(dot, "Cannot find data type of LHS");
  push(ykobject(dt_pool_));
}
void type_checker::visit_set_expr(set_expr *obj) {
  handle_dot_operator(obj->lhs_, obj->dot_, obj->item_);
}
void type_checker::visit_assign_member_expr(assign_member_expr *obj) {
  obj->set_oper_->accept(this);
  auto lhs = pop();
  obj->right_->accept(this);
  auto rhs = pop();
  handle_assigns(obj->opr_, lhs, rhs);
}
void type_checker::visit_square_bracket_access_expr(
    square_bracket_access_expr *obj) {
  handle_square_access(obj->index_expr_, obj->sqb_token_, obj->name_);
}
void type_checker::handle_square_access(expr *index_expr, token *sqb_token,
                                        expr *name_expr) {
  index_expr->accept(this);
  auto index_exp = pop();
  if (!index_exp.datatype_->is_an_integer()) {
    push(ykobject(dt_pool_));
    error(sqb_token, "Invalid index expression, must be of a valid integer");
  }
  name_expr->accept(this);
  auto arr_var = pop();
  if (arr_var.datatype_->is_an_array()) {
    auto placeholder = ykobject(dt_pool_);
    placeholder.datatype_ = arr_var.datatype_->args_[0];
    push(placeholder);
    return;
  }
  push(ykobject(dt_pool_));
  error(sqb_token, "Not an array");
}
void type_checker::visit_assign_arr_expr(assign_arr_expr *obj) {
  obj->assign_oper_->accept(this);
  auto lhs = pop();
  obj->right_->accept(this);
  auto rhs = pop();
  handle_assigns(obj->opr_, lhs, rhs);
}
void type_checker::handle_assigns(token *oper, const ykobject &lhs,
                                  const ykobject &rhs) {
  if (lhs.object_type_ != rhs.object_type_ ||
      *lhs.datatype_ != *rhs.datatype_) {
    error(oper, "Cannot assign between 2 different data types.");
  }
  if (lhs.datatype_->is_const()) { error(oper, "Cannot assign to a constant"); }
}
void type_checker::visit_square_bracket_set_expr(square_bracket_set_expr *obj) {
  handle_square_access(obj->index_expr_, obj->sqb_token_, obj->name_);
}
void type_checker::visit_ccode_stmt(ccode_stmt *obj) {
  auto fname = peek_function();
  auto fn = defs_classes_->get_function(fname);
  if (!fn->annotations_.native_ && !fn->annotations_.native_macro_) {
    error(obj->ccode_keyword_,
          "Invalid use of ccode statement outside non native function");
  }
}
void type_checker::visit_import_stmt(import_stmt *obj) {}
void type_checker::visit_const_stmt(const_stmt *obj) {
  if (!obj->data_type_->args_[0]->is_bool() && !obj->data_type_->args_[0]->is_a_number()) {
    error(obj->name_, "Only number and bool constants are supported");
  }
  if (obj->expression_ == nullptr) {
    error(obj->name_, "Need a value for the constant");
  }
  auto name = obj->name_->token_;
  auto placeholder = ykobject(obj->data_type_);
  if (obj->expression_ != nullptr) {
    obj->expression_->accept(this);
    auto expression_data = pop();
    if (expression_data.object_type_ != placeholder.object_type_) {
      error(obj->name_, "Data type mismatch in expression and declaration.");
    }
  }
  // If this is not a global constant define it
  if (!scope_.is_global_level()) { scope_.define(name, placeholder); }
}
