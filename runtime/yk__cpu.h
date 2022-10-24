#ifndef YK__CPU_H
#define YK__CPU_H
#include <stdbool.h>
#include <stdint.h>
struct yk__cpu_info {
  int32_t n_processors;
  int32_t n_processors_max;
  bool is_guess;
};
struct yk__cpu_info yk__get_cpu_count();
#endif