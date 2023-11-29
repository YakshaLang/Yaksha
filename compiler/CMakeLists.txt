cmake_minimum_required(VERSION 3.2)
project(Yaksha)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
set(CMAKE_INSTALL_PREFIX build})
set(UTF8_DIR 3rd/utfcpp/source)
set(REPROC_DIR 3rd/reproc)

get_filename_component(CMAKE_BINARY_DIR "bin" ABSOLUTE)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

file(COPY ${CMAKE_BINARY_DIR}/test.txt
        DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
file(COPY ${CMAKE_BINARY_DIR}/test.txt
        DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
include_directories(src)
include_directories(tests)
include_directories(${UTF8_DIR})
include_directories(${REPROC_DIR}/reproc/include)
include_directories(${REPROC_DIR}/reproc++/include)
# Add reproc
set(REPROC++ ON)
add_subdirectory(${REPROC_DIR})

## Enable below to use address sanitizer
# add_compile_options(-O1 -g -fsanitize=address -fno-omit-frame-pointer)
# add_link_options(-g -fsanitize=address)

## Enable below to use undefined behaviour sanitizer
# add_compile_options(-O1 -g -fsanitize=undefined -fsanitize=integer -fsanitize=nullability -fno-omit-frame-pointer)
# add_link_options(-g -fsanitize=undefined -fsanitize=integer -fsanitize=nullability)

set(YAKSHA_SOURCE_FILES
        src/ast/ast.h src/ast/ast_printer.h src/ast/ast_vis.h src/ast/codefiles.h src/ast/environment.h src/ast/environment_stack.h src/ast/parser.h src/builtins/builtin.h src/builtins/builtins.h src/compiler/compiler.h src/compiler/compiler_utils.h src/compiler/datatype_compiler.h src/compiler/datatype_parser.h src/compiler/def_class_visitor.h src/compiler/delete_stack.h src/compiler/delete_stack_stack.h src/compiler/desugaring_compiler.h src/compiler/entry_struct_func_compiler.h src/compiler/function_datatype_extractor.h src/compiler/multifile_compiler.h src/compiler/return_checker.h src/compiler/slot_matcher.h src/compiler/statement_writer.h src/compiler/type_checker.h src/compiler/usage_analyser.h src/file_formats/ic_tokens_file.h src/file_formats/tokens_file.h src/ic2c/ic2c.h src/ic2c/ic_ast.h src/ic2c/ic_compiler.h src/ic2c/ic_level2_parser.h src/ic2c/ic_level2_tokenizer.h src/ic2c/ic_line_splicer.h src/ic2c/ic_optimizer.h src/ic2c/ic_parser.h src/ic2c/ic_peek_ahead_iter.h src/ic2c/ic_preprocessor.h src/ic2c/ic_simple_character_iter.h src/ic2c/ic_token.h src/ic2c/ic_tokenizer.h src/ic2c/ic_trigraph_translater.h src/tokenizer/block_analyzer.h src/tokenizer/string_utils.h src/tokenizer/token.h src/tokenizer/tokenizer.h src/utilities/annotation.h src/utilities/annotations.h src/utilities/colours.h src/utilities/cpp_util.h src/utilities/defer_stack.h src/utilities/defer_stack_stack.h src/utilities/error_printer.h src/utilities/gc_pool.h src/utilities/human_id.h src/utilities/ykdatatype.h src/utilities/ykdt_pool.h src/utilities/ykobject.h src/yaksha_lisp/macro_processor.h src/yaksha_lisp/prelude.h src/yaksha_lisp/yaksha_lisp.h src/yaksha_lisp/yaksha_lisp_builtins.h src/ast/ast.cpp src/ast/ast_printer.cpp src/ast/ast_vis.cpp src/ast/codefiles.cpp src/ast/environment.cpp src/ast/environment_stack.cpp src/ast/parser.cpp src/builtins/builtins.cpp src/compiler/compiler.cpp src/compiler/compiler_utils.cpp src/compiler/def_class_visitor.cpp src/compiler/delete_stack.cpp src/compiler/delete_stack_stack.cpp src/compiler/desugaring_compiler.cpp src/compiler/entry_struct_func_compiler.cpp src/compiler/multifile_compiler.cpp src/compiler/return_checker.cpp src/compiler/type_checker.cpp src/compiler/usage_analyser.cpp src/file_formats/ic_tokens_file.cpp src/file_formats/tokens_file.cpp src/ic2c/ic2c.cpp src/ic2c/ic_ast.cpp src/ic2c/ic_compiler.cpp src/ic2c/ic_level2_parser.cpp src/ic2c/ic_level2_tokenizer.cpp src/ic2c/ic_line_splicer.cpp src/ic2c/ic_optimizer.cpp src/ic2c/ic_parser.cpp src/ic2c/ic_peek_ahead_iter.cpp src/ic2c/ic_preprocessor.cpp src/ic2c/ic_tokenizer.cpp src/ic2c/ic_trigraph_translater.cpp src/tokenizer/block_analyzer.cpp src/tokenizer/string_utils.cpp src/tokenizer/tokenizer.cpp src/utilities/annotation.cpp src/utilities/annotations.cpp src/utilities/colours.cpp src/utilities/cpp_util.cpp src/utilities/defer_stack.cpp src/utilities/defer_stack_stack.cpp src/utilities/error_printer.cpp src/utilities/human_id.cpp src/utilities/ykdatatype.cpp src/utilities/ykdt_pool.cpp src/utilities/ykobject.cpp src/yaksha_lisp/yaksha_lisp.cpp src/yaksha_lisp/yaksha_lisp_builtins.cpp) # update_makefile.py SRC

set(YAKSHA_TEST_FILES
        tests/btest.h tests/test_block_analyzer.cpp tests/test_compiler.cpp tests/test_gc_pool.cpp tests/test_ic_tokenizer.cpp tests/test_parser.cpp tests/test_string_utils.cpp tests/test_tokenizer.cpp tests/test_type_checker.cpp tests/test_yaksha_lisp.cpp) # update_makefile.py TESTS

include_directories("runtime")
set(YAKSHA_RUNTIME_FILES
        runtime/_include_bstr.h runtime/_include_io.h runtime/_include_mman_win.h runtime/argparse.h runtime/cr.h runtime/cr_userdata.h runtime/endianness.h runtime/ini.h runtime/stmmr.h runtime/subprocess.h runtime/tinycthread.h runtime/toml.h runtime/utf8proc.h runtime/wasm4.h runtime/whereami.h runtime/yk__argparse.h runtime/yk__arrayutils.h runtime/yk__console.h runtime/yk__cpu.h runtime/yk__graphic_utils.h runtime/yk__lib.h runtime/yk__process.h runtime/yk__system.h runtime/yk__utf8iter.h runtime/yk__wasm4_libc.h runtime/argparse.c runtime/tinycthread.c runtime/toml.c runtime/utf8proc.c runtime/whereami.c runtime/yk__argparse.c runtime/yk__arrayutils.c runtime/yk__console.c runtime/yk__cpu.c runtime/yk__graphic_utils.c runtime/yk__main.c runtime/yk__process.c runtime/yk__system.c) # update_makefile.py YK_RUNTIME

add_library(library_yaksha ${YAKSHA_SOURCE_FILES})

if(UNIX AND NOT APPLE)
    list(APPEND SYS_LIBS m dl pthread)
endif()

# -- yakshac - compiler --
add_executable(yakshac src/comp_main.cpp runtime/whereami.c)
target_link_libraries(yakshac PUBLIC ${SYS_LIBS})
target_link_libraries(yakshac PUBLIC library_yaksha)
target_link_libraries(yakshac PUBLIC reproc)
target_link_libraries(yakshac PUBLIC reproc++)
target_compile_features(yakshac PRIVATE cxx_std_17)

# -- yakshavz - visualizer --
add_executable(yakshavz src/viz_main.cpp)
target_link_libraries(yakshavz PUBLIC ${SYS_LIBS})
target_link_libraries(yakshavz PUBLIC library_yaksha)
target_compile_features(yakshavz PRIVATE cxx_std_17)
target_link_libraries(yakshavz PUBLIC reproc)
target_link_libraries(yakshavz PUBLIC reproc++)


# -- yakshadmp - syntax extractor --
add_executable(yakshadmp src/dump.cpp)
target_link_libraries(yakshadmp PUBLIC ${SYS_LIBS})
target_link_libraries(yakshadmp PUBLIC library_yaksha)
target_compile_features(yakshadmp PRIVATE cxx_std_17)
target_link_libraries(yakshadmp PUBLIC reproc++)


# -- ykreload - compiler --
if(MSVC)
add_executable(ykreload src/reloader.cpp)
target_compile_features(yakshac PRIVATE cxx_std_17)
endif (MSVC)

# -- yaksha binary --
add_executable(yaksha src/yk.cpp src/carpntr_wrapper.cpp runtime/whereami.c)
target_link_libraries(yaksha PUBLIC ${SYS_LIBS})
target_link_libraries(yaksha PUBLIC library_yaksha)
target_link_libraries(yaksha PUBLIC reproc)
target_link_libraries(yaksha PUBLIC reproc++)
target_compile_features(yaksha PRIVATE cxx_std_17)

# -- raylib-parser - raylib-parser --
add_executable(raylib-parser runtime/raylib/parser/raylib_parser.c)

# Adding Tests
# -----------------------
add_subdirectory(3rd/Catch2) # Add the Catch2 library
# Test executable
add_executable(YakshaTests ${YAKSHA_SOURCE_FILES} ${YAKSHA_TEST_FILES} tests/test_main.cpp runtime/whereami.c)
# #define TESTING
target_compile_definitions(YakshaTests PUBLIC TESTING)
target_link_libraries(YakshaTests PRIVATE Catch2::Catch2)
target_link_libraries(YakshaTests PUBLIC ${SYS_LIBS})
target_link_libraries(YakshaTests PUBLIC reproc)
target_link_libraries(YakshaTests PUBLIC reproc++)
target_compile_features(YakshaTests PRIVATE cxx_std_17)
# Add to CTest
include(CTest)
include(3rd/Catch2/contrib/Catch.cmake)
catch_discover_tests(YakshaTests)

# Adding Fuzzer Binary
# ---------------------
if(DEFINED ENV{YAKSHA_FUZZ})
    set(CMAKE_CXX_FLAGS "-fsanitize=fuzzer,address -g -O1")
    add_executable(YakshaFuzz ${YAKSHA_SOURCE_FILES}  tests/fuzz_main.cpp runtime/whereami.c)
    target_compile_definitions(YakshaFuzz PUBLIC YAKSHA_LLVM_FUZZ)
else()
    add_executable(YakshaFuzz tests/fuzz_main.cpp runtime/whereami.c)
endif()
target_link_libraries(YakshaFuzz PUBLIC ${SYS_LIBS})
target_link_libraries(YakshaFuzz PUBLIC reproc)
target_link_libraries(YakshaFuzz PUBLIC reproc++)
target_link_libraries(YakshaFuzz PUBLIC library_yaksha)
target_compile_features(YakshaFuzz PRIVATE cxx_std_17)

# CMake Build for carpntr
add_compile_options("$<$<C_COMPILER_ID:MSVC>:/utf-8>")
add_compile_options("$<$<CXX_COMPILER_ID:MSVC>:/utf-8>")
add_executable(cmakecarpntr ${YAKSHA_RUNTIME_FILES} carpntr/build/program_code.c)
target_compile_features(cmakecarpntr PRIVATE c_std_99)
target_compile_definitions(cmakecarpntr PUBLIC UTF8PROC_STATIC)
target_link_libraries(cmakecarpntr PUBLIC ${SYS_LIBS})
