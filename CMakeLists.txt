cmake_minimum_required(VERSION 3.2)
project(Yaksha)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
set(CMAKE_INSTALL_PREFIX build})
set(UTF8_DIR 3rd/utfcpp/source)

get_filename_component(CMAKE_BINARY_DIR "bin" ABSOLUTE)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

include_directories(src)
include_directories(tests)
include_directories(${UTF8_DIR})

set(YAKSHA_SOURCE_FILES
        src/ast/ast.h src/ast/ast_printer.h src/ast/ast_vis.h src/ast/codefiles.h src/ast/environment.h src/ast/environment_stack.h src/ast/parser.h src/builtins/builtin.h src/builtins/builtins.h src/compiler/compiler.h src/compiler/compiler_utils.h src/compiler/datatype_compiler.h src/compiler/datatype_parser.h src/compiler/def_class_visitor.h src/compiler/delete_stack.h src/compiler/delete_stack_stack.h src/compiler/entry_struct_func_compiler.h src/compiler/multifile_compiler.h src/compiler/slot_matcher.h src/compiler/statement_writer.h src/compiler/type_checker.h src/file_formats/tokens_file.h src/tokenizer/block_analyzer.h src/tokenizer/string_utils.h src/tokenizer/token.h src/tokenizer/tokenizer.h src/utilities/annotation.h src/utilities/annotations.h src/utilities/defer_stack.h src/utilities/defer_stack_stack.h src/utilities/error_printer.h src/utilities/ykdatatype.h src/utilities/ykdt_pool.h src/utilities/ykobject.h src/ast/ast.cpp src/ast/ast_printer.cpp src/ast/ast_vis.cpp src/ast/codefiles.cpp src/ast/environment.cpp src/ast/environment_stack.cpp src/ast/parser.cpp src/builtins/builtins.cpp src/compiler/compiler.cpp src/compiler/compiler_utils.cpp src/compiler/def_class_visitor.cpp src/compiler/delete_stack.cpp src/compiler/delete_stack_stack.cpp src/compiler/entry_struct_func_compiler.cpp src/compiler/multifile_compiler.cpp src/compiler/type_checker.cpp src/file_formats/tokens_file.cpp src/tokenizer/block_analyzer.cpp src/tokenizer/string_utils.cpp src/tokenizer/tokenizer.cpp src/utilities/annotation.cpp src/utilities/annotations.cpp src/utilities/defer_stack.cpp src/utilities/defer_stack_stack.cpp src/utilities/error_printer.cpp src/utilities/ykdatatype.cpp src/utilities/ykdt_pool.cpp src/utilities/ykobject.cpp) # update_makefile.py SRC

set(YAKSHA_TEST_FILES
        tests/btest.h tests/test_block_analyzer.cpp tests/test_compiler.cpp tests/test_parser.cpp tests/test_string_utils.cpp tests/test_tokenizer.cpp tests/test_type_checker.cpp) # update_makefile.py TESTS

include_directories("runtime")
set(YAKSHA_RUNTIME_FILES
        runtime/argparse.h runtime/ini.h runtime/mpc.h runtime/subprocess.h runtime/tinycthread.h runtime/toml.h runtime/utf8proc.h runtime/whereami.h runtime/yk__argparse.h runtime/yk__arrayutils.h runtime/yk__console.h runtime/yk__graphic_utils.h runtime/yk__lib.h runtime/yk__process.h runtime/yk__system.h runtime/yk__utf8iter.h runtime/argparse.c runtime/mpc.c runtime/tinycthread.c runtime/toml.c runtime/utf8proc.c runtime/whereami.c runtime/yk__argparse.c runtime/yk__arrayutils.c runtime/yk__console.c runtime/yk__graphic_utils.c runtime/yk__main.c runtime/yk__process.c runtime/yk__system.c) # update_makefile.py YK_RUNTIME

add_library(yaksha ${YAKSHA_SOURCE_FILES})

# -- yakshac - compiler --
add_executable(yakshac src/comp_main.cpp)
target_link_libraries(yakshac PUBLIC ${LIBS})
target_link_libraries(yakshac PUBLIC yaksha)
target_compile_features(yakshac PRIVATE cxx_std_17)

# -- yakshavz - visualizer --
add_executable(yakshavz src/viz_main.cpp)
target_link_libraries(yakshavz PUBLIC ${LIBS})
target_link_libraries(yakshavz PUBLIC yaksha)
target_compile_features(yakshavz PRIVATE cxx_std_17)

# -- yakshadmp - syntax extractor --
add_executable(yakshadmp src/dump.cpp)
target_link_libraries(yakshadmp PUBLIC ${LIBS})
target_link_libraries(yakshadmp PUBLIC yaksha)
target_compile_features(yakshadmp PRIVATE cxx_std_17)

# -- raylib-parser - raylib-parser --
add_executable(raylib-parser runtime/raylib/parser/raylib_parser.c)

# Adding Tests
# -----------------------
add_subdirectory(3rd/Catch2) # Add the Catch2 library
# Test executable
add_executable(YakshaTests ${YAKSHA_SOURCE_FILES} ${YAKSHA_TEST_FILES} tests/test_main.cpp)
# #define TESTING
target_compile_definitions(YakshaTests PUBLIC TESTING)
target_link_libraries(YakshaTests PRIVATE Catch2::Catch2)
target_link_libraries(YakshaTests PUBLIC ${LIBS})
target_compile_features(YakshaTests PRIVATE cxx_std_17)
# Add to CTest
include(CTest)
include(3rd/Catch2/contrib/Catch.cmake)
catch_discover_tests(YakshaTests)

# Adding Fuzzer Binary
# ---------------------
if(DEFINED ENV{YAKSHA_FUZZ})
    set(CMAKE_CXX_FLAGS "-fsanitize=fuzzer,address -g -O1")
    add_executable(YakshaFuzz ${YAKSHA_SOURCE_FILES}  tests/fuzz_main.cpp)
    target_compile_definitions(YakshaFuzz PUBLIC YAKSHA_LLVM_FUZZ)
else()
    add_executable(YakshaFuzz tests/fuzz_main.cpp)
endif()
target_link_libraries(YakshaFuzz ${LIBS})
target_link_libraries(YakshaFuzz PUBLIC yaksha)
target_compile_features(YakshaFuzz PRIVATE cxx_std_17)

# CMake Build for carpntr
add_compile_options("$<$<C_COMPILER_ID:MSVC>:/utf-8>")
add_compile_options("$<$<CXX_COMPILER_ID:MSVC>:/utf-8>")
add_executable(cmakecarpntr ${YAKSHA_RUNTIME_FILES} carpntr/build/program_code.c)
target_compile_features(cmakecarpntr PRIVATE c_std_99)
target_compile_definitions(cmakecarpntr PUBLIC UTF8PROC_STATIC)
if(UNIX AND NOT APPLE)
    target_link_libraries(cmakecarpntr PUBLIC m)
endif()

