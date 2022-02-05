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
        src/ast/ast.h src/ast/ast_printer.h src/ast/ast_vis.h src/ast/environment.h src/ast/environment_stack.h src/ast/interpreter.h src/ast/parser.h src/compiler/compiler.h src/compiler/compiler_utils.h src/compiler/def_visitor.h src/compiler/delete_stack.h src/compiler/delete_stack_stack.h src/compiler/type_checker.h src/file_formats/tokens_file.h src/pipeline/pipe.h src/pipeline/pipeline.h src/tokenizer/block_analyzer.h src/tokenizer/string_utils.h src/tokenizer/token.h src/tokenizer/tokenizer.h src/utilities/defer_stack.h src/utilities/defer_stack_stack.h src/utilities/error_printer.h src/utilities/udfunction.h src/utilities/ykdatatype.h src/utilities/ykdt_pool.h src/utilities/ykfunction.h src/utilities/ykobject.h src/ast/ast.cpp src/ast/ast_printer.cpp src/ast/ast_vis.cpp src/ast/environment.cpp src/ast/environment_stack.cpp src/ast/interpreter.cpp src/ast/parser.cpp src/comp_main.cpp src/compiler/compiler.cpp src/compiler/compiler_utils.cpp src/compiler/def_visitor.cpp src/compiler/delete_stack.cpp src/compiler/delete_stack_stack.cpp src/compiler/type_checker.cpp src/file_formats/tokens_file.cpp src/pipeline/pipeline.cpp src/tokenizer/block_analyzer.cpp src/tokenizer/string_utils.cpp src/tokenizer/tokenizer.cpp src/utilities/defer_stack.cpp src/utilities/defer_stack_stack.cpp src/utilities/udfunction.cpp src/utilities/ykdatatype.cpp src/utilities/ykdt_pool.cpp src/utilities/ykfunction.cpp src/utilities/ykobject.cpp) # update_makefile.py SRC

set(YAKSHA_TEST_FILES
        tests/btest.h tests/test_block_analyzer.cpp tests/test_compiler.cpp tests/test_interpreter.cpp tests/test_string_utils.cpp tests/test_tokenizer.cpp) # update_makefile.py TESTS

add_library(yaksha ${YAKSHA_SOURCE_FILES})
# -- Yaksha executable - interpreter --
add_executable(Yaksha src/main.cpp)

target_link_libraries(Yaksha PUBLIC ${LIBS})
target_link_libraries(Yaksha PUBLIC yaksha)

# -- yakshac - compiler --
# -- Yaksha executable - interpreter --
add_executable(yakshac src/comp_main.cpp)

target_link_libraries(yakshac PUBLIC ${LIBS})
target_link_libraries(yakshac PUBLIC yaksha)

# Adding Tests
# -----------------------
add_subdirectory(3rd/Catch2) # Add the Catch2 library
# Test executable
add_executable(YakshaTests ${YAKSHA_TEST_FILES} tests/test_main.cpp)
# #define TESTING
target_compile_definitions(YakshaTests PUBLIC TESTING)
target_link_libraries(YakshaTests PRIVATE Catch2::Catch2)
target_link_libraries(YakshaTests PUBLIC ${LIBS})
target_link_libraries(YakshaTests PUBLIC yaksha)
# Add to CTest
include(CTest)
include(3rd/Catch2/contrib/Catch.cmake)
catch_discover_tests(YakshaTests)

# Adding Fuzzer Binary
# ---------------------
add_executable(YakshaFuzz tests/fuzz_main.cpp)
target_link_libraries(YakshaFuzz ${LIBS})
target_link_libraries(YakshaFuzz PUBLIC yaksha)
