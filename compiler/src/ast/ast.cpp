// ast.cpp
// generated by update_ast.py
#include "ast/ast.h"
using namespace yaksha;
// ------- expressions -----
assign_expr::assign_expr(token* name, token* opr, expr* right, bool promoted, ykdatatype* promoted_data_type)
    : name_(name), opr_(opr), right_(right), promoted_(promoted), promoted_data_type_(promoted_data_type) {}
void assign_expr::accept(expr_visitor *v) {
  v->visit_assign_expr(this);
}
ast_type assign_expr::get_type() {
  return ast_type::EXPR_ASSIGN;
}
token* assign_expr::locate() {
  return name_;
}
expr *ast_pool::c_assign_expr(token* name, token* opr, expr* right, bool promoted, ykdatatype* promoted_data_type) {
  auto o = new assign_expr(name, opr, right, promoted, promoted_data_type);
  cleanup_expr_.push_back(o);
  return o;
}
assign_arr_expr::assign_arr_expr(expr* assign_oper, token* opr, expr* right)
    : assign_oper_(assign_oper), opr_(opr), right_(right) {}
void assign_arr_expr::accept(expr_visitor *v) {
  v->visit_assign_arr_expr(this);
}
ast_type assign_arr_expr::get_type() {
  return ast_type::EXPR_ASSIGN_ARR;
}
token* assign_arr_expr::locate() {
  return opr_;
}
expr *ast_pool::c_assign_arr_expr(expr* assign_oper, token* opr, expr* right) {
  auto o = new assign_arr_expr(assign_oper, opr, right);
  cleanup_expr_.push_back(o);
  return o;
}
assign_member_expr::assign_member_expr(expr* set_oper, token* opr, expr* right)
    : set_oper_(set_oper), opr_(opr), right_(right) {}
void assign_member_expr::accept(expr_visitor *v) {
  v->visit_assign_member_expr(this);
}
ast_type assign_member_expr::get_type() {
  return ast_type::EXPR_ASSIGN_MEMBER;
}
token* assign_member_expr::locate() {
  return opr_;
}
expr *ast_pool::c_assign_member_expr(expr* set_oper, token* opr, expr* right) {
  auto o = new assign_member_expr(set_oper, opr, right);
  cleanup_expr_.push_back(o);
  return o;
}
binary_expr::binary_expr(expr* left, token* opr, expr* right)
    : left_(left), opr_(opr), right_(right) {}
void binary_expr::accept(expr_visitor *v) {
  v->visit_binary_expr(this);
}
ast_type binary_expr::get_type() {
  return ast_type::EXPR_BINARY;
}
token* binary_expr::locate() {
  return opr_;
}
expr *ast_pool::c_binary_expr(expr* left, token* opr, expr* right) {
  auto o = new binary_expr(left, opr, right);
  cleanup_expr_.push_back(o);
  return o;
}
curly_call_expr::curly_call_expr(expr* dt_expr, token* curly_open, std::vector<name_val> values, token* curly_close)
    : dt_expr_(dt_expr), curly_open_(curly_open), values_(std::move(values)), curly_close_(curly_close) {}
void curly_call_expr::accept(expr_visitor *v) {
  v->visit_curly_call_expr(this);
}
ast_type curly_call_expr::get_type() {
  return ast_type::EXPR_CURLY_CALL;
}
token* curly_call_expr::locate() {
  return curly_open_;
}
expr *ast_pool::c_curly_call_expr(expr* dt_expr, token* curly_open, std::vector<name_val> values, token* curly_close) {
  auto o = new curly_call_expr(dt_expr, curly_open, std::move(values), curly_close);
  cleanup_expr_.push_back(o);
  return o;
}
fncall_expr::fncall_expr(expr* name, token* paren_token, std::vector<expr*> args)
    : name_(name), paren_token_(paren_token), args_(std::move(args)) {}
void fncall_expr::accept(expr_visitor *v) {
  v->visit_fncall_expr(this);
}
ast_type fncall_expr::get_type() {
  return ast_type::EXPR_FNCALL;
}
token* fncall_expr::locate() {
  return name_->locate();
}
expr *ast_pool::c_fncall_expr(expr* name, token* paren_token, std::vector<expr*> args) {
  auto o = new fncall_expr(name, paren_token, std::move(args));
  cleanup_expr_.push_back(o);
  return o;
}
get_expr::get_expr(expr* lhs, token* dot, token* item)
    : lhs_(lhs), dot_(dot), item_(item) {}
void get_expr::accept(expr_visitor *v) {
  v->visit_get_expr(this);
}
ast_type get_expr::get_type() {
  return ast_type::EXPR_GET;
}
token* get_expr::locate() {
  return dot_;
}
expr *ast_pool::c_get_expr(expr* lhs, token* dot, token* item) {
  auto o = new get_expr(lhs, dot, item);
  cleanup_expr_.push_back(o);
  return o;
}
grouping_expr::grouping_expr(expr* expression)
    : expression_(expression) {}
void grouping_expr::accept(expr_visitor *v) {
  v->visit_grouping_expr(this);
}
ast_type grouping_expr::get_type() {
  return ast_type::EXPR_GROUPING;
}
token* grouping_expr::locate() {
  return expression_->locate();
}
expr *ast_pool::c_grouping_expr(expr* expression) {
  auto o = new grouping_expr(expression);
  cleanup_expr_.push_back(o);
  return o;
}
literal_expr::literal_expr(token* literal_token)
    : literal_token_(literal_token) {}
void literal_expr::accept(expr_visitor *v) {
  v->visit_literal_expr(this);
}
ast_type literal_expr::get_type() {
  return ast_type::EXPR_LITERAL;
}
token* literal_expr::locate() {
  return literal_token_;
}
expr *ast_pool::c_literal_expr(token* literal_token) {
  auto o = new literal_expr(literal_token);
  cleanup_expr_.push_back(o);
  return o;
}
logical_expr::logical_expr(expr* left, token* opr, expr* right)
    : left_(left), opr_(opr), right_(right) {}
void logical_expr::accept(expr_visitor *v) {
  v->visit_logical_expr(this);
}
ast_type logical_expr::get_type() {
  return ast_type::EXPR_LOGICAL;
}
token* logical_expr::locate() {
  return opr_;
}
expr *ast_pool::c_logical_expr(expr* left, token* opr, expr* right) {
  auto o = new logical_expr(left, opr, right);
  cleanup_expr_.push_back(o);
  return o;
}
macro_call_expr::macro_call_expr(token* path, token* name, token* not_symbol_tok, token* paren_token, std::vector<expr*> args, token* close_paren_token)
    : path_(path), name_(name), not_symbol_tok_(not_symbol_tok), paren_token_(paren_token), args_(std::move(args)), close_paren_token_(close_paren_token) {}
void macro_call_expr::accept(expr_visitor *v) {
  v->visit_macro_call_expr(this);
}
ast_type macro_call_expr::get_type() {
  return ast_type::EXPR_MACRO_CALL;
}
token* macro_call_expr::locate() {
  return name_;
}
expr *ast_pool::c_macro_call_expr(token* path, token* name, token* not_symbol_tok, token* paren_token, std::vector<expr*> args, token* close_paren_token) {
  auto o = new macro_call_expr(path, name, not_symbol_tok, paren_token, std::move(args), close_paren_token);
  cleanup_expr_.push_back(o);
  return o;
}
set_expr::set_expr(expr* lhs, token* dot, token* item)
    : lhs_(lhs), dot_(dot), item_(item) {}
void set_expr::accept(expr_visitor *v) {
  v->visit_set_expr(this);
}
ast_type set_expr::get_type() {
  return ast_type::EXPR_SET;
}
token* set_expr::locate() {
  return dot_;
}
expr *ast_pool::c_set_expr(expr* lhs, token* dot, token* item) {
  auto o = new set_expr(lhs, dot, item);
  cleanup_expr_.push_back(o);
  return o;
}
square_bracket_access_expr::square_bracket_access_expr(expr* name, token* sqb_token, expr* index_expr)
    : name_(name), sqb_token_(sqb_token), index_expr_(index_expr) {}
void square_bracket_access_expr::accept(expr_visitor *v) {
  v->visit_square_bracket_access_expr(this);
}
ast_type square_bracket_access_expr::get_type() {
  return ast_type::EXPR_SQUARE_BRACKET_ACCESS;
}
token* square_bracket_access_expr::locate() {
  return sqb_token_;
}
expr *ast_pool::c_square_bracket_access_expr(expr* name, token* sqb_token, expr* index_expr) {
  auto o = new square_bracket_access_expr(name, sqb_token, index_expr);
  cleanup_expr_.push_back(o);
  return o;
}
square_bracket_set_expr::square_bracket_set_expr(expr* name, token* sqb_token, expr* index_expr)
    : name_(name), sqb_token_(sqb_token), index_expr_(index_expr) {}
void square_bracket_set_expr::accept(expr_visitor *v) {
  v->visit_square_bracket_set_expr(this);
}
ast_type square_bracket_set_expr::get_type() {
  return ast_type::EXPR_SQUARE_BRACKET_SET;
}
token* square_bracket_set_expr::locate() {
  return sqb_token_;
}
expr *ast_pool::c_square_bracket_set_expr(expr* name, token* sqb_token, expr* index_expr) {
  auto o = new square_bracket_set_expr(name, sqb_token, index_expr);
  cleanup_expr_.push_back(o);
  return o;
}
unary_expr::unary_expr(token* opr, expr* right)
    : opr_(opr), right_(right) {}
void unary_expr::accept(expr_visitor *v) {
  v->visit_unary_expr(this);
}
ast_type unary_expr::get_type() {
  return ast_type::EXPR_UNARY;
}
token* unary_expr::locate() {
  return opr_;
}
expr *ast_pool::c_unary_expr(token* opr, expr* right) {
  auto o = new unary_expr(opr, right);
  cleanup_expr_.push_back(o);
  return o;
}
variable_expr::variable_expr(token* name)
    : name_(name) {}
void variable_expr::accept(expr_visitor *v) {
  v->visit_variable_expr(this);
}
ast_type variable_expr::get_type() {
  return ast_type::EXPR_VARIABLE;
}
token* variable_expr::locate() {
  return name_;
}
expr *ast_pool::c_variable_expr(token* name) {
  auto o = new variable_expr(name);
  cleanup_expr_.push_back(o);
  return o;
}
// ------- statements -----
block_stmt::block_stmt(std::vector<stmt*> statements)
    : statements_(std::move(statements)) {}
void block_stmt::accept(stmt_visitor *v) {
  v->visit_block_stmt(this);
}
ast_type block_stmt::get_type() {
  return ast_type::STMT_BLOCK;
}
token* block_stmt::locate() {
  return statements_[0]->locate();
}
stmt *ast_pool::c_block_stmt(std::vector<stmt*> statements) {
  auto o = new block_stmt(std::move(statements));
  cleanup_stmt_.push_back(o);
  return o;
}
break_stmt::break_stmt(token* break_token)
    : break_token_(break_token) {}
void break_stmt::accept(stmt_visitor *v) {
  v->visit_break_stmt(this);
}
ast_type break_stmt::get_type() {
  return ast_type::STMT_BREAK;
}
token* break_stmt::locate() {
  return break_token_;
}
stmt *ast_pool::c_break_stmt(token* break_token) {
  auto o = new break_stmt(break_token);
  cleanup_stmt_.push_back(o);
  return o;
}
ccode_stmt::ccode_stmt(token* ccode_keyword, token* code_str)
    : ccode_keyword_(ccode_keyword), code_str_(code_str) {}
void ccode_stmt::accept(stmt_visitor *v) {
  v->visit_ccode_stmt(this);
}
ast_type ccode_stmt::get_type() {
  return ast_type::STMT_CCODE;
}
token* ccode_stmt::locate() {
  return ccode_keyword_;
}
stmt *ast_pool::c_ccode_stmt(token* ccode_keyword, token* code_str) {
  auto o = new ccode_stmt(ccode_keyword, code_str);
  cleanup_stmt_.push_back(o);
  return o;
}
cfor_stmt::cfor_stmt(token* for_keyword, token* open_paren, expr* init_expr, token* semi1, expr* comparison, token* semi2, expr* operation, token* close_paren, stmt* for_body)
    : for_keyword_(for_keyword), open_paren_(open_paren), init_expr_(init_expr), semi1_(semi1), comparison_(comparison), semi2_(semi2), operation_(operation), close_paren_(close_paren), for_body_(for_body) {}
void cfor_stmt::accept(stmt_visitor *v) {
  v->visit_cfor_stmt(this);
}
ast_type cfor_stmt::get_type() {
  return ast_type::STMT_CFOR;
}
token* cfor_stmt::locate() {
  return for_keyword_;
}
stmt *ast_pool::c_cfor_stmt(token* for_keyword, token* open_paren, expr* init_expr, token* semi1, expr* comparison, token* semi2, expr* operation, token* close_paren, stmt* for_body) {
  auto o = new cfor_stmt(for_keyword, open_paren, init_expr, semi1, comparison, semi2, operation, close_paren, for_body);
  cleanup_stmt_.push_back(o);
  return o;
}
class_stmt::class_stmt(token* name, std::vector<parameter> members, annotations annotations)
    : name_(name), members_(std::move(members)), annotations_(annotations) {}
void class_stmt::accept(stmt_visitor *v) {
  v->visit_class_stmt(this);
}
ast_type class_stmt::get_type() {
  return ast_type::STMT_CLASS;
}
token* class_stmt::locate() {
  return name_;
}
stmt *ast_pool::c_class_stmt(token* name, std::vector<parameter> members, annotations annotations) {
  auto o = new class_stmt(name, std::move(members), annotations);
  cleanup_stmt_.push_back(o);
  return o;
}
compins_stmt::compins_stmt(token* name, ykdatatype* data_type, token* meta1, ykdatatype* meta2, void* meta3)
    : name_(name), data_type_(data_type), meta1_(meta1), meta2_(meta2), meta3_(meta3) {}
void compins_stmt::accept(stmt_visitor *v) {
  v->visit_compins_stmt(this);
}
ast_type compins_stmt::get_type() {
  return ast_type::STMT_COMPINS;
}
token* compins_stmt::locate() {
  return name_;
}
stmt *ast_pool::c_compins_stmt(token* name, ykdatatype* data_type, token* meta1, ykdatatype* meta2, void* meta3) {
  auto o = new compins_stmt(name, data_type, meta1, meta2, meta3);
  cleanup_stmt_.push_back(o);
  return o;
}
const_stmt::const_stmt(token* name, ykdatatype* data_type, expr* expression, bool is_global)
    : name_(name), data_type_(data_type), expression_(expression), is_global_(is_global) {}
void const_stmt::accept(stmt_visitor *v) {
  v->visit_const_stmt(this);
}
ast_type const_stmt::get_type() {
  return ast_type::STMT_CONST;
}
token* const_stmt::locate() {
  return name_;
}
stmt *ast_pool::c_const_stmt(token* name, ykdatatype* data_type, expr* expression, bool is_global) {
  auto o = new const_stmt(name, data_type, expression, is_global);
  cleanup_stmt_.push_back(o);
  return o;
}
continue_stmt::continue_stmt(token* continue_token)
    : continue_token_(continue_token) {}
void continue_stmt::accept(stmt_visitor *v) {
  v->visit_continue_stmt(this);
}
ast_type continue_stmt::get_type() {
  return ast_type::STMT_CONTINUE;
}
token* continue_stmt::locate() {
  return continue_token_;
}
stmt *ast_pool::c_continue_stmt(token* continue_token) {
  auto o = new continue_stmt(continue_token);
  cleanup_stmt_.push_back(o);
  return o;
}
def_stmt::def_stmt(token* name, std::vector<parameter> params, stmt* function_body, ykdatatype* return_type, annotations annotations)
    : name_(name), params_(std::move(params)), function_body_(function_body), return_type_(return_type), annotations_(annotations) {}
void def_stmt::accept(stmt_visitor *v) {
  v->visit_def_stmt(this);
}
ast_type def_stmt::get_type() {
  return ast_type::STMT_DEF;
}
token* def_stmt::locate() {
  return name_;
}
stmt *ast_pool::c_def_stmt(token* name, std::vector<parameter> params, stmt* function_body, ykdatatype* return_type, annotations annotations) {
  auto o = new def_stmt(name, std::move(params), function_body, return_type, annotations);
  cleanup_stmt_.push_back(o);
  return o;
}
defer_stmt::defer_stmt(token* defer_keyword, expr* expression, stmt* del_statement)
    : defer_keyword_(defer_keyword), expression_(expression), del_statement_(del_statement) {}
void defer_stmt::accept(stmt_visitor *v) {
  v->visit_defer_stmt(this);
}
ast_type defer_stmt::get_type() {
  return ast_type::STMT_DEFER;
}
token* defer_stmt::locate() {
  return defer_keyword_;
}
stmt *ast_pool::c_defer_stmt(token* defer_keyword, expr* expression, stmt* del_statement) {
  auto o = new defer_stmt(defer_keyword, expression, del_statement);
  cleanup_stmt_.push_back(o);
  return o;
}
del_stmt::del_stmt(token* del_keyword, expr* expression)
    : del_keyword_(del_keyword), expression_(expression) {}
void del_stmt::accept(stmt_visitor *v) {
  v->visit_del_stmt(this);
}
ast_type del_stmt::get_type() {
  return ast_type::STMT_DEL;
}
token* del_stmt::locate() {
  return del_keyword_;
}
stmt *ast_pool::c_del_stmt(token* del_keyword, expr* expression) {
  auto o = new del_stmt(del_keyword, expression);
  cleanup_stmt_.push_back(o);
  return o;
}
directive_stmt::directive_stmt(token* directive_token, std::vector<parameter> values, token* directive_type, token* directive_val)
    : directive_token_(directive_token), values_(std::move(values)), directive_type_(directive_type), directive_val_(directive_val) {}
void directive_stmt::accept(stmt_visitor *v) {
  v->visit_directive_stmt(this);
}
ast_type directive_stmt::get_type() {
  return ast_type::STMT_DIRECTIVE;
}
token* directive_stmt::locate() {
  return directive_token_;
}
stmt *ast_pool::c_directive_stmt(token* directive_token, std::vector<parameter> values, token* directive_type, token* directive_val) {
  auto o = new directive_stmt(directive_token, std::move(values), directive_type, directive_val);
  cleanup_stmt_.push_back(o);
  return o;
}
enum_stmt::enum_stmt(token* name, std::vector<parameter> members, annotations annotations)
    : name_(name), members_(std::move(members)), annotations_(annotations) {}
void enum_stmt::accept(stmt_visitor *v) {
  v->visit_enum_stmt(this);
}
ast_type enum_stmt::get_type() {
  return ast_type::STMT_ENUM;
}
token* enum_stmt::locate() {
  return name_;
}
stmt *ast_pool::c_enum_stmt(token* name, std::vector<parameter> members, annotations annotations) {
  auto o = new enum_stmt(name, std::move(members), annotations);
  cleanup_stmt_.push_back(o);
  return o;
}
expression_stmt::expression_stmt(expr* expression)
    : expression_(expression) {}
void expression_stmt::accept(stmt_visitor *v) {
  v->visit_expression_stmt(this);
}
ast_type expression_stmt::get_type() {
  return ast_type::STMT_EXPRESSION;
}
token* expression_stmt::locate() {
  return expression_->locate();
}
stmt *ast_pool::c_expression_stmt(expr* expression) {
  auto o = new expression_stmt(expression);
  cleanup_stmt_.push_back(o);
  return o;
}
foreach_stmt::foreach_stmt(token* for_keyword, token* name, ykdatatype* data_type, token* in_keyword, expr* expression, stmt* for_body, ykdatatype* expr_datatype)
    : for_keyword_(for_keyword), name_(name), data_type_(data_type), in_keyword_(in_keyword), expression_(expression), for_body_(for_body), expr_datatype_(expr_datatype) {}
void foreach_stmt::accept(stmt_visitor *v) {
  v->visit_foreach_stmt(this);
}
ast_type foreach_stmt::get_type() {
  return ast_type::STMT_FOREACH;
}
token* foreach_stmt::locate() {
  return for_keyword_;
}
stmt *ast_pool::c_foreach_stmt(token* for_keyword, token* name, ykdatatype* data_type, token* in_keyword, expr* expression, stmt* for_body, ykdatatype* expr_datatype) {
  auto o = new foreach_stmt(for_keyword, name, data_type, in_keyword, expression, for_body, expr_datatype);
  cleanup_stmt_.push_back(o);
  return o;
}
forendless_stmt::forendless_stmt(token* for_keyword, stmt* for_body)
    : for_keyword_(for_keyword), for_body_(for_body) {}
void forendless_stmt::accept(stmt_visitor *v) {
  v->visit_forendless_stmt(this);
}
ast_type forendless_stmt::get_type() {
  return ast_type::STMT_FORENDLESS;
}
token* forendless_stmt::locate() {
  return for_keyword_;
}
stmt *ast_pool::c_forendless_stmt(token* for_keyword, stmt* for_body) {
  auto o = new forendless_stmt(for_keyword, for_body);
  cleanup_stmt_.push_back(o);
  return o;
}
if_stmt::if_stmt(token* if_keyword, expr* expression, stmt* if_branch, token* else_keyword, stmt* else_branch)
    : if_keyword_(if_keyword), expression_(expression), if_branch_(if_branch), else_keyword_(else_keyword), else_branch_(else_branch) {}
void if_stmt::accept(stmt_visitor *v) {
  v->visit_if_stmt(this);
}
ast_type if_stmt::get_type() {
  return ast_type::STMT_IF;
}
token* if_stmt::locate() {
  return if_keyword_;
}
stmt *ast_pool::c_if_stmt(token* if_keyword, expr* expression, stmt* if_branch, token* else_keyword, stmt* else_branch) {
  auto o = new if_stmt(if_keyword, expression, if_branch, else_keyword, else_branch);
  cleanup_stmt_.push_back(o);
  return o;
}
import_stmt::import_stmt(token* import_token, std::vector<token*> import_names, token* name, file_info* data)
    : import_token_(import_token), import_names_(std::move(import_names)), name_(name), data_(data) {}
void import_stmt::accept(stmt_visitor *v) {
  v->visit_import_stmt(this);
}
ast_type import_stmt::get_type() {
  return ast_type::STMT_IMPORT;
}
token* import_stmt::locate() {
  return import_token_;
}
stmt *ast_pool::c_import_stmt(token* import_token, std::vector<token*> import_names, token* name, file_info* data) {
  auto o = new import_stmt(import_token, std::move(import_names), name, data);
  cleanup_stmt_.push_back(o);
  return o;
}
let_stmt::let_stmt(token* name, ykdatatype* data_type, expr* expression)
    : name_(name), data_type_(data_type), expression_(expression) {}
void let_stmt::accept(stmt_visitor *v) {
  v->visit_let_stmt(this);
}
ast_type let_stmt::get_type() {
  return ast_type::STMT_LET;
}
token* let_stmt::locate() {
  return name_;
}
stmt *ast_pool::c_let_stmt(token* name, ykdatatype* data_type, expr* expression) {
  auto o = new let_stmt(name, data_type, expression);
  cleanup_stmt_.push_back(o);
  return o;
}
nativeconst_stmt::nativeconst_stmt(token* name, ykdatatype* data_type, token* ccode_keyword, token* code_str, bool is_global)
    : name_(name), data_type_(data_type), ccode_keyword_(ccode_keyword), code_str_(code_str), is_global_(is_global) {}
void nativeconst_stmt::accept(stmt_visitor *v) {
  v->visit_nativeconst_stmt(this);
}
ast_type nativeconst_stmt::get_type() {
  return ast_type::STMT_NATIVECONST;
}
token* nativeconst_stmt::locate() {
  return name_;
}
stmt *ast_pool::c_nativeconst_stmt(token* name, ykdatatype* data_type, token* ccode_keyword, token* code_str, bool is_global) {
  auto o = new nativeconst_stmt(name, data_type, ccode_keyword, code_str, is_global);
  cleanup_stmt_.push_back(o);
  return o;
}
pass_stmt::pass_stmt(token* pass_token)
    : pass_token_(pass_token) {}
void pass_stmt::accept(stmt_visitor *v) {
  v->visit_pass_stmt(this);
}
ast_type pass_stmt::get_type() {
  return ast_type::STMT_PASS;
}
token* pass_stmt::locate() {
  return pass_token_;
}
stmt *ast_pool::c_pass_stmt(token* pass_token) {
  auto o = new pass_stmt(pass_token);
  cleanup_stmt_.push_back(o);
  return o;
}
return_stmt::return_stmt(token* return_keyword, expr* expression, ykdatatype* result_type)
    : return_keyword_(return_keyword), expression_(expression), result_type_(result_type) {}
void return_stmt::accept(stmt_visitor *v) {
  v->visit_return_stmt(this);
}
ast_type return_stmt::get_type() {
  return ast_type::STMT_RETURN;
}
token* return_stmt::locate() {
  return return_keyword_;
}
stmt *ast_pool::c_return_stmt(token* return_keyword, expr* expression, ykdatatype* result_type) {
  auto o = new return_stmt(return_keyword, expression, result_type);
  cleanup_stmt_.push_back(o);
  return o;
}
runtimefeature_stmt::runtimefeature_stmt(token* runtimefeature_token, token* feature)
    : runtimefeature_token_(runtimefeature_token), feature_(feature) {}
void runtimefeature_stmt::accept(stmt_visitor *v) {
  v->visit_runtimefeature_stmt(this);
}
ast_type runtimefeature_stmt::get_type() {
  return ast_type::STMT_RUNTIMEFEATURE;
}
token* runtimefeature_stmt::locate() {
  return runtimefeature_token_;
}
stmt *ast_pool::c_runtimefeature_stmt(token* runtimefeature_token, token* feature) {
  auto o = new runtimefeature_stmt(runtimefeature_token, feature);
  cleanup_stmt_.push_back(o);
  return o;
}
while_stmt::while_stmt(token* while_keyword, expr* expression, stmt* while_body)
    : while_keyword_(while_keyword), expression_(expression), while_body_(while_body) {}
void while_stmt::accept(stmt_visitor *v) {
  v->visit_while_stmt(this);
}
ast_type while_stmt::get_type() {
  return ast_type::STMT_WHILE;
}
token* while_stmt::locate() {
  return while_keyword_;
}
stmt *ast_pool::c_while_stmt(token* while_keyword, expr* expression, stmt* while_body) {
  auto o = new while_stmt(while_keyword, expression, while_body);
  cleanup_stmt_.push_back(o);
  return o;
}dsl_macro_stmt::dsl_macro_stmt(token* name, token* name2, token* not_symbol_tok, token* curly_open, std::vector<token*> internal_soup, token* curly_close)
    : name_(name), name2_(name2), not_symbol_tok_(not_symbol_tok), curly_open_(curly_open), internal_soup_(std::move(internal_soup)), curly_close_(curly_close) {}
ast_type dsl_macro_stmt::get_type() {
  return ast_type::STMT_DSL_MACRO;
}
void dsl_macro_stmt::accept(stmt_visitor *v) {
}
token* dsl_macro_stmt::locate() {
  return name_;
}
stmt *ast_pool::c_dsl_macro_stmt(token* name, token* name2, token* not_symbol_tok, token* curly_open, std::vector<token*> internal_soup, token* curly_close) {
  auto o = new dsl_macro_stmt(name, name2, not_symbol_tok, curly_open, std::move(internal_soup), curly_close);
  cleanup_stmt_.push_back(o);
  return o;
}
elif_stmt::elif_stmt(token* elif_keyword, expr* expression, stmt* elif_branch)
    : elif_keyword_(elif_keyword), expression_(expression), elif_branch_(elif_branch) {}
ast_type elif_stmt::get_type() {
  return ast_type::STMT_ELIF;
}
void elif_stmt::accept(stmt_visitor *v) {
}
token* elif_stmt::locate() {
  return elif_keyword_;
}
stmt *ast_pool::c_elif_stmt(token* elif_keyword, expr* expression, stmt* elif_branch) {
  auto o = new elif_stmt(elif_keyword, expression, elif_branch);
  cleanup_stmt_.push_back(o);
  return o;
}
macros_stmt::macros_stmt(token* macros_token, token* not_symbol_tok, token* curly_open, std::vector<token*> lisp_code, token* curly_close)
    : macros_token_(macros_token), not_symbol_tok_(not_symbol_tok), curly_open_(curly_open), lisp_code_(std::move(lisp_code)), curly_close_(curly_close) {}
ast_type macros_stmt::get_type() {
  return ast_type::STMT_MACROS;
}
void macros_stmt::accept(stmt_visitor *v) {
}
token* macros_stmt::locate() {
  return macros_token_;
}
stmt *ast_pool::c_macros_stmt(token* macros_token, token* not_symbol_tok, token* curly_open, std::vector<token*> lisp_code, token* curly_close) {
  auto o = new macros_stmt(macros_token, not_symbol_tok, curly_open, std::move(lisp_code), curly_close);
  cleanup_stmt_.push_back(o);
  return o;
}
token_soup_stmt::token_soup_stmt(std::vector<token*> soup)
    : soup_(std::move(soup)) {}
ast_type token_soup_stmt::get_type() {
  return ast_type::STMT_TOKEN_SOUP;
}
void token_soup_stmt::accept(stmt_visitor *v) {
}
token* token_soup_stmt::locate() {
  return soup_[0];
}
stmt *ast_pool::c_token_soup_stmt(std::vector<token*> soup) {
  auto o = new token_soup_stmt(std::move(soup));
  cleanup_stmt_.push_back(o);
  return o;
}
// ------- utils ------
ast_pool::~ast_pool() {
  for (auto e : cleanup_expr_) {
    delete e;
  }
  for (auto e : cleanup_stmt_) {
    delete e;
  }
  cleanup_expr_.clear();
  cleanup_stmt_.clear();
}
ast_pool::ast_pool() {
  cleanup_expr_.reserve(1000);
  cleanup_stmt_.reserve(1000);
}