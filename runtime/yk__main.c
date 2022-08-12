#define YK__SDS_IMPLEMENTATION
#define YK__BHALIB_IMPLEMENTATION
#define YK__STB_DS_IMPLEMENTATION
#include "yk__system.h"
#if defined(_WIN32) || defined(_WIN64)
#include <fcntl.h>
#include <io.h>
#include <windows.h>
#endif
////// Get Arguments implementation that we have in yk__system ///
static struct yk__arguments *yk__arguments_copy;
struct yk__arguments *yk__get_args() {
  return yk__arguments_copy;
}
#if !defined(YK__MINIMAL_MAIN)
int main(int argc, char *argv[]) {
#if defined(_WIN32) || defined(_WIN64)
  int result_mode;
  result_mode = _setmode(_fileno(stdout), _O_U16TEXT);
  if (result_mode == -1) { return -1; }
#if defined(YK__WINDOWS_HIDE_CONSOLE)
  ShowWindow(GetConsoleWindow(), SW_HIDE);
  FreeConsole();
#endif
#endif
  yk__arguments_copy = yk__copy_args(argc, argv);
  int result = yy__main();
  // Free sds strings created for arguments
  for (int j = 0; j < argc; j++) { yk__sdsfree(yk__arguments_copy->argv[j]); }
  yk__arrfree(yk__arguments_copy->argv);
  free(yk__arguments_copy);
  return result;
}
#endif