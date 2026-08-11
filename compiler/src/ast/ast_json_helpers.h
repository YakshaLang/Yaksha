#ifndef AST_JSON_HELPERS_H
#define AST_JSON_HELPERS_H

#include "ast/ast.h"
#include "tokenizer/token.h"
#include "utilities/ykdatatype.h"
#include "utilities/annotations.h"
#include "3rd/nlohmann/json.hpp"

namespace yaksha {

inline nlohmann::json to_json_val(token* t) {
    if (!t) return nullptr;
    nlohmann::json j;
    j["file"] = t->file_;
    j["line"] = t->line_;
    j["pos"] = t->pos_;
    j["token"] = t->token_;
    j["type"] = token_to_str(t->type_);
    return j;
}
inline nlohmann::json to_json_val(expr* e) {
    if (!e) return nullptr;
    return e->to_json();
}
inline nlohmann::json to_json_val(stmt* s) {
    if (!s) return nullptr;
    return s->to_json();
}
inline nlohmann::json to_json_val(yk_datatype* dt) {
    if (!dt) return nullptr;
    return dt->as_string();
}
inline nlohmann::json to_json_val(bool b) {
    return b;
}
inline nlohmann::json to_json_val(const annotations& anns) {
    nlohmann::json j = nlohmann::json::object();
    return j;
}
inline nlohmann::json to_json_val(file_info* fi) {
    return fi ? fi->filepath_.string() : nlohmann::json(nullptr);
}
inline nlohmann::json to_json_val(void* p) {
    return nullptr;
}
inline nlohmann::json to_json_val(const name_val& nv) {
    nlohmann::json j;
    j["name"] = to_json_val(nv.name_);
    j["value"] = to_json_val(nv.value_);
    return j;
}
inline nlohmann::json to_json_val(const parameter& p) {
    nlohmann::json j;
    j["name"] = to_json_val(p.name_);
    j["data_type"] = to_json_val(p.data_type_);
    j["enum_val_override"] = to_json_val(p.enum_val_override_);
    return j;
}

// from_json helpers

inline token* from_json_val_token(const nlohmann::json& j, ast_pool* pool) {
    return nullptr; // TODO
}
inline expr* from_json_val_expr(const nlohmann::json& j, ast_pool* pool) {
    return nullptr; // TODO
}
inline stmt* from_json_val_stmt(const nlohmann::json& j, ast_pool* pool) {
    return nullptr; // TODO
}
inline yk_datatype* from_json_val_yk_datatype(const nlohmann::json& j, ast_pool* pool) {
    return nullptr; // TODO
}
inline bool from_json_val_bool(const nlohmann::json& j, ast_pool* pool) {
    if (j.is_boolean()) return j.get<bool>();
    return false;
}
inline annotations from_json_val_annotations(const nlohmann::json& j, ast_pool* pool) {
    return annotations{};
}
inline file_info* from_json_val_file_info(const nlohmann::json& j, ast_pool* pool) {
    return nullptr;
}
inline void* from_json_val_void_ptr(const nlohmann::json& j, ast_pool* pool) {
    return nullptr;
}
inline name_val from_json_val_name_val(const nlohmann::json& j, ast_pool* pool) {
    return name_val{nullptr, nullptr};
}
inline parameter from_json_val_parameter(const nlohmann::json& j, ast_pool* pool) {
    return parameter{nullptr, nullptr, nullptr};
}

template<typename Func>
auto from_json_val_vector_helper(const nlohmann::json& j, Func f) {
    using T = decltype(f(j[0]));
    std::vector<T> v;
    if (j.is_array()) {
        for (const auto& item : j) {
            v.push_back(f(item));
        }
    }
    return v;
}

} // yaksha
#endif
