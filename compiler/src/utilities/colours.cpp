// colors.cpp
#include "colours.h"
#include "cpp_util.h"
using namespace yaksha;
#include <iostream>
#if defined(_WIN32) || defined(_WIN64)
#include <conio.h>
#include <cstdio>
#include <io.h>
#include <windows.h>
#define ISATTY _isatty
#define FILENO _fileno
void yaksha::colour_print(colour c, const std::string &content,
                          std::ostream &outs) {
  int col = 7;
  if (c == colour::BLUE) {
    col = 1;
  } else if (c == colour::GREEN) {
    col = 2;
  } else if (c == colour::CYAN) {
    col = 3;
  } else if (c == colour::RED) {
    col = 4;
  } else if (c == colour::MAGENTA) {
    col = 5;
  } else if (c == colour::YELLOW) {
    col = 6;
  } else {
    outs << content;
    return;
  }
  HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
  SetConsoleTextAttribute(hConsole, col);
  outs << content;
  SetConsoleTextAttribute(hConsole, 7);
}
#else
#ifndef _POSIX_C_SOURCE
#define _POSIX_C_SOURCE 200809L
#endif
#include <cstdio>
#include <unistd.h>
#define ISATTY isatty
#define FILENO fileno
void yaksha::colour_print(colour c, const std::string &content,
                          std::ostream &outs) {
  std::string col{};
  if (c == colour::BLUE) {
    col = "\033[0;34m";
  } else if (c == colour::GREEN) {
    col = "\033[0;32m";
  } else if (c == colour::CYAN) {
    col = "\033[0;36m";
  } else if (c == colour::RED) {
    col = "\033[0;31m";
  } else if (c == colour::MAGENTA) {
    col = "\033[0;35m";
  } else if (c == colour::YELLOW) {
    col = "\033[0;33m";
  } else {
    outs << content;
    return;
  }
  outs << col << content << "\033[0m";
}
#endif
bool yaksha::is_stdout_a_terminal() {
#if defined(YAKSHA_DEBUG) || defined(YAKSHA_FAST_TESTS)
  return false;
#else
  return ISATTY(FILENO(stdout));
#endif
}
std::ostream &yaksha::operator<<(std::ostream &outs,
                                 const coloured_content &p) {
  if (is_stdout_a_terminal()) {
    colour_print(p.c_, p.line_, outs);
  } else {
    outs << p.line_;
  }
  return outs;
}
