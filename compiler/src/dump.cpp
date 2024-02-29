// ==============================================================================================
// ╦  ┬┌─┐┌─┐┌┐┌┌─┐┌─┐    Yaksha Programming Language
// ║  ││  ├┤ │││└─┐├┤     is Licensed with GPLv3 + extra terms. Please see below.
// ╩═╝┴└─┘└─┘┘└┘└─┘└─┘
// Note: libs - MIT license, runtime/3rd - various
// ==============================================================================================
// GPLv3:
//
// Yaksha - Programming Language.
// Copyright (C) 2020 - 2024 Bhathiya Perera
//
// This program is free software: you can redistribute it and/or modify it under the terms
// of the GNU General Public License as published by the Free Software Foundation,
// either version 3 of the License, or (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
// or FITNESS FOR A PARTICULAR PURPOSE.
// See the GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License along with this program.
// If not, see https://www.gnu.org/licenses/.
//
// ==============================================================================================
// Additional Terms:
//
// Please note that any commercial use of the programming language's compiler source code
// (everything except compiler/runtime, compiler/libs and compiler/3rd) require a written agreement
// with author of the language (Bhathiya Perera).
//
// If you are using it for an open source project, please give credits.
// Your own project must use GPLv3 license with these additional terms.
//
// You may use programs written in Yaksha/YakshaLisp for any legal purpose
// (commercial, open-source, closed-source, etc) as long as it agrees
// to the licenses of linked runtime libraries (see compiler/runtime/README.md).
//
// ==============================================================================================
#include "ast/ast_printer.h"
#include "ast/parser.h"
#include "compiler/def_class_visitor.h"
#include "compiler/multifile_compiler.h"
#include "tokenizer/block_analyzer.h"
#include "tokenizer/tokenizer.h"
#include "utilities/error_printer.h"
#include "yaksha_lisp/yaksha_lisp.h"
#ifndef PROGRAM_NAME
#define PROGRAM_NAME "ykashadmp"
#endif
using namespace yaksha;
std::string extract_comments(int definition_line, tokenizer &token_extractor) {
  std::size_t position = 0;
  // Skip to first token, after `def, class, const` line
  for (; position < token_extractor.tokens_.size(); position++) {
    auto token = token_extractor.tokens_[position];
    if (token->line_ > definition_line) { break; }
  }
  std::stringstream comments{};
  bool first = true;
  // Extract comments
  for (; position < token_extractor.tokens_.size(); position++) {
    auto token = token_extractor.tokens_[position];
    if (token->type_ == yaksha::token_type::NEW_LINE ||
        token->type_ == yaksha::token_type::INDENT) {
      continue;
    }
    if (token->type_ == yaksha::token_type::COMMENT) {
      if (first) {
        first = false;
      } else {
        comments << "\n";
      }
      comments << trim_copy(token->token_);
    } else {
      break;
    }
  }
  return comments.str();
}
void display_datatype(ykdatatype *dt);
void display_dt_args(std::vector<ykdatatype *> &args) {
  bool first = true;
  for (auto &arg : args) {
    if (first) {
      first = false;
    } else {
      std::cout << ",";
    }
    display_datatype(arg);
  }
}
void display_datatype(ykdatatype *dt) {
  std::cout << "{ \"type\": \"" << string_utils::escape_json(dt->token_->token_)
            << "\"";
  if (!dt->module_.empty()) {
    std::cout << ", \"module\": \"" << string_utils::escape_json(dt->module_)
              << "\"";
  }
  if (!dt->args_.empty()) {
    std::cout << ", \"arguments\": [";
    display_dt_args(dt->args_);
    std::cout << "]";
  }
  std::cout << " }";
}
void display_const(const_stmt *const_statement, tokenizer &token_extractor) {
  std::string comment =
      extract_comments(const_statement->name_->line_, token_extractor);
  std::cout << "\n{ \"name\": \""
            << string_utils::escape_json(const_statement->name_->token_)
            << "\", \"comment\": \"" << string_utils::escape_json(comment)
            << "\", \"datatype\": ";
  display_datatype(const_statement->data_type_);
  std::cout << " }";
}
void display_const(nativeconst_stmt *const_statement,
                   tokenizer &token_extractor) {
  std::string comment =
      extract_comments(const_statement->name_->line_, token_extractor);
  std::cout << "\n{ \"name\": \""
            << string_utils::escape_json(const_statement->name_->token_)
            << "\", \"comment\": \"" << string_utils::escape_json(comment)
            << "\", \"datatype\": ";
  display_datatype(const_statement->data_type_);
  std::cout << " }";
}
void display_params(std::vector<parameter> &params) {
  bool first = true;
  for (auto &param : params) {
    if (first) {
      first = false;
    } else {
      std::cout << ",";
    }
    std::cout << "{ \"name\": \""
              << string_utils::escape_json(param.name_->token_)
              << "\", \"datatype\": ";
    display_datatype(param.data_type_);
    std::cout << "}";
  }
}
void display_annotations(annotations &annotations) {
  bool first = true;
  if (annotations.native_) {
    std::cout << "{ \"name\": \"@native\", \"argument\": \""
              << string_utils::escape_json(annotations.native_arg_) << "\" }";
    first = false;
  }
  if (annotations.native_define_) {
    if (!first) { std::cout << ","; }
    std::cout << "{ \"name\": \"@nativedefine\", \"argument\": \""
              << string_utils::escape_json(annotations.native_define_arg_)
              << "\" }";
    first = false;
  }
  if (annotations.native_macro_) {
    if (!first) { std::cout << ","; }
    std::cout << "{ \"name\": \"@nativemacro\", \"argument\": \""
              << string_utils::escape_json(annotations.native_macro_arg_)
              << "\" }";
    first = false;
  }
  if (annotations.template_) {
    if (!first) { std::cout << ","; }
    std::cout << "{ \"name\": \"@template\", \"argument\": \""
              << string_utils::escape_json(annotations.template_arg_) << "\" }";
    first = false;
  }
  if (annotations.on_stack_) {
    if (!first) { std::cout << ","; }
    std::cout << "{ \"name\": \"@onstack\" }";
    first = false;
  }
  if (annotations.varargs_) {
    if (!first) { std::cout << ","; }
    std::cout << "{ \"name\": \"@varargs\", \"argument\": \"\" }";
  }
}
void display_fnc(def_stmt *def_statement, tokenizer &token_extractor) {
  std::string comment =
      extract_comments(def_statement->name_->line_, token_extractor);
  std::cout << "\n{ \"name\": \""
            << string_utils::escape_json(def_statement->name_->token_)
            << "\", \"comment\": \"" << string_utils::escape_json(comment)
            << "\", \"return_type\": ";
  display_datatype(def_statement->return_type_);
  std::cout << ", \"parameters\": [";
  display_params(def_statement->params_);
  std::cout << "], \"annotations\": [";
  display_annotations(def_statement->annotations_);
  std::cout << "] }";
}
void display_cls(class_stmt *class_statement, tokenizer &token_extractor) {
  std::string comment =
      extract_comments(class_statement->name_->line_, token_extractor);
  std::cout << "\n{ \"name\": \""
            << string_utils::escape_json(class_statement->name_->token_)
            << "\", \"comment\": \"" << string_utils::escape_json(comment)
            << "\", \"members\": [";
  display_params(class_statement->members_);
  std::cout << "], \"annotations\": [";
  display_annotations(class_statement->annotations_);
  std::cout << "] }";
}
void display_import_path(import_stmt *import_statement) {
  bool first = true;
  for (auto name : import_statement->import_names_) {
    if (first) {
      first = false;
    } else {
      std::cout << ",";
    }
    std::cout << "\"" << string_utils::escape_json(name->token_) << "\"";
  }
}
void display_import(import_stmt *import_statement) {
  std::cout << "\n{ \"alias\": \""
            << string_utils::escape_json(import_statement->name_->token_)
            << "\", \"path\": [";
  display_import_path(import_statement);
  std::cout << "] }";
}
std::string yaksha_lisp_value_type_to_str(yaksha_lisp_value_type p) {
  switch (p) {
    case yaksha_lisp_value_type::BUILTIN:
      return "BUILTIN";
    case yaksha_lisp_value_type::EXPR:
      return "EXPR";
    case yaksha_lisp_value_type::LAMBDA:
      return "LAMBDA";
    case yaksha_lisp_value_type::LIST:
      return "LIST";
    case yaksha_lisp_value_type::MAP:
      return "MAP";
    case yaksha_lisp_value_type::METAMACRO:
      return "METAMACRO";
    case yaksha_lisp_value_type::MODULE:
      return "MODULE";
    case yaksha_lisp_value_type::NUMBER:
      return "NUMBER";
    case yaksha_lisp_value_type::STRING:
      return "STRING";
  }
  return "UNKNOWN";
}
void display(def_class_visitor &df, parser &parser_object,
             tokenizer &token_extractor, yaksha_envmap *macro_env) {
  std::cout << "{";
  // Dump macro environment
  std::cout << "\"macro_env\": [";
  bool first = true;
  for (auto &macro : macro_env->symbols_) {
    if (first) {
      first = false;
    } else {
      std::cout << ",";
    }
    std::cout << "{\"name\": \"" << string_utils::escape_json(macro.first)
              << "\", \"type\": \""
              << yaksha_lisp_value_type_to_str(macro.second->type_) << "\" }";
  }
  std::cout << "],";
  // Dump imports
  std::cout << "\n \"imports\": [";
  first = true;
  for (auto import_statement : parser_object.import_stmts_) {
    if (first) {
      first = false;
    } else {
      std::cout << ",";
    }
    display_import(import_statement);
  }
  // Dump global constants
  std::cout << "\n], \"global_consts\": [";
  first = true;
  for (auto &const_name : df.global_const_names_) {
    if (first) {
      first = false;
    } else {
      std::cout << ",";
    }
    display_const(df.get_const(const_name), token_extractor);
  }
  for (auto &const_name : df.global_native_const_names_) {
    if (first) {
      first = false;
    } else {
      std::cout << ",";
    }
    display_const(df.get_native_const(const_name), token_extractor);
  }
  // Dump Functions
  std::cout << "\n], \"functions\": [";
  first = true;
  for (auto &fnc_name : df.function_names_) {
    if (first) {
      first = false;
    } else {
      std::cout << ",";
    }
    display_fnc(df.get_function(fnc_name), token_extractor);
  }
  // Dump classes
  std::cout << "\n], \"classes\": [";
  first = true;
  for (auto &cls_name : df.class_names_) {
    if (first) {
      first = false;
    } else {
      std::cout << ",";
    }
    display_cls(df.get_class(cls_name), token_extractor);
  }
  std::cout << "\n]}" << std::endl;
}
int main(int argc, char *argv[]) {
  if (argc != 2) {
    std::cerr << "Usage: " << PROGRAM_NAME << " script.yaka\n";
    return EXIT_FAILURE;
  }
  multifile_compiler mc{};
  mc.main_required_ = false;
  do_nothing_codegen cg{};
  std::string file_name{argv[1]};
  gc_pool<token> token_pool{};
  std::ifstream script_file{file_name};
  std::string data((std::istreambuf_iterator<char>(script_file)),
                   std::istreambuf_iterator<char>());
  tokenizer token_extractor{file_name, data, &token_pool};
  token_extractor.tokenize();
  if (!token_extractor.errors_.empty()) {
    errors::print_errors(token_extractor.errors_);
    return EXIT_FAILURE;
  }
  auto result = mc.compile(file_name, &cg);
  if (result.failed_) {
    std::cerr << "Failed:" << file_name << "\n";
    return EXIT_FAILURE;
  }
  try {
    auto &cf = mc.get_codefiles();
    auto main_files = cf.main_file_info_;
    auto &tree = main_files->data_->parser_->stmts_;
    auto macro_env = cf.yaksha_macros_.validate_and_get_environment_root(
        main_files->filepath_.string());
    display(*(main_files->data_->dsv_), *(main_files->data_->parser_),
            token_extractor, macro_env);
  } catch (parsing_error &p) {
    std::cerr << "Parsing failed " << p.message_ << "\n";
    return EXIT_FAILURE;
  }
  return EXIT_SUCCESS;
}
