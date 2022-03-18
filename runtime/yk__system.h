#if !defined(YK__SYSTEM)
#define YK__SYSTEM
#include "yk__lib.h"
#include <string.h>
#include <stdlib.h>
////////////////////////// Base System Module //////////////////////////
struct yk__arguments {
  yk__sds *argv;
  int argc;
};
struct yk__arguments *yk__get_args();
struct yk__arguments *yk__copy_args(int argc, char **argv);
void yk__printstr(const char *str);
void yk__printlnstr(const char *str);
char *yk__get_current_dir_path();
bool yk__exists(yk__sds path);
bool yk__readable(yk__sds path);
bool yk__writable(yk__sds path);
bool yk__executable(yk__sds path);
yk__sds yk__getenv(yk__sds name);
yk__sds yk__io_readfile(yk__sds name);
bool yk__io_writefile(yk__sds name, yk__sds data);
#if defined(_WIN32) || defined(_WIN64)
wchar_t *yk__utf8_to_utf16_null_terminated(const char *str);
char *yk__utf16_to_utf8_null_terminated(const wchar_t *str);
#endif
//////////////////////// Forward declaration to yaksha code main() /////////////
int32_t yy__main();
#endif// YK__SYSTEM