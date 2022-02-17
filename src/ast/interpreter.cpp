// interpreter.cpp
#include "ast/interpreter.h"
#include "tokenizer/string_utils.h"
#include "utilities/udfunction.h"
#include "utilities/ykfunction.h"
using namespace yaksha;
#define NUMBER_OPERATION(operator)                                             \
  do {                                                                         \
    if (left_val.is_primitive_or_obj() && left_val.datatype_->is_int()) {      \
      push(ykobject(left_val.integer_val_ operator right_val.integer_val_,     \
                    dt_pool_));                                                \
    } else if (left_val.is_primitive_or_obj() &&                               \
               left_val.datatype_->is_f64()) {                                 \
      push(ykobject(left_val.double_val_ operator right_val.double_val_,       \
                    dt_pool_));                                                \
    } else {                                                                   \
      push(ykobject{"Unsupported binary operation for strings", obj->opr_});   \
    }                                                                          \
  } while (0)
#define EQ_OPERATION(operator, tk)                                             \
  do {                                                                         \
    bool found_val = false;                                                    \
    if ((tk) == token_type::EQ_EQ) {                                           \
      if (!left_val.is_same_datatype(right_val)) {                             \
        found_val = true;                                                      \
        push(ykobject(false, dt_pool_));                                       \
      }                                                                        \
    } else if ((tk) == token_type::NOT_EQ) {                                   \
      if (!left_val.is_same_datatype(right_val)) {                             \
        found_val = true;                                                      \
        push(ykobject(true, dt_pool_));                                        \
      }                                                                        \
    }                                                                          \
    if (!found_val) {                                                          \
      if (left_val.is_primitive_or_obj() && left_val.datatype_->is_int()) {    \
        push(ykobject(left_val.integer_val_ operator right_val.integer_val_,   \
                      dt_pool_));                                              \
      } else if (left_val.is_primitive_or_obj() &&                             \
                 left_val.datatype_->is_f64()) {                               \
        push(ykobject(left_val.double_val_ operator right_val.double_val_,     \
                      dt_pool_));                                              \
      } else if (left_val.is_primitive_or_obj() &&                             \
                 left_val.datatype_->is_str()) {                               \
        push(ykobject(left_val.string_val_ operator right_val.string_val_,     \
                      dt_pool_));                                              \
      } else if (left_val.is_primitive_or_obj() &&                             \
                 left_val.datatype_->is_none()) {                              \
        push(ykobject((tk) == token_type::EQ_EQ, dt_pool_));                   \
      } else {                                                                 \
        push(ykobject{"Unsupported binary operation", obj->opr_});             \
      }                                                                        \
    }                                                                          \
  } while (0)
#define VALIDATE_NON_NULL_SAME_DATA_TYPE                                       \
  do {                                                                         \
    if (!left_val.is_same_datatype(right_val)) {                               \
      push(ykobject{"Different data types..?", obj->opr_});                    \
      return;                                                                  \
    }                                                                          \
    if ((left_val.is_primitive_or_obj() && left_val.datatype_->is_none()) ||   \
        (right_val.is_primitive_or_obj() && right_val.datatype_->is_none())) { \
      push(ykobject{"Cannot operate on None", obj->opr_});                     \
      return;                                                                  \
    }                                                                          \
  } while (0)
interpreter::interpreter(ykdt_pool *pool) : dt_pool_(pool), globals_(pool) {}
interpreter::~interpreter() {
  for (auto fn : func_pool_) { delete fn; }
}
void interpreter::visit_binary_expr(binary_expr *obj) {
  if (has_error()) { return; }
  obj->left_->accept(this);
  if (has_error()) { return; }
  auto left_val = pop();
  obj->right_->accept(this);
  if (has_error()) { return; }
  auto right_val = pop();
  switch (obj->opr_->type_) {
    case token_type::PLUS:
      VALIDATE_NON_NULL_SAME_DATA_TYPE;
      if (left_val.is_primitive_or_obj() && left_val.datatype_->is_str()) {
        push(ykobject(left_val.string_val_ + right_val.string_val_, dt_pool_));
        return;
      }
      NUMBER_OPERATION(+);
      break;
    case token_type::MUL:
      VALIDATE_NON_NULL_SAME_DATA_TYPE;
      NUMBER_OPERATION(*);
      break;
    case token_type::DIV:
      VALIDATE_NON_NULL_SAME_DATA_TYPE;
      if (left_val.is_primitive_or_obj() && left_val.datatype_->is_int()) {
        if (right_val.integer_val_ == 0) {
          push(ykobject{"Integer division by zero", obj->opr_});
          return;
        }
      }
      NUMBER_OPERATION(/);
      break;
    case token_type::SUB:
      VALIDATE_NON_NULL_SAME_DATA_TYPE;
      NUMBER_OPERATION(-);
      break;
    case token_type::LESS:
      VALIDATE_NON_NULL_SAME_DATA_TYPE;
      NUMBER_OPERATION(<);
      break;
    case token_type::LESS_EQ:
      VALIDATE_NON_NULL_SAME_DATA_TYPE;
      NUMBER_OPERATION(<=);
      break;
    case token_type::GREAT:
      VALIDATE_NON_NULL_SAME_DATA_TYPE;
      NUMBER_OPERATION(>);
      break;
    case token_type::GREAT_EQ:
      VALIDATE_NON_NULL_SAME_DATA_TYPE;
      NUMBER_OPERATION(>=);
      break;
    case token_type::EQ_EQ:
      EQ_OPERATION(==, token_type::EQ_EQ);
      break;
    case token_type::NOT_EQ:
      EQ_OPERATION(!=, token_type::NOT_EQ);
      break;
    default:
      push(ykobject{"Unsupported binary operation", obj->opr_});
      break;
  }
}
void interpreter::visit_grouping_expr(grouping_expr *obj) {
  if (has_error()) { return; }
  obj->expression_->accept(this);
}
void interpreter::visit_literal_expr(literal_expr *obj) {
  if (has_error()) { return; }
  if (obj->literal_token_->type_ == token_type::STRING ||
      obj->literal_token_->type_ == token_type::THREE_QUOTE_STRING) {
    push(ykobject(string_utils::unescape(obj->literal_token_->token_),
                  dt_pool_));
  } else if (obj->literal_token_->type_ == token_type::INTEGER_DECIMAL) {
    int val;
    try {
      val = std::stoi(obj->literal_token_->token_);
    } catch (std::out_of_range &e) {
      push(ykobject("Integer number out of range", obj->literal_token_));
      return;
    }
    push(ykobject(val, dt_pool_));
  } else if (obj->literal_token_->type_ == token_type::FLOAT_NUMBER) {
    double val;
    try {
      val = std::stod(obj->literal_token_->token_);
    } catch (std::out_of_range &e) {
      push(ykobject("Double number out of range", obj->literal_token_));
      return;
    }
    push(ykobject(val, dt_pool_));
  } else if (obj->literal_token_->type_ == token_type::KEYWORD_NONE) {
    push(ykobject(dt_pool_));
  } else if (obj->literal_token_->type_ == token_type::KEYWORD_TRUE) {
    push(ykobject(true, dt_pool_));
  } else if (obj->literal_token_->type_ == token_type::KEYWORD_FALSE) {
    push(ykobject(false, dt_pool_));
  } else {
    push(ykobject("Invalid literal data type", obj->literal_token_));
  }
}
void interpreter::visit_unary_expr(unary_expr *obj) {
  if (has_error()) return;
  obj->right_->accept(this);
  if (has_error()) return;
  auto ex = pop();
  if (obj->opr_->type_ == token_type::SUB) {
    if (ex.is_primitive_or_obj() && ex.datatype_->is_f64()) {
      push(ykobject(-ex.double_val_, dt_pool_));
    } else if (ex.is_primitive_or_obj() && ex.datatype_->is_int()) {
      push(ykobject(-ex.integer_val_, dt_pool_));
    } else {
      push(ykobject("Invalid data type", obj->opr_));
    }
  } else {
    push(ykobject("Invalid unary operator", obj->opr_));
  }
}
void interpreter::visit_return_stmt(return_stmt *obj) {
  if (obj->expression_ == nullptr) {
    push(ykobject(dt_pool_));// None
  } else {
    obj->expression_->accept(this);
  }
  // If it's an error we will just return that..
  push(ykobject(control_flow_change::RETURN));
}
void interpreter::push(ykobject obj) {
  object_stack_.emplace_back(std::move(obj));
}
ykobject interpreter::pop() {
  auto val = object_stack_.back();
  object_stack_.pop_back();
  return val;
}
const ykobject &interpreter::peek() { return object_stack_.back(); }
bool interpreter::has_error() {
  return !object_stack_.empty() &&
         peek().object_type_ == object_type::RUNTIME_ERROR;
}
void interpreter::calculate(const std::vector<stmt *> &statements) {
  if (has_error()) { return; }
  for (auto statement : statements) {
    if (has_error()) { return; }
    statement->accept(this);
  }
}
const ykobject &interpreter::evaluate(expr *exp) {
  // exp cannot be null here?
  exp->accept(this);
  return peek();
}
void interpreter::visit_expression_stmt(expression_stmt *obj) {
  evaluate(obj->expression_);
}
void interpreter::visit_print_stmt(print_stmt *obj) {
  evaluate(obj->expression_);
  if (!has_error()) { peek().stringify(std::cout); }
}
void interpreter::visit_variable_expr(variable_expr *obj) {
  if (globals_.is_defined(obj->name_->token_)) {
    push(globals_.get(obj->name_->token_));
    return;
  }
  push(ykobject("Variable undefined", obj->name_));
}
void interpreter::visit_let_stmt(let_stmt *obj) {
  if (has_error()) return;
  // TODO look at data type and create a default object accordingly
  if (obj->expression_ == nullptr) {
    if (globals_.is_defined(obj->name_->token_)) {
      push(ykobject("Redefining variable", obj->name_));
      return;
    }
    globals_.define(obj->name_->token_, ykobject(dt_pool_));
    return;
  }
  evaluate(obj->expression_);
  if (has_error()) { return; }
  // TODO look at the data type here
  if (globals_.is_defined(obj->name_->token_)) {
    push(ykobject("Redefining variable", obj->name_));
    return;
  }
  globals_.define(obj->name_->token_, peek());
}
void interpreter::visit_assign_expr(assign_expr *obj) {
  evaluate(obj->right_);
  if (has_error()) return;
  if (!globals_.is_defined(obj->name_->token_)) {
    push(ykobject("Assigning to an undefined variable.", obj->name_));
    return;
  }
  // TODO check if same data type!
  globals_.assign(obj->name_->token_, peek());
}
void interpreter::visit_block_stmt(block_stmt *obj) {
  if (has_error()) return;
  for (auto st : obj->statements_) {
    st->accept(this);
    if (has_error()) return;
  }
}
void interpreter::visit_if_stmt(if_stmt *obj) {
  if (has_error()) return;
  obj->expression_->accept(this);
  if (has_error()) return;
  auto bool_val = peek();
  if (!bool_val.is_primitive_or_obj() || !bool_val.datatype_->is_bool()) {
    push(ykobject("A boolean is needed for if statement", obj->if_keyword_));
    return;
  }
  if (bool_val.bool_val_) {// True
    obj->if_branch_->accept(this);
    return;
  }
  // If not True and only if we got a real else branch here
  if (obj->else_branch_ != nullptr) { obj->else_branch_->accept(this); }
}
void interpreter::visit_pass_stmt(pass_stmt *obj) {
  // Do nothing
}
void interpreter::visit_logical_expr(logical_expr *obj) {
  if (has_error()) { return; }
  obj->left_->accept(this);
  if (has_error()) { return; }
  auto left_val = pop();
  if (!left_val.is_primitive_or_obj() || !left_val.datatype_->is_bool()) {
    // We are not using truthy stuff in our language
    // such as "" being false for example I may change my mind later though :)
    push(ykobject("Only boolean expressions can be used on LHS", obj->opr_));
    return;
  }
  if (obj->opr_->type_ == token_type::KEYWORD_OR) {
    // Why?, stop here if RHS of an `or` operator is true
    if (left_val.bool_val_) {
      push(left_val);
      return;
    }
  } else {// token_type::KEYWORD_AND
    // Why?, stop here if LHS of an `and` operator is false
    if (!left_val.bool_val_) {
      push(left_val);
      return;
    }
  }
  evaluate(obj->right_);
}
void interpreter::visit_while_stmt(while_stmt *obj) {
  if (has_error()) { return; }
  obj->expression_->accept(this);
  while (true) {
    if (has_error()) { return; }
    auto condition = peek();
    // Type checking for a valid bool type!
    if (!condition.is_primitive_or_obj() || !condition.datatype_->is_bool()) {
      push(ykobject("Only boolean expressions can be used in a while",
                    obj->while_keyword_));
      return;
    }
    // Break from this loop! because condition is now False
    if (!condition.bool_val_) { return; }
    // Execute the body of the loop.
    obj->while_body_->accept(this);
    if (has_error()) {
      if (peek().flow_ == control_flow_change::BREAK) {
        pop();
        break;
      } else if (peek().flow_ == control_flow_change::CONTINUE) {
        pop();
      } else {// Normal runtime error or a return
        return;
      }
    }
    // Execute the condition again, so we can peek at it in line 303
    obj->expression_->accept(this);
  }
}
const ykobject *interpreter::result() {
  if (object_stack_.empty()) { return nullptr; }
  return &peek();
}
void interpreter::visit_break_stmt(break_stmt *obj) {
  push(ykobject(control_flow_change::BREAK));
}
void interpreter::visit_continue_stmt(continue_stmt *obj) {
  push(ykobject(control_flow_change::CONTINUE));
}
void interpreter::visit_fncall_expr(fncall_expr *obj) {
  if (has_error()) return;
  // TODO only allow function calls from variables..
  //  TODO (ex: do not allow to return functions?)
  // get the name of the function by evaluating name expression
  // So we can perhaps have something like return_function()(1, 2, 3)
  // But perhaps, this should be disallowed, would be a bit hard to compile these hmm
  obj->name_->accept(this);
  if (has_error()) return;
  ykobject fn = pop();
  if (fn.object_type_ != object_type::FUNCTION) {
    push(ykobject("Not a callable", obj->paren_token_));
    return;
  }
  // Evaluate all args and convert them to objects that function can understand
  std::vector<ykobject> arguments{};
  for (auto arg : obj->args_) {
    arg->accept(this);
    if (has_error()) return;
    arguments.emplace_back(pop());
  }
  // Verify arguments before we call the function
  ykobject verification = fn.fn_val_->verify(arguments, dt_pool_);
  if (!verification.is_primitive_or_obj() ||
      !verification.datatype_->is_none()) {
    // error with verification of given arguments
    push(verification);
    return;
  }
  // Actually call the function
  globals_.push();// scope of the function
  auto val = fn.fn_val_->call(arguments, dt_pool_);
  if (val.first == func_control_flow::EXPECT_RETURN) {
    if (peek().flow_ == control_flow_change::RETURN) {
      pop();
    } else if (has_error()) {
      // Got an error -> do nothing so that is kept there.
    } else {
      push(ykobject(dt_pool_));// Default to returning None
    }
  } else {
    // We were calling a native function that returns a value, just push that
    push(val.second);
  }
  globals_.pop();
}
void interpreter::visit_def_stmt(def_stmt *obj) {
  auto ud = new udfunction(&globals_, this, obj->function_body_, &obj->params_,
                           obj->name_);
  // Add the function to the global scope
  globals_.define_global(obj->name_->token_, ykobject(ud));
  func_pool_.emplace_back(ud);
}
void interpreter::debug_print_stack() {
  for (const auto &a : object_stack_) {
    std::cout << a;
    std::cout << "\n";
  }
}
void interpreter::visit_defer_stmt(defer_stmt *obj) {}
void interpreter::visit_class_stmt(class_stmt *obj) {}
void interpreter::visit_del_stmt(del_stmt *obj) {}
void interpreter::visit_get_expr(get_expr *obj) {}
void interpreter::visit_set_expr(set_expr *obj) {}
void interpreter::visit_assign_member_expr(assign_member_expr *obj) {}
void interpreter::visit_square_bracket_access_expr(
    square_bracket_access_expr *obj) {}
void interpreter::visit_square_bracket_set_expr(square_bracket_set_expr *obj) {}
void interpreter::visit_assign_arr_expr(assign_arr_expr *obj) {}
void interpreter::visit_ccode_stmt(ccode_stmt *obj) {}
