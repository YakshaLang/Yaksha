// delete_stack_stack.h
#ifndef DELETE_STACK_STACK_H
#define DELETE_STACK_STACK_H
#include "delete_stack.h"
namespace yaksha {
  struct delete_stack_stack : delete_stack {
    delete_stack_stack();
    void push(const std::string &name, const std::string &free_code) override;
    void push_delete_stack(ast_type stack_type);
    void pop_delete_stack();
    void remove(const std::string &name) override;
    void write(std::stringstream &target, int indent_level) override;
    void write(std::stringstream &target, int indent_level,
               const std::string &return_name) override;
    void write_one(std::stringstream &target, int indent_level);
    void write_one(std::stringstream &target, int indent_level,
                   const std::string &return_name);
    void write_upto_loop(std::stringstream &target, int indent_level);
    void write_upto_loop(std::stringstream &target, int indent_level,
                   const std::string &return_name);
    ~delete_stack_stack() override;

private:
    std::vector<delete_stack> delete_levels_{};
  };
}// namespace yaksha
#endif
