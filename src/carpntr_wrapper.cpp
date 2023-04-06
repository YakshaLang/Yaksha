#if defined(_WIN32) || defined(_WIN64)
#include <windows.h>
#else
// NOTE: These needs to be properly wrapped like we do for Yaksha runtime
// Better to just use these for unix for now
#include "../runtime/subprocess.h"
#include "../runtime/whereami.h"
#endif
#include <cstdlib>
#include <cstring>
#include <filesystem>
#include <iostream>
#include <string>
static const int ERR_ALLOC = -4;
static const int ERR_CREATE_SUB = -3;
std::string get_my_exe_path();
int execute_process(std::filesystem::path carpntr_path, int argc,
                    char **arguments);
int execute_carpntr(int argc, char **arguments) {
  std::string path_str = get_my_exe_path();
  std::filesystem::path exe_path{path_str};
  exe_path = std::filesystem::absolute(exe_path);
#if defined(_WIN32) || defined(_WIN64)
  std::filesystem::path carpntr = exe_path.parent_path() / "carpntr.exe";
  if (!std::filesystem::exists(carpntr)) {
    carpntr = exe_path.parent_path() / "cmakecarpntr.exe";
  }
#else
  std::filesystem::path carpntr = exe_path.parent_path() / "carpntr";
  if (!std::filesystem::exists(carpntr)) {
    carpntr = exe_path.parent_path() / "cmakecarpntr";
  }
#endif
  int result = execute_process(carpntr, argc, arguments);
  return result;
}
#if defined(_WIN32) || defined(_WIN64)
// https://learn.microsoft.com/en-gb/archive/blogs/twistylittlepassagesallalike/everyone-quotes-command-line-arguments-the-wrong-way
void ArgvQuote(const std::string &Argument, std::string &CommandLine,
               bool Force)
/*++

Routine Description:

    This routine appends the given argument to a command line such
    that CommandLineToArgvW will return the argument string unchanged.
    Arguments in a command line should be separated by spaces; this
    function does not add these spaces.

Arguments:

    Argument - Supplies the argument to encode.

    CommandLine - Supplies the command line to which we append the encoded argument string.

      Force - Supplies an indication of whether we should quote
          the argument even if it does not contain any characters that would
          ordinarily require quoting.

          Return Value:

    None.

    Environment:

    Arbitrary.

    --*/
{
  //
  // Unless we're told otherwise, don't quote unless we actually
  // need to do so --- hopefully avoid problems if programs won't
  // parse quotes properly
  //
  if (!Force && !Argument.empty() &&
      Argument.find_first_of(" \t\n\v\"") == Argument.npos) {
    CommandLine.append(Argument);
  } else {
    CommandLine.push_back('"');
    for (auto It = Argument.begin();; ++It) {
      unsigned NumberBackslashes = 0;
      while (It != Argument.end() && *It == '\\') {
        ++It;
        ++NumberBackslashes;
      }
      if (It == Argument.end()) {
        //
        // Escape all backslashes, but let the terminating
        // double quotation mark we add below be interpreted
        // as a metacharacter.
        //
        CommandLine.append(NumberBackslashes * 2, '\\');
        break;
      } else if (*It == '"') {
        //
        // Escape all backslashes and the following
        // double quotation mark.
        //
        CommandLine.append(NumberBackslashes * 2 + 1, '\\');
        CommandLine.push_back(*It);
      } else {
        //
        // Backslashes aren't special here.
        //
        CommandLine.append(NumberBackslashes, '\\');
        CommandLine.push_back(*It);
      }
    }
    CommandLine.push_back('"');
  }
}
std::string ws2s(const std::wstring &wide) {
  std::string str;
  std::transform(wide.begin(), wide.end(), std::back_inserter(str),
                 [](wchar_t c) { return (char) c; });
  return str;
}
int execute_process(std::filesystem::path carpntr_path, int argc,
                    char **arguments) {
  std::string argument{};
  ArgvQuote(ws2s(carpntr_path.wstring()), argument, false);
  for (int i = 1; i < argc; i++) {
    char *c_arg = arguments[i];
    size_t arg_len = std::strlen(c_arg);
    std::string arg_cpp{c_arg, arg_len};
    argument.push_back(' ');
    ArgvQuote(arg_cpp, argument, false);
  }
  return (int) std::system(argument.c_str());
}
std::string get_my_exe_path() {
  char rawPathName[MAX_PATH];
  GetModuleFileNameA(NULL, rawPathName, MAX_PATH);
  return {rawPathName};
}
#else
#include "../runtime/subprocess.h"
int execute_process(std::filesystem::path carpntr_path, int argc,
                    char **arguments) {
  char **arguments_copy =
      static_cast<char **>(malloc(sizeof(char *) * (argc + 1)));
  if (arguments_copy == nullptr) { return ERR_ALLOC; }
  arguments_copy[argc] = nullptr;
  const std::string &carpntr_path_str = carpntr_path.string();
  arguments_copy[0] = const_cast<char *>(carpntr_path_str.c_str());
  for (int i = 1; i < argc; i++) { arguments_copy[i] = nullptr; }
  for (int i = 1; i < argc; i++) {
    char *argument = arguments[i];
    size_t arg_len = std::strlen(argument);
    char *copy = static_cast<char *>(std::malloc(arg_len + 1));
    if (copy == nullptr) {
      // TODO clean?
      return ERR_ALLOC;
    }
    std::strncpy(copy, argument, arg_len);
    copy[arg_len] = '\0';
    arguments_copy[i] = copy;
  }
  // Now arguments are copied
  // Create subproc
  struct subprocess_s subprocess {};
  int sp_res = subprocess_create(arguments_copy,
                                 subprocess_option_inherit_environment |
                                     subprocess_option_combined_stdout_stderr,
                                 &subprocess);
  if (0 != sp_res) {
    std::cerr << "Failed to create proc \n";
    return ERR_CREATE_SUB;
  }
  int process_return;
  sp_res = subprocess_join(&subprocess, &process_return);
  if (0 != sp_res) {
    std::cerr << "Failed to join proc \n";
    return ERR_CREATE_SUB;
  }
  auto const buffer_size = 4096;
  FILE *ptr = subprocess_stdout(&subprocess);
  if (ptr != nullptr) {
    char str[buffer_size];
    while (fgets(str, buffer_size, ptr) != nullptr) { printf("%s", str); }
  }
  subprocess_destroy(&subprocess);
  // TODO clean
  return process_return;
}
std::string get_my_exe_path() {
  int length = wai_getModulePath(nullptr, 0, nullptr);
  char *path = (char *) malloc(length + 1);
  if (path == nullptr) { return nullptr; }
  wai_getModulePath(path, length, nullptr);
  path[length] = '\0';
  return std::string{path, length};
}
#endif
