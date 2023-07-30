// cpp_util.h
/**
 * C Preprocessor utilities
 */
#ifndef CPP_UTIL_H
#define CPP_UTIL_H
#include <iostream>
//
// ╦ ╦╔═╗╦╔═╔═╗╦ ╦╔═╗    ╔═╗╔═╗
// ╚╦╝╠═╣╠╩╗╚═╗╠═╣╠═╣    ║ ║╚═╗
//  ╩ ╩ ╩╩ ╩╚═╝╩ ╩╩ ╩────╚═╝╚═╝
#if defined(WIN32) || defined(__WIN32__) || defined(_WIN32) ||                 \
    defined(_WIN64) || defined(_MSC_VER) || defined(__MINGW32__)
#define YAKSHA_OS "WINDOWS"
#define YAKSHA_OS_WINDOWS
#elif defined(__APPLE__)
#define YAKSHA_OS "MACOS"
#define YAKSHA_OS_MACOS
#elif defined(linux) || defined(__linux) || defined(__linux__)
#define YAKSHA_OS "LINUX"
#define YAKSHA_OS_LINUX
#else
#define YAKSHA_OS "UNKNOWN"
#define YAKSHA_OS_UNKNOWN
#endif
#define YAKSHA_DEBUG_LOG(msg)                                                  \
  do {                                                                         \
    std::cout << "// [DEBUG] " << __FILE__ << ":" << __LINE__ << ": " << msg   \
              << std::endl;                                                    \
  } while (0)
//
// ╦ ╦╔═╗╦╔═╔═╗╦ ╦╔═╗    ╔╦╗╔═╗╔╗ ╦ ╦╔═╗
// ╚╦╝╠═╣╠╩╗╚═╗╠═╣╠═╣     ║║║╣ ╠╩╗║ ║║ ╦
//  ╩ ╩ ╩╩ ╩╚═╝╩ ╩╩ ╩────═╩╝╚═╝╚═╝╚═╝╚═╝
//
//// ---- less verbose during tests
#ifndef YAKSHA_FAST_TESTS
#define YAKSHA_FAST_TESTS
#endif
//// ---- debug gc pool
//#ifndef GC_POOL_DEBUG
//#define GC_POOL_DEBUG
//#endif
//// ---- print lisp data types differently (make certain tests fail)
//#ifndef YASKSHA_LISP_PRINT_TYPE
//#define YASKSHA_LISP_PRINT_TYPE
//#endif
//// ---- testing and error capturing mode enabled
#ifndef YAKSHA_TESTING
#define YAKSHA_TESTING
#endif
//// ---- yaksha compiler steps are debugged
//#ifndef YAKSHA_DEBUG_COMPILE
//#define YAKSHA_DEBUG_COMPILE
//#endif
//// ---- yaksha high level debug enabled if we are in possible debug mode
//#define YAKSHA_DEBUG
#if !defined(YAKSHA_DEBUG) &&                                                  \
    (defined(DEBUG) || defined(_DEBUG) || !defined(NDEBUG)) &&                 \
    !defined(YAKSHA_FAST_TESTS)
#define YAKSHA_DEBUG
#endif
// -----------------------
// ------------- debug logs for compiling ---------
#ifdef YAKSHA_DEBUG_COMPILE
#define LOG_COMP(msg) YAKSHA_DEBUG_LOG("[COMP] " << msg)
#else
#define LOG_COMP(msg)
#endif
#endif
