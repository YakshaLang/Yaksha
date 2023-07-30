// ============================================================================
/**
 * All in one CPP file for Yaksha
 * Wraps - compiler, dump, viz, reload, lisp commands
 */
#include "utilities/colours.h"
// ============================================================================
// compiler_main(int: argc, char** argv)
#define PROGRAM_NAME "yaksha compile"
#define main compiler_main
#include "comp_main.cpp"
#undef main
#undef PROGRAM_NAME
// dump_main(int: argc, char** argv)
#define PROGRAM_NAME "yaksha dump"
#define main dump_main
#include "dump.cpp"
#undef main
#undef PROGRAM_NAME
// reloader_main(int: argc, char** argv)
#define PROGRAM_NAME "yaksha reload"
#define main reloader_main
#if !defined(_MSC_VER) && (defined(_WIN32) || defined(_WIN64))
#include "reloader_alt.cpp"
#else
#include "reloader.cpp"
#endif
#undef main
#undef PROGRAM_NAME
// viz_main(int: argc, char** argv)
#define PROGRAM_NAME "yaksha viz"
#define main viz_main
#include "viz_main.cpp"
#undef main
#undef PROGRAM_NAME
// lisp_main(int: argc, char** argv)
#define PROGRAM_NAME "yaksha lisp"
#define main lisp_main
#include "lisp_main.cpp"
#undef main
#undef PROGRAM_NAME
// html_gen_main(int: argc, char** argv)
#define PROGRAM_NAME "htmlgen"
#define main htmlgen_main
#include "html_gen.cpp"
#undef main
#undef PROGRAM_NAME
int execute_carpntr(int argc, char **arguments);
// -------- Yaksha C API ---------
extern "C" {
struct yk_compile_result {
  char *output;
  size_t length;
  int success;
};
yk_compile_result compile(char *main_file, size_t main_file_len,
                          char *library_path, size_t library_path_len) {
  yaksha::multifile_compiler mc{};
  yaksha::multifile_compiler_result result;
  std::string main_file_str{main_file, main_file_len};
  std::string lib_path_str{library_path, library_path_len};
  result = mc.compile(main_file_str, lib_path_str);
  // ---
  char *compile_result = nullptr;
  if (!result.failed_) {
    compile_result = static_cast<char *>(malloc(result.code_.size() + 1));
    if (compile_result != nullptr) {
      memcpy(compile_result, result.code_.c_str(), result.code_.size());
    }
  }
  return {compile_result, result.code_.size(), compile_result != nullptr};
}
void display_banner() {
  std::cout << colours::red("                                 \n"
                            " __ __ _____ _____     _   _____ \n"
                            "|  |  |  _  |  |  |___| |_|  _  |\n"
                            "|_   _|     |    -|_ -|   |     |\n"
                            "  |_| |__|__|__|__|___|_|_|__|__|\n"
                            "                                 \n"
                            "\n");
}
};
// ------ End of Yaksha C API --------
#ifndef YK_CPP_NO_MAIN
// --- Main ---
void display_help() {
  std::cout << colours::cyan("Usage:\n\n");
  std::cout << "yaksha compile file_path.yaka [libs_path]\n";
  // TODO add ability to do no-runtime/no-lib compile
  std::cout << colours::green(
      " # Compile a given file (must have main() function), library "
      "path is required if libs are used\n");
  std::cout << "yaksha reload dll_path/dll.so\n";
  std::cout << colours::green(" # Run given hot-reload .dll/.dylib/.so file\n");
  std::cout << "yaksha viz file_path.yaka\n";
  std::cout << colours::green(" # Visualize given file as HTML structure\n");
  std::cout << "yaksha dump file_path.yaka\n";
  std::cout << colours::green(" # Dump structure of the file to JSON\n");
  std::cout << "yaksha htmlgen file_path.yaka\n";
  std::cout << colours::green(" # Generate HTML syntax highlighted code\n");
  std::cout << "yaksha build -R my_code.yaka\n";
  std::cout << colours::green(
      " # Build (and/or run) project/file using carpntr\n");
  std::cout << "yaksha lisp [script.lisp]\n";
  std::cout << colours::green(" # YakshaLisp repl or execute a file\n");
}
int main(int argc, char *argv[]) {
  if (argc <= 1) {
    display_banner();
    std::cerr << "Invalid usage.\n";
    display_help();
    return EXIT_FAILURE;
  }
  const std::string first_arg{argv[1]};
  if (first_arg == "--help") {
    display_banner();
    display_help();
    return EXIT_SUCCESS;
  }
  if (first_arg == "compile") { return compiler_main(argc - 1, &argv[1]); }
  if (first_arg == "reload") { return reloader_main(argc - 1, &argv[1]); }
  if (first_arg == "viz") { return viz_main(argc - 1, &argv[1]); }
  if (first_arg == "dump") { return dump_main(argc - 1, &argv[1]); }
  if (first_arg == "build") { return execute_carpntr(argc - 1, &argv[1]); }
  if (first_arg == "lisp") { return lisp_main(argc - 1, &argv[1]); }
  if (first_arg == "htmlgen") { return htmlgen_main(argc - 1, &argv[1]); }
  display_banner();
  std::cerr << "Invalid sub command.\n";
  display_help();
  return EXIT_FAILURE;
}
#endif
