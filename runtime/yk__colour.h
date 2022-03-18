#if !defined(YK__COLOUR)
#define YK__COLOUR
#if defined(_WIN32) || defined(_WIN64)
#include <windows.h>
void yk__set_colour(int color);
#define RED FOREGROUND_RED
#define GREEN FOREGROUND_GREEN
#define WHITE FOREGROUND_BLUE | FOREGROUND_RED | FOREGROUND_GREEN
#define BLUE FOREGROUND_BLUE
#define PURPLE FOREGROUND_BLUE | FOREGROUND_RED
#define YELLOW FOREGROUND_RED | FOREGROUND_GREEN
#define CYAN FOREGROUND_GREEN | FOREGROUND_BLUE
#define REWIND FOREGROUND_BLUE | FOREGROUND_RED | FOREGROUND_GREEN
#else
#define RED "\033[0;31m"
#define GREEN "\033[0;32m"
#define WHITE "\033[0;37m"
#define BLUE "\033[0;34m"
#define PURPLE "\033[0;35m"
#define YELLOW "\033[0;33m"
#define CYAN "\033[0;36m"
#define REWIND "\x1B[0m"
#if defined(__linux__) || (defined(__APPLE__) && defined(__MACH__)) ||         \
    defined(__unix__)
void yk__set_colour(char *color);
#else
// Do nothing if not supported
#define yk__set_colour(x)
#endif
#endif
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
