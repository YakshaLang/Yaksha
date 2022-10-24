#if defined(_WIN32) || defined(_WIN64)
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#else
#include <unistd.h>
#endif
#include "yk__cpu.h"
// Reference: https://stackoverflow.com/a/4586990
// Reference: https://lists.gnu.org/archive/html/autoconf/2002-08/msg00126.html
struct yk__cpu_info yk__get_cpu_count() {
  int32_t nprocs = -1;
  int32_t nprocs_max = -1;
  bool guess = false;
#if defined(_WIN32) || defined(_WIN64)
#ifndef _SC_NPROCESSORS_ONLN
  SYSTEM_INFO info;
  GetSystemInfo(&info);
#define sysconf(a) info.dwNumberOfProcessors
#define GET_PROCS
#endif
#endif
#ifdef _SC_NPROCESSORS_ONLN
#define GET_PROCS _SC_NPROCESSORS_ONLN
  nprocs = sysconf(GET_PROCS);
  nprocs_max = sysconf(GET_PROCS);
#endif
  if (nprocs < 1) {
    nprocs = 2;
    guess = true;
  }
  if (nprocs_max < 1) {
    nprocs_max = 2;
    guess = true;
  }
  return (struct yk__cpu_info){nprocs, nprocs_max, guess};
}