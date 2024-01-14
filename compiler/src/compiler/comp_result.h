// comp_result.h
#ifndef COMP_RESULT_H
#define COMP_RESULT_H
#include "tokenizer/token.h"
#include <string>
namespace yaksha {
  struct comp_result {
    bool failed_;
    std::string code_;

private:
  };
  struct compiler_output {
    std::string struct_forward_declarations_{};
    std::string function_forward_declarations_{};
    std::string classes_{};
    std::string body_{};
    std::string global_constants_{};
    std::vector<parsing_error> errors_{};
  };
}// namespace yaksha
#endif
