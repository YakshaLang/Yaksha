cmake_minimum_required(VERSION 3.2)
project(Yaksha)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")

set(CMAKE_INSTALL_PREFIX "build")

# Path to UTFCpp source
set(UTF8_DIR 3rd/utfcpp/source)

get_filename_component(CMAKE_BINARY_DIR "bin" ABSOLUTE)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

include_directories(src)
include_directories(tests)
include_directories(${UTF8_DIR})

set(YAKSHA_SOURCE_FILES
        src/tokenizer/token.h
        src/tokenizer/parsing_error.cpp)
set(YAKSHA_TEST_FILES
        tests/test_tokenizer.cpp)

# -- Main library --
add_library(yaksha ${YAKSHA_SOURCE_FILES})

# -- Main binary --
add_executable(Yaksha src/main.cpp)
target_link_libraries(Yaksha PUBLIC yaksha)

# -- Test binary --
add_subdirectory(3rd/Catch2)
add_executable(YakshaTests ${YAKSHA_TEST_FILES} tests/test_main.cpp)
target_link_libraries(YakshaTests PUBLIC yaksha)
target_compile_definitions(YakshaTests PUBLIC TESTING)
target_link_libraries(YakshaTests PRIVATE Catch2::Catch2)
# Adding tests to CTest
include(CTest)
include(3rd/Catch2/contrib/Catch.cmake) # This is needed to discover
catch_discover_tests(YakshaTests)

# -- Fuzz binary --
add_executable(YakshaFuzz tests/fuzz_main.cpp)
target_link_libraries(YakshaFuzz PUBLIC yaksha)



