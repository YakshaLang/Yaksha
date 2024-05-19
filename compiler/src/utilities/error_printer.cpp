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
// Note this file only has things to compile during TESTING
#include "utilities/error_printer.h"
namespace yaksha::errors {
  void error_printer::print_token(std::ostream &output, const token &tok) {
    output << tok.file_ << colours::green(":") << tok.line_ + 1
           << colours::green(":") << tok.pos_;
    if (tok.type_ == token_type::END_OF_FILE) {
      output << " at EOF";
    } else if (tok.type_ != token_type::TK_UNKNOWN_TOKEN_DETECTED) {
      output << " at "
             << colours::cyan(string_utils::repr_string(tok.original_));
    } else {
      output << " ";
    }
  }
  void error_printer::print_error(std::ostream &output,
                                  const parsing_error &err) {
#ifdef YAKSHA_TESTING
    error_capture.push_back(err.message_);
#endif
    if (!err.token_set_) {
      output << colours::red(err.message_);
      return;
    }
    auto tok = err.tok_;
    print_token(output, tok);
    output << " --> " << colours::red(err.message_);
  }
#ifdef YAKSHA_TESTING
  bool error_printer::has_error(const std::string &error_message) {
    for (auto &e : error_capture) {
      if (e == error_message) { return true; }
    }
    return false;
  }
  bool error_printer::has_any_error() { return !error_capture.empty(); }
  bool error_printer::has_no_errors() { return error_capture.empty(); }
#endif
  void error_printer::print_errors(const std::vector<parsing_error> &errors) {
    if (json_output_) {
      std::cerr << errors_to_json_lines(errors);
      return;
    } else {
      for (auto &err : errors) {
        print_error(std::cerr, err);
        std::cerr << "\n";
      }
    }
  }
  std::string error_printer::errors_to_json_lines(
      const std::vector<parsing_error> &errors) {
    std::stringstream ss{};
    for (auto &err : errors) {
      ss << "{";
      if (err.token_set_) {
        ss << "\"file\":\"" << string_utils::escape_json(err.tok_.file_)
           << "\",";
        auto relative_file =
            std::filesystem::relative(err.tok_.file_, "./").string();
        ss << "\"relative_file\":\"" << string_utils::escape_json(relative_file)
           << "\",";
        ss << "\"line\":" << err.tok_.line_ + 1 << ",";
        ss << "\"pos\":" << err.tok_.pos_ << ",";
        ss << "\"message\":\"" << string_utils::escape_json(err.message_)
           << "\",";
        ss << "\"token\":\"" << string_utils::escape_json(err.tok_.original_)
           << "\"";
      } else {
        ss << "\"message\":\"" << string_utils::escape_json(err.message_)
           << "\"";
      }
      ss << "}\n";
    }
    return ss.str();
  }
}// namespace yaksha::errors