import os

file_path = "compiler/scripts/update_ast.py"
with open(file_path, "r", encoding="utf-8") as f:
    content = f.read()

# 1. Update headers
content = content.replace('// codegen_json.h', '') # just in case
header_insert = """#include "tokenizer/token.h"
#include "utilities/ykdatatype.h"
#include "utilities/annotations.h"
#include <vector>
#include "3rd/nlohmann/json.hpp"

namespace yaksha {
template<typename T> nlohmann::json to_json_val(const std::vector<T>& v);
"""

content = content.replace('#include "utilities/annotations.h"\\n#include <vector>\\nnamespace yaksha {', header_insert)

# 2. Add to_json and from_json to expr/stmt base classes
expr_base_replacement = """struct expr {
  virtual ~expr() = default;
  virtual void accept(expr_visitor *v) = 0;
  virtual ast_type get_type() = 0;
  virtual token* locate() = 0;
  virtual nlohmann::json to_json() = 0;
  size_t hits_{0};
};"""
content = content.replace("""struct expr {
  virtual ~expr() = default;
  virtual void accept(expr_visitor *v) = 0;
  virtual ast_type get_type() = 0;
  virtual token* locate() = 0;
  size_t hits_{0};
};""", expr_base_replacement)

stmt_base_replacement = """struct stmt {
  virtual ~stmt() = default;
  virtual void accept(stmt_visitor *v) = 0;
  virtual ast_type get_type() = 0;
  virtual token* locate() = 0;
  virtual nlohmann::json to_json() = 0;
  size_t hits_{0};
};"""
content = content.replace("""struct stmt {
  virtual ~stmt() = default;
  virtual void accept(stmt_visitor *v) = 0;
  virtual ast_type get_type() = 0;
  virtual token* locate() = 0;
  size_t hits_{0};
};""", stmt_base_replacement)

# 3. Add to_json and from_json to structs
struct_replacement = """struct $R$_expr : expr {
  $EXPLICIT$$R$_expr($PARAMS$);
  void accept(expr_visitor *v) override;
  ast_type get_type() override;
  token* locate() override;
  nlohmann::json to_json() override;
  static $R$_expr* from_json(const nlohmann::json& j, ast_pool* pool);
$STATE$
};"""
content = content.replace("""struct $R$_expr : expr {
  $EXPLICIT$$R$_expr($PARAMS$);
  void accept(expr_visitor *v) override;
  ast_type get_type() override;
  token* locate() override;
$STATE$
};""", struct_replacement)

# 4. Modify C++ implementation generation
cpp_expr_repl = """$R$_expr::$R$_expr($PARAMS$)
    : $FILL_STATE_PARAMS$ {}
void $R$_expr::accept(expr_visitor *v) {
  v->visit_$R$_expr(this);
}
ast_type $R$_expr::get_type() {
  return ast_type::EXPR_$RU$;
}
token* $R$_expr::locate() {
  return $LOCATION_FIELD$;
}
nlohmann::json $R$_expr::to_json() {
  nlohmann::json j;
  j["ast_type"] = "expr_$R$";
$JSON_ASSIGNMENTS$
  return j;
}
$R$_expr* $R$_expr::from_json(const nlohmann::json& j, ast_pool* pool) {
  return static_cast<$R$_expr*>(pool->c_$R$_expr($JSON_PARSE_ARGS$));
}
expr *ast_pool::c_$R$_expr($PARAMS$) {
  auto o = new $R$_expr($PARAMS_NO_TYPES$);
  cleanup_expr_.push_back(o);
  return o;
}"""
content = content.replace("""$R$_expr::$R$_expr($PARAMS$)
    : $FILL_STATE_PARAMS$ {}
void $R$_expr::accept(expr_visitor *v) {
  v->visit_$R$_expr(this);
}
ast_type $R$_expr::get_type() {
  return ast_type::EXPR_$RU$;
}
token* $R$_expr::locate() {
  return $LOCATION_FIELD$;
}
expr *ast_pool::c_$R$_expr($PARAMS$) {
  auto o = new $R$_expr($PARAMS_NO_TYPES$);
  cleanup_expr_.push_back(o);
  return o;
}""", cpp_expr_repl)

cpp_expr_no_accept_repl = """$R$_expr::$R$_expr($PARAMS$)
    : $FILL_STATE_PARAMS$ {}
ast_type $R$_expr::get_type() {
  return ast_type::EXPR_$RU$;
}
void $R$_expr::accept(expr_visitor *v) {
}
token* $R$_expr::locate() {
  return $LOCATION_FIELD$;
}
nlohmann::json $R$_expr::to_json() {
  nlohmann::json j;
  j["ast_type"] = "expr_$R$";
$JSON_ASSIGNMENTS$
  return j;
}
$R$_expr* $R$_expr::from_json(const nlohmann::json& j, ast_pool* pool) {
  return static_cast<$R$_expr*>(pool->c_$R$_expr($JSON_PARSE_ARGS$));
}
expr *ast_pool::c_$R$_expr($PARAMS$) {
  auto o = new $R$_expr($PARAMS_NO_TYPES$);
  cleanup_expr_.push_back(o);
  return o;
}"""
content = content.replace("""$R$_expr::$R$_expr($PARAMS$)
    : $FILL_STATE_PARAMS$ {}
ast_type $R$_expr::get_type() {
  return ast_type::EXPR_$RU$;
}
void $R$_expr::accept(expr_visitor *v) {
}
token* $R$_expr::locate() {
  return $LOCATION_FIELD$;
}
expr *ast_pool::c_$R$_expr($PARAMS$) {
  auto o = new $R$_expr($PARAMS_NO_TYPES$);
  cleanup_expr_.push_back(o);
  return o;
}""", cpp_expr_no_accept_repl)

# 5. Add python functions for json assignment and parse args
helpers = """def get_from_json_call(type_str, field_name):
    j_field = f'j["{field_name}"]'
    if type_str == "token*": return f'from_json_val_token({j_field}, pool)'
    elif type_str == "expr*": return f'from_json_val_expr({j_field}, pool)'
    elif type_str == "stmt*": return f'from_json_val_stmt({j_field}, pool)'
    elif type_str == "yk_datatype*": return f'from_json_val_yk_datatype({j_field}, pool)'
    elif type_str == "bool": return f'from_json_val_bool({j_field}, pool)'
    elif type_str == "annotations": return f'from_json_val_annotations({j_field}, pool)'
    elif type_str == "file_info*": return f'from_json_val_file_info({j_field}, pool)'
    elif type_str == "void*": return f'from_json_val_void_ptr({j_field}, pool)'
    elif type_str.startswith("std::vector<"):
        inner = type_str[12:-1]
        inner_func = get_from_json_call(inner, "__INNER__").replace('j["__INNER__"]', "item")
        return f'from_json_val_vector_helper({j_field}, [&](const nlohmann::json& item) {{ return {inner_func}; }})'
    elif type_str == "name_val": return f'from_json_val_name_val({j_field}, pool)'
    elif type_str == "parameter": return f'from_json_val_parameter({j_field}, pool)'
    else: return f'/* TODO from_json for {type_str} */'

def c_json_assignments(x):
    assignments = []
    for type_str, name in x[1]:
        assignments.append(f'  j["{name}"] = to_json_val({name}_);')
    return "\\n".join(assignments)

def c_json_parse_args(x):
    args = []
    for type_str, name in x[1]:
        args.append(get_from_json_call(type_str, name))
    return ",\\n      ".join(args)
"""

content = content.replace("def c_explicit(x):", helpers + "\\ndef c_explicit(x):")

c_impl_repl = """def c_impl(types, impl_template: str, locations: dict) -> str:
    return "\\n".join([impl_template
                     .replace("$R$", c_r(x))
                     .replace("$LOCATION_FIELD$", locations.get(c_r(x), "nullptr"))
                     .replace("$RU$", c_r(x).upper())
                     .replace("$PARAMS$", c_params(x))
                     .replace("$FILL_STATE_PARAMS$", c_fill_state_params(x))
                     .replace("$PARAMS_NO_TYPES$", c_params_no_types(x))
                     .replace("$JSON_ASSIGNMENTS$", c_json_assignments(x))
                     .replace("$JSON_PARSE_ARGS$", c_json_parse_args(x)) for x in types])"""
content = content.replace("""def c_impl(types, impl_template: str, locations: dict) -> str:
    return "\\n".join([impl_template
                     .replace("$R$", c_r(x))
                     .replace("$LOCATION_FIELD$", locations.get(c_r(x), "nullptr"))
                     .replace("$RU$", c_r(x).upper())
                     .replace("$PARAMS$", c_params(x))
                     .replace("$FILL_STATE_PARAMS$", c_fill_state_params(x))
                     .replace("$PARAMS_NO_TYPES$", c_params_no_types(x)) for x in types])""", c_impl_repl)

with open(file_path, "w", encoding="utf-8") as f:
    f.write(content)
