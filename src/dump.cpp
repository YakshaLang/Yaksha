#include "ast/ast_printer.h"
#include "ast/parser.h"
#include "compiler/def_class_visitor.h"
#include "tokenizer/block_analyzer.h"
#include "tokenizer/tokenizer.h"
#include "utilities/error_printer.h"
using namespace yaksha;
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
  std::cout << "{ \"type\": \"" << string_utils::escape(dt->token_->token_)
            << "\"";
  if (!dt->module_.empty()) {
    std::cout << ", \"module\": \"" << string_utils::escape(dt->module_)
              << "\"";
  }
  if (!dt->args_.empty()) {
    std::cout << ", \"arguments\": [";
    display_dt_args(dt->args_);
    std::cout << "]";
  }
  std::cout << " }";
}
void display_const(const_stmt *const_statement) {
  std::cout << "\n{ \"name\": \""
            << string_utils::escape(const_statement->name_->token_)
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
    std::cout << "{ \"name\": \"" << string_utils::escape(param.name_->token_)
              << "\", \"datatype\": ";
    display_datatype(param.data_type_);
    std::cout << "}";
  }
}
void display_annotations(annotations &annotations) {
  bool first = true;
  if (annotations.native_) {
    std::cout << "{ \"name\": \"@native\", \"argument\": \""
              << string_utils::escape(annotations.native_arg_) << "\" }";
    first = false;
  }
  if (annotations.native_define_) {
    if (!first) { std::cout << ","; }
    std::cout << "{ \"name\": \"@nativedefine\", \"argument\": \""
              << string_utils::escape(annotations.native_define_arg_) << "\" }";
    first = false;
  }
  if (annotations.native_macro_) {
    if (!first) { std::cout << ","; }
    std::cout << "{ \"name\": \"@nativemacro\", \"argument\": \""
              << string_utils::escape(annotations.native_macro_arg_) << "\" }";
    first = false;
  }
  if (annotations.template_) {
    if (!first) { std::cout << ","; }
    std::cout << "{ \"name\": \"@template\", \"argument\": \""
              << string_utils::escape(annotations.template_arg_) << "\" }";
    first = false;
  }
  if (annotations.varargs_) {
    if (!first) { std::cout << ","; }
    std::cout << "{ \"name\": \"@varargs\", \"argument\": \"\" }";
  }
}
void display_fnc(def_stmt *def_statement) {
  std::cout << "\n{ \"name\": \""
            << string_utils::escape(def_statement->name_->token_)
            << "\", \"return_type\": ";
  display_datatype(def_statement->return_type_);
  std::cout << ", \"parameters\": [";
  display_params(def_statement->params_);
  std::cout << "], \"annotations\": [";
  display_annotations(def_statement->annotations_);
  std::cout << "] }";
}
void display_cls(class_stmt *class_statement) {
  std::cout << "\n{ \"name\": \""
            << string_utils::escape(class_statement->name_->token_)
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
    std::cout << "\"" << string_utils::escape(name->token_) << "\"";
  }
}
void display_import(import_stmt *import_statement) {
  std::cout << "\n{ \"alias\": \""
            << string_utils::escape(import_statement->name_->token_)
            << "\", \"path\": [";
  display_import_path(import_statement);
  std::cout << "] }";
}
void display(def_class_visitor &df, parser &parser_object) {
  std::cout << "{";
  // Dump imports
  std::cout << "\n \"imports\": [";
  bool first = true;
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
    display_const(df.get_const(const_name));
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
    display_fnc(df.get_function(fnc_name));
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
    display_cls(df.get_class(cls_name));
  }
  std::cout << "\n]}" << std::endl;
}
// Simple main function to run a script and print the ast.
int main(int argc, char *argv[]) {
  if (argc != 2) {
    std::cerr << "Usage: yakshadmp script.yaka\n";
    return EXIT_FAILURE;
  }
  std::string file_name{argv[1]};
  std::ifstream script_file(file_name);
  if (!script_file.good()) {
    std::cerr << "Failed to read file:" << file_name << "\n";
    return EXIT_FAILURE;
  }
  std::string data((std::istreambuf_iterator<char>(script_file)),
                   std::istreambuf_iterator<char>());
  tokenizer t{file_name, data};
  t.tokenize();
  if (!t.errors_.empty()) {
    errors::print_errors(t.errors_);
    return EXIT_FAILURE;
  }
  block_analyzer b{t.tokens_};
  b.analyze();
  ykdt_pool dt_pool{};
  try {
    parser p{file_name, b.tokens_, &dt_pool};
    auto tree = p.parse();
    if (!tree.empty() && p.errors_.empty()) {
      def_class_visitor def_visitor{};
      def_visitor.extract(tree);
      // def visitor should extract functions, classes & consts
      if (!def_visitor.errors_.empty()) {
        errors::print_errors(def_visitor.errors_);
        return EXIT_FAILURE;
      }
      display(def_visitor, p);
    } else {
      errors::print_errors(p.errors_);
      return EXIT_FAILURE;
    }
  } catch (parsing_error &p) {
    std::cerr << "Parsing failed " << p.message_ << "\n";
    return EXIT_FAILURE;
  }
  return EXIT_SUCCESS;
}