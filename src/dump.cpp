#include "ast/ast_printer.h"
#include "ast/parser.h"
#include "compiler/def_class_visitor.h"
#include "tokenizer/block_analyzer.h"
#include "tokenizer/tokenizer.h"
#include "utilities/error_printer.h"
using namespace yaksha;
// trim from start (in place)
static inline void ltrim(std::string &s) {
  s.erase(s.begin(), std::find_if(s.begin(), s.end(), [](unsigned char ch) {
            return !std::isspace(ch);
          }));
}
// trim from end (in place)
static inline void rtrim(std::string &s) {
  s.erase(std::find_if(s.rbegin(), s.rend(),
                       [](unsigned char ch) { return !std::isspace(ch); })
              .base(),
          s.end());
}
// trim from both ends (in place)
static inline void trim(std::string &s) {
  ltrim(s);
  rtrim(s);
}
// trim from both ends (copying)
static inline std::string trim_copy(std::string s) {
  trim(s);
  return s;
}
// https://stackoverflow.com/questions/5878775/how-to-find-and-replace-string
void replace_all(std::string &s, std::string const &toReplace,
                 std::string const &replaceWith) {
  std::ostringstream oss;
  std::size_t pos = 0;
  std::size_t prevPos = pos;
  while (true) {
    prevPos = pos;
    pos = s.find(toReplace, pos);
    if (pos == std::string::npos) { break; }
    oss << s.substr(prevPos, pos - prevPos);
    oss << replaceWith;
    pos += toReplace.size();
  }
  oss << s.substr(prevPos);
  s = oss.str();
}
std::string extract_comments(int definition_line, tokenizer &token_extractor) {
  std::size_t position = 0;
  // Skip to first token, after `def, class, const` line
  for (; position < token_extractor.tokens_.size(); position++) {
    auto token = token_extractor.tokens_[position];
    if (token.line_ > definition_line) { break; }
  }
  std::stringstream comments{};
  bool first = true;
  // Extract comments
  for (; position < token_extractor.tokens_.size(); position++) {
    auto token = token_extractor.tokens_[position];
    if (token.type_ == yaksha::token_type::NEW_LINE ||
        token.type_ == yaksha::token_type::INDENT) {
      continue;
    }
    if (token.type_ == yaksha::token_type::COMMENT) {
      if (first) {
        first = false;
      } else {
        comments << "\n";
      }
      comments << trim_copy(token.token_);
    } else {
      break;
    }
  }
  return comments.str();
}
std::string escape_comment(const std::string &v) {
  std::string escaped = string_utils::escape(v, false);
  replace_all(escaped, "\\'", "'");
  return escaped;
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
  std::cout << "{ \"type\": \""
            << string_utils::escape(dt->token_->token_, false) << "\"";
  if (!dt->module_.empty()) {
    std::cout << ", \"module\": \"" << string_utils::escape(dt->module_, false)
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
            << string_utils::escape(const_statement->name_->token_, false)
            << "\", \"comment\": \"" << escape_comment(comment)
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
              << string_utils::escape(param.name_->token_, false)
              << "\", \"datatype\": ";
    display_datatype(param.data_type_);
    std::cout << "}";
  }
}
void display_annotations(annotations &annotations) {
  bool first = true;
  if (annotations.native_) {
    std::cout << "{ \"name\": \"@native\", \"argument\": \""
              << string_utils::escape(annotations.native_arg_, false) << "\" }";
    first = false;
  }
  if (annotations.native_define_) {
    if (!first) { std::cout << ","; }
    std::cout << "{ \"name\": \"@nativedefine\", \"argument\": \""
              << string_utils::escape(annotations.native_define_arg_, false)
              << "\" }";
    first = false;
  }
  if (annotations.native_macro_) {
    if (!first) { std::cout << ","; }
    std::cout << "{ \"name\": \"@nativemacro\", \"argument\": \""
              << string_utils::escape(annotations.native_macro_arg_, false)
              << "\" }";
    first = false;
  }
  if (annotations.template_) {
    if (!first) { std::cout << ","; }
    std::cout << "{ \"name\": \"@template\", \"argument\": \""
              << string_utils::escape(annotations.template_arg_, false)
              << "\" }";
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
            << string_utils::escape(def_statement->name_->token_, false)
            << "\", \"comment\": \"" << escape_comment(comment)
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
            << string_utils::escape(class_statement->name_->token_, false)
            << "\", \"comment\": \"" << escape_comment(comment)
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
    std::cout << "\"" << string_utils::escape(name->token_, false) << "\"";
  }
}
void display_import(import_stmt *import_statement) {
  std::cout << "\n{ \"alias\": \""
            << string_utils::escape(import_statement->name_->token_, false)
            << "\", \"path\": [";
  display_import_path(import_statement);
  std::cout << "] }";
}
void display(def_class_visitor &df, parser &parser_object,
             tokenizer &token_extractor) {
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
    display_const(df.get_const(const_name), token_extractor);
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
  tokenizer token_extractor{file_name, data};
  token_extractor.tokenize();
  if (!token_extractor.errors_.empty()) {
    errors::print_errors(token_extractor.errors_);
    return EXIT_FAILURE;
  }
  block_analyzer block_scanner{token_extractor.tokens_};
  block_scanner.analyze();
  ykdt_pool dt_pool{};
  try {
    parser parser_obj{file_name, block_scanner.tokens_, &dt_pool};
    auto tree = parser_obj.parse();
    if (!tree.empty() && parser_obj.errors_.empty()) {
      auto builtins_obj = new builtins{&dt_pool};
      def_class_visitor def_visitor{builtins_obj};
      def_visitor.extract(tree);
      delete builtins_obj;
      // def visitor should extract functions, classes & consts
      if (!def_visitor.errors_.empty()) {
        errors::print_errors(def_visitor.errors_);
        return EXIT_FAILURE;
      }
      display(def_visitor, parser_obj, token_extractor);
    } else {
      errors::print_errors(parser_obj.errors_);
      return EXIT_FAILURE;
    }
  } catch (parsing_error &p) {
    std::cerr << "Parsing failed " << p.message_ << "\n";
    return EXIT_FAILURE;
  }
  return EXIT_SUCCESS;
}