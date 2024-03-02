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
#include "tokenizer/block_analyzer.h"
#include "tokenizer/string_utils.h"
#include "tokenizer/tokenizer.h"
#include "utilities/error_printer.h"
#ifndef PROGRAM_NAME
#define PROGRAM_NAME "htmlgen"
#endif
using namespace yaksha;
// Reference: https://stackoverflow.com/a/5665377
void encode(std::string &data) {
  std::string buffer;
  buffer.reserve(data.size());
  for (char &pos : data) {
    switch (pos) {
      case '&':
        buffer.append("&amp;");
        break;
      case '\"':
        buffer.append("&quot;");
        break;
      case '\'':
        buffer.append("&apos;");
        break;
      case '<':
        buffer.append("&lt;");
        break;
      case '>':
        buffer.append("&gt;");
        break;
      case ' ':
        buffer.append("&nbsp;");
        break;
      default:
        buffer.append(&pos, 1);
        break;
    }
  }
  data.swap(buffer);
}
std::string keyword_(const std::string &k) {
  std::string mine = k;
  encode(mine);
  return "<span class=\"green\">" + mine + "</span>";
}
std::string numbers_(token_type typ, const std::string &k) {
  std::string mine = k;
  if (typ == token_type::INTEGER_HEX_64 ||
      typ == token_type::INTEGER_DECIMAL_64 ||
      typ == token_type::INTEGER_BIN_64 || typ == token_type::INTEGER_OCT_64) {
    mine += "i64";
  } else if (typ == token_type::INTEGER_HEX_16 ||
             typ == token_type::INTEGER_DECIMAL_16 ||
             typ == token_type::INTEGER_BIN_16 ||
             typ == token_type::INTEGER_OCT_16) {
    mine += "i16";
  } else if (typ == token_type::INTEGER_HEX_8 ||
             typ == token_type::INTEGER_DECIMAL_8 ||
             typ == token_type::INTEGER_BIN_8 ||
             typ == token_type::INTEGER_OCT_8) {
    mine += "i8";
  } else if (typ == token_type::INTEGER_HEX ||
             typ == token_type::INTEGER_DECIMAL ||
             typ == token_type::INTEGER_BIN || typ == token_type::INTEGER_OCT) {
    // ignored
  } else if (typ == token_type::UINTEGER_HEX_16 ||
             typ == token_type::UINTEGER_DECIMAL_16 ||
             typ == token_type::UINTEGER_BIN_16 ||
             typ == token_type::UINTEGER_OCT_16) {
    mine += "u16";
  } else if (typ == token_type::UINTEGER_HEX_8 ||
             typ == token_type::UINTEGER_DECIMAL_8 ||
             typ == token_type::UINTEGER_BIN_8 ||
             typ == token_type::UINTEGER_OCT_8) {
    mine += "u8";
  } else if (typ == token_type::UINTEGER_HEX ||
             typ == token_type::UINTEGER_DECIMAL ||
             typ == token_type::UINTEGER_BIN ||
             typ == token_type::UINTEGER_OCT) {
    mine += "u32";
  } else if (typ == token_type::UINTEGER_HEX_64 ||
             typ == token_type::UINTEGER_DECIMAL_64 ||
             typ == token_type::UINTEGER_BIN_64 ||
             typ == token_type::UINTEGER_OCT_64) {
    mine += "u64";
  }
  encode(mine);
  return "<span class=\"blue\">" + mine + "</span>";
}
std::string strings_(const std::string &k) {
  std::string mine = k;
  encode(mine);
  return "<span class=\"brown\">" + mine + "</span>";
}
std::string operator_(const std::string &k) {
  std::string mine = k;
  encode(mine);
  return "<span class=\"purple\">" + mine + "</span>";
}
bool token_type_has(const token_type &type,
                    std::initializer_list<std::string> str) {
  bool f = false;
  for (auto &s : str) {
    f = f || token_to_str(type).find(s) != std::string::npos;
  }
  return f;
}
int main(int argc, char *argv[]) {
  if (argc != 2) {
    std::cerr << "Usage: " << PROGRAM_NAME << " script.yaka\n";
    return EXIT_FAILURE;
  }
  std::string file_name{argv[1]};
  std::ifstream script_file(file_name);
  if (!script_file.good()) {
    std::cerr << "Failed to read file:" << file_name << "\n";
    return EXIT_FAILURE;
  }
  gc_pool<token> token_pool{};
  std::string data((std::istreambuf_iterator<char>(script_file)),
                   std::istreambuf_iterator<char>());
  tokenizer token_extractor{file_name, data, &token_pool};
  errors::error_printer ep{};
  token_extractor.tokenize();
  if (!token_extractor.errors_.empty()) {
    ep.print_errors(token_extractor.errors_);
    return EXIT_FAILURE;
  }
  // Now to print stuff
  std::cout << "<!DOCTYPE html>\n"
            << "<html>\n"
            << "<head>\n"
            << "<style>\n"
            << "body {\n"
            << "  background-color: #000000;\n"
            << "  color: #ffffff;\n"
            << "  font-family: monospace;\n"
            << "}\n"
            << "span.green {\n"
            << "  color: #00ff00;\n"
            << "}\n"
            << "span.blue {\n"
            << "  color: #0000ff;\n"
            << "}\n"
            << "span.brown {\n"
            << "  color: #ff0000;\n"
            << "}\n"
            << "span.purple {\n"
            << "  color: #ff00ff;\n"
            << "}\n"
            << "</style>\n"
            << "</head>\n"
            << "<body>\n"
            << "<details>\n"
               "<summary>Click to see code sample</summary>\n"
               "<br/>"
            << "\n<!-- START OF CODE -->\n";
  int prev_pos = 999999999;// Smol hack to prevent indenting first line
  for (auto &t : token_extractor.tokens_) {
    if (t->pos_ > prev_pos) {
      for (int i = prev_pos; i < t->pos_; i++) { std::cout << " "; }
    }
    if (t->type_ == token_type::NEW_LINE) {
      std::cout << "<br/>\n";
    } else if (t->type_ == token_type::COMMENT) {
      std::cout << strings_("# " + t->token_);
    } else if (t->type_ == token_type::STRING ||
               t->type_ == token_type::THREE_QUOTE_STRING) {
      std::cout << strings_("\"" + string_utils::escape(t->token_) + "\"");
      t->pos_ += 2;// Smol hack
    } else if (token_type_has(t->type_, {"KEYWORD"})) {
      std::cout << keyword_(t->token_);
    } else if (token_type_has(t->type_, {"NUMBER", "INTEGER"})) {
      std::cout << numbers_(t->type_, t->token_);
    } else if (t->type_ == yaksha::token_type::INDENT) {
      int indent_size = (int) t->token_.size() / 4;
      for (int i = 0; i < indent_size; i++) {
        std::cout << "&nbsp;&nbsp;&nbsp;&nbsp;";
      }
    } else if (t->type_ != token_type::NAME) {
      std::cout << operator_(t->token_);
    } else {
      std::cout << t->token_;
    }
    prev_pos = t->pos_ + (int) t->token_.size();
  }
  std::cout << "\n<!-- END OF CODE -->\n"
            << "<br/>\n"
               "</details>\n"
            << "</body>\n"
            << "</html>\n";
  return EXIT_SUCCESS;
}
