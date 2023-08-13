#include "cpp_util.h"
#if defined(_WIN32) || defined(_WIN64)
#include <windows.h>
#else
// NOTE: These needs to be properly wrapped like we do for Yaksha runtime
// Better to just use these for unix for now
#include "../../runtime/subprocess.h"
#include "../../runtime/whereami.h"
#endif
#if defined(YAKSHA_OS_WINDOWS)
std::string yaksha::get_my_exe_path() {
  char rawPathName[MAX_PATH];
  GetModuleFileNameA(NULL, rawPathName, MAX_PATH);
  return {rawPathName};
}
#else
std::string yaksha::get_my_exe_path() {
  int length = wai_getModulePath(nullptr, 0, nullptr);
  char *path = (char *) malloc(length + 1);
  if (path == nullptr) { return ""; }
  wai_getModulePath(path, length, nullptr);
  path[length] = '\0';
  return std::string{path,
                     static_cast<std::basic_string<char>::size_type>(length)};
}
#endif
