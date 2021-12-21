// environment.cpp
#include "environment.h"
using namespace yaksha;
environment::environment() : variables_() {}
environment::~environment() = default;
bool environment::is_defined(const std::string &name) {
  return variables_.find(name) != variables_.end();
}
void environment::define(const std::string &name, ykobject data) {
  variables_.emplace(name, std::move(data));
}
ykobject &environment::get(const std::string &name) { return variables_[name]; }
void environment::assign(const std::string &name, ykobject data) {
  variables_[name] = std::move(data);
}
