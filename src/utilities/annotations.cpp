// annotations.cpp
#include "utilities/annotations.h"
#include <utility>
using namespace yaksha;
void annotations::validate_native_arg(std::string &arg, bool arg_set) {
  if (arg.empty() && arg_set) {
    error_ =
        "Empty string cannot be used as argument to @native or @nativemacro.";
  }
}
void annotations::validate_template(std::string &arg, bool arg_set) {
  if (!arg_set || arg.empty()) {
    error_ = "Argument must be set for @template with valid template types. "
             "Argument cannot be empty as well.";
  }
}
void annotations::add(const annotation &a) {
  if (a.name_ == "native") {
    if (native_) {
      error_ = "Duplicate annotation: @native";
      return;
    }
    if (native_macro_) {
      error_ = "Cannot use @nativemacro when @native is present";
      return;
    }
    if (native_define_) {
      error_ = "Cannot use @nativedefine when @native is present";
      return;
    }
    native_ = true;
    native_arg_ = a.arg_;
    validate_native_arg(native_arg_, a.arg_set_);
    if (!error_.empty()) return;
  } else if (a.name_ == "nativemacro") {
    if (native_macro_) {
      error_ = "Duplicate annotation: @nativemacro";
      return;
    }
    if (native_) {
      error_ = "Cannot use @native when @nativemacro is present";
      return;
    }
    if (native_define_) {
      error_ = "Cannot use @native when @nativedefine is present";
      return;
    }
    native_macro_ = true;
    native_macro_arg_ = a.arg_;
    validate_native_arg(native_macro_arg_, a.arg_set_);
    if (!error_.empty()) return;
  } else if (a.name_ == "nativedefine") {
    if (native_define_) {
      error_ = "Duplicate annotation: @nativedefine";
      return;
    }
    if (native_) {
      error_ = "Cannot use @native when @nativedefine is present";
      return;
    }
    if (native_macro_) {
      error_ = "Cannot use @nativemacro when @nativedefine is present";
      return;
    }
    native_define_ = true;
    native_define_arg_ = a.arg_;
    validate_native_arg(native_define_arg_, a.arg_set_);
    if (native_define_arg_.empty()) {
      error_ = "@nativedefine must have an argument";
      native_define_ = false;
      native_define_arg_ = "";
      return;
    }
    if (!error_.empty()) return;
  } else if (a.name_ == "template") {
    if (template_) {
      error_ = "Duplicate annotation: @template";
      return;
    }
    template_ = true;
    template_arg_ = a.arg_;
    validate_template(template_arg_, a.arg_set_);
    if (!error_.empty()) return;
  } else if (a.name_ == "varargs") {
    if (varargs_) {
      error_ = "Duplicate annotation: @varargs";
      return;
    }
    if (a.arg_set_) {
      error_ = "@vararg does not allow any argument";
      return;
    }
    varargs_ = true;
  } else if (a.name_ == "dotaccess") {
    if (dot_access_) {
      error_ = "Duplicate annotation: @dotaccess";
      return;
    }
    if (a.arg_set_) {
      error_ = "@dotaccess does not allow any argument";
      return;
    }
    dot_access_ = true;
  } else {
    error_ = "Invalid annotation:" + a.name_;
    return;
  }
  annotations_.emplace_back(a);
}
