#include "yk__colour.h"
#if defined(_WIN32) || defined(_WIN64)
#include <io.h>
#include <stdio.h>
#define ISATTY _isatty
#define FILENO _fileno
HANDLE out;
void yk__set_colour(int color) {
  if (!ISATTY(FILENO(stdout))) { return; }
  if (!out) out = GetStdHandle(STD_OUTPUT_HANDLE);
  SetConsoleTextAttribute(out, FOREGROUND_INTENSITY | color);
}
#elif defined(__linux__) || (defined(__APPLE__) && defined(__MACH__)) ||       \
    defined(__unix__)
#ifndef _POSIX_C_SOURCE
#define _POSIX_C_SOURCE 200809L
#endif
#include <stdio.h>
#include <unistd.h>
#define ISATTY isatty
#define FILENO fileno
void yk__set_colour(char *color) {
  if (!ISATTY(FILENO(stdout))) { return; }
  printf("%s", color);
}
#endif
/*
The MIT License (MIT)

Copyright (c) 2014 Giovanny Andres Gongora Granada
Copyright (c) 2022 Bhathiya Perera
Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:
The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.
THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.

*/
