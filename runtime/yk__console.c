#include "yk__console.h"
#if defined(_WIN32) || defined(_WIN64)
#include <windows.h>
#include <conio.h>
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
int yk__getch() {
  return (int)_getwch();
}
// https://stackoverflow.com/a/6487534/1355145
void yk__clear() {
  COORD topLeft = {0, 0};
  HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
  CONSOLE_SCREEN_BUFFER_INFO screen;
  DWORD written;
  GetConsoleScreenBufferInfo(console, &screen);
  FillConsoleOutputCharacterA(console, ' ', screen.dwSize.X * screen.dwSize.Y,
                              topLeft, &written);
  FillConsoleOutputAttribute(
      console, FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_BLUE,
      screen.dwSize.X * screen.dwSize.Y, topLeft, &written);
  SetConsoleCursorPosition(console, topLeft);
}
#elif defined(__linux__) || (defined(__APPLE__) && defined(__MACH__)) ||       \
    defined(__unix__)
#ifndef _POSIX_C_SOURCE
#define _POSIX_C_SOURCE 200809L
#endif
#include <stdbool.h>
#include <stdio.h>
#include <termios.h>
#include <unistd.h>
#define ISATTY isatty
#define FILENO fileno
void yk__set_colour(char *color) {
  if (!ISATTY(FILENO(stdout))) { return; }
  printf("%s", color);
}
// https://stackoverflow.com/a/912796
int yk__getch() {
  bool success = true;
  char buf = 0;
  struct termios old = {0};
  if (tcgetattr(0, &old) < 0) { success = false; }
  old.c_lflag &= ~ICANON;
  old.c_lflag &= ~ECHO;
  old.c_cc[VMIN] = 1;
  old.c_cc[VTIME] = 0;
  if (tcsetattr(0, TCSANOW, &old) < 0) { success = false; }
  if (read(0, &buf, 1) < 0) { success = false; }
  old.c_lflag |= ICANON;
  old.c_lflag |= ECHO;
  if (tcsetattr(0, TCSADRAIN, &old) < 0) { success = false; }
  return !success ? EOF : buf;
}
// https://stackoverflow.com/a/6487534/1355145
void yk__clear() { printf("\x1B[2J\x1B[H"); }
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
