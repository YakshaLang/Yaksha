// type_checker.cpp
#include "type_checker.h"
#include "compiler_utils.h"
#include "utilities/ykfunction.h"
using namespace yaksha;
type_checker::type_checker(ykdt_pool *pool) : dt_pool_(pool), scope_(pool) {}
type_checker::~type_checker() = default;
void type_checker::visit_assign_expr(assign_expr *obj) {
  obj->right_->accept(this);
  auto rhs = pop();
  auto name = prefix(obj->name_->token_);
  if (!scope_.is_defined(name)) {
    error(obj->name_, "This is not defined");
    return;
  }
  auto object = scope_.get(name);
  if (rhs.object_type_ != object.object_type_) {
    error(obj->name_, "Cannot assign between 2 different data types.");
  }
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
  if (name.object_type_ == object_type::CLASS_ITSELF) {
    auto class_name = name.string_val_;
    auto data = ykobject(dt_pool_->create(class_name));
    push(data);
    // Creating a custom object from user defined type / class;
    return;
  }
  if (name.object_type_ != object_type::FUNCTION) {
    error(obj->paren_token_, "Calling a non callable "
                             "or a non existing function");
    push(ykobject(dt_pool_));// Push None here
    return;
  }
  std::vector<ykobject> arguments{};
  for (auto arg : obj->args_) {
    arg->accept(this);
    arguments.push_back(pop());
  }
  // check if it's same size
  auto funct = defs_classes_.get_function(name.string_val_);
  if (funct->params_.size() != arguments.size()) {
    error(obj->paren_token_, "Too few or too "
                             "much arguments for function call");
    push(ykobject(dt_pool_));// Push None here
    return;
  }
  for (auto i = 0; i < funct->params_.size(); i++) {
    auto param = funct->params_[i];
    auto arg = arguments[i];
    if (!(arg.is_primitive_or_obj() && *arg.datatype_ == *param.data_type_)) {
      std::stringstream message{};
      message << "Parameter & argument " << (i + 1) << " mismatches";
      error(obj->paren_token_, message.str());
    }
  }
  auto data = ykobject(funct->return_type_);
  push(data);
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
        lhs.is_primitive_or_obj() && lhs.datatype_->is_bool())) {
    error(obj->opr_, "Both LHS and RHS of logical"
                     " operator need to be boolean");
  }
}
void type_checker::visit_unary_expr(unary_expr *obj) {
  // -5 - correct, -"some string" is not
  obj->right_->accept(this);
  auto rhs = pop();
  if (!rhs.is_primitive_or_obj() || !rhs.datatype_->is_a_number()) {
    error(obj->opr_, "Invalid unary operation");
  }
  push(rhs);
}
void type_checker::visit_variable_expr(variable_expr *obj) {
  auto name = prefix(obj->name_->token_);
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
  push_function(prefix(obj->name_->token_));
  scope_.push();
  for (auto param : obj->params_) {
    auto name = prefix(param.name_->token_);
    if (scope_.is_defined(name)) {
      error(param.name_, "Parameter shadows outer scope name.");
    } else {
      auto data = ykobject(param.data_type_);
      scope_.define(name, data);
    }
  }
  obj->function_body_->accept(this);
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
  auto name = prefix(obj->name_->token_);
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
void type_checker::visit_print_stmt(print_stmt *obj) {
  obj->expression_->accept(this);
  pop();
}
void type_checker::visit_return_stmt(return_stmt *obj) {
  auto function_name = peek_function();
  obj->expression_->accept(this);
  auto return_data_type = pop();
  if (function_name.empty() ||
      !this->defs_classes_.has_function(function_name)) {
    error(obj->return_keyword_, "Invalid use of return statement");
  } else {
    // func cannot be null here.
    auto func = this->defs_classes_.get_function(function_name);
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
  defs_classes_.extract(statements);
  for (const auto &err : defs_classes_.errors_) { errors_.emplace_back(err); }
  auto main_function_name = prefix("main");
  if (!defs_classes_.has_function(main_function_name)) {
    error("Critical !! main() function must be present");
  } else {
    auto main_function = defs_classes_.get_function(main_function_name);
    if (!main_function->params_.empty()) {
      error("Critical !! main() function must not have parameters");
    }
    if (!main_function->return_type_->is_int()) {
      error("Critical !! main() function must return an integer");
    }
  }
  for (const auto &name : defs_classes_.function_names_) {
    auto function_definition = defs_classes_.get_function(name);
    if (function_definition->params_.size() > 100) {
      error(function_definition->name_,
            "Number of parameters cannot be larger than 100.");
    }
    auto function_placeholder_object = ykobject(dt_pool_);
    function_placeholder_object.object_type_ = object_type::FUNCTION;
    scope_.define_global(name, function_placeholder_object);
  }
  // Define classes
  for (const auto &class_name : defs_classes_.class_names_) {
    auto class_placeholder_object = ykobject(dt_pool_);
    class_placeholder_object.object_type_ = object_type::CLASS_ITSELF;
    scope_.define_global(class_name, class_placeholder_object);
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
  if (!lhs.is_primitive_or_obj() || lhs.datatype_->is_primitive()) {
    error(dot, "Invalid dot operator, LHS need to be an object");
    push(ykobject(dt_pool_));
    return;
  }
  auto item = prefix(member_item->token_);
  auto user_defined_type = prefix(lhs.datatype_->type_);
  if (defs_classes_.has_class(user_defined_type)) {
    auto class_ = defs_classes_.get_class(user_defined_type);
    for (const auto &member : class_->members_) {
      if (item == prefix(member.name_->token_)) {
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
  if (*lhs.datatype_ != *rhs.datatype_) {
    error(obj->opr_, "Cannot assign between 2 different data types.");
  }
}
