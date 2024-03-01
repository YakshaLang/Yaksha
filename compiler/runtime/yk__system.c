#include "yk__system.h"
#if defined(_WIN32) || defined(_WIN64)
#include <fcntl.h>
#include <io.h>
#include <locale.h>
#include <stdio.h>
// clang-format off
#include <windows.h>
#include <shellapi.h>
#include <wchar.h>
#else
#include <sys/types.h>
#include <sys/stat.h>
#endif
#ifndef ssize_t
#define ssize_t intmax_t
#endif
// Below code is originally from mman-win32
//
/*
 * sys/mman.h
 * mman-win32
 */
#ifndef _WIN32_WINNT// Allow use of features specific to Windows XP or later.
#define _WIN32_WINNT                                                           \
  0x0501// Change this to the appropriate value to target other versions of Windows.
#endif
#if  !defined(_MSC_VER) && (defined(_WIN32) || defined(_WIN64))
#include <_mingw.h>
#endif
// clang-format on
void yk__printint(intmax_t to_print) {
#if defined(_WIN32) || defined(_WIN64)
  wprintf(L"%jd", to_print);
#else
  printf("%jd", to_print);
#endif
}
void yk__printlnint(intmax_t to_print) {
#if defined(_WIN32) || defined(_WIN64)
  wprintf(L"%jd\n", to_print);
#else
  printf("%jd\n", to_print);
#endif
}
void yk__printuint(uintmax_t to_print) {
#if defined(_WIN32) || defined(_WIN64)
  wprintf(L"%ju", to_print);
#else
  printf("%ju", to_print);
#endif
}
void yk__printlnuint(uintmax_t to_print) {
#if defined(_WIN32) || defined(_WIN64)
  wprintf(L"%ju\n", to_print);
#else
  printf("%ju\n", to_print);
#endif
}
void yk__printdbl(double to_print) {
#if defined(_WIN32) || defined(_WIN64)
  wprintf(L"%f", to_print);
#else
  printf("%f", to_print);
#endif
}
void yk__printlndbl(double to_print) {
#if defined(_WIN32) || defined(_WIN64)
  wprintf(L"%f\n", to_print);
#else
  printf("%f\n", to_print);
#endif
}
struct yk__arguments *yk__copy_args(int argc, char **argv) {
  // Create arguments by copying argv
  struct yk__arguments *arguments = malloc(sizeof(struct yk__arguments));
  arguments->argv = NULL;
  arguments->argc = argc;
#if defined(_WIN32) || defined(_WIN64)
  int windows_argc;
  LPWSTR *windows_argv = CommandLineToArgvW(GetCommandLineW(), &windows_argc);
  if (windows_argv == NULL) { return NULL; }
  for (int i = 0; i < windows_argc; i++) {
    char *utf8 = yk__utf16_to_utf8_null_terminated(windows_argv[i]);
    yk__sds s = yk__sdsnewlen(utf8, strlen(utf8));
    yk__arrput(arguments->argv, s);
    free(utf8);
  }
  LocalFree(windows_argv);
#else
  for (int i = 0; i < argc; i++) {
    yk__sds argument_copy = yk__sdsnewlen(argv[i], strlen(argv[i]));
    yk__arrput(arguments->argv, argument_copy);
  }
#endif
  return arguments;
}
#if defined(_WIN32) || defined(_WIN64)
wchar_t *yk__utf8_to_utf16_null_terminated(const char *str) {
  if (!str) return NULL;
  UINT cp = CP_UTF8;
  if (strlen(str) >= 3 && str[0] == (char) 0xef && str[1] == (char) 0xbb &&
      str[2] == (char) 0xbf)
    str += 3;
  size_t pwcl = MultiByteToWideChar(cp, 0, str, -1, NULL, 0);
  wchar_t *pwcs = (wchar_t *) malloc(sizeof(wchar_t) * (pwcl + 1));
  pwcl = MultiByteToWideChar(cp, 0, str, -1, pwcs, pwcl + 1);
  pwcs[pwcl] = '\0';
  return pwcs;
}
char *yk__utf16_to_utf8_null_terminated(const wchar_t *pwcs) {
  if (!pwcs) return NULL;
  UINT cp = CP_UTF8;
  size_t pmbl = WideCharToMultiByte(cp, 0, pwcs, -1, NULL, 0, NULL, NULL);
  char *pmbs = (char *) malloc(sizeof(char) * (pmbl + 1));
  pmbl = WideCharToMultiByte(cp, 0, pwcs, wcslen(pwcs), pmbs, pmbl, NULL, NULL);
  pmbs[pmbl] = '\0';
  return pmbs;
}
void yk__freewchar_array(wchar_t **arr) {
  if (arr == NULL) return;
  size_t length = yk__arrlenu(arr);
  for (size_t i = 0; i < length; i++) { free(arr[i]); }
  yk__arrfree(arr);
}
void yk__printstr(const char *str) {
  wchar_t *text = yk__utf8_to_utf16_null_terminated(str);
  /* wprintf(L"%ls", text); */
  fputws(text, stdout);
  free(text);
}
void yk__printlnstr(const char *str) {
  wchar_t *text = yk__utf8_to_utf16_null_terminated(str);
  /* wprintf(L"%ls\n", text); */
  _putws(text);
  free(text);
}
#else
void yk__printstr(const char *str) {
  /* printf("%s", str); */
  fputs(str, stdout);
}
void yk__printlnstr(const char *str) {
  /* printf("%s\n", str); */
  puts(str);
}
#endif
#if defined(_WIN32) || defined(_WIN64)
#include <direct.h>
#define GetCurrentDir _wgetcwd
#define ChangeDirectory _wchdir
#else
#include <unistd.h>
#define GetCurrentDir getcwd
#define ChangeDirectory chdir
#endif
char *yk__get_current_dir_path() {
#if defined(_WIN32) || defined(_WIN64)
  wchar_t *wide_buff = malloc(FILENAME_MAX * sizeof(wchar_t));
  if (wide_buff == NULL) return NULL;
  if (!GetCurrentDir(wide_buff, FILENAME_MAX)) {
    free(wide_buff);
    return NULL;
  }
  char *output = yk__utf16_to_utf8_null_terminated(wide_buff);
  free(wide_buff);
  return output;
#else
  char *buff = malloc(FILENAME_MAX);
  if (buff == NULL) return NULL;
  if (!GetCurrentDir(buff, FILENAME_MAX)) {
    free(buff);
    return NULL;
  }
  return buff;
#endif
}
bool yk__change_current_dir_path(yk__sds path) {
  if (path == NULL || !yk__sdslen(path)) {
    yk__sdsfree(path);
    return false;
  }
#if defined(_WIN32) || defined(_WIN64)
  wchar_t *wpath = yk__utf8_to_utf16_null_terminated(path);
  if (wpath == NULL) {
    return false;
  }
  int result = ChangeDirectory(wpath);
  yk__sdsfree(path);
  free(wpath);
  return result == 0;
#else
  int result = ChangeDirectory(path);
  yk__sdsfree(path);
  return result == 0;
#endif
}
////// File stuff ///////////
bool yk__exists(yk__sds path) {
  if (path == NULL || !yk__sdslen(path)) {
    yk__sdsfree(path);
    return false;
  }
#if defined(_WIN32) || defined(_WIN64)
  wchar_t *wpath = yk__utf8_to_utf16_null_terminated(path);
  if (wpath == NULL) {
    yk__sdsfree(path);
    return false;
  }
  bool value = (_waccess(wpath, 0) == 0);
  free(wpath);
#else
  bool value = access(path, F_OK) == 0;
#endif
  yk__sdsfree(path);
  return value;
}
bool yk__readable(yk__sds path) {
  if (path == NULL || !yk__sdslen(path)) {
    yk__sdsfree(path);
    return false;
  }
#if defined(_WIN32) || defined(_WIN64)
  wchar_t *wpath = yk__utf8_to_utf16_null_terminated(path);
  if (wpath == NULL) {
    yk__sdsfree(path);
    return false;
  }
  bool value = (_waccess(wpath, 2) == 0);
  free(wpath);
#else
  bool value = access(path, R_OK) == 0;
#endif
  yk__sdsfree(path);
  return value;
}
bool yk__writable(yk__sds path) {
  if (path == NULL || !yk__sdslen(path)) {
    yk__sdsfree(path);
    return false;
  }
#if defined(_WIN32) || defined(_WIN64)
  wchar_t *wpath = yk__utf8_to_utf16_null_terminated(path);
  if (wpath == NULL) {
    yk__sdsfree(path);
    return false;
  }
  bool value = (_waccess(wpath, 4) == 0);
  free(wpath);
#else
  bool value = access(path, W_OK) == 0;
#endif
  yk__sdsfree(path);
  return value;
}
bool yk__executable(yk__sds path) {
  if (path == NULL || !yk__sdslen(path)) {
    yk__sdsfree(path);
    return false;
  }
#if defined(_WIN32) || defined(_WIN64)
  bool value = yk__readable(yk__sdsdup(path));
  bool end_with_exe = false;
  size_t length = yk__sdslen(path);
  if (length > 4) {
    char e2_char = path[length - 1];
    char x_char = path[length - 2];
    char e_char = path[length - 3];
    char dot_char = path[length - 4];
    end_with_exe = (dot_char == '.') && (e_char == 'e' || e_char == 'E') &&
                   (x_char == 'x' || x_char == 'X') &&
                   (e2_char == 'e' || e2_char == 'E');
  }
  value = value && end_with_exe;
#else
  bool value = access(path, X_OK) == 0;
#endif
  yk__sdsfree(path);
  return value;
}
bool yk__mkdir(yk__sds path) {
  if (path == NULL || !yk__sdslen(path)) {
    yk__sdsfree(path);
    return false;
  }
#if defined(_WIN32) || defined(_WIN64)
  wchar_t *wpath = yk__utf8_to_utf16_null_terminated(path);
  if (wpath == NULL) {
    yk__sdsfree(path);
    return false;
  }
  bool value = (_wmkdir(wpath) == 0);
  free(wpath);
#else
  bool value = mkdir(path, 0755) == 0;
#endif
  yk__sdsfree(path);
  return value;
}
////// Environ ///////
yk__sds yk__getenv(yk__sds name) {
  if (name == NULL || !yk__sdslen(name)) {
    yk__sdsfree(name);
    return yk__sdsempty();
  }
#if defined(_WIN32) || defined(_WIN64)
  wchar_t *wname = yk__utf8_to_utf16_null_terminated(name);
  if (NULL == wname) {
    yk__sdsfree(name);
    return yk__sdsempty();
  }
  wchar_t *env_val;
#if defined(_MSC_VER)// MSVC
  size_t len;
  errno_t error = _wdupenv_s(&env_val, &len, wname);
  if (0 != error) {
    free(wname);
    yk__sdsfree(name);
    return yk__sdsempty();
  }
#else// ZIG CC, MingW, etc
  env_val = _wgetenv(wname);
#endif
  if (NULL == env_val) {
    free(wname);
    yk__sdsfree(name);
    return yk__sdsempty();
  }
  char *converted = yk__utf16_to_utf8_null_terminated(env_val);
  if (NULL == converted) {
#if defined(_MSC_VER)
    free(env_val);
#endif
    free(wname);
    yk__sdsfree(name);
    return yk__sdsempty();
  }
  yk__sds result = yk__sdsnew(converted);
#if defined(_MSC_VER)
  free(env_val);
#endif
  free(wname);
  yk__sdsfree(name);
  free(converted);
  return result;
#else
  char *p = getenv(name);
  if (NULL == p) {
    yk__sdsfree(name);
    return yk__sdsempty();
  }
  yk__sds val = yk__sdsnew(p);
  yk__sdsfree(name);
  return val;
#endif
}
//////////////////////////////////////////////// Io Library //////////////////////////////////////////////////
#if defined(_WIN32) || defined(_WIN64)
char *yk__windows_read_file(const char *path, size_t *length, int *error) {
  // both length and error must be present
  if (length == NULL || error == NULL) { return NULL; }
  wchar_t *wpath = yk__utf8_to_utf16_null_terminated(path);
  if (wpath == NULL) { return NULL; }
  *error = 0;
#if defined(_MSC_VER)// MSVC
  FILE *file;
  errno_t openerr = _wfopen_s(&file, wpath, L"rb");
  if (0 != openerr) {
    free(wpath);
    if (NULL != file) { fclose(file); }
    *error = YK__BHALIB_ERROR_NO_OPEN;
    return NULL;
  }
#else
  FILE *file = _wfopen(wpath, L"rb");
  if (file == NULL) {
    free(wpath);
    *error = YK__BHALIB_ERROR_NO_OPEN;
    return NULL;
  }
#endif
  fseek(file, 0L, SEEK_END);
  *length = ftell(file);
  rewind(file);
  char *buffer = (char *) yk__bhalib_malloc(*length + 1);
  if (buffer == NULL) {
    free(wpath);
    fclose(file);
    *error = YK__BHALIB_ERROR_NO_MEM;
    return NULL;
  }
  size_t bytes_read = fread(buffer, sizeof(char), *length, file);
  if (bytes_read < *length) {
    free(wpath);
    fclose(file);
    yk__bhalib_free(buffer);
    *error = YK__BHALIB_ERROR_NO_READ;
    return NULL;
  }
  buffer[bytes_read] = '\0';
  free(wpath);
  fclose(file);
  return buffer;
}
#endif
yk__sds yk__io_readfile(yk__sds name) {
  size_t ln;
  int err;
#if defined(_WIN32) || defined(_WIN64)
  char *out = yk__windows_read_file(name, &ln, &err);
#else
  char *out = yk__bhalib_read_file(name, &ln, &err);
#endif
  yk__sdsfree(name);// clean up filename as it will be copied
  if (err == 0) {
    yk__sds tmp = yk__sdsnewlen(out, ln);
    yk__bhalib_free(out);
    return tmp;
  }
  return yk__sdsempty();
}
bool yk__io_writefile(yk__sds fpath, yk__sds data) {
#if defined(_WIN32) || defined(_WIN64)
  wchar_t *wpath = yk__utf8_to_utf16_null_terminated(fpath);
  if (wpath == NULL) {
    yk__sdsfree(fpath);
    yk__sdsfree(data);
    return false;
  }
#if defined(_MSC_VER)// MSVC
  FILE *file;
  errno_t openerr = _wfopen_s(&file, wpath, L"wb+");
  if (0 != openerr) {
    if (NULL != file) { fclose(file); }
    free(wpath);
    yk__sdsfree(fpath);
    yk__sdsfree(data);
    return false;
  }
#else // GCC, MingW, etc
  FILE *file = _wfopen(wpath, L"wb+");
  if (file == NULL) {
    free(wpath);
    yk__sdsfree(fpath);
    yk__sdsfree(data);
    return false;
  }
#endif// msvc check
#else // not windows
  FILE *file = fopen(fpath, "wb+");
  if (file == NULL) {
    yk__sdsfree(fpath);
    yk__sdsfree(data);
    return false;
  }
#endif// unix / windows check
  size_t written = fwrite(data, sizeof(char), yk__sdslen(data), file);
  bool fully_written = (written == yk__sdslen(data));
#if defined(_WIN32) || defined(_WIN64)
  free(wpath);
#endif
  yk__sdsfree(fpath);
  yk__sdsfree(data);
  fclose(file);
  return fully_written;
}
#if !defined(YAKSHA__WASM_BUILD)
#include "_include_io.c"
#if defined(_WIN32) || defined(_WIN64)
#include "_include_mman_win.c"
#endif
#endif
