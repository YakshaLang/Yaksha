// error_printer.h
#ifndef ERROR_PRINTER_H
#define ERROR_PRINTER_H
#include "tokenizer/string_utils.h"
#include "tokenizer/token.h"
#include <iostream>
#include <ostream>
#include <vector>
namespace yaksha::errors {
  /**
   * Print a problematic token
   * @param output where to write the output to
   * @param tok token object
   */
  static inline void print_token(std::ostream &output, const token &tok) {
    output << tok.file_ << ":" << tok.line_ + 1 << ":" << tok.pos_;//<< ":";
    if (tok.type_ == token_type::END_OF_FILE) {
      output << " at EOF";
    } else if (tok.type_ != token_type::TK_UNKNOWN_TOKEN_DETECTED) {
      output << " at " << string_utils::repr_string(tok.token_);
    } else {
      output << " ";
    }
  }
  /**
   * Print a single error
   * @param output where to write the error message
   * @param err error object
   */
  static inline void print_error(std::ostream &output,
                                 const parsing_error &err) {
    if (!err.token_set_) {
      output << err.message_;
      return;
    }
    auto tok = err.tok_;
    print_token(output, tok);
    output << " --> " << err.message_;
  }
  /**
   * Print a vector of errors to std::cerr
   * @param errors errors to print
   */
  static inline void print_errors(const std::vector<parsing_error> &errors) {
    for (auto &err : errors) {
      print_error(std::cerr, err);
      std::cerr << "\n";
    }
  }
}// namespace yaksha::errors
#endif
