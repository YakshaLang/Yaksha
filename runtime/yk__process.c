#include "yk__process.h"
#if defined(__linux__) || (defined(__APPLE__) && defined(__MACH__)) ||         \
    defined(__unix__)
// clang-format off
#ifndef _POSIX_C_SOURCE
#define _POSIX_C_SOURCE 200809L
#endif
#include <stdio.h>
#include <unistd.h>
#include "subprocess.h"
#else
#include <stdio.h>
#include <fcntl.h>
#include <io.h>
#include <locale.h>
#include <windows.h>
#include <shellapi.h>
// clang-format on
#endif
#include "yk__system.h"
#if defined(_WIN32) || defined(_WIN64)
// Reference - https://docs.microsoft.com/en-gb/archive/blogs/twistylittlepassagesallalike/everyone-quotes-command-line-arguments-the-wrong-way
bool yk__windows_has_special_chars(yk__sds argument) {
  if (NULL == argument) return false;
  size_t length = yk__sdslen(argument);
  for (size_t i = 0; i < length; i++) {
    char c = argument[i];
    if (c == ' ' || c == '\t' || c == '\n' || c == '\v' || c == '"') {
      return true;
    }
  }
  return false;
}
// Note does not delete argument!
size_t yk__windows_quote_argument(yk__sds argument, yk__sds *output,
                                  bool force) {
  //
  // Unless we're told otherwise, don't quote unless we actually
  // need to do so --- hopefully avoid problems if programs won't
  // parse quotes properly
  //
  size_t input_length = yk__sdslen(argument);
  if (NULL == argument || 0 == input_length) {
    if (NULL != output) { *output = yk__sdsempty(); }
    return 0;
  }
  size_t length = 0;
  if (!yk__windows_has_special_chars(argument) && !force) {
    if (NULL != output) { *output = yk__sdsdup(argument); }
    return yk__sdslen(argument);
  }
#define yk__append(A, B)                                                       \
  do {                                                                         \
    length++;                                                                  \
    if (NULL != (A)) { *(A) = yk__sdscatlen(*(A), (B), 1); }                   \
  } while (0)
#define yk__append_cnt(A, B, count)                                            \
  do {                                                                         \
    length += (count);                                                         \
    if (NULL != (A)) {                                                         \
      for (int x = 0; x < (count); x++) {                                      \
        *(A) = yk__sdscatlen(*(A), (B), 1);                                    \
      }                                                                        \
    }                                                                          \
  } while (0)
  if (NULL != output) { *output = yk__sdsempty(); }
  yk__append(output, "\"");
  for (size_t i = 0; i < input_length; ++i) {
    unsigned NumberBackslashes = 0;
    while (i < input_length && argument[i] == '\\') {
      ++i;
      ++NumberBackslashes;
    }
    if (i == input_length) {
      //
      // Escape all backslashes, but let the terminating
      // double quotation mark we add below be interpreted
      // as a metacharacter.
      //
      yk__append_cnt(output, "\\", NumberBackslashes * 2);
      break;
    } else if (argument[i] == '"') {
      //
      // Escape all backslashes and the following
      // double quotation mark.
      //
      yk__append_cnt(output, "\\", NumberBackslashes * 2 + 1);
      yk__append(output, argument + i);
    } else {
      //
      // Backslashes aren't special here.
      //
      yk__append_cnt(output, "\\", NumberBackslashes);
      yk__append(output, argument + i);
    }
  }
  yk__append(output, "\"");
  return length;
}
yk__sds yk__windows_join_args(yk__sds *args) {
  if (NULL == args) return yk__sdsempty();
  size_t argc = yk__arrlenu(args);
  if (0 == argc) { return yk__sdsempty(); }
  yk__sds output = yk__sdsempty();
  for (size_t i = 0; i < argc; ++i) {
    if (NULL == args[i] || 0 == yk__sdslen(args[i])) { continue; }
    yk__sds converted = NULL;
    size_t converted_count =
        yk__windows_quote_argument(args[i], &converted, false);
    if (0 == converted_count) {
      yk__sdsfree(converted);
      continue;
    }
    if (i != 0) { output = yk__sdscatlen(output, " ", 1); }
    output = yk__sdscatsds(output, converted);
    yk__sdsfree(converted);
  }
  return output;
}
#endif
struct yk__process_result *yk__run(yk__sds *args) {
  struct yk__process_result *res = calloc(1, sizeof(struct yk__process_result));
  res->ok = false;
  res->return_code = -1;
  res->output = NULL;
#if defined(__linux__) || (defined(__APPLE__) && defined(__MACH__)) ||         \
    defined(__unix__)
  if (args == NULL || yk__arrlenu(args) == 0) {
    res->output = yk__sdsempty();
    return res;
  }
  yk__sds* args_copy = NULL;
  size_t args_size = yk__arrlenu(args);
  for (size_t i = 0; i < args_size; i++) {
    yk__arrput(args_copy, args[i]);
  }
  yk__arrput(args_copy, (yk__sds) NULL);
  struct subprocess_s *sub = calloc(1, sizeof(struct subprocess_s));
  int result = subprocess_create((const char *const *) args_copy,
                                 subprocess_option_combined_stdout_stderr |
                                     subprocess_option_inherit_environment |
                                     subprocess_option_no_window,
                                 sub);
  yk__arrfree(args_copy);
  if (0 != result || sub->stdin_file == 0) {
    subprocess_destroy(sub);
    free(sub);
    res->output = yk__sdsempty();
    return res;
  }
  FILE *so = subprocess_stdout(sub);
  if (NULL == so) {
    subprocess_destroy(sub);
    free(sub);
    res->output = yk__sdsempty();
    return res;
  }
  yk__sds text = yk__sdsempty();
  size_t bytes_read;
  char buffer[1024];
  while ((bytes_read = fread(buffer, sizeof(char), 1024, so)) != 0) {
    text = yk__sdscatlen(text, buffer, bytes_read);
  }
  int return_code;
  if (0 != subprocess_join(sub, &return_code)) {
    subprocess_destroy(sub);
    free(sub);
    res->output = text;
    return res;
  }
  // Read left over content after joining..
  while ((bytes_read = fread(buffer, sizeof(char), 1024, so)) != 0) {
    text = yk__sdscatlen(text, buffer, bytes_read);
  }
  subprocess_destroy(sub);
  free(sub);
  res->ok = return_code == 0;
  res->output = text;
  res->return_code = return_code;
  return res;
#else
  yk__sds joined = yk__windows_join_args(args);
  if (NULL == joined) {
    res->output = yk__sdsempty();
    return res;
  }
  wchar_t *cmd = yk__utf8_to_utf16_null_terminated(joined);
  if (NULL == cmd) {     res->output = yk__sdsempty();
    return res; }
  yk__sdsfree(joined);// no longer needed free it.
  yk__sds result = yk__sdsempty();
  HANDLE hPipeRead, hPipeWrite;
  SECURITY_ATTRIBUTES saAttr = {sizeof(SECURITY_ATTRIBUTES)};
  saAttr.bInheritHandle = TRUE;// Pipe handles are inherited by child process.
  saAttr.lpSecurityDescriptor = NULL;
  // Create a pipe to get results from child's stdout.
  if (!CreatePipe(&hPipeRead, &hPipeWrite, &saAttr, 0)) {
    free(cmd);
    res->output = result;
    return res;
  }
  STARTUPINFOW si = {sizeof(STARTUPINFOW)};
  si.dwFlags = STARTF_USESHOWWINDOW | STARTF_USESTDHANDLES;
  si.hStdOutput = hPipeWrite;
  si.hStdError = hPipeWrite;
  si.wShowWindow = SW_HIDE;// Prevents cmd window from flashing.
                           // Requires STARTF_USESHOWWINDOW in dwFlags.
  PROCESS_INFORMATION pi = {0};
  BOOL fSuccess = CreateProcessW(NULL, cmd, NULL, NULL, TRUE,
                                 CREATE_NEW_CONSOLE, NULL, NULL, &si, &pi);
  if (!fSuccess) {
    CloseHandle(hPipeWrite);
    CloseHandle(hPipeRead);
    free(cmd);
    res->output = result;
    return res;
  }
  bool bProcessEnded = false;
  for (; !bProcessEnded;) {
    // Give some timeslice (50 ms), so we won't waste 100% CPU.
    bProcessEnded = WaitForSingleObject(pi.hProcess, 50) == WAIT_OBJECT_0;
    // Even if process exited - we continue reading, if
    // there is some data available over pipe.
    for (;;) {
      char buf[1024];
      DWORD dwRead = 0;
      DWORD dwAvail = 0;
      if (!PeekNamedPipe(hPipeRead, NULL, 0, NULL, &dwAvail, NULL)) break;
      if (!dwAvail)// No data available, return
        break;
#define yk__min(a, b) (a < b ? a : b)
      if (!ReadFile(hPipeRead, buf, yk__min(sizeof(buf) - 1, dwAvail), &dwRead,
                    NULL) ||
          !dwRead)
#undef yk__min
        // Error, the child process might end
        break;
      buf[dwRead] = 0;
      result = yk__sdscatlen(result, buf, dwRead);
    }
  }//for
  // Process exited, get return code.
  DWORD exit_code;
  if (FALSE != GetExitCodeProcess(pi.hProcess, &exit_code)) {
    res->return_code = (int)exit_code;
    res->ok = res->return_code == 0;
  }
  CloseHandle(hPipeWrite);
  CloseHandle(hPipeRead);
  CloseHandle(pi.hProcess);
  CloseHandle(pi.hThread);
  free(cmd);
  res->output = result;
  return res;
#endif
}

void yk__free_process_result(struct yk__process_result* result) {
  if (NULL == result) return;
  yk__sdsfree(result->output);
  free(result);
}