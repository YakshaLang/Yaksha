#include <filesystem>
#include <iostream>
#ifndef PROGRAM_NAME
#define PROGRAM_NAME "ykreload"
#endif
#include <windows.h>
std::string get_exe_path() {
  char rawPathName[MAX_PATH];
  GetModuleFileNameA(NULL, rawPathName, MAX_PATH);
  return {rawPathName};
}
int execute_program(LPCSTR lpApplicationName, LPSTR arg) {
  // additional information
  STARTUPINFOA si;
  PROCESS_INFORMATION pi;
  DWORD exit_code;
  // set the size of the structures
  ZeroMemory(&si, sizeof(si));
  si.cb = sizeof(si);
  ZeroMemory(&pi, sizeof(pi));
  // start the program up
  if (!CreateProcessA(lpApplicationName,// the path
                      arg,              // Command line
                      NULL,             // Process handle not inheritable
                      NULL,             // Thread handle not inheritable
                      FALSE,            // Set handle inheritance to FALSE
                      0,                // No configuration
                      NULL,             // Use parent's environment block
                      NULL,             // Use parent's starting directory
                      &si,              // Pointer to STARTUPINFO structure
                      &pi// Pointer to PROCESS_INFORMATION structure
                      )) {
    return -1;
  }
  WaitForSingleObject(pi.hProcess, INFINITE);
  GetExitCodeProcess(pi.hProcess, &exit_code);
  // Close process and thread handles.
  CloseHandle(pi.hProcess);
  CloseHandle(pi.hThread);
  return (int) exit_code;
}
int main(int argc, char *argv[]) {
  if (argc != 2) {
    std::cerr << "Invalid usage. Use as: " << PROGRAM_NAME << " libgame.so"
              << std::endl;
    return -1;
  }
  auto reloader = std::filesystem::path(get_exe_path()) / "ykreload.exe";
  auto argument = std::string("\"") + argv[1] + "\"";
  auto cstr = std::make_unique<char[]>(argument.length() + 1);
  strcpy(cstr.get(), argument.c_str());
  return execute_program(reinterpret_cast<LPCSTR>(reloader.c_str()),
                         cstr.get());
}
