#if !defined(YK__SYSTEM)
#define YK__SYSTEM
#include "yk__lib.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
////////////////////////// Base System Module //////////////////////////
struct yk__arguments {
  yk__sds *argv;
  int argc;
};
struct yk__arguments *yk__get_args();
struct yk__arguments *yk__copy_args(int argc, char **argv);
void yk__printstr(const char *str);
void yk__printlnstr(const char *str);
void yk__printint(intmax_t to_print);
void yk__printlnint(intmax_t to_print);
void yk__printuint(uintmax_t to_print);
void yk__printlnuint(uintmax_t to_print);
void yk__printdbl(double to_print);
void yk__printlndbl(double to_print);
char *yk__get_current_dir_path();
bool yk__change_current_dir_path(yk__sds path);
bool yk__exists(yk__sds path);
bool yk__readable(yk__sds path);
bool yk__writable(yk__sds path);
bool yk__executable(yk__sds path);
bool yk__mkdir(yk__sds path);
yk__sds yk__getenv(yk__sds name);
yk__sds yk__io_readfile(struct yk__bstr name);
bool yk__io_writefile(struct yk__bstr name, struct yk__bstr data);
#if defined(_WIN32) || defined(_WIN64)
wchar_t *yk__utf8_to_utf16_null_terminated(const char *str);
char *yk__utf16_to_utf8_null_terminated(const wchar_t *str);
#endif
#if defined(__EMSCRIPTEN__) || defined(__wasm__) || defined(__wasm32__) || defined(__wasm64__)
#define YAKSHA__WASM_BUILD
#endif
#if !defined(YAKSHA__WASM_BUILD)
#include "_include_io.h"
#include <fcntl.h>
#if defined(_WIN32) || defined(_WIN64)
#include "_include_mman_win.h"
#else
#include <unistd.h>
#include <sys/mman.h>
#endif
#define ENDIANNESS_PORTABLE_CONVERSION
#include "endianness.h"
#endif
//////////////////////// Forward declaration to yaksha code main() /////////////
int32_t yy__main();
#endif// YK__SYSTEM
