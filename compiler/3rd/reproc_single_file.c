#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__)
#define YK_R_OS_WIN
#elif __APPLE__
#define YK_R_OS_MAC
#elif __linux__
#define YK_R_OS_LINUX
#else
#error "Not supported"
#endif

#ifdef YK_R_OS_WIN
#include "reproc/reproc/src/clock.windows.c"
#else
#include "reproc/reproc/src/clock.posix.c"
#endif

#include "reproc/reproc/src/drain.c"


#ifdef YK_R_OS_WIN
#include "reproc/reproc/src/error.windows.c"
#include "reproc/reproc/src/handle.windows.c"
#include "reproc/reproc/src/init.windows.c"
#else
#include "reproc/reproc/src/error.posix.c"
#include "reproc/reproc/src/handle.posix.c"
#include "reproc/reproc/src/init.posix.c"
#endif



#include "reproc/reproc/src/options.c"

#ifdef YK_R_OS_WIN
#include "reproc/reproc/src/pipe.windows.c"
#include "reproc/reproc/src/process.windows.c"
#include "reproc/reproc/src/redirect.windows.c"
#else
#include "reproc/reproc/src/pipe.posix.c"
#include "reproc/reproc/src/process.posix.c"
#include "reproc/reproc/src/redirect.posix.c"
#endif



#include "reproc/reproc/src/redirect.c"
#include "reproc/reproc/src/reproc.c"
#include "reproc/reproc/src/run.c"
#include "reproc/reproc/src/strv.c"


#ifdef YK_R_OS_WIN
#include "reproc/reproc/src/utf.windows.c"
#else
#include "reproc/reproc/src/utf.posix.c"
#endif
