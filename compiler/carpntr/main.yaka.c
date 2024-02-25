// YK:argparse,arrayutils,console,cpu,process,tinycthread,toml,whereami#
#include "yk__lib.h"
// --forward declarations-- 
int32_t const  yy__mutex_PLAIN = INT32_C(0);
int32_t const  yy__thread_SUCCESS = INT32_C(1);
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
int32_t const  yy__configuration_CLANG = INT32_C(44);
int32_t const  yy__configuration_GCC = INT32_C(33);
int32_t const  yy__configuration_NOT_FOUND = INT32_C(0);
int32_t const  yy__argparse_ARGPARSE_DEFAULT = INT32_C(0);
struct yy__raylib_support_CObject;
struct yy__raylib_support_BuildData;
#define yy__cpu_Cpu struct yk__cpu_info
#define yy__mutex_Mutex mtx_t
#define yy__condition_Condition cnd_t
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
#define yy__toml_Table toml_table_t*
#define yy__toml_TomlArray toml_array_t*
#define yy__toml_valid_table(nn__x) (NULL != nn__x)
#define yy__toml_valid_array(nn__x) (NULL != nn__x)
#define yy__path_mkdir yk__mkdir
#define yy__path_exists yk__exists
#define yy__path_readable yk__readable
#define yy__path_executable yk__executable
#define yy__array_del_str_array yk__delsdsarray
#define yy__array_dup yk__sdsarraydup
#define yy__c_CStr char*
#define yy__c_system system
#define yy__strings_valid_cstr(nn__s) (NULL != nn__s)
#define yy__os_Arguments struct yk__arguments*
#define yy__os_get_args yk__get_args
#define yy__os_ProcessResult struct yk__process_result*
struct yt_tuple_fn_in_any_ptr_out_any_ptr;
typedef int32_t (*yt_fn_in_any_ptr_out_int)(void*);
typedef void (*yt_fn_in_any_ptr_out)(void*);
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
int32_t yy__mutex_unlock(yy__mutex_Mutex*);
int32_t yy__condition_init(yy__condition_Condition*);
void yy__condition_destroy(yy__condition_Condition*);
int32_t yy__condition_signal(yy__condition_Condition*);
int32_t yy__condition_broadcast(yy__condition_Condition*);
int32_t yy__condition_wait(yy__condition_Condition*, yy__mutex_Mutex*);
int32_t yy__thread_create_with_data(yy__thread_Thread*, yt_fn_in_any_ptr_out_int, void*);
void yy__thread_exit(int32_t);
int32_t yy__thread_join(yy__thread_Thread);
struct yy__pool_ThreadPool* yy__pool_create(uint8_t, uint32_t);
int32_t yy__pool_add(struct yy__pool_ThreadPool*, yt_fn_in_any_ptr_out, void*);
int32_t yy__pool_destroy(struct yy__pool_ThreadPool*, bool);
int32_t yy__pool_internal_del_pool(struct yy__pool_ThreadPool*);
int32_t yy__pool_internal_tpool_work(void*);
yy__buffer_StringBuffer yy__buffer_new();
void yy__buffer_append(yy__buffer_StringBuffer, struct yk__bstr);
yk__sds yy__buffer_to_str(yy__buffer_StringBuffer);
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
bool yy__building_is_arm64_cpu();
yk__sds yy__building_get_alt_compiler(struct yy__configuration_Config*);
yk__sds* yy__building_create_args(struct yy__configuration_Config*, yk__sds, yk__sds, yk__sds, yk__sds*);
void yy__building_print_target_eq(yk__sds, bool);
int32_t yy__building_build_target(struct yy__configuration_Config*, yk__sds, yk__sds, yk__sds, yk__sds*, bool);
bool yy__building_print_error(yk__sds, int32_t);
int32_t yy__building_build(struct yy__configuration_Config*, yk__sds);
int32_t yy__building_build_simple(struct yy__configuration_Config*, yk__sds, bool);
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
struct yy__configuration_Config* yy__configuration_load_runtime_features(struct yy__configuration_Config*, yk__sds, bool);
struct yy__configuration_Config* yy__configuration_load_config();
struct yy__configuration_Config* yy__configuration_create_adhoc_config(yk__sds, yk__sds, bool, bool, bool, yk__sds, yk__sds, bool, bool);
void yy__configuration_del_config(struct yy__configuration_Config*);
yy__argparse_ArgParseWrapper yy__argparse_new_ex(yy__argparse_Option*, yk__sds*, int32_t);
yy__argparse_ArgParseWrapper yy__argparse_new(yy__argparse_Option*, yk__sds*);
void yy__argparse_del_argparse(yy__argparse_ArgParseWrapper);
yy__argparse_ArgParseRemainder yy__argparse_parse(yy__argparse_ArgParse, yk__sds*);
void yy__argparse_usage(yy__argparse_ArgParse);
void yy__argparse_del_remainder(yy__argparse_ArgParseRemainder);
yy__argparse_Option yy__argparse_opt_boolean(yk__sds, yk__sds, int32_t*, yk__sds);
yy__argparse_Option yy__argparse_opt_string(yk__sds, yk__sds, yy__c_CStr*, yk__sds);
yy__argparse_Option yy__argparse_opt_end();
void yy__console_set_color(int32_t);
void yy__console_color_print(int32_t, struct yk__bstr);
void yy__console_red(struct yk__bstr);
void yy__console_green(struct yk__bstr);
void yy__console_yellow(struct yk__bstr);
void yy__console_cyan(struct yk__bstr);
yk__sds yy__io_readfile(yk__sds);
bool yy__io_writefile(yk__sds, yk__sds);
yy__toml_Table yy__toml_from_str(yk__sds);
yy__toml_Table yy__toml_get_table(yy__toml_Table, yk__sds);
yy__toml_TomlArray yy__toml_get_array(yy__toml_Table, yk__sds);
int32_t yy__toml_array_len(yy__toml_TomlArray);
yk__sds yy__toml_get_string(yy__toml_Table, yk__sds);
bool yy__toml_get_bool_default(yy__toml_Table, yk__sds, bool);
yk__sds yy__toml_string_at(yy__toml_TomlArray, int32_t);
yk__sds* yy__toml_get_string_array(yy__toml_Table, yk__sds);
void yy__toml_del_table(yy__toml_Table);
bool yy__path_forward_slash();
bool yy__path_end_with_slash(yk__sds);
yk__sds yy__path_join(yk__sds, yk__sds);
yk__sds yy__path_basename(yk__sds);
yk__sds yy__path_dirname(yk__sds);
yk__sds yy__path_remove_extension(yk__sds);
yk__sds yy__array_join(yk__sds*, yk__sds);
yk__sds* yy__array_extend(yk__sds*, yk__sds*);
int32_t yy__strings_get_cstr(yy__c_CStr, int32_t);
int32_t yy__strings_get(yk__sds, int32_t);
bool yy__strings_contains(yk__sds, yk__sds);
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
int32_t yy__build_from_config(struct yy__configuration_Config*, bool, bool);
int32_t yy__perform_build();
int32_t yy__perform_mini_build(yk__sds, bool, bool, bool, yk__sds, yk__sds, bool, bool, bool, bool);
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
    struct yt_tuple_fn_in_any_ptr_out_any_ptr* yy__pool_queue;
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
    yk__sds yy__configuration_web_assets;
    bool yy__configuration_wasm4;
    bool yy__configuration_disable_parallel_build;
};
struct yy__configuration_Config {
    yk__sds yy__configuration_runtime_path;
    yk__sds yy__configuration_compiler_path;
    yk__sds yy__configuration_libs_path;
    yk__sds yy__configuration_zig_compiler_path;
    yk__sds yy__configuration_emcc_compiler_path;
    yk__sds yy__configuration_gcc_compiler_path;
    yk__sds yy__configuration_clang_compiler_path;
    int32_t yy__configuration_alt_compiler;
    bool yy__configuration_use_alt_compiler;
    yk__sds yy__configuration_emrun_path;
    yk__sds yy__configuration_w4_path;
    struct yy__configuration_CCode* yy__configuration_c_code;
    struct yy__configuration_Project* yy__configuration_project;
    struct yy__configuration_Compilation* yy__configuration_compilation;
    yk__sds* yy__configuration_errors;
};
struct yt_tuple_fn_in_any_ptr_out_any_ptr { yt_fn_in_any_ptr_out e1; void* e2; };
// --functions-- 
struct yy__raylib_support_CObject* yy__raylib_support_fill_arguments(yk__sds yy__raylib_support_src_path, struct yy__raylib_support_CObject* yy__raylib_support_c, bool yy__raylib_support_dll) 
{
    yk__sds* yy__raylib_support_args = NULL;
    if (yy__raylib_support_dll)
    {
        yk__sds* t__0 = NULL;
        yk__arrsetcap(t__0, 5);
        yk__arrput(t__0, yk__sdsnewlen("-std=gnu99", 10));
        yk__arrput(t__0, yk__sdsnewlen("-DPLATFORM_DESKTOP", 18));
        yk__arrput(t__0, yk__sdsnewlen("-DGL_SILENCE_DEPRECATION=199309L", 32));
        yk__arrput(t__0, yk__sdsnewlen("-fno-sanitize=undefined", 23));
        yk__arrput(t__0, yk__sdsnewlen("-Oz", 3));
        yy__raylib_support_args = t__0;
    }
    else
    {
        yk__sds* t__1 = NULL;
        yk__arrsetcap(t__1, 5);
        yk__arrput(t__1, yk__sdsnewlen("-std=gnu99", 10));
        yk__arrput(t__1, yk__sdsnewlen("-DPLATFORM_DESKTOP", 18));
        yk__arrput(t__1, yk__sdsnewlen("-DGL_SILENCE_DEPRECATION=199309L", 32));
        yk__arrput(t__1, yk__sdsnewlen("-fno-sanitize=undefined", 23));
        yk__arrput(t__1, yk__sdsnewlen("-O1", 3));
        yy__raylib_support_args = t__1;
    }
    if (yy__raylib_support_dll)
    {
        yk__arrput(yy__raylib_support_args, yk__sdsnewlen("-DYK__CR_DLL", 12));
    }
    yk__sds t__2 = yk__concat_lit_sds("-I", 2, yy__raylib_support_src_path);
    yk__arrput(yy__raylib_support_args, yk__sdsdup(t__2));
    yk__sds t__3 = yy__path_join(yk__sdsdup(yy__raylib_support_src_path), yk__sdsnewlen("external", 8));
    yk__sds yy__raylib_support_external = yk__sdsdup(t__3);
    yk__sds t__4 = yy__path_join(yk__sdsdup(yy__raylib_support_external), yk__sdsnewlen("glfw", 4));
    yk__sds yy__raylib_support_glfw = yk__sdsdup(t__4);
    yk__sds t__5 = yy__path_join(yk__sdsdup(yy__raylib_support_glfw), yk__sdsnewlen("include", 7));
    yk__sds t__6 = yk__concat_lit_sds("-I", 2, t__5);
    yk__arrput(yy__raylib_support_args, yk__sdsdup(t__6));
    if (yy__os_is_windows())
    {
        yk__sds t__7 = yy__path_join(yk__sdsdup(yy__raylib_support_glfw), yk__sdsnewlen("deps", 4));
        yk__sds t__8 = yy__path_join(yk__sdsdup(t__7), yk__sdsnewlen("mingw", 5));
        yk__sds t__9 = yk__concat_lit_sds("-I", 2, t__8);
        yk__arrput(yy__raylib_support_args, yk__sdsdup(t__9));
        yk__sdsfree(t__9);
        yk__sdsfree(t__8);
        yk__sdsfree(t__7);
    }
    if (yy__os_is_macos() && (yk__cmp_sds_lit(yy__raylib_support_c->yy__raylib_support_base_name, "rglfw", 5) == 0))
    {
        yk__arrput(yy__raylib_support_args, yk__sdsnewlen("-ObjC", 5));
    }
    if ((!(yy__os_is_macos())) && !yy__raylib_support_dll)
    {
        yk__arrput(yy__raylib_support_args, yk__sdsnewlen("-flto=full", 10));
    }
    yk__arrput(yy__raylib_support_args, yk__sdsdup(yy__raylib_support_c->yy__raylib_support_c_file));
    yk__arrput(yy__raylib_support_args, yk__sdsnewlen("-o", 2));
    yk__arrput(yy__raylib_support_args, yk__sdsdup(yy__raylib_support_c->yy__raylib_support_o_file));
    yy__raylib_support_c->yy__raylib_support_args = yy__raylib_support_args;
    struct yy__raylib_support_CObject* t__10 = yy__raylib_support_c;
    yk__sdsfree(t__6);
    yk__sdsfree(t__5);
    yk__sdsfree(yy__raylib_support_glfw);
    yk__sdsfree(t__4);
    yk__sdsfree(yy__raylib_support_external);
    yk__sdsfree(t__3);
    yk__sdsfree(t__2);
    yk__sdsfree(yy__raylib_support_src_path);
    return t__10;
}
struct yy__raylib_support_CObject* yy__raylib_support_fill_web_arguments(yk__sds yy__raylib_support_src_path, struct yy__raylib_support_CObject* yy__raylib_support_c) 
{
    yk__sds* t__11 = NULL;
    yk__arrsetcap(t__11, 4);
    yk__arrput(t__11, yk__sdsnewlen("-std=gnu99", 10));
    yk__arrput(t__11, yk__sdsnewlen("-DPLATFORM_WEB", 14));
    yk__arrput(t__11, yk__sdsnewlen("-DGRAPHICS_API_OPENGL_ES2", 25));
    yk__arrput(t__11, yk__sdsnewlen("-Oz", 3));
    yk__sds* yy__raylib_support_args = t__11;
    yk__arrput(yy__raylib_support_args, yk__sdsdup(yy__raylib_support_c->yy__raylib_support_c_file));
    yk__arrput(yy__raylib_support_args, yk__sdsnewlen("-o", 2));
    yk__arrput(yy__raylib_support_args, yk__sdsdup(yy__raylib_support_c->yy__raylib_support_o_file));
    yy__raylib_support_c->yy__raylib_support_args = yy__raylib_support_args;
    struct yy__raylib_support_CObject* t__12 = yy__raylib_support_c;
    yk__sdsfree(yy__raylib_support_src_path);
    return t__12;
}
struct yy__raylib_support_CObject* yy__raylib_support_co(yk__sds yy__raylib_support_filename, yk__sds yy__raylib_support_src_path, yk__sds yy__raylib_support_target_path, bool yy__raylib_support_web, bool yy__raylib_support_dll) 
{
    struct yy__raylib_support_CObject* yy__raylib_support_obj = calloc(1, sizeof(struct yy__raylib_support_CObject));
    yk__sds t__13 = yk__concat_sds_lit(yy__raylib_support_filename, ".c", 2);
    yk__sds t__14 = yy__path_join(yk__sdsdup(yy__raylib_support_src_path), yk__sdsdup(t__13));
    yy__raylib_support_obj->yy__raylib_support_c_file = yk__sdsdup(t__14);
    if (yy__raylib_support_web)
    {
        yk__sds t__15 = yk__concat_lit_sds("web-", 4, yy__raylib_support_filename);
        yy__raylib_support_obj->yy__raylib_support_base_name = yk__sdsdup(t__15);
        yk__sds t__16 = yk__concat_sds_lit(yy__raylib_support_obj->yy__raylib_support_base_name, ".o", 2);
        yk__sds t__17 = yy__path_join(yk__sdsdup(yy__raylib_support_target_path), yk__sdsdup(t__16));
        yy__raylib_support_obj->yy__raylib_support_o_file = yk__sdsdup(t__17);
        yy__raylib_support_obj = yy__raylib_support_fill_web_arguments(yk__sdsdup(yy__raylib_support_src_path), yy__raylib_support_obj);
        yk__sdsfree(t__17);
        yk__sdsfree(t__16);
        yk__sdsfree(t__15);
    }
    else
    {
        yk__sds t__18 = yk__concat_lit_sds("native-", 7, yy__raylib_support_filename);
        yy__raylib_support_obj->yy__raylib_support_base_name = yk__sdsdup(t__18);
        yk__sds t__19 = yk__concat_sds_lit(yy__raylib_support_filename, ".o", 2);
        yk__sds t__20 = yy__path_join(yk__sdsdup(yy__raylib_support_target_path), yk__sdsdup(t__19));
        yy__raylib_support_obj->yy__raylib_support_o_file = yk__sdsdup(t__20);
        yy__raylib_support_obj = yy__raylib_support_fill_arguments(yk__sdsdup(yy__raylib_support_src_path), yy__raylib_support_obj, yy__raylib_support_dll);
        yk__sdsfree(t__20);
        yk__sdsfree(t__19);
        yk__sdsfree(t__18);
    }
    struct yy__raylib_support_CObject* t__21 = yy__raylib_support_obj;
    yk__sdsfree(t__14);
    yk__sdsfree(t__13);
    yk__sdsfree(yy__raylib_support_target_path);
    yk__sdsfree(yy__raylib_support_src_path);
    yk__sdsfree(yy__raylib_support_filename);
    return t__21;
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
    if (yk__arrlen(yy__raylib_support_x) == INT32_C(0))
    {
        yk__arrfree(yy__raylib_support_x);
        return;
    }
    int32_t yy__raylib_support_pos = INT32_C(0);
    int32_t yy__raylib_support_length = yk__arrlen(yy__raylib_support_x);
    while (true)
    {
        if (!(yy__raylib_support_pos < yy__raylib_support_length))
        {
            break;
        }
        yy__raylib_support_del_c_object(yy__raylib_support_x[yy__raylib_support_pos]);
        yy__raylib_support_pos = (yy__raylib_support_pos + INT32_C(1));
    }
    yk__arrfree(yy__raylib_support_x);
    return;
}
struct yy__raylib_support_CObject** yy__raylib_support_get_objects(yk__sds yy__raylib_support_raylib_src_path, yk__sds yy__raylib_support_gui_path, yk__sds yy__raylib_support_extra_path, yk__sds yy__raylib_support_build_path, bool yy__raylib_support_web, bool yy__raylib_support_dll) 
{
    struct yy__raylib_support_CObject** yy__raylib_support_objects = NULL;
    if (!yy__raylib_support_web)
    {
        yk__arrput(yy__raylib_support_objects, yy__raylib_support_co(yk__sdsnewlen("rglfw", 5), yk__sdsdup(yy__raylib_support_raylib_src_path), yk__sdsdup(yy__raylib_support_build_path), yy__raylib_support_web, yy__raylib_support_dll));
    }
    yk__arrput(yy__raylib_support_objects, yy__raylib_support_co(yk__sdsnewlen("raudio", 6), yk__sdsdup(yy__raylib_support_raylib_src_path), yk__sdsdup(yy__raylib_support_build_path), yy__raylib_support_web, yy__raylib_support_dll));
    yk__arrput(yy__raylib_support_objects, yy__raylib_support_co(yk__sdsnewlen("rcore", 5), yk__sdsdup(yy__raylib_support_raylib_src_path), yk__sdsdup(yy__raylib_support_build_path), yy__raylib_support_web, yy__raylib_support_dll));
    yk__arrput(yy__raylib_support_objects, yy__raylib_support_co(yk__sdsnewlen("rmodels", 7), yk__sdsdup(yy__raylib_support_raylib_src_path), yk__sdsdup(yy__raylib_support_build_path), yy__raylib_support_web, yy__raylib_support_dll));
    yk__arrput(yy__raylib_support_objects, yy__raylib_support_co(yk__sdsnewlen("rshapes", 7), yk__sdsdup(yy__raylib_support_raylib_src_path), yk__sdsdup(yy__raylib_support_build_path), yy__raylib_support_web, yy__raylib_support_dll));
    yk__arrput(yy__raylib_support_objects, yy__raylib_support_co(yk__sdsnewlen("rtext", 5), yk__sdsdup(yy__raylib_support_raylib_src_path), yk__sdsdup(yy__raylib_support_build_path), yy__raylib_support_web, yy__raylib_support_dll));
    yk__arrput(yy__raylib_support_objects, yy__raylib_support_co(yk__sdsnewlen("rtextures", 9), yk__sdsdup(yy__raylib_support_raylib_src_path), yk__sdsdup(yy__raylib_support_build_path), yy__raylib_support_web, yy__raylib_support_dll));
    yk__arrput(yy__raylib_support_objects, yy__raylib_support_co(yk__sdsnewlen("utils", 5), yk__sdsdup(yy__raylib_support_raylib_src_path), yk__sdsdup(yy__raylib_support_build_path), yy__raylib_support_web, yy__raylib_support_dll));
    struct yy__raylib_support_CObject* yy__raylib_support_extra = yy__raylib_support_co(yk__sdsnewlen("rayextras", 9), yk__sdsdup(yy__raylib_support_extra_path), yk__sdsdup(yy__raylib_support_build_path), yy__raylib_support_web, yy__raylib_support_dll);
    yk__sds t__22 = yk__concat_lit_sds("-I", 2, yy__raylib_support_raylib_src_path);
    yk__arrput(yy__raylib_support_extra->yy__raylib_support_args, yk__sdsdup(t__22));
    yk__sds t__23 = yk__concat_lit_sds("-I", 2, yy__raylib_support_gui_path);
    yk__arrput(yy__raylib_support_extra->yy__raylib_support_args, yk__sdsdup(t__23));
    yk__arrput(yy__raylib_support_objects, yy__raylib_support_extra);
    struct yy__raylib_support_CObject** t__24 = yy__raylib_support_objects;
    yk__sdsfree(t__23);
    yk__sdsfree(t__22);
    yk__sdsfree(yy__raylib_support_build_path);
    yk__sdsfree(yy__raylib_support_extra_path);
    yk__sdsfree(yy__raylib_support_gui_path);
    yk__sdsfree(yy__raylib_support_raylib_src_path);
    return t__24;
}
yk__sds* yy__raylib_support_get_external_libs() 
{
    yk__sds* yy__raylib_support_external_libs = NULL;
    if (yy__os_is_windows())
    {
        yk__sds* t__25 = NULL;
        yk__arrsetcap(t__25, 3);
        yk__arrput(t__25, yk__sdsnewlen("-lwinmm", 7));
        yk__arrput(t__25, yk__sdsnewlen("-lgdi32", 7));
        yk__arrput(t__25, yk__sdsnewlen("-lopengl32", 10));
        yy__raylib_support_external_libs = t__25;
    }
    else
    {
        if (yy__os_is_macos())
        {
            yk__sds* t__26 = NULL;
            yk__arrsetcap(t__26, 12);
            yk__arrput(t__26, yk__sdsnewlen("-framework", 10));
            yk__arrput(t__26, yk__sdsnewlen("Foundation", 10));
            yk__arrput(t__26, yk__sdsnewlen("-framework", 10));
            yk__arrput(t__26, yk__sdsnewlen("OpenGL", 6));
            yk__arrput(t__26, yk__sdsnewlen("-framework", 10));
            yk__arrput(t__26, yk__sdsnewlen("OpenAL", 6));
            yk__arrput(t__26, yk__sdsnewlen("-framework", 10));
            yk__arrput(t__26, yk__sdsnewlen("IOKit", 5));
            yk__arrput(t__26, yk__sdsnewlen("-framework", 10));
            yk__arrput(t__26, yk__sdsnewlen("CoreVideo", 9));
            yk__arrput(t__26, yk__sdsnewlen("-framework", 10));
            yk__arrput(t__26, yk__sdsnewlen("Cocoa", 5));
            yy__raylib_support_external_libs = t__26;
        }
        else
        {
            yk__sds* t__27 = NULL;
            yk__arrsetcap(t__27, 5);
            yk__arrput(t__27, yk__sdsnewlen("-lGL", 4));
            yk__arrput(t__27, yk__sdsnewlen("-lrt", 4));
            yk__arrput(t__27, yk__sdsnewlen("-ldl", 4));
            yk__arrput(t__27, yk__sdsnewlen("-lm", 3));
            yk__arrput(t__27, yk__sdsnewlen("-lX11", 5));
            yy__raylib_support_external_libs = t__27;
        }
    }
    yk__sds* t__28 = yy__raylib_support_external_libs;
    return t__28;
}
yk__sds* yy__raylib_support_get_web_args() 
{
    yk__sds* t__29 = NULL;
    yk__arrsetcap(t__29, 5);
    yk__arrput(t__29, yk__sdsnewlen("-s", 2));
    yk__arrput(t__29, yk__sdsnewlen("USE_GLFW=3", 10));
    yk__arrput(t__29, yk__sdsnewlen("-s", 2));
    yk__arrput(t__29, yk__sdsnewlen("ASYNCIFY", 8));
    yk__arrput(t__29, yk__sdsnewlen("-DPLATFORM_WEB", 14));
    yk__sds* yy__raylib_support_web_args = t__29;
    yk__sds* t__30 = yy__raylib_support_web_args;
    return t__30;
}
bool yy__raylib_support_produce_object(struct yy__raylib_support_CObject* yy__raylib_support_c, struct yy__configuration_Config* yy__raylib_support_conf, bool yy__raylib_support_print_info) 
{
    if (yy__raylib_support_print_info)
    {
        yy__console_cyan(yk__bstr_s("raylib::", 8));
        yy__console_yellow(yk__bstr_h(yy__raylib_support_c->yy__raylib_support_base_name));
        yy__console_cyan(yk__bstr_s(" := ", 4));
    }
    if (yy__path_readable(yk__sdsdup(yy__raylib_support_c->yy__raylib_support_o_file)))
    {
        if (yy__raylib_support_print_info)
        {
            yy__console_green(yk__bstr_s("ok.\n", 4));
        }
        return true;
    }
    yk__sds* yy__raylib_support_cmd = NULL;
    if (yy__raylib_support_conf->yy__configuration_compilation->yy__configuration_web)
    {
        yk__sds* t__31 = NULL;
        yk__arrsetcap(t__31, 3);
        yk__arrput(t__31, yk__sdsdup(yy__raylib_support_conf->yy__configuration_emcc_compiler_path));
        yk__arrput(t__31, yk__sdsnewlen("-c", 2));
        yk__arrput(t__31, yk__sdsnewlen("-Oz", 3));
        yy__raylib_support_cmd = t__31;
    }
    else
    {
        yk__sds* t__32 = NULL;
        yk__arrsetcap(t__32, 4);
        yk__arrput(t__32, yk__sdsdup(yy__raylib_support_conf->yy__configuration_zig_compiler_path));
        yk__arrput(t__32, yk__sdsnewlen("cc", 2));
        yk__arrput(t__32, yk__sdsnewlen("-c", 2));
        yk__arrput(t__32, yk__sdsnewlen("-Oz", 3));
        yy__raylib_support_cmd = t__32;
    }
    yy__raylib_support_cmd = yy__array_extend(yy__raylib_support_cmd, yy__raylib_support_c->yy__raylib_support_args);
    yy__os_ProcessResult yy__raylib_support_pr = yy__os_run(yy__raylib_support_cmd);
    if (yy__raylib_support_pr->ok)
    {
        if (yy__raylib_support_print_info)
        {
            yy__console_green(yk__bstr_s("ok.\n", 4));
        }
        yy__os_del_process_result(yy__raylib_support_pr);
        yy__array_del_str_array(yy__raylib_support_cmd);
        return true;
    }
    if (yy__raylib_support_print_info)
    {
        yy__console_red(yk__bstr_s("failed.\n", 8));
        yy__console_cyan(yk__bstr_s("--c compiler output---\n", 23));
        yy__console_red(yk__bstr_s("command := ", 11));
        yk__sds t__33 = yy__array_join(yy__raylib_support_cmd, yk__sdsnewlen(" ", 1));
        yk__sds t__34 = yk__concat_sds_lit(t__33, "\n", 1);
        yy__console_cyan(yk__bstr_h(t__34));
        yy__console_red(yk__bstr_h(yy__raylib_support_pr->output));
        yy__console_cyan(yk__bstr_s("--end c compiler output---\n", 27));
        yk__sdsfree(t__34);
        yk__sdsfree(t__33);
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
    while (true)
    {
        if (!(yy__raylib_support_pos < yy__raylib_support_object_count))
        {
            break;
        }
        struct yy__raylib_support_CObject* yy__raylib_support_object = yy__raylib_support_objects[yy__raylib_support_pos];
        yy__raylib_support_produce_object(yy__raylib_support_object, yy__raylib_support_conf, true);
        yy__raylib_support_pos += INT32_C(1);
    }
    return;
}
void yy__raylib_support_build_objects(struct yy__raylib_support_CObject** yy__raylib_support_objects, struct yy__configuration_Config* yy__raylib_support_conf) 
{
    yk__printlnstr("building raylib ...");
    if (yy__raylib_support_conf->yy__configuration_compilation->yy__configuration_disable_parallel_build)
    {
        yy__raylib_support_build_objects_sequential(yy__raylib_support_objects, yy__raylib_support_conf);
        return;
    }
    int32_t yy__raylib_support_object_count = yk__arrlen(yy__raylib_support_objects);
    yy__cpu_Cpu yy__raylib_support_cpu_data = yy__cpu_info();
    uint8_t yy__raylib_support_threads = ((uint8_t)yy__raylib_support_cpu_data.n_processors);
    yy__raylib_support_threads = ((yy__raylib_support_threads > yy__pool_MAX_THREAD_SIZE) ? yy__pool_MAX_THREAD_SIZE : yy__raylib_support_threads);
    struct yy__pool_ThreadPool* yy__raylib_support_tpool = yy__pool_create(yy__raylib_support_threads, ((uint32_t)(yy__raylib_support_object_count + INT32_C(2))));
    if (yy__raylib_support_tpool == NULL)
    {
        yy__raylib_support_build_objects_sequential(yy__raylib_support_objects, yy__raylib_support_conf);
        return;
    }
    struct yy__raylib_support_BuildData** yy__raylib_support_to_pass = NULL;
    int32_t yy__raylib_support_pos = INT32_C(0);
    while (true)
    {
        if (!(yy__raylib_support_pos < yy__raylib_support_object_count))
        {
            break;
        }
        struct yy__raylib_support_CObject* yy__raylib_support_object = yy__raylib_support_objects[yy__raylib_support_pos];
        struct yy__raylib_support_BuildData* yy__raylib_support_data = calloc(1, sizeof(struct yy__raylib_support_BuildData));
        yy__raylib_support_data->yy__raylib_support_object_data = yy__raylib_support_object;
        yy__raylib_support_data->yy__raylib_support_config = yy__raylib_support_conf;
        yk__arrput(yy__raylib_support_to_pass, yy__raylib_support_data);
        yy__pool_add(yy__raylib_support_tpool, yy__raylib_support_build_object, yy__raylib_support_data);
        yy__raylib_support_pos += INT32_C(1);
    }
    yy__pool_destroy(yy__raylib_support_tpool, true);
    yy__raylib_support_pos = INT32_C(0);
    while (true)
    {
        if (!(yy__raylib_support_pos < yy__raylib_support_object_count))
        {
            break;
        }
        free(yy__raylib_support_to_pass[yy__raylib_support_pos]);
        yy__raylib_support_pos += INT32_C(1);
    }
    yk__arrfree(yy__raylib_support_to_pass);
    return;
}
yk__sds* yy__raylib_support_get_raylib_args(struct yy__configuration_Config* yy__raylib_support_conf, yk__sds yy__raylib_support_build_path) 
{
    yk__sds* yy__raylib_support_arguments = NULL;
    yk__sds yy__raylib_support_runtime_path = yk__sdsdup(yy__raylib_support_conf->yy__configuration_runtime_path);
    yy__path_mkdir(yk__sdsdup(yy__raylib_support_build_path));
    yk__sds t__35 = yy__path_join(yk__sdsdup(yy__raylib_support_runtime_path), yk__sdsnewlen("raylib", 6));
    yk__sds t__36 = yy__path_join(yk__sdsdup(t__35), yk__sdsnewlen("src", 3));
    yk__sds yy__raylib_support_raylib_path = yk__sdsdup(t__36);
    yk__sds t__37 = yy__path_join(yk__sdsdup(yy__raylib_support_runtime_path), yk__sdsnewlen("raygui", 6));
    yk__sds t__38 = yy__path_join(yk__sdsdup(t__37), yk__sdsnewlen("src", 3));
    yk__sds yy__raylib_support_raygui_path = yk__sdsdup(t__38);
    yk__sds t__39 = yy__path_join(yk__sdsdup(yy__raylib_support_runtime_path), yk__sdsnewlen("raylib_additional", 17));
    yk__sds yy__raylib_support_rayextra_path = yk__sdsdup(t__39);
    struct yy__raylib_support_CObject** yy__raylib_support_objects = yy__raylib_support_get_objects(yk__sdsdup(yy__raylib_support_raylib_path), yk__sdsdup(yy__raylib_support_raygui_path), yk__sdsdup(yy__raylib_support_rayextra_path), yk__sdsdup(yy__raylib_support_build_path), yy__raylib_support_conf->yy__configuration_compilation->yy__configuration_web, yy__raylib_support_conf->yy__configuration_compilation->yy__configuration_raylib_hot_reloading_dll);
    yk__sds* yy__raylib_support_o_files = NULL;
    int32_t yy__raylib_support_object_count = yk__arrlen(yy__raylib_support_objects);
    yy__raylib_support_build_objects(yy__raylib_support_objects, yy__raylib_support_conf);
    int32_t yy__raylib_support_pos = INT32_C(0);
    while (true)
    {
        if (!(yy__raylib_support_pos < yy__raylib_support_object_count))
        {
            break;
        }
        struct yy__raylib_support_CObject* yy__raylib_support_object = yy__raylib_support_objects[yy__raylib_support_pos];
        yk__arrput(yy__raylib_support_o_files, yk__sdsdup(yy__raylib_support_object->yy__raylib_support_o_file));
        yy__raylib_support_pos += INT32_C(1);
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
            yk__arrput(yy__raylib_support_arguments, yk__sdsnewlen("-DYK__WINDOWS_HIDE_CONSOLE", 26));
        }
    }
    yk__sds t__40 = yk__concat_lit_sds("-I", 2, yy__raylib_support_raylib_path);
    yk__arrput(yy__raylib_support_arguments, yk__sdsdup(t__40));
    yk__sds t__41 = yk__concat_lit_sds("-I", 2, yy__raylib_support_raygui_path);
    yk__arrput(yy__raylib_support_arguments, yk__sdsdup(t__41));
    yk__sds t__42 = yk__concat_lit_sds("-I", 2, yy__raylib_support_rayextra_path);
    yk__arrput(yy__raylib_support_arguments, yk__sdsdup(t__42));
    yk__sds* t__43 = yy__raylib_support_arguments;
    yy__raylib_support_del_objects(yy__raylib_support_objects);
    yy__array_del_str_array(yy__raylib_support_o_files);
    yk__sdsfree(t__42);
    yk__sdsfree(t__41);
    yk__sdsfree(t__40);
    yk__sdsfree(yy__raylib_support_rayextra_path);
    yk__sdsfree(t__39);
    yk__sdsfree(yy__raylib_support_raygui_path);
    yk__sdsfree(t__38);
    yk__sdsfree(t__37);
    yk__sdsfree(yy__raylib_support_raylib_path);
    yk__sdsfree(t__36);
    yk__sdsfree(t__35);
    yk__sdsfree(yy__raylib_support_runtime_path);
    yk__sdsfree(yy__raylib_support_build_path);
    return t__43;
}
yy__cpu_Cpu yy__cpu_info() { return yk__get_cpu_count(); }
int32_t yy__mutex_init(yy__mutex_Mutex* nn__mtx, int32_t nn__type) { return mtx_init(nn__mtx, nn__type); }
void yy__mutex_destroy(yy__mutex_Mutex* nn__mtx) { mtx_destroy(nn__mtx); }
int32_t yy__mutex_lock(yy__mutex_Mutex* nn__mtx) { return mtx_lock(nn__mtx); }
int32_t yy__mutex_unlock(yy__mutex_Mutex* nn__mtx) { return mtx_unlock(nn__mtx); }
int32_t yy__condition_init(yy__condition_Condition* nn__cnd) { return cnd_init(nn__cnd); }
void yy__condition_destroy(yy__condition_Condition* nn__cnd) { cnd_destroy(nn__cnd); }
int32_t yy__condition_signal(yy__condition_Condition* nn__cnd) { return cnd_signal(nn__cnd); }
int32_t yy__condition_broadcast(yy__condition_Condition* nn__cnd) { return cnd_broadcast(nn__cnd); }
int32_t yy__condition_wait(yy__condition_Condition* nn__cnd, yy__mutex_Mutex* nn__mtx) { return cnd_wait(nn__cnd, nn__mtx); }
int32_t yy__thread_create_with_data(yy__thread_Thread* nn__thr, yt_fn_in_any_ptr_out_int nn__func, void* nn__data) { return thrd_create(nn__thr, nn__func, nn__data); }
void yy__thread_exit(int32_t nn__res) { thrd_exit(nn__res); }
int32_t yy__thread_join(yy__thread_Thread nn__thr) 
{
    return thrd_join(nn__thr, NULL);
}
struct yy__pool_ThreadPool* yy__pool_create(uint8_t yy__pool_thread_count, uint32_t yy__pool_queue_size) 
{
    if ((((yy__pool_thread_count == UINT8_C(0)) || (yy__pool_queue_size == UINT32_C(0))) || (yy__pool_thread_count > yy__pool_MAX_THREAD_SIZE)) || (yy__pool_queue_size > yy__pool_MAX_QUEUE_SIZE))
    {
        struct yy__pool_ThreadPool* t__0 = NULL;
        return t__0;
    }
    struct yy__pool_ThreadPool* yy__pool_tpool = calloc(1, sizeof(struct yy__pool_ThreadPool));
    if (yy__pool_tpool == NULL)
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
    if (!yy__pool_locks_ok || !yy__pool_arrays_ok)
    {
        yy__pool_internal_del_pool(yy__pool_tpool);
        struct yy__pool_ThreadPool* t__2 = NULL;
        return t__2;
    }
    int32_t yy__pool_i = INT32_C(0);
    int32_t yy__pool_thread_count_i = ((int32_t)yy__pool_thread_count);
    while (true)
    {
        if (!(yy__pool_i < yy__pool_thread_count_i))
        {
            break;
        }
        bool yy__pool_ok = (yy__thread_create_with_data((&(yy__pool_tpool->yy__pool_threads[yy__pool_i])), yy__pool_internal_tpool_work, yy__pool_tpool) == yy__thread_SUCCESS);
        if (!yy__pool_ok)
        {
            yy__pool_destroy(yy__pool_tpool, true);
            struct yy__pool_ThreadPool* t__3 = NULL;
            return t__3;
        }
        yy__pool_i += INT32_C(1);
        yy__pool_tpool->yy__pool_thread_count += INT32_C(1);
        yy__pool_tpool->yy__pool_started += INT32_C(1);
    }
    struct yy__pool_ThreadPool* t__4 = yy__pool_tpool;
    return t__4;
}
int32_t yy__pool_add(struct yy__pool_ThreadPool* yy__pool_tpool, yt_fn_in_any_ptr_out yy__pool_func, void* yy__pool_arg) 
{
    int32_t yy__pool_err = yy__pool_SUCCESS;
    int32_t yy__pool_next = INT32_C(0);
    if (yy__pool_tpool == NULL)
    {
        int32_t const  t__5 = yy__pool_ERROR_INVALID;
        return t__5;
    }
    if (yy__mutex_lock((&(yy__pool_tpool->yy__pool_lock))) != yy__thread_SUCCESS)
    {
        int32_t const  t__6 = yy__pool_ERROR_LOCK_FAILURE;
        return t__6;
    }
    yy__pool_next = (((yy__pool_tpool->yy__pool_tail + INT32_C(1))) % yy__pool_tpool->yy__pool_queue_size);
    while (true)
    {
        if (yy__pool_tpool->yy__pool_count == yy__pool_tpool->yy__pool_queue_size)
        {
            yy__pool_err = yy__pool_ERROR_QUEUE_FULL;
            break;
        }
        if (yy__pool_tpool->yy__pool_shutdown != yy__pool_NO_SHUTDOWN)
        {
            yy__pool_err = yy__pool_ERROR_SHUTDOWN;
            break;
        }
        yy__pool_tpool->yy__pool_queue[yy__pool_tpool->yy__pool_tail].e1 = yy__pool_func;
        yy__pool_tpool->yy__pool_queue[yy__pool_tpool->yy__pool_tail].e2 = yy__pool_arg;
        yy__pool_tpool->yy__pool_tail = yy__pool_next;
        yy__pool_tpool->yy__pool_count += INT32_C(1);
        if (yy__condition_signal((&(yy__pool_tpool->yy__pool_notify))) != yy__thread_SUCCESS)
        {
            yy__pool_err = yy__pool_ERROR_LOCK_FAILURE;
        }
        break;
    }
    if (yy__mutex_unlock((&(yy__pool_tpool->yy__pool_lock))) != yy__thread_SUCCESS)
    {
        yy__pool_err = yy__pool_ERROR_LOCK_FAILURE;
    }
    int32_t t__7 = yy__pool_err;
    return t__7;
}
int32_t yy__pool_destroy(struct yy__pool_ThreadPool* yy__pool_tpool, bool yy__pool_graceful) 
{
    if (yy__pool_tpool == NULL)
    {
        int32_t const  t__8 = yy__pool_ERROR_INVALID;
        return t__8;
    }
    if (yy__mutex_lock((&(yy__pool_tpool->yy__pool_lock))) != yy__thread_SUCCESS)
    {
        int32_t const  t__9 = yy__pool_ERROR_LOCK_FAILURE;
        return t__9;
    }
    int32_t yy__pool_err = yy__pool_SUCCESS;
    while (true)
    {
        if (yy__pool_tpool->yy__pool_shutdown != yy__pool_NO_SHUTDOWN)
        {
            yy__pool_err = yy__pool_ERROR_SHUTDOWN;
            break;
        }
        yy__pool_tpool->yy__pool_shutdown = (yy__pool_graceful ? yy__pool_GRACEFUL_SHUTDOWN : yy__pool_IMMEDIATE_SHUTDOWN);
        if ((yy__condition_broadcast((&(yy__pool_tpool->yy__pool_notify))) != yy__thread_SUCCESS) || (yy__mutex_unlock((&(yy__pool_tpool->yy__pool_lock))) != yy__thread_SUCCESS))
        {
            yy__pool_err = yy__pool_ERROR_LOCK_FAILURE;
            break;
        }
        int32_t yy__pool_i = INT32_C(0);
        while (true)
        {
            if (!(yy__pool_i < yy__pool_tpool->yy__pool_thread_count))
            {
                break;
            }
            bool yy__pool_ok = (yy__thread_join(yy__pool_tpool->yy__pool_threads[yy__pool_i]) == yy__thread_SUCCESS);
            if (!yy__pool_ok)
            {
                yy__pool_err = yy__pool_ERROR_THREAD_FAILURE;
            }
            yy__pool_i += INT32_C(1);
        }
        break;
    }
    if (yy__pool_err == yy__pool_SUCCESS)
    {
        yy__pool_internal_del_pool(yy__pool_tpool);
    }
    int32_t t__10 = yy__pool_err;
    return t__10;
}
int32_t yy__pool_internal_del_pool(struct yy__pool_ThreadPool* yy__pool_tpool) 
{
    if ((yy__pool_tpool == NULL) || (yy__pool_tpool->yy__pool_started > INT32_C(0)))
    {
        int32_t const  t__11 = yy__pool_ERROR_INVALID;
        return t__11;
    }
    if ((yy__pool_tpool->yy__pool_threads != NULL) || (yy__pool_tpool->yy__pool_queue != NULL))
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
    struct yt_tuple_fn_in_any_ptr_out_any_ptr yy__pool_task;
    while (true)
    {
        yy__mutex_lock((&(yy__pool_tpool->yy__pool_lock)));
        while (true)
        {
            if (!((((yy__pool_tpool->yy__pool_count == INT32_C(0)) && (yy__pool_tpool->yy__pool_shutdown == yy__pool_NO_SHUTDOWN)))))
            {
                break;
            }
            yy__condition_wait((&(yy__pool_tpool->yy__pool_notify)), (&(yy__pool_tpool->yy__pool_lock)));
        }
        if ((((yy__pool_tpool->yy__pool_shutdown == yy__pool_GRACEFUL_SHUTDOWN) && (yy__pool_tpool->yy__pool_count == INT32_C(0)))) || (yy__pool_tpool->yy__pool_shutdown == yy__pool_IMMEDIATE_SHUTDOWN))
        {
            break;
        }
        yy__pool_task.e1 = yy__pool_tpool->yy__pool_queue[yy__pool_tpool->yy__pool_head].e1;
        yy__pool_task.e2 = yy__pool_tpool->yy__pool_queue[yy__pool_tpool->yy__pool_head].e2;
        yy__pool_tpool->yy__pool_head = (((yy__pool_tpool->yy__pool_head + INT32_C(1))) % yy__pool_tpool->yy__pool_queue_size);
        yy__pool_tpool->yy__pool_count -= INT32_C(1);
        yy__mutex_unlock((&(yy__pool_tpool->yy__pool_lock)));
        yt_fn_in_any_ptr_out yy__pool_fnc = yy__pool_task.e1;
        yy__pool_fnc(yy__pool_task.e2);
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
void yy__buffer_append(yy__buffer_StringBuffer nn__buf, struct yk__bstr nn__v) 
{
    nn__buf[0] = yk__sdscatlen(nn__buf[0], yk__bstr_get_reference(nn__v), yk__bstr_len(nn__v));
}
yk__sds yy__buffer_to_str(yy__buffer_StringBuffer nn__buf) 
{
    return yk__sdsdup(nn__buf[0]);
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
    while (true)
    {
        if (!(yy__building_x < yy__building_length))
        {
            break;
        }
        yk__sds t__0 = yk__concat_lit_sds("#define ", 8, yy__building_c->yy__configuration_c_code->yy__configuration_runtime_feature_defines[yy__building_x]);
        yk__sds t__1 = yk__concat_sds_lit(t__0, "\n", 1);
        yy__buffer_append(yy__building_buf, yk__bstr_h(t__1));
        yy__building_x = (yy__building_x + INT32_C(1));
        yk__sdsfree(t__1);
        yk__sdsfree(t__0);
    }
    yy__building_length = yk__arrlen(yy__building_c->yy__configuration_c_code->yy__configuration_defines);
    yy__building_x = INT32_C(0);
    while (true)
    {
        if (!(yy__building_x < yy__building_length))
        {
            break;
        }
        yk__sds t__2 = yk__concat_lit_sds("#define ", 8, yy__building_c->yy__configuration_c_code->yy__configuration_defines[yy__building_x]);
        yk__sds t__3 = yk__concat_sds_lit(t__2, "\n", 1);
        yy__buffer_append(yy__building_buf, yk__bstr_h(t__3));
        yy__building_x = (yy__building_x + INT32_C(1));
        yk__sdsfree(t__3);
        yk__sdsfree(t__2);
    }
    yy__building_length = yk__arrlen(yy__building_c->yy__configuration_c_code->yy__configuration_system_includes);
    yy__building_x = INT32_C(0);
    while (true)
    {
        if (!(yy__building_x < yy__building_length))
        {
            break;
        }
        yk__sds t__4 = yk__concat_lit_sds("#include <", 10, yy__building_c->yy__configuration_c_code->yy__configuration_system_includes[yy__building_x]);
        yk__sds t__5 = yk__concat_sds_lit(t__4, ">\n", 2);
        yy__buffer_append(yy__building_buf, yk__bstr_h(t__5));
        yy__building_x = (yy__building_x + INT32_C(1));
        yk__sdsfree(t__5);
        yk__sdsfree(t__4);
    }
    if (yy__building_c->yy__configuration_compilation->yy__configuration_raylib)
    {
        yy__buffer_append(yy__building_buf, yk__bstr_s("#include \"raylib.h\"\n", 20));
        yy__buffer_append(yy__building_buf, yk__bstr_s("#include \"raygui.h\"\n", 20));
        yy__buffer_append(yy__building_buf, yk__bstr_s("#include \"raymath.h\"\n", 21));
        yy__buffer_append(yy__building_buf, yk__bstr_s("#include \"rlgl.h\"\n", 18));
        yy__buffer_append(yy__building_buf, yk__bstr_s("#include \"rayextras.h\"\n", 23));
    }
    yy__building_length = yk__arrlen(yy__building_c->yy__configuration_c_code->yy__configuration_runtime_feature_includes);
    yy__building_x = INT32_C(0);
    while (true)
    {
        if (!(yy__building_x < yy__building_length))
        {
            break;
        }
        yk__sds t__6 = yk__concat_lit_sds("#include \"", 10, yy__building_c->yy__configuration_c_code->yy__configuration_runtime_feature_includes[yy__building_x]);
        yk__sds t__7 = yk__concat_sds_lit(t__6, "\"\n", 2);
        yy__buffer_append(yy__building_buf, yk__bstr_h(t__7));
        yy__building_x = (yy__building_x + INT32_C(1));
        yk__sdsfree(t__7);
        yk__sdsfree(t__6);
    }
    yy__building_length = yk__arrlen(yy__building_c->yy__configuration_c_code->yy__configuration_includes);
    yy__building_x = INT32_C(0);
    while (true)
    {
        if (!(yy__building_x < yy__building_length))
        {
            break;
        }
        yk__sds t__8 = yk__concat_lit_sds("#include \"", 10, yy__building_c->yy__configuration_c_code->yy__configuration_includes[yy__building_x]);
        yk__sds t__9 = yk__concat_sds_lit(t__8, "\"\n", 2);
        yy__buffer_append(yy__building_buf, yk__bstr_h(t__9));
        yy__building_x = (yy__building_x + INT32_C(1));
        yk__sdsfree(t__9);
        yk__sdsfree(t__8);
    }
    yy__buffer_append(yy__building_buf, yk__bstr_h(yy__building_code));
    yy__buffer_append(yy__building_buf, yk__bstr_s("\n", 1));
    yk__sds t__10 = yy__buffer_to_str(yy__building_buf);
    yk__sds yy__building_result = yk__sdsdup(t__10);
    yk__sds t__11 = yy__building_result;
    yy__buffer_del_buf(yy__building_buf);
    yk__sdsfree(t__10);
    yk__sdsfree(yy__building_code);
    return t__11;
}
bool yy__building_is_target_macos(yk__sds yy__building_target_to_check) 
{
    bool yy__building_native = (yk__sdslen(yy__building_target_to_check) == INT32_C(0));
    if (yy__building_native)
    {
        bool t__12 = yy__os_is_macos();
        yk__sdsfree(yy__building_target_to_check);
        return t__12;
    }
    bool t__13 = yy__strings_contains(yk__sdsdup(yy__building_target_to_check), yk__sdsnewlen("macos", 5));
    yk__sdsfree(yy__building_target_to_check);
    return t__13;
}
bool yy__building_is_target_windows(yk__sds yy__building_target_to_check) 
{
    bool yy__building_native = (yk__sdslen(yy__building_target_to_check) == INT32_C(0));
    if (yy__building_native)
    {
        bool t__14 = yy__os_is_windows();
        yk__sdsfree(yy__building_target_to_check);
        return t__14;
    }
    bool t__15 = yy__strings_contains(yk__sdsdup(yy__building_target_to_check), yk__sdsnewlen("windows", 7));
    yk__sdsfree(yy__building_target_to_check);
    return t__15;
}
void yy__building_produce_obj_function(void* yy__building_arg) 
{
    struct yy__building_BObject* yy__building_data = ((struct yy__building_BObject*)yy__building_arg);
    yk__sds* yy__building_my_args = yy__array_dup(yy__building_data->yy__building_args);
    yk__sds t__16 = yy__path_basename(yk__sdsdup(yy__building_data->yy__building_c_file));
    yk__sds t__17 = yy__path_remove_extension(yk__sdsdup(t__16));
    yk__sds yy__building_object_file = yk__sdsdup(t__17);
    if (yy__building_data->yy__building_print_info)
    {
        yy__console_cyan(yk__bstr_s("runtime::", 9));
        yy__console_yellow(yk__bstr_h(yy__building_object_file));
        yy__console_cyan(yk__bstr_s(" := ", 4));
    }
    if ((!(yy__building_data->yy__building_always_build)) && yy__path_readable(yk__sdsdup(yy__building_data->yy__building_object_file_path)))
    {
        if (yy__building_data->yy__building_print_info)
        {
            yy__console_green(yk__bstr_s("ok.\n", 4));
        }
        yy__array_del_str_array(yy__building_my_args);
        yk__sdsfree(yy__building_object_file);
        yk__sdsfree(t__17);
        yk__sdsfree(t__16);
        return;
    }
    yk__arrput(yy__building_my_args, yk__sdsnewlen("-c", 2));
    yk__arrput(yy__building_my_args, yk__sdsdup(yy__building_data->yy__building_c_file));
    yk__arrput(yy__building_my_args, yk__sdsnewlen("-o", 2));
    yk__arrput(yy__building_my_args, yk__sdsdup(yy__building_data->yy__building_object_file_path));
    yy__os_ProcessResult yy__building_pr = yy__os_run(yy__building_my_args);
    if (yy__building_data->yy__building_print_info)
    {
        if (yy__building_pr->ok)
        {
            yy__console_green(yk__bstr_s("ok.\n", 4));
        }
        else
        {
            yy__console_red(yk__bstr_s("failed.\n", 8));
            yy__console_cyan(yk__bstr_s("--c compiler output---\n", 23));
            yy__console_red(yk__bstr_s("command := ", 11));
            yk__sds t__18 = yy__array_join(yy__building_my_args, yk__sdsnewlen(" ", 1));
            yk__sds t__19 = yk__concat_sds_lit(t__18, "\n", 1);
            yy__console_cyan(yk__bstr_h(t__19));
            yy__console_red(yk__bstr_h(yy__building_pr->output));
            yy__console_cyan(yk__bstr_s("--end c compiler output---\n", 27));
            yk__sdsfree(t__19);
            yk__sdsfree(t__18);
        }
    }
    yy__os_del_process_result(yy__building_pr);
    yy__array_del_str_array(yy__building_my_args);
    yk__sdsfree(yy__building_object_file);
    yk__sdsfree(t__17);
    yk__sdsfree(t__16);
    return;
}
yk__sds yy__building_core_object(yk__sds* yy__building_args, yk__sds yy__building_c_file, yk__sds yy__building_build_path, yk__sds yy__building_target, bool yy__building_always_build, struct yy__building_BObject*** yy__building_bobj_array) 
{
    yk__sds yy__building_suffix = yk__sdsnewlen("-" , 1);
    bool yy__building_native = (yk__sdslen(yy__building_target) == INT32_C(0));
    if (yy__building_native)
    {
        yy__building_suffix = yk__append_sds_lit(yy__building_suffix, "native" , 6);
    }
    else
    {
        yy__building_suffix = yk__append_sds_sds(yy__building_suffix, yy__building_target);
    }
    yk__sds t__20 = yy__path_basename(yk__sdsdup(yy__building_c_file));
    yk__sds t__21 = yy__path_remove_extension(yk__sdsdup(t__20));
    yk__sds yy__building_object_file = yk__sdsdup(t__21);
    yy__building_object_file = yk__append_sds_sds(yy__building_object_file, yy__building_suffix);
    yy__building_object_file = yk__append_sds_lit(yy__building_object_file, ".o" , 2);
    yk__sds t__22 = yy__path_join(yk__sdsdup(yy__building_build_path), yk__sdsdup(yy__building_object_file));
    yk__sds yy__building_object_file_path = yk__sdsdup(t__22);
    struct yy__building_BObject* yy__building_bobj = calloc(1, sizeof(struct yy__building_BObject));
    yy__building_bobj->yy__building_args = yy__building_args;
    yy__building_bobj->yy__building_c_file = yk__sdsdup(yy__building_c_file);
    yy__building_bobj->yy__building_always_build = yy__building_always_build;
    yy__building_bobj->yy__building_object_file_path = yk__sdsdup(yy__building_object_file_path);
    yy__building_bobj->yy__building_print_info = false;
    yk__arrput((*(yy__building_bobj_array)), yy__building_bobj);
    yk__sds t__23 = yy__building_object_file_path;
    yk__sdsfree(t__22);
    yk__sdsfree(yy__building_object_file);
    yk__sdsfree(t__21);
    yk__sdsfree(t__20);
    yk__sdsfree(yy__building_suffix);
    yk__sdsfree(yy__building_target);
    yk__sdsfree(yy__building_build_path);
    yk__sdsfree(yy__building_c_file);
    return t__23;
}
void yy__building_build_objects_sequential(struct yy__building_BObject** yy__building_buildables) 
{
    int32_t yy__building_object_count = yk__arrlen(yy__building_buildables);
    int32_t yy__building_pos = INT32_C(0);
    while (true)
    {
        if (!(yy__building_pos < yy__building_object_count))
        {
            break;
        }
        struct yy__building_BObject* yy__building_buildable = yy__building_buildables[yy__building_pos];
        yy__building_buildable->yy__building_print_info = true;
        yy__building_produce_obj_function(yy__building_buildable);
        yy__building_pos += INT32_C(1);
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
    if (yy__building_tpool == NULL)
    {
        yy__building_build_objects_sequential(yy__building_buildables);
        return;
    }
    int32_t yy__building_pos = INT32_C(0);
    while (true)
    {
        if (!(yy__building_pos < yy__building_object_count))
        {
            break;
        }
        struct yy__building_BObject* yy__building_buildable = yy__building_buildables[yy__building_pos];
        yy__pool_add(yy__building_tpool, yy__building_produce_obj_function, yy__building_buildable);
        yy__building_pos += INT32_C(1);
    }
    yy__pool_destroy(yy__building_tpool, true);
    return;
}
void yy__building_cleanup_buildables(struct yy__building_BObject** yy__building_buildables) 
{
    int32_t yy__building_object_count = yk__arrlen(yy__building_buildables);
    int32_t yy__building_pos = INT32_C(0);
    while (true)
    {
        if (!(yy__building_pos < yy__building_object_count))
        {
            break;
        }
        struct yy__building_BObject* yy__building_buildable = yy__building_buildables[yy__building_pos];
        yk__sdsfree(yy__building_buildable->yy__building_c_file);
        yk__sdsfree(yy__building_buildable->yy__building_object_file_path);
        free(yy__building_buildable);
        yy__building_pos += INT32_C(1);
    }
    yk__arrfree(yy__building_buildables);
    return;
}
bool yy__building_keep_ray_objects(yk__sds yy__building_element, bool yy__building_negate) 
{
    bool yy__building_obj = yy__strings_endswith(yk__sdsdup(yy__building_element), yk__sdsnewlen(".o", 2));
    if (yy__building_negate)
    {
        bool t__24 = !yy__building_obj;
        yk__sdsfree(yy__building_element);
        return t__24;
    }
    bool t__25 = yy__building_obj;
    yk__sdsfree(yy__building_element);
    return t__25;
}
bool yy__building_is_arm64_cpu() 
{
    
    #if defined(__arm64__) || defined(__aarch64__) || defined(__arm64)
        return true;
    #else
        return false;
    #endif
    ;
}
yk__sds yy__building_get_alt_compiler(struct yy__configuration_Config* yy__building_c) 
{
    if (yy__building_c->yy__configuration_alt_compiler == yy__configuration_GCC)
    {
        yk__sds t__26 = yy__building_c->yy__configuration_gcc_compiler_path;
        return t__26;
    }
    yk__sds t__27 = yy__building_c->yy__configuration_clang_compiler_path;
    return t__27;
}
yk__sds* yy__building_create_args(struct yy__configuration_Config* yy__building_c, yk__sds yy__building_code_path, yk__sds yy__building_build_path, yk__sds yy__building_target, yk__sds* yy__building_raylib_args) 
{
    bool yy__building_native = (yk__sdslen(yy__building_target) == INT32_C(0));
    yk__sds* yy__building_args = NULL;
    yk__sds* yy__building_objects = NULL;
    struct yy__building_BObject** yy__building_buildable_objects = NULL;
    yk__sds* t__30 = yy__building_raylib_args;
    bool t__32 = false;
    size_t t__29 = yk__arrlenu(t__30);
    yk__sds* t__33 = NULL;
    for (size_t t__28 = 0; t__28 < t__29; t__28++) { 
        yk__sds t__31 = yk__sdsdup(t__30[t__28]);
        bool t__34 = yy__building_keep_ray_objects(t__31, t__32);
        t__31 = yk__sdsdup(t__30[t__28]); if (t__34) {yk__arrput(t__33, t__31); } else { yk__sdsfree(t__31); }
    }
    yk__sds* yy__building_ray_objects = t__33;
    yk__sds* t__37 = yy__building_raylib_args;
    bool t__39 = true;
    size_t t__36 = yk__arrlenu(t__37);
    yk__sds* t__40 = NULL;
    for (size_t t__35 = 0; t__35 < t__36; t__35++) { 
        yk__sds t__38 = yk__sdsdup(t__37[t__35]);
        bool t__41 = yy__building_keep_ray_objects(t__38, t__39);
        t__38 = yk__sdsdup(t__37[t__35]); if (t__41) {yk__arrput(t__40, t__38); } else { yk__sdsfree(t__38); }
    }
    yk__sds* yy__building_ray_other_args = t__40;
    yk__sds yy__building_alt_compiler = yk__sdsnewlen("" , 0);
    if (yy__building_c->yy__configuration_use_alt_compiler)
    {
        yk__sds t__42 = yy__building_get_alt_compiler(yy__building_c);
        yk__sdsfree(yy__building_alt_compiler);
        yy__building_alt_compiler = yk__sdsdup(t__42);
        yk__sdsfree(t__42);
    }
    if (yy__building_c->yy__configuration_compilation->yy__configuration_wasm4)
    {
        yk__sds* t__43 = NULL;
        yk__arrsetcap(t__43, 8);
        yk__arrput(t__43, yk__sdsdup(yy__building_c->yy__configuration_zig_compiler_path));
        yk__arrput(t__43, yk__sdsnewlen("cc", 2));
        yk__arrput(t__43, yk__sdsnewlen("-std=c99", 8));
        yk__arrput(t__43, yk__sdsnewlen("-Wno-newline-eof", 16));
        yk__arrput(t__43, yk__sdsnewlen("-Wno-parentheses-equality", 25));
        yk__arrput(t__43, yk__sdsnewlen("-MMD", 4));
        yk__arrput(t__43, yk__sdsnewlen("-MP", 3));
        yk__arrput(t__43, yk__sdsnewlen("-Oz", 3));
        yy__building_args = t__43;
    }
    else
    {
        if (yy__building_c->yy__configuration_compilation->yy__configuration_web)
        {
            yk__sds* t__44 = NULL;
            yk__arrsetcap(t__44, 5);
            yk__arrput(t__44, yk__sdsdup(yy__building_c->yy__configuration_emcc_compiler_path));
            yk__arrput(t__44, yk__sdsnewlen("-std=c99", 8));
            yk__arrput(t__44, yk__sdsnewlen("-Oz", 3));
            yk__arrput(t__44, yk__sdsnewlen("-Wno-newline-eof", 16));
            yk__arrput(t__44, yk__sdsnewlen("-Wno-parentheses-equality", 25));
            yy__building_args = t__44;
        }
        else
        {
            if (yy__building_c->yy__configuration_compilation->yy__configuration_raylib_hot_reloading_dll)
            {
                if (yy__building_c->yy__configuration_use_alt_compiler)
                {
                    yk__sds* t__45 = NULL;
                    yk__arrsetcap(t__45, 8);
                    yk__arrput(t__45, yk__sdsdup(yy__building_alt_compiler));
                    yk__arrput(t__45, yk__sdsnewlen("-std=c99", 8));
                    yk__arrput(t__45, yk__sdsnewlen("-O1", 3));
                    yk__arrput(t__45, yk__sdsnewlen("-pedantic", 9));
                    yk__arrput(t__45, yk__sdsnewlen("-Wall", 5));
                    yk__arrput(t__45, yk__sdsnewlen("-Wno-newline-eof", 16));
                    yk__arrput(t__45, yk__sdsnewlen("-fPIC", 5));
                    yk__arrput(t__45, yk__sdsnewlen("-Wno-parentheses-equality", 25));
                    yy__building_args = t__45;
                }
                else
                {
                    yk__sds* t__46 = NULL;
                    yk__arrsetcap(t__46, 9);
                    yk__arrput(t__46, yk__sdsdup(yy__building_c->yy__configuration_zig_compiler_path));
                    yk__arrput(t__46, yk__sdsnewlen("cc", 2));
                    yk__arrput(t__46, yk__sdsnewlen("-std=c99", 8));
                    yk__arrput(t__46, yk__sdsnewlen("-O1", 3));
                    yk__arrput(t__46, yk__sdsnewlen("-pedantic", 9));
                    yk__arrput(t__46, yk__sdsnewlen("-Wall", 5));
                    yk__arrput(t__46, yk__sdsnewlen("-Wno-newline-eof", 16));
                    yk__arrput(t__46, yk__sdsnewlen("-fPIC", 5));
                    yk__arrput(t__46, yk__sdsnewlen("-Wno-parentheses-equality", 25));
                    yy__building_args = t__46;
                }
            }
            else
            {
                if (yy__building_c->yy__configuration_compilation->yy__configuration_disable_parallel_build)
                {
                    if (yy__building_c->yy__configuration_use_alt_compiler)
                    {
                        yk__sds* t__47 = NULL;
                        yk__arrsetcap(t__47, 4);
                        yk__arrput(t__47, yk__sdsdup(yy__building_alt_compiler));
                        yk__arrput(t__47, yk__sdsnewlen("-std=c99", 8));
                        yk__arrput(t__47, yk__sdsnewlen("-O0", 3));
                        yk__arrput(t__47, yk__sdsnewlen("-fPIC", 5));
                        yy__building_args = t__47;
                    }
                    else
                    {
                        yk__sds* t__48 = NULL;
                        yk__arrsetcap(t__48, 5);
                        yk__arrput(t__48, yk__sdsdup(yy__building_c->yy__configuration_zig_compiler_path));
                        yk__arrput(t__48, yk__sdsnewlen("cc", 2));
                        yk__arrput(t__48, yk__sdsnewlen("-std=c99", 8));
                        yk__arrput(t__48, yk__sdsnewlen("-O0", 3));
                        yk__arrput(t__48, yk__sdsnewlen("-fPIC", 5));
                        yy__building_args = t__48;
                    }
                }
                else
                {
                    if (yy__building_c->yy__configuration_use_alt_compiler)
                    {
                        yk__sds* t__49 = NULL;
                        yk__arrsetcap(t__49, 8);
                        yk__arrput(t__49, yk__sdsdup(yy__building_alt_compiler));
                        yk__arrput(t__49, yk__sdsnewlen("-std=c99", 8));
                        yk__arrput(t__49, yk__sdsnewlen("-Oz", 3));
                        yk__arrput(t__49, yk__sdsnewlen("-pedantic", 9));
                        yk__arrput(t__49, yk__sdsnewlen("-Wall", 5));
                        yk__arrput(t__49, yk__sdsnewlen("-Wno-newline-eof", 16));
                        yk__arrput(t__49, yk__sdsnewlen("-fPIC", 5));
                        yk__arrput(t__49, yk__sdsnewlen("-Wno-parentheses-equality", 25));
                        yy__building_args = t__49;
                    }
                    else
                    {
                        yk__sds* t__50 = NULL;
                        yk__arrsetcap(t__50, 9);
                        yk__arrput(t__50, yk__sdsdup(yy__building_c->yy__configuration_zig_compiler_path));
                        yk__arrput(t__50, yk__sdsnewlen("cc", 2));
                        yk__arrput(t__50, yk__sdsnewlen("-std=c99", 8));
                        yk__arrput(t__50, yk__sdsnewlen("-Oz", 3));
                        yk__arrput(t__50, yk__sdsnewlen("-pedantic", 9));
                        yk__arrput(t__50, yk__sdsnewlen("-Wall", 5));
                        yk__arrput(t__50, yk__sdsnewlen("-Wno-newline-eof", 16));
                        yk__arrput(t__50, yk__sdsnewlen("-fPIC", 5));
                        yk__arrput(t__50, yk__sdsnewlen("-Wno-parentheses-equality", 25));
                        yy__building_args = t__50;
                    }
                }
            }
        }
    }
    if (((!(yy__building_is_target_macos(yk__sdsdup(yy__building_target)))) && (!(yy__building_c->yy__configuration_compilation->yy__configuration_raylib_hot_reloading_dll))) && (!(yy__building_c->yy__configuration_compilation->yy__configuration_disable_parallel_build)))
    {
        yk__arrput(yy__building_args, yk__sdsnewlen("-flto=full", 10));
    }
    if (yy__building_c->yy__configuration_compilation->yy__configuration_raylib_hot_reloading_dll)
    {
        yk__arrput(yy__building_args, yk__sdsnewlen("-DYK__CR_DLL", 12));
    }
    yy__building_args = yy__array_extend(yy__building_args, yy__building_ray_other_args);
    int32_t yy__building_length = INT32_C(0);
    int32_t yy__building_x = INT32_C(0);
    yy__building_length = yk__arrlen(yy__building_c->yy__configuration_c_code->yy__configuration_include_paths);
    yy__building_x = INT32_C(0);
    while (true)
    {
        if (!(yy__building_x < yy__building_length))
        {
            break;
        }
        yk__sds t__51 = yk__concat_lit_sds("-I", 2, yy__building_c->yy__configuration_c_code->yy__configuration_include_paths[yy__building_x]);
        yk__sds yy__building_include = yk__sdsdup(t__51);
        yk__arrput(yy__building_args, yk__sdsdup(yy__building_include));
        yy__building_x = (yy__building_x + INT32_C(1));
        yk__sdsfree(yy__building_include);
        yk__sdsfree(t__51);
    }
    yy__building_length = yk__arrlen(yy__building_c->yy__configuration_c_code->yy__configuration_runtime_feature_compiler_defines);
    yy__building_x = INT32_C(0);
    while (true)
    {
        if (!(yy__building_x < yy__building_length))
        {
            break;
        }
        yk__sds t__52 = yk__concat_lit_sds("-D", 2, yy__building_c->yy__configuration_c_code->yy__configuration_runtime_feature_compiler_defines[yy__building_x]);
        yk__sds yy__building_cdefine = yk__sdsdup(t__52);
        yk__arrput(yy__building_args, yk__sdsdup(yy__building_cdefine));
        yy__building_x = (yy__building_x + INT32_C(1));
        yk__sdsfree(yy__building_cdefine);
        yk__sdsfree(t__52);
    }
    yy__building_length = yk__arrlen(yy__building_c->yy__configuration_c_code->yy__configuration_compiler_defines);
    yy__building_x = INT32_C(0);
    while (true)
    {
        if (!(yy__building_x < yy__building_length))
        {
            break;
        }
        yk__sds t__53 = yk__concat_lit_sds("-D", 2, yy__building_c->yy__configuration_c_code->yy__configuration_compiler_defines[yy__building_x]);
        yk__sds yy__building_cdefine = yk__sdsdup(t__53);
        yk__arrput(yy__building_args, yk__sdsdup(yy__building_cdefine));
        yy__building_x = (yy__building_x + INT32_C(1));
        yk__sdsfree(yy__building_cdefine);
        yk__sdsfree(t__53);
    }
    if ((!yy__building_native && (yk__cmp_sds_lit(yy__building_target, "web", 3) != 0)) && (yk__cmp_sds_lit(yy__building_target, "wasm4", 5) != 0))
    {
        yk__arrput(yy__building_args, yk__sdsnewlen("-target", 7));
        yk__arrput(yy__building_args, yk__sdsdup(yy__building_target));
    }
    if (yk__cmp_sds_lit(yy__building_target, "wasm4", 5) == 0)
    {
        yk__arrput(yy__building_args, yk__sdsnewlen("-target", 7));
        yk__arrput(yy__building_args, yk__sdsnewlen("wasm32-wasi-musl", 16));
    }
    if (((yy__building_native && yy__building_is_arm64_cpu()) && yy__building_is_target_macos(yk__sdsdup(yy__building_target))) && (!(yy__building_c->yy__configuration_use_alt_compiler)))
    {
        yk__arrput(yy__building_args, yk__sdsnewlen("-target", 7));
        yk__arrput(yy__building_args, yk__sdsnewlen("aarch64-macos-gnu", 17));
    }
    yy__building_length = yk__arrlen(yy__building_c->yy__configuration_c_code->yy__configuration_runtime_feature_c_code);
    yy__building_x = INT32_C(0);
    while (true)
    {
        if (!(yy__building_x < yy__building_length))
        {
            break;
        }
        yk__sds yy__building_rfc = yk__sdsdup(yy__building_c->yy__configuration_c_code->yy__configuration_runtime_feature_c_code[yy__building_x]);
        yk__sds t__54 = yy__building_core_object(yy__building_args, yk__sdsdup(yy__building_rfc), yk__sdsdup(yy__building_build_path), yk__sdsdup(yy__building_target), false, (&(yy__building_buildable_objects)));
        yk__sdsfree(yy__building_rfc);
        yy__building_rfc = yk__sdsdup(t__54);
        yk__arrput(yy__building_objects, yk__sdsdup(yy__building_rfc));
        yy__building_x = (yy__building_x + INT32_C(1));
        yk__sdsfree(t__54);
        yk__sdsfree(yy__building_rfc);
    }
    yy__building_length = yk__arrlen(yy__building_c->yy__configuration_c_code->yy__configuration_c_code);
    yy__building_x = INT32_C(0);
    while (true)
    {
        if (!(yy__building_x < yy__building_length))
        {
            break;
        }
        yk__sds yy__building_cc = yk__sdsdup(yy__building_c->yy__configuration_c_code->yy__configuration_c_code[yy__building_x]);
        yk__sds t__55 = yy__building_core_object(yy__building_args, yk__sdsdup(yy__building_cc), yk__sdsdup(yy__building_build_path), yk__sdsdup(yy__building_target), true, (&(yy__building_buildable_objects)));
        yk__sdsfree(yy__building_cc);
        yy__building_cc = yk__sdsdup(t__55);
        yk__arrput(yy__building_objects, yk__sdsdup(yy__building_cc));
        yy__building_x = (yy__building_x + INT32_C(1));
        yk__sdsfree(t__55);
        yk__sdsfree(yy__building_cc);
    }
    yk__sds t__56 = yy__building_core_object(yy__building_args, yk__sdsdup(yy__building_code_path), yk__sdsdup(yy__building_build_path), yk__sdsdup(yy__building_target), true, (&(yy__building_buildable_objects)));
    yk__sds yy__building_program_object = yk__sdsdup(t__56);
    yk__arrput(yy__building_objects, yk__sdsdup(yy__building_program_object));
    yk__sds t__57 = yy__path_join(yk__sdsdup(yy__building_c->yy__configuration_runtime_path), yk__sdsnewlen("yk__main.c", 10));
    yk__sds yy__building_the_yk_main = yk__sdsdup(t__57);
    yk__sds t__58 = yy__building_core_object(yy__building_args, yk__sdsdup(yy__building_the_yk_main), yk__sdsdup(yy__building_build_path), yk__sdsdup(yy__building_target), false, (&(yy__building_buildable_objects)));
    yk__sdsfree(yy__building_the_yk_main);
    yy__building_the_yk_main = yk__sdsdup(t__58);
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
        yk__sds* t__59 = NULL;
        yk__arrsetcap(t__59, 19);
        yk__arrput(t__59, yk__sdsdup(yy__building_c->yy__configuration_zig_compiler_path));
        yk__arrput(t__59, yk__sdsnewlen("build-lib", 9));
        yk__arrput(t__59, yk__sdsnewlen("-dynamic", 8));
        yk__arrput(t__59, yk__sdsnewlen("-flto", 5));
        yk__arrput(t__59, yk__sdsnewlen("-mexec-model=reactor", 20));
        yk__arrput(t__59, yk__sdsnewlen("-O", 2));
        yk__arrput(t__59, yk__sdsnewlen("ReleaseSmall", 12));
        yk__arrput(t__59, yk__sdsnewlen("-target", 7));
        yk__arrput(t__59, yk__sdsnewlen("wasm32-wasi-musl", 16));
        yk__arrput(t__59, yk__sdsnewlen("--strip", 7));
        yk__arrput(t__59, yk__sdsnewlen("--stack", 7));
        yk__arrput(t__59, yk__sdsnewlen("50784", 5));
        yk__arrput(t__59, yk__sdsnewlen("--global-base=6560", 18));
        yk__arrput(t__59, yk__sdsnewlen("--import-memory", 15));
        yk__arrput(t__59, yk__sdsnewlen("--initial-memory=65536", 22));
        yk__arrput(t__59, yk__sdsnewlen("--max-memory=65536", 18));
        yk__arrput(t__59, yk__sdsnewlen("-ofmt=wasm", 10));
        yk__arrput(t__59, yk__sdsnewlen("--export=start", 14));
        yk__arrput(t__59, yk__sdsnewlen("--export=update", 15));
        yy__building_args = t__59;
    }
    yy__building_args = yy__array_extend(yy__building_args, yy__building_objects);
    yy__building_args = yy__array_extend(yy__building_args, yy__building_ray_objects);
    yy__array_del_str_array(yy__building_objects);
    if (yy__building_c->yy__configuration_compilation->yy__configuration_web && (yk__sdslen(yy__building_c->yy__configuration_compilation->yy__configuration_web_shell) > INT32_C(0)))
    {
        yk__arrput(yy__building_args, yk__sdsnewlen("--shell-file", 12));
        yk__arrput(yy__building_args, yk__sdsdup(yy__building_c->yy__configuration_compilation->yy__configuration_web_shell));
    }
    if (yy__building_c->yy__configuration_compilation->yy__configuration_web && (yk__sdslen(yy__building_c->yy__configuration_compilation->yy__configuration_web_assets) > INT32_C(0)))
    {
        yk__arrput(yy__building_args, yk__sdsnewlen("--preload-file", 14));
        yk__arrput(yy__building_args, yk__sdsdup(yy__building_c->yy__configuration_compilation->yy__configuration_web_assets));
    }
    if (yy__building_c->yy__configuration_compilation->yy__configuration_raylib_hot_reloading_dll)
    {
        yk__arrput(yy__building_args, yk__sdsnewlen("-shared", 7));
    }
    if (yk__cmp_sds_lit(yy__building_target, "wasm4", 5) != 0)
    {
        yk__arrput(yy__building_args, yk__sdsnewlen("-o", 2));
    }
    yk__sds yy__building_binary = yk__sdsdup(yy__building_c->yy__configuration_project->yy__configuration_name);
    if ((!yy__building_native && (yk__cmp_sds_lit(yy__building_target, "web", 3) != 0)) && (yk__cmp_sds_lit(yy__building_target, "wasm4", 5) != 0))
    {
        yk__sds t__60 = yk__concat_sds_lit(yy__building_binary, "-", 1);
        yk__sds t__61 = yk__sdscatsds(yk__sdsdup(t__60), yy__building_target);
        yk__sdsfree(yy__building_binary);
        yy__building_binary = yk__sdsdup(t__61);
        yk__sdsfree(t__61);
        yk__sdsfree(t__60);
    }
    if (yy__building_c->yy__configuration_compilation->yy__configuration_raylib_hot_reloading_dll)
    {
        if (yy__building_is_target_windows(yk__sdsdup(yy__building_target)))
        {
            yk__sds t__62 = yk__concat_sds_lit(yy__building_binary, ".dll", 4);
            yk__sdsfree(yy__building_binary);
            yy__building_binary = yk__sdsdup(t__62);
            yk__sdsfree(t__62);
        }
        else
        {
            if (yy__building_is_target_macos(yk__sdsdup(yy__building_target)))
            {
                yk__sds t__63 = yk__concat_lit_sds("lib", 3, yy__building_binary);
                yk__sds t__64 = yk__concat_sds_lit(t__63, ".dylib", 6);
                yk__sdsfree(yy__building_binary);
                yy__building_binary = yk__sdsdup(t__64);
                yk__sdsfree(t__64);
                yk__sdsfree(t__63);
            }
            else
            {
                yk__sds t__65 = yk__concat_lit_sds("lib", 3, yy__building_binary);
                yk__sds t__66 = yk__concat_sds_lit(t__65, ".so", 3);
                yk__sdsfree(yy__building_binary);
                yy__building_binary = yk__sdsdup(t__66);
                yk__sdsfree(t__66);
                yk__sdsfree(t__65);
            }
        }
    }
    else
    {
        if (yy__building_is_target_windows(yk__sdsdup(yy__building_target)))
        {
            yk__sds t__67 = yk__concat_sds_lit(yy__building_binary, ".exe", 4);
            yk__sdsfree(yy__building_binary);
            yy__building_binary = yk__sdsdup(t__67);
            yk__sdsfree(t__67);
        }
    }
    if (yk__cmp_sds_lit(yy__building_target, "web", 3) == 0)
    {
        yk__sds t__68 = yk__concat_sds_lit(yy__building_binary, ".html", 5);
        yk__sdsfree(yy__building_binary);
        yy__building_binary = yk__sdsdup(t__68);
        yk__sdsfree(t__68);
    }
    if (yk__cmp_sds_lit(yy__building_target, "wasm4", 5) == 0)
    {
        yk__sds t__69 = yk__concat_sds_lit(yy__building_binary, ".wasm", 5);
        yk__sdsfree(yy__building_binary);
        yy__building_binary = yk__sdsdup(t__69);
        yk__sdsfree(t__69);
    }
    yk__sds t__70 = yy__path_join(yk__sdsdup(yy__building_build_path), yk__sdsdup(yy__building_binary));
    yk__sdsfree(yy__building_binary);
    yy__building_binary = yk__sdsdup(t__70);
    if (yk__cmp_sds_lit(yy__building_target, "wasm4", 5) == 0)
    {
        yk__sds t__71 = yk__concat_lit_sds("-femit-bin=", 11, yy__building_binary);
        yk__arrput(yy__building_args, yk__sdsdup(t__71));
        yk__sdsfree(t__71);
    }
    else
    {
        yk__arrput(yy__building_args, yk__sdsdup(yy__building_binary));
    }
    yk__sds* t__72 = yy__building_args;
    yy__array_del_str_array(yy__building_ray_other_args);
    yy__array_del_str_array(yy__building_ray_objects);
    yk__sdsfree(t__70);
    yk__sdsfree(yy__building_binary);
    yk__sdsfree(t__58);
    yk__sdsfree(yy__building_the_yk_main);
    yk__sdsfree(t__57);
    yk__sdsfree(yy__building_program_object);
    yk__sdsfree(t__56);
    yk__sdsfree(yy__building_alt_compiler);
    yk__sdsfree(yy__building_target);
    yk__sdsfree(yy__building_build_path);
    yk__sdsfree(yy__building_code_path);
    return t__72;
}
void yy__building_print_target_eq(yk__sds yy__building_target, bool yy__building_native) 
{
    if (yy__building_native)
    {
        yy__console_yellow(yk__bstr_s("native", 6));
    }
    else
    {
        yy__console_yellow(yk__bstr_h(yy__building_target));
    }
    yy__console_cyan(yk__bstr_s(" := ", 4));
    yk__sdsfree(yy__building_target);
    return;
}
int32_t yy__building_build_target(struct yy__configuration_Config* yy__building_c, yk__sds yy__building_code_path, yk__sds yy__building_build_path, yk__sds yy__building_target, yk__sds* yy__building_raylib_args, bool yy__building_silent) 
{
    bool yy__building_native = (yk__sdslen(yy__building_target) == INT32_C(0));
    yk__sds* yy__building_a = yy__building_create_args(yy__building_c, yk__sdsdup(yy__building_code_path), yk__sdsdup(yy__building_build_path), yk__sdsdup(yy__building_target), yy__building_raylib_args);
    yy__os_ProcessResult yy__building_result = yy__os_run(yy__building_a);
    if (yy__building_result->ok)
    {
        if (!yy__building_silent)
        {
            yy__building_print_target_eq(yk__sdsdup(yy__building_target), yy__building_native);
            yy__console_green(yk__bstr_s("done.\n", 6));
        }
        yy__os_del_process_result(yy__building_result);
        yy__array_del_str_array(yy__building_a);
        yk__sdsfree(yy__building_target);
        yk__sdsfree(yy__building_build_path);
        yk__sdsfree(yy__building_code_path);
        return INT32_C(0);
    }
    else
    {
        yy__building_print_target_eq(yk__sdsdup(yy__building_target), yy__building_native);
        yy__console_red(yk__bstr_s("failed.\n", 8));
        yy__console_cyan(yk__bstr_s("-------\n", 8));
        yy__console_red(yk__bstr_s("command := ", 11));
        yk__sds t__73 = yy__array_join(yy__building_a, yk__sdsnewlen(" ", 1));
        yy__console_yellow(yk__bstr_h(t__73));
        yy__console_cyan(yk__bstr_s("\n-------\n", 9));
        yy__console_red(yk__bstr_h(yy__building_result->output));
        yy__os_del_process_result(yy__building_result);
        yy__array_del_str_array(yy__building_a);
        yk__sdsfree(t__73);
        yk__sdsfree(yy__building_target);
        yk__sdsfree(yy__building_build_path);
        yk__sdsfree(yy__building_code_path);
        return INT32_C(1);
        yk__sdsfree(t__73);
    }
}
bool yy__building_print_error(yk__sds yy__building_error, int32_t yy__building_ignored) 
{
    yy__console_red(yk__bstr_s("error", 5));
    yy__console_yellow(yk__bstr_s(":", 1));
    yk__printlnstr(yy__building_error);
    yk__sdsfree(yy__building_error);
    return true;
}
int32_t yy__building_build(struct yy__configuration_Config* yy__building_c, yk__sds yy__building_code) 
{
    yy__configuration_load_runtime_features(yy__building_c, yk__sdsdup(yy__building_code), false);
    if (yy__building_c->yy__configuration_compilation->yy__configuration_wasm4 && (yy__building_c->yy__configuration_compilation->yy__configuration_web || yy__building_c->yy__configuration_compilation->yy__configuration_raylib))
    {
        yk__arrput(yy__building_c->yy__configuration_errors, yk__sdsnewlen("WASM4 builds are not compatible with raylib/web builds", 54));
    }
    yk__sds yy__building_target = yk__sdsnewlen("" , 0);
    if (yk__arrlen(yy__building_c->yy__configuration_errors) > INT32_C(0))
    {
        yk__sds* t__76 = yy__building_c->yy__configuration_errors;
        int32_t t__78 = INT32_C(0);
        size_t t__75 = yk__arrlenu(t__76);
        bool t__79 = true;
        for (size_t t__74 = 0; t__74 < t__75; t__74++) { 
            yk__sds t__77 = yk__sdsdup(t__76[t__74]);
            bool t__80 = yy__building_print_error(t__77, t__78);
            if (!t__80) {t__79 = false; break; }
        }
        t__79;
        int32_t t__81 = (-(INT32_C(1)));
        yk__sdsfree(yy__building_target);
        yk__sdsfree(yy__building_code);
        return t__81;
    }
    if (yy__building_c->yy__configuration_compilation->yy__configuration_wasm4)
    {
        yk__sdsfree(yy__building_target);
        yy__building_target = yk__sdsnewlen("wasm4", 5);
    }
    if (yy__building_c->yy__configuration_compilation->yy__configuration_web)
    {
        yk__sdsfree(yy__building_target);
        yy__building_target = yk__sdsnewlen("web", 3);
    }
    int32_t yy__building_target_count = yk__arrlen(yy__building_c->yy__configuration_compilation->yy__configuration_targets);
    if (yy__building_c->yy__configuration_use_alt_compiler)
    {
        yy__building_target_count = INT32_C(0);
    }
    yk__sds* yy__building_raylib_args = NULL;
    if ((yy__building_target_count != INT32_C(0)) && yy__building_c->yy__configuration_compilation->yy__configuration_raylib)
    {
        yy__console_red(yk__bstr_s("raylib build only support native builds.\n", 41));
        yy__console_cyan(yk__bstr_s("Hint: You need to keep [compilation].targets empty\n", 51));
        int32_t t__82 = (-(INT32_C(1)));
        yy__array_del_str_array(yy__building_raylib_args);
        yk__sdsfree(yy__building_target);
        yk__sdsfree(yy__building_code);
        return t__82;
    }
    if ((yy__building_target_count != INT32_C(0)) && yy__building_c->yy__configuration_compilation->yy__configuration_raylib)
    {
        yy__console_red(yk__bstr_s("wasm4 build does not support additional targets.\n", 49));
        yy__console_cyan(yk__bstr_s("Hint: You need to keep [compilation].targets empty\n", 51));
        int32_t t__83 = (-(INT32_C(1)));
        yy__array_del_str_array(yy__building_raylib_args);
        yk__sdsfree(yy__building_target);
        yk__sdsfree(yy__building_code);
        return t__83;
    }
    yk__sds t__84 = yy__os_cwd();
    yk__sds t__85 = yy__path_join(yk__sdsdup(t__84), yk__sdsnewlen("build", 5));
    yk__sds yy__building_build_path = yk__sdsdup(t__85);
    if (yy__building_c->yy__configuration_compilation->yy__configuration_raylib)
    {
        yy__building_raylib_args = yy__raylib_support_get_raylib_args(yy__building_c, yk__sdsdup(yy__building_build_path));
    }
    yk__printstr("\nbuilding ");
    yk__printint((intmax_t)(yy__building_target_count + INT32_C(1)));
    yk__printlnstr(" target(s) ...");
    yy__path_mkdir(yk__sdsdup(yy__building_build_path));
    yk__sds t__86 = yy__path_join(yk__sdsdup(yy__building_build_path), yk__sdsnewlen("program_code.c", 14));
    yk__sds yy__building_code_path = yk__sdsdup(t__86);
    yk__sds t__87 = yy__building_prepare_code(yy__building_c, yk__sdsdup(yy__building_code));
    if (!(yy__io_writefile(yk__sdsdup(yy__building_code_path), yk__sdsdup(t__87))))
    {
        yy__console_red(yk__bstr_s("Failed to write file:", 21));
        yk__printlnstr(yy__building_code_path);
        int32_t t__88 = (-(INT32_C(1)));
        yy__array_del_str_array(yy__building_raylib_args);
        yk__sdsfree(t__87);
        yk__sdsfree(yy__building_code_path);
        yk__sdsfree(t__86);
        yk__sdsfree(yy__building_build_path);
        yk__sdsfree(t__85);
        yk__sdsfree(t__84);
        yk__sdsfree(yy__building_target);
        yk__sdsfree(yy__building_code);
        return t__88;
    }
    int32_t yy__building_failed_count = INT32_C(0);
    yy__building_failed_count = (yy__building_failed_count + yy__building_build_target(yy__building_c, yk__sdsdup(yy__building_code_path), yk__sdsdup(yy__building_build_path), yk__sdsdup(yy__building_target), yy__building_raylib_args, false));
    int32_t yy__building_cnt = INT32_C(0);
    while (true)
    {
        if (!(yy__building_cnt < yy__building_target_count))
        {
            break;
        }
        yk__sdsfree(yy__building_target);
        yy__building_target = yk__sdsdup(yy__building_c->yy__configuration_compilation->yy__configuration_targets[yy__building_cnt]);
        yy__building_failed_count = (yy__building_failed_count + yy__building_build_target(yy__building_c, yk__sdsdup(yy__building_code_path), yk__sdsdup(yy__building_build_path), yk__sdsdup(yy__building_target), yy__building_raylib_args, false));
        yy__building_cnt = (yy__building_cnt + INT32_C(1));
    }
    yk__printstr("\n");
    if (yy__building_failed_count > INT32_C(0))
    {
        int32_t t__89 = (-(INT32_C(1)));
        yy__array_del_str_array(yy__building_raylib_args);
        yk__sdsfree(t__87);
        yk__sdsfree(yy__building_code_path);
        yk__sdsfree(t__86);
        yk__sdsfree(yy__building_build_path);
        yk__sdsfree(t__85);
        yk__sdsfree(t__84);
        yk__sdsfree(yy__building_target);
        yk__sdsfree(yy__building_code);
        return t__89;
    }
    yy__array_del_str_array(yy__building_raylib_args);
    yk__sdsfree(t__87);
    yk__sdsfree(yy__building_code_path);
    yk__sdsfree(t__86);
    yk__sdsfree(yy__building_build_path);
    yk__sdsfree(t__85);
    yk__sdsfree(t__84);
    yk__sdsfree(yy__building_target);
    yk__sdsfree(yy__building_code);
    return INT32_C(0);
}
int32_t yy__building_build_simple(struct yy__configuration_Config* yy__building_c, yk__sds yy__building_code, bool yy__building_silent) 
{
    yy__configuration_load_runtime_features(yy__building_c, yk__sdsdup(yy__building_code), yy__building_silent);
    if (yy__building_c->yy__configuration_compilation->yy__configuration_wasm4 && (yy__building_c->yy__configuration_compilation->yy__configuration_web || yy__building_c->yy__configuration_compilation->yy__configuration_raylib))
    {
        yk__arrput(yy__building_c->yy__configuration_errors, yk__sdsnewlen("WASM4 builds are not compatible with raylib/web builds", 54));
    }
    if (yk__arrlen(yy__building_c->yy__configuration_errors) > INT32_C(0))
    {
        yk__sds* t__92 = yy__building_c->yy__configuration_errors;
        int32_t t__94 = INT32_C(0);
        size_t t__91 = yk__arrlenu(t__92);
        bool t__95 = true;
        for (size_t t__90 = 0; t__90 < t__91; t__90++) { 
            yk__sds t__93 = yk__sdsdup(t__92[t__90]);
            bool t__96 = yy__building_print_error(t__93, t__94);
            if (!t__96) {t__95 = false; break; }
        }
        t__95;
        int32_t t__97 = (-(INT32_C(1)));
        yk__sdsfree(yy__building_code);
        return t__97;
    }
    yk__sds t__98 = yy__os_cwd();
    yk__sds t__99 = yk__concat_sds_lit(yy__building_c->yy__configuration_project->yy__configuration_name, ".c", 2);
    yk__sds t__100 = yy__path_join(yk__sdsdup(t__98), yk__sdsdup(t__99));
    yk__sds yy__building_code_path = yk__sdsdup(t__100);
    yk__sds* yy__building_raylib_args = NULL;
    yk__sds yy__building_target = yk__sdsnewlen("" , 0);
    if (yy__building_c->yy__configuration_compilation->yy__configuration_raylib)
    {
        yk__sds t__101 = yy__os_cwd();
        yy__building_raylib_args = yy__raylib_support_get_raylib_args(yy__building_c, yk__sdsdup(t__101));
        yk__sdsfree(t__101);
    }
    if (yy__building_c->yy__configuration_compilation->yy__configuration_wasm4)
    {
        yk__sdsfree(yy__building_target);
        yy__building_target = yk__sdsnewlen("wasm4", 5);
    }
    if (yy__building_c->yy__configuration_compilation->yy__configuration_web)
    {
        yk__sdsfree(yy__building_target);
        yy__building_target = yk__sdsnewlen("web", 3);
    }
    yk__sds t__102 = yy__building_prepare_code(yy__building_c, yk__sdsdup(yy__building_code));
    if (!(yy__io_writefile(yk__sdsdup(yy__building_code_path), yk__sdsdup(t__102))))
    {
        yy__console_red(yk__bstr_s("Failed to write file:", 21));
        yk__printlnstr(yy__building_code_path);
        int32_t t__103 = (-(INT32_C(1)));
        yy__array_del_str_array(yy__building_raylib_args);
        yk__sdsfree(t__102);
        yk__sdsfree(yy__building_target);
        yk__sdsfree(yy__building_code_path);
        yk__sdsfree(t__100);
        yk__sdsfree(t__99);
        yk__sdsfree(t__98);
        yk__sdsfree(yy__building_code);
        return t__103;
    }
    yk__sds t__104 = yy__os_cwd();
    int32_t yy__building_failed_count = yy__building_build_target(yy__building_c, yk__sdsdup(yy__building_code_path), yk__sdsdup(t__104), yk__sdsdup(yy__building_target), yy__building_raylib_args, yy__building_silent);
    if (yy__building_failed_count > INT32_C(0))
    {
        int32_t t__105 = (-(INT32_C(1)));
        yy__array_del_str_array(yy__building_raylib_args);
        yk__sdsfree(t__104);
        yk__sdsfree(t__102);
        yk__sdsfree(yy__building_target);
        yk__sdsfree(yy__building_code_path);
        yk__sdsfree(t__100);
        yk__sdsfree(t__99);
        yk__sdsfree(t__98);
        yk__sdsfree(yy__building_code);
        return t__105;
    }
    yy__array_del_str_array(yy__building_raylib_args);
    yk__sdsfree(t__104);
    yk__sdsfree(t__102);
    yk__sdsfree(yy__building_target);
    yk__sdsfree(yy__building_code_path);
    yk__sdsfree(t__100);
    yk__sdsfree(t__99);
    yk__sdsfree(t__98);
    yk__sdsfree(yy__building_code);
    return INT32_C(0);
}
void yy__configuration_find_runtime_path(struct yy__configuration_Config* yy__configuration_c) 
{
    yk__sds t__0 = yy__os_exe_path();
    yk__sds yy__configuration_exe_parent = yk__sdsdup(t__0);
    yk__sds t__1 = yy__path_dirname(yk__sdsdup(yy__configuration_exe_parent));
    yk__sds t__2 = yy__path_join(yk__sdsdup(t__1), yk__sdsnewlen("runtime", 7));
    yk__sds yy__configuration_l1 = yk__sdsdup(t__2);
    yk__sds t__3 = yy__path_dirname(yk__sdsdup(yy__configuration_exe_parent));
    yk__sds t__4 = yy__path_dirname(yk__sdsdup(t__3));
    yk__sds t__5 = yy__path_join(yk__sdsdup(t__4), yk__sdsnewlen("runtime", 7));
    yk__sds yy__configuration_l2 = yk__sdsdup(t__5);
    yk__sds t__6 = yy__path_join(yk__sdsdup(yy__configuration_exe_parent), yk__sdsnewlen("runtime", 7));
    yk__sds yy__configuration_l3 = yk__sdsdup(t__6);
    yk__sds t__7 = yy__path_join(yk__sdsdup(yy__configuration_l1), yk__sdsnewlen("yk__lib.h", 9));
    if (yy__path_readable(yk__sdsdup(t__7)))
    {
        yy__configuration_c->yy__configuration_runtime_path = yk__sdsdup(yy__configuration_l1);
        yk__sdsfree(t__7);
        yk__sdsfree(yy__configuration_l3);
        yk__sdsfree(t__6);
        yk__sdsfree(yy__configuration_l2);
        yk__sdsfree(t__5);
        yk__sdsfree(t__4);
        yk__sdsfree(t__3);
        yk__sdsfree(yy__configuration_l1);
        yk__sdsfree(t__2);
        yk__sdsfree(t__1);
        yk__sdsfree(yy__configuration_exe_parent);
        yk__sdsfree(t__0);
        return;
    }
    yk__sds t__8 = yy__path_join(yk__sdsdup(yy__configuration_l2), yk__sdsnewlen("yk__lib.h", 9));
    if (yy__path_readable(yk__sdsdup(t__8)))
    {
        yy__configuration_c->yy__configuration_runtime_path = yk__sdsdup(yy__configuration_l2);
        yk__sdsfree(t__8);
        yk__sdsfree(t__7);
        yk__sdsfree(yy__configuration_l3);
        yk__sdsfree(t__6);
        yk__sdsfree(yy__configuration_l2);
        yk__sdsfree(t__5);
        yk__sdsfree(t__4);
        yk__sdsfree(t__3);
        yk__sdsfree(yy__configuration_l1);
        yk__sdsfree(t__2);
        yk__sdsfree(t__1);
        yk__sdsfree(yy__configuration_exe_parent);
        yk__sdsfree(t__0);
        return;
    }
    yk__sds t__9 = yy__path_join(yk__sdsdup(yy__configuration_l3), yk__sdsnewlen("yk__lib.h", 9));
    if (yy__path_readable(yk__sdsdup(t__9)))
    {
        yy__configuration_c->yy__configuration_runtime_path = yk__sdsdup(yy__configuration_l3);
        yk__sdsfree(t__9);
        yk__sdsfree(t__8);
        yk__sdsfree(t__7);
        yk__sdsfree(yy__configuration_l3);
        yk__sdsfree(t__6);
        yk__sdsfree(yy__configuration_l2);
        yk__sdsfree(t__5);
        yk__sdsfree(t__4);
        yk__sdsfree(t__3);
        yk__sdsfree(yy__configuration_l1);
        yk__sdsfree(t__2);
        yk__sdsfree(t__1);
        yk__sdsfree(yy__configuration_exe_parent);
        yk__sdsfree(t__0);
        return;
    }
    yk__sds t__10 = yk__concat_lit_sds("Failed to find runtime library in :", 35, yy__configuration_l1);
    yk__arrput(yy__configuration_c->yy__configuration_errors, yk__sdsdup(t__10));
    yk__sds t__11 = yk__concat_lit_sds("Failed to find runtime library in :", 35, yy__configuration_l2);
    yk__arrput(yy__configuration_c->yy__configuration_errors, yk__sdsdup(t__11));
    yk__sds t__12 = yk__concat_lit_sds("Failed to find runtime library in :", 35, yy__configuration_l3);
    yk__arrput(yy__configuration_c->yy__configuration_errors, yk__sdsdup(t__12));
    yy__configuration_c->yy__configuration_runtime_path = yk__sdsnewlen("<not found>", 11);
    yk__sdsfree(t__12);
    yk__sdsfree(t__11);
    yk__sdsfree(t__10);
    yk__sdsfree(t__9);
    yk__sdsfree(t__8);
    yk__sdsfree(t__7);
    yk__sdsfree(yy__configuration_l3);
    yk__sdsfree(t__6);
    yk__sdsfree(yy__configuration_l2);
    yk__sdsfree(t__5);
    yk__sdsfree(t__4);
    yk__sdsfree(t__3);
    yk__sdsfree(yy__configuration_l1);
    yk__sdsfree(t__2);
    yk__sdsfree(t__1);
    yk__sdsfree(yy__configuration_exe_parent);
    yk__sdsfree(t__0);
    return;
}
void yy__configuration_find_libs_path(struct yy__configuration_Config* yy__configuration_c) 
{
    yk__sds t__13 = yy__os_exe_path();
    yk__sds yy__configuration_exe_parent = yk__sdsdup(t__13);
    yk__sds t__14 = yy__path_dirname(yk__sdsdup(yy__configuration_exe_parent));
    yk__sds t__15 = yy__path_join(yk__sdsdup(t__14), yk__sdsnewlen("libs", 4));
    yk__sds yy__configuration_l1 = yk__sdsdup(t__15);
    yk__sds t__16 = yy__path_dirname(yk__sdsdup(yy__configuration_exe_parent));
    yk__sds t__17 = yy__path_dirname(yk__sdsdup(t__16));
    yk__sds t__18 = yy__path_join(yk__sdsdup(t__17), yk__sdsnewlen("libs", 4));
    yk__sds yy__configuration_l2 = yk__sdsdup(t__18);
    yk__sds t__19 = yy__path_join(yk__sdsdup(yy__configuration_exe_parent), yk__sdsnewlen("libs", 4));
    yk__sds yy__configuration_l3 = yk__sdsdup(t__19);
    yk__sds t__20 = yy__path_join(yk__sdsdup(yy__configuration_l1), yk__sdsnewlen("libs.yaka", 9));
    if (yy__path_readable(yk__sdsdup(t__20)))
    {
        yy__configuration_c->yy__configuration_libs_path = yk__sdsdup(yy__configuration_l1);
        yk__sdsfree(t__20);
        yk__sdsfree(yy__configuration_l3);
        yk__sdsfree(t__19);
        yk__sdsfree(yy__configuration_l2);
        yk__sdsfree(t__18);
        yk__sdsfree(t__17);
        yk__sdsfree(t__16);
        yk__sdsfree(yy__configuration_l1);
        yk__sdsfree(t__15);
        yk__sdsfree(t__14);
        yk__sdsfree(yy__configuration_exe_parent);
        yk__sdsfree(t__13);
        return;
    }
    yk__sds t__21 = yy__path_join(yk__sdsdup(yy__configuration_l2), yk__sdsnewlen("libs.yaka", 9));
    if (yy__path_readable(yk__sdsdup(t__21)))
    {
        yy__configuration_c->yy__configuration_libs_path = yk__sdsdup(yy__configuration_l2);
        yk__sdsfree(t__21);
        yk__sdsfree(t__20);
        yk__sdsfree(yy__configuration_l3);
        yk__sdsfree(t__19);
        yk__sdsfree(yy__configuration_l2);
        yk__sdsfree(t__18);
        yk__sdsfree(t__17);
        yk__sdsfree(t__16);
        yk__sdsfree(yy__configuration_l1);
        yk__sdsfree(t__15);
        yk__sdsfree(t__14);
        yk__sdsfree(yy__configuration_exe_parent);
        yk__sdsfree(t__13);
        return;
    }
    yk__sds t__22 = yy__path_join(yk__sdsdup(yy__configuration_l3), yk__sdsnewlen("libs.yaka", 9));
    if (yy__path_readable(yk__sdsdup(t__22)))
    {
        yy__configuration_c->yy__configuration_libs_path = yk__sdsdup(yy__configuration_l3);
        yk__sdsfree(t__22);
        yk__sdsfree(t__21);
        yk__sdsfree(t__20);
        yk__sdsfree(yy__configuration_l3);
        yk__sdsfree(t__19);
        yk__sdsfree(yy__configuration_l2);
        yk__sdsfree(t__18);
        yk__sdsfree(t__17);
        yk__sdsfree(t__16);
        yk__sdsfree(yy__configuration_l1);
        yk__sdsfree(t__15);
        yk__sdsfree(t__14);
        yk__sdsfree(yy__configuration_exe_parent);
        yk__sdsfree(t__13);
        return;
    }
    yk__sds t__23 = yk__concat_lit_sds("Failed to find std library in :", 31, yy__configuration_l1);
    yk__arrput(yy__configuration_c->yy__configuration_errors, yk__sdsdup(t__23));
    yk__sds t__24 = yk__concat_lit_sds("Failed to find std library in :", 31, yy__configuration_l2);
    yk__arrput(yy__configuration_c->yy__configuration_errors, yk__sdsdup(t__24));
    yk__sds t__25 = yk__concat_lit_sds("Failed to find std library in :", 31, yy__configuration_l3);
    yk__arrput(yy__configuration_c->yy__configuration_errors, yk__sdsdup(t__25));
    yy__configuration_c->yy__configuration_libs_path = yk__sdsnewlen("<not found>", 11);
    yk__sdsfree(t__25);
    yk__sdsfree(t__24);
    yk__sdsfree(t__23);
    yk__sdsfree(t__22);
    yk__sdsfree(t__21);
    yk__sdsfree(t__20);
    yk__sdsfree(yy__configuration_l3);
    yk__sdsfree(t__19);
    yk__sdsfree(yy__configuration_l2);
    yk__sdsfree(t__18);
    yk__sdsfree(t__17);
    yk__sdsfree(t__16);
    yk__sdsfree(yy__configuration_l1);
    yk__sdsfree(t__15);
    yk__sdsfree(t__14);
    yk__sdsfree(yy__configuration_exe_parent);
    yk__sdsfree(t__13);
    return;
}
void yy__configuration_find_yaksha_compiler(struct yy__configuration_Config* yy__configuration_c) 
{
    yk__sds t__26 = yy__os_exe_path();
    yk__sds yy__configuration_exe_parent = yk__sdsdup(t__26);
    yk__sds t__27 = yy__path_join(yk__sdsdup(yy__configuration_exe_parent), yk__sdsnewlen("yaksha", 6));
    yk__sds yy__configuration_l1 = yk__sdsdup(t__27);
    if (yy__os_is_windows())
    {
        yk__sds t__28 = yk__concat_sds_lit(yy__configuration_l1, ".exe", 4);
        yk__sdsfree(yy__configuration_l1);
        yy__configuration_l1 = yk__sdsdup(t__28);
        yk__sdsfree(t__28);
    }
    yk__sds t__29 = yy__path_dirname(yk__sdsdup(yy__configuration_exe_parent));
    yk__sds t__30 = yy__path_dirname(yk__sdsdup(t__29));
    yk__sds t__31 = yy__path_join(yk__sdsdup(t__30), yk__sdsnewlen("bin", 3));
    yk__sds yy__configuration_l2 = yk__sdsdup(t__31);
    yk__sds t__32 = yy__path_join(yk__sdsdup(yy__configuration_l2), yk__sdsnewlen("yaksha", 6));
    yk__sdsfree(yy__configuration_l2);
    yy__configuration_l2 = yk__sdsdup(t__32);
    if (yy__os_is_windows())
    {
        yk__sds t__33 = yk__concat_sds_lit(yy__configuration_l2, ".exe", 4);
        yk__sdsfree(yy__configuration_l2);
        yy__configuration_l2 = yk__sdsdup(t__33);
        yk__sdsfree(t__33);
    }
    if (yy__path_executable(yk__sdsdup(yy__configuration_l1)))
    {
        yy__configuration_c->yy__configuration_compiler_path = yk__sdsdup(yy__configuration_l1);
        yk__sdsfree(t__32);
        yk__sdsfree(yy__configuration_l2);
        yk__sdsfree(t__31);
        yk__sdsfree(t__30);
        yk__sdsfree(t__29);
        yk__sdsfree(yy__configuration_l1);
        yk__sdsfree(t__27);
        yk__sdsfree(yy__configuration_exe_parent);
        yk__sdsfree(t__26);
        return;
    }
    if (yy__path_executable(yk__sdsdup(yy__configuration_l2)))
    {
        yy__configuration_c->yy__configuration_compiler_path = yk__sdsdup(yy__configuration_l2);
        yk__sdsfree(t__32);
        yk__sdsfree(yy__configuration_l2);
        yk__sdsfree(t__31);
        yk__sdsfree(t__30);
        yk__sdsfree(t__29);
        yk__sdsfree(yy__configuration_l1);
        yk__sdsfree(t__27);
        yk__sdsfree(yy__configuration_exe_parent);
        yk__sdsfree(t__26);
        return;
    }
    yk__sds t__34 = yy__os_which(yk__sdsnewlen("yaksha", 6));
    yk__sds yy__configuration_fallback = yk__sdsdup(t__34);
    if (yk__sdslen(yy__configuration_fallback) > INT32_C(0))
    {
        yy__configuration_c->yy__configuration_compiler_path = yk__sdsdup(yy__configuration_fallback);
        yk__sdsfree(yy__configuration_fallback);
        yk__sdsfree(t__34);
        yk__sdsfree(t__32);
        yk__sdsfree(yy__configuration_l2);
        yk__sdsfree(t__31);
        yk__sdsfree(t__30);
        yk__sdsfree(t__29);
        yk__sdsfree(yy__configuration_l1);
        yk__sdsfree(t__27);
        yk__sdsfree(yy__configuration_exe_parent);
        yk__sdsfree(t__26);
        return;
    }
    yk__sds t__35 = yk__concat_lit_sds("Failed to find yaksha in :", 26, yy__configuration_l1);
    yk__arrput(yy__configuration_c->yy__configuration_errors, yk__sdsdup(t__35));
    yk__sds t__36 = yk__concat_lit_sds("Failed to find yaksha in :", 26, yy__configuration_l2);
    yk__arrput(yy__configuration_c->yy__configuration_errors, yk__sdsdup(t__36));
    yk__arrput(yy__configuration_c->yy__configuration_errors, yk__sdsnewlen("Failed to find yaksha in PATH", 29));
    yy__configuration_c->yy__configuration_compiler_path = yk__sdsnewlen("<not found>", 11);
    yk__sdsfree(t__36);
    yk__sdsfree(t__35);
    yk__sdsfree(yy__configuration_fallback);
    yk__sdsfree(t__34);
    yk__sdsfree(t__32);
    yk__sdsfree(yy__configuration_l2);
    yk__sdsfree(t__31);
    yk__sdsfree(t__30);
    yk__sdsfree(t__29);
    yk__sdsfree(yy__configuration_l1);
    yk__sdsfree(t__27);
    yk__sdsfree(yy__configuration_exe_parent);
    yk__sdsfree(t__26);
    return;
}
void yy__configuration_find_zig_compiler(struct yy__configuration_Config* yy__configuration_c) 
{
    yk__sds t__37 = yy__os_which(yk__sdsnewlen("zig", 3));
    yk__sds yy__configuration_zig = yk__sdsdup(t__37);
    if (yk__sdslen(yy__configuration_zig) > INT32_C(0))
    {
        yy__configuration_c->yy__configuration_zig_compiler_path = yk__sdsdup(yy__configuration_zig);
        yk__sdsfree(yy__configuration_zig);
        yk__sdsfree(t__37);
        return;
    }
    if (yy__configuration_c->yy__configuration_compilation->yy__configuration_wasm4)
    {
        yk__arrput(yy__configuration_c->yy__configuration_errors, yk__sdsnewlen("Failed to find zig in PATH", 26));
        yy__configuration_c->yy__configuration_zig_compiler_path = yk__sdsnewlen("<not found>", 11);
        yk__sdsfree(yy__configuration_zig);
        yk__sdsfree(t__37);
        return;
    }
    yk__sds t__38 = yy__os_which(yk__sdsnewlen("gcc", 3));
    yk__sds yy__configuration_gcc = yk__sdsdup(t__38);
    yk__sds t__39 = yy__os_which(yk__sdsnewlen("clang", 5));
    yk__sds yy__configuration_clang = yk__sdsdup(t__39);
    bool yy__configuration_found_altenative = ((yk__sdslen(yy__configuration_gcc) > INT32_C(0)) || (yk__sdslen(yy__configuration_clang) > INT32_C(0)));
    yy__configuration_c->yy__configuration_alt_compiler = yy__configuration_NOT_FOUND;
    if (yk__sdslen(yy__configuration_gcc) > INT32_C(0))
    {
        yy__configuration_c->yy__configuration_gcc_compiler_path = yk__sdsdup(yy__configuration_gcc);
        yy__configuration_c->yy__configuration_alt_compiler = yy__configuration_GCC;
    }
    else
    {
        yy__configuration_c->yy__configuration_gcc_compiler_path = yk__sdsnewlen("<not found>", 11);
    }
    if (yk__sdslen(yy__configuration_clang) > INT32_C(0))
    {
        yy__configuration_c->yy__configuration_clang_compiler_path = yk__sdsdup(yy__configuration_clang);
        yy__configuration_c->yy__configuration_alt_compiler = yy__configuration_CLANG;
    }
    else
    {
        yy__configuration_c->yy__configuration_clang_compiler_path = yk__sdsnewlen("<not found>", 11);
    }
    if ((!(yy__configuration_c->yy__configuration_compilation->yy__configuration_web)) && !yy__configuration_found_altenative)
    {
        yk__arrput(yy__configuration_c->yy__configuration_errors, yk__sdsnewlen("Failed to find zig/clang/gcc in PATH", 36));
    }
    yy__configuration_c->yy__configuration_zig_compiler_path = yk__sdsnewlen("<not found>", 11);
    yy__configuration_c->yy__configuration_use_alt_compiler = yy__configuration_found_altenative;
    yk__sdsfree(yy__configuration_clang);
    yk__sdsfree(t__39);
    yk__sdsfree(yy__configuration_gcc);
    yk__sdsfree(t__38);
    yk__sdsfree(yy__configuration_zig);
    yk__sdsfree(t__37);
    return;
}
void yy__configuration_find_emsdk(struct yy__configuration_Config* yy__configuration_c) 
{
    yk__sds t__40 = yy__os_which(yk__sdsnewlen("emcc", 4));
    yk__sds yy__configuration_emcc = yk__sdsdup(t__40);
    yk__sds t__41 = yy__os_which(yk__sdsnewlen("emrun", 5));
    yk__sds yy__configuration_emrun = yk__sdsdup(t__41);
    bool yy__configuration_not_found = ((yk__sdslen(yy__configuration_emcc) == INT32_C(0)) || (yk__sdslen(yy__configuration_emrun) == INT32_C(0)));
    if (yy__configuration_c->yy__configuration_compilation->yy__configuration_web && yy__configuration_not_found)
    {
        yk__arrput(yy__configuration_c->yy__configuration_errors, yk__sdsnewlen("Failed to find emsdk (emcc, emrun) in PATH", 42));
        yy__configuration_c->yy__configuration_emcc_compiler_path = yk__sdsnewlen("<not found>", 11);
        yy__configuration_c->yy__configuration_emrun_path = yk__sdsnewlen("<not found>", 11);
    }
    else
    {
        yy__configuration_c->yy__configuration_emcc_compiler_path = yk__sdsdup(yy__configuration_emcc);
        yy__configuration_c->yy__configuration_emrun_path = yk__sdsdup(yy__configuration_emrun);
    }
    yk__sdsfree(yy__configuration_emrun);
    yk__sdsfree(t__41);
    yk__sdsfree(yy__configuration_emcc);
    yk__sdsfree(t__40);
    return;
}
void yy__configuration_find_w4(struct yy__configuration_Config* yy__configuration_c) 
{
    yk__sds t__42 = yy__os_which(yk__sdsnewlen("w4", 2));
    yk__sds yy__configuration_w4 = yk__sdsdup(t__42);
    bool yy__configuration_not_found = (yk__sdslen(yy__configuration_w4) == INT32_C(0));
    if (yy__configuration_c->yy__configuration_compilation->yy__configuration_wasm4 && yy__configuration_not_found)
    {
        yk__arrput(yy__configuration_c->yy__configuration_errors, yk__sdsnewlen("Failed to find w4 in PATH", 25));
        yy__configuration_c->yy__configuration_w4_path = yk__sdsnewlen("<not found>", 11);
    }
    else
    {
        yy__configuration_c->yy__configuration_w4_path = yk__sdsdup(yy__configuration_w4);
    }
    yk__sdsfree(yy__configuration_w4);
    yk__sdsfree(t__42);
    return;
}
struct yy__configuration_Project* yy__configuration_load_project(yy__toml_Table yy__configuration_conf, struct yy__configuration_Config* yy__configuration_c) 
{
    struct yy__configuration_Project* yy__configuration_p = calloc(1, sizeof(struct yy__configuration_Project));
    yy__toml_Table yy__configuration_project = yy__toml_get_table(yy__configuration_conf, yk__sdsnewlen("project", 7));
    if (!(yy__toml_valid_table(yy__configuration_project)))
    {
        yk__arrput(yy__configuration_c->yy__configuration_errors, yk__sdsnewlen("Failed to read \'[project]\'", 26));
        struct yy__configuration_Project* t__43 = yy__configuration_p;
        return t__43;
    }
    yk__sds t__44 = yy__toml_get_string(yy__configuration_project, yk__sdsnewlen("main", 4));
    yk__sds yy__configuration_main_code_file = yk__sdsdup(t__44);
    yk__sds t__45 = yy__toml_get_string(yy__configuration_project, yk__sdsnewlen("name", 4));
    yk__sds yy__configuration_project_name = yk__sdsdup(t__45);
    yk__sds t__46 = yy__toml_get_string(yy__configuration_project, yk__sdsnewlen("author", 6));
    yk__sds yy__configuration_project_author = yk__sdsdup(t__46);
    if (yk__cmp_sds_lit(yy__configuration_main_code_file, "", 0) == 0)
    {
        yk__arrput(yy__configuration_c->yy__configuration_errors, yk__sdsnewlen("Invalid \'[project].main\'", 24));
    }
    if (yk__cmp_sds_lit(yy__configuration_project_name, "", 0) == 0)
    {
        yk__arrput(yy__configuration_c->yy__configuration_errors, yk__sdsnewlen("Invalid \'[project].name\'", 24));
    }
    if (yk__cmp_sds_lit(yy__configuration_project_author, "", 0) == 0)
    {
        yk__arrput(yy__configuration_c->yy__configuration_errors, yk__sdsnewlen("Invalid \'[project].author\'", 26));
    }
    yy__configuration_p->yy__configuration_main = yk__sdsdup(yy__configuration_main_code_file);
    yy__configuration_p->yy__configuration_author = yk__sdsdup(yy__configuration_project_author);
    yy__configuration_p->yy__configuration_name = yk__sdsdup(yy__configuration_project_name);
    struct yy__configuration_Project* t__47 = yy__configuration_p;
    yk__sdsfree(yy__configuration_project_author);
    yk__sdsfree(t__46);
    yk__sdsfree(yy__configuration_project_name);
    yk__sdsfree(t__45);
    yk__sdsfree(yy__configuration_main_code_file);
    yk__sdsfree(t__44);
    return t__47;
}
struct yy__configuration_CCode* yy__configuration_load_c_code(yy__toml_Table yy__configuration_conf, struct yy__configuration_Config* yy__configuration_c) 
{
    struct yy__configuration_CCode* yy__configuration_cc = calloc(1, sizeof(struct yy__configuration_CCode));
    yy__toml_Table yy__configuration_cc_data = yy__toml_get_table(yy__configuration_conf, yk__sdsnewlen("ccode", 5));
    if (!(yy__toml_valid_table(yy__configuration_cc_data)))
    {
        struct yy__configuration_CCode* t__48 = yy__configuration_cc;
        return t__48;
    }
    yy__configuration_cc->yy__configuration_include_paths = yy__toml_get_string_array(yy__configuration_cc_data, yk__sdsnewlen("include_paths", 13));
    yy__configuration_cc->yy__configuration_defines = yy__toml_get_string_array(yy__configuration_cc_data, yk__sdsnewlen("defines", 7));
    yy__configuration_cc->yy__configuration_compiler_defines = yy__toml_get_string_array(yy__configuration_cc_data, yk__sdsnewlen("compiler_defines", 16));
    yy__configuration_cc->yy__configuration_includes = yy__toml_get_string_array(yy__configuration_cc_data, yk__sdsnewlen("includes", 8));
    yy__configuration_cc->yy__configuration_system_includes = yy__toml_get_string_array(yy__configuration_cc_data, yk__sdsnewlen("system_includes", 15));
    yy__configuration_cc->yy__configuration_c_code = yy__toml_get_string_array(yy__configuration_cc_data, yk__sdsnewlen("c_code", 6));
    yy__configuration_cc->yy__configuration_cpp_code = yy__toml_get_string_array(yy__configuration_cc_data, yk__sdsnewlen("cpp_code", 8));
    struct yy__configuration_CCode* t__49 = yy__configuration_cc;
    return t__49;
}
struct yy__configuration_Compilation* yy__configuration_load_compilation(yy__toml_Table yy__configuration_conf, struct yy__configuration_Config* yy__configuration_c) 
{
    struct yy__configuration_Compilation* yy__configuration_co = calloc(1, sizeof(struct yy__configuration_Compilation));
    yy__toml_Table yy__configuration_co_data = yy__toml_get_table(yy__configuration_conf, yk__sdsnewlen("compilation", 11));
    if (!(yy__toml_valid_table(yy__configuration_co_data)))
    {
        struct yy__configuration_Compilation* t__50 = yy__configuration_co;
        return t__50;
    }
    yy__configuration_co->yy__configuration_targets = yy__toml_get_string_array(yy__configuration_co_data, yk__sdsnewlen("targets", 7));
    yy__configuration_co->yy__configuration_raylib = yy__toml_get_bool_default(yy__configuration_co_data, yk__sdsnewlen("raylib", 6), false);
    yy__configuration_co->yy__configuration_raylib_hot_reloading_dll = yy__toml_get_bool_default(yy__configuration_co_data, yk__sdsnewlen("raylib_hot_reloading_dll", 24), false);
    yy__configuration_co->yy__configuration_disable_parallel_build = yy__toml_get_bool_default(yy__configuration_co_data, yk__sdsnewlen("disable_parallel_build", 22), false);
    yy__configuration_co->yy__configuration_web = yy__toml_get_bool_default(yy__configuration_co_data, yk__sdsnewlen("web", 3), false);
    yy__configuration_co->yy__configuration_wasm4 = yy__toml_get_bool_default(yy__configuration_co_data, yk__sdsnewlen("wasm4", 5), false);
    yk__sds t__51 = yy__toml_get_string(yy__configuration_co_data, yk__sdsnewlen("web_shell", 9));
    yy__configuration_co->yy__configuration_web_shell = yk__sdsdup(t__51);
    yk__sds t__52 = yy__toml_get_string(yy__configuration_co_data, yk__sdsnewlen("web_assets", 10));
    yy__configuration_co->yy__configuration_web_assets = yk__sdsdup(t__52);
    struct yy__configuration_Compilation* t__53 = yy__configuration_co;
    yk__sdsfree(t__52);
    yk__sdsfree(t__51);
    return t__53;
}
struct yy__configuration_CCode* yy__configuration_inject_c_code_defaults(struct yy__configuration_CCode* yy__configuration_cc, struct yy__configuration_Config* yy__configuration_c) 
{
    yk__sds t__54 = yy__os_cwd();
    yk__sds t__55 = yy__path_dirname(yk__sdsdup(t__54));
    yk__sds yy__configuration_current_dir = yk__sdsdup(t__55);
    yk__sds t__56 = yy__path_join(yk__sdsdup(yy__configuration_current_dir), yk__sdsnewlen("build", 5));
    yk__sds* t__57 = NULL;
    yk__arrsetcap(t__57, 2);
    yk__arrput(t__57, yk__sdsdup(yy__configuration_c->yy__configuration_runtime_path));
    yk__arrput(t__57, yk__sdsdup(t__56));
    yk__sds* yy__configuration_df_include_paths = t__57;
    yk__sds* yy__configuration_orig_include_paths = yy__configuration_cc->yy__configuration_include_paths;
    yy__configuration_cc->yy__configuration_include_paths = yy__array_extend(yy__configuration_df_include_paths, yy__configuration_cc->yy__configuration_include_paths);
    yk__sds* t__58 = NULL;
    yk__arrsetcap(t__58, 1);
    yk__arrput(t__58, yk__sdsnewlen("yk__system.h", 12));
    yy__configuration_cc->yy__configuration_runtime_feature_includes = t__58;
    yk__sds t__59 = yy__path_join(yk__sdsdup(yy__configuration_c->yy__configuration_runtime_path), yk__sdsnewlen("yk__system.c", 12));
    yk__sds* t__60 = NULL;
    yk__arrsetcap(t__60, 1);
    yk__arrput(t__60, yk__sdsdup(t__59));
    yy__configuration_cc->yy__configuration_runtime_feature_c_code = t__60;
    struct yy__configuration_CCode* t__61 = yy__configuration_cc;
    yy__array_del_str_array(yy__configuration_orig_include_paths);
    yk__sdsfree(t__59);
    yk__sdsfree(t__56);
    yk__sdsfree(yy__configuration_current_dir);
    yk__sdsfree(t__55);
    yk__sdsfree(t__54);
    return t__61;
}
struct yy__configuration_Config* yy__configuration_load_runtime_features(struct yy__configuration_Config* yy__configuration_c, yk__sds yy__configuration_code, bool yy__configuration_silent) 
{
    yk__sds yy__configuration_header = yk__sdsnewlen("// YK:" , 6);
    bool yy__configuration_has_requirements = yy__strings_startswith(yk__sdsdup(yy__configuration_code), yk__sdsdup(yy__configuration_header));
    if (!yy__configuration_has_requirements)
    {
        if (!yy__configuration_silent)
        {
            yy__console_cyan(yk__bstr_s("runtime_features", 16));
            yy__console_red(yk__bstr_s(" := ", 4));
            yy__console_green(yk__bstr_s("none!", 5));
            yk__printstr("\n");
        }
        struct yy__configuration_Config* t__62 = yy__configuration_c;
        yk__sdsfree(yy__configuration_header);
        yk__sdsfree(yy__configuration_code);
        return t__62;
    }
    int32_t yy__configuration_until = yy__strings_find_char(yk__sdsdup(yy__configuration_code), yy__strings_ord(yk__sdsnewlen("#", 1)));
    if (yy__configuration_until == (-(INT32_C(1))))
    {
        yk__arrput(yy__configuration_c->yy__configuration_errors, yk__sdsnewlen("Failed to extract runtime features. Cannot find # in compiled code first line.", 78));
        struct yy__configuration_Config* t__63 = yy__configuration_c;
        yk__sdsfree(yy__configuration_header);
        yk__sdsfree(yy__configuration_code);
        return t__63;
    }
    yk__sds t__64 = yy__strings_mid(yk__sdsdup(yy__configuration_code), yk__sdslen(yy__configuration_header), (yy__configuration_until - yk__sdslen(yy__configuration_header)));
    yk__sds yy__configuration_temp_features = yk__sdsdup(t__64);
    if (!yy__configuration_silent)
    {
        yy__console_cyan(yk__bstr_s("runtime_features", 16));
        yy__console_red(yk__bstr_s(" := ", 4));
        yy__console_green(yk__bstr_h(yy__configuration_temp_features));
        yk__printstr("\n");
    }
    yk__sds* yy__configuration_features = yy__strings_split(yk__sdsdup(yy__configuration_temp_features), yk__sdsnewlen(",", 1));
    int32_t yy__configuration_x = INT32_C(0);
    int32_t yy__configuration_length = yk__arrlen(yy__configuration_features);
    while (true)
    {
        if (!(yy__configuration_x < yy__configuration_length))
        {
            break;
        }
        yk__sds yy__configuration_feature = yk__sdsdup(yy__configuration_features[yy__configuration_x]);
        yy__configuration_x = (yy__configuration_x + INT32_C(1));
        if (yk__cmp_sds_lit(yy__configuration_feature, "wasm4", 5) == 0)
        {
            yk__arrput(yy__configuration_c->yy__configuration_c_code->yy__configuration_runtime_feature_includes, yk__sdsnewlen("wasm4.h", 7));
            yk__arrput(yy__configuration_c->yy__configuration_c_code->yy__configuration_runtime_feature_includes, yk__sdsnewlen("yk__wasm4_libc.h", 16));
            yk__sds t__65 = yy__path_join(yk__sdsdup(yy__configuration_c->yy__configuration_runtime_path), yk__sdsnewlen("yk__wasm4_libc.c", 16));
            yk__arrput(yy__configuration_c->yy__configuration_c_code->yy__configuration_runtime_feature_c_code, yk__sdsdup(t__65));
            yk__arrput(yy__configuration_c->yy__configuration_c_code->yy__configuration_runtime_feature_compiler_defines, yk__sdsnewlen("YK__WASM4", 9));
            if (!(yy__configuration_c->yy__configuration_compilation->yy__configuration_wasm4))
            {
                yk__arrput(yy__configuration_c->yy__configuration_errors, yk__sdsnewlen("wasm4 feature used without configuring it", 41));
            }
            yk__sdsfree(t__65);
            yk__sdsfree(yy__configuration_feature);
            continue;
            yk__sdsfree(t__65);
        }
        if (yk__cmp_sds_lit(yy__configuration_feature, "argparse", 8) == 0)
        {
            yk__sds t__66 = yy__path_join(yk__sdsdup(yy__configuration_c->yy__configuration_runtime_path), yk__sdsnewlen("yk__argparse.c", 14));
            yk__arrput(yy__configuration_c->yy__configuration_c_code->yy__configuration_runtime_feature_c_code, yk__sdsdup(t__66));
            yk__sds t__67 = yy__path_join(yk__sdsdup(yy__configuration_c->yy__configuration_runtime_path), yk__sdsnewlen("argparse.c", 10));
            yk__arrput(yy__configuration_c->yy__configuration_c_code->yy__configuration_runtime_feature_c_code, yk__sdsdup(t__67));
            yk__arrput(yy__configuration_c->yy__configuration_c_code->yy__configuration_runtime_feature_includes, yk__sdsnewlen("yk__argparse.h", 14));
            yk__arrput(yy__configuration_c->yy__configuration_c_code->yy__configuration_runtime_feature_includes, yk__sdsnewlen("argparse.h", 10));
            yk__sdsfree(t__67);
            yk__sdsfree(t__66);
            yk__sdsfree(yy__configuration_feature);
            continue;
            yk__sdsfree(t__67);
            yk__sdsfree(t__66);
        }
        if (yk__cmp_sds_lit(yy__configuration_feature, "arrayutils", 10) == 0)
        {
            yk__sds t__68 = yy__path_join(yk__sdsdup(yy__configuration_c->yy__configuration_runtime_path), yk__sdsnewlen("yk__arrayutils.c", 16));
            yk__arrput(yy__configuration_c->yy__configuration_c_code->yy__configuration_runtime_feature_c_code, yk__sdsdup(t__68));
            yk__arrput(yy__configuration_c->yy__configuration_c_code->yy__configuration_runtime_feature_includes, yk__sdsnewlen("yk__arrayutils.h", 16));
            yk__sdsfree(t__68);
            yk__sdsfree(yy__configuration_feature);
            continue;
            yk__sdsfree(t__68);
        }
        if (yk__cmp_sds_lit(yy__configuration_feature, "console", 7) == 0)
        {
            yk__sds t__69 = yy__path_join(yk__sdsdup(yy__configuration_c->yy__configuration_runtime_path), yk__sdsnewlen("yk__console.c", 13));
            yk__arrput(yy__configuration_c->yy__configuration_c_code->yy__configuration_runtime_feature_c_code, yk__sdsdup(t__69));
            yk__arrput(yy__configuration_c->yy__configuration_c_code->yy__configuration_runtime_feature_includes, yk__sdsnewlen("yk__console.h", 13));
            yk__sdsfree(t__69);
            yk__sdsfree(yy__configuration_feature);
            continue;
            yk__sdsfree(t__69);
        }
        if (yk__cmp_sds_lit(yy__configuration_feature, "graphicutils", 12) == 0)
        {
            yk__sds t__70 = yy__path_join(yk__sdsdup(yy__configuration_c->yy__configuration_runtime_path), yk__sdsnewlen("yk__graphic_utils.c", 19));
            yk__arrput(yy__configuration_c->yy__configuration_c_code->yy__configuration_runtime_feature_c_code, yk__sdsdup(t__70));
            yk__arrput(yy__configuration_c->yy__configuration_c_code->yy__configuration_runtime_feature_includes, yk__sdsnewlen("yk__graphic_utils.h", 19));
            yk__sdsfree(t__70);
            yk__sdsfree(yy__configuration_feature);
            continue;
            yk__sdsfree(t__70);
        }
        if (yk__cmp_sds_lit(yy__configuration_feature, "ini", 3) == 0)
        {
            yk__arrput(yy__configuration_c->yy__configuration_c_code->yy__configuration_runtime_feature_defines, yk__sdsnewlen("INI_IMPLEMENTATION", 18));
            yk__arrput(yy__configuration_c->yy__configuration_c_code->yy__configuration_runtime_feature_includes, yk__sdsnewlen("ini.h", 5));
            yk__sdsfree(yy__configuration_feature);
            continue;
        }
        if (yk__cmp_sds_lit(yy__configuration_feature, "process", 7) == 0)
        {
            yk__sds t__71 = yy__path_join(yk__sdsdup(yy__configuration_c->yy__configuration_runtime_path), yk__sdsnewlen("yk__process.c", 13));
            yk__arrput(yy__configuration_c->yy__configuration_c_code->yy__configuration_runtime_feature_c_code, yk__sdsdup(t__71));
            yk__arrput(yy__configuration_c->yy__configuration_c_code->yy__configuration_runtime_feature_includes, yk__sdsnewlen("yk__process.h", 13));
            yk__sdsfree(t__71);
            yk__sdsfree(yy__configuration_feature);
            continue;
            yk__sdsfree(t__71);
        }
        if (yk__cmp_sds_lit(yy__configuration_feature, "cpu", 3) == 0)
        {
            yk__sds t__72 = yy__path_join(yk__sdsdup(yy__configuration_c->yy__configuration_runtime_path), yk__sdsnewlen("yk__cpu.c", 9));
            yk__arrput(yy__configuration_c->yy__configuration_c_code->yy__configuration_runtime_feature_c_code, yk__sdsdup(t__72));
            yk__arrput(yy__configuration_c->yy__configuration_c_code->yy__configuration_runtime_feature_includes, yk__sdsnewlen("yk__cpu.h", 9));
            yk__sdsfree(t__72);
            yk__sdsfree(yy__configuration_feature);
            continue;
            yk__sdsfree(t__72);
        }
        if (yk__cmp_sds_lit(yy__configuration_feature, "raylib", 6) == 0)
        {
            if (!(yy__configuration_c->yy__configuration_compilation->yy__configuration_raylib))
            {
                yk__arrput(yy__configuration_c->yy__configuration_errors, yk__sdsnewlen("raylib feature used without configuring it", 42));
            }
            yk__sdsfree(yy__configuration_feature);
            continue;
        }
        if (yk__cmp_sds_lit(yy__configuration_feature, "tinycthread", 11) == 0)
        {
            yk__sds t__73 = yy__path_join(yk__sdsdup(yy__configuration_c->yy__configuration_runtime_path), yk__sdsnewlen("tinycthread.c", 13));
            yk__arrput(yy__configuration_c->yy__configuration_c_code->yy__configuration_runtime_feature_c_code, yk__sdsdup(t__73));
            yk__arrput(yy__configuration_c->yy__configuration_c_code->yy__configuration_runtime_feature_includes, yk__sdsnewlen("tinycthread.h", 13));
            yk__sdsfree(t__73);
            yk__sdsfree(yy__configuration_feature);
            continue;
            yk__sdsfree(t__73);
        }
        if (yk__cmp_sds_lit(yy__configuration_feature, "toml", 4) == 0)
        {
            yk__sds t__74 = yy__path_join(yk__sdsdup(yy__configuration_c->yy__configuration_runtime_path), yk__sdsnewlen("toml.c", 6));
            yk__arrput(yy__configuration_c->yy__configuration_c_code->yy__configuration_runtime_feature_c_code, yk__sdsdup(t__74));
            yk__arrput(yy__configuration_c->yy__configuration_c_code->yy__configuration_runtime_feature_includes, yk__sdsnewlen("toml.h", 6));
            yk__sdsfree(t__74);
            yk__sdsfree(yy__configuration_feature);
            continue;
            yk__sdsfree(t__74);
        }
        if (yk__cmp_sds_lit(yy__configuration_feature, "utf8proc", 8) == 0)
        {
            yk__sds t__75 = yy__path_join(yk__sdsdup(yy__configuration_c->yy__configuration_runtime_path), yk__sdsnewlen("utf8proc.c", 10));
            yk__arrput(yy__configuration_c->yy__configuration_c_code->yy__configuration_runtime_feature_c_code, yk__sdsdup(t__75));
            yk__arrput(yy__configuration_c->yy__configuration_c_code->yy__configuration_runtime_feature_compiler_defines, yk__sdsnewlen("UTF8PROC_STATIC", 15));
            yk__arrput(yy__configuration_c->yy__configuration_c_code->yy__configuration_runtime_feature_includes, yk__sdsnewlen("utf8proc.h", 10));
            yk__arrput(yy__configuration_c->yy__configuration_c_code->yy__configuration_runtime_feature_includes, yk__sdsnewlen("yk__utf8iter.h", 14));
            yk__sdsfree(t__75);
            yk__sdsfree(yy__configuration_feature);
            continue;
            yk__sdsfree(t__75);
        }
        if (yk__cmp_sds_lit(yy__configuration_feature, "whereami", 8) == 0)
        {
            if (yy__configuration_c->yy__configuration_compilation->yy__configuration_web)
            {
                yk__sds t__76 = yy__path_join(yk__sdsdup(yy__configuration_c->yy__configuration_runtime_path), yk__sdsnewlen("yk__fake_whereami.c", 19));
                yk__arrput(yy__configuration_c->yy__configuration_c_code->yy__configuration_runtime_feature_c_code, yk__sdsdup(t__76));
                yk__sdsfree(t__76);
            }
            else
            {
                yk__sds t__77 = yy__path_join(yk__sdsdup(yy__configuration_c->yy__configuration_runtime_path), yk__sdsnewlen("whereami.c", 10));
                yk__arrput(yy__configuration_c->yy__configuration_c_code->yy__configuration_runtime_feature_c_code, yk__sdsdup(t__77));
                yk__sdsfree(t__77);
            }
            yk__arrput(yy__configuration_c->yy__configuration_c_code->yy__configuration_runtime_feature_includes, yk__sdsnewlen("whereami.h", 10));
            yk__sdsfree(yy__configuration_feature);
            continue;
        }
        yk__sds t__78 = yk__concat_lit_sds("Invalid runtime feature: ", 25, yy__configuration_feature);
        yk__arrput(yy__configuration_c->yy__configuration_errors, yk__sdsdup(t__78));
        yk__sdsfree(t__78);
        yk__sdsfree(yy__configuration_feature);
        break;
        yk__sdsfree(t__78);
        yk__sdsfree(yy__configuration_feature);
    }
    struct yy__configuration_Config* t__79 = yy__configuration_c;
    yy__array_del_str_array(yy__configuration_features);
    yk__sdsfree(yy__configuration_temp_features);
    yk__sdsfree(t__64);
    yk__sdsfree(yy__configuration_header);
    yk__sdsfree(yy__configuration_code);
    return t__79;
}
struct yy__configuration_Config* yy__configuration_load_config() 
{
    struct yy__configuration_Config* yy__configuration_c = calloc(1, sizeof(struct yy__configuration_Config));
    yk__sds t__80 = yy__os_cwd();
    yk__sds t__81 = yy__path_join(yk__sdsdup(t__80), yk__sdsnewlen("yaksha.toml", 11));
    yk__sds yy__configuration_configf = yk__sdsdup(t__81);
    yk__sds t__82 = yy__io_readfile(yk__sdsdup(yy__configuration_configf));
    yk__sds yy__configuration_config_text = yk__sdsdup(t__82);
    yy__toml_Table yy__configuration_conf = yy__toml_from_str(yk__sdsdup(yy__configuration_config_text));
    if (!(yy__toml_valid_table(yy__configuration_conf)))
    {
        yk__arrput(yy__configuration_c->yy__configuration_errors, yk__sdsnewlen("Failed to read config file", 26));
        struct yy__configuration_Config* t__83 = yy__configuration_c;
        yk__sdsfree(yy__configuration_config_text);
        yk__sdsfree(t__82);
        yk__sdsfree(yy__configuration_configf);
        yk__sdsfree(t__81);
        yk__sdsfree(t__80);
        return t__83;
    }
    yy__configuration_c->yy__configuration_compilation = yy__configuration_load_compilation(yy__configuration_conf, yy__configuration_c);
    yy__configuration_find_yaksha_compiler(yy__configuration_c);
    if (yk__arrlen(yy__configuration_c->yy__configuration_errors) > INT32_C(0))
    {
        struct yy__configuration_Config* t__84 = yy__configuration_c;
        yy__toml_del_table(yy__configuration_conf);
        yk__sdsfree(yy__configuration_config_text);
        yk__sdsfree(t__82);
        yk__sdsfree(yy__configuration_configf);
        yk__sdsfree(t__81);
        yk__sdsfree(t__80);
        return t__84;
    }
    yy__configuration_find_zig_compiler(yy__configuration_c);
    if (yk__arrlen(yy__configuration_c->yy__configuration_errors) > INT32_C(0))
    {
        struct yy__configuration_Config* t__85 = yy__configuration_c;
        yy__toml_del_table(yy__configuration_conf);
        yk__sdsfree(yy__configuration_config_text);
        yk__sdsfree(t__82);
        yk__sdsfree(yy__configuration_configf);
        yk__sdsfree(t__81);
        yk__sdsfree(t__80);
        return t__85;
    }
    yy__configuration_find_emsdk(yy__configuration_c);
    if (yk__arrlen(yy__configuration_c->yy__configuration_errors) > INT32_C(0))
    {
        struct yy__configuration_Config* t__86 = yy__configuration_c;
        yy__toml_del_table(yy__configuration_conf);
        yk__sdsfree(yy__configuration_config_text);
        yk__sdsfree(t__82);
        yk__sdsfree(yy__configuration_configf);
        yk__sdsfree(t__81);
        yk__sdsfree(t__80);
        return t__86;
    }
    yy__configuration_find_w4(yy__configuration_c);
    if (yk__arrlen(yy__configuration_c->yy__configuration_errors) > INT32_C(0))
    {
        struct yy__configuration_Config* t__87 = yy__configuration_c;
        yy__toml_del_table(yy__configuration_conf);
        yk__sdsfree(yy__configuration_config_text);
        yk__sdsfree(t__82);
        yk__sdsfree(yy__configuration_configf);
        yk__sdsfree(t__81);
        yk__sdsfree(t__80);
        return t__87;
    }
    yy__configuration_find_runtime_path(yy__configuration_c);
    if (yk__arrlen(yy__configuration_c->yy__configuration_errors) > INT32_C(0))
    {
        struct yy__configuration_Config* t__88 = yy__configuration_c;
        yy__toml_del_table(yy__configuration_conf);
        yk__sdsfree(yy__configuration_config_text);
        yk__sdsfree(t__82);
        yk__sdsfree(yy__configuration_configf);
        yk__sdsfree(t__81);
        yk__sdsfree(t__80);
        return t__88;
    }
    yy__configuration_find_libs_path(yy__configuration_c);
    if (yk__arrlen(yy__configuration_c->yy__configuration_errors) > INT32_C(0))
    {
        struct yy__configuration_Config* t__89 = yy__configuration_c;
        yy__toml_del_table(yy__configuration_conf);
        yk__sdsfree(yy__configuration_config_text);
        yk__sdsfree(t__82);
        yk__sdsfree(yy__configuration_configf);
        yk__sdsfree(t__81);
        yk__sdsfree(t__80);
        return t__89;
    }
    yy__configuration_c->yy__configuration_project = yy__configuration_load_project(yy__configuration_conf, yy__configuration_c);
    if (yk__arrlen(yy__configuration_c->yy__configuration_errors) > INT32_C(0))
    {
        struct yy__configuration_Config* t__90 = yy__configuration_c;
        yy__toml_del_table(yy__configuration_conf);
        yk__sdsfree(yy__configuration_config_text);
        yk__sdsfree(t__82);
        yk__sdsfree(yy__configuration_configf);
        yk__sdsfree(t__81);
        yk__sdsfree(t__80);
        return t__90;
    }
    if (!(yy__path_exists(yk__sdsdup(yy__configuration_c->yy__configuration_project->yy__configuration_main))))
    {
        yk__arrput(yy__configuration_c->yy__configuration_errors, yk__sdsnewlen("Project main file not found", 27));
        struct yy__configuration_Config* t__91 = yy__configuration_c;
        yy__toml_del_table(yy__configuration_conf);
        yk__sdsfree(yy__configuration_config_text);
        yk__sdsfree(t__82);
        yk__sdsfree(yy__configuration_configf);
        yk__sdsfree(t__81);
        yk__sdsfree(t__80);
        return t__91;
    }
    yy__configuration_c->yy__configuration_c_code = yy__configuration_inject_c_code_defaults(yy__configuration_load_c_code(yy__configuration_conf, yy__configuration_c), yy__configuration_c);
    if (yk__arrlen(yy__configuration_c->yy__configuration_errors) > INT32_C(0))
    {
        struct yy__configuration_Config* t__92 = yy__configuration_c;
        yy__toml_del_table(yy__configuration_conf);
        yk__sdsfree(yy__configuration_config_text);
        yk__sdsfree(t__82);
        yk__sdsfree(yy__configuration_configf);
        yk__sdsfree(t__81);
        yk__sdsfree(t__80);
        return t__92;
    }
    struct yy__configuration_Config* t__93 = yy__configuration_c;
    yy__toml_del_table(yy__configuration_conf);
    yk__sdsfree(yy__configuration_config_text);
    yk__sdsfree(t__82);
    yk__sdsfree(yy__configuration_configf);
    yk__sdsfree(t__81);
    yk__sdsfree(t__80);
    return t__93;
}
struct yy__configuration_Config* yy__configuration_create_adhoc_config(yk__sds yy__configuration_name, yk__sds yy__configuration_file_path, bool yy__configuration_use_raylib, bool yy__configuration_use_web, bool yy__configuration_wasm4, yk__sds yy__configuration_web_shell, yk__sds yy__configuration_web_assets, bool yy__configuration_crdll, bool yy__configuration_no_parallel) 
{
    struct yy__configuration_Config* yy__configuration_c = calloc(1, sizeof(struct yy__configuration_Config));
    yy__configuration_c->yy__configuration_compilation = calloc(1, sizeof(struct yy__configuration_Compilation));
    yk__sds* t__94 = NULL;
    yk__arrsetcap(t__94, 1);
    yk__arrput(t__94, yk__sdsnewlen("native", 6));
    yy__configuration_c->yy__configuration_compilation->yy__configuration_targets = t__94;
    yy__configuration_c->yy__configuration_compilation->yy__configuration_raylib = yy__configuration_use_raylib;
    yy__configuration_c->yy__configuration_compilation->yy__configuration_raylib_hot_reloading_dll = yy__configuration_crdll;
    yy__configuration_c->yy__configuration_compilation->yy__configuration_web = yy__configuration_use_web;
    yy__configuration_c->yy__configuration_compilation->yy__configuration_web_shell = yk__sdsdup(yy__configuration_web_shell);
    yy__configuration_c->yy__configuration_compilation->yy__configuration_web_assets = yk__sdsdup(yy__configuration_web_assets);
    yy__configuration_c->yy__configuration_compilation->yy__configuration_wasm4 = yy__configuration_wasm4;
    yy__configuration_c->yy__configuration_compilation->yy__configuration_disable_parallel_build = yy__configuration_no_parallel;
    yy__configuration_find_yaksha_compiler(yy__configuration_c);
    if (yk__arrlen(yy__configuration_c->yy__configuration_errors) > INT32_C(0))
    {
        struct yy__configuration_Config* t__95 = yy__configuration_c;
        yk__sdsfree(yy__configuration_web_assets);
        yk__sdsfree(yy__configuration_web_shell);
        yk__sdsfree(yy__configuration_file_path);
        yk__sdsfree(yy__configuration_name);
        return t__95;
    }
    yy__configuration_find_zig_compiler(yy__configuration_c);
    if (yk__arrlen(yy__configuration_c->yy__configuration_errors) > INT32_C(0))
    {
        struct yy__configuration_Config* t__96 = yy__configuration_c;
        yk__sdsfree(yy__configuration_web_assets);
        yk__sdsfree(yy__configuration_web_shell);
        yk__sdsfree(yy__configuration_file_path);
        yk__sdsfree(yy__configuration_name);
        return t__96;
    }
    yy__configuration_find_emsdk(yy__configuration_c);
    if (yk__arrlen(yy__configuration_c->yy__configuration_errors) > INT32_C(0))
    {
        struct yy__configuration_Config* t__97 = yy__configuration_c;
        yk__sdsfree(yy__configuration_web_assets);
        yk__sdsfree(yy__configuration_web_shell);
        yk__sdsfree(yy__configuration_file_path);
        yk__sdsfree(yy__configuration_name);
        return t__97;
    }
    yy__configuration_find_w4(yy__configuration_c);
    if (yk__arrlen(yy__configuration_c->yy__configuration_errors) > INT32_C(0))
    {
        struct yy__configuration_Config* t__98 = yy__configuration_c;
        yk__sdsfree(yy__configuration_web_assets);
        yk__sdsfree(yy__configuration_web_shell);
        yk__sdsfree(yy__configuration_file_path);
        yk__sdsfree(yy__configuration_name);
        return t__98;
    }
    yy__configuration_find_runtime_path(yy__configuration_c);
    if (yk__arrlen(yy__configuration_c->yy__configuration_errors) > INT32_C(0))
    {
        struct yy__configuration_Config* t__99 = yy__configuration_c;
        yk__sdsfree(yy__configuration_web_assets);
        yk__sdsfree(yy__configuration_web_shell);
        yk__sdsfree(yy__configuration_file_path);
        yk__sdsfree(yy__configuration_name);
        return t__99;
    }
    yy__configuration_find_libs_path(yy__configuration_c);
    if (yk__arrlen(yy__configuration_c->yy__configuration_errors) > INT32_C(0))
    {
        struct yy__configuration_Config* t__100 = yy__configuration_c;
        yk__sdsfree(yy__configuration_web_assets);
        yk__sdsfree(yy__configuration_web_shell);
        yk__sdsfree(yy__configuration_file_path);
        yk__sdsfree(yy__configuration_name);
        return t__100;
    }
    yy__configuration_c->yy__configuration_project = calloc(1, sizeof(struct yy__configuration_Project));
    yy__configuration_c->yy__configuration_project->yy__configuration_main = yk__sdsdup(yy__configuration_file_path);
    yy__configuration_c->yy__configuration_project->yy__configuration_author = yk__sdsnewlen("unknown", 7);
    yy__configuration_c->yy__configuration_project->yy__configuration_name = yk__sdsdup(yy__configuration_name);
    yy__configuration_c->yy__configuration_c_code = yy__configuration_inject_c_code_defaults(calloc(1, sizeof(struct yy__configuration_CCode)), yy__configuration_c);
    if (yk__arrlen(yy__configuration_c->yy__configuration_errors) > INT32_C(0))
    {
        struct yy__configuration_Config* t__101 = yy__configuration_c;
        yk__sdsfree(yy__configuration_web_assets);
        yk__sdsfree(yy__configuration_web_shell);
        yk__sdsfree(yy__configuration_file_path);
        yk__sdsfree(yy__configuration_name);
        return t__101;
    }
    struct yy__configuration_Config* t__102 = yy__configuration_c;
    yk__sdsfree(yy__configuration_web_assets);
    yk__sdsfree(yy__configuration_web_shell);
    yk__sdsfree(yy__configuration_file_path);
    yk__sdsfree(yy__configuration_name);
    return t__102;
}
void yy__configuration_del_config(struct yy__configuration_Config* yy__configuration_c) 
{
    if (yy__configuration_c->yy__configuration_c_code != NULL)
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
    if (yy__configuration_c->yy__configuration_compilation != NULL)
    {
        yy__array_del_str_array(yy__configuration_c->yy__configuration_compilation->yy__configuration_targets);
        yk__sdsfree(yy__configuration_c->yy__configuration_compilation->yy__configuration_libc);
        yk__sdsfree(yy__configuration_c->yy__configuration_compilation->yy__configuration_compiler);
        yk__sdsfree(yy__configuration_c->yy__configuration_compilation->yy__configuration_web_shell);
        yk__sdsfree(yy__configuration_c->yy__configuration_compilation->yy__configuration_web_assets);
    }
    if (yy__configuration_c->yy__configuration_project != NULL)
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
    yk__sdsfree(yy__configuration_c->yy__configuration_gcc_compiler_path);
    yk__sdsfree(yy__configuration_c->yy__configuration_clang_compiler_path);
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
void yy__argparse_del_argparse(yy__argparse_ArgParseWrapper nn__object) { yk__delargparse(nn__object); }
yy__argparse_ArgParseRemainder yy__argparse_parse(yy__argparse_ArgParse nn__argp, yk__sds* nn__arguments) { return yk__argparse_parse(nn__argp, nn__arguments); }
void yy__argparse_usage(yy__argparse_ArgParse nn__argp) { argparse_usage(nn__argp); }
void yy__argparse_del_remainder(yy__argparse_ArgParseRemainder nn__a) { yk__del_argparse_remainder(nn__a); }
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
void yy__console_color_print(int32_t yy__console_color, struct yk__bstr yy__console_x) 
{
    yy__console_set_color(yy__console_color);
    yk__printstr(yk__bstr_get_reference(yy__console_x));
    yy__console_set_color(INT32_C(0));
    return;
}
void yy__console_red(struct yk__bstr yy__console_x) 
{
    yy__console_color_print(INT32_C(1), yy__console_x);
    return;
}
void yy__console_green(struct yk__bstr yy__console_x) 
{
    yy__console_color_print(INT32_C(2), yy__console_x);
    return;
}
void yy__console_yellow(struct yk__bstr yy__console_x) 
{
    yy__console_color_print(INT32_C(6), yy__console_x);
    return;
}
void yy__console_cyan(struct yk__bstr yy__console_x) 
{
    yy__console_color_print(INT32_C(7), yy__console_x);
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
bool yy__toml_get_bool_default(yy__toml_Table nn__x, yk__sds nn__name, bool nn__default) 
{
    toml_datum_t v = toml_bool_in(nn__x, nn__name);
    yk__sdsfree(nn__name);
    if (v.ok) {
        return (1 == v.u.b);
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
yk__sds* yy__toml_get_string_array(yy__toml_Table yy__toml_x, yk__sds yy__toml_name) 
{
    yk__sds* yy__toml_str_array = NULL;
    yy__toml_TomlArray yy__toml_arr = yy__toml_get_array(yy__toml_x, yk__sdsdup(yy__toml_name));
    if (!(yy__toml_valid_array(yy__toml_arr)))
    {
        yk__sds* t__0 = yy__toml_str_array;
        yk__sdsfree(yy__toml_name);
        return t__0;
    }
    int32_t yy__toml_length = yy__toml_array_len(yy__toml_arr);
    int32_t yy__toml_c = INT32_C(0);
    while (true)
    {
        if (!(yy__toml_c < yy__toml_length))
        {
            break;
        }
        yk__sds t__1 = yy__toml_string_at(yy__toml_arr, yy__toml_c);
        yk__arrput(yy__toml_str_array, yk__sdsdup(t__1));
        yy__toml_c = (yy__toml_c + INT32_C(1));
        yk__sdsfree(t__1);
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
    if (yy__path_length < INT32_C(1))
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
yk__sds yy__path_join(yk__sds yy__path_a, yk__sds yy__path_b) 
{
    if (yy__path_end_with_slash(yk__sdsdup(yy__path_a)))
    {
        yk__sds t__1 = yk__sdscatsds(yk__sdsdup(yy__path_a), yy__path_b);
        yk__sds t__2 = t__1;
        yk__sdsfree(yy__path_b);
        yk__sdsfree(yy__path_a);
        return t__2;
        yk__sdsfree(t__1);
    }
yk__sds yy__path_result = yk__sdsempty();
    if (yy__path_forward_slash())
    {
        yk__sds t__3 = yk__concat_sds_lit(yy__path_a, "\\", 1);
        yk__sds t__4 = yk__sdscatsds(yk__sdsdup(t__3), yy__path_b);
        yk__sdsfree(yy__path_result);
        yy__path_result = yk__sdsdup(t__4);
        yk__sdsfree(t__4);
        yk__sdsfree(t__3);
    }
    else
    {
        yk__sds t__5 = yk__concat_sds_lit(yy__path_a, "/", 1);
        yk__sds t__6 = yk__sdscatsds(yk__sdsdup(t__5), yy__path_b);
        yk__sdsfree(yy__path_result);
        yy__path_result = yk__sdsdup(t__6);
        yk__sdsfree(t__6);
        yk__sdsfree(t__5);
    }
    yk__sds t__7 = yy__path_result;
    yk__sdsfree(yy__path_b);
    yk__sdsfree(yy__path_a);
    return t__7;
}
yk__sds yy__path_basename(yk__sds yy__path_p) 
{
    int32_t yy__path_full_length = yk__sdslen(yy__path_p);
    int32_t yy__path_length = yk__sdslen(yy__path_p);
    if (yy__path_length < INT32_C(1))
    {
        yk__sds t__8 = yy__path_p;
        return t__8;
    }
    if (yy__path_end_with_slash(yk__sdsdup(yy__path_p)))
    {
        yk__sdsfree(yy__path_p);
        return yk__sdsnewlen("", 0);
    }
    yy__c_CStr yy__path_x = yy__strings_to_cstr(yk__sdsdup(yy__path_p));
    while (true)
    {
        if (!(((yy__path_length > INT32_C(0)))))
        {
            break;
        }
        yy__path_length = (yy__path_length - INT32_C(1));
        int32_t yy__path_chr = yy__strings_get_cstr(yy__path_x, yy__path_length);
        bool yy__path_is_slash = ((yy__path_chr == INT32_C(47)) || (yy__path_chr == INT32_C(92)));
        if (yy__path_is_slash)
        {
            break;
        }
    }
    if (yy__path_length <= INT32_C(0))
    {
        yk__sds t__9 = yy__path_p;
        yy__strings_del_str(yy__path_x);
        return t__9;
    }
    yk__sds t__10 = yy__strings_from_cstrlen_after(yy__path_x, ((yy__path_full_length - yy__path_length) - INT32_C(1)), (yy__path_length + INT32_C(1)));
    yk__sds yy__path_s = yk__sdsdup(t__10);
    yk__sds t__11 = yy__path_s;
    yy__strings_del_str(yy__path_x);
    yk__sdsfree(t__10);
    yk__sdsfree(yy__path_p);
    return t__11;
}
yk__sds yy__path_dirname(yk__sds yy__path_p) 
{
    int32_t yy__path_length = yk__sdslen(yy__path_p);
    if (yy__path_length <= INT32_C(2))
    {
        yk__sds t__12 = yy__path_p;
        return t__12;
    }
    if (yy__path_end_with_slash(yk__sdsdup(yy__path_p)))
    {
        yy__path_length = (yy__path_length - INT32_C(1));
    }
    yy__c_CStr yy__path_x = yy__strings_to_cstr(yk__sdsdup(yy__path_p));
    while (true)
    {
        if (!(((yy__path_length > INT32_C(0)))))
        {
            break;
        }
        yy__path_length = (yy__path_length - INT32_C(1));
        int32_t yy__path_chr = yy__strings_get_cstr(yy__path_x, yy__path_length);
        bool yy__path_is_slash = ((yy__path_chr == INT32_C(47)) || (yy__path_chr == INT32_C(92)));
        if (yy__path_is_slash)
        {
            break;
        }
    }
    if (yy__path_length <= INT32_C(0))
    {
        yy__strings_del_str(yy__path_x);
        yk__sdsfree(yy__path_p);
        return yk__sdsnewlen("", 0);
    }
    yk__sds t__13 = yy__strings_from_cstrlen(yy__path_x, yy__path_length);
    yk__sds yy__path_s = yk__sdsdup(t__13);
    yk__sds t__14 = yy__path_s;
    yy__strings_del_str(yy__path_x);
    yk__sdsfree(t__13);
    yk__sdsfree(yy__path_p);
    return t__14;
}
yk__sds yy__path_remove_extension(yk__sds yy__path_p) 
{
    int32_t yy__path_length = yk__sdslen(yy__path_p);
    if (yy__path_length <= INT32_C(1))
    {
        yk__sds t__15 = yy__path_p;
        return t__15;
    }
    if (yy__path_end_with_slash(yk__sdsdup(yy__path_p)))
    {
        yy__path_length = (yy__path_length - INT32_C(1));
    }
    yy__c_CStr yy__path_x = yy__strings_to_cstr(yk__sdsdup(yy__path_p));
    while (true)
    {
        if (!(((yy__path_length > INT32_C(0)))))
        {
            break;
        }
        yy__path_length = (yy__path_length - INT32_C(1));
        int32_t yy__path_chr = yy__strings_get_cstr(yy__path_x, yy__path_length);
        bool yy__path_is_dot = (yy__path_chr == INT32_C(46));
        if (yy__path_is_dot)
        {
            break;
        }
    }
    if (yy__path_length <= INT32_C(0))
    {
        yy__strings_del_str(yy__path_x);
        yk__sdsfree(yy__path_p);
        return yk__sdsnewlen("", 0);
    }
    yk__sds t__16 = yy__strings_from_cstrlen(yy__path_x, yy__path_length);
    yk__sds yy__path_s = yk__sdsdup(t__16);
    yk__sds t__17 = yy__path_s;
    yy__strings_del_str(yy__path_x);
    yk__sdsfree(t__16);
    yk__sdsfree(yy__path_p);
    return t__17;
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
int32_t yy__strings_get_cstr(yy__c_CStr nn__s, int32_t nn__pos) 
{
    return (int32_t)nn__s[nn__pos];
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
    if (yk__sdslen(yy__strings_b) > yk__sdslen(yy__strings_a))
    {
        yk__sdsfree(yy__strings_b);
        yk__sdsfree(yy__strings_a);
        return false;
    }
    int32_t yy__strings_pos = (yk__sdslen(yy__strings_a) - yk__sdslen(yy__strings_b));
    yk__sds t__1 = yy__strings_cut_from(yk__sdsdup(yy__strings_a), yy__strings_pos);
    yk__sds yy__strings_cut_a = yk__sdsdup(t__1);
    bool yy__strings_result = (yk__sdscmp(yy__strings_cut_a , yy__strings_b) == 0);
    bool t__2 = yy__strings_result;
    yk__sdsfree(yy__strings_cut_a);
    yk__sdsfree(t__1);
    yk__sdsfree(yy__strings_b);
    yk__sdsfree(yy__strings_a);
    return t__2;
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
    yk__sds t__0 = yy__os_getenv(yk__sdsnewlen("PATH", 4));
    yk__sds yy__os_env = yk__sdsdup(t__0);
    yk__sds yy__os_sep = yk__sdsnewlen(":" , 1);
    if (yy__os_is_windows())
    {
        yk__sdsfree(yy__os_sep);
        yy__os_sep = yk__sdsnewlen(";", 1);
        yk__sds t__1 = yk__concat_sds_lit(yy__os_bin1, ".exe", 4);
        yk__sdsfree(yy__os_bin1);
        yy__os_bin1 = yk__sdsdup(t__1);
        yk__sds t__2 = yk__concat_sds_lit(yy__os_bin2, ".bat", 4);
        yk__sdsfree(yy__os_bin2);
        yy__os_bin2 = yk__sdsdup(t__2);
        yk__sds t__3 = yk__concat_sds_lit(yy__os_bin3, ".cmd", 4);
        yk__sdsfree(yy__os_bin3);
        yy__os_bin3 = yk__sdsdup(t__3);
        yk__sdsfree(t__3);
        yk__sdsfree(t__2);
        yk__sdsfree(t__1);
    }
    yk__sds* yy__os_paths = yy__strings_split(yk__sdsdup(yy__os_env), yk__sdsdup(yy__os_sep));
    int32_t yy__os_length = yk__arrlen(yy__os_paths);
    while (true)
    {
        if (!(((yy__os_length > INT32_C(0)))))
        {
            break;
        }
        yy__os_length = (yy__os_length - INT32_C(1));
        yk__sds yy__os_cur_path = yk__sdsdup(yy__os_paths[yy__os_length]);
        yk__sds t__4 = yy__path_join(yk__sdsdup(yy__os_cur_path), yk__sdsdup(yy__os_bin1));
        yk__sds yy__os_full_path = yk__sdsdup(t__4);
        if (yy__path_executable(yk__sdsdup(yy__os_full_path)))
        {
            yk__sds t__5 = yy__os_full_path;
            yy__array_del_str_array(yy__os_paths);
            yk__sdsfree(t__4);
            yk__sdsfree(yy__os_cur_path);
            yk__sdsfree(yy__os_sep);
            yk__sdsfree(yy__os_env);
            yk__sdsfree(t__0);
            yk__sdsfree(yy__os_bin3);
            yk__sdsfree(yy__os_bin2);
            yk__sdsfree(yy__os_bin1);
            yk__sdsfree(yy__os_binary);
            return t__5;
        }
        if (yy__os_is_windows())
        {
            yk__sds t__6 = yy__path_join(yk__sdsdup(yy__os_cur_path), yk__sdsdup(yy__os_bin2));
            yk__sdsfree(yy__os_full_path);
            yy__os_full_path = yk__sdsdup(t__6);
            if (yy__path_exists(yk__sdsdup(yy__os_full_path)))
            {
                yk__sds t__7 = yy__os_full_path;
                yy__array_del_str_array(yy__os_paths);
                yk__sdsfree(t__6);
                yk__sdsfree(t__4);
                yk__sdsfree(yy__os_cur_path);
                yk__sdsfree(yy__os_sep);
                yk__sdsfree(yy__os_env);
                yk__sdsfree(t__0);
                yk__sdsfree(yy__os_bin3);
                yk__sdsfree(yy__os_bin2);
                yk__sdsfree(yy__os_bin1);
                yk__sdsfree(yy__os_binary);
                return t__7;
            }
            yk__sds t__8 = yy__path_join(yk__sdsdup(yy__os_cur_path), yk__sdsdup(yy__os_bin3));
            yk__sdsfree(yy__os_full_path);
            yy__os_full_path = yk__sdsdup(t__8);
            if (yy__path_exists(yk__sdsdup(yy__os_full_path)))
            {
                yk__sds t__9 = yy__os_full_path;
                yy__array_del_str_array(yy__os_paths);
                yk__sdsfree(t__8);
                yk__sdsfree(t__6);
                yk__sdsfree(t__4);
                yk__sdsfree(yy__os_cur_path);
                yk__sdsfree(yy__os_sep);
                yk__sdsfree(yy__os_env);
                yk__sdsfree(t__0);
                yk__sdsfree(yy__os_bin3);
                yk__sdsfree(yy__os_bin2);
                yk__sdsfree(yy__os_bin1);
                yk__sdsfree(yy__os_binary);
                return t__9;
            }
            yk__sdsfree(t__8);
            yk__sdsfree(t__6);
        }
        yk__sdsfree(yy__os_full_path);
        yk__sdsfree(t__4);
        yk__sdsfree(yy__os_cur_path);
    }
    yk__sds t__10 = yy__os_cwd();
    yk__sds t__11 = yy__path_join(yk__sdsdup(t__10), yk__sdsdup(yy__os_bin1));
    yk__sds yy__os_special = yk__sdsdup(t__11);
    if (yy__path_executable(yk__sdsdup(yy__os_special)))
    {
        yk__sds t__12 = yy__os_special;
        yy__array_del_str_array(yy__os_paths);
        yk__sdsfree(t__11);
        yk__sdsfree(t__10);
        yk__sdsfree(yy__os_sep);
        yk__sdsfree(yy__os_env);
        yk__sdsfree(t__0);
        yk__sdsfree(yy__os_bin3);
        yk__sdsfree(yy__os_bin2);
        yk__sdsfree(yy__os_bin1);
        yk__sdsfree(yy__os_binary);
        return t__12;
    }
    if (yy__os_is_windows())
    {
        yk__sds t__13 = yy__os_cwd();
        yk__sds t__14 = yy__path_join(yk__sdsdup(t__13), yk__sdsdup(yy__os_bin2));
        yk__sdsfree(yy__os_special);
        yy__os_special = yk__sdsdup(t__14);
        if (yy__path_exists(yk__sdsdup(yy__os_special)))
        {
            yk__sds t__15 = yy__os_special;
            yy__array_del_str_array(yy__os_paths);
            yk__sdsfree(t__14);
            yk__sdsfree(t__13);
            yk__sdsfree(t__11);
            yk__sdsfree(t__10);
            yk__sdsfree(yy__os_sep);
            yk__sdsfree(yy__os_env);
            yk__sdsfree(t__0);
            yk__sdsfree(yy__os_bin3);
            yk__sdsfree(yy__os_bin2);
            yk__sdsfree(yy__os_bin1);
            yk__sdsfree(yy__os_binary);
            return t__15;
        }
        yk__sds t__16 = yy__os_cwd();
        yk__sds t__17 = yy__path_join(yk__sdsdup(t__16), yk__sdsdup(yy__os_bin3));
        yk__sdsfree(yy__os_special);
        yy__os_special = yk__sdsdup(t__17);
        if (yy__path_exists(yk__sdsdup(yy__os_special)))
        {
            yk__sds t__18 = yy__os_special;
            yy__array_del_str_array(yy__os_paths);
            yk__sdsfree(t__17);
            yk__sdsfree(t__16);
            yk__sdsfree(t__14);
            yk__sdsfree(t__13);
            yk__sdsfree(t__11);
            yk__sdsfree(t__10);
            yk__sdsfree(yy__os_sep);
            yk__sdsfree(yy__os_env);
            yk__sdsfree(t__0);
            yk__sdsfree(yy__os_bin3);
            yk__sdsfree(yy__os_bin2);
            yk__sdsfree(yy__os_bin1);
            yk__sdsfree(yy__os_binary);
            return t__18;
        }
        yk__sdsfree(t__17);
        yk__sdsfree(t__16);
        yk__sdsfree(t__14);
        yk__sdsfree(t__13);
    }
    yk__sds t__19 = yy__os_exe_path();
    yk__sds t__20 = yy__path_join(yk__sdsdup(t__19), yk__sdsdup(yy__os_bin1));
    yk__sdsfree(yy__os_special);
    yy__os_special = yk__sdsdup(t__20);
    if (yy__path_executable(yk__sdsdup(yy__os_special)))
    {
        yk__sds t__21 = yy__os_special;
        yy__array_del_str_array(yy__os_paths);
        yk__sdsfree(t__20);
        yk__sdsfree(t__19);
        yk__sdsfree(t__11);
        yk__sdsfree(t__10);
        yk__sdsfree(yy__os_sep);
        yk__sdsfree(yy__os_env);
        yk__sdsfree(t__0);
        yk__sdsfree(yy__os_bin3);
        yk__sdsfree(yy__os_bin2);
        yk__sdsfree(yy__os_bin1);
        yk__sdsfree(yy__os_binary);
        return t__21;
    }
    if (yy__os_is_windows())
    {
        yk__sds t__22 = yy__os_exe_path();
        yk__sds t__23 = yy__path_join(yk__sdsdup(t__22), yk__sdsdup(yy__os_bin2));
        yk__sdsfree(yy__os_special);
        yy__os_special = yk__sdsdup(t__23);
        if (yy__path_exists(yk__sdsdup(yy__os_special)))
        {
            yk__sds t__24 = yy__os_special;
            yy__array_del_str_array(yy__os_paths);
            yk__sdsfree(t__23);
            yk__sdsfree(t__22);
            yk__sdsfree(t__20);
            yk__sdsfree(t__19);
            yk__sdsfree(t__11);
            yk__sdsfree(t__10);
            yk__sdsfree(yy__os_sep);
            yk__sdsfree(yy__os_env);
            yk__sdsfree(t__0);
            yk__sdsfree(yy__os_bin3);
            yk__sdsfree(yy__os_bin2);
            yk__sdsfree(yy__os_bin1);
            yk__sdsfree(yy__os_binary);
            return t__24;
        }
        yk__sds t__25 = yy__os_exe_path();
        yk__sds t__26 = yy__path_join(yk__sdsdup(t__25), yk__sdsdup(yy__os_bin3));
        yk__sdsfree(yy__os_special);
        yy__os_special = yk__sdsdup(t__26);
        if (yy__path_exists(yk__sdsdup(yy__os_special)))
        {
            yk__sds t__27 = yy__os_special;
            yy__array_del_str_array(yy__os_paths);
            yk__sdsfree(t__26);
            yk__sdsfree(t__25);
            yk__sdsfree(t__23);
            yk__sdsfree(t__22);
            yk__sdsfree(t__20);
            yk__sdsfree(t__19);
            yk__sdsfree(t__11);
            yk__sdsfree(t__10);
            yk__sdsfree(yy__os_sep);
            yk__sdsfree(yy__os_env);
            yk__sdsfree(t__0);
            yk__sdsfree(yy__os_bin3);
            yk__sdsfree(yy__os_bin2);
            yk__sdsfree(yy__os_bin1);
            yk__sdsfree(yy__os_binary);
            return t__27;
        }
        yk__sdsfree(t__26);
        yk__sdsfree(t__25);
        yk__sdsfree(t__23);
        yk__sdsfree(t__22);
    }
    yy__array_del_str_array(yy__os_paths);
    yk__sdsfree(t__20);
    yk__sdsfree(t__19);
    yk__sdsfree(yy__os_special);
    yk__sdsfree(t__11);
    yk__sdsfree(t__10);
    yk__sdsfree(yy__os_sep);
    yk__sdsfree(yy__os_env);
    yk__sdsfree(t__0);
    yk__sdsfree(yy__os_bin3);
    yk__sdsfree(yy__os_bin2);
    yk__sdsfree(yy__os_bin1);
    yk__sdsfree(yy__os_binary);
    return yk__sdsnewlen("", 0);
}
yk__sds yy__libs_version() 
{
    return yk__sdsnewlen("0.0.6", 5);
}
void yy__print_banner() 
{
    yk__sds yy__art = yk__sdsnewlen("\n    ╔═╗┌─┐┬─┐╔═╗┌┐┌┌┬┐┬─┐\n    ║  ├─┤├┬┘╠═╝│││ │ ├┬┘\n    ╚═╝┴ ┴┴└─╩  ┘└┘ ┴ ┴└─\n    " , 191);
    yk__sds yy__text = yk__sdsnewlen("\n    Tool for building Yaksha\n    Projects\n    " , 47);
    yk__sds yy__art2 = yk__sdsnewlen("\n       ,\n      /(  ___________\n     |  >:===========`\n      )(\n      \"\"\n" , 73);
    yy__console_green(yk__bstr_h(yy__art));
    yy__console_cyan(yk__bstr_h(yy__text));
    yy__console_yellow(yk__bstr_h(yy__art2));
    yk__sdsfree(yy__art2);
    yk__sdsfree(yy__text);
    yk__sdsfree(yy__art);
    return;
}
void yy__print_errors(yk__sds* yy__er) 
{
    int32_t yy__length = yk__arrlen(yy__er);
    int32_t yy__x = INT32_C(0);
    while (true)
    {
        if (!(yy__x < yy__length))
        {
            break;
        }
        yk__sds t__0 = yk__concat_sds_lit(yy__er[yy__x], "\n", 1);
        yy__console_red(yk__bstr_h(t__0));
        yy__x = (yy__x + INT32_C(1));
        yk__sdsfree(t__0);
    }
    return;
}
void yy__printkv(yk__sds yy__k, yk__sds yy__v) 
{
    yy__console_cyan(yk__bstr_h(yy__k));
    yy__console_red(yk__bstr_s(" := ", 4));
    if (yk__sdslen(yy__v) == INT32_C(0))
    {
        yy__console_green(yk__bstr_s("<not found>", 11));
    }
    else
    {
        yy__console_green(yk__bstr_h(yy__v));
    }
    yk__printstr("\n");
    yk__sdsfree(yy__v);
    yk__sdsfree(yy__k);
    return;
}
void yy__print_config(struct yy__configuration_Config* yy__config) 
{
    yy__printkv(yk__sdsnewlen("libs", 4), yk__sdsdup(yy__config->yy__configuration_libs_path));
    yy__printkv(yk__sdsnewlen("runtime", 7), yk__sdsdup(yy__config->yy__configuration_runtime_path));
    yy__printkv(yk__sdsnewlen("compiler", 8), yk__sdsdup(yy__config->yy__configuration_compiler_path));
    yy__printkv(yk__sdsnewlen("zig compiler", 12), yk__sdsdup(yy__config->yy__configuration_zig_compiler_path));
    yy__printkv(yk__sdsnewlen("emcc compiler", 13), yk__sdsdup(yy__config->yy__configuration_emcc_compiler_path));
    yy__printkv(yk__sdsnewlen("emrun", 5), yk__sdsdup(yy__config->yy__configuration_emrun_path));
    yy__printkv(yk__sdsnewlen("w4", 2), yk__sdsdup(yy__config->yy__configuration_w4_path));
    yk__sds t__1 = yy__libs_version();
    yy__printkv(yk__sdsnewlen("standard library version", 24), yk__sdsdup(t__1));
    yk__sdsfree(t__1);
    return;
}
int32_t yy__build_from_config(struct yy__configuration_Config* yy__config, bool yy__simple, bool yy__silent) 
{
    int32_t yy__return_val = INT32_C(0);
    yk__sds* t__2 = NULL;
    yk__arrsetcap(t__2, 4);
    yk__arrput(t__2, yk__sdsdup(yy__config->yy__configuration_compiler_path));
    yk__arrput(t__2, yk__sdsnewlen("compile", 7));
    yk__arrput(t__2, yk__sdsdup(yy__config->yy__configuration_project->yy__configuration_main));
    yk__arrput(t__2, yk__sdsdup(yy__config->yy__configuration_libs_path));
    yk__sds* yy__yk_args = t__2;
    yy__os_ProcessResult yy__result = yy__os_run(yy__yk_args);
    if (!(yy__result->ok))
    {
        yy__console_cyan(yk__bstr_s("---- running Yaksha compiler ---\n", 33));
        yy__console_red(yk__bstr_s("Failed to execute: ", 19));
        yk__sds t__3 = yy__array_join(yy__yk_args, yk__sdsnewlen(" ", 1));
        yy__console_yellow(yk__bstr_h(t__3));
        yk__printstr("\n");
        yy__console_red(yk__bstr_h(yy__result->output));
        yk__printstr("\n");
        yy__return_val = (-(INT32_C(1)));
        yy__console_cyan(yk__bstr_s("---- end of compiler run ---\n", 29));
        yk__sdsfree(t__3);
    }
    else
    {
        if (yy__strings_startswith(yk__sdsdup(yy__result->output), yk__sdsnewlen("// YK", 5)))
        {
            if (yy__simple)
            {
                yy__return_val = yy__building_build_simple(yy__config, yk__sdsdup(yy__result->output), yy__silent);
            }
            else
            {
                yy__return_val = yy__building_build(yy__config, yk__sdsdup(yy__result->output));
            }
        }
        else
        {
            yy__console_cyan(yk__bstr_s("---- running Yaksha compiler ---\n", 33));
            yy__console_red(yk__bstr_h(yy__result->output));
            yk__printstr("\n");
            yy__return_val = (-(INT32_C(1)));
            yy__console_cyan(yk__bstr_s("---- end of compiler run ---\n", 29));
        }
    }
    int32_t t__4 = yy__return_val;
    yy__os_del_process_result(yy__result);
    yy__array_del_str_array(yy__yk_args);
    return t__4;
}
int32_t yy__perform_build() 
{
    struct yy__configuration_Config* yy__config = yy__configuration_load_config();
    if (yk__arrlen(yy__config->yy__configuration_errors) > INT32_C(0))
    {
        yy__print_errors(yy__config->yy__configuration_errors);
        int32_t t__5 = (-(INT32_C(1)));
        yy__configuration_del_config(yy__config);
        return t__5;
    }
    yy__print_config(yy__config);
    int32_t yy__ret = yy__build_from_config(yy__config, false, false);
    int32_t t__6 = yy__ret;
    yy__configuration_del_config(yy__config);
    return t__6;
}
int32_t yy__perform_mini_build(yk__sds yy__filename, bool yy__use_raylib, bool yy__use_web, bool yy__wasm4, yk__sds yy__web_shell, yk__sds yy__asset_path, bool yy__silent, bool yy__actually_run, bool yy__crdll, bool yy__no_parallel) 
{
    yk__sds t__7 = yy__path_basename(yk__sdsdup(yy__filename));
    yk__sds t__8 = yy__path_remove_extension(yk__sdsdup(t__7));
    yk__sds yy__name = yk__sdsdup(t__8);
    struct yy__configuration_Config* yy__config = yy__configuration_create_adhoc_config(yk__sdsdup(yy__name), yk__sdsdup(yy__filename), yy__use_raylib, yy__use_web, yy__wasm4, yk__sdsdup(yy__web_shell), yk__sdsdup(yy__asset_path), yy__crdll, yy__no_parallel);
    if (yk__arrlen(yy__config->yy__configuration_errors) > INT32_C(0))
    {
        yy__print_errors(yy__config->yy__configuration_errors);
        int32_t t__9 = (-(INT32_C(1)));
        yy__configuration_del_config(yy__config);
        yk__sdsfree(yy__name);
        yk__sdsfree(t__8);
        yk__sdsfree(t__7);
        yk__sdsfree(yy__asset_path);
        yk__sdsfree(yy__web_shell);
        yk__sdsfree(yy__filename);
        return t__9;
    }
    if (!yy__silent)
    {
        yy__print_config(yy__config);
    }
    int32_t yy__ret = yy__build_from_config(yy__config, true, yy__silent);
    if (yy__ret != INT32_C(0))
    {
        int32_t t__10 = yy__ret;
        yy__configuration_del_config(yy__config);
        yk__sdsfree(yy__name);
        yk__sdsfree(t__8);
        yk__sdsfree(t__7);
        yk__sdsfree(yy__asset_path);
        yk__sdsfree(yy__web_shell);
        yk__sdsfree(yy__filename);
        return t__10;
    }
    if (!yy__actually_run)
    {
        yy__configuration_del_config(yy__config);
        yk__sdsfree(yy__name);
        yk__sdsfree(t__8);
        yk__sdsfree(t__7);
        yk__sdsfree(yy__asset_path);
        yk__sdsfree(yy__web_shell);
        yk__sdsfree(yy__filename);
        return INT32_C(0);
    }
    if (!yy__silent)
    {
        yy__console_cyan(yk__bstr_s("-----------------------------", 29));
        yk__printstr("\n");
    }
    yk__sds yy__binary = yk__sdsdup(yy__name);
    if (yy__use_web)
    {
        yk__sds t__11 = yk__concat_sds_lit(yy__binary, ".html", 5);
        yk__sdsfree(yy__binary);
        yy__binary = yk__sdsdup(t__11);
        yk__sds t__12 = yy__os_cwd();
        yk__sds t__13 = yy__path_join(yk__sdsdup(t__12), yk__sdsdup(yy__binary));
        yk__sds* t__14 = NULL;
        yk__arrsetcap(t__14, 2);
        yk__arrput(t__14, yk__sdsdup(yy__config->yy__configuration_emrun_path));
        yk__arrput(t__14, yk__sdsdup(t__13));
        yk__sds* yy__em_args = t__14;
        yy__os_ProcessResult yy__r = yy__os_run(yy__em_args);
        yy__array_del_str_array(yy__em_args);
        yy__os_del_process_result(yy__r);
        yk__sdsfree(t__13);
        yk__sdsfree(t__12);
        yk__sdsfree(t__11);
    }
    else
    {
        if (yy__wasm4)
        {
            yk__sds t__15 = yk__concat_sds_lit(yy__binary, ".wasm", 5);
            yk__sdsfree(yy__binary);
            yy__binary = yk__sdsdup(t__15);
            yk__sds t__16 = yy__os_cwd();
            yk__sds t__17 = yy__path_join(yk__sdsdup(t__16), yk__sdsdup(yy__binary));
            yk__sds* t__18 = NULL;
            yk__arrsetcap(t__18, 3);
            yk__arrput(t__18, yk__sdsdup(yy__config->yy__configuration_w4_path));
            yk__arrput(t__18, yk__sdsnewlen("run-native", 10));
            yk__arrput(t__18, yk__sdsdup(t__17));
            yk__sds* yy__em_args = t__18;
            yy__os_ProcessResult yy__r = yy__os_run(yy__em_args);
            yy__array_del_str_array(yy__em_args);
            yy__os_del_process_result(yy__r);
            yk__sdsfree(t__17);
            yk__sdsfree(t__16);
            yk__sdsfree(t__15);
        }
        else
        {
            if (yy__os_is_windows())
            {
                yk__sds t__19 = yk__concat_sds_lit(yy__binary, ".exe", 4);
                yk__sdsfree(yy__binary);
                yy__binary = yk__sdsdup(t__19);
                yk__sdsfree(t__19);
            }
            else
            {
                yk__sds t__20 = yk__concat_lit_sds("./", 2, yy__binary);
                yk__sdsfree(yy__binary);
                yy__binary = yk__sdsdup(t__20);
                yk__sdsfree(t__20);
            }
            yy__c_CStr yy__binary_cstr = yy__strings_to_cstr(yk__sdsdup(yy__binary));
            yy__c_system(yy__binary_cstr);
            yy__strings_del_str(yy__binary_cstr);
        }
    }
    yy__configuration_del_config(yy__config);
    yk__sdsfree(yy__binary);
    yk__sdsfree(yy__name);
    yk__sdsfree(t__8);
    yk__sdsfree(t__7);
    yk__sdsfree(yy__asset_path);
    yk__sdsfree(yy__web_shell);
    yk__sdsfree(yy__filename);
    return INT32_C(0);
}
int32_t yy__handle_args(yy__os_Arguments yy__args) 
{
    yk__sds* yy__arguments = yy__array_dup(yy__args->argv);
    yy__argparse_Option* yy__options = NULL;
    yk__sds* t__21 = NULL;
    yk__arrsetcap(t__21, 2);
    yk__arrput(t__21, yk__sdsnewlen("carpntr", 7));
    yk__arrput(t__21, yk__sdsnewlen("carpntr [options] file", 22));
    yk__sds* yy__usages = t__21;
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
    yy__c_CStr yy__assets_path = yy__strings_null_cstr();
    yk__sds yy__web_shell = yk__sdsnewlen("" , 0);
    yk__sds yy__assets_path_s = yk__sdsnewlen("" , 0);
    yk__arrput(yy__options, yy__argparse_opt_boolean(yk__sdsnewlen("h", 1), yk__sdsnewlen("help", 4), (&(yy__help)), yk__sdsnewlen("show help and exit", 18)));
    yk__arrput(yy__options, yy__argparse_opt_boolean(yk__sdsnewlen("R", 1), yk__sdsnewlen("run", 3), (&(yy__run)), yk__sdsnewlen("run a single file", 17)));
    yk__arrput(yy__options, yy__argparse_opt_boolean(yk__sdsnewlen("C", 1), yk__sdsnewlen("compile", 7), (&(yy__just_compile)), yk__sdsnewlen("compile a single file", 21)));
    yk__arrput(yy__options, yy__argparse_opt_boolean(yk__sdsnewlen("r", 1), yk__sdsnewlen("raylib", 6), (&(yy__raylib)), yk__sdsnewlen("enable raylib", 13)));
    yk__arrput(yy__options, yy__argparse_opt_boolean(yk__sdsnewlen("w", 1), yk__sdsnewlen("web", 3), (&(yy__web)), yk__sdsnewlen("build for web (works only with raylib)", 38)));
    yk__arrput(yy__options, yy__argparse_opt_boolean(yk__sdsnewlen("d", 1), yk__sdsnewlen("dll", 3), (&(yy__crdll)), yk__sdsnewlen("enable .dll client build for hot reloading with ykreload/cr.h (works only with raylib)", 86)));
    yk__arrput(yy__options, yy__argparse_opt_string(yk__sdsnewlen("s", 1), yk__sdsnewlen("shell", 5), (&(yy__file_path)), yk__sdsnewlen("specify shell file for web builds", 33)));
    yk__arrput(yy__options, yy__argparse_opt_string(yk__sdsnewlen("a", 1), yk__sdsnewlen("assets", 6), (&(yy__assets_path)), yk__sdsnewlen("specify assets directory for web builds", 39)));
    yk__arrput(yy__options, yy__argparse_opt_boolean(yk__sdsnewlen("4", 1), yk__sdsnewlen("wasm4", 5), (&(yy__wasm4)), yk__sdsnewlen("wasm4 build", 11)));
    yk__arrput(yy__options, yy__argparse_opt_boolean(yk__sdsnewlen("S", 1), yk__sdsnewlen("silent", 6), (&(yy__silent_mode)), yk__sdsnewlen("do not print anything except errors", 35)));
    yk__arrput(yy__options, yy__argparse_opt_boolean(yk__sdsnewlen("N", 1), yk__sdsnewlen("nothread", 8), (&(yy__no_parallel)), yk__sdsnewlen("no parallel build & disable optimization (for debugging)", 56)));
    yk__arrput(yy__options, yy__argparse_opt_end());
    yy__argparse_ArgParseWrapper yy__a = yy__argparse_new(yy__options, yy__usages);
    yy__argparse_ArgParseRemainder yy__remainder = yy__argparse_parse(yy__a->state, yy__arguments);
    if (yy__silent_mode != INT32_C(1))
    {
        yy__print_banner();
    }
    if (yy__help == INT32_C(1))
    {
        yy__argparse_usage(yy__a->state);
        yy__strings_del_cstr(yy__file_path);
        yy__argparse_del_remainder(yy__remainder);
        yy__argparse_del_argparse(yy__a);
        yy__array_del_str_array(yy__usages);
        yk__arrfree(yy__options);
        yy__array_del_str_array(yy__arguments);
        yk__sdsfree(yy__assets_path_s);
        yk__sdsfree(yy__web_shell);
        return INT32_C(0);
    }
    if (yy__remainder->argc != INT32_C(1))
    {
        yk__printlnstr("One file must be preset for excution");
        yy__strings_del_cstr(yy__file_path);
        yy__argparse_del_remainder(yy__remainder);
        yy__argparse_del_argparse(yy__a);
        yy__array_del_str_array(yy__usages);
        yk__arrfree(yy__options);
        yy__array_del_str_array(yy__arguments);
        yk__sdsfree(yy__assets_path_s);
        yk__sdsfree(yy__web_shell);
        return INT32_C(1);
    }
    yk__sds yy__single_file = yk__sdsdup(yy__remainder->remainder[INT32_C(0)]);
    if ((yy__wasm4 == INT32_C(1)) && (((yy__raylib == INT32_C(1)) || (yy__web == INT32_C(1)))))
    {
        yk__printlnstr("Wasm4 is not compatible with raylib/web");
        yy__strings_del_cstr(yy__file_path);
        yy__argparse_del_remainder(yy__remainder);
        yy__argparse_del_argparse(yy__a);
        yy__array_del_str_array(yy__usages);
        yk__arrfree(yy__options);
        yy__array_del_str_array(yy__arguments);
        yk__sdsfree(yy__single_file);
        yk__sdsfree(yy__assets_path_s);
        yk__sdsfree(yy__web_shell);
        return INT32_C(1);
    }
    if ((yy__web == INT32_C(1)) && (yy__raylib != INT32_C(1)))
    {
        yk__printlnstr("Web is only supported with raylib");
        yy__strings_del_cstr(yy__file_path);
        yy__argparse_del_remainder(yy__remainder);
        yy__argparse_del_argparse(yy__a);
        yy__array_del_str_array(yy__usages);
        yk__arrfree(yy__options);
        yy__array_del_str_array(yy__arguments);
        yk__sdsfree(yy__single_file);
        yk__sdsfree(yy__assets_path_s);
        yk__sdsfree(yy__web_shell);
        return INT32_C(1);
    }
    if ((yy__web != INT32_C(1)) && yy__strings_valid_cstr(yy__file_path))
    {
        yk__printlnstr("Shell is only supported with web");
        yy__strings_del_cstr(yy__file_path);
        yy__argparse_del_remainder(yy__remainder);
        yy__argparse_del_argparse(yy__a);
        yy__array_del_str_array(yy__usages);
        yk__arrfree(yy__options);
        yy__array_del_str_array(yy__arguments);
        yk__sdsfree(yy__single_file);
        yk__sdsfree(yy__assets_path_s);
        yk__sdsfree(yy__web_shell);
        return INT32_C(1);
    }
    if ((yy__web != INT32_C(1)) && yy__strings_valid_cstr(yy__file_path))
    {
        yk__printlnstr("Shell is only supported with web");
        yy__strings_del_cstr(yy__file_path);
        yy__argparse_del_remainder(yy__remainder);
        yy__argparse_del_argparse(yy__a);
        yy__array_del_str_array(yy__usages);
        yk__arrfree(yy__options);
        yy__array_del_str_array(yy__arguments);
        yk__sdsfree(yy__single_file);
        yk__sdsfree(yy__assets_path_s);
        yk__sdsfree(yy__web_shell);
        return INT32_C(1);
    }
    if ((yy__run == INT32_C(1)) && (yy__crdll == INT32_C(1)))
    {
        yk__printlnstr("Use -C instead of -R to compile a dll.");
        yy__strings_del_cstr(yy__file_path);
        yy__argparse_del_remainder(yy__remainder);
        yy__argparse_del_argparse(yy__a);
        yy__array_del_str_array(yy__usages);
        yk__arrfree(yy__options);
        yy__array_del_str_array(yy__arguments);
        yk__sdsfree(yy__single_file);
        yk__sdsfree(yy__assets_path_s);
        yk__sdsfree(yy__web_shell);
        return INT32_C(1);
    }
    if ((yy__run == INT32_C(1)) || (yy__just_compile == INT32_C(1)))
    {
        if (yy__strings_valid_cstr(yy__file_path))
        {
            yk__sds t__22 = yy__strings_from_cstr(yy__file_path);
            yk__sdsfree(yy__web_shell);
            yy__web_shell = yk__sdsdup(t__22);
            yk__printstr("Using web-shell:");
            yk__printlnstr(yy__web_shell);
            yk__sdsfree(t__22);
        }
        if (yy__strings_valid_cstr(yy__assets_path))
        {
            yk__sds t__23 = yy__strings_from_cstr(yy__assets_path);
            yk__sdsfree(yy__assets_path_s);
            yy__assets_path_s = yk__sdsdup(t__23);
            yk__printstr("Using asset-path:");
            yk__printlnstr(yy__assets_path_s);
            yk__sdsfree(t__23);
        }
        int32_t t__24 = yy__perform_mini_build(yk__sdsdup(yy__single_file), (yy__raylib == INT32_C(1)), (yy__web == INT32_C(1)), (yy__wasm4 == INT32_C(1)), yk__sdsdup(yy__web_shell), yk__sdsdup(yy__assets_path_s), (yy__silent_mode == INT32_C(1)), (yy__run == INT32_C(1)), (yy__crdll == INT32_C(1)), (yy__no_parallel == INT32_C(1)));
        yy__strings_del_cstr(yy__file_path);
        yy__argparse_del_remainder(yy__remainder);
        yy__argparse_del_argparse(yy__a);
        yy__array_del_str_array(yy__usages);
        yk__arrfree(yy__options);
        yy__array_del_str_array(yy__arguments);
        yk__sdsfree(yy__single_file);
        yk__sdsfree(yy__assets_path_s);
        yk__sdsfree(yy__web_shell);
        return t__24;
    }
    yy__console_red(yk__bstr_s("Invalid usage. Please use \'-R\' option if you want to run a program. Try \'carpntr --help\' for more information.\n", 111));
    yy__strings_del_cstr(yy__file_path);
    yy__argparse_del_remainder(yy__remainder);
    yy__argparse_del_argparse(yy__a);
    yy__array_del_str_array(yy__usages);
    yk__arrfree(yy__options);
    yy__array_del_str_array(yy__arguments);
    yk__sdsfree(yy__single_file);
    yk__sdsfree(yy__assets_path_s);
    yk__sdsfree(yy__web_shell);
    return INT32_C(0);
}
int32_t yy__main() 
{
    yy__os_Arguments yy__args = yy__os_get_args();
    if (yy__args->argc <= INT32_C(1))
    {
        yy__print_banner();
        int32_t t__25 = yy__perform_build();
        return t__25;
    }
    int32_t t__26 = yy__handle_args(yy__args);
    return t__26;
}
#if defined(YK__MINIMAL_MAIN)
int main(void) { return yy__main(); }
#endif