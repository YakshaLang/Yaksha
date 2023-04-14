#if !defined(YK__PROCESS)
#define YK__PROCESS
#include <stdbool.h>
struct yk__process_result {
  /**
   * If return code is 0 and we did not encounter any error
   */
  bool ok;
  char *output;
  int return_code;
};
// Note this char* assumed to be yk__sds, so do not pass in without wrapping up first.
struct yk__process_result *yk__run(char **args);
void yk__free_process_result(struct yk__process_result* result);
#endif// YK__PROCESS