// annotation.h
#ifndef ANNOTATION_H
#define ANNOTATION_H
#include <string>
namespace yaksha {
  struct annotation {
    annotation();
    ~annotation();
    std::string name_{};
    std::string arg_{};
    bool arg_set_{false};
  };
}// namespace yaksha
#endif
