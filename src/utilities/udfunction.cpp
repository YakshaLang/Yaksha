// udfunction.cpp
#include "udfunction.h"
#include <utility>
using namespace yaksha;
udfunction::udfunction(environment *scope, stmt_visitor *statement_visitor, stmt *code,
                       std::vector<parameter> *parameters, token *token)
    : scope_(scope), statement_visitor_(statement_visitor), code_(code),
      parameters_(parameters), token_(token) {}
udfunction::~udfunction() = default;
ykobject udfunction::verify(const std::vector<ykobject> &args) {
  if (args.size() != parameters_->size()) {
    return ykobject("Too few or much arguments for function call", token_);
  }
  // TODO Actually check data type
  return ykfunction::verify(args);
}
std::pair<func_control_flow, ykobject>
udfunction::call(const std::vector<ykobject> &args) {
  // Map parameters and arguments in current scope
  for (size_t i = 0; i < args.size(); i++) {
    auto param = (*parameters_)[i];
    auto arg = args[i];
    // no need to check data type here, we should do it in verify()
    scope_->define(param.name_->token_, arg);
  }
  // Actually call the code block
  code_->accept(statement_visitor_);
  return std::make_pair(func_control_flow::EXPECT_RETURN, ykobject());
}
