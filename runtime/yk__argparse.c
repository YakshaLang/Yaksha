#include "yk__argparse.h"
struct yk__arg_remainder *yk__argparse_parse(struct argparse *argparse_obj,
                                             yk__sds *array) {
  // Create a ready for destruction
  int argc = yk__arrlen(array);
  const char **argv = NULL;
  argv = malloc(argc * sizeof(yk__sds));
  for (int i = 0; i < argc; i++) { argv[i] = (char *) array[i]; }
  // Parse
  int new_argc = argparse_parse(argparse_obj, argc, argv);
  // Pack to a result
  yk__sds *new_args = NULL;
  for (int i = 0; i < new_argc; i++) {
    yk__sds item = yk__sdsdup((yk__sds) argv[i]);
    yk__arrput(new_args, item);
  }
  struct yk__arg_remainder *result = malloc(sizeof(struct yk__arg_remainder));
  result->argc = new_argc;
  result->remainder = new_args;
  result->unreadable_argv = argv;
  return result;
}
void yk__del_argparse_remainder(struct yk__arg_remainder *remainder) {
  yk__delsdsarray(remainder->remainder);
  free(remainder->unreadable_argv);
  free(remainder);
}
struct yk__argparse_wrapper *yk__newargparse(struct argparse_option *options,
                                 yk__sds *usages, int flags) {
  struct yk__argparse_wrapper *wrapper = malloc(sizeof (struct yk__argparse_wrapper));
  struct argparse *result = malloc(sizeof(struct argparse));
  yk__sds *usages_copy = yk__sdsarraydup(usages);
  yk__arrput(usages_copy, NULL);
  argparse_init(result, options, (const char *const *) usages_copy, flags);
  wrapper->state = result;
  wrapper->usages = usages_copy;
  wrapper->options = options;
  return wrapper;
}
void yk__delargparse(struct yk__argparse_wrapper *a) {
  // Remove usages copy we made
  yk__delsdsarray((yk__sds *) a->usages);
  // Remove option strings (help and long_name)
  size_t length = yk__arrlenu(a->options);
  // Clean up all option help & long_name data
  for (size_t i = 0; i < length; i++) {
    yk__sdsfree((yk__sds) a->options[i].help);
    yk__sdsfree((yk__sds) a->options[i].long_name);
  }
  yk__sdsfree((yk__sds) a->state->description);
  yk__sdsfree((yk__sds) a->state->epilog);
  // Delete malloc
  free(a);
}