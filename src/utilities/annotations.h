// annotations.h
#ifndef ANNOTATIONS_H
#define ANNOTATIONS_H
#include "tokenizer/token.h"
#include "utilities/annotation.h"
#include <vector>
namespace yaksha {
  struct annotations {
    void add(const annotation &a);
    bool native_{false};
    bool native_macro_{false};
    bool template_{false};
    std::string native_arg_{};
    std::string native_macro_arg_{};
    std::string template_arg_{};
    std::string error_{};

private:
    std::vector<annotation> annotations_{};
    void validate_native_arg(std::string &arg, bool arg_set);
    void validate_template(std::string &arg, bool arg_set);
  };
}// namespace yaksha
#endif
