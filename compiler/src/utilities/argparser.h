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
// argparser.h
/**
 * Argument Parser
 */
#ifndef ARGPARSER_H
#define ARGPARSER_H
#include "colours.h"
#include <iostream>
#include <string>
#include <vector>
namespace yaksha::argparser {
  struct optional_arg {
    char short_name_;        // c for -c
    std::string long_name_;  // --compile for --compile
    bool has_arg_;           // true if the option has an argument
    std::string arg_value_{};// value of the argument
    bool is_set_{false};     // true if the option is found
    std::string help_{};     // help message
  };
  static inline optional_arg OP_BOOL(const char short_name,
                                     const std::string &long_name,
                                     const std::string &help) {
    return optional_arg{short_name, long_name, false, "", false, help};
  }
  static inline optional_arg OP_VAL(const char short_name,
                                    const std::string &long_name,
                                    const std::string &help) {
    return optional_arg{short_name, long_name, true, "", false, help};
  }
  struct positional_arg {
    std::string name_;   // name of the argument
    std::string value_{};// value of the argument
    bool is_set_{false}; // true if the argument is found
    std::string help_{}; // help message
    bool is_required_{true};
  };
  static inline positional_arg PO(const std::string &name,
                                  const std::string &help) {
    return positional_arg{name, "", false, help, true};
  }
  static inline positional_arg PO_OPT(const std::string &name,
                                      const std::string &help) {
    return positional_arg{name, "", false, help, false};
  }
  struct commandline_args {
    std::string program_name_{};
    std::string program_description_{};
    std::string epilog_{};
    std::vector<optional_arg *> optional_{};
    std::vector<positional_arg *> positional_{};
    std::vector<std::string> remaining_{};
    std::vector<std::string> errors_{};
  };
  static inline commandline_args ARGS(const std::string &program_name,
                                      const std::string &program_description,
                                      const std::string &epilog) {
    return commandline_args{program_name, program_description, epilog};
  }
  /**
   * Parse command line arguments
   */
  static inline void parse_args(int argc, char **argv, commandline_args &args) {
    std::vector<std::string> non_optionals{};
    // Match optional arguments and capture non-optional arguments
    for (int i = 1; i < argc; ++i) {
      std::string current_arg{argv[i]};
      if (current_arg.size() > 1 && current_arg[0] == '-') {
        bool found = false;
        for (optional_arg *option : args.optional_) {
          // support single -c or --compile
          if ((current_arg[0] == '-' && current_arg[1] == option->short_name_ &&
               current_arg.size() == 2) ||
              current_arg == option->long_name_) {
            if (option->has_arg_) {
              if (i + 1 < argc) {
                option->arg_value_ = std::string{argv[i + 1]};
                option->is_set_ = true;
                ++i;// Skip argument value
              } else {
                args.errors_.emplace_back("Error: Missing argument for " +
                                          option->long_name_);
              }
            } else {
              option->arg_value_ = "1";
              option->is_set_ = true;
            }
            found = true;
            break;
          }
        }
        if (!found) {
          args.errors_.emplace_back("Error: Unknown option " + current_arg);
        }
      } else {
        non_optionals.emplace_back(current_arg);
      }
    }
    // Match non-optional arguments with positional arguments
    for (size_t i = 0; i < non_optionals.size(); ++i) {
      if (i < args.positional_.size()) {
        args.positional_[i]->value_ = non_optionals[i];
        args.positional_[i]->is_set_ = true;
      } else {
        args.remaining_.emplace_back(non_optionals[i]);
      }
    }
    // Check for missing positional arguments
    for (positional_arg *arg : args.positional_) {
      if (!arg->is_set_ && arg->is_required_) {
        args.errors_.emplace_back("Error: Missing argument for " + arg->name_);
      }
    }
  }
  /**
   * Print help message
   */
  static inline void print_help(const commandline_args &args) {
    size_t max_op_len = 0;
    for (const optional_arg *arg : args.optional_) {
      size_t len = arg->long_name_.size() + 3;
      if (arg->has_arg_) { len += 6; }
      if (len > max_op_len) { max_op_len = len; }
    }
    size_t max_po_len = 0;
    for (const positional_arg *arg : args.positional_) {
      size_t len = arg->name_.size();
      if (len > max_po_len) { max_po_len = len; }
    }
    std::cout << colours::cyan(
        "==============================================\n");
    std::cout << "Usage: " << colours::green(args.program_name_)
              << " [options]";
    for (const positional_arg *arg : args.positional_) {
      std::cout << " " << arg->name_;
    }
    std::cout << "\n";
    std::cout << colours::magenta(args.program_description_) << "\n";
    std::cout << colours::cyan(
        "==============================================\n");
    std::cout << colours::yellow("Options:\n");
    for (const optional_arg *arg : args.optional_) {
      size_t len = arg->long_name_.size() + 3;
      if (arg->has_arg_) { len += 6; }
      std::cout << colours::cyan("  -")
                << colours::cyan(std::string(1, arg->short_name_))
                << colours::red(", ");
      std::cout << colours::cyan(arg->long_name_);
      if (arg->has_arg_) { std::cout << colours::magenta(" <arg>"); }
      std::cout << std::string(max_op_len - len + 3, ' ');
      std::cout << arg->help_ << "\n";
    }
    std::cout << colours::yellow("Positional arguments:\n");
    for (const positional_arg *arg : args.positional_) {
      std::cout << "  " << colours::cyan(arg->name_);
      std::cout << std::string(max_po_len - arg->name_.size() + 3, ' ');
      std::cout << arg->help_ << "\n";
    }
    std::cout << args.epilog_ << "\n";
  }
  /**
   * Print errors
   */
  static inline void print_errors(const commandline_args &args) {
    for (const std::string &error : args.errors_) {
      std::cerr << error << "\n";
    }
  }
}// namespace yaksha::argparser
#endif