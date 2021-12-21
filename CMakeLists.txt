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
        src/ast/ast.h src/ast/ast_printer.h src/ast/ast_vis.h src/ast/environment.h src/ast/interpreter.h src/ast/parser.h src/file_formats/tokens_file.h src/pipeline/pipe.h src/pipeline/pipeline.h src/tokenizer/block_analyzer.h src/tokenizer/string_utils.h src/tokenizer/token.h src/tokenizer/tokenizer.h src/utilities/error_printer.h src/utilities/ykobject.h src/ast/ast.cpp src/ast/ast_printer.cpp src/ast/ast_vis.cpp src/ast/environment.cpp src/ast/interpreter.cpp src/ast/parser.cpp src/file_formats/tokens_file.cpp src/pipeline/pipeline.cpp src/tokenizer/block_analyzer.cpp src/tokenizer/string_utils.cpp src/tokenizer/tokenizer.cpp src/utilities/ykobject.cpp) # update_makefile.py SRC

set(YAKSHA_TEST_FILES
        tests/btest.h tests/test_block_analyzer.cpp tests/test_interpreter.cpp tests/test_string_utils.cpp tests/test_tokenizer.cpp) # update_makefile.py TESTS

add_executable(Yaksha ${YAKSHA_SOURCE_FILES} src/main.cpp)

target_link_libraries(Yaksha ${LIBS})

# Adding Tests
# -----------------------
add_subdirectory(3rd/Catch2) # Add the Catch2 library
# Test executable
add_executable(YakshaTests ${YAKSHA_SOURCE_FILES} ${YAKSHA_TEST_FILES} tests/test_main.cpp)
# #define TESTING
target_compile_definitions(YakshaTests PUBLIC TESTING)
target_link_libraries(YakshaTests PRIVATE Catch2::Catch2)
target_link_libraries(YakshaTests PUBLIC ${LIBS})
# Add to CTest
include(CTest)
include(3rd/Catch2/contrib/Catch.cmake)
catch_discover_tests(YakshaTests)

# Adding Fuzzer Binary
# ---------------------
add_executable(YakshaFuzz ${YAKSHA_SOURCE_FILES} tests/fuzz_main.cpp)
target_link_libraries(YakshaFuzz ${LIBS})
