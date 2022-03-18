#if !defined(YK__PROCESS)
#define YK__PROCESS
// Note this char* assumed to be yk__sds, so do not pass in without wrapping up first.
char *yk__run(char **args);
#endif// YK__PROCESS