#if !defined(YK__ARG_PARSE)
#define YK__ARG_PARSE
#include "argparse.h"
#include "yk__arrayutils.h"
struct yk__arg_remainder {
  yk__sds *remainder;
  int argc;
  // Hidden state that we use to delete stuff with
  const char **unreadable_argv;
};
struct yk__arg_remainder *yk__argparse_parse(struct argparse *argparse_obj,
                                             yk__sds *array);
void yk__del_argparse_remainder(struct yk__arg_remainder *remainder);
struct argparse *yk__newargparse(struct argparse_option *options,
                                 yk__sds *usages, int flags);
void yk__delargparse(struct argparse *);
#endif