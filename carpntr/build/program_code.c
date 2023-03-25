#include "yk__system.h"
#include "yk__argparse.h"
#include "argparse.h"
#include "yk__arrayutils.h"
#include "yk__console.h"
#include "yk__cpu.h"
#include "yk__process.h"
#include "tinycthread.h"
#include "toml.h"
#include "whereami.h"
// YK:argparse,arrayutils,console,cpu,process,tinycthread,toml,whereami#
#include "yk__lib.h"
// --forward declarations-- 
int32_t const  yy__mutex_PLAIN = INT32_C(0);
int32_t const  yy__mutex_TIMED = INT32_C(1);
int32_t const  yy__mutex_RECURSIVE = INT32_C(2);
int32_t const  yy__thread_ERROR = INT32_C(0);
int32_t const  yy__thread_SUCCESS = INT32_C(1);
int32_t const  yy__thread_TIMEOUT = INT32_C(2);
int32_t const  yy__thread_BUSY = INT32_C(3);
int32_t const  yy__thread_NOMEM = INT32_C(4);
int32_t const  yy__thread_SLEEP_SUCCES = INT32_C(0);
int32_t const  yy__pool_IMMEDIATE_SHUTDOWN = INT32_C(1);
int32_t const  yy__pool_GRACEFUL_SHUTDOWN = INT32_C(2);
int32_t const  yy__pool_NO_SHUTDOWN = INT32_C(0);
uint8_t const  yy__pool_MAX_THREAD_SIZE = UINT8_C(64);
uint32_t const  yy__pool_MAX_QUEUE_SIZE = UINT32_C(65536);
int32_t const  yy__pool_ERROR_INVALID = INT32_C(10);
int32_t const  yy__pool_ERROR_LOCK_FAILURE = INT32_C(20);
int32_t const  yy__pool_ERROR_QUEUE_FULL = INT32_C(30);
int32_t const  yy__pool_ERROR_SHUTDOWN = INT32_C(40);
int32_t const  yy__pool_ERROR_THREAD_FAILURE = INT32_C(50);
int32_t const  yy__pool_SUCCESS = INT32_C(0);
int32_t const  yy__argparse_ARGPARSE_DEFAULT = INT32_C(0);
int32_t const  yy__argparse_ARGPARSE_STOP_AT_NON_OPTION = INT32_C(1);
int32_t const  yy__argparse_ARGPARSE_IGNORE_UNKNOWN_ARGS = INT32_C(2);
int32_t const  yy__argparse_ARGPARSE_STOP_AT_NON_AND_IGNORE_UNKNWON = INT32_C(3);
int32_t const  yy__console_REWIND = INT32_C(0);
int32_t const  yy__console_RED = INT32_C(1);
int32_t const  yy__console_GREEN = INT32_C(2);
int32_t const  yy__console_WHITE = INT32_C(3);
int32_t const  yy__console_BLUE = INT32_C(4);
int32_t const  yy__console_PURPLE = INT32_C(5);
int32_t const  yy__console_YELLOW = INT32_C(6);
int32_t const  yy__console_CYAN = INT32_C(7);
struct yy__raylib_support_CObject;
struct yy__raylib_support_BuildData;
#define yy__cpu_Cpu struct yk__cpu_info
#define yy__mutex_Mutex mtx_t
#define yy__condition_Condition cnd_t
#define yy__timespec_TimeSpec struct timespec
#define yy__thread_Thread thrd_t
struct yy__pool_ThreadPool;
#define yy__buffer_StringBuffer yk__sds*
struct yy__building_BObject;
struct yy__configuration_CCode;
struct yy__configuration_Project;
struct yy__configuration_Compilation;
struct yy__configuration_Config;
#define yy__argparse_ArgParseRemainder struct yk__arg_remainder*
#define yy__argparse_ArgParse struct argparse*
#define yy__argparse_ArgParseWrapper struct yk__argparse_wrapper*
#define yy__argparse_Option struct argparse_option
#define yy__argparse_opt_group(nn__name) (struct argparse_option) OPT_GROUP(nn__name)
#define yy__console_clear yk__clear
#define yy__toml_Table toml_table_t*
#define yy__toml_TomlArray toml_array_t*
#define yy__toml_valid_table(nn__x) (NULL != nn__x)
#define yy__toml_valid_array(nn__x) (NULL != nn__x)
#define yy__path_mkdir yk__mkdir
#define yy__path_exists yk__exists
#define yy__path_readable yk__readable
#define yy__path_writable yk__writable
#define yy__path_executable yk__executable
#define yy__array_new yk__newsdsarray
#define yy__array_del_str_array yk__delsdsarray
#define yy__array_dup yk__sdsarraydup
#define yy__c_VoidPtr void*
#define yy__c_Size size_t
#define yy__c_CStr char*
#define yy__c_CDouble double
#define yy__c_CBool bool
#define yy__c_CInt int
#define yy__c_CLong long
#define yy__c_CShort short
#define yy__c_CChar char
#define yy__c_CUInt unsigned int
#define yy__c_CULong unsigned long
#define yy__c_CUShort unsigned short
#define yy__c_CUChar unsigned char
#define yy__c_CFloat float
#define yy__c_free free
#define yy__c_calloc calloc
#define yy__c_realloc realloc
#define yy__c_malloc malloc
#define yy__c_itosize(nn__i) ((size_t)nn__i)
#define yy__c_system system
#define yy__c_acos acos
#define yy__c_asin asin
#define yy__c_atan atan
#define yy__c_atan2 atan2
#define yy__c_cos cos
#define yy__c_cosh cosh
#define yy__c_sin sin
#define yy__c_sinh sinh
#define yy__c_tan tan
#define yy__c_tanh tanh
#define yy__c_log log
#define yy__c_log10 log10
#define yy__c_log2 log2
#define yy__c_pow pow
#define yy__c_sqrt sqrt
#define yy__c_ceil ceil
#define yy__c_fabs fabs
#define yy__c_floor floor
#define yy__c_fmod pow
#define yy__c_memcpy memcpy
#define yy__c_memmove memmove
#define yy__c_memset memset
#define yy__c_memcmp memcmp
#define yy__strings_valid_cstr(nn__s) (NULL != nn__s)
#define yy__os_Arguments struct yk__arguments*
#define yy__os_get_args yk__get_args
#define yy__os_ProcessResult struct yk__process_result*
struct yktuple0;
typedef int32_t (*ykfncptr0)(void*);
typedef void (*ykfncptr1)(void*);
struct yy__raylib_support_CObject* yy__raylib_support_fill_arguments(yk__sds, struct yy__raylib_support_CObject*, bool);
struct yy__raylib_support_CObject* yy__raylib_support_fill_web_arguments(yk__sds, struct yy__raylib_support_CObject*);
struct yy__raylib_support_CObject* yy__raylib_support_co(yk__sds, yk__sds, yk__sds, bool, bool);
void yy__raylib_support_del_c_object(struct yy__raylib_support_CObject*);
void yy__raylib_support_del_objects(struct yy__raylib_support_CObject**);
struct yy__raylib_support_CObject** yy__raylib_support_get_objects(yk__sds, yk__sds, yk__sds, yk__sds, bool, bool);
yk__sds* yy__raylib_support_get_external_libs();
yk__sds* yy__raylib_support_get_web_args();
bool yy__raylib_support_produce_object(struct yy__raylib_support_CObject*, struct yy__configuration_Config*, bool);
void yy__raylib_support_build_object(void*);
void yy__raylib_support_build_objects_sequential(struct yy__raylib_support_CObject**, struct yy__configuration_Config*);
void yy__raylib_support_build_objects(struct yy__raylib_support_CObject**, struct yy__configuration_Config*);
yk__sds* yy__raylib_support_get_raylib_args(struct yy__configuration_Config*, yk__sds);
yy__cpu_Cpu yy__cpu_info();
int32_t yy__mutex_init(yy__mutex_Mutex*, int32_t);
void yy__mutex_destroy(yy__mutex_Mutex*);
int32_t yy__mutex_lock(yy__mutex_Mutex*);
int32_t yy__mutex_trylock(yy__mutex_Mutex*);
int32_t yy__mutex_unlock(yy__mutex_Mutex*);
int32_t yy__condition_init(yy__condition_Condition*);
void yy__condition_destroy(yy__condition_Condition*);
int32_t yy__condition_signal(yy__condition_Condition*);
int32_t yy__condition_broadcast(yy__condition_Condition*);
int32_t yy__condition_wait(yy__condition_Condition*, yy__mutex_Mutex*);
int32_t yy__condition_timed_wait(yy__condition_Condition*, yy__mutex_Mutex*, yy__timespec_TimeSpec*);
bool yy__timespec_get_utc_now(yy__timespec_TimeSpec*);
int64_t yy__timespec_compare_ex(yy__timespec_TimeSpec*, yy__timespec_TimeSpec*);
bool yy__timespec_greater(yy__timespec_TimeSpec, yy__timespec_TimeSpec);
bool yy__timespec_lessser(yy__timespec_TimeSpec, yy__timespec_TimeSpec);
bool yy__timespec_equal(yy__timespec_TimeSpec, yy__timespec_TimeSpec);
void yy__timespec_add_nanoseconds(yy__timespec_TimeSpec*, int64_t);
void yy__timespec_add_seconds(yy__timespec_TimeSpec*, int32_t);
yy__timespec_TimeSpec yy__timespec_create();
yy__timespec_TimeSpec yy__timespec_create_ex(int32_t);
yy__timespec_TimeSpec yy__timespec_now();
yy__timespec_TimeSpec yy__timespec_in_future(int32_t);
yy__timespec_TimeSpec yy__timespec_in_future_ex(int32_t, int64_t);
int32_t yy__timespec_get_seconds(yy__timespec_TimeSpec);
int64_t yy__timespec_get_nanoseconds(yy__timespec_TimeSpec);
int32_t yy__thread_create_with_data(yy__thread_Thread*, ykfncptr0, void*);
int32_t yy__thread_create(yy__thread_Thread*, ykfncptr0);
yy__thread_Thread yy__thread_current();
int32_t yy__thread_detach(yy__thread_Thread);
int32_t yy__thread_equal(yy__thread_Thread, yy__thread_Thread);
void yy__thread_exit(int32_t);
int32_t yy__thread_join_with_result(yy__thread_Thread, int32_t*);
int32_t yy__thread_join(yy__thread_Thread);
void yy__thread_yield();
int32_t yy__thread_sleep_ex(yy__timespec_TimeSpec*, yy__timespec_TimeSpec*);
int32_t yy__thread_sleep(int32_t);
struct yy__pool_ThreadPool* yy__pool_create(uint8_t, uint32_t);
int32_t yy__pool_add(struct yy__pool_ThreadPool*, ykfncptr1, void*);
int32_t yy__pool_destroy(struct yy__pool_ThreadPool*, bool);
int32_t yy__pool_internal_del_pool(struct yy__pool_ThreadPool*);
int32_t yy__pool_internal_tpool_work(void*);
yy__buffer_StringBuffer yy__buffer_new();
yy__buffer_StringBuffer yy__buffer_new_size(int32_t);
void yy__buffer_append(yy__buffer_StringBuffer, yk__sds);
void yy__buffer_prepend(yy__buffer_StringBuffer, yk__sds);
yk__sds yy__buffer_to_str(yy__buffer_StringBuffer);
void yy__buffer_join(yy__buffer_StringBuffer, yk__sds*, yk__sds);
void yy__buffer_del_buf(yy__buffer_StringBuffer);
yk__sds yy__building_prepare_code(struct yy__configuration_Config*, yk__sds);
bool yy__building_is_target_macos(yk__sds);
bool yy__building_is_target_windows(yk__sds);
void yy__building_produce_obj_function(void*);
yk__sds yy__building_core_object(yk__sds*, yk__sds, yk__sds, yk__sds, bool, struct yy__building_BObject***);
void yy__building_build_objects_sequential(struct yy__building_BObject**);
void yy__building_build_objects(struct yy__building_BObject**);
void yy__building_cleanup_buildables(struct yy__building_BObject**);
bool yy__building_keep_ray_objects(yk__sds, bool);
yk__sds* yy__building_create_args(struct yy__configuration_Config*, yk__sds, yk__sds, yk__sds, yk__sds*);
int32_t yy__building_build_target(struct yy__configuration_Config*, yk__sds, yk__sds, yk__sds, yk__sds*);
bool yy__building_print_error(yk__sds, int32_t);
int32_t yy__building_build(struct yy__configuration_Config*, yk__sds);
int32_t yy__building_build_simple(struct yy__configuration_Config*, yk__sds);
void yy__configuration_find_runtime_path(struct yy__configuration_Config*);
void yy__configuration_find_libs_path(struct yy__configuration_Config*);
void yy__configuration_find_yaksha_compiler(struct yy__configuration_Config*);
void yy__configuration_find_zig_compiler(struct yy__configuration_Config*);
void yy__configuration_find_emsdk(struct yy__configuration_Config*);
void yy__configuration_find_w4(struct yy__configuration_Config*);
struct yy__configuration_Project* yy__configuration_load_project(yy__toml_Table, struct yy__configuration_Config*);
struct yy__configuration_CCode* yy__configuration_load_c_code(yy__toml_Table, struct yy__configuration_Config*);
struct yy__configuration_Compilation* yy__configuration_load_compilation(yy__toml_Table, struct yy__configuration_Config*);
struct yy__configuration_CCode* yy__configuration_inject_c_code_defaults(struct yy__configuration_CCode*, struct yy__configuration_Config*);
struct yy__configuration_Config* yy__configuration_load_runtime_features(struct yy__configuration_Config*, yk__sds);
struct yy__configuration_Config* yy__configuration_load_config();
struct yy__configuration_Config* yy__configuration_create_adhoc_config(yk__sds, yk__sds, bool, bool, bool, yk__sds, bool, bool);
void yy__configuration_del_config(struct yy__configuration_Config*);
yy__argparse_ArgParseWrapper yy__argparse_new_ex(yy__argparse_Option*, yk__sds*, int32_t);
yy__argparse_ArgParseWrapper yy__argparse_new(yy__argparse_Option*, yk__sds*);
void yy__argparse_set_description(yy__argparse_ArgParse, yk__sds, yk__sds);
void yy__argparse_del_argparse(yy__argparse_ArgParseWrapper);
yy__argparse_ArgParseRemainder yy__argparse_parse(yy__argparse_ArgParse, yk__sds*);
void yy__argparse_usage(yy__argparse_ArgParse);
void yy__argparse_del_remainder(yy__argparse_ArgParseRemainder);
yy__argparse_Option yy__argparse_opt_help();
yy__argparse_Option yy__argparse_opt_boolean(yk__sds, yk__sds, int32_t*, yk__sds);
yy__argparse_Option yy__argparse_opt_string(yk__sds, yk__sds, yy__c_CStr*, yk__sds);
yy__argparse_Option yy__argparse_opt_integer(yk__sds, yk__sds, int32_t*, yk__sds);
yy__argparse_Option yy__argparse_opt_float(yk__sds, yk__sds, float*, yk__sds);
yy__argparse_Option yy__argparse_opt_end();
void yy__console_set_color(int32_t);
int32_t yy__console_getch();
void yy__console_color_print(int32_t, yk__sds);
void yy__console_red(yk__sds);
void yy__console_green(yk__sds);
void yy__console_white(yk__sds);
void yy__console_blue(yk__sds);
void yy__console_purple(yk__sds);
void yy__console_yellow(yk__sds);
void yy__console_cyan(yk__sds);
yk__sds yy__io_readfile(yk__sds);
bool yy__io_writefile(yk__sds, yk__sds);
yy__toml_Table yy__toml_from_str(yk__sds);
yy__toml_Table yy__toml_get_table(yy__toml_Table, yk__sds);
yy__toml_TomlArray yy__toml_get_array(yy__toml_Table, yk__sds);
int32_t yy__toml_array_len(yy__toml_TomlArray);
yk__sds yy__toml_get_string(yy__toml_Table, yk__sds);
yk__sds yy__toml_get_string_default(yy__toml_Table, yk__sds, yk__sds);
bool yy__toml_get_bool(yy__toml_Table, yk__sds);
bool yy__toml_get_bool_default(yy__toml_Table, yk__sds, bool);
int32_t yy__toml_get_int(yy__toml_Table, yk__sds);
int32_t yy__toml_get_int_default(yy__toml_Table, yk__sds, int32_t);
yk__sds yy__toml_string_at(yy__toml_TomlArray, int32_t);
yk__sds yy__toml_string_at_default(yy__toml_TomlArray, int32_t, yk__sds);
bool yy__toml_bool_at(yy__toml_TomlArray, int32_t);
bool yy__toml_bool_at_default(yy__toml_TomlArray, int32_t, bool);
int32_t yy__toml_int_at(yy__toml_TomlArray, int32_t);
int32_t yy__toml_int_at_default(yy__toml_TomlArray, int32_t, int32_t);
yk__sds* yy__toml_get_string_array(yy__toml_Table, yk__sds);
void yy__toml_del_table(yy__toml_Table);
bool yy__path_forward_slash();
bool yy__path_end_with_slash(yk__sds);
bool yy__path_end_with_dot(yk__sds);
yk__sds yy__path_join(yk__sds, yk__sds);
yk__sds yy__path_basename(yk__sds);
yk__sds yy__path_dirname(yk__sds);
yk__sds yy__path_remove_extension(yk__sds);
yk__sds* yy__array_prefix(yk__sds*, yk__sds);
yk__sds* yy__array_suffix(yk__sds*, yk__sds);
yk__sds yy__array_join(yk__sds*, yk__sds);
yk__sds* yy__array_extend(yk__sds*, yk__sds*);
bool yy__c_has_command_processor();
int32_t yy__strings_get_cstr(yy__c_CStr, int32_t);
void yy__strings_set_cstr(yy__c_CStr, int32_t, int32_t);
int32_t yy__strings_get(yk__sds, int32_t);
bool yy__strings_contains(yk__sds, yk__sds);
bool yy__strings_isempty(yk__sds);
bool yy__strings_isempty_cstr(yy__c_CStr);
int32_t yy__strings_ord_cstr(yy__c_CStr);
int32_t yy__strings_ord(yk__sds);
bool yy__strings_startswith(yk__sds, yk__sds);
yk__sds* yy__strings_split(yk__sds, yk__sds);
int32_t yy__strings_find_char(yk__sds, int32_t);
yk__sds yy__strings_from_cstr(yy__c_CStr);
yk__sds yy__strings_from_cstrlen(yy__c_CStr, int32_t);
yk__sds yy__strings_from_cstrlen_after(yy__c_CStr, int32_t, int32_t);
yy__c_CStr yy__strings_null_cstr();
yy__c_CStr yy__strings_to_cstr(yk__sds);
void yy__strings_del_cstr(yy__c_CStr);
void yy__strings_del_str(yy__c_CStr);
yk__sds yy__strings_cut_from(yk__sds, int32_t);
yk__sds yy__strings_mid(yk__sds, int32_t, int32_t);
bool yy__strings_endswith(yk__sds, yk__sds);
yk__sds yy__strings_spaces(int32_t);
yk__sds yy__strings_rpad(yk__sds, int32_t);
yk__sds yy__strings_lpad(yk__sds, int32_t);
yk__sds yy__os_exe();
yk__sds yy__os_exe_path();
yk__sds yy__os_cwd();
yy__os_ProcessResult yy__os_run(yk__sds*);
void yy__os_del_process_result(yy__os_ProcessResult);
bool yy__os_is_windows();
bool yy__os_is_macos();
yk__sds yy__os_getenv(yk__sds);
yk__sds yy__os_which(yk__sds);
yk__sds yy__libs_version();
void yy__print_banner();
void yy__print_errors(yk__sds*);
void yy__printkv(yk__sds, yk__sds);
void yy__print_config(struct yy__configuration_Config*);
int32_t yy__build_from_config(struct yy__configuration_Config*, bool);
int32_t yy__perform_build();
int32_t yy__perform_mini_build(yk__sds, bool, bool, bool, yk__sds, bool, bool, bool, bool);
int32_t yy__handle_args(yy__os_Arguments);
int32_t yy__main();
// --structs-- 
struct yy__raylib_support_CObject {
    yk__sds yy__raylib_support_c_file;
    yk__sds yy__raylib_support_o_file;
    yk__sds yy__raylib_support_base_name;
    yk__sds* yy__raylib_support_args;
};
struct yy__raylib_support_BuildData {
    struct yy__raylib_support_CObject* yy__raylib_support_object_data;
    struct yy__configuration_Config* yy__raylib_support_config;
};
struct yy__pool_ThreadPool {
    yy__mutex_Mutex yy__pool_lock;
    yy__condition_Condition yy__pool_notify;
    yy__thread_Thread* yy__pool_threads;
    struct yktuple0* yy__pool_queue;
    int32_t yy__pool_thread_count;
    int32_t yy__pool_queue_size;
    int32_t yy__pool_head;
    int32_t yy__pool_tail;
    int32_t yy__pool_count;
    int32_t yy__pool_shutdown;
    int32_t yy__pool_started;
};
struct yy__building_BObject {
    yk__sds* yy__building_args;
    yk__sds yy__building_c_file;
    yk__sds yy__building_object_file_path;
    bool yy__building_always_build;
    bool yy__building_print_info;
};
struct yy__configuration_CCode {
    yk__sds* yy__configuration_include_paths;
    yk__sds* yy__configuration_defines;
    yk__sds* yy__configuration_compiler_defines;
    yk__sds* yy__configuration_includes;
    yk__sds* yy__configuration_system_includes;
    yk__sds* yy__configuration_c_code;
    yk__sds* yy__configuration_cpp_code;
    yk__sds* yy__configuration_runtime_feature_defines;
    yk__sds* yy__configuration_runtime_feature_includes;
    yk__sds* yy__configuration_runtime_feature_c_code;
    yk__sds* yy__configuration_runtime_feature_compiler_defines;
};
struct yy__configuration_Project {
    yk__sds yy__configuration_main;
    yk__sds yy__configuration_name;
    yk__sds yy__configuration_author;
};
struct yy__configuration_Compilation {
    bool yy__configuration_override_alloc;
    bool yy__configuration_only_ccode;
    yk__sds yy__configuration_libc;
    yk__sds yy__configuration_compiler;
    yk__sds* yy__configuration_targets;
    bool yy__configuration_raylib;
    bool yy__configuration_raylib_hot_reloading_dll;
    bool yy__configuration_web;
    yk__sds yy__configuration_web_shell;
    bool yy__configuration_wasm4;
    bool yy__configuration_disable_parallel_build;
};
struct yy__configuration_Config {
    yk__sds yy__configuration_runtime_path;
    yk__sds yy__configuration_compiler_path;
    yk__sds yy__configuration_libs_path;
    yk__sds yy__configuration_zig_compiler_path;
    yk__sds yy__configuration_emcc_compiler_path;
    yk__sds yy__configuration_emrun_path;
    yk__sds yy__configuration_w4_path;
    struct yy__configuration_CCode* yy__configuration_c_code;
    struct yy__configuration_Project* yy__configuration_project;
    struct yy__configuration_Compilation* yy__configuration_compilation;
    yk__sds* yy__configuration_errors;
};
struct yktuple0 { ykfncptr1 e1; void* e2; };
// --functions-- 
struct yy__raylib_support_CObject* yy__raylib_support_fill_arguments(yk__sds yy__raylib_support_src_path, struct yy__raylib_support_CObject* yy__raylib_support_c, bool yy__raylib_support_dll) 
{
    yk__sds* yy__raylib_support_args = NULL;
    if (yy__raylib_support_dll)
    {
        yk__sds t__0 = yk__sdsnewlen("-std=gnu99", 10);
        yk__sds t__1 = yk__sdsnewlen("-DPLATFORM_DESKTOP", 18);
        yk__sds t__2 = yk__sdsnewlen("-DGL_SILENCE_DEPRECATION=199309L", 32);
        yk__sds t__3 = yk__sdsnewlen("-fno-sanitize=undefined", 23);
        yk__sds t__4 = yk__sdsnewlen("-Oz", 3);
        yk__sds* t__5 = NULL;
        yk__arrsetcap(t__5, 5);
        yk__arrput(t__5, yk__sdsdup(t__0));
        yk__arrput(t__5, yk__sdsdup(t__1));
        yk__arrput(t__5, yk__sdsdup(t__2));
        yk__arrput(t__5, yk__sdsdup(t__3));
        yk__arrput(t__5, yk__sdsdup(t__4));
        yy__raylib_support_args = t__5;
        yk__sdsfree(t__4);
        yk__sdsfree(t__3);
        yk__sdsfree(t__2);
        yk__sdsfree(t__1);
        yk__sdsfree(t__0);
    }
    else
    {
        yk__sds t__6 = yk__sdsnewlen("-std=gnu99", 10);
        yk__sds t__7 = yk__sdsnewlen("-DPLATFORM_DESKTOP", 18);
        yk__sds t__8 = yk__sdsnewlen("-DGL_SILENCE_DEPRECATION=199309L", 32);
        yk__sds t__9 = yk__sdsnewlen("-fno-sanitize=undefined", 23);
        yk__sds t__10 = yk__sdsnewlen("-O1", 3);
        yk__sds* t__11 = NULL;
        yk__arrsetcap(t__11, 5);
        yk__arrput(t__11, yk__sdsdup(t__6));
        yk__arrput(t__11, yk__sdsdup(t__7));
        yk__arrput(t__11, yk__sdsdup(t__8));
        yk__arrput(t__11, yk__sdsdup(t__9));
        yk__arrput(t__11, yk__sdsdup(t__10));
        yy__raylib_support_args = t__11;
        yk__sdsfree(t__10);
        yk__sdsfree(t__9);
        yk__sdsfree(t__8);
        yk__sdsfree(t__7);
        yk__sdsfree(t__6);
    }
    if (yy__raylib_support_dll)
    {
        yk__sds t__12 = yk__sdsnewlen("-DYK__CR_DLL", 12);
        yk__arrput(yy__raylib_support_args, yk__sdsdup(t__12));
        yk__sdsfree(t__12);
    }
    yk__sds t__13 = yk__sdsnewlen("-I", 2);
    yk__sds t__14 = yk__sdscatsds(yk__sdsdup(t__13), yy__raylib_support_src_path);
    yk__arrput(yy__raylib_support_args, yk__sdsdup(t__14));
    yk__sds t__15 = yk__sdsnewlen("external", 8);
    yk__sds t__16 = yy__path_join(yk__sdsdup(yy__raylib_support_src_path), yk__sdsdup(t__15));
    yk__sds yy__raylib_support_external = yk__sdsdup((t__16));
    yk__sds t__17 = yk__sdsnewlen("glfw", 4);
    yk__sds t__18 = yy__path_join(yk__sdsdup(yy__raylib_support_external), yk__sdsdup(t__17));
    yk__sds yy__raylib_support_glfw = yk__sdsdup((t__18));
    yk__sds t__19 = yk__sdsnewlen("-I", 2);
    yk__sds t__20 = yk__sdsnewlen("include", 7);
    yk__sds t__21 = yy__path_join(yk__sdsdup(yy__raylib_support_glfw), yk__sdsdup(t__20));
    yk__sds t__22 = yk__sdscatsds(yk__sdsdup(t__19), (t__21));
    yk__arrput(yy__raylib_support_args, yk__sdsdup(t__22));
    if (yy__os_is_windows())
    {
        yk__sds t__23 = yk__sdsnewlen("-I", 2);
        yk__sds t__24 = yk__sdsnewlen("deps", 4);
        yk__sds t__25 = yy__path_join(yk__sdsdup(yy__raylib_support_glfw), yk__sdsdup(t__24));
        yk__sds t__26 = yk__sdsnewlen("mingw", 5);
        yk__sds t__27 = yy__path_join(yk__sdsdup((t__25)), yk__sdsdup(t__26));
        yk__sds t__28 = yk__sdscatsds(yk__sdsdup(t__23), (t__27));
        yk__arrput(yy__raylib_support_args, yk__sdsdup(t__28));
        yk__sdsfree(t__28);
        yk__sdsfree(t__27);
        yk__sdsfree(t__26);
        yk__sdsfree(t__25);
        yk__sdsfree(t__24);
        yk__sdsfree(t__23);
    }
    yk__sds t__29 = yk__sdsnewlen("rglfw", 5);
    if ((yy__os_is_macos() && (yk__sdscmp(yy__raylib_support_c->yy__raylib_support_base_name , t__29) == 0)))
    {
        yk__sds t__30 = yk__sdsnewlen("-ObjC", 5);
        yk__arrput(yy__raylib_support_args, yk__sdsdup(t__30));
        yk__sdsfree(t__30);
    }
    if (((! (yy__os_is_macos())) && (! (yy__raylib_support_dll))))
    {
        yk__sds t__31 = yk__sdsnewlen("-flto=full", 10);
        yk__arrput(yy__raylib_support_args, yk__sdsdup(t__31));
        yk__sdsfree(t__31);
    }
    yk__arrput(yy__raylib_support_args, yk__sdsdup(yy__raylib_support_c->yy__raylib_support_c_file));
    yk__sds t__32 = yk__sdsnewlen("-o", 2);
    yk__arrput(yy__raylib_support_args, yk__sdsdup(t__32));
    yk__arrput(yy__raylib_support_args, yk__sdsdup(yy__raylib_support_c->yy__raylib_support_o_file));
    yy__raylib_support_c->yy__raylib_support_args = yy__raylib_support_args;
    struct yy__raylib_support_CObject* t__33 = yy__raylib_support_c;
    yk__sdsfree(t__32);
    yk__sdsfree(t__29);
    yk__sdsfree(t__22);
    yk__sdsfree(t__21);
    yk__sdsfree(t__20);
    yk__sdsfree(t__19);
    yk__sdsfree(yy__raylib_support_glfw);
    yk__sdsfree(t__18);
    yk__sdsfree(t__17);
    yk__sdsfree(yy__raylib_support_external);
    yk__sdsfree(t__16);
    yk__sdsfree(t__15);
    yk__sdsfree(t__14);
    yk__sdsfree(t__13);
    yk__sdsfree(yy__raylib_support_src_path);
    return t__33;
}
struct yy__raylib_support_CObject* yy__raylib_support_fill_web_arguments(yk__sds yy__raylib_support_src_path, struct yy__raylib_support_CObject* yy__raylib_support_c) 
{
    yk__sds t__34 = yk__sdsnewlen("-std=gnu99", 10);
    yk__sds t__35 = yk__sdsnewlen("-DPLATFORM_WEB", 14);
    yk__sds t__36 = yk__sdsnewlen("-DGRAPHICS_API_OPENGL_ES2", 25);
    yk__sds t__37 = yk__sdsnewlen("-Oz", 3);
    yk__sds* t__38 = NULL;
    yk__arrsetcap(t__38, 4);
    yk__arrput(t__38, yk__sdsdup(t__34));
    yk__arrput(t__38, yk__sdsdup(t__35));
    yk__arrput(t__38, yk__sdsdup(t__36));
    yk__arrput(t__38, yk__sdsdup(t__37));
    yk__sds* yy__raylib_support_args = t__38;
    yk__arrput(yy__raylib_support_args, yk__sdsdup(yy__raylib_support_c->yy__raylib_support_c_file));
    yk__sds t__39 = yk__sdsnewlen("-o", 2);
    yk__arrput(yy__raylib_support_args, yk__sdsdup(t__39));
    yk__arrput(yy__raylib_support_args, yk__sdsdup(yy__raylib_support_c->yy__raylib_support_o_file));
    yy__raylib_support_c->yy__raylib_support_args = yy__raylib_support_args;
    struct yy__raylib_support_CObject* t__40 = yy__raylib_support_c;
    yk__sdsfree(t__39);
    yk__sdsfree(t__37);
    yk__sdsfree(t__36);
    yk__sdsfree(t__35);
    yk__sdsfree(t__34);
    yk__sdsfree(yy__raylib_support_src_path);
    return t__40;
}
struct yy__raylib_support_CObject* yy__raylib_support_co(yk__sds yy__raylib_support_filename, yk__sds yy__raylib_support_src_path, yk__sds yy__raylib_support_target_path, bool yy__raylib_support_web, bool yy__raylib_support_dll) 
{
    struct yy__raylib_support_CObject* yy__raylib_support_obj = calloc(1, sizeof(struct yy__raylib_support_CObject));
    yk__sds t__41 = yk__sdsnewlen(".c", 2);
    yk__sds t__42 = yk__sdscatsds(yk__sdsdup(yy__raylib_support_filename), t__41);
    yk__sds t__43 = yy__path_join(yk__sdsdup(yy__raylib_support_src_path), yk__sdsdup(t__42));
    yk__sdsfree(yy__raylib_support_obj->yy__raylib_support_c_file);
    yy__raylib_support_obj->yy__raylib_support_c_file = yk__sdsdup((t__43));
    if (yy__raylib_support_web)
    {
        yk__sds t__44 = yk__sdsnewlen("web-", 4);
        yk__sds t__45 = yk__sdscatsds(yk__sdsdup(t__44), yy__raylib_support_filename);
        yk__sdsfree(yy__raylib_support_obj->yy__raylib_support_base_name);
        yy__raylib_support_obj->yy__raylib_support_base_name = yk__sdsdup(t__45);
        yk__sds t__46 = yk__sdsnewlen(".o", 2);
        yk__sds t__47 = yk__sdscatsds(yk__sdsdup(yy__raylib_support_obj->yy__raylib_support_base_name), t__46);
        yk__sds t__48 = yy__path_join(yk__sdsdup(yy__raylib_support_target_path), yk__sdsdup(t__47));
        yk__sdsfree(yy__raylib_support_obj->yy__raylib_support_o_file);
        yy__raylib_support_obj->yy__raylib_support_o_file = yk__sdsdup((t__48));
        yy__raylib_support_obj = yy__raylib_support_fill_web_arguments(yk__sdsdup(yy__raylib_support_src_path), yy__raylib_support_obj);
        yk__sdsfree(t__48);
        yk__sdsfree(t__47);
        yk__sdsfree(t__46);
        yk__sdsfree(t__45);
        yk__sdsfree(t__44);
    }
    else
    {
        yk__sds t__49 = yk__sdsnewlen("native-", 7);
        yk__sds t__50 = yk__sdscatsds(yk__sdsdup(t__49), yy__raylib_support_filename);
        yk__sdsfree(yy__raylib_support_obj->yy__raylib_support_base_name);
        yy__raylib_support_obj->yy__raylib_support_base_name = yk__sdsdup(t__50);
        yk__sds t__51 = yk__sdsnewlen(".o", 2);
        yk__sds t__52 = yk__sdscatsds(yk__sdsdup(yy__raylib_support_filename), t__51);
        yk__sds t__53 = yy__path_join(yk__sdsdup(yy__raylib_support_target_path), yk__sdsdup(t__52));
        yk__sdsfree(yy__raylib_support_obj->yy__raylib_support_o_file);
        yy__raylib_support_obj->yy__raylib_support_o_file = yk__sdsdup((t__53));
        yy__raylib_support_obj = yy__raylib_support_fill_arguments(yk__sdsdup(yy__raylib_support_src_path), yy__raylib_support_obj, yy__raylib_support_dll);
        yk__sdsfree(t__53);
        yk__sdsfree(t__52);
        yk__sdsfree(t__51);
        yk__sdsfree(t__50);
        yk__sdsfree(t__49);
    }
    struct yy__raylib_support_CObject* t__54 = yy__raylib_support_obj;
    yk__sdsfree(t__43);
    yk__sdsfree(t__42);
    yk__sdsfree(t__41);
    yk__sdsfree(yy__raylib_support_target_path);
    yk__sdsfree(yy__raylib_support_src_path);
    yk__sdsfree(yy__raylib_support_filename);
    return t__54;
}
void yy__raylib_support_del_c_object(struct yy__raylib_support_CObject* yy__raylib_support_c) 
{
    yk__sdsfree(yy__raylib_support_c->yy__raylib_support_c_file);
    yk__sdsfree(yy__raylib_support_c->yy__raylib_support_o_file);
    yk__sdsfree(yy__raylib_support_c->yy__raylib_support_base_name);
    yy__array_del_str_array(yy__raylib_support_c->yy__raylib_support_args);
    free(yy__raylib_support_c);
    return;
}
void yy__raylib_support_del_objects(struct yy__raylib_support_CObject** yy__raylib_support_x) 
{
    if ((yk__arrlen(yy__raylib_support_x) == INT32_C(0)))
    {
        yk__arrfree(yy__raylib_support_x);
        return;
    }
    int32_t yy__raylib_support_pos = INT32_C(0);
    int32_t yy__raylib_support_length = yk__arrlen(yy__raylib_support_x);
    while (1) {
        if (!((yy__raylib_support_pos < yy__raylib_support_length))) { break; } // Check
        // Body of while loop

        {
            yy__raylib_support_del_c_object(yy__raylib_support_x[yy__raylib_support_pos]);
            yy__raylib_support_pos = (yy__raylib_support_pos + INT32_C(1));
        }
    }
    yk__arrfree(yy__raylib_support_x);
    return;
}
struct yy__raylib_support_CObject** yy__raylib_support_get_objects(yk__sds yy__raylib_support_raylib_src_path, yk__sds yy__raylib_support_gui_path, yk__sds yy__raylib_support_extra_path, yk__sds yy__raylib_support_build_path, bool yy__raylib_support_web, bool yy__raylib_support_dll) 
{
    struct yy__raylib_support_CObject** yy__raylib_support_objects = NULL;
    if ((! (yy__raylib_support_web)))
    {
        yk__sds t__55 = yk__sdsnewlen("rglfw", 5);
        yk__arrput(yy__raylib_support_objects, yy__raylib_support_co(yk__sdsdup(t__55), yk__sdsdup(yy__raylib_support_raylib_src_path), yk__sdsdup(yy__raylib_support_build_path), yy__raylib_support_web, yy__raylib_support_dll));
        yk__sdsfree(t__55);
    }
    yk__sds t__56 = yk__sdsnewlen("raudio", 6);
    yk__arrput(yy__raylib_support_objects, yy__raylib_support_co(yk__sdsdup(t__56), yk__sdsdup(yy__raylib_support_raylib_src_path), yk__sdsdup(yy__raylib_support_build_path), yy__raylib_support_web, yy__raylib_support_dll));
    yk__sds t__57 = yk__sdsnewlen("rcore", 5);
    yk__arrput(yy__raylib_support_objects, yy__raylib_support_co(yk__sdsdup(t__57), yk__sdsdup(yy__raylib_support_raylib_src_path), yk__sdsdup(yy__raylib_support_build_path), yy__raylib_support_web, yy__raylib_support_dll));
    yk__sds t__58 = yk__sdsnewlen("rmodels", 7);
    yk__arrput(yy__raylib_support_objects, yy__raylib_support_co(yk__sdsdup(t__58), yk__sdsdup(yy__raylib_support_raylib_src_path), yk__sdsdup(yy__raylib_support_build_path), yy__raylib_support_web, yy__raylib_support_dll));
    yk__sds t__59 = yk__sdsnewlen("rshapes", 7);
    yk__arrput(yy__raylib_support_objects, yy__raylib_support_co(yk__sdsdup(t__59), yk__sdsdup(yy__raylib_support_raylib_src_path), yk__sdsdup(yy__raylib_support_build_path), yy__raylib_support_web, yy__raylib_support_dll));
    yk__sds t__60 = yk__sdsnewlen("rtext", 5);
    yk__arrput(yy__raylib_support_objects, yy__raylib_support_co(yk__sdsdup(t__60), yk__sdsdup(yy__raylib_support_raylib_src_path), yk__sdsdup(yy__raylib_support_build_path), yy__raylib_support_web, yy__raylib_support_dll));
    yk__sds t__61 = yk__sdsnewlen("rtextures", 9);
    yk__arrput(yy__raylib_support_objects, yy__raylib_support_co(yk__sdsdup(t__61), yk__sdsdup(yy__raylib_support_raylib_src_path), yk__sdsdup(yy__raylib_support_build_path), yy__raylib_support_web, yy__raylib_support_dll));
    yk__sds t__62 = yk__sdsnewlen("utils", 5);
    yk__arrput(yy__raylib_support_objects, yy__raylib_support_co(yk__sdsdup(t__62), yk__sdsdup(yy__raylib_support_raylib_src_path), yk__sdsdup(yy__raylib_support_build_path), yy__raylib_support_web, yy__raylib_support_dll));
    yk__sds t__63 = yk__sdsnewlen("rayextras", 9);
    struct yy__raylib_support_CObject* yy__raylib_support_extra = yy__raylib_support_co(yk__sdsdup(t__63), yk__sdsdup(yy__raylib_support_extra_path), yk__sdsdup(yy__raylib_support_build_path), yy__raylib_support_web, yy__raylib_support_dll);
    yk__sds t__64 = yk__sdsnewlen("-I", 2);
    yk__sds t__65 = yk__sdscatsds(yk__sdsdup(t__64), yy__raylib_support_raylib_src_path);
    yk__arrput(yy__raylib_support_extra->yy__raylib_support_args, yk__sdsdup(t__65));
    yk__sds t__66 = yk__sdsnewlen("-I", 2);
    yk__sds t__67 = yk__sdscatsds(yk__sdsdup(t__66), yy__raylib_support_gui_path);
    yk__arrput(yy__raylib_support_extra->yy__raylib_support_args, yk__sdsdup(t__67));
    yk__arrput(yy__raylib_support_objects, yy__raylib_support_extra);
    struct yy__raylib_support_CObject** t__68 = yy__raylib_support_objects;
    yk__sdsfree(t__67);
    yk__sdsfree(t__66);
    yk__sdsfree(t__65);
    yk__sdsfree(t__64);
    yk__sdsfree(t__63);
    yk__sdsfree(t__62);
    yk__sdsfree(t__61);
    yk__sdsfree(t__60);
    yk__sdsfree(t__59);
    yk__sdsfree(t__58);
    yk__sdsfree(t__57);
    yk__sdsfree(t__56);
    yk__sdsfree(yy__raylib_support_build_path);
    yk__sdsfree(yy__raylib_support_extra_path);
    yk__sdsfree(yy__raylib_support_gui_path);
    yk__sdsfree(yy__raylib_support_raylib_src_path);
    return t__68;
}
yk__sds* yy__raylib_support_get_external_libs() 
{
    yk__sds* yy__raylib_support_external_libs = NULL;
    if (yy__os_is_windows())
    {
        yk__sds t__69 = yk__sdsnewlen("-lwinmm", 7);
        yk__sds t__70 = yk__sdsnewlen("-lgdi32", 7);
        yk__sds t__71 = yk__sdsnewlen("-lopengl32", 10);
        yk__sds* t__72 = NULL;
        yk__arrsetcap(t__72, 3);
        yk__arrput(t__72, yk__sdsdup(t__69));
        yk__arrput(t__72, yk__sdsdup(t__70));
        yk__arrput(t__72, yk__sdsdup(t__71));
        yy__raylib_support_external_libs = t__72;
        yk__sdsfree(t__71);
        yk__sdsfree(t__70);
        yk__sdsfree(t__69);
    }
    else
    {
        if (yy__os_is_macos())
        {
            yk__sds t__73 = yk__sdsnewlen("-framework", 10);
            yk__sds t__74 = yk__sdsnewlen("Foundation", 10);
            yk__sds t__75 = yk__sdsnewlen("-framework", 10);
            yk__sds t__76 = yk__sdsnewlen("OpenGL", 6);
            yk__sds t__77 = yk__sdsnewlen("-framework", 10);
            yk__sds t__78 = yk__sdsnewlen("OpenAL", 6);
            yk__sds t__79 = yk__sdsnewlen("-framework", 10);
            yk__sds t__80 = yk__sdsnewlen("IOKit", 5);
            yk__sds t__81 = yk__sdsnewlen("-framework", 10);
            yk__sds t__82 = yk__sdsnewlen("CoreVideo", 9);
            yk__sds t__83 = yk__sdsnewlen("-framework", 10);
            yk__sds t__84 = yk__sdsnewlen("Cocoa", 5);
            yk__sds* t__85 = NULL;
            yk__arrsetcap(t__85, 12);
            yk__arrput(t__85, yk__sdsdup(t__73));
            yk__arrput(t__85, yk__sdsdup(t__74));
            yk__arrput(t__85, yk__sdsdup(t__75));
            yk__arrput(t__85, yk__sdsdup(t__76));
            yk__arrput(t__85, yk__sdsdup(t__77));
            yk__arrput(t__85, yk__sdsdup(t__78));
            yk__arrput(t__85, yk__sdsdup(t__79));
            yk__arrput(t__85, yk__sdsdup(t__80));
            yk__arrput(t__85, yk__sdsdup(t__81));
            yk__arrput(t__85, yk__sdsdup(t__82));
            yk__arrput(t__85, yk__sdsdup(t__83));
            yk__arrput(t__85, yk__sdsdup(t__84));
            yy__raylib_support_external_libs = t__85;
            yk__sdsfree(t__84);
            yk__sdsfree(t__83);
            yk__sdsfree(t__82);
            yk__sdsfree(t__81);
            yk__sdsfree(t__80);
            yk__sdsfree(t__79);
            yk__sdsfree(t__78);
            yk__sdsfree(t__77);
            yk__sdsfree(t__76);
            yk__sdsfree(t__75);
            yk__sdsfree(t__74);
            yk__sdsfree(t__73);
        }
        else
        {
            yk__sds t__86 = yk__sdsnewlen("-lGL", 4);
            yk__sds t__87 = yk__sdsnewlen("-lrt", 4);
            yk__sds t__88 = yk__sdsnewlen("-ldl", 4);
            yk__sds t__89 = yk__sdsnewlen("-lm", 3);
            yk__sds t__90 = yk__sdsnewlen("-lX11", 5);
            yk__sds* t__91 = NULL;
            yk__arrsetcap(t__91, 5);
            yk__arrput(t__91, yk__sdsdup(t__86));
            yk__arrput(t__91, yk__sdsdup(t__87));
            yk__arrput(t__91, yk__sdsdup(t__88));
            yk__arrput(t__91, yk__sdsdup(t__89));
            yk__arrput(t__91, yk__sdsdup(t__90));
            yy__raylib_support_external_libs = t__91;
            yk__sdsfree(t__90);
            yk__sdsfree(t__89);
            yk__sdsfree(t__88);
            yk__sdsfree(t__87);
            yk__sdsfree(t__86);
        }
    }
    yk__sds* t__92 = yy__raylib_support_external_libs;
    return t__92;
}
yk__sds* yy__raylib_support_get_web_args() 
{
    yk__sds t__93 = yk__sdsnewlen("-s", 2);
    yk__sds t__94 = yk__sdsnewlen("USE_GLFW=3", 10);
    yk__sds t__95 = yk__sdsnewlen("-s", 2);
    yk__sds t__96 = yk__sdsnewlen("ASYNCIFY", 8);
    yk__sds t__97 = yk__sdsnewlen("-DPLATFORM_WEB", 14);
    yk__sds* t__98 = NULL;
    yk__arrsetcap(t__98, 5);
    yk__arrput(t__98, yk__sdsdup(t__93));
    yk__arrput(t__98, yk__sdsdup(t__94));
    yk__arrput(t__98, yk__sdsdup(t__95));
    yk__arrput(t__98, yk__sdsdup(t__96));
    yk__arrput(t__98, yk__sdsdup(t__97));
    yk__sds* yy__raylib_support_web_args = t__98;
    yk__sds* t__99 = yy__raylib_support_web_args;
    yk__sdsfree(t__97);
    yk__sdsfree(t__96);
    yk__sdsfree(t__95);
    yk__sdsfree(t__94);
    yk__sdsfree(t__93);
    return t__99;
}
bool yy__raylib_support_produce_object(struct yy__raylib_support_CObject* yy__raylib_support_c, struct yy__configuration_Config* yy__raylib_support_conf, bool yy__raylib_support_print_info) 
{
    if (yy__raylib_support_print_info)
    {
        yk__sds t__100 = yk__sdsnewlen("raylib::", 8);
        yy__console_cyan(yk__sdsdup(t__100));
        yy__console_yellow(yk__sdsdup(yy__raylib_support_c->yy__raylib_support_base_name));
        yk__sds t__101 = yk__sdsnewlen(" := ", 4);
        yy__console_cyan(yk__sdsdup(t__101));
        yk__sdsfree(t__101);
        yk__sdsfree(t__100);
    }
    if (yy__path_readable(yk__sdsdup(yy__raylib_support_c->yy__raylib_support_o_file)))
    {
        if (yy__raylib_support_print_info)
        {
            yk__sds t__102 = yk__sdsnewlen("ok.\n", 4);
            yy__console_green(yk__sdsdup(t__102));
            yk__sdsfree(t__102);
        }
        return true;
    }
    yk__sds* yy__raylib_support_cmd = NULL;
    if (yy__raylib_support_conf->yy__configuration_compilation->yy__configuration_web)
    {
        yk__sds t__103 = yk__sdsnewlen("-c", 2);
        yk__sds t__104 = yk__sdsnewlen("-Oz", 3);
        yk__sds* t__105 = NULL;
        yk__arrsetcap(t__105, 3);
        yk__arrput(t__105, yk__sdsdup(yy__raylib_support_conf->yy__configuration_emcc_compiler_path));
        yk__arrput(t__105, yk__sdsdup(t__103));
        yk__arrput(t__105, yk__sdsdup(t__104));
        yy__raylib_support_cmd = t__105;
        yk__sdsfree(t__104);
        yk__sdsfree(t__103);
    }
    else
    {
        yk__sds t__106 = yk__sdsnewlen("cc", 2);
        yk__sds t__107 = yk__sdsnewlen("-c", 2);
        yk__sds t__108 = yk__sdsnewlen("-Oz", 3);
        yk__sds* t__109 = NULL;
        yk__arrsetcap(t__109, 4);
        yk__arrput(t__109, yk__sdsdup(yy__raylib_support_conf->yy__configuration_zig_compiler_path));
        yk__arrput(t__109, yk__sdsdup(t__106));
        yk__arrput(t__109, yk__sdsdup(t__107));
        yk__arrput(t__109, yk__sdsdup(t__108));
        yy__raylib_support_cmd = t__109;
        yk__sdsfree(t__108);
        yk__sdsfree(t__107);
        yk__sdsfree(t__106);
    }
    yy__raylib_support_cmd = yy__array_extend(yy__raylib_support_cmd, yy__raylib_support_c->yy__raylib_support_args);
    yy__os_ProcessResult yy__raylib_support_pr = yy__os_run(yy__raylib_support_cmd);
    if (yy__raylib_support_pr->ok)
    {
        if (yy__raylib_support_print_info)
        {
            yk__sds t__110 = yk__sdsnewlen("ok.\n", 4);
            yy__console_green(yk__sdsdup(t__110));
            yk__sdsfree(t__110);
        }
        yy__os_del_process_result(yy__raylib_support_pr);
        yy__array_del_str_array(yy__raylib_support_cmd);
        return true;
    }
    if (yy__raylib_support_print_info)
    {
        yk__sds t__111 = yk__sdsnewlen("failed.\n", 8);
        yy__console_red(yk__sdsdup(t__111));
        yk__sds t__112 = yk__sdsnewlen("--c compiler output---\n", 23);
        yy__console_cyan(yk__sdsdup(t__112));
        yk__sds t__113 = yk__sdsnewlen("command := ", 11);
        yy__console_red(yk__sdsdup(t__113));
        yk__sds t__114 = yk__sdsnewlen(" ", 1);
        yk__sds t__115 = yy__array_join(yy__raylib_support_cmd, yk__sdsdup(t__114));
        yk__sds t__116 = yk__sdsnewlen("\n", 1);
        yk__sds t__117 = yk__sdscatsds(yk__sdsdup((t__115)), t__116);
        yy__console_cyan(yk__sdsdup(t__117));
        yy__console_red(yk__sdsdup(yy__raylib_support_pr->output));
        yk__sds t__118 = yk__sdsnewlen("--end c compiler output---\n", 27);
        yy__console_cyan(yk__sdsdup(t__118));
        yk__sdsfree(t__118);
        yk__sdsfree(t__117);
        yk__sdsfree(t__116);
        yk__sdsfree(t__115);
        yk__sdsfree(t__114);
        yk__sdsfree(t__113);
        yk__sdsfree(t__112);
        yk__sdsfree(t__111);
    }
    yy__os_del_process_result(yy__raylib_support_pr);
    yy__array_del_str_array(yy__raylib_support_cmd);
    return false;
}
void yy__raylib_support_build_object(void* yy__raylib_support_arg) 
{
    struct yy__raylib_support_BuildData* yy__raylib_support_data = ((struct yy__raylib_support_BuildData*)yy__raylib_support_arg);
    yy__raylib_support_produce_object(yy__raylib_support_data->yy__raylib_support_object_data, yy__raylib_support_data->yy__raylib_support_config, false);
    return;
}
void yy__raylib_support_build_objects_sequential(struct yy__raylib_support_CObject** yy__raylib_support_objects, struct yy__configuration_Config* yy__raylib_support_conf) 
{
    int32_t yy__raylib_support_object_count = yk__arrlen(yy__raylib_support_objects);
    int32_t yy__raylib_support_pos = INT32_C(0);
    while (1) {
        if (!((yy__raylib_support_pos < yy__raylib_support_object_count))) { break; } // Check
        // Body of while loop

        {
            struct yy__raylib_support_CObject* yy__raylib_support_object = yy__raylib_support_objects[yy__raylib_support_pos];
            yy__raylib_support_produce_object(yy__raylib_support_object, yy__raylib_support_conf, true);
            yy__raylib_support_pos += INT32_C(1);
        }
    }
    return;
}
void yy__raylib_support_build_objects(struct yy__raylib_support_CObject** yy__raylib_support_objects, struct yy__configuration_Config* yy__raylib_support_conf) 
{
    yk__sds t__119 = yk__sdsnewlen("building raylib ...", 19);
    yk__printlnstr((t__119));
    if (yy__raylib_support_conf->yy__configuration_compilation->yy__configuration_disable_parallel_build)
    {
        yy__raylib_support_build_objects_sequential(yy__raylib_support_objects, yy__raylib_support_conf);
        yk__sdsfree(t__119);
        return;
    }
    int32_t yy__raylib_support_object_count = yk__arrlen(yy__raylib_support_objects);
    yy__cpu_Cpu yy__raylib_support_cpu_data = yy__cpu_info();
    uint8_t yy__raylib_support_threads = ((uint8_t)yy__raylib_support_cpu_data.n_processors);
    yy__raylib_support_threads = ((yy__raylib_support_threads > yy__pool_MAX_THREAD_SIZE) ? yy__pool_MAX_THREAD_SIZE : yy__raylib_support_threads);
    struct yy__pool_ThreadPool* yy__raylib_support_tpool = yy__pool_create(yy__raylib_support_threads, ((uint32_t)(yy__raylib_support_object_count + INT32_C(2))));
    if ((yy__raylib_support_tpool == NULL))
    {
        yy__raylib_support_build_objects_sequential(yy__raylib_support_objects, yy__raylib_support_conf);
        yk__sdsfree(t__119);
        return;
    }
    struct yy__raylib_support_BuildData** yy__raylib_support_to_pass = NULL;
    int32_t yy__raylib_support_pos = INT32_C(0);
    while (1) {
        if (!((yy__raylib_support_pos < yy__raylib_support_object_count))) { break; } // Check
        // Body of while loop

        {
            struct yy__raylib_support_CObject* yy__raylib_support_object = yy__raylib_support_objects[yy__raylib_support_pos];
            struct yy__raylib_support_BuildData* yy__raylib_support_data = calloc(1, sizeof(struct yy__raylib_support_BuildData));
            yy__raylib_support_data->yy__raylib_support_object_data = yy__raylib_support_object;
            yy__raylib_support_data->yy__raylib_support_config = yy__raylib_support_conf;
            yk__arrput(yy__raylib_support_to_pass, yy__raylib_support_data);
            yy__pool_add(yy__raylib_support_tpool, yy__raylib_support_build_object, (yy__raylib_support_data));
            yy__raylib_support_pos += INT32_C(1);
        }
    }
    yy__pool_destroy(yy__raylib_support_tpool, true);
    yy__raylib_support_pos = INT32_C(0);
    while (1) {
        if (!((yy__raylib_support_pos < yy__raylib_support_object_count))) { break; } // Check
        // Body of while loop

        {
            free(yy__raylib_support_to_pass[yy__raylib_support_pos]);
            yy__raylib_support_pos += INT32_C(1);
        }
    }
    yk__arrfree(yy__raylib_support_to_pass);
    yk__sdsfree(t__119);
    return;
}
yk__sds* yy__raylib_support_get_raylib_args(struct yy__configuration_Config* yy__raylib_support_conf, yk__sds yy__raylib_support_build_path) 
{
    yk__sds* yy__raylib_support_arguments = NULL;
    yk__sds yy__raylib_support_runtime_path = yk__sdsdup(yy__raylib_support_conf->yy__configuration_runtime_path);
    yy__path_mkdir(yk__sdsdup(yy__raylib_support_build_path));
    yk__sds t__120 = yk__sdsnewlen("raylib", 6);
    yk__sds t__121 = yy__path_join(yk__sdsdup(yy__raylib_support_runtime_path), yk__sdsdup(t__120));
    yk__sds t__122 = yk__sdsnewlen("src", 3);
    yk__sds t__123 = yy__path_join(yk__sdsdup((t__121)), yk__sdsdup(t__122));
    yk__sds yy__raylib_support_raylib_path = yk__sdsdup((t__123));
    yk__sds t__124 = yk__sdsnewlen("raygui", 6);
    yk__sds t__125 = yy__path_join(yk__sdsdup(yy__raylib_support_runtime_path), yk__sdsdup(t__124));
    yk__sds t__126 = yk__sdsnewlen("src", 3);
    yk__sds t__127 = yy__path_join(yk__sdsdup((t__125)), yk__sdsdup(t__126));
    yk__sds yy__raylib_support_raygui_path = yk__sdsdup((t__127));
    yk__sds t__128 = yk__sdsnewlen("raylib_additional", 17);
    yk__sds t__129 = yy__path_join(yk__sdsdup(yy__raylib_support_runtime_path), yk__sdsdup(t__128));
    yk__sds yy__raylib_support_rayextra_path = yk__sdsdup((t__129));
    struct yy__raylib_support_CObject** yy__raylib_support_objects = yy__raylib_support_get_objects(yk__sdsdup(yy__raylib_support_raylib_path), yk__sdsdup(yy__raylib_support_raygui_path), yk__sdsdup(yy__raylib_support_rayextra_path), yk__sdsdup(yy__raylib_support_build_path), yy__raylib_support_conf->yy__configuration_compilation->yy__configuration_web, yy__raylib_support_conf->yy__configuration_compilation->yy__configuration_raylib_hot_reloading_dll);
    yk__sds* yy__raylib_support_o_files = NULL;
    int32_t yy__raylib_support_object_count = yk__arrlen(yy__raylib_support_objects);
    yy__raylib_support_build_objects(yy__raylib_support_objects, yy__raylib_support_conf);
    int32_t yy__raylib_support_pos = INT32_C(0);
    while (1) {
        if (!((yy__raylib_support_pos < yy__raylib_support_object_count))) { break; } // Check
        // Body of while loop

        {
            struct yy__raylib_support_CObject* yy__raylib_support_object = yy__raylib_support_objects[yy__raylib_support_pos];
            yk__arrput(yy__raylib_support_o_files, yk__sdsdup(yy__raylib_support_object->yy__raylib_support_o_file));
            yy__raylib_support_pos += INT32_C(1);
        }
    }
    if (yy__raylib_support_conf->yy__configuration_compilation->yy__configuration_web)
    {
        yy__raylib_support_arguments = yy__raylib_support_get_web_args();
        yy__raylib_support_arguments = yy__array_extend(yy__raylib_support_arguments, yy__raylib_support_o_files);
    }
    else
    {
        yy__raylib_support_arguments = yy__raylib_support_get_external_libs();
        yy__raylib_support_arguments = yy__array_extend(yy__raylib_support_arguments, yy__raylib_support_o_files);
        if (yy__os_is_windows())
        {
            yk__sds t__130 = yk__sdsnewlen("-Wl,--subsystem,windows", 23);
            yk__arrput(yy__raylib_support_arguments, yk__sdsdup(t__130));
            yk__sds t__131 = yk__sdsnewlen("-DYK__WINDOWS_HIDE_CONSOLE", 26);
            yk__arrput(yy__raylib_support_arguments, yk__sdsdup(t__131));
            yk__sdsfree(t__131);
            yk__sdsfree(t__130);
        }
    }
    yk__sds t__132 = yk__sdsnewlen("-I", 2);
    yk__sds t__133 = yk__sdscatsds(yk__sdsdup(t__132), yy__raylib_support_raylib_path);
    yk__arrput(yy__raylib_support_arguments, yk__sdsdup(t__133));
    yk__sds t__134 = yk__sdsnewlen("-I", 2);
    yk__sds t__135 = yk__sdscatsds(yk__sdsdup(t__134), yy__raylib_support_raygui_path);
    yk__arrput(yy__raylib_support_arguments, yk__sdsdup(t__135));
    yk__sds t__136 = yk__sdsnewlen("-I", 2);
    yk__sds t__137 = yk__sdscatsds(yk__sdsdup(t__136), yy__raylib_support_rayextra_path);
    yk__arrput(yy__raylib_support_arguments, yk__sdsdup(t__137));
    yk__sds* t__138 = yy__raylib_support_arguments;
    yy__raylib_support_del_objects(yy__raylib_support_objects);
    yy__array_del_str_array(yy__raylib_support_o_files);
    yk__sdsfree(t__137);
    yk__sdsfree(t__136);
    yk__sdsfree(t__135);
    yk__sdsfree(t__134);
    yk__sdsfree(t__133);
    yk__sdsfree(t__132);
    yk__sdsfree(yy__raylib_support_rayextra_path);
    yk__sdsfree(t__129);
    yk__sdsfree(t__128);
    yk__sdsfree(yy__raylib_support_raygui_path);
    yk__sdsfree(t__127);
    yk__sdsfree(t__126);
    yk__sdsfree(t__125);
    yk__sdsfree(t__124);
    yk__sdsfree(yy__raylib_support_raylib_path);
    yk__sdsfree(t__123);
    yk__sdsfree(t__122);
    yk__sdsfree(t__121);
    yk__sdsfree(t__120);
    yk__sdsfree(yy__raylib_support_runtime_path);
    yk__sdsfree(yy__raylib_support_build_path);
    return t__138;
}
yy__cpu_Cpu yy__cpu_info() { return yk__get_cpu_count(); }
int32_t yy__mutex_init(yy__mutex_Mutex* nn__mtx, int32_t nn__type) { return mtx_init(nn__mtx, nn__type); }
void yy__mutex_destroy(yy__mutex_Mutex* nn__mtx) { mtx_destroy(nn__mtx); }
int32_t yy__mutex_lock(yy__mutex_Mutex* nn__mtx) { return mtx_lock(nn__mtx); }
int32_t yy__mutex_trylock(yy__mutex_Mutex* nn__mtx) { return mtx_trylock(nn__mtx); }
int32_t yy__mutex_unlock(yy__mutex_Mutex* nn__mtx) { return mtx_unlock(nn__mtx); }
int32_t yy__condition_init(yy__condition_Condition* nn__cnd) { return cnd_init(nn__cnd); }
void yy__condition_destroy(yy__condition_Condition* nn__cnd) { cnd_destroy(nn__cnd); }
int32_t yy__condition_signal(yy__condition_Condition* nn__cnd) { return cnd_signal(nn__cnd); }
int32_t yy__condition_broadcast(yy__condition_Condition* nn__cnd) { return cnd_broadcast(nn__cnd); }
int32_t yy__condition_wait(yy__condition_Condition* nn__cnd, yy__mutex_Mutex* nn__mtx) { return cnd_wait(nn__cnd, nn__mtx); }
int32_t yy__condition_timed_wait(yy__condition_Condition* nn__cnd, yy__mutex_Mutex* nn__mtx, yy__timespec_TimeSpec* nn__ts) { return cnd_timedwait(nn__cnd, nn__mtx, nn__ts); }
bool yy__timespec_get_utc_now(yy__timespec_TimeSpec* nn__t) 
{
    return timespec_get(nn__t, TIME_UTC) == TIME_UTC;
}
int64_t yy__timespec_compare_ex(yy__timespec_TimeSpec* nn__a, yy__timespec_TimeSpec* nn__b) 
{
    
    if (nn__a->tv_sec != nn__b->tv_sec) {
        return (nn__a->tv_sec - nn__b->tv_sec);
    } else if (nn__a->tv_nsec != nn__b->tv_nsec) {
        return (nn__a->tv_nsec - nn__b->tv_nsec);
    }
    return 0;
}
bool yy__timespec_greater(yy__timespec_TimeSpec yy__timespec_a, yy__timespec_TimeSpec yy__timespec_b) 
{
    bool t__0 = (yy__timespec_compare_ex((&(yy__timespec_a)), (&(yy__timespec_b))) > ((int64_t)INT32_C(0)));
    return t__0;
}
bool yy__timespec_lessser(yy__timespec_TimeSpec yy__timespec_a, yy__timespec_TimeSpec yy__timespec_b) 
{
    bool t__1 = (yy__timespec_compare_ex((&(yy__timespec_a)), (&(yy__timespec_b))) < ((int64_t)INT32_C(0)));
    return t__1;
}
bool yy__timespec_equal(yy__timespec_TimeSpec yy__timespec_a, yy__timespec_TimeSpec yy__timespec_b) 
{
    bool t__2 = (yy__timespec_compare_ex((&(yy__timespec_a)), (&(yy__timespec_b))) == ((int64_t)INT32_C(0)));
    return t__2;
}
void yy__timespec_add_nanoseconds(yy__timespec_TimeSpec* nn__a, int64_t nn__n) 
{
    
    #define NSECS_PER_SECOND 1000000000
    nn__a->tv_sec += nn__n / NSECS_PER_SECOND;
    nn__a->tv_nsec += nn__n % NSECS_PER_SECOND;
    while (nn__a->tv_nsec >= NSECS_PER_SECOND) {
        nn__a->tv_sec++;
        nn__a->tv_nsec -= NSECS_PER_SECOND;
    }
    #undef NSECS_PER_SECOND
    return;
}
void yy__timespec_add_seconds(yy__timespec_TimeSpec* nn__a, int32_t nn__n) 
{
    nn__a->tv_sec += nn__n;
}
yy__timespec_TimeSpec yy__timespec_create() 
{
    struct timespec t = {0, };
    t.tv_sec = 0;
    t.tv_nsec = 0;
    return t;
}
yy__timespec_TimeSpec yy__timespec_create_ex(int32_t nn__seconds) 
{
    struct timespec t = {0, };
    t.tv_sec = nn__seconds;
    t.tv_nsec = 0;
    return t;
}
yy__timespec_TimeSpec yy__timespec_now() 
{
    yy__timespec_TimeSpec yy__timespec_t = yy__timespec_create();
    yy__timespec_get_utc_now((&(yy__timespec_t)));
    yy__timespec_TimeSpec t__3 = yy__timespec_t;
    return t__3;
}
yy__timespec_TimeSpec yy__timespec_in_future(int32_t yy__timespec_seconds) 
{
    yy__timespec_TimeSpec yy__timespec_t = yy__timespec_create();
    yy__timespec_get_utc_now((&(yy__timespec_t)));
    yy__timespec_add_seconds((&(yy__timespec_t)), yy__timespec_seconds);
    yy__timespec_TimeSpec t__4 = yy__timespec_t;
    return t__4;
}
yy__timespec_TimeSpec yy__timespec_in_future_ex(int32_t yy__timespec_seconds, int64_t yy__timespec_nanoseconds) 
{
    yy__timespec_TimeSpec yy__timespec_t = yy__timespec_create();
    yy__timespec_get_utc_now((&(yy__timespec_t)));
    yy__timespec_add_seconds((&(yy__timespec_t)), yy__timespec_seconds);
    yy__timespec_add_nanoseconds((&(yy__timespec_t)), yy__timespec_nanoseconds);
    yy__timespec_TimeSpec t__5 = yy__timespec_t;
    return t__5;
}
int32_t yy__timespec_get_seconds(yy__timespec_TimeSpec nn__t) 
{
    return nn__t.tv_sec;
}
int64_t yy__timespec_get_nanoseconds(yy__timespec_TimeSpec nn__t) 
{
    return nn__t.tv_nsec;
}
int32_t yy__thread_create_with_data(yy__thread_Thread* nn__thr, ykfncptr0 nn__func, void* nn__data) { return thrd_create(nn__thr, nn__func, nn__data); }
int32_t yy__thread_create(yy__thread_Thread* nn__thr, ykfncptr0 nn__func) 
{
    return thrd_create(nn__thr, nn__func, NULL);
}
yy__thread_Thread yy__thread_current() { return thrd_current(); }
int32_t yy__thread_detach(yy__thread_Thread nn__thr) { return thrd_detach(nn__thr); }
int32_t yy__thread_equal(yy__thread_Thread nn__thr1, yy__thread_Thread nn__thr2) { return thrd_equal(nn__thr1, nn__thr2); }
void yy__thread_exit(int32_t nn__res) { thrd_exit(nn__res); }
int32_t yy__thread_join_with_result(yy__thread_Thread nn__thr, int32_t* nn__res) { return thrd_join(nn__thr, nn__res); }
int32_t yy__thread_join(yy__thread_Thread nn__thr) 
{
    return thrd_join(nn__thr, NULL);
}
void yy__thread_yield() { thrd_yield(); }
int32_t yy__thread_sleep_ex(yy__timespec_TimeSpec* nn__duration, yy__timespec_TimeSpec* nn__remainder) { return thrd_sleep(nn__duration, nn__remainder); }
int32_t yy__thread_sleep(int32_t nn__seconds) 
{
    struct timespec t = {0, };
    t.tv_sec = nn__seconds;
    t.tv_nsec = 0;
    return thrd_sleep(&t, &t);
}
struct yy__pool_ThreadPool* yy__pool_create(uint8_t yy__pool_thread_count, uint32_t yy__pool_queue_size) 
{
    if (((((yy__pool_thread_count == UINT8_C(0)) || (yy__pool_queue_size == UINT32_C(0))) || (yy__pool_thread_count > yy__pool_MAX_THREAD_SIZE)) || (yy__pool_queue_size > yy__pool_MAX_QUEUE_SIZE)))
    {
        struct yy__pool_ThreadPool* t__0 = NULL;
        return t__0;
    }
    struct yy__pool_ThreadPool* yy__pool_tpool = calloc(1, sizeof(struct yy__pool_ThreadPool));
    if ((yy__pool_tpool == NULL))
    {
        struct yy__pool_ThreadPool* t__1 = yy__pool_tpool;
        return t__1;
    }
    yy__pool_tpool->yy__pool_thread_count = INT32_C(0);
    yy__pool_tpool->yy__pool_queue_size = ((int32_t)yy__pool_queue_size);
    yy__pool_tpool->yy__pool_head = INT32_C(0);
    yy__pool_tpool->yy__pool_tail = INT32_C(0);
    yy__pool_tpool->yy__pool_count = INT32_C(0);
    yy__pool_tpool->yy__pool_shutdown = INT32_C(0);
    yy__pool_tpool->yy__pool_started = INT32_C(0);
    yk__arrsetlen(yy__pool_tpool->yy__pool_threads, yy__pool_thread_count);
    yk__arrsetlen(yy__pool_tpool->yy__pool_queue, yy__pool_queue_size);
    bool yy__pool_locks_ok = ((yy__mutex_init((&(yy__pool_tpool->yy__pool_lock)), yy__mutex_PLAIN) == yy__thread_SUCCESS) && (yy__condition_init((&(yy__pool_tpool->yy__pool_notify))) == yy__thread_SUCCESS));
    bool yy__pool_arrays_ok = ((yy__pool_tpool->yy__pool_threads != NULL) && (yy__pool_tpool->yy__pool_queue != NULL));
    if (((! (yy__pool_locks_ok)) || (! (yy__pool_arrays_ok))))
    {
        yy__pool_internal_del_pool(yy__pool_tpool);
        struct yy__pool_ThreadPool* t__2 = NULL;
        return t__2;
    }
    int32_t yy__pool_i = INT32_C(0);
    int32_t yy__pool_thread_count_i = ((int32_t)yy__pool_thread_count);
    while (1) {
        if (!((yy__pool_i < yy__pool_thread_count_i))) { break; } // Check
        // Body of while loop

        {
            bool yy__pool_ok = (yy__thread_create_with_data((&(yy__pool_tpool->yy__pool_threads[yy__pool_i])), yy__pool_internal_tpool_work, (yy__pool_tpool)) == yy__thread_SUCCESS);
            if ((! (yy__pool_ok)))
            {
                yy__pool_destroy(yy__pool_tpool, true);
                struct yy__pool_ThreadPool* t__3 = NULL;
                return t__3;
            }
            yy__pool_i += INT32_C(1);
            yy__pool_tpool->yy__pool_thread_count += INT32_C(1);
            yy__pool_tpool->yy__pool_started += INT32_C(1);
        }
    }
    struct yy__pool_ThreadPool* t__4 = yy__pool_tpool;
    return t__4;
}
int32_t yy__pool_add(struct yy__pool_ThreadPool* yy__pool_tpool, ykfncptr1 yy__pool_func, void* yy__pool_arg) 
{
    int32_t yy__pool_err = yy__pool_SUCCESS;
    int32_t yy__pool_next = INT32_C(0);
    if ((yy__pool_tpool == NULL))
    {
        int32_t const  t__5 = yy__pool_ERROR_INVALID;
        return t__5;
    }
    if ((yy__mutex_lock((&(yy__pool_tpool->yy__pool_lock))) != yy__thread_SUCCESS))
    {
        int32_t const  t__6 = yy__pool_ERROR_LOCK_FAILURE;
        return t__6;
    }
    yy__pool_next = (((yy__pool_tpool->yy__pool_tail + INT32_C(1))) % yy__pool_tpool->yy__pool_queue_size);
    while (1) {
        if (!(true)) { break; } // Check
        // Body of while loop

        {
            if ((yy__pool_tpool->yy__pool_count == yy__pool_tpool->yy__pool_queue_size))
            {
                yy__pool_err = yy__pool_ERROR_QUEUE_FULL;
                break;
            }
            if ((yy__pool_tpool->yy__pool_shutdown != yy__pool_NO_SHUTDOWN))
            {
                yy__pool_err = yy__pool_ERROR_SHUTDOWN;
                break;
            }
            yy__pool_tpool->yy__pool_queue[yy__pool_tpool->yy__pool_tail].e1 = yy__pool_func;
            yy__pool_tpool->yy__pool_queue[yy__pool_tpool->yy__pool_tail].e2 = yy__pool_arg;
            yy__pool_tpool->yy__pool_tail = yy__pool_next;
            yy__pool_tpool->yy__pool_count += INT32_C(1);
            if ((yy__condition_signal((&(yy__pool_tpool->yy__pool_notify))) != yy__thread_SUCCESS))
            {
                yy__pool_err = yy__pool_ERROR_LOCK_FAILURE;
            }
            break;
        }
    }
    if ((yy__mutex_unlock((&(yy__pool_tpool->yy__pool_lock))) != yy__thread_SUCCESS))
    {
        yy__pool_err = yy__pool_ERROR_LOCK_FAILURE;
    }
    int32_t t__7 = yy__pool_err;
    return t__7;
}
int32_t yy__pool_destroy(struct yy__pool_ThreadPool* yy__pool_tpool, bool yy__pool_graceful) 
{
    if ((yy__pool_tpool == NULL))
    {
        int32_t const  t__8 = yy__pool_ERROR_INVALID;
        return t__8;
    }
    if ((yy__mutex_lock((&(yy__pool_tpool->yy__pool_lock))) != yy__thread_SUCCESS))
    {
        int32_t const  t__9 = yy__pool_ERROR_LOCK_FAILURE;
        return t__9;
    }
    int32_t yy__pool_err = yy__pool_SUCCESS;
    while (1) {
        if (!(true)) { break; } // Check
        // Body of while loop

        {
            if ((yy__pool_tpool->yy__pool_shutdown != yy__pool_NO_SHUTDOWN))
            {
                yy__pool_err = yy__pool_ERROR_SHUTDOWN;
                break;
            }
            yy__pool_tpool->yy__pool_shutdown = (yy__pool_graceful ? yy__pool_GRACEFUL_SHUTDOWN : yy__pool_IMMEDIATE_SHUTDOWN);
            if (((yy__condition_broadcast((&(yy__pool_tpool->yy__pool_notify))) != yy__thread_SUCCESS) || (yy__mutex_unlock((&(yy__pool_tpool->yy__pool_lock))) != yy__thread_SUCCESS)))
            {
                yy__pool_err = yy__pool_ERROR_LOCK_FAILURE;
                break;
            }
            int32_t yy__pool_i = INT32_C(0);
            while (1) {
                if (!((yy__pool_i < yy__pool_tpool->yy__pool_thread_count))) { break; } // Check
                // Body of while loop

                {
                    bool yy__pool_ok = (yy__thread_join(yy__pool_tpool->yy__pool_threads[yy__pool_i]) == yy__thread_SUCCESS);
                    if ((! (yy__pool_ok)))
                    {
                        yy__pool_err = yy__pool_ERROR_THREAD_FAILURE;
                    }
                    yy__pool_i += INT32_C(1);
                }
            }
            break;
        }
    }
    if ((yy__pool_err == yy__pool_SUCCESS))
    {
        yy__pool_internal_del_pool(yy__pool_tpool);
    }
    int32_t t__10 = yy__pool_err;
    return t__10;
}
int32_t yy__pool_internal_del_pool(struct yy__pool_ThreadPool* yy__pool_tpool) 
{
    if (((yy__pool_tpool == NULL) || (yy__pool_tpool->yy__pool_started > INT32_C(0))))
    {
        int32_t const  t__11 = yy__pool_ERROR_INVALID;
        return t__11;
    }
    if (((yy__pool_tpool->yy__pool_threads != NULL) || (yy__pool_tpool->yy__pool_queue != NULL)))
    {
        yk__arrfree(yy__pool_tpool->yy__pool_threads);
        yk__arrfree(yy__pool_tpool->yy__pool_queue);
        yy__mutex_lock((&(yy__pool_tpool->yy__pool_lock)));
        yy__mutex_unlock((&(yy__pool_tpool->yy__pool_lock)));
        yy__mutex_destroy((&(yy__pool_tpool->yy__pool_lock)));
        yy__condition_destroy((&(yy__pool_tpool->yy__pool_notify)));
    }
    free(yy__pool_tpool);
    int32_t const  t__12 = yy__pool_SUCCESS;
    return t__12;
}
int32_t yy__pool_internal_tpool_work(void* yy__pool_tpool_obj) 
{
    struct yy__pool_ThreadPool* yy__pool_tpool = ((struct yy__pool_ThreadPool*)yy__pool_tpool_obj);
    struct yktuple0 yy__pool_task;
    while (1) {
        if (!(true)) { break; } // Check
        // Body of while loop

        {
            yy__mutex_lock((&(yy__pool_tpool->yy__pool_lock)));
            while (1) {
                if (!(((yy__pool_tpool->yy__pool_count == INT32_C(0)) && (yy__pool_tpool->yy__pool_shutdown == yy__pool_NO_SHUTDOWN)))) { break; } // Check
                // Body of while loop

                {
                    yy__condition_wait((&(yy__pool_tpool->yy__pool_notify)), (&(yy__pool_tpool->yy__pool_lock)));
                }
            }
            if (((((yy__pool_tpool->yy__pool_shutdown == yy__pool_GRACEFUL_SHUTDOWN) && (yy__pool_tpool->yy__pool_count == INT32_C(0)))) || (yy__pool_tpool->yy__pool_shutdown == yy__pool_IMMEDIATE_SHUTDOWN)))
            {
                break;
            }
            yy__pool_task.e1 = yy__pool_tpool->yy__pool_queue[yy__pool_tpool->yy__pool_head].e1;
            yy__pool_task.e2 = yy__pool_tpool->yy__pool_queue[yy__pool_tpool->yy__pool_head].e2;
            yy__pool_tpool->yy__pool_head = (((yy__pool_tpool->yy__pool_head + INT32_C(1))) % yy__pool_tpool->yy__pool_queue_size);
            yy__pool_tpool->yy__pool_count -= INT32_C(1);
            yy__mutex_unlock((&(yy__pool_tpool->yy__pool_lock)));
            ykfncptr1 yy__pool_fnc = yy__pool_task.e1;
            yy__pool_fnc(yy__pool_task.e2);
        }
    }
    yy__pool_tpool->yy__pool_started -= INT32_C(1);
    yy__mutex_unlock((&(yy__pool_tpool->yy__pool_lock)));
    yy__thread_exit(INT32_C(0));
    return INT32_C(0);
}
yy__buffer_StringBuffer yy__buffer_new() 
{
    yk__sds* srr = calloc(1, sizeof(yk__sds*));
    srr[0] = yk__sdsempty();
    return srr;
}
yy__buffer_StringBuffer yy__buffer_new_size(int32_t nn__s) 
{
    yk__sds* srr = calloc(1, sizeof(yk__sds*));
    srr[0] = yk__sdsempty();
    srr[0] = yk__sdsgrowzero(srr[0], nn__s);
    return srr;
}
void yy__buffer_append(yy__buffer_StringBuffer nn__buf, yk__sds nn__v) 
{
    nn__buf[0] = yk__sdscatsds(nn__buf[0], nn__v);
    yk__sdsfree(nn__v);
}
void yy__buffer_prepend(yy__buffer_StringBuffer nn__buf, yk__sds nn__v) 
{
    yk__sds tmp = nn__buf[0];
    nn__buf[0] = yk__sdscatsds(nn__v, nn__buf[0]);
    yk__sdsfree(tmp);;
}
yk__sds yy__buffer_to_str(yy__buffer_StringBuffer nn__buf) 
{
    return yk__sdsdup(nn__buf[0]);
}
void yy__buffer_join(yy__buffer_StringBuffer nn__buf, yk__sds* nn__values, yk__sds nn__sep) 
{
    if (NULL == nn__values) {
        yk__sdsfree(nn__sep);
        return;
    }
    yk__sds tmp = yk__sdsjoinsds(nn__values, yk__arrlen(nn__values), nn__sep, yk__sdslen(nn__sep));
    nn__buf[0] = yk__sdscatsds(nn__buf[0], tmp);
    yk__sdsfree(tmp);
    yk__sdsfree(nn__sep);
}
void yy__buffer_del_buf(yy__buffer_StringBuffer nn__buf) 
{
    yk__sdsfree(nn__buf[0]); 
    free(nn__buf);
}
yk__sds yy__building_prepare_code(struct yy__configuration_Config* yy__building_c, yk__sds yy__building_code) 
{
    yy__buffer_StringBuffer yy__building_buf = yy__buffer_new();
    int32_t yy__building_length = INT32_C(0);
    int32_t yy__building_x = INT32_C(0);
    yy__building_length = yk__arrlen(yy__building_c->yy__configuration_c_code->yy__configuration_runtime_feature_defines);
    yy__building_x = INT32_C(0);
    while (1) {
        if (!((yy__building_x < yy__building_length))) { break; } // Check
        // Body of while loop

        {
            yk__sds t__0 = yk__sdsnewlen("#define ", 8);
            yk__sds t__1 = yk__sdscatsds(yk__sdsdup(t__0), yy__building_c->yy__configuration_c_code->yy__configuration_runtime_feature_defines[yy__building_x]);
            yk__sds t__2 = yk__sdsnewlen("\n", 1);
            yk__sds t__3 = yk__sdscatsds(yk__sdsdup(t__1), t__2);
            yy__buffer_append(yy__building_buf, yk__sdsdup(t__3));
            yy__building_x = (yy__building_x + INT32_C(1));
            yk__sdsfree(t__3);
            yk__sdsfree(t__2);
            yk__sdsfree(t__1);
            yk__sdsfree(t__0);
        }
    }
    yy__building_length = yk__arrlen(yy__building_c->yy__configuration_c_code->yy__configuration_defines);
    yy__building_x = INT32_C(0);
    while (1) {
        if (!((yy__building_x < yy__building_length))) { break; } // Check
        // Body of while loop

        {
            yk__sds t__4 = yk__sdsnewlen("#define ", 8);
            yk__sds t__5 = yk__sdscatsds(yk__sdsdup(t__4), yy__building_c->yy__configuration_c_code->yy__configuration_defines[yy__building_x]);
            yk__sds t__6 = yk__sdsnewlen("\n", 1);
            yk__sds t__7 = yk__sdscatsds(yk__sdsdup(t__5), t__6);
            yy__buffer_append(yy__building_buf, yk__sdsdup(t__7));
            yy__building_x = (yy__building_x + INT32_C(1));
            yk__sdsfree(t__7);
            yk__sdsfree(t__6);
            yk__sdsfree(t__5);
            yk__sdsfree(t__4);
        }
    }
    yy__building_length = yk__arrlen(yy__building_c->yy__configuration_c_code->yy__configuration_system_includes);
    yy__building_x = INT32_C(0);
    while (1) {
        if (!((yy__building_x < yy__building_length))) { break; } // Check
        // Body of while loop

        {
            yk__sds t__8 = yk__sdsnewlen("#include <", 10);
            yk__sds t__9 = yk__sdscatsds(yk__sdsdup(t__8), yy__building_c->yy__configuration_c_code->yy__configuration_system_includes[yy__building_x]);
            yk__sds t__10 = yk__sdsnewlen(">\n", 2);
            yk__sds t__11 = yk__sdscatsds(yk__sdsdup(t__9), t__10);
            yy__buffer_append(yy__building_buf, yk__sdsdup(t__11));
            yy__building_x = (yy__building_x + INT32_C(1));
            yk__sdsfree(t__11);
            yk__sdsfree(t__10);
            yk__sdsfree(t__9);
            yk__sdsfree(t__8);
        }
    }
    if (yy__building_c->yy__configuration_compilation->yy__configuration_raylib)
    {
        yk__sds t__12 = yk__sdsnewlen("#include \"raylib.h\"\n", 20);
        yy__buffer_append(yy__building_buf, yk__sdsdup(t__12));
        yk__sds t__13 = yk__sdsnewlen("#include \"raygui.h\"\n", 20);
        yy__buffer_append(yy__building_buf, yk__sdsdup(t__13));
        yk__sds t__14 = yk__sdsnewlen("#include \"raymath.h\"\n", 21);
        yy__buffer_append(yy__building_buf, yk__sdsdup(t__14));
        yk__sds t__15 = yk__sdsnewlen("#include \"rlgl.h\"\n", 18);
        yy__buffer_append(yy__building_buf, yk__sdsdup(t__15));
        yk__sds t__16 = yk__sdsnewlen("#include \"rayextras.h\"\n", 23);
        yy__buffer_append(yy__building_buf, yk__sdsdup(t__16));
        yk__sdsfree(t__16);
        yk__sdsfree(t__15);
        yk__sdsfree(t__14);
        yk__sdsfree(t__13);
        yk__sdsfree(t__12);
    }
    yy__building_length = yk__arrlen(yy__building_c->yy__configuration_c_code->yy__configuration_runtime_feature_includes);
    yy__building_x = INT32_C(0);
    while (1) {
        if (!((yy__building_x < yy__building_length))) { break; } // Check
        // Body of while loop

        {
            yk__sds t__17 = yk__sdsnewlen("#include \"", 10);
            yk__sds t__18 = yk__sdscatsds(yk__sdsdup(t__17), yy__building_c->yy__configuration_c_code->yy__configuration_runtime_feature_includes[yy__building_x]);
            yk__sds t__19 = yk__sdsnewlen("\"\n", 2);
            yk__sds t__20 = yk__sdscatsds(yk__sdsdup(t__18), t__19);
            yy__buffer_append(yy__building_buf, yk__sdsdup(t__20));
            yy__building_x = (yy__building_x + INT32_C(1));
            yk__sdsfree(t__20);
            yk__sdsfree(t__19);
            yk__sdsfree(t__18);
            yk__sdsfree(t__17);
        }
    }
    yy__building_length = yk__arrlen(yy__building_c->yy__configuration_c_code->yy__configuration_includes);
    yy__building_x = INT32_C(0);
    while (1) {
        if (!((yy__building_x < yy__building_length))) { break; } // Check
        // Body of while loop

        {
            yk__sds t__21 = yk__sdsnewlen("#include \"", 10);
            yk__sds t__22 = yk__sdscatsds(yk__sdsdup(t__21), yy__building_c->yy__configuration_c_code->yy__configuration_includes[yy__building_x]);
            yk__sds t__23 = yk__sdsnewlen("\"\n", 2);
            yk__sds t__24 = yk__sdscatsds(yk__sdsdup(t__22), t__23);
            yy__buffer_append(yy__building_buf, yk__sdsdup(t__24));
            yy__building_x = (yy__building_x + INT32_C(1));
            yk__sdsfree(t__24);
            yk__sdsfree(t__23);
            yk__sdsfree(t__22);
            yk__sdsfree(t__21);
        }
    }
    yy__buffer_append(yy__building_buf, yk__sdsdup(yy__building_code));
    yk__sds t__25 = yk__sdsnewlen("\n", 1);
    yy__buffer_append(yy__building_buf, yk__sdsdup(t__25));
    yk__sds t__26 = yy__buffer_to_str(yy__building_buf);
    yk__sds yy__building_result = yk__sdsdup((t__26));
    yk__sds t__27 = yy__building_result;
    yy__buffer_del_buf(yy__building_buf);
    yk__sdsfree(t__26);
    yk__sdsfree(t__25);
    yk__sdsfree(yy__building_code);
    return t__27;
}
bool yy__building_is_target_macos(yk__sds yy__building_target_to_check) 
{
    bool yy__building_native = (yk__sdslen(yy__building_target_to_check) == INT32_C(0));
    if (yy__building_native)
    {
        bool t__28 = yy__os_is_macos();
        yk__sdsfree(yy__building_target_to_check);
        return t__28;
    }
    yk__sds t__29 = yk__sdsnewlen("macos", 5);
    bool t__30 = yy__strings_contains(yk__sdsdup(yy__building_target_to_check), yk__sdsdup(t__29));
    yk__sdsfree(t__29);
    yk__sdsfree(yy__building_target_to_check);
    return t__30;
}
bool yy__building_is_target_windows(yk__sds yy__building_target_to_check) 
{
    bool yy__building_native = (yk__sdslen(yy__building_target_to_check) == INT32_C(0));
    if (yy__building_native)
    {
        bool t__31 = yy__os_is_windows();
        yk__sdsfree(yy__building_target_to_check);
        return t__31;
    }
    yk__sds t__32 = yk__sdsnewlen("windows", 7);
    bool t__33 = yy__strings_contains(yk__sdsdup(yy__building_target_to_check), yk__sdsdup(t__32));
    yk__sdsfree(t__32);
    yk__sdsfree(yy__building_target_to_check);
    return t__33;
}
void yy__building_produce_obj_function(void* yy__building_arg) 
{
    struct yy__building_BObject* yy__building_data = ((struct yy__building_BObject*)yy__building_arg);
    yk__sds* yy__building_my_args = yy__array_dup(yy__building_data->yy__building_args);
    yk__sds t__34 = yy__path_basename(yk__sdsdup(yy__building_data->yy__building_c_file));
    yk__sds t__35 = yy__path_remove_extension(yk__sdsdup((t__34)));
    yk__sds yy__building_object_file = yk__sdsdup((t__35));
    if (yy__building_data->yy__building_print_info)
    {
        yk__sds t__36 = yk__sdsnewlen("runtime::", 9);
        yy__console_cyan(yk__sdsdup(t__36));
        yy__console_yellow(yk__sdsdup(yy__building_object_file));
        yk__sds t__37 = yk__sdsnewlen(" := ", 4);
        yy__console_cyan(yk__sdsdup(t__37));
        yk__sdsfree(t__37);
        yk__sdsfree(t__36);
    }
    if (((! (yy__building_data->yy__building_always_build)) && yy__path_readable(yk__sdsdup(yy__building_data->yy__building_object_file_path))))
    {
        if (yy__building_data->yy__building_print_info)
        {
            yk__sds t__38 = yk__sdsnewlen("ok.\n", 4);
            yy__console_green(yk__sdsdup(t__38));
            yk__sdsfree(t__38);
        }
        yy__array_del_str_array(yy__building_my_args);
        yk__sdsfree(yy__building_object_file);
        yk__sdsfree(t__35);
        yk__sdsfree(t__34);
        return;
    }
    yk__sds t__39 = yk__sdsnewlen("-c", 2);
    yk__arrput(yy__building_my_args, yk__sdsdup(t__39));
    yk__arrput(yy__building_my_args, yk__sdsdup(yy__building_data->yy__building_c_file));
    yk__sds t__40 = yk__sdsnewlen("-o", 2);
    yk__arrput(yy__building_my_args, yk__sdsdup(t__40));
    yk__arrput(yy__building_my_args, yk__sdsdup(yy__building_data->yy__building_object_file_path));
    yy__os_ProcessResult yy__building_pr = yy__os_run(yy__building_my_args);
    if (yy__building_data->yy__building_print_info)
    {
        if (yy__building_pr->ok)
        {
            yk__sds t__41 = yk__sdsnewlen("ok.\n", 4);
            yy__console_green(yk__sdsdup(t__41));
            yk__sdsfree(t__41);
        }
        else
        {
            yk__sds t__42 = yk__sdsnewlen("failed.\n", 8);
            yy__console_red(yk__sdsdup(t__42));
            yk__sds t__43 = yk__sdsnewlen("--c compiler output---\n", 23);
            yy__console_cyan(yk__sdsdup(t__43));
            yk__sds t__44 = yk__sdsnewlen("command := ", 11);
            yy__console_red(yk__sdsdup(t__44));
            yk__sds t__45 = yk__sdsnewlen(" ", 1);
            yk__sds t__46 = yy__array_join(yy__building_my_args, yk__sdsdup(t__45));
            yk__sds t__47 = yk__sdsnewlen("\n", 1);
            yk__sds t__48 = yk__sdscatsds(yk__sdsdup((t__46)), t__47);
            yy__console_cyan(yk__sdsdup(t__48));
            yy__console_red(yk__sdsdup(yy__building_pr->output));
            yk__sds t__49 = yk__sdsnewlen("--end c compiler output---\n", 27);
            yy__console_cyan(yk__sdsdup(t__49));
            yk__sdsfree(t__49);
            yk__sdsfree(t__48);
            yk__sdsfree(t__47);
            yk__sdsfree(t__46);
            yk__sdsfree(t__45);
            yk__sdsfree(t__44);
            yk__sdsfree(t__43);
            yk__sdsfree(t__42);
        }
    }
    yy__os_del_process_result(yy__building_pr);
    yy__array_del_str_array(yy__building_my_args);
    yk__sdsfree(t__40);
    yk__sdsfree(t__39);
    yk__sdsfree(yy__building_object_file);
    yk__sdsfree(t__35);
    yk__sdsfree(t__34);
    return;
}
yk__sds yy__building_core_object(yk__sds* yy__building_args, yk__sds yy__building_c_file, yk__sds yy__building_build_path, yk__sds yy__building_target, bool yy__building_always_build, struct yy__building_BObject*** yy__building_bobj_array) 
{
    yk__sds t__50 = yk__sdsnewlen("-", 1);
    yk__sds yy__building_suffix = yk__sdsdup(t__50);
    bool yy__building_native = (yk__sdslen(yy__building_target) == INT32_C(0));
    if (yy__building_native)
    {
        yk__sds t__51 = yk__sdsnewlen("native", 6);
        yy__building_suffix = yk__sdscatsds(yy__building_suffix, t__51);
        yk__sdsfree(t__51);
    }
    else
    {
        yy__building_suffix = yk__sdscatsds(yy__building_suffix, yy__building_target);
    }
    yk__sds t__52 = yy__path_basename(yk__sdsdup(yy__building_c_file));
    yk__sds t__53 = yy__path_remove_extension(yk__sdsdup((t__52)));
    yk__sds yy__building_object_file = yk__sdsdup((t__53));
    yy__building_object_file = yk__sdscatsds(yy__building_object_file, yy__building_suffix);
    yk__sds t__54 = yk__sdsnewlen(".o", 2);
    yy__building_object_file = yk__sdscatsds(yy__building_object_file, t__54);
    yk__sds t__55 = yy__path_join(yk__sdsdup(yy__building_build_path), yk__sdsdup(yy__building_object_file));
    yk__sds yy__building_object_file_path = yk__sdsdup((t__55));
    struct yy__building_BObject* yy__building_bobj = calloc(1, sizeof(struct yy__building_BObject));
    yy__building_bobj->yy__building_args = yy__building_args;
    yk__sdsfree(yy__building_bobj->yy__building_c_file);
    yy__building_bobj->yy__building_c_file = yk__sdsdup(yy__building_c_file);
    yy__building_bobj->yy__building_always_build = yy__building_always_build;
    yk__sdsfree(yy__building_bobj->yy__building_object_file_path);
    yy__building_bobj->yy__building_object_file_path = yk__sdsdup(yy__building_object_file_path);
    yy__building_bobj->yy__building_print_info = false;
    yk__arrput((*(yy__building_bobj_array)), yy__building_bobj);
    yk__sds t__56 = yy__building_object_file_path;
    yk__sdsfree(t__55);
    yk__sdsfree(t__54);
    yk__sdsfree(yy__building_object_file);
    yk__sdsfree(t__53);
    yk__sdsfree(t__52);
    yk__sdsfree(yy__building_suffix);
    yk__sdsfree(t__50);
    yk__sdsfree(yy__building_target);
    yk__sdsfree(yy__building_build_path);
    yk__sdsfree(yy__building_c_file);
    return t__56;
}
void yy__building_build_objects_sequential(struct yy__building_BObject** yy__building_buildables) 
{
    int32_t yy__building_object_count = yk__arrlen(yy__building_buildables);
    int32_t yy__building_pos = INT32_C(0);
    while (1) {
        if (!((yy__building_pos < yy__building_object_count))) { break; } // Check
        // Body of while loop

        {
            struct yy__building_BObject* yy__building_buildable = yy__building_buildables[yy__building_pos];
            yy__building_buildable->yy__building_print_info = true;
            yy__building_produce_obj_function((yy__building_buildable));
            yy__building_pos += INT32_C(1);
        }
    }
    return;
}
void yy__building_build_objects(struct yy__building_BObject** yy__building_buildables) 
{
    int32_t yy__building_object_count = yk__arrlen(yy__building_buildables);
    yy__cpu_Cpu yy__building_cpu_data = yy__cpu_info();
    uint8_t yy__building_threads = ((uint8_t)yy__building_cpu_data.n_processors);
    yy__building_threads = ((yy__building_threads > yy__pool_MAX_THREAD_SIZE) ? yy__pool_MAX_THREAD_SIZE : yy__building_threads);
    struct yy__pool_ThreadPool* yy__building_tpool = yy__pool_create(yy__building_threads, ((uint32_t)(yy__building_object_count + INT32_C(2))));
    if ((yy__building_tpool == NULL))
    {
        yy__building_build_objects_sequential(yy__building_buildables);
        return;
    }
    int32_t yy__building_pos = INT32_C(0);
    while (1) {
        if (!((yy__building_pos < yy__building_object_count))) { break; } // Check
        // Body of while loop

        {
            struct yy__building_BObject* yy__building_buildable = yy__building_buildables[yy__building_pos];
            yy__pool_add(yy__building_tpool, yy__building_produce_obj_function, (yy__building_buildable));
            yy__building_pos += INT32_C(1);
        }
    }
    yy__pool_destroy(yy__building_tpool, true);
    return;
}
void yy__building_cleanup_buildables(struct yy__building_BObject** yy__building_buildables) 
{
    int32_t yy__building_object_count = yk__arrlen(yy__building_buildables);
    int32_t yy__building_pos = INT32_C(0);
    while (1) {
        if (!((yy__building_pos < yy__building_object_count))) { break; } // Check
        // Body of while loop

        {
            struct yy__building_BObject* yy__building_buildable = yy__building_buildables[yy__building_pos];
            yk__sdsfree(yy__building_buildable->yy__building_c_file);
            yk__sdsfree(yy__building_buildable->yy__building_object_file_path);
            free(yy__building_buildable);
            yy__building_pos += INT32_C(1);
        }
    }
    yk__arrfree(yy__building_buildables);
    return;
}
bool yy__building_keep_ray_objects(yk__sds yy__building_element, bool yy__building_negate) 
{
    yk__sds t__57 = yk__sdsnewlen(".o", 2);
    bool yy__building_obj = yy__strings_endswith(yk__sdsdup(yy__building_element), yk__sdsdup(t__57));
    if (yy__building_negate)
    {
        bool t__58 = (! (yy__building_obj));
        yk__sdsfree(t__57);
        yk__sdsfree(yy__building_element);
        return t__58;
    }
    bool t__59 = yy__building_obj;
    yk__sdsfree(t__57);
    yk__sdsfree(yy__building_element);
    return t__59;
}
yk__sds* yy__building_create_args(struct yy__configuration_Config* yy__building_c, yk__sds yy__building_code_path, yk__sds yy__building_build_path, yk__sds yy__building_target, yk__sds* yy__building_raylib_args) 
{
    bool yy__building_native = (yk__sdslen(yy__building_target) == INT32_C(0));
    yk__sds* yy__building_args = NULL;
    yk__sds* yy__building_objects = NULL;
    struct yy__building_BObject** yy__building_buildable_objects = NULL;
    yk__sds* t__62 = yy__building_raylib_args;
    bool t__64 = false;
    size_t t__61 = yk__arrlenu(t__62);
    yk__sds* t__65 = NULL;
    for (size_t t__60 = 0; t__60 < t__61; t__60++) { 
        yk__sds t__63 = yk__sdsdup(t__62[t__60]);
        bool t__66 = yy__building_keep_ray_objects(t__63, t__64);
        t__63 = yk__sdsdup(t__62[t__60]); if (t__66) {yk__arrput(t__65, t__63); } else { yk__sdsfree(t__63); }
    }
    yk__sds* yy__building_ray_objects = t__65;
    yk__sds* t__69 = yy__building_raylib_args;
    bool t__71 = true;
    size_t t__68 = yk__arrlenu(t__69);
    yk__sds* t__72 = NULL;
    for (size_t t__67 = 0; t__67 < t__68; t__67++) { 
        yk__sds t__70 = yk__sdsdup(t__69[t__67]);
        bool t__73 = yy__building_keep_ray_objects(t__70, t__71);
        t__70 = yk__sdsdup(t__69[t__67]); if (t__73) {yk__arrput(t__72, t__70); } else { yk__sdsfree(t__70); }
    }
    yk__sds* yy__building_ray_other_args = t__72;
    if (yy__building_c->yy__configuration_compilation->yy__configuration_wasm4)
    {
        yk__sds t__74 = yk__sdsnewlen("cc", 2);
        yk__sds t__75 = yk__sdsnewlen("-std=c99", 8);
        yk__sds t__76 = yk__sdsnewlen("-Wno-newline-eof", 16);
        yk__sds t__77 = yk__sdsnewlen("-Wno-parentheses-equality", 25);
        yk__sds t__78 = yk__sdsnewlen("-MMD", 4);
        yk__sds t__79 = yk__sdsnewlen("-MP", 3);
        yk__sds t__80 = yk__sdsnewlen("-Oz", 3);
        yk__sds* t__81 = NULL;
        yk__arrsetcap(t__81, 8);
        yk__arrput(t__81, yk__sdsdup(yy__building_c->yy__configuration_zig_compiler_path));
        yk__arrput(t__81, yk__sdsdup(t__74));
        yk__arrput(t__81, yk__sdsdup(t__75));
        yk__arrput(t__81, yk__sdsdup(t__76));
        yk__arrput(t__81, yk__sdsdup(t__77));
        yk__arrput(t__81, yk__sdsdup(t__78));
        yk__arrput(t__81, yk__sdsdup(t__79));
        yk__arrput(t__81, yk__sdsdup(t__80));
        yy__building_args = t__81;
        yk__sdsfree(t__80);
        yk__sdsfree(t__79);
        yk__sdsfree(t__78);
        yk__sdsfree(t__77);
        yk__sdsfree(t__76);
        yk__sdsfree(t__75);
        yk__sdsfree(t__74);
    }
    else
    {
        if (yy__building_c->yy__configuration_compilation->yy__configuration_web)
        {
            yk__sds t__82 = yk__sdsnewlen("-std=c99", 8);
            yk__sds t__83 = yk__sdsnewlen("-Oz", 3);
            yk__sds t__84 = yk__sdsnewlen("-Wno-newline-eof", 16);
            yk__sds t__85 = yk__sdsnewlen("-Wno-parentheses-equality", 25);
            yk__sds* t__86 = NULL;
            yk__arrsetcap(t__86, 5);
            yk__arrput(t__86, yk__sdsdup(yy__building_c->yy__configuration_emcc_compiler_path));
            yk__arrput(t__86, yk__sdsdup(t__82));
            yk__arrput(t__86, yk__sdsdup(t__83));
            yk__arrput(t__86, yk__sdsdup(t__84));
            yk__arrput(t__86, yk__sdsdup(t__85));
            yy__building_args = t__86;
            yk__sdsfree(t__85);
            yk__sdsfree(t__84);
            yk__sdsfree(t__83);
            yk__sdsfree(t__82);
        }
        else
        {
            if (yy__building_c->yy__configuration_compilation->yy__configuration_raylib_hot_reloading_dll)
            {
                yk__sds t__87 = yk__sdsnewlen("cc", 2);
                yk__sds t__88 = yk__sdsnewlen("-std=c99", 8);
                yk__sds t__89 = yk__sdsnewlen("-O1", 3);
                yk__sds t__90 = yk__sdsnewlen("-pedantic", 9);
                yk__sds t__91 = yk__sdsnewlen("-Wall", 5);
                yk__sds t__92 = yk__sdsnewlen("-Wno-newline-eof", 16);
                yk__sds t__93 = yk__sdsnewlen("-fPIC", 5);
                yk__sds t__94 = yk__sdsnewlen("-Wno-parentheses-equality", 25);
                yk__sds* t__95 = NULL;
                yk__arrsetcap(t__95, 9);
                yk__arrput(t__95, yk__sdsdup(yy__building_c->yy__configuration_zig_compiler_path));
                yk__arrput(t__95, yk__sdsdup(t__87));
                yk__arrput(t__95, yk__sdsdup(t__88));
                yk__arrput(t__95, yk__sdsdup(t__89));
                yk__arrput(t__95, yk__sdsdup(t__90));
                yk__arrput(t__95, yk__sdsdup(t__91));
                yk__arrput(t__95, yk__sdsdup(t__92));
                yk__arrput(t__95, yk__sdsdup(t__93));
                yk__arrput(t__95, yk__sdsdup(t__94));
                yy__building_args = t__95;
                yk__sdsfree(t__94);
                yk__sdsfree(t__93);
                yk__sdsfree(t__92);
                yk__sdsfree(t__91);
                yk__sdsfree(t__90);
                yk__sdsfree(t__89);
                yk__sdsfree(t__88);
                yk__sdsfree(t__87);
            }
            else
            {
                yk__sds t__96 = yk__sdsnewlen("cc", 2);
                yk__sds t__97 = yk__sdsnewlen("-std=c99", 8);
                yk__sds t__98 = yk__sdsnewlen("-Oz", 3);
                yk__sds t__99 = yk__sdsnewlen("-pedantic", 9);
                yk__sds t__100 = yk__sdsnewlen("-Wall", 5);
                yk__sds t__101 = yk__sdsnewlen("-Wno-newline-eof", 16);
                yk__sds t__102 = yk__sdsnewlen("-fPIC", 5);
                yk__sds t__103 = yk__sdsnewlen("-Wno-parentheses-equality", 25);
                yk__sds* t__104 = NULL;
                yk__arrsetcap(t__104, 9);
                yk__arrput(t__104, yk__sdsdup(yy__building_c->yy__configuration_zig_compiler_path));
                yk__arrput(t__104, yk__sdsdup(t__96));
                yk__arrput(t__104, yk__sdsdup(t__97));
                yk__arrput(t__104, yk__sdsdup(t__98));
                yk__arrput(t__104, yk__sdsdup(t__99));
                yk__arrput(t__104, yk__sdsdup(t__100));
                yk__arrput(t__104, yk__sdsdup(t__101));
                yk__arrput(t__104, yk__sdsdup(t__102));
                yk__arrput(t__104, yk__sdsdup(t__103));
                yy__building_args = t__104;
                yk__sdsfree(t__103);
                yk__sdsfree(t__102);
                yk__sdsfree(t__101);
                yk__sdsfree(t__100);
                yk__sdsfree(t__99);
                yk__sdsfree(t__98);
                yk__sdsfree(t__97);
                yk__sdsfree(t__96);
            }
        }
    }
    if (((! (yy__building_is_target_macos(yk__sdsdup(yy__building_target)))) && (! (yy__building_c->yy__configuration_compilation->yy__configuration_raylib_hot_reloading_dll))))
    {
        yk__sds t__105 = yk__sdsnewlen("-flto=full", 10);
        yk__arrput(yy__building_args, yk__sdsdup(t__105));
        yk__sdsfree(t__105);
    }
    if (yy__building_c->yy__configuration_compilation->yy__configuration_raylib_hot_reloading_dll)
    {
        yk__sds t__106 = yk__sdsnewlen("-DYK__CR_DLL", 12);
        yk__arrput(yy__building_args, yk__sdsdup(t__106));
        yk__sdsfree(t__106);
    }
    yy__building_args = yy__array_extend(yy__building_args, yy__building_ray_other_args);
    int32_t yy__building_length = INT32_C(0);
    int32_t yy__building_x = INT32_C(0);
    yy__building_length = yk__arrlen(yy__building_c->yy__configuration_c_code->yy__configuration_include_paths);
    yy__building_x = INT32_C(0);
    while (1) {
        if (!((yy__building_x < yy__building_length))) { break; } // Check
        // Body of while loop

        {
            yk__sds t__107 = yk__sdsnewlen("-I", 2);
            yk__sds t__108 = yk__sdscatsds(yk__sdsdup(t__107), yy__building_c->yy__configuration_c_code->yy__configuration_include_paths[yy__building_x]);
            yk__sds yy__building_include = yk__sdsdup(t__108);
            yk__arrput(yy__building_args, yk__sdsdup(yy__building_include));
            yy__building_x = (yy__building_x + INT32_C(1));
            yk__sdsfree(yy__building_include);
            yk__sdsfree(t__108);
            yk__sdsfree(t__107);
        }
    }
    yy__building_length = yk__arrlen(yy__building_c->yy__configuration_c_code->yy__configuration_runtime_feature_compiler_defines);
    yy__building_x = INT32_C(0);
    while (1) {
        if (!((yy__building_x < yy__building_length))) { break; } // Check
        // Body of while loop

        {
            yk__sds t__109 = yk__sdsnewlen("-D", 2);
            yk__sds t__110 = yk__sdscatsds(yk__sdsdup(t__109), yy__building_c->yy__configuration_c_code->yy__configuration_runtime_feature_compiler_defines[yy__building_x]);
            yk__sds yy__building_cdefine = yk__sdsdup(t__110);
            yk__arrput(yy__building_args, yk__sdsdup(yy__building_cdefine));
            yy__building_x = (yy__building_x + INT32_C(1));
            yk__sdsfree(yy__building_cdefine);
            yk__sdsfree(t__110);
            yk__sdsfree(t__109);
        }
    }
    yy__building_length = yk__arrlen(yy__building_c->yy__configuration_c_code->yy__configuration_compiler_defines);
    yy__building_x = INT32_C(0);
    while (1) {
        if (!((yy__building_x < yy__building_length))) { break; } // Check
        // Body of while loop

        {
            yk__sds t__111 = yk__sdsnewlen("-D", 2);
            yk__sds t__112 = yk__sdscatsds(yk__sdsdup(t__111), yy__building_c->yy__configuration_c_code->yy__configuration_compiler_defines[yy__building_x]);
            yk__sds yy__building_cdefine = yk__sdsdup(t__112);
            yk__arrput(yy__building_args, yk__sdsdup(yy__building_cdefine));
            yy__building_x = (yy__building_x + INT32_C(1));
            yk__sdsfree(yy__building_cdefine);
            yk__sdsfree(t__112);
            yk__sdsfree(t__111);
        }
    }
    yk__sds t__113 = yk__sdsnewlen("web", 3);
    yk__sds t__114 = yk__sdsnewlen("wasm4", 5);
    if ((((! (yy__building_native)) && (yk__sdscmp(yy__building_target , t__113) != 0)) && (yk__sdscmp(yy__building_target , t__114) != 0)))
    {
        yk__sds t__115 = yk__sdsnewlen("-target", 7);
        yk__arrput(yy__building_args, yk__sdsdup(t__115));
        yk__arrput(yy__building_args, yk__sdsdup(yy__building_target));
        yk__sdsfree(t__115);
    }
    yk__sds t__116 = yk__sdsnewlen("wasm4", 5);
    if ((yk__sdscmp(yy__building_target , t__116) == 0))
    {
        yk__sds t__117 = yk__sdsnewlen("-target", 7);
        yk__arrput(yy__building_args, yk__sdsdup(t__117));
        yk__sds t__118 = yk__sdsnewlen("wasm32-wasi-musl", 16);
        yk__arrput(yy__building_args, yk__sdsdup(t__118));
        yk__sdsfree(t__118);
        yk__sdsfree(t__117);
    }
    yy__building_length = yk__arrlen(yy__building_c->yy__configuration_c_code->yy__configuration_runtime_feature_c_code);
    yy__building_x = INT32_C(0);
    while (1) {
        if (!((yy__building_x < yy__building_length))) { break; } // Check
        // Body of while loop

        {
            yk__sds yy__building_rfc = yk__sdsdup(yy__building_c->yy__configuration_c_code->yy__configuration_runtime_feature_c_code[yy__building_x]);
            yk__sds t__119 = yy__building_core_object(yy__building_args, yk__sdsdup(yy__building_rfc), yk__sdsdup(yy__building_build_path), yk__sdsdup(yy__building_target), false, (&(yy__building_buildable_objects)));
            yk__sdsfree(yy__building_rfc);
            yy__building_rfc = yk__sdsdup((t__119));
            yk__arrput(yy__building_objects, yk__sdsdup(yy__building_rfc));
            yy__building_x = (yy__building_x + INT32_C(1));
            yk__sdsfree(t__119);
            yk__sdsfree(yy__building_rfc);
        }
    }
    yy__building_length = yk__arrlen(yy__building_c->yy__configuration_c_code->yy__configuration_c_code);
    yy__building_x = INT32_C(0);
    while (1) {
        if (!((yy__building_x < yy__building_length))) { break; } // Check
        // Body of while loop

        {
            yk__sds yy__building_cc = yk__sdsdup(yy__building_c->yy__configuration_c_code->yy__configuration_c_code[yy__building_x]);
            yk__sds t__120 = yy__building_core_object(yy__building_args, yk__sdsdup(yy__building_cc), yk__sdsdup(yy__building_build_path), yk__sdsdup(yy__building_target), true, (&(yy__building_buildable_objects)));
            yk__sdsfree(yy__building_cc);
            yy__building_cc = yk__sdsdup((t__120));
            yk__arrput(yy__building_objects, yk__sdsdup(yy__building_cc));
            yy__building_x = (yy__building_x + INT32_C(1));
            yk__sdsfree(t__120);
            yk__sdsfree(yy__building_cc);
        }
    }
    yk__sds t__121 = yy__building_core_object(yy__building_args, yk__sdsdup(yy__building_code_path), yk__sdsdup(yy__building_build_path), yk__sdsdup(yy__building_target), true, (&(yy__building_buildable_objects)));
    yk__sds yy__building_program_object = yk__sdsdup((t__121));
    yk__arrput(yy__building_objects, yk__sdsdup(yy__building_program_object));
    yk__sds t__122 = yk__sdsnewlen("yk__main.c", 10);
    yk__sds t__123 = yy__path_join(yk__sdsdup(yy__building_c->yy__configuration_runtime_path), yk__sdsdup(t__122));
    yk__sds yy__building_the_yk_main = yk__sdsdup((t__123));
    yk__sds t__124 = yy__building_core_object(yy__building_args, yk__sdsdup(yy__building_the_yk_main), yk__sdsdup(yy__building_build_path), yk__sdsdup(yy__building_target), false, (&(yy__building_buildable_objects)));
    yk__sdsfree(yy__building_the_yk_main);
    yy__building_the_yk_main = yk__sdsdup((t__124));
    yk__arrput(yy__building_objects, yk__sdsdup(yy__building_the_yk_main));
    if (yy__building_c->yy__configuration_compilation->yy__configuration_disable_parallel_build)
    {
        yy__building_build_objects_sequential(yy__building_buildable_objects);
    }
    else
    {
        yy__building_build_objects(yy__building_buildable_objects);
    }
    yy__building_cleanup_buildables(yy__building_buildable_objects);
    if (yy__building_c->yy__configuration_compilation->yy__configuration_wasm4)
    {
        yy__array_del_str_array(yy__building_args);
        yk__sds t__125 = yk__sdsnewlen("build-lib", 9);
        yk__sds t__126 = yk__sdsnewlen("-dynamic", 8);
        yk__sds t__127 = yk__sdsnewlen("-flto", 5);
        yk__sds t__128 = yk__sdsnewlen("-mexec-model=reactor", 20);
        yk__sds t__129 = yk__sdsnewlen("-O", 2);
        yk__sds t__130 = yk__sdsnewlen("ReleaseSmall", 12);
        yk__sds t__131 = yk__sdsnewlen("-target", 7);
        yk__sds t__132 = yk__sdsnewlen("wasm32-wasi-musl", 16);
        yk__sds t__133 = yk__sdsnewlen("--strip", 7);
        yk__sds t__134 = yk__sdsnewlen("--stack", 7);
        yk__sds t__135 = yk__sdsnewlen("50784", 5);
        yk__sds t__136 = yk__sdsnewlen("--global-base=6560", 18);
        yk__sds t__137 = yk__sdsnewlen("--import-memory", 15);
        yk__sds t__138 = yk__sdsnewlen("--initial-memory=65536", 22);
        yk__sds t__139 = yk__sdsnewlen("--max-memory=65536", 18);
        yk__sds t__140 = yk__sdsnewlen("-ofmt=wasm", 10);
        yk__sds t__141 = yk__sdsnewlen("--export=start", 14);
        yk__sds t__142 = yk__sdsnewlen("--export=update", 15);
        yk__sds* t__143 = NULL;
        yk__arrsetcap(t__143, 19);
        yk__arrput(t__143, yk__sdsdup(yy__building_c->yy__configuration_zig_compiler_path));
        yk__arrput(t__143, yk__sdsdup(t__125));
        yk__arrput(t__143, yk__sdsdup(t__126));
        yk__arrput(t__143, yk__sdsdup(t__127));
        yk__arrput(t__143, yk__sdsdup(t__128));
        yk__arrput(t__143, yk__sdsdup(t__129));
        yk__arrput(t__143, yk__sdsdup(t__130));
        yk__arrput(t__143, yk__sdsdup(t__131));
        yk__arrput(t__143, yk__sdsdup(t__132));
        yk__arrput(t__143, yk__sdsdup(t__133));
        yk__arrput(t__143, yk__sdsdup(t__134));
        yk__arrput(t__143, yk__sdsdup(t__135));
        yk__arrput(t__143, yk__sdsdup(t__136));
        yk__arrput(t__143, yk__sdsdup(t__137));
        yk__arrput(t__143, yk__sdsdup(t__138));
        yk__arrput(t__143, yk__sdsdup(t__139));
        yk__arrput(t__143, yk__sdsdup(t__140));
        yk__arrput(t__143, yk__sdsdup(t__141));
        yk__arrput(t__143, yk__sdsdup(t__142));
        yy__building_args = t__143;
        yk__sdsfree(t__142);
        yk__sdsfree(t__141);
        yk__sdsfree(t__140);
        yk__sdsfree(t__139);
        yk__sdsfree(t__138);
        yk__sdsfree(t__137);
        yk__sdsfree(t__136);
        yk__sdsfree(t__135);
        yk__sdsfree(t__134);
        yk__sdsfree(t__133);
        yk__sdsfree(t__132);
        yk__sdsfree(t__131);
        yk__sdsfree(t__130);
        yk__sdsfree(t__129);
        yk__sdsfree(t__128);
        yk__sdsfree(t__127);
        yk__sdsfree(t__126);
        yk__sdsfree(t__125);
    }
    yy__building_args = yy__array_extend(yy__building_args, yy__building_objects);
    yy__building_args = yy__array_extend(yy__building_args, yy__building_ray_objects);
    yy__array_del_str_array(yy__building_objects);
    if ((yy__building_c->yy__configuration_compilation->yy__configuration_web && (yk__sdslen(yy__building_c->yy__configuration_compilation->yy__configuration_web_shell) > INT32_C(0))))
    {
        yk__sds t__144 = yk__sdsnewlen("--shell-file", 12);
        yk__arrput(yy__building_args, yk__sdsdup(t__144));
        yk__arrput(yy__building_args, yk__sdsdup(yy__building_c->yy__configuration_compilation->yy__configuration_web_shell));
        yk__sdsfree(t__144);
    }
    if (yy__building_c->yy__configuration_compilation->yy__configuration_raylib_hot_reloading_dll)
    {
        yk__sds t__145 = yk__sdsnewlen("-shared", 7);
        yk__arrput(yy__building_args, yk__sdsdup(t__145));
        yk__sdsfree(t__145);
    }
    yk__sds t__146 = yk__sdsnewlen("wasm4", 5);
    if ((yk__sdscmp(yy__building_target , t__146) != 0))
    {
        yk__sds t__147 = yk__sdsnewlen("-o", 2);
        yk__arrput(yy__building_args, yk__sdsdup(t__147));
        yk__sdsfree(t__147);
    }
    yk__sds yy__building_binary = yk__sdsdup(yy__building_c->yy__configuration_project->yy__configuration_name);
    yk__sds t__148 = yk__sdsnewlen("web", 3);
    yk__sds t__149 = yk__sdsnewlen("wasm4", 5);
    if ((((! (yy__building_native)) && (yk__sdscmp(yy__building_target , t__148) != 0)) && (yk__sdscmp(yy__building_target , t__149) != 0)))
    {
        yk__sds t__150 = yk__sdsnewlen("-", 1);
        yk__sds t__151 = yk__sdscatsds(yk__sdsdup(yy__building_binary), t__150);
        yk__sds t__152 = yk__sdscatsds(yk__sdsdup(t__151), yy__building_target);
        yk__sdsfree(yy__building_binary);
        yy__building_binary = yk__sdsdup(t__152);
        yk__sdsfree(t__152);
        yk__sdsfree(t__151);
        yk__sdsfree(t__150);
    }
    if (yy__building_c->yy__configuration_compilation->yy__configuration_raylib_hot_reloading_dll)
    {
        if (yy__building_is_target_windows(yk__sdsdup(yy__building_target)))
        {
            yk__sds t__153 = yk__sdsnewlen(".dll", 4);
            yk__sds t__154 = yk__sdscatsds(yk__sdsdup(yy__building_binary), t__153);
            yk__sdsfree(yy__building_binary);
            yy__building_binary = yk__sdsdup(t__154);
            yk__sdsfree(t__154);
            yk__sdsfree(t__153);
        }
        else
        {
            if (yy__building_is_target_macos(yk__sdsdup(yy__building_target)))
            {
                yk__sds t__155 = yk__sdsnewlen("lib", 3);
                yk__sds t__156 = yk__sdscatsds(yk__sdsdup(t__155), yy__building_binary);
                yk__sds t__157 = yk__sdsnewlen(".dylib", 6);
                yk__sds t__158 = yk__sdscatsds(yk__sdsdup(t__156), t__157);
                yk__sdsfree(yy__building_binary);
                yy__building_binary = yk__sdsdup(t__158);
                yk__sdsfree(t__158);
                yk__sdsfree(t__157);
                yk__sdsfree(t__156);
                yk__sdsfree(t__155);
            }
            else
            {
                yk__sds t__159 = yk__sdsnewlen("lib", 3);
                yk__sds t__160 = yk__sdscatsds(yk__sdsdup(t__159), yy__building_binary);
                yk__sds t__161 = yk__sdsnewlen(".so", 3);
                yk__sds t__162 = yk__sdscatsds(yk__sdsdup(t__160), t__161);
                yk__sdsfree(yy__building_binary);
                yy__building_binary = yk__sdsdup(t__162);
                yk__sdsfree(t__162);
                yk__sdsfree(t__161);
                yk__sdsfree(t__160);
                yk__sdsfree(t__159);
            }
        }
    }
    else
    {
        if (yy__building_is_target_windows(yk__sdsdup(yy__building_target)))
        {
            yk__sds t__163 = yk__sdsnewlen(".exe", 4);
            yk__sds t__164 = yk__sdscatsds(yk__sdsdup(yy__building_binary), t__163);
            yk__sdsfree(yy__building_binary);
            yy__building_binary = yk__sdsdup(t__164);
            yk__sdsfree(t__164);
            yk__sdsfree(t__163);
        }
    }
    yk__sds t__165 = yk__sdsnewlen("web", 3);
    if ((yk__sdscmp(yy__building_target , t__165) == 0))
    {
        yk__sds t__166 = yk__sdsnewlen(".html", 5);
        yk__sds t__167 = yk__sdscatsds(yk__sdsdup(yy__building_binary), t__166);
        yk__sdsfree(yy__building_binary);
        yy__building_binary = yk__sdsdup(t__167);
        yk__sdsfree(t__167);
        yk__sdsfree(t__166);
    }
    yk__sds t__168 = yk__sdsnewlen("wasm4", 5);
    if ((yk__sdscmp(yy__building_target , t__168) == 0))
    {
        yk__sds t__169 = yk__sdsnewlen(".wasm", 5);
        yk__sds t__170 = yk__sdscatsds(yk__sdsdup(yy__building_binary), t__169);
        yk__sdsfree(yy__building_binary);
        yy__building_binary = yk__sdsdup(t__170);
        yk__sdsfree(t__170);
        yk__sdsfree(t__169);
    }
    yk__sds t__171 = yy__path_join(yk__sdsdup(yy__building_build_path), yk__sdsdup(yy__building_binary));
    yk__sdsfree(yy__building_binary);
    yy__building_binary = yk__sdsdup((t__171));
    yk__sds t__172 = yk__sdsnewlen("wasm4", 5);
    if ((yk__sdscmp(yy__building_target , t__172) == 0))
    {
        yk__sds t__173 = yk__sdsnewlen("-femit-bin=", 11);
        yk__sds t__174 = yk__sdscatsds(yk__sdsdup(t__173), yy__building_binary);
        yk__arrput(yy__building_args, yk__sdsdup(t__174));
        yk__sdsfree(t__174);
        yk__sdsfree(t__173);
    }
    else
    {
        yk__arrput(yy__building_args, yk__sdsdup(yy__building_binary));
    }
    yk__sds* t__175 = yy__building_args;
    yy__array_del_str_array(yy__building_ray_other_args);
    yy__array_del_str_array(yy__building_ray_objects);
    yk__sdsfree(t__172);
    yk__sdsfree(t__171);
    yk__sdsfree(t__168);
    yk__sdsfree(t__165);
    yk__sdsfree(t__149);
    yk__sdsfree(t__148);
    yk__sdsfree(yy__building_binary);
    yk__sdsfree(t__146);
    yk__sdsfree(t__124);
    yk__sdsfree(yy__building_the_yk_main);
    yk__sdsfree(t__123);
    yk__sdsfree(t__122);
    yk__sdsfree(yy__building_program_object);
    yk__sdsfree(t__121);
    yk__sdsfree(t__116);
    yk__sdsfree(t__114);
    yk__sdsfree(t__113);
    yk__sdsfree(yy__building_target);
    yk__sdsfree(yy__building_build_path);
    yk__sdsfree(yy__building_code_path);
    return t__175;
}
int32_t yy__building_build_target(struct yy__configuration_Config* yy__building_c, yk__sds yy__building_code_path, yk__sds yy__building_build_path, yk__sds yy__building_target, yk__sds* yy__building_raylib_args) 
{
    bool yy__building_native = (yk__sdslen(yy__building_target) == INT32_C(0));
    yk__sds* yy__building_a = yy__building_create_args(yy__building_c, yk__sdsdup(yy__building_code_path), yk__sdsdup(yy__building_build_path), yk__sdsdup(yy__building_target), yy__building_raylib_args);
    yy__os_ProcessResult yy__building_result = yy__os_run(yy__building_a);
    if (yy__building_native)
    {
        yk__sds t__176 = yk__sdsnewlen("native", 6);
        yy__console_yellow(yk__sdsdup(t__176));
        yk__sdsfree(t__176);
    }
    else
    {
        yy__console_yellow(yk__sdsdup(yy__building_target));
    }
    yk__sds t__177 = yk__sdsnewlen(" := ", 4);
    yy__console_cyan(yk__sdsdup(t__177));
    if (yy__building_result->ok)
    {
        yk__sds t__178 = yk__sdsnewlen("done.\n", 6);
        yy__console_green(yk__sdsdup(t__178));
        yy__os_del_process_result(yy__building_result);
        yy__array_del_str_array(yy__building_a);
        yk__sdsfree(t__178);
        yk__sdsfree(t__177);
        yk__sdsfree(yy__building_target);
        yk__sdsfree(yy__building_build_path);
        yk__sdsfree(yy__building_code_path);
        return INT32_C(0);
        yk__sdsfree(t__178);
    }
    else
    {
        yk__sds t__179 = yk__sdsnewlen("failed.\n", 8);
        yy__console_red(yk__sdsdup(t__179));
        yk__sds t__180 = yk__sdsnewlen("-------\n", 8);
        yy__console_cyan(yk__sdsdup(t__180));
        yk__sds t__181 = yk__sdsnewlen("command := ", 11);
        yy__console_red(yk__sdsdup(t__181));
        yk__sds t__182 = yk__sdsnewlen(" ", 1);
        yk__sds t__183 = yy__array_join(yy__building_a, yk__sdsdup(t__182));
        yy__console_yellow(yk__sdsdup((t__183)));
        yk__sds t__184 = yk__sdsnewlen("\n-------\n", 9);
        yy__console_cyan(yk__sdsdup(t__184));
        yy__console_red(yk__sdsdup(yy__building_result->output));
        yy__os_del_process_result(yy__building_result);
        yy__array_del_str_array(yy__building_a);
        yk__sdsfree(t__184);
        yk__sdsfree(t__183);
        yk__sdsfree(t__182);
        yk__sdsfree(t__181);
        yk__sdsfree(t__180);
        yk__sdsfree(t__179);
        yk__sdsfree(t__177);
        yk__sdsfree(yy__building_target);
        yk__sdsfree(yy__building_build_path);
        yk__sdsfree(yy__building_code_path);
        return INT32_C(1);
        yk__sdsfree(t__184);
        yk__sdsfree(t__183);
        yk__sdsfree(t__182);
        yk__sdsfree(t__181);
        yk__sdsfree(t__180);
        yk__sdsfree(t__179);
    }
}
bool yy__building_print_error(yk__sds yy__building_error, int32_t yy__building_ignored) 
{
    yk__sds t__185 = yk__sdsnewlen("error", 5);
    yy__console_red(yk__sdsdup(t__185));
    yk__sds t__186 = yk__sdsnewlen(":", 1);
    yy__console_yellow(yk__sdsdup(t__186));
    yk__printlnstr((yy__building_error));
    yk__sdsfree(t__186);
    yk__sdsfree(t__185);
    yk__sdsfree(yy__building_error);
    return true;
}
int32_t yy__building_build(struct yy__configuration_Config* yy__building_c, yk__sds yy__building_code) 
{
    yy__configuration_load_runtime_features(yy__building_c, yk__sdsdup(yy__building_code));
    if ((yy__building_c->yy__configuration_compilation->yy__configuration_wasm4 && ((yy__building_c->yy__configuration_compilation->yy__configuration_web || yy__building_c->yy__configuration_compilation->yy__configuration_raylib))))
    {
        yk__sds t__187 = yk__sdsnewlen("WASM4 builds are not compatible with raylib/web builds", 54);
        yk__arrput(yy__building_c->yy__configuration_errors, yk__sdsdup(t__187));
        yk__sdsfree(t__187);
    }
    yk__sds t__188 = yk__sdsempty();
    yk__sds yy__building_target = yk__sdsdup(t__188);
    if ((yk__arrlen(yy__building_c->yy__configuration_errors) > INT32_C(0)))
    {
        yk__sds* t__191 = yy__building_c->yy__configuration_errors;
        int32_t t__193 = INT32_C(0);
        size_t t__190 = yk__arrlenu(t__191);
        bool t__194 = true;
        for (size_t t__189 = 0; t__189 < t__190; t__189++) { 
            yk__sds t__192 = yk__sdsdup(t__191[t__189]);
            bool t__195 = yy__building_print_error(t__192, t__193);
            if (!t__195) {t__194 = false; break; }
        }
        t__194;
        int32_t t__196 = (- (INT32_C(1)));
        yk__sdsfree(yy__building_target);
        yk__sdsfree(t__188);
        yk__sdsfree(yy__building_code);
        return t__196;
    }
    if (yy__building_c->yy__configuration_compilation->yy__configuration_wasm4)
    {
        yk__sds t__197 = yk__sdsnewlen("wasm4", 5);
        yk__sdsfree(yy__building_target);
        yy__building_target = yk__sdsdup(t__197);
        yk__sdsfree(t__197);
    }
    if (yy__building_c->yy__configuration_compilation->yy__configuration_web)
    {
        yk__sds t__198 = yk__sdsnewlen("web", 3);
        yk__sdsfree(yy__building_target);
        yy__building_target = yk__sdsdup(t__198);
        yk__sdsfree(t__198);
    }
    int32_t yy__building_target_count = yk__arrlen(yy__building_c->yy__configuration_compilation->yy__configuration_targets);
    yk__sds* yy__building_raylib_args = NULL;
    if (((yy__building_target_count != INT32_C(0)) && yy__building_c->yy__configuration_compilation->yy__configuration_raylib))
    {
        yk__sds t__199 = yk__sdsnewlen("raylib build only support native builds.\n", 41);
        yy__console_red(yk__sdsdup(t__199));
        yk__sds t__200 = yk__sdsnewlen("Hint: You need to keep [compilation].targets empty\n", 51);
        yy__console_cyan(yk__sdsdup(t__200));
        int32_t t__201 = (- (INT32_C(1)));
        yy__array_del_str_array(yy__building_raylib_args);
        yk__sdsfree(t__200);
        yk__sdsfree(t__199);
        yk__sdsfree(yy__building_target);
        yk__sdsfree(t__188);
        yk__sdsfree(yy__building_code);
        return t__201;
        yk__sdsfree(t__200);
        yk__sdsfree(t__199);
    }
    if (((yy__building_target_count != INT32_C(0)) && yy__building_c->yy__configuration_compilation->yy__configuration_raylib))
    {
        yk__sds t__202 = yk__sdsnewlen("wasm4 build does not support additional targets.\n", 49);
        yy__console_red(yk__sdsdup(t__202));
        yk__sds t__203 = yk__sdsnewlen("Hint: You need to keep [compilation].targets empty\n", 51);
        yy__console_cyan(yk__sdsdup(t__203));
        int32_t t__204 = (- (INT32_C(1)));
        yy__array_del_str_array(yy__building_raylib_args);
        yk__sdsfree(t__203);
        yk__sdsfree(t__202);
        yk__sdsfree(yy__building_target);
        yk__sdsfree(t__188);
        yk__sdsfree(yy__building_code);
        return t__204;
        yk__sdsfree(t__203);
        yk__sdsfree(t__202);
    }
    yk__sds t__205 = yy__os_cwd();
    yk__sds t__206 = yk__sdsnewlen("build", 5);
    yk__sds t__207 = yy__path_join(yk__sdsdup((t__205)), yk__sdsdup(t__206));
    yk__sds yy__building_build_path = yk__sdsdup((t__207));
    if (yy__building_c->yy__configuration_compilation->yy__configuration_raylib)
    {
        yy__building_raylib_args = yy__raylib_support_get_raylib_args(yy__building_c, yk__sdsdup(yy__building_build_path));
    }
    yk__sds t__208 = yk__sdsnewlen("\nbuilding ", 10);
    yk__printstr((t__208));
    yk__printint(((intmax_t)(yy__building_target_count + INT32_C(1))));
    yk__sds t__209 = yk__sdsnewlen(" target(s) ...", 14);
    yk__printlnstr((t__209));
    yy__path_mkdir(yk__sdsdup(yy__building_build_path));
    yk__sds t__210 = yk__sdsnewlen("program_code.c", 14);
    yk__sds t__211 = yy__path_join(yk__sdsdup(yy__building_build_path), yk__sdsdup(t__210));
    yk__sds yy__building_code_path = yk__sdsdup((t__211));
    yk__sds t__212 = yy__building_prepare_code(yy__building_c, yk__sdsdup(yy__building_code));
    if ((! (yy__io_writefile(yk__sdsdup(yy__building_code_path), yk__sdsdup((t__212))))))
    {
        yk__sds t__213 = yk__sdsnewlen("Failed to write file:", 21);
        yy__console_red(yk__sdsdup(t__213));
        yk__printlnstr((yy__building_code_path));
        int32_t t__214 = (- (INT32_C(1)));
        yy__array_del_str_array(yy__building_raylib_args);
        yk__sdsfree(t__213);
        yk__sdsfree(t__212);
        yk__sdsfree(yy__building_code_path);
        yk__sdsfree(t__211);
        yk__sdsfree(t__210);
        yk__sdsfree(t__209);
        yk__sdsfree(t__208);
        yk__sdsfree(yy__building_build_path);
        yk__sdsfree(t__207);
        yk__sdsfree(t__206);
        yk__sdsfree(t__205);
        yk__sdsfree(yy__building_target);
        yk__sdsfree(t__188);
        yk__sdsfree(yy__building_code);
        return t__214;
        yk__sdsfree(t__213);
    }
    int32_t yy__building_failed_count = INT32_C(0);
    yy__building_failed_count = (yy__building_failed_count + yy__building_build_target(yy__building_c, yk__sdsdup(yy__building_code_path), yk__sdsdup(yy__building_build_path), yk__sdsdup(yy__building_target), yy__building_raylib_args));
    int32_t yy__building_cnt = INT32_C(0);
    while (1) {
        if (!((yy__building_cnt < yk__arrlen(yy__building_c->yy__configuration_compilation->yy__configuration_targets)))) { break; } // Check
        // Body of while loop

        {
            yk__sdsfree(yy__building_target);
            yy__building_target = yk__sdsdup(yy__building_c->yy__configuration_compilation->yy__configuration_targets[yy__building_cnt]);
            yy__building_failed_count = (yy__building_failed_count + yy__building_build_target(yy__building_c, yk__sdsdup(yy__building_code_path), yk__sdsdup(yy__building_build_path), yk__sdsdup(yy__building_target), yy__building_raylib_args));
            yy__building_cnt = (yy__building_cnt + INT32_C(1));
        }
    }
    yk__sds t__215 = yk__sdsnewlen("\n", 1);
    yk__printstr((t__215));
    if ((yy__building_failed_count > INT32_C(0)))
    {
        int32_t t__216 = (- (INT32_C(1)));
        yy__array_del_str_array(yy__building_raylib_args);
        yk__sdsfree(t__215);
        yk__sdsfree(t__212);
        yk__sdsfree(yy__building_code_path);
        yk__sdsfree(t__211);
        yk__sdsfree(t__210);
        yk__sdsfree(t__209);
        yk__sdsfree(t__208);
        yk__sdsfree(yy__building_build_path);
        yk__sdsfree(t__207);
        yk__sdsfree(t__206);
        yk__sdsfree(t__205);
        yk__sdsfree(yy__building_target);
        yk__sdsfree(t__188);
        yk__sdsfree(yy__building_code);
        return t__216;
    }
    yy__array_del_str_array(yy__building_raylib_args);
    yk__sdsfree(t__215);
    yk__sdsfree(t__212);
    yk__sdsfree(yy__building_code_path);
    yk__sdsfree(t__211);
    yk__sdsfree(t__210);
    yk__sdsfree(t__209);
    yk__sdsfree(t__208);
    yk__sdsfree(yy__building_build_path);
    yk__sdsfree(t__207);
    yk__sdsfree(t__206);
    yk__sdsfree(t__205);
    yk__sdsfree(yy__building_target);
    yk__sdsfree(t__188);
    yk__sdsfree(yy__building_code);
    return INT32_C(0);
}
int32_t yy__building_build_simple(struct yy__configuration_Config* yy__building_c, yk__sds yy__building_code) 
{
    yy__configuration_load_runtime_features(yy__building_c, yk__sdsdup(yy__building_code));
    if ((yy__building_c->yy__configuration_compilation->yy__configuration_wasm4 && ((yy__building_c->yy__configuration_compilation->yy__configuration_web || yy__building_c->yy__configuration_compilation->yy__configuration_raylib))))
    {
        yk__sds t__217 = yk__sdsnewlen("WASM4 builds are not compatible with raylib/web builds", 54);
        yk__arrput(yy__building_c->yy__configuration_errors, yk__sdsdup(t__217));
        yk__sdsfree(t__217);
    }
    if ((yk__arrlen(yy__building_c->yy__configuration_errors) > INT32_C(0)))
    {
        yk__sds* t__220 = yy__building_c->yy__configuration_errors;
        int32_t t__222 = INT32_C(0);
        size_t t__219 = yk__arrlenu(t__220);
        bool t__223 = true;
        for (size_t t__218 = 0; t__218 < t__219; t__218++) { 
            yk__sds t__221 = yk__sdsdup(t__220[t__218]);
            bool t__224 = yy__building_print_error(t__221, t__222);
            if (!t__224) {t__223 = false; break; }
        }
        t__223;
        int32_t t__225 = (- (INT32_C(1)));
        yk__sdsfree(yy__building_code);
        return t__225;
    }
    yk__sds t__226 = yy__os_cwd();
    yk__sds t__227 = yk__sdsnewlen(".c", 2);
    yk__sds t__228 = yk__sdscatsds(yk__sdsdup(yy__building_c->yy__configuration_project->yy__configuration_name), t__227);
    yk__sds t__229 = yy__path_join(yk__sdsdup((t__226)), yk__sdsdup(t__228));
    yk__sds yy__building_code_path = yk__sdsdup((t__229));
    yk__sds* yy__building_raylib_args = NULL;
    yk__sds t__230 = yk__sdsempty();
    yk__sds yy__building_target = yk__sdsdup(t__230);
    if (yy__building_c->yy__configuration_compilation->yy__configuration_raylib)
    {
        yk__sds t__231 = yy__os_cwd();
        yy__building_raylib_args = yy__raylib_support_get_raylib_args(yy__building_c, yk__sdsdup((t__231)));
        yk__sdsfree(t__231);
    }
    if (yy__building_c->yy__configuration_compilation->yy__configuration_wasm4)
    {
        yk__sds t__232 = yk__sdsnewlen("wasm4", 5);
        yk__sdsfree(yy__building_target);
        yy__building_target = yk__sdsdup(t__232);
        yk__sdsfree(t__232);
    }
    if (yy__building_c->yy__configuration_compilation->yy__configuration_web)
    {
        yk__sds t__233 = yk__sdsnewlen("web", 3);
        yk__sdsfree(yy__building_target);
        yy__building_target = yk__sdsdup(t__233);
        yk__sdsfree(t__233);
    }
    yk__sds t__234 = yy__building_prepare_code(yy__building_c, yk__sdsdup(yy__building_code));
    if ((! (yy__io_writefile(yk__sdsdup(yy__building_code_path), yk__sdsdup((t__234))))))
    {
        yk__sds t__235 = yk__sdsnewlen("Failed to write file:", 21);
        yy__console_red(yk__sdsdup(t__235));
        yk__printlnstr((yy__building_code_path));
        int32_t t__236 = (- (INT32_C(1)));
        yy__array_del_str_array(yy__building_raylib_args);
        yk__sdsfree(t__235);
        yk__sdsfree(t__234);
        yk__sdsfree(yy__building_target);
        yk__sdsfree(t__230);
        yk__sdsfree(yy__building_code_path);
        yk__sdsfree(t__229);
        yk__sdsfree(t__228);
        yk__sdsfree(t__227);
        yk__sdsfree(t__226);
        yk__sdsfree(yy__building_code);
        return t__236;
        yk__sdsfree(t__235);
    }
    yk__sds t__237 = yy__os_cwd();
    int32_t yy__building_failed_count = yy__building_build_target(yy__building_c, yk__sdsdup(yy__building_code_path), yk__sdsdup((t__237)), yk__sdsdup(yy__building_target), yy__building_raylib_args);
    if ((yy__building_failed_count > INT32_C(0)))
    {
        int32_t t__238 = (- (INT32_C(1)));
        yy__array_del_str_array(yy__building_raylib_args);
        yk__sdsfree(t__237);
        yk__sdsfree(t__234);
        yk__sdsfree(yy__building_target);
        yk__sdsfree(t__230);
        yk__sdsfree(yy__building_code_path);
        yk__sdsfree(t__229);
        yk__sdsfree(t__228);
        yk__sdsfree(t__227);
        yk__sdsfree(t__226);
        yk__sdsfree(yy__building_code);
        return t__238;
    }
    yy__array_del_str_array(yy__building_raylib_args);
    yk__sdsfree(t__237);
    yk__sdsfree(t__234);
    yk__sdsfree(yy__building_target);
    yk__sdsfree(t__230);
    yk__sdsfree(yy__building_code_path);
    yk__sdsfree(t__229);
    yk__sdsfree(t__228);
    yk__sdsfree(t__227);
    yk__sdsfree(t__226);
    yk__sdsfree(yy__building_code);
    return INT32_C(0);
}
void yy__configuration_find_runtime_path(struct yy__configuration_Config* yy__configuration_c) 
{
    yk__sds t__0 = yy__os_exe_path();
    yk__sds yy__configuration_exe_parent = yk__sdsdup((t__0));
    yk__sds t__1 = yy__path_dirname(yk__sdsdup(yy__configuration_exe_parent));
    yk__sds t__2 = yk__sdsnewlen("runtime", 7);
    yk__sds t__3 = yy__path_join(yk__sdsdup((t__1)), yk__sdsdup(t__2));
    yk__sds yy__configuration_l1 = yk__sdsdup((t__3));
    yk__sds t__4 = yy__path_dirname(yk__sdsdup(yy__configuration_exe_parent));
    yk__sds t__5 = yy__path_dirname(yk__sdsdup((t__4)));
    yk__sds t__6 = yk__sdsnewlen("runtime", 7);
    yk__sds t__7 = yy__path_join(yk__sdsdup((t__5)), yk__sdsdup(t__6));
    yk__sds yy__configuration_l2 = yk__sdsdup((t__7));
    yk__sds t__8 = yk__sdsnewlen("runtime", 7);
    yk__sds t__9 = yy__path_join(yk__sdsdup(yy__configuration_exe_parent), yk__sdsdup(t__8));
    yk__sds yy__configuration_l3 = yk__sdsdup((t__9));
    yk__sds t__10 = yk__sdsnewlen("yk__lib.h", 9);
    yk__sds t__11 = yy__path_join(yk__sdsdup(yy__configuration_l1), yk__sdsdup(t__10));
    if (yy__path_readable(yk__sdsdup((t__11))))
    {
        yk__sdsfree(yy__configuration_c->yy__configuration_runtime_path);
        yy__configuration_c->yy__configuration_runtime_path = yk__sdsdup(yy__configuration_l1);
        yk__sdsfree(t__11);
        yk__sdsfree(t__10);
        yk__sdsfree(yy__configuration_l3);
        yk__sdsfree(t__9);
        yk__sdsfree(t__8);
        yk__sdsfree(yy__configuration_l2);
        yk__sdsfree(t__7);
        yk__sdsfree(t__6);
        yk__sdsfree(t__5);
        yk__sdsfree(t__4);
        yk__sdsfree(yy__configuration_l1);
        yk__sdsfree(t__3);
        yk__sdsfree(t__2);
        yk__sdsfree(t__1);
        yk__sdsfree(yy__configuration_exe_parent);
        yk__sdsfree(t__0);
        return;
    }
    yk__sds t__12 = yk__sdsnewlen("yk__lib.h", 9);
    yk__sds t__13 = yy__path_join(yk__sdsdup(yy__configuration_l2), yk__sdsdup(t__12));
    if (yy__path_readable(yk__sdsdup((t__13))))
    {
        yk__sdsfree(yy__configuration_c->yy__configuration_runtime_path);
        yy__configuration_c->yy__configuration_runtime_path = yk__sdsdup(yy__configuration_l2);
        yk__sdsfree(t__13);
        yk__sdsfree(t__12);
        yk__sdsfree(t__11);
        yk__sdsfree(t__10);
        yk__sdsfree(yy__configuration_l3);
        yk__sdsfree(t__9);
        yk__sdsfree(t__8);
        yk__sdsfree(yy__configuration_l2);
        yk__sdsfree(t__7);
        yk__sdsfree(t__6);
        yk__sdsfree(t__5);
        yk__sdsfree(t__4);
        yk__sdsfree(yy__configuration_l1);
        yk__sdsfree(t__3);
        yk__sdsfree(t__2);
        yk__sdsfree(t__1);
        yk__sdsfree(yy__configuration_exe_parent);
        yk__sdsfree(t__0);
        return;
    }
    yk__sds t__14 = yk__sdsnewlen("yk__lib.h", 9);
    yk__sds t__15 = yy__path_join(yk__sdsdup(yy__configuration_l3), yk__sdsdup(t__14));
    if (yy__path_readable(yk__sdsdup((t__15))))
    {
        yk__sdsfree(yy__configuration_c->yy__configuration_runtime_path);
        yy__configuration_c->yy__configuration_runtime_path = yk__sdsdup(yy__configuration_l3);
        yk__sdsfree(t__15);
        yk__sdsfree(t__14);
        yk__sdsfree(t__13);
        yk__sdsfree(t__12);
        yk__sdsfree(t__11);
        yk__sdsfree(t__10);
        yk__sdsfree(yy__configuration_l3);
        yk__sdsfree(t__9);
        yk__sdsfree(t__8);
        yk__sdsfree(yy__configuration_l2);
        yk__sdsfree(t__7);
        yk__sdsfree(t__6);
        yk__sdsfree(t__5);
        yk__sdsfree(t__4);
        yk__sdsfree(yy__configuration_l1);
        yk__sdsfree(t__3);
        yk__sdsfree(t__2);
        yk__sdsfree(t__1);
        yk__sdsfree(yy__configuration_exe_parent);
        yk__sdsfree(t__0);
        return;
    }
    yk__sds t__16 = yk__sdsnewlen("Failed to find runtime library in :", 35);
    yk__sds t__17 = yk__sdscatsds(yk__sdsdup(t__16), yy__configuration_l1);
    yk__arrput(yy__configuration_c->yy__configuration_errors, yk__sdsdup(t__17));
    yk__sds t__18 = yk__sdsnewlen("Failed to find runtime library in :", 35);
    yk__sds t__19 = yk__sdscatsds(yk__sdsdup(t__18), yy__configuration_l2);
    yk__arrput(yy__configuration_c->yy__configuration_errors, yk__sdsdup(t__19));
    yk__sds t__20 = yk__sdsnewlen("Failed to find runtime library in :", 35);
    yk__sds t__21 = yk__sdscatsds(yk__sdsdup(t__20), yy__configuration_l3);
    yk__arrput(yy__configuration_c->yy__configuration_errors, yk__sdsdup(t__21));
    yk__sds t__22 = yk__sdsnewlen("<not found>", 11);
    yk__sdsfree(yy__configuration_c->yy__configuration_runtime_path);
    yy__configuration_c->yy__configuration_runtime_path = yk__sdsdup(t__22);
    yk__sdsfree(t__22);
    yk__sdsfree(t__21);
    yk__sdsfree(t__20);
    yk__sdsfree(t__19);
    yk__sdsfree(t__18);
    yk__sdsfree(t__17);
    yk__sdsfree(t__16);
    yk__sdsfree(t__15);
    yk__sdsfree(t__14);
    yk__sdsfree(t__13);
    yk__sdsfree(t__12);
    yk__sdsfree(t__11);
    yk__sdsfree(t__10);
    yk__sdsfree(yy__configuration_l3);
    yk__sdsfree(t__9);
    yk__sdsfree(t__8);
    yk__sdsfree(yy__configuration_l2);
    yk__sdsfree(t__7);
    yk__sdsfree(t__6);
    yk__sdsfree(t__5);
    yk__sdsfree(t__4);
    yk__sdsfree(yy__configuration_l1);
    yk__sdsfree(t__3);
    yk__sdsfree(t__2);
    yk__sdsfree(t__1);
    yk__sdsfree(yy__configuration_exe_parent);
    yk__sdsfree(t__0);
    return;
}
void yy__configuration_find_libs_path(struct yy__configuration_Config* yy__configuration_c) 
{
    yk__sds t__23 = yy__os_exe_path();
    yk__sds yy__configuration_exe_parent = yk__sdsdup((t__23));
    yk__sds t__24 = yy__path_dirname(yk__sdsdup(yy__configuration_exe_parent));
    yk__sds t__25 = yk__sdsnewlen("libs", 4);
    yk__sds t__26 = yy__path_join(yk__sdsdup((t__24)), yk__sdsdup(t__25));
    yk__sds yy__configuration_l1 = yk__sdsdup((t__26));
    yk__sds t__27 = yy__path_dirname(yk__sdsdup(yy__configuration_exe_parent));
    yk__sds t__28 = yy__path_dirname(yk__sdsdup((t__27)));
    yk__sds t__29 = yk__sdsnewlen("libs", 4);
    yk__sds t__30 = yy__path_join(yk__sdsdup((t__28)), yk__sdsdup(t__29));
    yk__sds yy__configuration_l2 = yk__sdsdup((t__30));
    yk__sds t__31 = yk__sdsnewlen("libs", 4);
    yk__sds t__32 = yy__path_join(yk__sdsdup(yy__configuration_exe_parent), yk__sdsdup(t__31));
    yk__sds yy__configuration_l3 = yk__sdsdup((t__32));
    yk__sds t__33 = yk__sdsnewlen("libs.yaka", 9);
    yk__sds t__34 = yy__path_join(yk__sdsdup(yy__configuration_l1), yk__sdsdup(t__33));
    if (yy__path_readable(yk__sdsdup((t__34))))
    {
        yk__sdsfree(yy__configuration_c->yy__configuration_libs_path);
        yy__configuration_c->yy__configuration_libs_path = yk__sdsdup(yy__configuration_l1);
        yk__sdsfree(t__34);
        yk__sdsfree(t__33);
        yk__sdsfree(yy__configuration_l3);
        yk__sdsfree(t__32);
        yk__sdsfree(t__31);
        yk__sdsfree(yy__configuration_l2);
        yk__sdsfree(t__30);
        yk__sdsfree(t__29);
        yk__sdsfree(t__28);
        yk__sdsfree(t__27);
        yk__sdsfree(yy__configuration_l1);
        yk__sdsfree(t__26);
        yk__sdsfree(t__25);
        yk__sdsfree(t__24);
        yk__sdsfree(yy__configuration_exe_parent);
        yk__sdsfree(t__23);
        return;
    }
    yk__sds t__35 = yk__sdsnewlen("libs.yaka", 9);
    yk__sds t__36 = yy__path_join(yk__sdsdup(yy__configuration_l2), yk__sdsdup(t__35));
    if (yy__path_readable(yk__sdsdup((t__36))))
    {
        yk__sdsfree(yy__configuration_c->yy__configuration_libs_path);
        yy__configuration_c->yy__configuration_libs_path = yk__sdsdup(yy__configuration_l2);
        yk__sdsfree(t__36);
        yk__sdsfree(t__35);
        yk__sdsfree(t__34);
        yk__sdsfree(t__33);
        yk__sdsfree(yy__configuration_l3);
        yk__sdsfree(t__32);
        yk__sdsfree(t__31);
        yk__sdsfree(yy__configuration_l2);
        yk__sdsfree(t__30);
        yk__sdsfree(t__29);
        yk__sdsfree(t__28);
        yk__sdsfree(t__27);
        yk__sdsfree(yy__configuration_l1);
        yk__sdsfree(t__26);
        yk__sdsfree(t__25);
        yk__sdsfree(t__24);
        yk__sdsfree(yy__configuration_exe_parent);
        yk__sdsfree(t__23);
        return;
    }
    yk__sds t__37 = yk__sdsnewlen("libs.yaka", 9);
    yk__sds t__38 = yy__path_join(yk__sdsdup(yy__configuration_l3), yk__sdsdup(t__37));
    if (yy__path_readable(yk__sdsdup((t__38))))
    {
        yk__sdsfree(yy__configuration_c->yy__configuration_libs_path);
        yy__configuration_c->yy__configuration_libs_path = yk__sdsdup(yy__configuration_l3);
        yk__sdsfree(t__38);
        yk__sdsfree(t__37);
        yk__sdsfree(t__36);
        yk__sdsfree(t__35);
        yk__sdsfree(t__34);
        yk__sdsfree(t__33);
        yk__sdsfree(yy__configuration_l3);
        yk__sdsfree(t__32);
        yk__sdsfree(t__31);
        yk__sdsfree(yy__configuration_l2);
        yk__sdsfree(t__30);
        yk__sdsfree(t__29);
        yk__sdsfree(t__28);
        yk__sdsfree(t__27);
        yk__sdsfree(yy__configuration_l1);
        yk__sdsfree(t__26);
        yk__sdsfree(t__25);
        yk__sdsfree(t__24);
        yk__sdsfree(yy__configuration_exe_parent);
        yk__sdsfree(t__23);
        return;
    }
    yk__sds t__39 = yk__sdsnewlen("Failed to find std library in :", 31);
    yk__sds t__40 = yk__sdscatsds(yk__sdsdup(t__39), yy__configuration_l1);
    yk__arrput(yy__configuration_c->yy__configuration_errors, yk__sdsdup(t__40));
    yk__sds t__41 = yk__sdsnewlen("Failed to find std library in :", 31);
    yk__sds t__42 = yk__sdscatsds(yk__sdsdup(t__41), yy__configuration_l2);
    yk__arrput(yy__configuration_c->yy__configuration_errors, yk__sdsdup(t__42));
    yk__sds t__43 = yk__sdsnewlen("Failed to find std library in :", 31);
    yk__sds t__44 = yk__sdscatsds(yk__sdsdup(t__43), yy__configuration_l3);
    yk__arrput(yy__configuration_c->yy__configuration_errors, yk__sdsdup(t__44));
    yk__sds t__45 = yk__sdsnewlen("<not found>", 11);
    yk__sdsfree(yy__configuration_c->yy__configuration_libs_path);
    yy__configuration_c->yy__configuration_libs_path = yk__sdsdup(t__45);
    yk__sdsfree(t__45);
    yk__sdsfree(t__44);
    yk__sdsfree(t__43);
    yk__sdsfree(t__42);
    yk__sdsfree(t__41);
    yk__sdsfree(t__40);
    yk__sdsfree(t__39);
    yk__sdsfree(t__38);
    yk__sdsfree(t__37);
    yk__sdsfree(t__36);
    yk__sdsfree(t__35);
    yk__sdsfree(t__34);
    yk__sdsfree(t__33);
    yk__sdsfree(yy__configuration_l3);
    yk__sdsfree(t__32);
    yk__sdsfree(t__31);
    yk__sdsfree(yy__configuration_l2);
    yk__sdsfree(t__30);
    yk__sdsfree(t__29);
    yk__sdsfree(t__28);
    yk__sdsfree(t__27);
    yk__sdsfree(yy__configuration_l1);
    yk__sdsfree(t__26);
    yk__sdsfree(t__25);
    yk__sdsfree(t__24);
    yk__sdsfree(yy__configuration_exe_parent);
    yk__sdsfree(t__23);
    return;
}
void yy__configuration_find_yaksha_compiler(struct yy__configuration_Config* yy__configuration_c) 
{
    yk__sds t__46 = yy__os_exe_path();
    yk__sds yy__configuration_exe_parent = yk__sdsdup((t__46));
    yk__sds t__47 = yk__sdsnewlen("yaksha", 6);
    yk__sds t__48 = yy__path_join(yk__sdsdup(yy__configuration_exe_parent), yk__sdsdup(t__47));
    yk__sds yy__configuration_l1 = yk__sdsdup((t__48));
    if (yy__os_is_windows())
    {
        yk__sds t__49 = yk__sdsnewlen(".exe", 4);
        yk__sds t__50 = yk__sdscatsds(yk__sdsdup(yy__configuration_l1), t__49);
        yk__sdsfree(yy__configuration_l1);
        yy__configuration_l1 = yk__sdsdup(t__50);
        yk__sdsfree(t__50);
        yk__sdsfree(t__49);
    }
    yk__sds t__51 = yy__path_dirname(yk__sdsdup(yy__configuration_exe_parent));
    yk__sds t__52 = yy__path_dirname(yk__sdsdup((t__51)));
    yk__sds t__53 = yk__sdsnewlen("bin", 3);
    yk__sds t__54 = yy__path_join(yk__sdsdup((t__52)), yk__sdsdup(t__53));
    yk__sds yy__configuration_l2 = yk__sdsdup((t__54));
    yk__sds t__55 = yk__sdsnewlen("yaksha", 6);
    yk__sds t__56 = yy__path_join(yk__sdsdup(yy__configuration_l2), yk__sdsdup(t__55));
    yk__sdsfree(yy__configuration_l2);
    yy__configuration_l2 = yk__sdsdup((t__56));
    if (yy__os_is_windows())
    {
        yk__sds t__57 = yk__sdsnewlen(".exe", 4);
        yk__sds t__58 = yk__sdscatsds(yk__sdsdup(yy__configuration_l2), t__57);
        yk__sdsfree(yy__configuration_l2);
        yy__configuration_l2 = yk__sdsdup(t__58);
        yk__sdsfree(t__58);
        yk__sdsfree(t__57);
    }
    if (yy__path_executable(yk__sdsdup(yy__configuration_l1)))
    {
        yk__sdsfree(yy__configuration_c->yy__configuration_compiler_path);
        yy__configuration_c->yy__configuration_compiler_path = yk__sdsdup(yy__configuration_l1);
        yk__sdsfree(t__56);
        yk__sdsfree(t__55);
        yk__sdsfree(yy__configuration_l2);
        yk__sdsfree(t__54);
        yk__sdsfree(t__53);
        yk__sdsfree(t__52);
        yk__sdsfree(t__51);
        yk__sdsfree(yy__configuration_l1);
        yk__sdsfree(t__48);
        yk__sdsfree(t__47);
        yk__sdsfree(yy__configuration_exe_parent);
        yk__sdsfree(t__46);
        return;
    }
    if (yy__path_executable(yk__sdsdup(yy__configuration_l2)))
    {
        yk__sdsfree(yy__configuration_c->yy__configuration_compiler_path);
        yy__configuration_c->yy__configuration_compiler_path = yk__sdsdup(yy__configuration_l2);
        yk__sdsfree(t__56);
        yk__sdsfree(t__55);
        yk__sdsfree(yy__configuration_l2);
        yk__sdsfree(t__54);
        yk__sdsfree(t__53);
        yk__sdsfree(t__52);
        yk__sdsfree(t__51);
        yk__sdsfree(yy__configuration_l1);
        yk__sdsfree(t__48);
        yk__sdsfree(t__47);
        yk__sdsfree(yy__configuration_exe_parent);
        yk__sdsfree(t__46);
        return;
    }
    yk__sds t__59 = yk__sdsnewlen("yaksha", 6);
    yk__sds t__60 = yy__os_which(yk__sdsdup(t__59));
    yk__sds yy__configuration_fallback = yk__sdsdup((t__60));
    if ((yk__sdslen(yy__configuration_fallback) > INT32_C(0)))
    {
        yk__sdsfree(yy__configuration_c->yy__configuration_compiler_path);
        yy__configuration_c->yy__configuration_compiler_path = yk__sdsdup(yy__configuration_fallback);
        yk__sdsfree(yy__configuration_fallback);
        yk__sdsfree(t__60);
        yk__sdsfree(t__59);
        yk__sdsfree(t__56);
        yk__sdsfree(t__55);
        yk__sdsfree(yy__configuration_l2);
        yk__sdsfree(t__54);
        yk__sdsfree(t__53);
        yk__sdsfree(t__52);
        yk__sdsfree(t__51);
        yk__sdsfree(yy__configuration_l1);
        yk__sdsfree(t__48);
        yk__sdsfree(t__47);
        yk__sdsfree(yy__configuration_exe_parent);
        yk__sdsfree(t__46);
        return;
    }
    yk__sds t__61 = yk__sdsnewlen("Failed to find yaksha in :", 26);
    yk__sds t__62 = yk__sdscatsds(yk__sdsdup(t__61), yy__configuration_l1);
    yk__arrput(yy__configuration_c->yy__configuration_errors, yk__sdsdup(t__62));
    yk__sds t__63 = yk__sdsnewlen("Failed to find yaksha in :", 26);
    yk__sds t__64 = yk__sdscatsds(yk__sdsdup(t__63), yy__configuration_l2);
    yk__arrput(yy__configuration_c->yy__configuration_errors, yk__sdsdup(t__64));
    yk__sds t__65 = yk__sdsnewlen("Failed to find yaksha in PATH", 29);
    yk__arrput(yy__configuration_c->yy__configuration_errors, yk__sdsdup(t__65));
    yk__sds t__66 = yk__sdsnewlen("<not found>", 11);
    yk__sdsfree(yy__configuration_c->yy__configuration_compiler_path);
    yy__configuration_c->yy__configuration_compiler_path = yk__sdsdup(t__66);
    yk__sdsfree(t__66);
    yk__sdsfree(t__65);
    yk__sdsfree(t__64);
    yk__sdsfree(t__63);
    yk__sdsfree(t__62);
    yk__sdsfree(t__61);
    yk__sdsfree(yy__configuration_fallback);
    yk__sdsfree(t__60);
    yk__sdsfree(t__59);
    yk__sdsfree(t__56);
    yk__sdsfree(t__55);
    yk__sdsfree(yy__configuration_l2);
    yk__sdsfree(t__54);
    yk__sdsfree(t__53);
    yk__sdsfree(t__52);
    yk__sdsfree(t__51);
    yk__sdsfree(yy__configuration_l1);
    yk__sdsfree(t__48);
    yk__sdsfree(t__47);
    yk__sdsfree(yy__configuration_exe_parent);
    yk__sdsfree(t__46);
    return;
}
void yy__configuration_find_zig_compiler(struct yy__configuration_Config* yy__configuration_c) 
{
    yk__sds t__67 = yk__sdsnewlen("zig", 3);
    yk__sds t__68 = yy__os_which(yk__sdsdup(t__67));
    yk__sds yy__configuration_zig = yk__sdsdup((t__68));
    if ((yk__sdslen(yy__configuration_zig) > INT32_C(0)))
    {
        yk__sdsfree(yy__configuration_c->yy__configuration_zig_compiler_path);
        yy__configuration_c->yy__configuration_zig_compiler_path = yk__sdsdup(yy__configuration_zig);
        yk__sdsfree(yy__configuration_zig);
        yk__sdsfree(t__68);
        yk__sdsfree(t__67);
        return;
    }
    if ((! (yy__configuration_c->yy__configuration_compilation->yy__configuration_web)))
    {
        yk__sds t__69 = yk__sdsnewlen("Failed to find zig in PATH", 26);
        yk__arrput(yy__configuration_c->yy__configuration_errors, yk__sdsdup(t__69));
        yk__sdsfree(t__69);
    }
    yk__sds t__70 = yk__sdsnewlen("<not found>", 11);
    yk__sdsfree(yy__configuration_c->yy__configuration_zig_compiler_path);
    yy__configuration_c->yy__configuration_zig_compiler_path = yk__sdsdup(t__70);
    yk__sdsfree(t__70);
    yk__sdsfree(yy__configuration_zig);
    yk__sdsfree(t__68);
    yk__sdsfree(t__67);
    return;
}
void yy__configuration_find_emsdk(struct yy__configuration_Config* yy__configuration_c) 
{
    yk__sds t__71 = yk__sdsnewlen("emcc", 4);
    yk__sds t__72 = yy__os_which(yk__sdsdup(t__71));
    yk__sds yy__configuration_emcc = yk__sdsdup((t__72));
    yk__sds t__73 = yk__sdsnewlen("emrun", 5);
    yk__sds t__74 = yy__os_which(yk__sdsdup(t__73));
    yk__sds yy__configuration_emrun = yk__sdsdup((t__74));
    bool yy__configuration_not_found = ((yk__sdslen(yy__configuration_emcc) == INT32_C(0)) || (yk__sdslen(yy__configuration_emrun) == INT32_C(0)));
    if ((yy__configuration_c->yy__configuration_compilation->yy__configuration_web && yy__configuration_not_found))
    {
        yk__sds t__75 = yk__sdsnewlen("Failed to find emsdk (emcc, emrun) in PATH", 42);
        yk__arrput(yy__configuration_c->yy__configuration_errors, yk__sdsdup(t__75));
        yk__sds t__76 = yk__sdsnewlen("<not found>", 11);
        yk__sdsfree(yy__configuration_c->yy__configuration_emcc_compiler_path);
        yy__configuration_c->yy__configuration_emcc_compiler_path = yk__sdsdup(t__76);
        yk__sds t__77 = yk__sdsnewlen("<not found>", 11);
        yk__sdsfree(yy__configuration_c->yy__configuration_emrun_path);
        yy__configuration_c->yy__configuration_emrun_path = yk__sdsdup(t__77);
        yk__sdsfree(t__77);
        yk__sdsfree(t__76);
        yk__sdsfree(t__75);
    }
    else
    {
        yk__sdsfree(yy__configuration_c->yy__configuration_emcc_compiler_path);
        yy__configuration_c->yy__configuration_emcc_compiler_path = yk__sdsdup(yy__configuration_emcc);
        yk__sdsfree(yy__configuration_c->yy__configuration_emrun_path);
        yy__configuration_c->yy__configuration_emrun_path = yk__sdsdup(yy__configuration_emrun);
    }
    yk__sdsfree(yy__configuration_emrun);
    yk__sdsfree(t__74);
    yk__sdsfree(t__73);
    yk__sdsfree(yy__configuration_emcc);
    yk__sdsfree(t__72);
    yk__sdsfree(t__71);
    return;
}
void yy__configuration_find_w4(struct yy__configuration_Config* yy__configuration_c) 
{
    yk__sds t__78 = yk__sdsnewlen("w4", 2);
    yk__sds t__79 = yy__os_which(yk__sdsdup(t__78));
    yk__sds yy__configuration_w4 = yk__sdsdup((t__79));
    bool yy__configuration_not_found = (yk__sdslen(yy__configuration_w4) == INT32_C(0));
    if ((yy__configuration_c->yy__configuration_compilation->yy__configuration_wasm4 && yy__configuration_not_found))
    {
        yk__sds t__80 = yk__sdsnewlen("Failed to find w4 in PATH", 25);
        yk__arrput(yy__configuration_c->yy__configuration_errors, yk__sdsdup(t__80));
        yk__sds t__81 = yk__sdsnewlen("<not found>", 11);
        yk__sdsfree(yy__configuration_c->yy__configuration_w4_path);
        yy__configuration_c->yy__configuration_w4_path = yk__sdsdup(t__81);
        yk__sdsfree(t__81);
        yk__sdsfree(t__80);
    }
    else
    {
        yk__sdsfree(yy__configuration_c->yy__configuration_w4_path);
        yy__configuration_c->yy__configuration_w4_path = yk__sdsdup(yy__configuration_w4);
    }
    yk__sdsfree(yy__configuration_w4);
    yk__sdsfree(t__79);
    yk__sdsfree(t__78);
    return;
}
struct yy__configuration_Project* yy__configuration_load_project(yy__toml_Table yy__configuration_conf, struct yy__configuration_Config* yy__configuration_c) 
{
    struct yy__configuration_Project* yy__configuration_p = calloc(1, sizeof(struct yy__configuration_Project));
    yk__sds t__82 = yk__sdsnewlen("project", 7);
    yy__toml_Table yy__configuration_project = yy__toml_get_table(yy__configuration_conf, yk__sdsdup(t__82));
    if ((! (yy__toml_valid_table(yy__configuration_project))))
    {
        yk__sds t__83 = yk__sdsnewlen("Failed to read \'[project]\'", 26);
        yk__arrput(yy__configuration_c->yy__configuration_errors, yk__sdsdup(t__83));
        struct yy__configuration_Project* t__84 = yy__configuration_p;
        yk__sdsfree(t__83);
        yk__sdsfree(t__82);
        return t__84;
        yk__sdsfree(t__83);
    }
    yk__sds t__85 = yk__sdsnewlen("main", 4);
    yk__sds t__86 = yy__toml_get_string(yy__configuration_project, yk__sdsdup(t__85));
    yk__sds yy__configuration_main_code_file = yk__sdsdup((t__86));
    yk__sds t__87 = yk__sdsnewlen("name", 4);
    yk__sds t__88 = yy__toml_get_string(yy__configuration_project, yk__sdsdup(t__87));
    yk__sds yy__configuration_project_name = yk__sdsdup((t__88));
    yk__sds t__89 = yk__sdsnewlen("author", 6);
    yk__sds t__90 = yy__toml_get_string(yy__configuration_project, yk__sdsdup(t__89));
    yk__sds yy__configuration_project_author = yk__sdsdup((t__90));
    yk__sds t__91 = yk__sdsempty();
    if ((yk__sdscmp(yy__configuration_main_code_file , t__91) == 0))
    {
        yk__sds t__92 = yk__sdsnewlen("Invalid \'[project].main\'", 24);
        yk__arrput(yy__configuration_c->yy__configuration_errors, yk__sdsdup(t__92));
        yk__sdsfree(t__92);
    }
    yk__sds t__93 = yk__sdsempty();
    if ((yk__sdscmp(yy__configuration_project_name , t__93) == 0))
    {
        yk__sds t__94 = yk__sdsnewlen("Invalid \'[project].name\'", 24);
        yk__arrput(yy__configuration_c->yy__configuration_errors, yk__sdsdup(t__94));
        yk__sdsfree(t__94);
    }
    yk__sds t__95 = yk__sdsempty();
    if ((yk__sdscmp(yy__configuration_project_author , t__95) == 0))
    {
        yk__sds t__96 = yk__sdsnewlen("Invalid \'[project].author\'", 26);
        yk__arrput(yy__configuration_c->yy__configuration_errors, yk__sdsdup(t__96));
        yk__sdsfree(t__96);
    }
    yk__sdsfree(yy__configuration_p->yy__configuration_main);
    yy__configuration_p->yy__configuration_main = yk__sdsdup(yy__configuration_main_code_file);
    yk__sdsfree(yy__configuration_p->yy__configuration_author);
    yy__configuration_p->yy__configuration_author = yk__sdsdup(yy__configuration_project_author);
    yk__sdsfree(yy__configuration_p->yy__configuration_name);
    yy__configuration_p->yy__configuration_name = yk__sdsdup(yy__configuration_project_name);
    struct yy__configuration_Project* t__97 = yy__configuration_p;
    yk__sdsfree(t__95);
    yk__sdsfree(t__93);
    yk__sdsfree(t__91);
    yk__sdsfree(yy__configuration_project_author);
    yk__sdsfree(t__90);
    yk__sdsfree(t__89);
    yk__sdsfree(yy__configuration_project_name);
    yk__sdsfree(t__88);
    yk__sdsfree(t__87);
    yk__sdsfree(yy__configuration_main_code_file);
    yk__sdsfree(t__86);
    yk__sdsfree(t__85);
    yk__sdsfree(t__82);
    return t__97;
}
struct yy__configuration_CCode* yy__configuration_load_c_code(yy__toml_Table yy__configuration_conf, struct yy__configuration_Config* yy__configuration_c) 
{
    struct yy__configuration_CCode* yy__configuration_cc = calloc(1, sizeof(struct yy__configuration_CCode));
    yk__sds t__98 = yk__sdsnewlen("ccode", 5);
    yy__toml_Table yy__configuration_cc_data = yy__toml_get_table(yy__configuration_conf, yk__sdsdup(t__98));
    if ((! (yy__toml_valid_table(yy__configuration_cc_data))))
    {
        struct yy__configuration_CCode* t__99 = yy__configuration_cc;
        yk__sdsfree(t__98);
        return t__99;
    }
    yk__sds t__100 = yk__sdsnewlen("include_paths", 13);
    yy__configuration_cc->yy__configuration_include_paths = yy__toml_get_string_array(yy__configuration_cc_data, yk__sdsdup(t__100));
    yk__sds t__101 = yk__sdsnewlen("defines", 7);
    yy__configuration_cc->yy__configuration_defines = yy__toml_get_string_array(yy__configuration_cc_data, yk__sdsdup(t__101));
    yk__sds t__102 = yk__sdsnewlen("compiler_defines", 16);
    yy__configuration_cc->yy__configuration_compiler_defines = yy__toml_get_string_array(yy__configuration_cc_data, yk__sdsdup(t__102));
    yk__sds t__103 = yk__sdsnewlen("includes", 8);
    yy__configuration_cc->yy__configuration_includes = yy__toml_get_string_array(yy__configuration_cc_data, yk__sdsdup(t__103));
    yk__sds t__104 = yk__sdsnewlen("system_includes", 15);
    yy__configuration_cc->yy__configuration_system_includes = yy__toml_get_string_array(yy__configuration_cc_data, yk__sdsdup(t__104));
    yk__sds t__105 = yk__sdsnewlen("c_code", 6);
    yy__configuration_cc->yy__configuration_c_code = yy__toml_get_string_array(yy__configuration_cc_data, yk__sdsdup(t__105));
    yk__sds t__106 = yk__sdsnewlen("cpp_code", 8);
    yy__configuration_cc->yy__configuration_cpp_code = yy__toml_get_string_array(yy__configuration_cc_data, yk__sdsdup(t__106));
    struct yy__configuration_CCode* t__107 = yy__configuration_cc;
    yk__sdsfree(t__106);
    yk__sdsfree(t__105);
    yk__sdsfree(t__104);
    yk__sdsfree(t__103);
    yk__sdsfree(t__102);
    yk__sdsfree(t__101);
    yk__sdsfree(t__100);
    yk__sdsfree(t__98);
    return t__107;
}
struct yy__configuration_Compilation* yy__configuration_load_compilation(yy__toml_Table yy__configuration_conf, struct yy__configuration_Config* yy__configuration_c) 
{
    struct yy__configuration_Compilation* yy__configuration_co = calloc(1, sizeof(struct yy__configuration_Compilation));
    yk__sds t__108 = yk__sdsnewlen("compilation", 11);
    yy__toml_Table yy__configuration_co_data = yy__toml_get_table(yy__configuration_conf, yk__sdsdup(t__108));
    if ((! (yy__toml_valid_table(yy__configuration_co_data))))
    {
        struct yy__configuration_Compilation* t__109 = yy__configuration_co;
        yk__sdsfree(t__108);
        return t__109;
    }
    yk__sds t__110 = yk__sdsnewlen("targets", 7);
    yy__configuration_co->yy__configuration_targets = yy__toml_get_string_array(yy__configuration_co_data, yk__sdsdup(t__110));
    yk__sds t__111 = yk__sdsnewlen("raylib", 6);
    yy__configuration_co->yy__configuration_raylib = yy__toml_get_bool_default(yy__configuration_co_data, yk__sdsdup(t__111), false);
    yk__sds t__112 = yk__sdsnewlen("raylib_hot_reloading_dll", 24);
    yy__configuration_co->yy__configuration_raylib_hot_reloading_dll = yy__toml_get_bool_default(yy__configuration_co_data, yk__sdsdup(t__112), false);
    yk__sds t__113 = yk__sdsnewlen("disable_parallel_build", 22);
    yy__configuration_co->yy__configuration_disable_parallel_build = yy__toml_get_bool_default(yy__configuration_co_data, yk__sdsdup(t__113), false);
    yk__sds t__114 = yk__sdsnewlen("web", 3);
    yy__configuration_co->yy__configuration_web = yy__toml_get_bool_default(yy__configuration_co_data, yk__sdsdup(t__114), false);
    yk__sds t__115 = yk__sdsnewlen("wasm4", 5);
    yy__configuration_co->yy__configuration_wasm4 = yy__toml_get_bool_default(yy__configuration_co_data, yk__sdsdup(t__115), false);
    yk__sds t__116 = yk__sdsnewlen("web_shell", 9);
    yk__sds t__117 = yy__toml_get_string(yy__configuration_co_data, yk__sdsdup(t__116));
    yk__sdsfree(yy__configuration_co->yy__configuration_web_shell);
    yy__configuration_co->yy__configuration_web_shell = yk__sdsdup((t__117));
    struct yy__configuration_Compilation* t__118 = yy__configuration_co;
    yk__sdsfree(t__117);
    yk__sdsfree(t__116);
    yk__sdsfree(t__115);
    yk__sdsfree(t__114);
    yk__sdsfree(t__113);
    yk__sdsfree(t__112);
    yk__sdsfree(t__111);
    yk__sdsfree(t__110);
    yk__sdsfree(t__108);
    return t__118;
}
struct yy__configuration_CCode* yy__configuration_inject_c_code_defaults(struct yy__configuration_CCode* yy__configuration_cc, struct yy__configuration_Config* yy__configuration_c) 
{
    yk__sds t__119 = yy__os_cwd();
    yk__sds t__120 = yy__path_dirname(yk__sdsdup((t__119)));
    yk__sds yy__configuration_current_dir = yk__sdsdup((t__120));
    yk__sds t__121 = yk__sdsnewlen("build", 5);
    yk__sds t__122 = yy__path_join(yk__sdsdup(yy__configuration_current_dir), yk__sdsdup(t__121));
    yk__sds* t__123 = NULL;
    yk__arrsetcap(t__123, 2);
    yk__arrput(t__123, yk__sdsdup(yy__configuration_c->yy__configuration_runtime_path));
    yk__arrput(t__123, yk__sdsdup((t__122)));
    yk__sds* yy__configuration_df_include_paths = t__123;
    yk__sds* yy__configuration_orig_include_paths = yy__configuration_cc->yy__configuration_include_paths;
    yy__configuration_cc->yy__configuration_include_paths = yy__array_extend(yy__configuration_df_include_paths, yy__configuration_cc->yy__configuration_include_paths);
    yk__sds t__124 = yk__sdsnewlen("yk__system.h", 12);
    yk__sds* t__125 = NULL;
    yk__arrsetcap(t__125, 1);
    yk__arrput(t__125, yk__sdsdup(t__124));
    yy__configuration_cc->yy__configuration_runtime_feature_includes = t__125;
    yk__sds t__126 = yk__sdsnewlen("yk__system.c", 12);
    yk__sds t__127 = yy__path_join(yk__sdsdup(yy__configuration_c->yy__configuration_runtime_path), yk__sdsdup(t__126));
    yk__sds* t__128 = NULL;
    yk__arrsetcap(t__128, 1);
    yk__arrput(t__128, yk__sdsdup((t__127)));
    yy__configuration_cc->yy__configuration_runtime_feature_c_code = t__128;
    struct yy__configuration_CCode* t__129 = yy__configuration_cc;
    yy__array_del_str_array(yy__configuration_orig_include_paths);
    yk__sdsfree(t__127);
    yk__sdsfree(t__126);
    yk__sdsfree(t__124);
    yk__sdsfree(t__122);
    yk__sdsfree(t__121);
    yk__sdsfree(yy__configuration_current_dir);
    yk__sdsfree(t__120);
    yk__sdsfree(t__119);
    return t__129;
}
struct yy__configuration_Config* yy__configuration_load_runtime_features(struct yy__configuration_Config* yy__configuration_c, yk__sds yy__configuration_code) 
{
    yk__sds t__130 = yk__sdsnewlen("// YK:", 6);
    yk__sds yy__configuration_header = yk__sdsdup(t__130);
    bool yy__configuration_has_requirements = yy__strings_startswith(yk__sdsdup(yy__configuration_code), yk__sdsdup(yy__configuration_header));
    if ((! (yy__configuration_has_requirements)))
    {
        yk__sds t__131 = yk__sdsnewlen("runtime_features", 16);
        yy__console_cyan(yk__sdsdup(t__131));
        yk__sds t__132 = yk__sdsnewlen(" := ", 4);
        yy__console_red(yk__sdsdup(t__132));
        yk__sds t__133 = yk__sdsnewlen("none!", 5);
        yy__console_green(yk__sdsdup(t__133));
        yk__sds t__134 = yk__sdsnewlen("\n", 1);
        yk__printstr((t__134));
        struct yy__configuration_Config* t__135 = yy__configuration_c;
        yk__sdsfree(t__134);
        yk__sdsfree(t__133);
        yk__sdsfree(t__132);
        yk__sdsfree(t__131);
        yk__sdsfree(yy__configuration_header);
        yk__sdsfree(t__130);
        yk__sdsfree(yy__configuration_code);
        return t__135;
        yk__sdsfree(t__134);
        yk__sdsfree(t__133);
        yk__sdsfree(t__132);
        yk__sdsfree(t__131);
    }
    yk__sds t__136 = yk__sdsnewlen("#", 1);
    int32_t yy__configuration_until = yy__strings_find_char(yk__sdsdup(yy__configuration_code), yy__strings_ord(yk__sdsdup(t__136)));
    if ((yy__configuration_until == (- (INT32_C(1)))))
    {
        yk__sds t__137 = yk__sdsnewlen("Failed to extract runtime features. Cannot find # in compiled code first line.", 78);
        yk__arrput(yy__configuration_c->yy__configuration_errors, yk__sdsdup(t__137));
        struct yy__configuration_Config* t__138 = yy__configuration_c;
        yk__sdsfree(t__137);
        yk__sdsfree(t__136);
        yk__sdsfree(yy__configuration_header);
        yk__sdsfree(t__130);
        yk__sdsfree(yy__configuration_code);
        return t__138;
        yk__sdsfree(t__137);
    }
    yk__sds t__139 = yy__strings_mid(yk__sdsdup(yy__configuration_code), yk__sdslen(yy__configuration_header), (yy__configuration_until - yk__sdslen(yy__configuration_header)));
    yk__sds yy__configuration_temp_features = yk__sdsdup((t__139));
    yk__sds t__140 = yk__sdsnewlen("runtime_features", 16);
    yy__console_cyan(yk__sdsdup(t__140));
    yk__sds t__141 = yk__sdsnewlen(" := ", 4);
    yy__console_red(yk__sdsdup(t__141));
    yy__console_green(yk__sdsdup(yy__configuration_temp_features));
    yk__sds t__142 = yk__sdsnewlen("\n", 1);
    yk__printstr((t__142));
    yk__sds t__143 = yk__sdsnewlen(",", 1);
    yk__sds* yy__configuration_features = yy__strings_split(yk__sdsdup(yy__configuration_temp_features), yk__sdsdup(t__143));
    int32_t yy__configuration_x = INT32_C(0);
    int32_t yy__configuration_length = yk__arrlen(yy__configuration_features);
    while (1) {
        if (!((yy__configuration_x < yy__configuration_length))) { break; } // Check
        // Body of while loop

        {
            yk__sds yy__configuration_feature = yk__sdsdup(yy__configuration_features[yy__configuration_x]);
            yy__configuration_x = (yy__configuration_x + INT32_C(1));
            yk__sds t__144 = yk__sdsnewlen("wasm4", 5);
            if ((yk__sdscmp(yy__configuration_feature , t__144) == 0))
            {
                yk__sds t__145 = yk__sdsnewlen("wasm4.h", 7);
                yk__arrput(yy__configuration_c->yy__configuration_c_code->yy__configuration_runtime_feature_includes, yk__sdsdup(t__145));
                yk__sds t__146 = yk__sdsnewlen("yk__wasm4_libc.h", 16);
                yk__arrput(yy__configuration_c->yy__configuration_c_code->yy__configuration_runtime_feature_includes, yk__sdsdup(t__146));
                yk__sds t__147 = yk__sdsnewlen("yk__wasm4_libc.c", 16);
                yk__sds t__148 = yy__path_join(yk__sdsdup(yy__configuration_c->yy__configuration_runtime_path), yk__sdsdup(t__147));
                yk__arrput(yy__configuration_c->yy__configuration_c_code->yy__configuration_runtime_feature_c_code, yk__sdsdup((t__148)));
                yk__sds t__149 = yk__sdsnewlen("YK__WASM4", 9);
                yk__arrput(yy__configuration_c->yy__configuration_c_code->yy__configuration_runtime_feature_compiler_defines, yk__sdsdup(t__149));
                if ((! (yy__configuration_c->yy__configuration_compilation->yy__configuration_wasm4)))
                {
                    yk__sds t__150 = yk__sdsnewlen("wasm4 feature used without configuring it", 41);
                    yk__arrput(yy__configuration_c->yy__configuration_errors, yk__sdsdup(t__150));
                    yk__sdsfree(t__150);
                }
                yk__sdsfree(t__149);
                yk__sdsfree(t__148);
                yk__sdsfree(t__147);
                yk__sdsfree(t__146);
                yk__sdsfree(t__145);
                yk__sdsfree(t__144);
                yk__sdsfree(yy__configuration_feature);
                continue;
                yk__sdsfree(t__149);
                yk__sdsfree(t__148);
                yk__sdsfree(t__147);
                yk__sdsfree(t__146);
                yk__sdsfree(t__145);
            }
            yk__sds t__151 = yk__sdsnewlen("argparse", 8);
            if ((yk__sdscmp(yy__configuration_feature , t__151) == 0))
            {
                yk__sds t__152 = yk__sdsnewlen("yk__argparse.c", 14);
                yk__sds t__153 = yy__path_join(yk__sdsdup(yy__configuration_c->yy__configuration_runtime_path), yk__sdsdup(t__152));
                yk__arrput(yy__configuration_c->yy__configuration_c_code->yy__configuration_runtime_feature_c_code, yk__sdsdup((t__153)));
                yk__sds t__154 = yk__sdsnewlen("argparse.c", 10);
                yk__sds t__155 = yy__path_join(yk__sdsdup(yy__configuration_c->yy__configuration_runtime_path), yk__sdsdup(t__154));
                yk__arrput(yy__configuration_c->yy__configuration_c_code->yy__configuration_runtime_feature_c_code, yk__sdsdup((t__155)));
                yk__sds t__156 = yk__sdsnewlen("yk__argparse.h", 14);
                yk__arrput(yy__configuration_c->yy__configuration_c_code->yy__configuration_runtime_feature_includes, yk__sdsdup(t__156));
                yk__sds t__157 = yk__sdsnewlen("argparse.h", 10);
                yk__arrput(yy__configuration_c->yy__configuration_c_code->yy__configuration_runtime_feature_includes, yk__sdsdup(t__157));
                yk__sdsfree(t__157);
                yk__sdsfree(t__156);
                yk__sdsfree(t__155);
                yk__sdsfree(t__154);
                yk__sdsfree(t__153);
                yk__sdsfree(t__152);
                yk__sdsfree(t__151);
                yk__sdsfree(t__144);
                yk__sdsfree(yy__configuration_feature);
                continue;
                yk__sdsfree(t__157);
                yk__sdsfree(t__156);
                yk__sdsfree(t__155);
                yk__sdsfree(t__154);
                yk__sdsfree(t__153);
                yk__sdsfree(t__152);
            }
            yk__sds t__158 = yk__sdsnewlen("arrayutils", 10);
            if ((yk__sdscmp(yy__configuration_feature , t__158) == 0))
            {
                yk__sds t__159 = yk__sdsnewlen("yk__arrayutils.c", 16);
                yk__sds t__160 = yy__path_join(yk__sdsdup(yy__configuration_c->yy__configuration_runtime_path), yk__sdsdup(t__159));
                yk__arrput(yy__configuration_c->yy__configuration_c_code->yy__configuration_runtime_feature_c_code, yk__sdsdup((t__160)));
                yk__sds t__161 = yk__sdsnewlen("yk__arrayutils.h", 16);
                yk__arrput(yy__configuration_c->yy__configuration_c_code->yy__configuration_runtime_feature_includes, yk__sdsdup(t__161));
                yk__sdsfree(t__161);
                yk__sdsfree(t__160);
                yk__sdsfree(t__159);
                yk__sdsfree(t__158);
                yk__sdsfree(t__151);
                yk__sdsfree(t__144);
                yk__sdsfree(yy__configuration_feature);
                continue;
                yk__sdsfree(t__161);
                yk__sdsfree(t__160);
                yk__sdsfree(t__159);
            }
            yk__sds t__162 = yk__sdsnewlen("console", 7);
            if ((yk__sdscmp(yy__configuration_feature , t__162) == 0))
            {
                yk__sds t__163 = yk__sdsnewlen("yk__console.c", 13);
                yk__sds t__164 = yy__path_join(yk__sdsdup(yy__configuration_c->yy__configuration_runtime_path), yk__sdsdup(t__163));
                yk__arrput(yy__configuration_c->yy__configuration_c_code->yy__configuration_runtime_feature_c_code, yk__sdsdup((t__164)));
                yk__sds t__165 = yk__sdsnewlen("yk__console.h", 13);
                yk__arrput(yy__configuration_c->yy__configuration_c_code->yy__configuration_runtime_feature_includes, yk__sdsdup(t__165));
                yk__sdsfree(t__165);
                yk__sdsfree(t__164);
                yk__sdsfree(t__163);
                yk__sdsfree(t__162);
                yk__sdsfree(t__158);
                yk__sdsfree(t__151);
                yk__sdsfree(t__144);
                yk__sdsfree(yy__configuration_feature);
                continue;
                yk__sdsfree(t__165);
                yk__sdsfree(t__164);
                yk__sdsfree(t__163);
            }
            yk__sds t__166 = yk__sdsnewlen("graphicutils", 12);
            if ((yk__sdscmp(yy__configuration_feature , t__166) == 0))
            {
                yk__sds t__167 = yk__sdsnewlen("yk__graphic_utils.c", 19);
                yk__sds t__168 = yy__path_join(yk__sdsdup(yy__configuration_c->yy__configuration_runtime_path), yk__sdsdup(t__167));
                yk__arrput(yy__configuration_c->yy__configuration_c_code->yy__configuration_runtime_feature_c_code, yk__sdsdup((t__168)));
                yk__sds t__169 = yk__sdsnewlen("yk__graphic_utils.h", 19);
                yk__arrput(yy__configuration_c->yy__configuration_c_code->yy__configuration_runtime_feature_includes, yk__sdsdup(t__169));
                yk__sdsfree(t__169);
                yk__sdsfree(t__168);
                yk__sdsfree(t__167);
                yk__sdsfree(t__166);
                yk__sdsfree(t__162);
                yk__sdsfree(t__158);
                yk__sdsfree(t__151);
                yk__sdsfree(t__144);
                yk__sdsfree(yy__configuration_feature);
                continue;
                yk__sdsfree(t__169);
                yk__sdsfree(t__168);
                yk__sdsfree(t__167);
            }
            yk__sds t__170 = yk__sdsnewlen("ini", 3);
            if ((yk__sdscmp(yy__configuration_feature , t__170) == 0))
            {
                yk__sds t__171 = yk__sdsnewlen("INI_IMPLEMENTATION", 18);
                yk__arrput(yy__configuration_c->yy__configuration_c_code->yy__configuration_runtime_feature_defines, yk__sdsdup(t__171));
                yk__sds t__172 = yk__sdsnewlen("ini.h", 5);
                yk__arrput(yy__configuration_c->yy__configuration_c_code->yy__configuration_runtime_feature_includes, yk__sdsdup(t__172));
                yk__sdsfree(t__172);
                yk__sdsfree(t__171);
                yk__sdsfree(t__170);
                yk__sdsfree(t__166);
                yk__sdsfree(t__162);
                yk__sdsfree(t__158);
                yk__sdsfree(t__151);
                yk__sdsfree(t__144);
                yk__sdsfree(yy__configuration_feature);
                continue;
                yk__sdsfree(t__172);
                yk__sdsfree(t__171);
            }
            yk__sds t__173 = yk__sdsnewlen("process", 7);
            if ((yk__sdscmp(yy__configuration_feature , t__173) == 0))
            {
                yk__sds t__174 = yk__sdsnewlen("yk__process.c", 13);
                yk__sds t__175 = yy__path_join(yk__sdsdup(yy__configuration_c->yy__configuration_runtime_path), yk__sdsdup(t__174));
                yk__arrput(yy__configuration_c->yy__configuration_c_code->yy__configuration_runtime_feature_c_code, yk__sdsdup((t__175)));
                yk__sds t__176 = yk__sdsnewlen("yk__process.h", 13);
                yk__arrput(yy__configuration_c->yy__configuration_c_code->yy__configuration_runtime_feature_includes, yk__sdsdup(t__176));
                yk__sdsfree(t__176);
                yk__sdsfree(t__175);
                yk__sdsfree(t__174);
                yk__sdsfree(t__173);
                yk__sdsfree(t__170);
                yk__sdsfree(t__166);
                yk__sdsfree(t__162);
                yk__sdsfree(t__158);
                yk__sdsfree(t__151);
                yk__sdsfree(t__144);
                yk__sdsfree(yy__configuration_feature);
                continue;
                yk__sdsfree(t__176);
                yk__sdsfree(t__175);
                yk__sdsfree(t__174);
            }
            yk__sds t__177 = yk__sdsnewlen("cpu", 3);
            if ((yk__sdscmp(yy__configuration_feature , t__177) == 0))
            {
                yk__sds t__178 = yk__sdsnewlen("yk__cpu.c", 9);
                yk__sds t__179 = yy__path_join(yk__sdsdup(yy__configuration_c->yy__configuration_runtime_path), yk__sdsdup(t__178));
                yk__arrput(yy__configuration_c->yy__configuration_c_code->yy__configuration_runtime_feature_c_code, yk__sdsdup((t__179)));
                yk__sds t__180 = yk__sdsnewlen("yk__cpu.h", 9);
                yk__arrput(yy__configuration_c->yy__configuration_c_code->yy__configuration_runtime_feature_includes, yk__sdsdup(t__180));
                yk__sdsfree(t__180);
                yk__sdsfree(t__179);
                yk__sdsfree(t__178);
                yk__sdsfree(t__177);
                yk__sdsfree(t__173);
                yk__sdsfree(t__170);
                yk__sdsfree(t__166);
                yk__sdsfree(t__162);
                yk__sdsfree(t__158);
                yk__sdsfree(t__151);
                yk__sdsfree(t__144);
                yk__sdsfree(yy__configuration_feature);
                continue;
                yk__sdsfree(t__180);
                yk__sdsfree(t__179);
                yk__sdsfree(t__178);
            }
            yk__sds t__181 = yk__sdsnewlen("raylib", 6);
            if ((yk__sdscmp(yy__configuration_feature , t__181) == 0))
            {
                if ((! (yy__configuration_c->yy__configuration_compilation->yy__configuration_raylib)))
                {
                    yk__sds t__182 = yk__sdsnewlen("raylib feature used without configuring it", 42);
                    yk__arrput(yy__configuration_c->yy__configuration_errors, yk__sdsdup(t__182));
                    yk__sdsfree(t__182);
                }
                yk__sdsfree(t__181);
                yk__sdsfree(t__177);
                yk__sdsfree(t__173);
                yk__sdsfree(t__170);
                yk__sdsfree(t__166);
                yk__sdsfree(t__162);
                yk__sdsfree(t__158);
                yk__sdsfree(t__151);
                yk__sdsfree(t__144);
                yk__sdsfree(yy__configuration_feature);
                continue;
            }
            yk__sds t__183 = yk__sdsnewlen("tinycthread", 11);
            if ((yk__sdscmp(yy__configuration_feature , t__183) == 0))
            {
                yk__sds t__184 = yk__sdsnewlen("tinycthread.c", 13);
                yk__sds t__185 = yy__path_join(yk__sdsdup(yy__configuration_c->yy__configuration_runtime_path), yk__sdsdup(t__184));
                yk__arrput(yy__configuration_c->yy__configuration_c_code->yy__configuration_runtime_feature_c_code, yk__sdsdup((t__185)));
                yk__sds t__186 = yk__sdsnewlen("tinycthread.h", 13);
                yk__arrput(yy__configuration_c->yy__configuration_c_code->yy__configuration_runtime_feature_includes, yk__sdsdup(t__186));
                yk__sdsfree(t__186);
                yk__sdsfree(t__185);
                yk__sdsfree(t__184);
                yk__sdsfree(t__183);
                yk__sdsfree(t__181);
                yk__sdsfree(t__177);
                yk__sdsfree(t__173);
                yk__sdsfree(t__170);
                yk__sdsfree(t__166);
                yk__sdsfree(t__162);
                yk__sdsfree(t__158);
                yk__sdsfree(t__151);
                yk__sdsfree(t__144);
                yk__sdsfree(yy__configuration_feature);
                continue;
                yk__sdsfree(t__186);
                yk__sdsfree(t__185);
                yk__sdsfree(t__184);
            }
            yk__sds t__187 = yk__sdsnewlen("toml", 4);
            if ((yk__sdscmp(yy__configuration_feature , t__187) == 0))
            {
                yk__sds t__188 = yk__sdsnewlen("toml.c", 6);
                yk__sds t__189 = yy__path_join(yk__sdsdup(yy__configuration_c->yy__configuration_runtime_path), yk__sdsdup(t__188));
                yk__arrput(yy__configuration_c->yy__configuration_c_code->yy__configuration_runtime_feature_c_code, yk__sdsdup((t__189)));
                yk__sds t__190 = yk__sdsnewlen("toml.h", 6);
                yk__arrput(yy__configuration_c->yy__configuration_c_code->yy__configuration_runtime_feature_includes, yk__sdsdup(t__190));
                yk__sdsfree(t__190);
                yk__sdsfree(t__189);
                yk__sdsfree(t__188);
                yk__sdsfree(t__187);
                yk__sdsfree(t__183);
                yk__sdsfree(t__181);
                yk__sdsfree(t__177);
                yk__sdsfree(t__173);
                yk__sdsfree(t__170);
                yk__sdsfree(t__166);
                yk__sdsfree(t__162);
                yk__sdsfree(t__158);
                yk__sdsfree(t__151);
                yk__sdsfree(t__144);
                yk__sdsfree(yy__configuration_feature);
                continue;
                yk__sdsfree(t__190);
                yk__sdsfree(t__189);
                yk__sdsfree(t__188);
            }
            yk__sds t__191 = yk__sdsnewlen("utf8proc", 8);
            if ((yk__sdscmp(yy__configuration_feature , t__191) == 0))
            {
                yk__sds t__192 = yk__sdsnewlen("utf8proc.c", 10);
                yk__sds t__193 = yy__path_join(yk__sdsdup(yy__configuration_c->yy__configuration_runtime_path), yk__sdsdup(t__192));
                yk__arrput(yy__configuration_c->yy__configuration_c_code->yy__configuration_runtime_feature_c_code, yk__sdsdup((t__193)));
                yk__sds t__194 = yk__sdsnewlen("UTF8PROC_STATIC", 15);
                yk__arrput(yy__configuration_c->yy__configuration_c_code->yy__configuration_runtime_feature_compiler_defines, yk__sdsdup(t__194));
                yk__sds t__195 = yk__sdsnewlen("utf8proc.h", 10);
                yk__arrput(yy__configuration_c->yy__configuration_c_code->yy__configuration_runtime_feature_includes, yk__sdsdup(t__195));
                yk__sds t__196 = yk__sdsnewlen("yk__utf8iter.h", 14);
                yk__arrput(yy__configuration_c->yy__configuration_c_code->yy__configuration_runtime_feature_includes, yk__sdsdup(t__196));
                yk__sdsfree(t__196);
                yk__sdsfree(t__195);
                yk__sdsfree(t__194);
                yk__sdsfree(t__193);
                yk__sdsfree(t__192);
                yk__sdsfree(t__191);
                yk__sdsfree(t__187);
                yk__sdsfree(t__183);
                yk__sdsfree(t__181);
                yk__sdsfree(t__177);
                yk__sdsfree(t__173);
                yk__sdsfree(t__170);
                yk__sdsfree(t__166);
                yk__sdsfree(t__162);
                yk__sdsfree(t__158);
                yk__sdsfree(t__151);
                yk__sdsfree(t__144);
                yk__sdsfree(yy__configuration_feature);
                continue;
                yk__sdsfree(t__196);
                yk__sdsfree(t__195);
                yk__sdsfree(t__194);
                yk__sdsfree(t__193);
                yk__sdsfree(t__192);
            }
            yk__sds t__197 = yk__sdsnewlen("whereami", 8);
            if ((yk__sdscmp(yy__configuration_feature , t__197) == 0))
            {
                if (yy__configuration_c->yy__configuration_compilation->yy__configuration_web)
                {
                    yk__sds t__198 = yk__sdsnewlen("yk__fake_whereami.c", 19);
                    yk__sds t__199 = yy__path_join(yk__sdsdup(yy__configuration_c->yy__configuration_runtime_path), yk__sdsdup(t__198));
                    yk__arrput(yy__configuration_c->yy__configuration_c_code->yy__configuration_runtime_feature_c_code, yk__sdsdup((t__199)));
                    yk__sdsfree(t__199);
                    yk__sdsfree(t__198);
                }
                else
                {
                    yk__sds t__200 = yk__sdsnewlen("whereami.c", 10);
                    yk__sds t__201 = yy__path_join(yk__sdsdup(yy__configuration_c->yy__configuration_runtime_path), yk__sdsdup(t__200));
                    yk__arrput(yy__configuration_c->yy__configuration_c_code->yy__configuration_runtime_feature_c_code, yk__sdsdup((t__201)));
                    yk__sdsfree(t__201);
                    yk__sdsfree(t__200);
                }
                yk__sds t__202 = yk__sdsnewlen("whereami.h", 10);
                yk__arrput(yy__configuration_c->yy__configuration_c_code->yy__configuration_runtime_feature_includes, yk__sdsdup(t__202));
                yk__sdsfree(t__202);
                yk__sdsfree(t__197);
                yk__sdsfree(t__191);
                yk__sdsfree(t__187);
                yk__sdsfree(t__183);
                yk__sdsfree(t__181);
                yk__sdsfree(t__177);
                yk__sdsfree(t__173);
                yk__sdsfree(t__170);
                yk__sdsfree(t__166);
                yk__sdsfree(t__162);
                yk__sdsfree(t__158);
                yk__sdsfree(t__151);
                yk__sdsfree(t__144);
                yk__sdsfree(yy__configuration_feature);
                continue;
                yk__sdsfree(t__202);
            }
            yk__sds t__203 = yk__sdsnewlen("Invalid runtime feature: ", 25);
            yk__sds t__204 = yk__sdscatsds(yk__sdsdup(t__203), yy__configuration_feature);
            yk__arrput(yy__configuration_c->yy__configuration_errors, yk__sdsdup(t__204));
            yk__sdsfree(t__204);
            yk__sdsfree(t__203);
            yk__sdsfree(t__197);
            yk__sdsfree(t__191);
            yk__sdsfree(t__187);
            yk__sdsfree(t__183);
            yk__sdsfree(t__181);
            yk__sdsfree(t__177);
            yk__sdsfree(t__173);
            yk__sdsfree(t__170);
            yk__sdsfree(t__166);
            yk__sdsfree(t__162);
            yk__sdsfree(t__158);
            yk__sdsfree(t__151);
            yk__sdsfree(t__144);
            yk__sdsfree(yy__configuration_feature);
            break;
            yk__sdsfree(t__204);
            yk__sdsfree(t__203);
            yk__sdsfree(t__197);
            yk__sdsfree(t__191);
            yk__sdsfree(t__187);
            yk__sdsfree(t__183);
            yk__sdsfree(t__181);
            yk__sdsfree(t__177);
            yk__sdsfree(t__173);
            yk__sdsfree(t__170);
            yk__sdsfree(t__166);
            yk__sdsfree(t__162);
            yk__sdsfree(t__158);
            yk__sdsfree(t__151);
            yk__sdsfree(t__144);
            yk__sdsfree(yy__configuration_feature);
        }
    }
    struct yy__configuration_Config* t__205 = yy__configuration_c;
    yy__array_del_str_array(yy__configuration_features);
    yk__sdsfree(t__143);
    yk__sdsfree(t__142);
    yk__sdsfree(t__141);
    yk__sdsfree(t__140);
    yk__sdsfree(yy__configuration_temp_features);
    yk__sdsfree(t__139);
    yk__sdsfree(t__136);
    yk__sdsfree(yy__configuration_header);
    yk__sdsfree(t__130);
    yk__sdsfree(yy__configuration_code);
    return t__205;
}
struct yy__configuration_Config* yy__configuration_load_config() 
{
    struct yy__configuration_Config* yy__configuration_c = calloc(1, sizeof(struct yy__configuration_Config));
    yk__sds t__206 = yy__os_cwd();
    yk__sds t__207 = yk__sdsnewlen("yaksha.toml", 11);
    yk__sds t__208 = yy__path_join(yk__sdsdup((t__206)), yk__sdsdup(t__207));
    yk__sds yy__configuration_configf = yk__sdsdup((t__208));
    yk__sds t__209 = yy__io_readfile(yk__sdsdup(yy__configuration_configf));
    yk__sds yy__configuration_config_text = yk__sdsdup((t__209));
    yy__toml_Table yy__configuration_conf = yy__toml_from_str(yk__sdsdup(yy__configuration_config_text));
    if ((! (yy__toml_valid_table(yy__configuration_conf))))
    {
        yk__sds t__210 = yk__sdsnewlen("Failed to read config file", 26);
        yk__arrput(yy__configuration_c->yy__configuration_errors, yk__sdsdup(t__210));
        struct yy__configuration_Config* t__211 = yy__configuration_c;
        yk__sdsfree(t__210);
        yk__sdsfree(yy__configuration_config_text);
        yk__sdsfree(t__209);
        yk__sdsfree(yy__configuration_configf);
        yk__sdsfree(t__208);
        yk__sdsfree(t__207);
        yk__sdsfree(t__206);
        return t__211;
        yk__sdsfree(t__210);
    }
    yy__configuration_c->yy__configuration_compilation = yy__configuration_load_compilation(yy__configuration_conf, yy__configuration_c);
    yy__configuration_find_yaksha_compiler(yy__configuration_c);
    if ((yk__arrlen(yy__configuration_c->yy__configuration_errors) > INT32_C(0)))
    {
        struct yy__configuration_Config* t__212 = yy__configuration_c;
        yy__toml_del_table(yy__configuration_conf);
        yk__sdsfree(yy__configuration_config_text);
        yk__sdsfree(t__209);
        yk__sdsfree(yy__configuration_configf);
        yk__sdsfree(t__208);
        yk__sdsfree(t__207);
        yk__sdsfree(t__206);
        return t__212;
    }
    yy__configuration_find_zig_compiler(yy__configuration_c);
    if ((yk__arrlen(yy__configuration_c->yy__configuration_errors) > INT32_C(0)))
    {
        struct yy__configuration_Config* t__213 = yy__configuration_c;
        yy__toml_del_table(yy__configuration_conf);
        yk__sdsfree(yy__configuration_config_text);
        yk__sdsfree(t__209);
        yk__sdsfree(yy__configuration_configf);
        yk__sdsfree(t__208);
        yk__sdsfree(t__207);
        yk__sdsfree(t__206);
        return t__213;
    }
    yy__configuration_find_emsdk(yy__configuration_c);
    if ((yk__arrlen(yy__configuration_c->yy__configuration_errors) > INT32_C(0)))
    {
        struct yy__configuration_Config* t__214 = yy__configuration_c;
        yy__toml_del_table(yy__configuration_conf);
        yk__sdsfree(yy__configuration_config_text);
        yk__sdsfree(t__209);
        yk__sdsfree(yy__configuration_configf);
        yk__sdsfree(t__208);
        yk__sdsfree(t__207);
        yk__sdsfree(t__206);
        return t__214;
    }
    yy__configuration_find_w4(yy__configuration_c);
    if ((yk__arrlen(yy__configuration_c->yy__configuration_errors) > INT32_C(0)))
    {
        struct yy__configuration_Config* t__215 = yy__configuration_c;
        yy__toml_del_table(yy__configuration_conf);
        yk__sdsfree(yy__configuration_config_text);
        yk__sdsfree(t__209);
        yk__sdsfree(yy__configuration_configf);
        yk__sdsfree(t__208);
        yk__sdsfree(t__207);
        yk__sdsfree(t__206);
        return t__215;
    }
    yy__configuration_find_runtime_path(yy__configuration_c);
    if ((yk__arrlen(yy__configuration_c->yy__configuration_errors) > INT32_C(0)))
    {
        struct yy__configuration_Config* t__216 = yy__configuration_c;
        yy__toml_del_table(yy__configuration_conf);
        yk__sdsfree(yy__configuration_config_text);
        yk__sdsfree(t__209);
        yk__sdsfree(yy__configuration_configf);
        yk__sdsfree(t__208);
        yk__sdsfree(t__207);
        yk__sdsfree(t__206);
        return t__216;
    }
    yy__configuration_find_libs_path(yy__configuration_c);
    if ((yk__arrlen(yy__configuration_c->yy__configuration_errors) > INT32_C(0)))
    {
        struct yy__configuration_Config* t__217 = yy__configuration_c;
        yy__toml_del_table(yy__configuration_conf);
        yk__sdsfree(yy__configuration_config_text);
        yk__sdsfree(t__209);
        yk__sdsfree(yy__configuration_configf);
        yk__sdsfree(t__208);
        yk__sdsfree(t__207);
        yk__sdsfree(t__206);
        return t__217;
    }
    yy__configuration_c->yy__configuration_project = yy__configuration_load_project(yy__configuration_conf, yy__configuration_c);
    if ((yk__arrlen(yy__configuration_c->yy__configuration_errors) > INT32_C(0)))
    {
        struct yy__configuration_Config* t__218 = yy__configuration_c;
        yy__toml_del_table(yy__configuration_conf);
        yk__sdsfree(yy__configuration_config_text);
        yk__sdsfree(t__209);
        yk__sdsfree(yy__configuration_configf);
        yk__sdsfree(t__208);
        yk__sdsfree(t__207);
        yk__sdsfree(t__206);
        return t__218;
    }
    if ((! (yy__path_exists(yk__sdsdup(yy__configuration_c->yy__configuration_project->yy__configuration_main)))))
    {
        yk__sds t__219 = yk__sdsnewlen("Project main file not found", 27);
        yk__arrput(yy__configuration_c->yy__configuration_errors, yk__sdsdup(t__219));
        struct yy__configuration_Config* t__220 = yy__configuration_c;
        yy__toml_del_table(yy__configuration_conf);
        yk__sdsfree(t__219);
        yk__sdsfree(yy__configuration_config_text);
        yk__sdsfree(t__209);
        yk__sdsfree(yy__configuration_configf);
        yk__sdsfree(t__208);
        yk__sdsfree(t__207);
        yk__sdsfree(t__206);
        return t__220;
        yk__sdsfree(t__219);
    }
    yy__configuration_c->yy__configuration_c_code = yy__configuration_inject_c_code_defaults(yy__configuration_load_c_code(yy__configuration_conf, yy__configuration_c), yy__configuration_c);
    if ((yk__arrlen(yy__configuration_c->yy__configuration_errors) > INT32_C(0)))
    {
        struct yy__configuration_Config* t__221 = yy__configuration_c;
        yy__toml_del_table(yy__configuration_conf);
        yk__sdsfree(yy__configuration_config_text);
        yk__sdsfree(t__209);
        yk__sdsfree(yy__configuration_configf);
        yk__sdsfree(t__208);
        yk__sdsfree(t__207);
        yk__sdsfree(t__206);
        return t__221;
    }
    struct yy__configuration_Config* t__222 = yy__configuration_c;
    yy__toml_del_table(yy__configuration_conf);
    yk__sdsfree(yy__configuration_config_text);
    yk__sdsfree(t__209);
    yk__sdsfree(yy__configuration_configf);
    yk__sdsfree(t__208);
    yk__sdsfree(t__207);
    yk__sdsfree(t__206);
    return t__222;
}
struct yy__configuration_Config* yy__configuration_create_adhoc_config(yk__sds yy__configuration_name, yk__sds yy__configuration_file_path, bool yy__configuration_use_raylib, bool yy__configuration_use_web, bool yy__configuration_wasm4, yk__sds yy__configuration_web_shell, bool yy__configuration_crdll, bool yy__configuration_no_parallel) 
{
    struct yy__configuration_Config* yy__configuration_c = calloc(1, sizeof(struct yy__configuration_Config));
    yy__configuration_c->yy__configuration_compilation = calloc(1, sizeof(struct yy__configuration_Compilation));
    yk__sds t__223 = yk__sdsnewlen("native", 6);
    yk__sds* t__224 = NULL;
    yk__arrsetcap(t__224, 1);
    yk__arrput(t__224, yk__sdsdup(t__223));
    yy__configuration_c->yy__configuration_compilation->yy__configuration_targets = t__224;
    yy__configuration_c->yy__configuration_compilation->yy__configuration_raylib = yy__configuration_use_raylib;
    yy__configuration_c->yy__configuration_compilation->yy__configuration_raylib_hot_reloading_dll = yy__configuration_crdll;
    yy__configuration_c->yy__configuration_compilation->yy__configuration_web = yy__configuration_use_web;
    yk__sdsfree(yy__configuration_c->yy__configuration_compilation->yy__configuration_web_shell);
    yy__configuration_c->yy__configuration_compilation->yy__configuration_web_shell = yk__sdsdup(yy__configuration_web_shell);
    yy__configuration_c->yy__configuration_compilation->yy__configuration_wasm4 = yy__configuration_wasm4;
    yy__configuration_c->yy__configuration_compilation->yy__configuration_disable_parallel_build = yy__configuration_no_parallel;
    yy__configuration_find_yaksha_compiler(yy__configuration_c);
    if ((yk__arrlen(yy__configuration_c->yy__configuration_errors) > INT32_C(0)))
    {
        struct yy__configuration_Config* t__225 = yy__configuration_c;
        yk__sdsfree(t__223);
        yk__sdsfree(yy__configuration_web_shell);
        yk__sdsfree(yy__configuration_file_path);
        yk__sdsfree(yy__configuration_name);
        return t__225;
    }
    yy__configuration_find_zig_compiler(yy__configuration_c);
    if ((yk__arrlen(yy__configuration_c->yy__configuration_errors) > INT32_C(0)))
    {
        struct yy__configuration_Config* t__226 = yy__configuration_c;
        yk__sdsfree(t__223);
        yk__sdsfree(yy__configuration_web_shell);
        yk__sdsfree(yy__configuration_file_path);
        yk__sdsfree(yy__configuration_name);
        return t__226;
    }
    yy__configuration_find_emsdk(yy__configuration_c);
    if ((yk__arrlen(yy__configuration_c->yy__configuration_errors) > INT32_C(0)))
    {
        struct yy__configuration_Config* t__227 = yy__configuration_c;
        yk__sdsfree(t__223);
        yk__sdsfree(yy__configuration_web_shell);
        yk__sdsfree(yy__configuration_file_path);
        yk__sdsfree(yy__configuration_name);
        return t__227;
    }
    yy__configuration_find_w4(yy__configuration_c);
    if ((yk__arrlen(yy__configuration_c->yy__configuration_errors) > INT32_C(0)))
    {
        struct yy__configuration_Config* t__228 = yy__configuration_c;
        yk__sdsfree(t__223);
        yk__sdsfree(yy__configuration_web_shell);
        yk__sdsfree(yy__configuration_file_path);
        yk__sdsfree(yy__configuration_name);
        return t__228;
    }
    yy__configuration_find_runtime_path(yy__configuration_c);
    if ((yk__arrlen(yy__configuration_c->yy__configuration_errors) > INT32_C(0)))
    {
        struct yy__configuration_Config* t__229 = yy__configuration_c;
        yk__sdsfree(t__223);
        yk__sdsfree(yy__configuration_web_shell);
        yk__sdsfree(yy__configuration_file_path);
        yk__sdsfree(yy__configuration_name);
        return t__229;
    }
    yy__configuration_find_libs_path(yy__configuration_c);
    if ((yk__arrlen(yy__configuration_c->yy__configuration_errors) > INT32_C(0)))
    {
        struct yy__configuration_Config* t__230 = yy__configuration_c;
        yk__sdsfree(t__223);
        yk__sdsfree(yy__configuration_web_shell);
        yk__sdsfree(yy__configuration_file_path);
        yk__sdsfree(yy__configuration_name);
        return t__230;
    }
    yy__configuration_c->yy__configuration_project = calloc(1, sizeof(struct yy__configuration_Project));
    yk__sdsfree(yy__configuration_c->yy__configuration_project->yy__configuration_main);
    yy__configuration_c->yy__configuration_project->yy__configuration_main = yk__sdsdup(yy__configuration_file_path);
    yk__sds t__231 = yk__sdsnewlen("unknown", 7);
    yk__sdsfree(yy__configuration_c->yy__configuration_project->yy__configuration_author);
    yy__configuration_c->yy__configuration_project->yy__configuration_author = yk__sdsdup(t__231);
    yk__sdsfree(yy__configuration_c->yy__configuration_project->yy__configuration_name);
    yy__configuration_c->yy__configuration_project->yy__configuration_name = yk__sdsdup(yy__configuration_name);
    yy__configuration_c->yy__configuration_c_code = yy__configuration_inject_c_code_defaults(calloc(1, sizeof(struct yy__configuration_CCode)), yy__configuration_c);
    if ((yk__arrlen(yy__configuration_c->yy__configuration_errors) > INT32_C(0)))
    {
        struct yy__configuration_Config* t__232 = yy__configuration_c;
        yk__sdsfree(t__231);
        yk__sdsfree(t__223);
        yk__sdsfree(yy__configuration_web_shell);
        yk__sdsfree(yy__configuration_file_path);
        yk__sdsfree(yy__configuration_name);
        return t__232;
    }
    struct yy__configuration_Config* t__233 = yy__configuration_c;
    yk__sdsfree(t__231);
    yk__sdsfree(t__223);
    yk__sdsfree(yy__configuration_web_shell);
    yk__sdsfree(yy__configuration_file_path);
    yk__sdsfree(yy__configuration_name);
    return t__233;
}
void yy__configuration_del_config(struct yy__configuration_Config* yy__configuration_c) 
{
    if ((yy__configuration_c->yy__configuration_c_code != NULL))
    {
        yy__array_del_str_array(yy__configuration_c->yy__configuration_c_code->yy__configuration_include_paths);
        yy__array_del_str_array(yy__configuration_c->yy__configuration_c_code->yy__configuration_defines);
        yy__array_del_str_array(yy__configuration_c->yy__configuration_c_code->yy__configuration_compiler_defines);
        yy__array_del_str_array(yy__configuration_c->yy__configuration_c_code->yy__configuration_includes);
        yy__array_del_str_array(yy__configuration_c->yy__configuration_c_code->yy__configuration_system_includes);
        yy__array_del_str_array(yy__configuration_c->yy__configuration_c_code->yy__configuration_c_code);
        yy__array_del_str_array(yy__configuration_c->yy__configuration_c_code->yy__configuration_cpp_code);
        yy__array_del_str_array(yy__configuration_c->yy__configuration_c_code->yy__configuration_runtime_feature_defines);
        yy__array_del_str_array(yy__configuration_c->yy__configuration_c_code->yy__configuration_runtime_feature_includes);
        yy__array_del_str_array(yy__configuration_c->yy__configuration_c_code->yy__configuration_runtime_feature_c_code);
        yy__array_del_str_array(yy__configuration_c->yy__configuration_c_code->yy__configuration_runtime_feature_compiler_defines);
    }
    yy__array_del_str_array(yy__configuration_c->yy__configuration_errors);
    if ((yy__configuration_c->yy__configuration_compilation != NULL))
    {
        yy__array_del_str_array(yy__configuration_c->yy__configuration_compilation->yy__configuration_targets);
        yk__sdsfree(yy__configuration_c->yy__configuration_compilation->yy__configuration_libc);
        yk__sdsfree(yy__configuration_c->yy__configuration_compilation->yy__configuration_compiler);
        yk__sdsfree(yy__configuration_c->yy__configuration_compilation->yy__configuration_web_shell);
    }
    if ((yy__configuration_c->yy__configuration_project != NULL))
    {
        yk__sdsfree(yy__configuration_c->yy__configuration_project->yy__configuration_main);
        yk__sdsfree(yy__configuration_c->yy__configuration_project->yy__configuration_name);
        yk__sdsfree(yy__configuration_c->yy__configuration_project->yy__configuration_author);
    }
    free(yy__configuration_c->yy__configuration_c_code);
    free(yy__configuration_c->yy__configuration_project);
    free(yy__configuration_c->yy__configuration_compilation);
    yk__sdsfree(yy__configuration_c->yy__configuration_runtime_path);
    yk__sdsfree(yy__configuration_c->yy__configuration_compiler_path);
    yk__sdsfree(yy__configuration_c->yy__configuration_libs_path);
    yk__sdsfree(yy__configuration_c->yy__configuration_zig_compiler_path);
    yk__sdsfree(yy__configuration_c->yy__configuration_emcc_compiler_path);
    yk__sdsfree(yy__configuration_c->yy__configuration_emrun_path);
    yk__sdsfree(yy__configuration_c->yy__configuration_w4_path);
    free(yy__configuration_c);
    return;
}
yy__argparse_ArgParseWrapper yy__argparse_new_ex(yy__argparse_Option* nn__options, yk__sds* nn__usages, int32_t nn__flag) { return yk__newargparse(nn__options, nn__usages, nn__flag); }
yy__argparse_ArgParseWrapper yy__argparse_new(yy__argparse_Option* yy__argparse_options, yk__sds* yy__argparse_usages) 
{
    yy__argparse_ArgParseWrapper t__0 = yy__argparse_new_ex(yy__argparse_options, yy__argparse_usages, yy__argparse_ARGPARSE_DEFAULT);
    return t__0;
}
void yy__argparse_set_description(yy__argparse_ArgParse nn__argp, yk__sds nn__description, yk__sds nn__epilog) { argparse_describe(nn__argp, nn__description, nn__epilog); }
void yy__argparse_del_argparse(yy__argparse_ArgParseWrapper nn__object) { yk__delargparse(nn__object); }
yy__argparse_ArgParseRemainder yy__argparse_parse(yy__argparse_ArgParse nn__argp, yk__sds* nn__arguments) { return yk__argparse_parse(nn__argp, nn__arguments); }
void yy__argparse_usage(yy__argparse_ArgParse nn__argp) { argparse_usage(nn__argp); }
void yy__argparse_del_remainder(yy__argparse_ArgParseRemainder nn__a) { yk__del_argparse_remainder(nn__a); }
yy__argparse_Option yy__argparse_opt_help() 
{
    return (struct argparse_option)OPT_BOOLEAN('h', yk__sdsnew("help"),
    NULL, yk__sdsnew("show this help message and exit"), argparse_help_cb, 0, OPT_NONEG);
}
yy__argparse_Option yy__argparse_opt_boolean(yk__sds nn__short, yk__sds nn__large, int32_t* nn__result, yk__sds nn__help) 
{
    struct argparse_option o = ((struct argparse_option) OPT_BOOLEAN(nn__short[0], nn__large, nn__result, nn__help, NULL, 0, 0));
    yk__sdsfree(nn__short);
    return o;
}
yy__argparse_Option yy__argparse_opt_string(yk__sds nn__short, yk__sds nn__large, yy__c_CStr* nn__result, yk__sds nn__help) 
{
    struct argparse_option o = ((struct argparse_option) OPT_STRING(nn__short[0], nn__large, nn__result, nn__help, NULL, 0, 0));
    yk__sdsfree(nn__short);
    return o;
}
yy__argparse_Option yy__argparse_opt_integer(yk__sds nn__short, yk__sds nn__large, int32_t* nn__result, yk__sds nn__help) 
{
    struct argparse_option o = ((struct argparse_option) OPT_INTEGER(nn__short[0], nn__large, nn__result, nn__help, NULL, 0, 0));
    yk__sdsfree(nn__short);
    return o;
}
yy__argparse_Option yy__argparse_opt_float(yk__sds nn__short, yk__sds nn__large, float* nn__result, yk__sds nn__help) 
{
    struct argparse_option o = ((struct argparse_option) OPT_FLOAT(nn__short[0], nn__large, nn__result, nn__help, NULL, 0, 0));
    yk__sdsfree(nn__short);
    return o;
}
yy__argparse_Option yy__argparse_opt_end() 
{
    return (struct argparse_option) OPT_END();
}
void yy__console_set_color(int32_t nn__c) 
{
    if (nn__c == 0) { // rewind
        yk__set_colour(YK__CONSOLE_REWIND);
    } else if (nn__c == 1) { // red 
        yk__set_colour(YK__CONSOLE_RED);
    } else if (nn__c == 2) { // green 
        yk__set_colour(YK__CONSOLE_GREEN);
    } else if (nn__c == 3) { // white 
        yk__set_colour(YK__CONSOLE_WHITE);
    } else if (nn__c == 4) { // blue 
        yk__set_colour(YK__CONSOLE_BLUE);
    } else if (nn__c == 5) { // purple 
        yk__set_colour(YK__CONSOLE_PURPLE);
    } else if (nn__c == 6) { // yellow 
        yk__set_colour(YK__CONSOLE_YELLOW);
    } else if (nn__c == 7) { // cyan  
        yk__set_colour(YK__CONSOLE_CYAN);
    };
}
int32_t yy__console_getch() 
{
    return yk__getch();
}
void yy__console_color_print(int32_t yy__console_color, yk__sds yy__console_x) 
{
    yy__console_set_color(yy__console_color);
    yk__printstr((yy__console_x));
    yy__console_set_color(INT32_C(0));
    yk__sdsfree(yy__console_x);
    return;
}
void yy__console_red(yk__sds yy__console_x) 
{
    yy__console_color_print(INT32_C(1), yk__sdsdup(yy__console_x));
    yk__sdsfree(yy__console_x);
    return;
}
void yy__console_green(yk__sds yy__console_x) 
{
    yy__console_color_print(INT32_C(2), yk__sdsdup(yy__console_x));
    yk__sdsfree(yy__console_x);
    return;
}
void yy__console_white(yk__sds yy__console_x) 
{
    yy__console_color_print(INT32_C(3), yk__sdsdup(yy__console_x));
    yk__sdsfree(yy__console_x);
    return;
}
void yy__console_blue(yk__sds yy__console_x) 
{
    yy__console_color_print(INT32_C(4), yk__sdsdup(yy__console_x));
    yk__sdsfree(yy__console_x);
    return;
}
void yy__console_purple(yk__sds yy__console_x) 
{
    yy__console_color_print(INT32_C(5), yk__sdsdup(yy__console_x));
    yk__sdsfree(yy__console_x);
    return;
}
void yy__console_yellow(yk__sds yy__console_x) 
{
    yy__console_color_print(INT32_C(6), yk__sdsdup(yy__console_x));
    yk__sdsfree(yy__console_x);
    return;
}
void yy__console_cyan(yk__sds yy__console_x) 
{
    yy__console_color_print(INT32_C(7), yk__sdsdup(yy__console_x));
    yk__sdsfree(yy__console_x);
    return;
}
yk__sds yy__io_readfile(yk__sds nn__fname) { return yk__io_readfile(nn__fname); }
bool yy__io_writefile(yk__sds nn__fname, yk__sds nn__data) { return yk__io_writefile(nn__fname, nn__data); }
yy__toml_Table yy__toml_from_str(yk__sds nn__x) 
{
    char errbuf[200];
    toml_table_t* t = toml_parse(nn__x, errbuf, sizeof(errbuf));
    yk__sdsfree(nn__x);
    return t;
}
yy__toml_Table yy__toml_get_table(yy__toml_Table nn__x, yk__sds nn__name) 
{
    toml_table_t* t = toml_table_in(nn__x, nn__name);
    yk__sdsfree(nn__name);
    return t;
}
yy__toml_TomlArray yy__toml_get_array(yy__toml_Table nn__x, yk__sds nn__name) 
{
    toml_array_t* t = toml_array_in(nn__x, nn__name);
    yk__sdsfree(nn__name);
    return t;
}
int32_t yy__toml_array_len(yy__toml_TomlArray nn__x) 
{
    if (NULL == nn__x) { return -1; }
    return toml_array_nelem(nn__x);
}
yk__sds yy__toml_get_string(yy__toml_Table nn__x, yk__sds nn__name) 
{
    toml_datum_t v = toml_string_in(nn__x, nn__name);
    yk__sdsfree(nn__name);
    if (v.ok) {
        yk__sds s = yk__sdsnew(v.u.s);
        free(v.u.s);
        return s;
    }
    return yk__sdsempty();
}
yk__sds yy__toml_get_string_default(yy__toml_Table nn__x, yk__sds nn__name, yk__sds nn__default) 
{
    toml_datum_t v = toml_string_in(nn__x, nn__name);
    yk__sdsfree(nn__name);
    if (v.ok) {
        yk__sds s = yk__sdsnew(v.u.s);
        free(v.u.s);
        yk__sdsfree(nn__default);
        return s;
    }
    return nn__default;
}
bool yy__toml_get_bool(yy__toml_Table nn__x, yk__sds nn__name) 
{
    toml_datum_t v = toml_bool_in(nn__x, nn__name);
    yk__sdsfree(nn__name);
    if (v.ok) {
        return (1 == v.u.b);
    }
    return false;
}
bool yy__toml_get_bool_default(yy__toml_Table nn__x, yk__sds nn__name, bool nn__default) 
{
    toml_datum_t v = toml_bool_in(nn__x, nn__name);
    yk__sdsfree(nn__name);
    if (v.ok) {
        return (1 == v.u.b);
    }
    return nn__default;
}
int32_t yy__toml_get_int(yy__toml_Table nn__x, yk__sds nn__name) 
{
    toml_datum_t v = toml_int_in(nn__x, nn__name);
    yk__sdsfree(nn__name);
    if (v.ok) {
        return v.u.i;
    }
    return 0;
}
int32_t yy__toml_get_int_default(yy__toml_Table nn__x, yk__sds nn__name, int32_t nn__default) 
{
    toml_datum_t v = toml_int_in(nn__x, nn__name);
    yk__sdsfree(nn__name);
    if (v.ok) {
        return v.u.i;
    }
    return nn__default;
}
yk__sds yy__toml_string_at(yy__toml_TomlArray nn__x, int32_t nn__pos) 
{
    toml_datum_t v = toml_string_at(nn__x, nn__pos);
    if (v.ok) {
        yk__sds s = yk__sdsnew(v.u.s);
        free(v.u.s);
        return s;
    }
    return yk__sdsempty();
}
yk__sds yy__toml_string_at_default(yy__toml_TomlArray nn__x, int32_t nn__pos, yk__sds nn__default) 
{
    toml_datum_t v = toml_string_at(nn__x, nn__pos);
    if (v.ok) {
        yk__sds s = yk__sdsnew(v.u.s);
        free(v.u.s);
        yk__sdsfree(nn__default);
        return s;
    }
    return nn__default;
}
bool yy__toml_bool_at(yy__toml_TomlArray nn__x, int32_t nn__pos) 
{
    toml_datum_t v = toml_bool_at(nn__x, nn__pos);
    if (v.ok) {
        return (1 == v.u.b);
    }
    return false;
}
bool yy__toml_bool_at_default(yy__toml_TomlArray nn__x, int32_t nn__pos, bool nn__default) 
{
    toml_datum_t v = toml_bool_at(nn__x, nn__pos);
    if (v.ok) {
        return (1 == v.u.b);
    }
    return nn__default;
}
int32_t yy__toml_int_at(yy__toml_TomlArray nn__x, int32_t nn__pos) 
{
    toml_datum_t v = toml_int_at(nn__x, nn__pos);
    if (v.ok) {
        return v.u.i;
    }
    return 0;
}
int32_t yy__toml_int_at_default(yy__toml_TomlArray nn__x, int32_t nn__pos, int32_t nn__default) 
{
    toml_datum_t v = toml_int_at(nn__x, nn__pos);
    if (v.ok) {
        return v.u.i;
    }
    return nn__default;
}
yk__sds* yy__toml_get_string_array(yy__toml_Table yy__toml_x, yk__sds yy__toml_name) 
{
    yk__sds* yy__toml_str_array = NULL;
    yy__toml_TomlArray yy__toml_arr = yy__toml_get_array(yy__toml_x, yk__sdsdup(yy__toml_name));
    if ((! (yy__toml_valid_array(yy__toml_arr))))
    {
        yk__sds* t__0 = yy__toml_str_array;
        yk__sdsfree(yy__toml_name);
        return t__0;
    }
    int32_t yy__toml_length = yy__toml_array_len(yy__toml_arr);
    int32_t yy__toml_c = INT32_C(0);
    while (1) {
        if (!((yy__toml_c < yy__toml_length))) { break; } // Check
        // Body of while loop

        {
            yk__sds t__1 = yy__toml_string_at(yy__toml_arr, yy__toml_c);
            yk__arrput(yy__toml_str_array, yk__sdsdup((t__1)));
            yy__toml_c = (yy__toml_c + INT32_C(1));
            yk__sdsfree(t__1);
        }
    }
    yk__sds* t__2 = yy__toml_str_array;
    yk__sdsfree(yy__toml_name);
    return t__2;
}
void yy__toml_del_table(yy__toml_Table nn__x) 
{
    if (NULL == nn__x) return;
    toml_free(nn__x);
}
bool yy__path_forward_slash() 
{
    #if defined(_WIN32) || defined(_WIN64)
    bool bfwd = true;
    #else
    bool bfwd = false;
    #endif
    return bfwd;
}
bool yy__path_end_with_slash(yk__sds yy__path_a) 
{
    int32_t yy__path_length = yk__sdslen(yy__path_a);
    if ((yy__path_length < INT32_C(1)))
    {
        yk__sdsfree(yy__path_a);
        return false;
    }
    int32_t yy__path_chr = (yy__path_a[(yy__path_length - INT32_C(1))]);
    bool yy__path_x = ((yy__path_chr == INT32_C(47)) || (yy__path_chr == INT32_C(92)));
    bool t__0 = yy__path_x;
    yk__sdsfree(yy__path_a);
    return t__0;
}
bool yy__path_end_with_dot(yk__sds yy__path_a) 
{
    int32_t yy__path_length = yk__sdslen(yy__path_a);
    if ((yy__path_length < INT32_C(1)))
    {
        yk__sdsfree(yy__path_a);
        return false;
    }
    int32_t yy__path_chr = (yy__path_a[(yy__path_length - INT32_C(1))]);
    bool yy__path_x = (yy__path_chr == INT32_C(46));
    bool t__1 = yy__path_x;
    yk__sdsfree(yy__path_a);
    return t__1;
}
yk__sds yy__path_join(yk__sds yy__path_a, yk__sds yy__path_b) 
{
    if (yy__path_end_with_slash(yk__sdsdup(yy__path_a)))
    {
        yk__sds t__2 = yk__sdscatsds(yk__sdsdup(yy__path_a), yy__path_b);
        yk__sds t__3 = t__2;
        yk__sdsfree(yy__path_b);
        yk__sdsfree(yy__path_a);
        return t__3;
        yk__sdsfree(t__2);
    }
    yk__sds yy__path_result = yk__sdsempty();
    if (yy__path_forward_slash())
    {
        yk__sds t__4 = yk__sdsnewlen("\\", 1);
        yk__sds t__5 = yk__sdscatsds(yk__sdsdup(yy__path_a), t__4);
        yk__sds t__6 = yk__sdscatsds(yk__sdsdup(t__5), yy__path_b);
        yk__sdsfree(yy__path_result);
        yy__path_result = yk__sdsdup(t__6);
        yk__sdsfree(t__6);
        yk__sdsfree(t__5);
        yk__sdsfree(t__4);
    }
    else
    {
        yk__sds t__7 = yk__sdsnewlen("/", 1);
        yk__sds t__8 = yk__sdscatsds(yk__sdsdup(yy__path_a), t__7);
        yk__sds t__9 = yk__sdscatsds(yk__sdsdup(t__8), yy__path_b);
        yk__sdsfree(yy__path_result);
        yy__path_result = yk__sdsdup(t__9);
        yk__sdsfree(t__9);
        yk__sdsfree(t__8);
        yk__sdsfree(t__7);
    }
    yk__sds t__10 = yy__path_result;
    yk__sdsfree(yy__path_b);
    yk__sdsfree(yy__path_a);
    return t__10;
}
yk__sds yy__path_basename(yk__sds yy__path_p) 
{
    int32_t yy__path_full_length = yk__sdslen(yy__path_p);
    int32_t yy__path_length = yk__sdslen(yy__path_p);
    if ((yy__path_length < INT32_C(1)))
    {
        yk__sds t__11 = yy__path_p;
        return t__11;
    }
    if (yy__path_end_with_slash(yk__sdsdup(yy__path_p)))
    {
        yk__sds t__12 = yk__sdsempty();
        yk__sdsfree(yy__path_p);
        return t__12;
        yk__sdsfree(t__12);
    }
    yy__c_CStr yy__path_x = yy__strings_to_cstr(yk__sdsdup(yy__path_p));
    while (1) {
        if (!((yy__path_length > INT32_C(0)))) { break; } // Check
        // Body of while loop

        {
            yy__path_length = (yy__path_length - INT32_C(1));
            int32_t yy__path_chr = yy__strings_get_cstr(yy__path_x, yy__path_length);
            bool yy__path_is_slash = ((yy__path_chr == INT32_C(47)) || (yy__path_chr == INT32_C(92)));
            if (yy__path_is_slash)
            {
                break;
            }
        }
    }
    if ((yy__path_length <= INT32_C(0)))
    {
        yk__sds t__13 = yy__path_p;
        yy__strings_del_str(yy__path_x);
        return t__13;
    }
    yk__sds t__14 = yy__strings_from_cstrlen_after(yy__path_x, ((yy__path_full_length - yy__path_length) - INT32_C(1)), (yy__path_length + INT32_C(1)));
    yk__sds yy__path_s = yk__sdsdup((t__14));
    yk__sds t__15 = yy__path_s;
    yy__strings_del_str(yy__path_x);
    yk__sdsfree(t__14);
    yk__sdsfree(yy__path_p);
    return t__15;
}
yk__sds yy__path_dirname(yk__sds yy__path_p) 
{
    int32_t yy__path_length = yk__sdslen(yy__path_p);
    if ((yy__path_length <= INT32_C(2)))
    {
        yk__sds t__16 = yy__path_p;
        return t__16;
    }
    if (yy__path_end_with_slash(yk__sdsdup(yy__path_p)))
    {
        yy__path_length = (yy__path_length - INT32_C(1));
    }
    yy__c_CStr yy__path_x = yy__strings_to_cstr(yk__sdsdup(yy__path_p));
    while (1) {
        if (!((yy__path_length > INT32_C(0)))) { break; } // Check
        // Body of while loop

        {
            yy__path_length = (yy__path_length - INT32_C(1));
            int32_t yy__path_chr = yy__strings_get_cstr(yy__path_x, yy__path_length);
            bool yy__path_is_slash = ((yy__path_chr == INT32_C(47)) || (yy__path_chr == INT32_C(92)));
            if (yy__path_is_slash)
            {
                break;
            }
        }
    }
    if ((yy__path_length <= INT32_C(0)))
    {
        yk__sds t__17 = yk__sdsempty();
        yy__strings_del_str(yy__path_x);
        yk__sdsfree(yy__path_p);
        return t__17;
        yk__sdsfree(t__17);
    }
    yk__sds t__18 = yy__strings_from_cstrlen(yy__path_x, yy__path_length);
    yk__sds yy__path_s = yk__sdsdup((t__18));
    yk__sds t__19 = yy__path_s;
    yy__strings_del_str(yy__path_x);
    yk__sdsfree(t__18);
    yk__sdsfree(yy__path_p);
    return t__19;
}
yk__sds yy__path_remove_extension(yk__sds yy__path_p) 
{
    int32_t yy__path_length = yk__sdslen(yy__path_p);
    if ((yy__path_length <= INT32_C(1)))
    {
        yk__sds t__20 = yy__path_p;
        return t__20;
    }
    if (yy__path_end_with_slash(yk__sdsdup(yy__path_p)))
    {
        yy__path_length = (yy__path_length - INT32_C(1));
    }
    yy__c_CStr yy__path_x = yy__strings_to_cstr(yk__sdsdup(yy__path_p));
    while (1) {
        if (!((yy__path_length > INT32_C(0)))) { break; } // Check
        // Body of while loop

        {
            yy__path_length = (yy__path_length - INT32_C(1));
            int32_t yy__path_chr = yy__strings_get_cstr(yy__path_x, yy__path_length);
            bool yy__path_is_dot = (yy__path_chr == INT32_C(46));
            if (yy__path_is_dot)
            {
                break;
            }
        }
    }
    if ((yy__path_length <= INT32_C(0)))
    {
        yk__sds t__21 = yk__sdsempty();
        yy__strings_del_str(yy__path_x);
        yk__sdsfree(yy__path_p);
        return t__21;
        yk__sdsfree(t__21);
    }
    yk__sds t__22 = yy__strings_from_cstrlen(yy__path_x, yy__path_length);
    yk__sds yy__path_s = yk__sdsdup((t__22));
    yk__sds t__23 = yy__path_s;
    yy__strings_del_str(yy__path_x);
    yk__sdsfree(t__22);
    yk__sdsfree(yy__path_p);
    return t__23;
}
yk__sds* yy__array_prefix(yk__sds* nn__sa, yk__sds nn__prefix_str) 
{
    if (NULL == nn__sa) return NULL;
    size_t l = yk__arrlenu(nn__sa);
    for (size_t x = 0; x < l; x++) {
        yk__sds tmp = nn__sa[x];
        nn__sa[x] = yk__sdscatsds(yk__sdsdup(nn__prefix_str), nn__sa[x]);
        yk__sdsfree(tmp);
    }
    yk__sdsfree(nn__prefix_str);
    return nn__sa;
}
yk__sds* yy__array_suffix(yk__sds* nn__sa, yk__sds nn__suffix_str) 
{
    if (NULL == nn__sa) return NULL;
    size_t l = yk__arrlenu(nn__sa);
    for (size_t x = 0; x < l; x++) {
        nn__sa[x] = yk__sdscatsds(nn__sa[x], nn__suffix_str);
    }
    yk__sdsfree(nn__suffix_str);
    return nn__sa;
}
yk__sds yy__array_join(yk__sds* nn__values, yk__sds nn__sep) 
{
    
    if (NULL == nn__values) {
        yk__sdsfree(nn__sep);
        return yk__sdsempty();
    }
    yk__sds tmp = yk__sdsjoinsds(nn__values, yk__arrlen(nn__values), nn__sep, yk__sdslen(nn__sep));
    yk__sdsfree(nn__sep);
    return tmp;
}
yk__sds* yy__array_extend(yk__sds* nn__a, yk__sds* nn__b) 
{
    yk__sds* lhs = nn__a;
    if (NULL != nn__b) {
        size_t l = yk__arrlenu(nn__b);
        for (size_t x = 0; x < l; x++) {
            yk__arrput(lhs, yk__sdsdup(nn__b[x]));
        }
    }
    return lhs;
}
bool yy__c_has_command_processor() 
{
    return (!!system(NULL));
}
int32_t yy__strings_get_cstr(yy__c_CStr nn__s, int32_t nn__pos) 
{
    return (int32_t)nn__s[nn__pos];
}
void yy__strings_set_cstr(yy__c_CStr nn__s, int32_t nn__pos, int32_t nn__v) 
{
    nn__s[nn__pos] = nn__v;;
}
int32_t yy__strings_get(yk__sds nn__s, int32_t nn__pos) 
{
    int32_t x = (int32_t)nn__s[nn__pos];
    yk__sdsfree(nn__s);
    return x;
}
bool yy__strings_contains(yk__sds nn__haystack, yk__sds nn__needle) 
{
    bool val = strstr(nn__haystack, nn__needle) != NULL;
    yk__sdsfree(nn__haystack);
    yk__sdsfree(nn__needle);
    return val;
}
bool yy__strings_isempty(yk__sds nn__s) 
{
    bool x = yk__sdslen(nn__s) == 0;
    yk__sdsfree(nn__s);
    return x;
}
bool yy__strings_isempty_cstr(yy__c_CStr nn__s) 
{
    bool x = strlen(nn__s) == 0;
    return x;
}
int32_t yy__strings_ord_cstr(yy__c_CStr nn__s) 
{
    return (int32_t)nn__s[0];
}
int32_t yy__strings_ord(yk__sds yy__strings_s) 
{
    int32_t t__0 = yy__strings_get(yk__sdsdup(yy__strings_s), INT32_C(0));
    yk__sdsfree(yy__strings_s);
    return t__0;
}
bool yy__strings_startswith(yk__sds nn__a, yk__sds nn__b) 
{
    bool x = (strstr(nn__a, nn__b) != NULL);
    yk__sdsfree(nn__a);
    yk__sdsfree(nn__b);
    return x;
}
yk__sds* yy__strings_split(yk__sds nn__value, yk__sds nn__sep) 
{
    int count;
    yk__sds* result = yk__sdssplitlen(nn__value, yk__sdslen(nn__value),
            nn__sep, yk__sdslen(nn__sep), &count);
    yk__sdsfree(nn__value);
    yk__sdsfree(nn__sep);
    if (NULL == result) {
        return NULL;
    }
    yk__sds* newarr = NULL;
    for (int i = 0; i < count; i++) {
        yk__arrput(newarr, result[i]);
    }
    free(result); // free array itself.
    return newarr;
}
int32_t yy__strings_find_char(yk__sds nn__value, int32_t nn__ch) 
{
    int position = -1;
    int length = (int)yk__sdslen(nn__value);
    for (int i = 0; i < length; i++) {
        if (nn__value[i] == nn__ch) {
            position = i;
            break;
        }
    }
    yk__sdsfree(nn__value);
    return position;
}
yk__sds yy__strings_from_cstr(yy__c_CStr nn__a) 
{
    return yk__sdsnewlen(nn__a, strlen(nn__a));
}
yk__sds yy__strings_from_cstrlen(yy__c_CStr nn__a, int32_t nn__length) 
{
    return yk__sdsnewlen(nn__a, nn__length);
}
yk__sds yy__strings_from_cstrlen_after(yy__c_CStr nn__a, int32_t nn__length, int32_t nn__after) 
{
    return yk__sdsnewlen(nn__a + nn__after, nn__length);
}
yy__c_CStr yy__strings_null_cstr() 
{
    return (char*)NULL;
}
yy__c_CStr yy__strings_to_cstr(yk__sds nn__a) 
{
    return nn__a;
}
void yy__strings_del_cstr(yy__c_CStr nn__a) 
{
    free(nn__a);
}
void yy__strings_del_str(yy__c_CStr nn__a) 
{
    if (NULL == nn__a) return;
    yk__sdsfree(nn__a);
}
yk__sds yy__strings_cut_from(yk__sds nn__a, int32_t nn__position) 
{
    if (nn__a == NULL || yk__sdslen(nn__a) < nn__position) {
        yk__sdsfree(nn__a);
        return yk__sdsempty();
    }
    yk__sds s = yk__sdsnewlen(nn__a + nn__position, yk__sdslen(nn__a) - nn__position);
    yk__sdsfree(nn__a);
    return s;
}
yk__sds yy__strings_mid(yk__sds nn__a, int32_t nn__position, int32_t nn__number) 
{
    if (nn__a == NULL || nn__number < 1 || yk__sdslen(nn__a) < (nn__position + nn__number)) {
        yk__sdsfree(nn__a);
        return yk__sdsempty();
    }
    yk__sds s = yk__sdsnewlen(nn__a + nn__position, nn__number);
    yk__sdsfree(nn__a);
    return s;
}
bool yy__strings_endswith(yk__sds yy__strings_a, yk__sds yy__strings_b) 
{
    if ((yk__sdslen(yy__strings_b) > yk__sdslen(yy__strings_a)))
    {
        yk__sdsfree(yy__strings_b);
        yk__sdsfree(yy__strings_a);
        return false;
    }
    int32_t yy__strings_pos = (yk__sdslen(yy__strings_a) - yk__sdslen(yy__strings_b));
    yk__sds t__1 = yy__strings_cut_from(yk__sdsdup(yy__strings_a), yy__strings_pos);
    yk__sds yy__strings_cut_a = yk__sdsdup((t__1));
    bool yy__strings_result = (yk__sdscmp(yy__strings_cut_a , yy__strings_b) == 0);
    bool t__2 = yy__strings_result;
    yk__sdsfree(yy__strings_cut_a);
    yk__sdsfree(t__1);
    yk__sdsfree(yy__strings_b);
    yk__sdsfree(yy__strings_a);
    return t__2;
}
yk__sds yy__strings_spaces(int32_t nn__count) 
{
    if (nn__count <= 0) {
        return yk__sdsempty();
    }
    yk__sds s = yk__sdsgrowzero(yk__sdsempty(), nn__count);
    for (int i = 0; i < nn__count; i++) {
        s[i] = ' ';
    }
    return s;
}
yk__sds yy__strings_rpad(yk__sds yy__strings_a, int32_t yy__strings_count) 
{
    if ((yk__sdslen(yy__strings_a) > yy__strings_count))
    {
        yk__sds t__3 = yy__strings_a;
        return t__3;
    }
    int32_t yy__strings_remainder = (yy__strings_count - yk__sdslen(yy__strings_a));
    yk__sds t__4 = yy__strings_spaces(yy__strings_remainder);
    yk__sds t__5 = yk__sdscatsds(yk__sdsdup(yy__strings_a), (t__4));
    yk__sds yy__strings_result = yk__sdsdup(t__5);
    yk__sds t__6 = yy__strings_result;
    yk__sdsfree(t__5);
    yk__sdsfree(t__4);
    yk__sdsfree(yy__strings_a);
    return t__6;
}
yk__sds yy__strings_lpad(yk__sds yy__strings_a, int32_t yy__strings_count) 
{
    if ((yk__sdslen(yy__strings_a) > yy__strings_count))
    {
        yk__sds t__7 = yy__strings_a;
        return t__7;
    }
    int32_t yy__strings_remainder = (yy__strings_count - yk__sdslen(yy__strings_a));
    yk__sds t__8 = yy__strings_spaces(yy__strings_remainder);
    yk__sds t__9 = yk__sdscatsds(yk__sdsdup((t__8)), yy__strings_a);
    yk__sds yy__strings_result = yk__sdsdup(t__9);
    yk__sds t__10 = yy__strings_result;
    yk__sdsfree(t__9);
    yk__sdsfree(t__8);
    yk__sdsfree(yy__strings_a);
    return t__10;
}
yk__sds yy__os_exe() 
{
    int length = wai_getExecutablePath(NULL, 0, NULL);
    char* path = malloc(length + 1);
    if (path == NULL) return yk__sdsempty();
    wai_getExecutablePath(path, length, NULL);
    path[length] = '\0';
    yk__sds value = yk__sdsnewlen(path, length);
    free(path);
    return value;
}
yk__sds yy__os_exe_path() 
{
    int length = wai_getExecutablePath(NULL, 0, NULL);
    char* path = malloc(length + 1);
    if (path == NULL) return yk__sdsempty();
    int path_len;
    wai_getExecutablePath(path, length, &path_len);
    path[path_len] = '\0';
    yk__sds value = yk__sdsnewlen(path, path_len);
    free(path);
    return value;
}
yk__sds yy__os_cwd() 
{
    char* path = yk__get_current_dir_path();
    if (path == NULL) return yk__sdsempty();
    yk__sds value = yk__sdsnewlen(path, strlen(path));
    free(path);
    return value;
}
yy__os_ProcessResult yy__os_run(yk__sds* nn__args) { return yk__run(nn__args); }
void yy__os_del_process_result(yy__os_ProcessResult nn__pr) { yk__free_process_result(nn__pr); }
bool yy__os_is_windows() 
{
    bool win = false;
    #if defined(_WIN32) || defined(_WIN64)
    win = true;
    #endif
    return win;
}
bool yy__os_is_macos() 
{
    bool mach_os = false;
    #if defined(__APPLE__) && defined(__MACH__)
    mach_os = true;
    #endif
    return mach_os;
}
yk__sds yy__os_getenv(yk__sds nn__name) { return yk__getenv(nn__name); }
yk__sds yy__os_which(yk__sds yy__os_binary) 
{
    yk__sds yy__os_bin1 = yk__sdsdup(yy__os_binary);
    yk__sds yy__os_bin2 = yk__sdsdup(yy__os_binary);
    yk__sds yy__os_bin3 = yk__sdsdup(yy__os_binary);
    yk__sds t__0 = yk__sdsnewlen("PATH", 4);
    yk__sds t__1 = yy__os_getenv(yk__sdsdup(t__0));
    yk__sds yy__os_env = yk__sdsdup((t__1));
    yk__sds t__2 = yk__sdsnewlen(":", 1);
    yk__sds yy__os_sep = yk__sdsdup(t__2);
    if (yy__os_is_windows())
    {
        yk__sds t__3 = yk__sdsnewlen(";", 1);
        yk__sdsfree(yy__os_sep);
        yy__os_sep = yk__sdsdup(t__3);
        yk__sds t__4 = yk__sdsnewlen(".exe", 4);
        yk__sds t__5 = yk__sdscatsds(yk__sdsdup(yy__os_bin1), t__4);
        yk__sdsfree(yy__os_bin1);
        yy__os_bin1 = yk__sdsdup(t__5);
        yk__sds t__6 = yk__sdsnewlen(".bat", 4);
        yk__sds t__7 = yk__sdscatsds(yk__sdsdup(yy__os_bin2), t__6);
        yk__sdsfree(yy__os_bin2);
        yy__os_bin2 = yk__sdsdup(t__7);
        yk__sds t__8 = yk__sdsnewlen(".cmd", 4);
        yk__sds t__9 = yk__sdscatsds(yk__sdsdup(yy__os_bin3), t__8);
        yk__sdsfree(yy__os_bin3);
        yy__os_bin3 = yk__sdsdup(t__9);
        yk__sdsfree(t__9);
        yk__sdsfree(t__8);
        yk__sdsfree(t__7);
        yk__sdsfree(t__6);
        yk__sdsfree(t__5);
        yk__sdsfree(t__4);
        yk__sdsfree(t__3);
    }
    yk__sds* yy__os_paths = yy__strings_split(yk__sdsdup(yy__os_env), yk__sdsdup(yy__os_sep));
    int32_t yy__os_length = yk__arrlen(yy__os_paths);
    while (1) {
        if (!((yy__os_length > INT32_C(0)))) { break; } // Check
        // Body of while loop

        {
            yy__os_length = (yy__os_length - INT32_C(1));
            yk__sds yy__os_cur_path = yk__sdsdup(yy__os_paths[yy__os_length]);
            yk__sds t__10 = yy__path_join(yk__sdsdup(yy__os_cur_path), yk__sdsdup(yy__os_bin1));
            yk__sds yy__os_full_path = yk__sdsdup((t__10));
            if (yy__path_executable(yk__sdsdup(yy__os_full_path)))
            {
                yk__sds t__11 = yy__os_full_path;
                yy__array_del_str_array(yy__os_paths);
                yk__sdsfree(t__10);
                yk__sdsfree(yy__os_cur_path);
                yk__sdsfree(yy__os_sep);
                yk__sdsfree(t__2);
                yk__sdsfree(yy__os_env);
                yk__sdsfree(t__1);
                yk__sdsfree(t__0);
                yk__sdsfree(yy__os_bin3);
                yk__sdsfree(yy__os_bin2);
                yk__sdsfree(yy__os_bin1);
                yk__sdsfree(yy__os_binary);
                return t__11;
            }
            if (yy__os_is_windows())
            {
                yk__sds t__12 = yy__path_join(yk__sdsdup(yy__os_cur_path), yk__sdsdup(yy__os_bin2));
                yk__sdsfree(yy__os_full_path);
                yy__os_full_path = yk__sdsdup((t__12));
                if (yy__path_exists(yk__sdsdup(yy__os_full_path)))
                {
                    yk__sds t__13 = yy__os_full_path;
                    yy__array_del_str_array(yy__os_paths);
                    yk__sdsfree(t__12);
                    yk__sdsfree(t__10);
                    yk__sdsfree(yy__os_cur_path);
                    yk__sdsfree(yy__os_sep);
                    yk__sdsfree(t__2);
                    yk__sdsfree(yy__os_env);
                    yk__sdsfree(t__1);
                    yk__sdsfree(t__0);
                    yk__sdsfree(yy__os_bin3);
                    yk__sdsfree(yy__os_bin2);
                    yk__sdsfree(yy__os_bin1);
                    yk__sdsfree(yy__os_binary);
                    return t__13;
                }
                yk__sds t__14 = yy__path_join(yk__sdsdup(yy__os_cur_path), yk__sdsdup(yy__os_bin3));
                yk__sdsfree(yy__os_full_path);
                yy__os_full_path = yk__sdsdup((t__14));
                if (yy__path_exists(yk__sdsdup(yy__os_full_path)))
                {
                    yk__sds t__15 = yy__os_full_path;
                    yy__array_del_str_array(yy__os_paths);
                    yk__sdsfree(t__14);
                    yk__sdsfree(t__12);
                    yk__sdsfree(t__10);
                    yk__sdsfree(yy__os_cur_path);
                    yk__sdsfree(yy__os_sep);
                    yk__sdsfree(t__2);
                    yk__sdsfree(yy__os_env);
                    yk__sdsfree(t__1);
                    yk__sdsfree(t__0);
                    yk__sdsfree(yy__os_bin3);
                    yk__sdsfree(yy__os_bin2);
                    yk__sdsfree(yy__os_bin1);
                    yk__sdsfree(yy__os_binary);
                    return t__15;
                }
                yk__sdsfree(t__14);
                yk__sdsfree(t__12);
            }
            yk__sdsfree(yy__os_full_path);
            yk__sdsfree(t__10);
            yk__sdsfree(yy__os_cur_path);
        }
    }
    yk__sds t__16 = yy__os_cwd();
    yk__sds t__17 = yy__path_join(yk__sdsdup((t__16)), yk__sdsdup(yy__os_bin1));
    yk__sds yy__os_special = yk__sdsdup((t__17));
    if (yy__path_executable(yk__sdsdup(yy__os_special)))
    {
        yk__sds t__18 = yy__os_special;
        yy__array_del_str_array(yy__os_paths);
        yk__sdsfree(t__17);
        yk__sdsfree(t__16);
        yk__sdsfree(yy__os_sep);
        yk__sdsfree(t__2);
        yk__sdsfree(yy__os_env);
        yk__sdsfree(t__1);
        yk__sdsfree(t__0);
        yk__sdsfree(yy__os_bin3);
        yk__sdsfree(yy__os_bin2);
        yk__sdsfree(yy__os_bin1);
        yk__sdsfree(yy__os_binary);
        return t__18;
    }
    if (yy__os_is_windows())
    {
        yk__sds t__19 = yy__os_cwd();
        yk__sds t__20 = yy__path_join(yk__sdsdup((t__19)), yk__sdsdup(yy__os_bin2));
        yk__sdsfree(yy__os_special);
        yy__os_special = yk__sdsdup((t__20));
        if (yy__path_exists(yk__sdsdup(yy__os_special)))
        {
            yk__sds t__21 = yy__os_special;
            yy__array_del_str_array(yy__os_paths);
            yk__sdsfree(t__20);
            yk__sdsfree(t__19);
            yk__sdsfree(t__17);
            yk__sdsfree(t__16);
            yk__sdsfree(yy__os_sep);
            yk__sdsfree(t__2);
            yk__sdsfree(yy__os_env);
            yk__sdsfree(t__1);
            yk__sdsfree(t__0);
            yk__sdsfree(yy__os_bin3);
            yk__sdsfree(yy__os_bin2);
            yk__sdsfree(yy__os_bin1);
            yk__sdsfree(yy__os_binary);
            return t__21;
        }
        yk__sds t__22 = yy__os_cwd();
        yk__sds t__23 = yy__path_join(yk__sdsdup((t__22)), yk__sdsdup(yy__os_bin3));
        yk__sdsfree(yy__os_special);
        yy__os_special = yk__sdsdup((t__23));
        if (yy__path_exists(yk__sdsdup(yy__os_special)))
        {
            yk__sds t__24 = yy__os_special;
            yy__array_del_str_array(yy__os_paths);
            yk__sdsfree(t__23);
            yk__sdsfree(t__22);
            yk__sdsfree(t__20);
            yk__sdsfree(t__19);
            yk__sdsfree(t__17);
            yk__sdsfree(t__16);
            yk__sdsfree(yy__os_sep);
            yk__sdsfree(t__2);
            yk__sdsfree(yy__os_env);
            yk__sdsfree(t__1);
            yk__sdsfree(t__0);
            yk__sdsfree(yy__os_bin3);
            yk__sdsfree(yy__os_bin2);
            yk__sdsfree(yy__os_bin1);
            yk__sdsfree(yy__os_binary);
            return t__24;
        }
        yk__sdsfree(t__23);
        yk__sdsfree(t__22);
        yk__sdsfree(t__20);
        yk__sdsfree(t__19);
    }
    yk__sds t__25 = yy__os_exe_path();
    yk__sds t__26 = yy__path_join(yk__sdsdup((t__25)), yk__sdsdup(yy__os_bin1));
    yk__sdsfree(yy__os_special);
    yy__os_special = yk__sdsdup((t__26));
    if (yy__path_executable(yk__sdsdup(yy__os_special)))
    {
        yk__sds t__27 = yy__os_special;
        yy__array_del_str_array(yy__os_paths);
        yk__sdsfree(t__26);
        yk__sdsfree(t__25);
        yk__sdsfree(t__17);
        yk__sdsfree(t__16);
        yk__sdsfree(yy__os_sep);
        yk__sdsfree(t__2);
        yk__sdsfree(yy__os_env);
        yk__sdsfree(t__1);
        yk__sdsfree(t__0);
        yk__sdsfree(yy__os_bin3);
        yk__sdsfree(yy__os_bin2);
        yk__sdsfree(yy__os_bin1);
        yk__sdsfree(yy__os_binary);
        return t__27;
    }
    if (yy__os_is_windows())
    {
        yk__sds t__28 = yy__os_exe_path();
        yk__sds t__29 = yy__path_join(yk__sdsdup((t__28)), yk__sdsdup(yy__os_bin2));
        yk__sdsfree(yy__os_special);
        yy__os_special = yk__sdsdup((t__29));
        if (yy__path_exists(yk__sdsdup(yy__os_special)))
        {
            yk__sds t__30 = yy__os_special;
            yy__array_del_str_array(yy__os_paths);
            yk__sdsfree(t__29);
            yk__sdsfree(t__28);
            yk__sdsfree(t__26);
            yk__sdsfree(t__25);
            yk__sdsfree(t__17);
            yk__sdsfree(t__16);
            yk__sdsfree(yy__os_sep);
            yk__sdsfree(t__2);
            yk__sdsfree(yy__os_env);
            yk__sdsfree(t__1);
            yk__sdsfree(t__0);
            yk__sdsfree(yy__os_bin3);
            yk__sdsfree(yy__os_bin2);
            yk__sdsfree(yy__os_bin1);
            yk__sdsfree(yy__os_binary);
            return t__30;
        }
        yk__sds t__31 = yy__os_exe_path();
        yk__sds t__32 = yy__path_join(yk__sdsdup((t__31)), yk__sdsdup(yy__os_bin3));
        yk__sdsfree(yy__os_special);
        yy__os_special = yk__sdsdup((t__32));
        if (yy__path_exists(yk__sdsdup(yy__os_special)))
        {
            yk__sds t__33 = yy__os_special;
            yy__array_del_str_array(yy__os_paths);
            yk__sdsfree(t__32);
            yk__sdsfree(t__31);
            yk__sdsfree(t__29);
            yk__sdsfree(t__28);
            yk__sdsfree(t__26);
            yk__sdsfree(t__25);
            yk__sdsfree(t__17);
            yk__sdsfree(t__16);
            yk__sdsfree(yy__os_sep);
            yk__sdsfree(t__2);
            yk__sdsfree(yy__os_env);
            yk__sdsfree(t__1);
            yk__sdsfree(t__0);
            yk__sdsfree(yy__os_bin3);
            yk__sdsfree(yy__os_bin2);
            yk__sdsfree(yy__os_bin1);
            yk__sdsfree(yy__os_binary);
            return t__33;
        }
        yk__sdsfree(t__32);
        yk__sdsfree(t__31);
        yk__sdsfree(t__29);
        yk__sdsfree(t__28);
    }
    yk__sds t__34 = yk__sdsempty();
    yy__array_del_str_array(yy__os_paths);
    yk__sdsfree(t__26);
    yk__sdsfree(t__25);
    yk__sdsfree(yy__os_special);
    yk__sdsfree(t__17);
    yk__sdsfree(t__16);
    yk__sdsfree(yy__os_sep);
    yk__sdsfree(t__2);
    yk__sdsfree(yy__os_env);
    yk__sdsfree(t__1);
    yk__sdsfree(t__0);
    yk__sdsfree(yy__os_bin3);
    yk__sdsfree(yy__os_bin2);
    yk__sdsfree(yy__os_bin1);
    yk__sdsfree(yy__os_binary);
    return t__34;
}
yk__sds yy__libs_version() 
{
    yk__sds t__0 = yk__sdsnewlen("0.1", 3);
    return t__0;
}
void yy__print_banner() 
{
    yk__sds t__0 = yk__sdsnewlen("\n    ╔═╗┌─┐┬─┐╔═╗┌┐┌┌┬┐┬─┐\n    ║  ├─┤├┬┘╠═╝│││ │ ├┬┘\n    ╚═╝┴ ┴┴└─╩  ┘└┘ ┴ ┴└─\n    ", 191);
    yk__sds yy__art = yk__sdsdup(t__0);
    yk__sds t__1 = yk__sdsnewlen("\n    Tool for building Yaksha\n    Projects\n    ", 47);
    yk__sds yy__text = yk__sdsdup(t__1);
    yk__sds t__2 = yk__sdsnewlen("\n       ,\n      /(  ___________\n     |  >:===========`\n      )(\n      \"\"\n", 73);
    yk__sds yy__art2 = yk__sdsdup(t__2);
    yy__console_green(yk__sdsdup(yy__art));
    yy__console_cyan(yk__sdsdup(yy__text));
    yy__console_yellow(yk__sdsdup(yy__art2));
    yk__sdsfree(yy__art2);
    yk__sdsfree(t__2);
    yk__sdsfree(yy__text);
    yk__sdsfree(t__1);
    yk__sdsfree(yy__art);
    yk__sdsfree(t__0);
    return;
}
void yy__print_errors(yk__sds* yy__er) 
{
    int32_t yy__length = yk__arrlen(yy__er);
    int32_t yy__x = INT32_C(0);
    while (1) {
        if (!((yy__x < yy__length))) { break; } // Check
        // Body of while loop

        {
            yk__sds t__3 = yk__sdsnewlen("\n", 1);
            yk__sds t__4 = yk__sdscatsds(yk__sdsdup(yy__er[yy__x]), t__3);
            yy__console_red(yk__sdsdup(t__4));
            yy__x = (yy__x + INT32_C(1));
            yk__sdsfree(t__4);
            yk__sdsfree(t__3);
        }
    }
    return;
}
void yy__printkv(yk__sds yy__k, yk__sds yy__v) 
{
    yy__console_cyan(yk__sdsdup(yy__k));
    yk__sds t__5 = yk__sdsnewlen(" := ", 4);
    yy__console_red(yk__sdsdup(t__5));
    if ((yk__sdslen(yy__v) == INT32_C(0)))
    {
        yk__sds t__6 = yk__sdsnewlen("<not found>", 11);
        yy__console_green(yk__sdsdup(t__6));
        yk__sdsfree(t__6);
    }
    else
    {
        yy__console_green(yk__sdsdup(yy__v));
    }
    yk__sds t__7 = yk__sdsnewlen("\n", 1);
    yk__printstr((t__7));
    yk__sdsfree(t__7);
    yk__sdsfree(t__5);
    yk__sdsfree(yy__v);
    yk__sdsfree(yy__k);
    return;
}
void yy__print_config(struct yy__configuration_Config* yy__config) 
{
    yk__sds t__8 = yk__sdsnewlen("libs", 4);
    yy__printkv(yk__sdsdup(t__8), yk__sdsdup(yy__config->yy__configuration_libs_path));
    yk__sds t__9 = yk__sdsnewlen("runtime", 7);
    yy__printkv(yk__sdsdup(t__9), yk__sdsdup(yy__config->yy__configuration_runtime_path));
    yk__sds t__10 = yk__sdsnewlen("compiler", 8);
    yy__printkv(yk__sdsdup(t__10), yk__sdsdup(yy__config->yy__configuration_compiler_path));
    yk__sds t__11 = yk__sdsnewlen("zig compiler", 12);
    yy__printkv(yk__sdsdup(t__11), yk__sdsdup(yy__config->yy__configuration_zig_compiler_path));
    yk__sds t__12 = yk__sdsnewlen("emcc compiler", 13);
    yy__printkv(yk__sdsdup(t__12), yk__sdsdup(yy__config->yy__configuration_emcc_compiler_path));
    yk__sds t__13 = yk__sdsnewlen("emrun", 5);
    yy__printkv(yk__sdsdup(t__13), yk__sdsdup(yy__config->yy__configuration_emrun_path));
    yk__sds t__14 = yk__sdsnewlen("w4", 2);
    yy__printkv(yk__sdsdup(t__14), yk__sdsdup(yy__config->yy__configuration_w4_path));
    yk__sds t__15 = yk__sdsnewlen("standard library version", 24);
    yk__sds t__16 = yy__libs_version();
    yy__printkv(yk__sdsdup(t__15), yk__sdsdup((t__16)));
    yk__sdsfree(t__16);
    yk__sdsfree(t__15);
    yk__sdsfree(t__14);
    yk__sdsfree(t__13);
    yk__sdsfree(t__12);
    yk__sdsfree(t__11);
    yk__sdsfree(t__10);
    yk__sdsfree(t__9);
    yk__sdsfree(t__8);
    return;
}
int32_t yy__build_from_config(struct yy__configuration_Config* yy__config, bool yy__simple) 
{
    int32_t yy__return_val = INT32_C(0);
    yk__sds t__17 = yk__sdsnewlen("compile", 7);
    yk__sds* t__18 = NULL;
    yk__arrsetcap(t__18, 4);
    yk__arrput(t__18, yk__sdsdup(yy__config->yy__configuration_compiler_path));
    yk__arrput(t__18, yk__sdsdup(t__17));
    yk__arrput(t__18, yk__sdsdup(yy__config->yy__configuration_project->yy__configuration_main));
    yk__arrput(t__18, yk__sdsdup(yy__config->yy__configuration_libs_path));
    yk__sds* yy__yk_args = t__18;
    yy__os_ProcessResult yy__result = yy__os_run(yy__yk_args);
    if ((! (yy__result->ok)))
    {
        yk__sds t__19 = yk__sdsnewlen("---- running Yaksha compiler ---\n", 33);
        yy__console_cyan(yk__sdsdup(t__19));
        yk__sds t__20 = yk__sdsnewlen("Failed to execute: ", 19);
        yy__console_red(yk__sdsdup(t__20));
        yk__sds t__21 = yk__sdsnewlen(" ", 1);
        yk__sds t__22 = yy__array_join(yy__yk_args, yk__sdsdup(t__21));
        yy__console_yellow(yk__sdsdup((t__22)));
        yk__sds t__23 = yk__sdsnewlen("\n", 1);
        yk__printstr((t__23));
        yy__console_red(yk__sdsdup(yy__result->output));
        yk__sds t__24 = yk__sdsnewlen("\n", 1);
        yk__printstr((t__24));
        yy__return_val = (- (INT32_C(1)));
        yk__sds t__25 = yk__sdsnewlen("---- end of compiler run ---\n", 29);
        yy__console_cyan(yk__sdsdup(t__25));
        yk__sdsfree(t__25);
        yk__sdsfree(t__24);
        yk__sdsfree(t__23);
        yk__sdsfree(t__22);
        yk__sdsfree(t__21);
        yk__sdsfree(t__20);
        yk__sdsfree(t__19);
    }
    else
    {
        yk__sds t__26 = yk__sdsnewlen("// YK", 5);
        if (yy__strings_startswith(yk__sdsdup(yy__result->output), yk__sdsdup(t__26)))
        {
            if (yy__simple)
            {
                yy__return_val = yy__building_build_simple(yy__config, yk__sdsdup(yy__result->output));
            }
            else
            {
                yy__return_val = yy__building_build(yy__config, yk__sdsdup(yy__result->output));
            }
        }
        else
        {
            yk__sds t__27 = yk__sdsnewlen("---- running Yaksha compiler ---\n", 33);
            yy__console_cyan(yk__sdsdup(t__27));
            yy__console_red(yk__sdsdup(yy__result->output));
            yk__sds t__28 = yk__sdsnewlen("\n", 1);
            yk__printstr((t__28));
            yy__return_val = (- (INT32_C(1)));
            yk__sds t__29 = yk__sdsnewlen("---- end of compiler run ---\n", 29);
            yy__console_cyan(yk__sdsdup(t__29));
            yk__sdsfree(t__29);
            yk__sdsfree(t__28);
            yk__sdsfree(t__27);
        }
        yk__sdsfree(t__26);
    }
    int32_t t__30 = yy__return_val;
    yy__os_del_process_result(yy__result);
    yy__array_del_str_array(yy__yk_args);
    yk__sdsfree(t__17);
    return t__30;
}
int32_t yy__perform_build() 
{
    struct yy__configuration_Config* yy__config = yy__configuration_load_config();
    if ((yk__arrlen(yy__config->yy__configuration_errors) > INT32_C(0)))
    {
        yy__print_errors(yy__config->yy__configuration_errors);
        int32_t t__31 = (- (INT32_C(1)));
        yy__configuration_del_config(yy__config);
        return t__31;
    }
    yy__print_config(yy__config);
    int32_t yy__ret = yy__build_from_config(yy__config, false);
    int32_t t__32 = yy__ret;
    yy__configuration_del_config(yy__config);
    return t__32;
}
int32_t yy__perform_mini_build(yk__sds yy__filename, bool yy__use_raylib, bool yy__use_web, bool yy__wasm4, yk__sds yy__web_shell, bool yy__silent, bool yy__actually_run, bool yy__crdll, bool yy__no_parallel) 
{
    yk__sds t__33 = yy__path_basename(yk__sdsdup(yy__filename));
    yk__sds t__34 = yy__path_remove_extension(yk__sdsdup((t__33)));
    yk__sds yy__name = yk__sdsdup((t__34));
    struct yy__configuration_Config* yy__config = yy__configuration_create_adhoc_config(yk__sdsdup(yy__name), yk__sdsdup(yy__filename), yy__use_raylib, yy__use_web, yy__wasm4, yk__sdsdup(yy__web_shell), yy__crdll, yy__no_parallel);
    if ((yk__arrlen(yy__config->yy__configuration_errors) > INT32_C(0)))
    {
        yy__print_errors(yy__config->yy__configuration_errors);
        int32_t t__35 = (- (INT32_C(1)));
        yy__configuration_del_config(yy__config);
        yk__sdsfree(yy__name);
        yk__sdsfree(t__34);
        yk__sdsfree(t__33);
        yk__sdsfree(yy__web_shell);
        yk__sdsfree(yy__filename);
        return t__35;
    }
    if ((! (yy__silent)))
    {
        yy__print_config(yy__config);
    }
    int32_t yy__ret = yy__build_from_config(yy__config, true);
    if ((yy__ret != INT32_C(0)))
    {
        int32_t t__36 = yy__ret;
        yy__configuration_del_config(yy__config);
        yk__sdsfree(yy__name);
        yk__sdsfree(t__34);
        yk__sdsfree(t__33);
        yk__sdsfree(yy__web_shell);
        yk__sdsfree(yy__filename);
        return t__36;
    }
    if ((! (yy__actually_run)))
    {
        yy__configuration_del_config(yy__config);
        yk__sdsfree(yy__name);
        yk__sdsfree(t__34);
        yk__sdsfree(t__33);
        yk__sdsfree(yy__web_shell);
        yk__sdsfree(yy__filename);
        return INT32_C(0);
    }
    yk__sds t__37 = yk__sdsnewlen("-----------------------------", 29);
    yy__console_cyan(yk__sdsdup(t__37));
    yk__sds t__38 = yk__sdsnewlen("\n", 1);
    yk__printstr((t__38));
    yk__sds yy__binary = yk__sdsdup(yy__name);
    if (yy__use_web)
    {
        yk__sds t__39 = yk__sdsnewlen(".html", 5);
        yk__sds t__40 = yk__sdscatsds(yk__sdsdup(yy__binary), t__39);
        yk__sdsfree(yy__binary);
        yy__binary = yk__sdsdup(t__40);
        yk__sds t__41 = yy__os_cwd();
        yk__sds t__42 = yy__path_join(yk__sdsdup((t__41)), yk__sdsdup(yy__binary));
        yk__sds* t__43 = NULL;
        yk__arrsetcap(t__43, 2);
        yk__arrput(t__43, yk__sdsdup(yy__config->yy__configuration_emrun_path));
        yk__arrput(t__43, yk__sdsdup((t__42)));
        yk__sds* yy__em_args = t__43;
        yy__os_ProcessResult yy__r = yy__os_run(yy__em_args);
        yy__array_del_str_array(yy__em_args);
        yy__os_del_process_result(yy__r);
        yk__sdsfree(t__42);
        yk__sdsfree(t__41);
        yk__sdsfree(t__40);
        yk__sdsfree(t__39);
    }
    else
    {
        if (yy__wasm4)
        {
            yk__sds t__44 = yk__sdsnewlen(".wasm", 5);
            yk__sds t__45 = yk__sdscatsds(yk__sdsdup(yy__binary), t__44);
            yk__sdsfree(yy__binary);
            yy__binary = yk__sdsdup(t__45);
            yk__sds t__46 = yk__sdsnewlen("run-native", 10);
            yk__sds t__47 = yy__os_cwd();
            yk__sds t__48 = yy__path_join(yk__sdsdup((t__47)), yk__sdsdup(yy__binary));
            yk__sds* t__49 = NULL;
            yk__arrsetcap(t__49, 3);
            yk__arrput(t__49, yk__sdsdup(yy__config->yy__configuration_w4_path));
            yk__arrput(t__49, yk__sdsdup(t__46));
            yk__arrput(t__49, yk__sdsdup((t__48)));
            yk__sds* yy__em_args = t__49;
            yy__os_ProcessResult yy__r = yy__os_run(yy__em_args);
            yy__array_del_str_array(yy__em_args);
            yy__os_del_process_result(yy__r);
            yk__sdsfree(t__48);
            yk__sdsfree(t__47);
            yk__sdsfree(t__46);
            yk__sdsfree(t__45);
            yk__sdsfree(t__44);
        }
        else
        {
            if (yy__os_is_windows())
            {
                yk__sds t__50 = yk__sdsnewlen(".exe", 4);
                yk__sds t__51 = yk__sdscatsds(yk__sdsdup(yy__binary), t__50);
                yk__sdsfree(yy__binary);
                yy__binary = yk__sdsdup(t__51);
                yk__sdsfree(t__51);
                yk__sdsfree(t__50);
            }
            else
            {
                yk__sds t__52 = yk__sdsnewlen("./", 2);
                yk__sds t__53 = yk__sdscatsds(yk__sdsdup(t__52), yy__binary);
                yk__sdsfree(yy__binary);
                yy__binary = yk__sdsdup(t__53);
                yk__sdsfree(t__53);
                yk__sdsfree(t__52);
            }
            yy__c_CStr yy__binary_cstr = yy__strings_to_cstr(yk__sdsdup(yy__binary));
            yy__c_system(yy__binary_cstr);
            yy__strings_del_str(yy__binary_cstr);
        }
    }
    yy__configuration_del_config(yy__config);
    yk__sdsfree(yy__binary);
    yk__sdsfree(t__38);
    yk__sdsfree(t__37);
    yk__sdsfree(yy__name);
    yk__sdsfree(t__34);
    yk__sdsfree(t__33);
    yk__sdsfree(yy__web_shell);
    yk__sdsfree(yy__filename);
    return INT32_C(0);
}
int32_t yy__handle_args(yy__os_Arguments yy__args) 
{
    yk__sds* yy__arguments = yy__array_dup(yy__args->argv);
    yy__argparse_Option* yy__options = NULL;
    yk__sds t__54 = yk__sdsnewlen("carpntr", 7);
    yk__sds t__55 = yk__sdsnewlen("carpntr [options] file", 22);
    yk__sds* t__56 = NULL;
    yk__arrsetcap(t__56, 2);
    yk__arrput(t__56, yk__sdsdup(t__54));
    yk__arrput(t__56, yk__sdsdup(t__55));
    yk__sds* yy__usages = t__56;
    int32_t yy__help = INT32_C(0);
    int32_t yy__run = INT32_C(0);
    int32_t yy__just_compile = INT32_C(0);
    int32_t yy__raylib = INT32_C(0);
    int32_t yy__crdll = INT32_C(0);
    int32_t yy__web = INT32_C(0);
    int32_t yy__wasm4 = INT32_C(0);
    int32_t yy__silent_mode = INT32_C(0);
    int32_t yy__no_parallel = INT32_C(0);
    yy__c_CStr yy__file_path = yy__strings_null_cstr();
    yk__sds t__57 = yk__sdsempty();
    yk__sds yy__web_shell = yk__sdsdup(t__57);
    yk__sds t__58 = yk__sdsnewlen("h", 1);
    yk__sds t__59 = yk__sdsnewlen("help", 4);
    yk__sds t__60 = yk__sdsnewlen("show help and exit", 18);
    yk__arrput(yy__options, yy__argparse_opt_boolean(yk__sdsdup(t__58), yk__sdsdup(t__59), (&(yy__help)), yk__sdsdup(t__60)));
    yk__sds t__61 = yk__sdsnewlen("R", 1);
    yk__sds t__62 = yk__sdsnewlen("run", 3);
    yk__sds t__63 = yk__sdsnewlen("run a single file", 17);
    yk__arrput(yy__options, yy__argparse_opt_boolean(yk__sdsdup(t__61), yk__sdsdup(t__62), (&(yy__run)), yk__sdsdup(t__63)));
    yk__sds t__64 = yk__sdsnewlen("C", 1);
    yk__sds t__65 = yk__sdsnewlen("compile", 7);
    yk__sds t__66 = yk__sdsnewlen("compile a single file", 21);
    yk__arrput(yy__options, yy__argparse_opt_boolean(yk__sdsdup(t__64), yk__sdsdup(t__65), (&(yy__just_compile)), yk__sdsdup(t__66)));
    yk__sds t__67 = yk__sdsnewlen("r", 1);
    yk__sds t__68 = yk__sdsnewlen("raylib", 6);
    yk__sds t__69 = yk__sdsnewlen("enable raylib", 13);
    yk__arrput(yy__options, yy__argparse_opt_boolean(yk__sdsdup(t__67), yk__sdsdup(t__68), (&(yy__raylib)), yk__sdsdup(t__69)));
    yk__sds t__70 = yk__sdsnewlen("w", 1);
    yk__sds t__71 = yk__sdsnewlen("web", 3);
    yk__sds t__72 = yk__sdsnewlen("build for web (works only with raylib)", 38);
    yk__arrput(yy__options, yy__argparse_opt_boolean(yk__sdsdup(t__70), yk__sdsdup(t__71), (&(yy__web)), yk__sdsdup(t__72)));
    yk__sds t__73 = yk__sdsnewlen("d", 1);
    yk__sds t__74 = yk__sdsnewlen("dll", 3);
    yk__sds t__75 = yk__sdsnewlen("enable .dll client build for hot reloading with ykreload/cr.h (works only with raylib)", 86);
    yk__arrput(yy__options, yy__argparse_opt_boolean(yk__sdsdup(t__73), yk__sdsdup(t__74), (&(yy__crdll)), yk__sdsdup(t__75)));
    yk__sds t__76 = yk__sdsnewlen("s", 1);
    yk__sds t__77 = yk__sdsnewlen("shell", 5);
    yk__sds t__78 = yk__sdsnewlen("specify shell file for web builds", 33);
    yk__arrput(yy__options, yy__argparse_opt_string(yk__sdsdup(t__76), yk__sdsdup(t__77), (&(yy__file_path)), yk__sdsdup(t__78)));
    yk__sds t__79 = yk__sdsnewlen("4", 1);
    yk__sds t__80 = yk__sdsnewlen("wasm4", 5);
    yk__sds t__81 = yk__sdsnewlen("wasm4 build", 11);
    yk__arrput(yy__options, yy__argparse_opt_boolean(yk__sdsdup(t__79), yk__sdsdup(t__80), (&(yy__wasm4)), yk__sdsdup(t__81)));
    yk__sds t__82 = yk__sdsnewlen("S", 1);
    yk__sds t__83 = yk__sdsnewlen("silent", 6);
    yk__sds t__84 = yk__sdsnewlen("do not print anything except errors", 35);
    yk__arrput(yy__options, yy__argparse_opt_boolean(yk__sdsdup(t__82), yk__sdsdup(t__83), (&(yy__silent_mode)), yk__sdsdup(t__84)));
    yk__sds t__85 = yk__sdsnewlen("N", 1);
    yk__sds t__86 = yk__sdsnewlen("nothread", 8);
    yk__sds t__87 = yk__sdsnewlen("no parallel builds (for debugging)", 34);
    yk__arrput(yy__options, yy__argparse_opt_boolean(yk__sdsdup(t__85), yk__sdsdup(t__86), (&(yy__no_parallel)), yk__sdsdup(t__87)));
    yk__arrput(yy__options, yy__argparse_opt_end());
    yy__argparse_ArgParseWrapper yy__a = yy__argparse_new(yy__options, yy__usages);
    yy__argparse_ArgParseRemainder yy__remainder = yy__argparse_parse(yy__a->state, yy__arguments);
    if ((yy__silent_mode != INT32_C(1)))
    {
        yy__print_banner();
    }
    if ((yy__help == INT32_C(1)))
    {
        yy__argparse_usage(yy__a->state);
        yy__strings_del_cstr(yy__file_path);
        yy__argparse_del_remainder(yy__remainder);
        yy__argparse_del_argparse(yy__a);
        yy__array_del_str_array(yy__usages);
        yk__arrfree(yy__options);
        yy__array_del_str_array(yy__arguments);
        yk__sdsfree(t__87);
        yk__sdsfree(t__86);
        yk__sdsfree(t__85);
        yk__sdsfree(t__84);
        yk__sdsfree(t__83);
        yk__sdsfree(t__82);
        yk__sdsfree(t__81);
        yk__sdsfree(t__80);
        yk__sdsfree(t__79);
        yk__sdsfree(t__78);
        yk__sdsfree(t__77);
        yk__sdsfree(t__76);
        yk__sdsfree(t__75);
        yk__sdsfree(t__74);
        yk__sdsfree(t__73);
        yk__sdsfree(t__72);
        yk__sdsfree(t__71);
        yk__sdsfree(t__70);
        yk__sdsfree(t__69);
        yk__sdsfree(t__68);
        yk__sdsfree(t__67);
        yk__sdsfree(t__66);
        yk__sdsfree(t__65);
        yk__sdsfree(t__64);
        yk__sdsfree(t__63);
        yk__sdsfree(t__62);
        yk__sdsfree(t__61);
        yk__sdsfree(t__60);
        yk__sdsfree(t__59);
        yk__sdsfree(t__58);
        yk__sdsfree(yy__web_shell);
        yk__sdsfree(t__57);
        yk__sdsfree(t__55);
        yk__sdsfree(t__54);
        return INT32_C(0);
    }
    if ((yy__remainder->argc != INT32_C(1)))
    {
        yk__sds t__88 = yk__sdsnewlen("One file must be preset for excution", 36);
        yk__printlnstr((t__88));
        yy__strings_del_cstr(yy__file_path);
        yy__argparse_del_remainder(yy__remainder);
        yy__argparse_del_argparse(yy__a);
        yy__array_del_str_array(yy__usages);
        yk__arrfree(yy__options);
        yy__array_del_str_array(yy__arguments);
        yk__sdsfree(t__88);
        yk__sdsfree(t__87);
        yk__sdsfree(t__86);
        yk__sdsfree(t__85);
        yk__sdsfree(t__84);
        yk__sdsfree(t__83);
        yk__sdsfree(t__82);
        yk__sdsfree(t__81);
        yk__sdsfree(t__80);
        yk__sdsfree(t__79);
        yk__sdsfree(t__78);
        yk__sdsfree(t__77);
        yk__sdsfree(t__76);
        yk__sdsfree(t__75);
        yk__sdsfree(t__74);
        yk__sdsfree(t__73);
        yk__sdsfree(t__72);
        yk__sdsfree(t__71);
        yk__sdsfree(t__70);
        yk__sdsfree(t__69);
        yk__sdsfree(t__68);
        yk__sdsfree(t__67);
        yk__sdsfree(t__66);
        yk__sdsfree(t__65);
        yk__sdsfree(t__64);
        yk__sdsfree(t__63);
        yk__sdsfree(t__62);
        yk__sdsfree(t__61);
        yk__sdsfree(t__60);
        yk__sdsfree(t__59);
        yk__sdsfree(t__58);
        yk__sdsfree(yy__web_shell);
        yk__sdsfree(t__57);
        yk__sdsfree(t__55);
        yk__sdsfree(t__54);
        return INT32_C(1);
        yk__sdsfree(t__88);
    }
    yk__sds yy__single_file = yk__sdsdup(yy__remainder->remainder[INT32_C(0)]);
    if (((yy__wasm4 == INT32_C(1)) && (((yy__raylib == INT32_C(1)) || (yy__web == INT32_C(1))))))
    {
        yk__sds t__89 = yk__sdsnewlen("Wasm4 is not compatible with raylib/web", 39);
        yk__printlnstr((t__89));
        yy__strings_del_cstr(yy__file_path);
        yy__argparse_del_remainder(yy__remainder);
        yy__argparse_del_argparse(yy__a);
        yy__array_del_str_array(yy__usages);
        yk__arrfree(yy__options);
        yy__array_del_str_array(yy__arguments);
        yk__sdsfree(t__89);
        yk__sdsfree(yy__single_file);
        yk__sdsfree(t__87);
        yk__sdsfree(t__86);
        yk__sdsfree(t__85);
        yk__sdsfree(t__84);
        yk__sdsfree(t__83);
        yk__sdsfree(t__82);
        yk__sdsfree(t__81);
        yk__sdsfree(t__80);
        yk__sdsfree(t__79);
        yk__sdsfree(t__78);
        yk__sdsfree(t__77);
        yk__sdsfree(t__76);
        yk__sdsfree(t__75);
        yk__sdsfree(t__74);
        yk__sdsfree(t__73);
        yk__sdsfree(t__72);
        yk__sdsfree(t__71);
        yk__sdsfree(t__70);
        yk__sdsfree(t__69);
        yk__sdsfree(t__68);
        yk__sdsfree(t__67);
        yk__sdsfree(t__66);
        yk__sdsfree(t__65);
        yk__sdsfree(t__64);
        yk__sdsfree(t__63);
        yk__sdsfree(t__62);
        yk__sdsfree(t__61);
        yk__sdsfree(t__60);
        yk__sdsfree(t__59);
        yk__sdsfree(t__58);
        yk__sdsfree(yy__web_shell);
        yk__sdsfree(t__57);
        yk__sdsfree(t__55);
        yk__sdsfree(t__54);
        return INT32_C(1);
        yk__sdsfree(t__89);
    }
    if (((yy__web == INT32_C(1)) && (yy__raylib != INT32_C(1))))
    {
        yk__sds t__90 = yk__sdsnewlen("Web is only supported with raylib", 33);
        yk__printlnstr((t__90));
        yy__strings_del_cstr(yy__file_path);
        yy__argparse_del_remainder(yy__remainder);
        yy__argparse_del_argparse(yy__a);
        yy__array_del_str_array(yy__usages);
        yk__arrfree(yy__options);
        yy__array_del_str_array(yy__arguments);
        yk__sdsfree(t__90);
        yk__sdsfree(yy__single_file);
        yk__sdsfree(t__87);
        yk__sdsfree(t__86);
        yk__sdsfree(t__85);
        yk__sdsfree(t__84);
        yk__sdsfree(t__83);
        yk__sdsfree(t__82);
        yk__sdsfree(t__81);
        yk__sdsfree(t__80);
        yk__sdsfree(t__79);
        yk__sdsfree(t__78);
        yk__sdsfree(t__77);
        yk__sdsfree(t__76);
        yk__sdsfree(t__75);
        yk__sdsfree(t__74);
        yk__sdsfree(t__73);
        yk__sdsfree(t__72);
        yk__sdsfree(t__71);
        yk__sdsfree(t__70);
        yk__sdsfree(t__69);
        yk__sdsfree(t__68);
        yk__sdsfree(t__67);
        yk__sdsfree(t__66);
        yk__sdsfree(t__65);
        yk__sdsfree(t__64);
        yk__sdsfree(t__63);
        yk__sdsfree(t__62);
        yk__sdsfree(t__61);
        yk__sdsfree(t__60);
        yk__sdsfree(t__59);
        yk__sdsfree(t__58);
        yk__sdsfree(yy__web_shell);
        yk__sdsfree(t__57);
        yk__sdsfree(t__55);
        yk__sdsfree(t__54);
        return INT32_C(1);
        yk__sdsfree(t__90);
    }
    if (((yy__web != INT32_C(1)) && yy__strings_valid_cstr(yy__file_path)))
    {
        yk__sds t__91 = yk__sdsnewlen("Shell is only supported with web", 32);
        yk__printlnstr((t__91));
        yy__strings_del_cstr(yy__file_path);
        yy__argparse_del_remainder(yy__remainder);
        yy__argparse_del_argparse(yy__a);
        yy__array_del_str_array(yy__usages);
        yk__arrfree(yy__options);
        yy__array_del_str_array(yy__arguments);
        yk__sdsfree(t__91);
        yk__sdsfree(yy__single_file);
        yk__sdsfree(t__87);
        yk__sdsfree(t__86);
        yk__sdsfree(t__85);
        yk__sdsfree(t__84);
        yk__sdsfree(t__83);
        yk__sdsfree(t__82);
        yk__sdsfree(t__81);
        yk__sdsfree(t__80);
        yk__sdsfree(t__79);
        yk__sdsfree(t__78);
        yk__sdsfree(t__77);
        yk__sdsfree(t__76);
        yk__sdsfree(t__75);
        yk__sdsfree(t__74);
        yk__sdsfree(t__73);
        yk__sdsfree(t__72);
        yk__sdsfree(t__71);
        yk__sdsfree(t__70);
        yk__sdsfree(t__69);
        yk__sdsfree(t__68);
        yk__sdsfree(t__67);
        yk__sdsfree(t__66);
        yk__sdsfree(t__65);
        yk__sdsfree(t__64);
        yk__sdsfree(t__63);
        yk__sdsfree(t__62);
        yk__sdsfree(t__61);
        yk__sdsfree(t__60);
        yk__sdsfree(t__59);
        yk__sdsfree(t__58);
        yk__sdsfree(yy__web_shell);
        yk__sdsfree(t__57);
        yk__sdsfree(t__55);
        yk__sdsfree(t__54);
        return INT32_C(1);
        yk__sdsfree(t__91);
    }
    if (((yy__run == INT32_C(1)) && (yy__crdll == INT32_C(1))))
    {
        yk__sds t__92 = yk__sdsnewlen("Use -C instead of -R to compile a dll.", 38);
        yk__printlnstr((t__92));
        yy__strings_del_cstr(yy__file_path);
        yy__argparse_del_remainder(yy__remainder);
        yy__argparse_del_argparse(yy__a);
        yy__array_del_str_array(yy__usages);
        yk__arrfree(yy__options);
        yy__array_del_str_array(yy__arguments);
        yk__sdsfree(t__92);
        yk__sdsfree(yy__single_file);
        yk__sdsfree(t__87);
        yk__sdsfree(t__86);
        yk__sdsfree(t__85);
        yk__sdsfree(t__84);
        yk__sdsfree(t__83);
        yk__sdsfree(t__82);
        yk__sdsfree(t__81);
        yk__sdsfree(t__80);
        yk__sdsfree(t__79);
        yk__sdsfree(t__78);
        yk__sdsfree(t__77);
        yk__sdsfree(t__76);
        yk__sdsfree(t__75);
        yk__sdsfree(t__74);
        yk__sdsfree(t__73);
        yk__sdsfree(t__72);
        yk__sdsfree(t__71);
        yk__sdsfree(t__70);
        yk__sdsfree(t__69);
        yk__sdsfree(t__68);
        yk__sdsfree(t__67);
        yk__sdsfree(t__66);
        yk__sdsfree(t__65);
        yk__sdsfree(t__64);
        yk__sdsfree(t__63);
        yk__sdsfree(t__62);
        yk__sdsfree(t__61);
        yk__sdsfree(t__60);
        yk__sdsfree(t__59);
        yk__sdsfree(t__58);
        yk__sdsfree(yy__web_shell);
        yk__sdsfree(t__57);
        yk__sdsfree(t__55);
        yk__sdsfree(t__54);
        return INT32_C(1);
        yk__sdsfree(t__92);
    }
    if (((yy__run == INT32_C(1)) || (yy__just_compile == INT32_C(1))))
    {
        if (yy__strings_valid_cstr(yy__file_path))
        {
            yk__sds t__93 = yy__strings_from_cstr(yy__file_path);
            yk__sdsfree(yy__web_shell);
            yy__web_shell = yk__sdsdup((t__93));
            yk__sds t__94 = yk__sdsnewlen("Using web-shell:", 16);
            yk__printstr((t__94));
            yk__printlnstr((yy__web_shell));
            yk__sdsfree(t__94);
            yk__sdsfree(t__93);
        }
        int32_t t__95 = yy__perform_mini_build(yk__sdsdup(yy__single_file), (yy__raylib == INT32_C(1)), (yy__web == INT32_C(1)), (yy__wasm4 == INT32_C(1)), yk__sdsdup(yy__web_shell), (yy__silent_mode == INT32_C(1)), (yy__run == INT32_C(1)), (yy__crdll == INT32_C(1)), (yy__no_parallel == INT32_C(1)));
        yy__strings_del_cstr(yy__file_path);
        yy__argparse_del_remainder(yy__remainder);
        yy__argparse_del_argparse(yy__a);
        yy__array_del_str_array(yy__usages);
        yk__arrfree(yy__options);
        yy__array_del_str_array(yy__arguments);
        yk__sdsfree(yy__single_file);
        yk__sdsfree(t__87);
        yk__sdsfree(t__86);
        yk__sdsfree(t__85);
        yk__sdsfree(t__84);
        yk__sdsfree(t__83);
        yk__sdsfree(t__82);
        yk__sdsfree(t__81);
        yk__sdsfree(t__80);
        yk__sdsfree(t__79);
        yk__sdsfree(t__78);
        yk__sdsfree(t__77);
        yk__sdsfree(t__76);
        yk__sdsfree(t__75);
        yk__sdsfree(t__74);
        yk__sdsfree(t__73);
        yk__sdsfree(t__72);
        yk__sdsfree(t__71);
        yk__sdsfree(t__70);
        yk__sdsfree(t__69);
        yk__sdsfree(t__68);
        yk__sdsfree(t__67);
        yk__sdsfree(t__66);
        yk__sdsfree(t__65);
        yk__sdsfree(t__64);
        yk__sdsfree(t__63);
        yk__sdsfree(t__62);
        yk__sdsfree(t__61);
        yk__sdsfree(t__60);
        yk__sdsfree(t__59);
        yk__sdsfree(t__58);
        yk__sdsfree(yy__web_shell);
        yk__sdsfree(t__57);
        yk__sdsfree(t__55);
        yk__sdsfree(t__54);
        return t__95;
    }
    yk__sds t__96 = yk__sdsnewlen("Invalid usage. Please use \'-R\' option if you want to run a program. Try \'carpntr --help\' for more information.\n", 111);
    yy__console_red(yk__sdsdup(t__96));
    yy__strings_del_cstr(yy__file_path);
    yy__argparse_del_remainder(yy__remainder);
    yy__argparse_del_argparse(yy__a);
    yy__array_del_str_array(yy__usages);
    yk__arrfree(yy__options);
    yy__array_del_str_array(yy__arguments);
    yk__sdsfree(t__96);
    yk__sdsfree(yy__single_file);
    yk__sdsfree(t__87);
    yk__sdsfree(t__86);
    yk__sdsfree(t__85);
    yk__sdsfree(t__84);
    yk__sdsfree(t__83);
    yk__sdsfree(t__82);
    yk__sdsfree(t__81);
    yk__sdsfree(t__80);
    yk__sdsfree(t__79);
    yk__sdsfree(t__78);
    yk__sdsfree(t__77);
    yk__sdsfree(t__76);
    yk__sdsfree(t__75);
    yk__sdsfree(t__74);
    yk__sdsfree(t__73);
    yk__sdsfree(t__72);
    yk__sdsfree(t__71);
    yk__sdsfree(t__70);
    yk__sdsfree(t__69);
    yk__sdsfree(t__68);
    yk__sdsfree(t__67);
    yk__sdsfree(t__66);
    yk__sdsfree(t__65);
    yk__sdsfree(t__64);
    yk__sdsfree(t__63);
    yk__sdsfree(t__62);
    yk__sdsfree(t__61);
    yk__sdsfree(t__60);
    yk__sdsfree(t__59);
    yk__sdsfree(t__58);
    yk__sdsfree(yy__web_shell);
    yk__sdsfree(t__57);
    yk__sdsfree(t__55);
    yk__sdsfree(t__54);
    return INT32_C(0);
}
int32_t yy__main() 
{
    yy__os_Arguments yy__args = yy__os_get_args();
    if ((yy__args->argc <= INT32_C(1)))
    {
        yy__print_banner();
        int32_t t__97 = yy__perform_build();
        return t__97;
    }
    int32_t t__98 = yy__handle_args(yy__args);
    return t__98;
}
#if defined(YK__MINIMAL_MAIN)
int main(void) { return yy__main(); }
#endif
