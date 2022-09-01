#include "whereami.h"
#include "yk__system.h"
#include "utf8proc.h"
#include "yk__utf8iter.h"
#include "toml.h"
#include "yk__console.h"
#include "mpc.h"
#include "yk__arrayutils.h"
#include "yk__process.h"
#include "yk__graphic_utils.h"
#include "yk__argparse.h"
#include "argparse.h"
// YK
#include "yk__lib.h"
// --forward declarations-- 
const int32_t yy__argparse_ARGPARSE_DEFAULT = 0;
const int32_t yy__argparse_ARGPARSE_STOP_AT_NON_OPTION = 1;
const int32_t yy__argparse_ARGPARSE_IGNORE_UNKNOWN_ARGS = 2;
const int32_t yy__argparse_ARGPARSE_STOP_AT_NON_AND_IGNORE_UNKNWON = 3;
const int32_t yy__console_REWIND = 0;
const int32_t yy__console_RED = 1;
const int32_t yy__console_GREEN = 2;
const int32_t yy__console_WHITE = 3;
const int32_t yy__console_BLUE = 4;
const int32_t yy__console_PURPLE = 5;
const int32_t yy__console_YELLOW = 6;
const int32_t yy__console_CYAN = 7;
struct yy__raylib_support_CObject;
#define yy__buffer_StringBuffer yk__sds*
struct yy__configuration_CCode;
struct yy__configuration_Project;
struct yy__configuration_Compilation;
struct yy__configuration_Config;
#define yy__argparse_ArgParseRemainder struct yk__arg_remainder*
#define yy__argparse_ArgParse struct argparse*
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
#define yy__strings_Utf8IterateState struct utf8proc_iter_state*
#define yy__os_arguments struct yk__arguments*
#define yy__os_get_args yk__get_args
#define yy__os_ProcessResult struct yk__process_result*
struct yy__raylib_support_CObject* yy__raylib_support_fill_arguments(yk__sds, struct yy__raylib_support_CObject*);
struct yy__raylib_support_CObject* yy__raylib_support_fill_web_arguments(yk__sds, struct yy__raylib_support_CObject*);
struct yy__raylib_support_CObject* yy__raylib_support_co(yk__sds, yk__sds, yk__sds, bool);
void yy__raylib_support_del_c_object(struct yy__raylib_support_CObject*);
void yy__raylib_support_del_objects(struct yy__raylib_support_CObject**);
struct yy__raylib_support_CObject** yy__raylib_support_get_objects(yk__sds, yk__sds, yk__sds, yk__sds, bool);
yk__sds* yy__raylib_support_get_external_libs();
yk__sds* yy__raylib_support_get_web_args();
bool yy__raylib_support_produce_object(struct yy__raylib_support_CObject*, struct yy__configuration_Config*);
yk__sds* yy__raylib_support_get_raylib_args(struct yy__configuration_Config*);
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
yk__sds* yy__building_create_args(struct yy__configuration_Config*, yk__sds, yk__sds, yk__sds, yk__sds*);
int32_t yy__building_build_target(struct yy__configuration_Config*, yk__sds, yk__sds, yk__sds, yk__sds*);
int32_t yy__building_build(struct yy__configuration_Config*, yk__sds);
int32_t yy__building_build_simple(struct yy__configuration_Config*, yk__sds);
void yy__configuration_find_runtime_path(struct yy__configuration_Config*);
void yy__configuration_find_libs_path(struct yy__configuration_Config*);
void yy__configuration_find_yaksha_compiler(struct yy__configuration_Config*);
void yy__configuration_find_zig_compiler(struct yy__configuration_Config*);
void yy__configuration_find_emsdk(struct yy__configuration_Config*);
struct yy__configuration_Project* yy__configuration_load_project(yy__toml_Table, struct yy__configuration_Config*);
struct yy__configuration_CCode* yy__configuration_load_c_code(yy__toml_Table, struct yy__configuration_Config*);
struct yy__configuration_Compilation* yy__configuration_load_compilation(yy__toml_Table, struct yy__configuration_Config*);
struct yy__configuration_CCode* yy__configuration_inject_c_code_defaults(struct yy__configuration_CCode*, struct yy__configuration_Config*);
struct yy__configuration_Config* yy__configuration_load_config();
struct yy__configuration_Config* yy__configuration_create_adhoc_config(yk__sds, yk__sds, bool, bool);
void yy__configuration_del_config(struct yy__configuration_Config*);
yy__argparse_ArgParse yy__argparse_new_ex(yy__argparse_Option*, yk__sds*, int32_t);
yy__argparse_ArgParse yy__argparse_new(yy__argparse_Option*, yk__sds*);
void yy__argparse_set_description(yy__argparse_ArgParse, yk__sds, yk__sds);
void yy__argparse_del_argparse(yy__argparse_ArgParse);
yy__argparse_ArgParseRemainder yy__argparse_parse(yy__argparse_ArgParse, yk__sds*);
void yy__argparse_usage(yy__argparse_ArgParse);
void yy__argparse_del_remainder(yy__argparse_ArgParseRemainder);
yy__argparse_Option yy__argparse_opt_help();
yy__argparse_Option yy__argparse_opt_boolean(yk__sds, yk__sds, int32_t*, yk__sds);
yy__argparse_Option yy__argparse_opt_string(yk__sds, yk__sds, yy__c_CStr, yk__sds);
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
yk__sds yy__strings_from_cstr(yy__c_CStr);
yk__sds yy__strings_from_cstrlen(yy__c_CStr, int32_t);
yk__sds yy__strings_from_cstrlen_after(yy__c_CStr, int32_t, int32_t);
yy__c_CStr yy__strings_to_cstr(yk__sds);
void yy__strings_del_cstr(yy__c_CStr);
void yy__strings_del_str(yy__c_CStr);
yy__strings_Utf8IterateState yy__strings_new_iter(yk__sds);
void yy__strings_del_iter(yy__strings_Utf8IterateState);
bool yy__strings_iterate(yy__strings_Utf8IterateState);
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
int32_t yy__perform_run(yk__sds, bool, bool);
int32_t yy__handle_args(yy__os_arguments);
int32_t yy__main();
// --structs-- 
struct yy__raylib_support_CObject {
    yk__sds yy__raylib_support_c_file;
    yk__sds yy__raylib_support_o_file;
    yk__sds yy__raylib_support_base_name;
    yk__sds* yy__raylib_support_args;
};
struct yy__configuration_CCode {
    yk__sds* yy__configuration_include_paths;
    yk__sds* yy__configuration_defines;
    yk__sds* yy__configuration_compiler_defines;
    yk__sds* yy__configuration_includes;
    yk__sds* yy__configuration_system_includes;
    yk__sds* yy__configuration_c_code;
    yk__sds* yy__configuration_cpp_code;
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
    bool yy__configuration_web;
};
struct yy__configuration_Config {
    yk__sds yy__configuration_runtime_path;
    yk__sds yy__configuration_compiler_path;
    yk__sds yy__configuration_libs_path;
    yk__sds yy__configuration_zig_compiler_path;
    yk__sds yy__configuration_emcc_compiler_path;
    yk__sds yy__configuration_emrun_path;
    struct yy__configuration_CCode* yy__configuration_c_code;
    struct yy__configuration_Project* yy__configuration_project;
    struct yy__configuration_Compilation* yy__configuration_compilation;
    yk__sds* yy__configuration_errors;
};
// --functions-- 
struct yy__raylib_support_CObject* yy__raylib_support_fill_arguments(yk__sds yy__raylib_support_src_path, struct yy__raylib_support_CObject* yy__raylib_support_c) 
{
    yk__sds t__0 = yk__sdsnew("-std=gnu99");
    yk__sds t__1 = yk__sdsnew("-DPLATFORM_DESKTOP");
    yk__sds t__2 = yk__sdsnew("-DGL_SILENCE_DEPRECATION=199309L");
    yk__sds t__3 = yk__sdsnew("-fno-sanitize=undefined");
    yk__sds* yy__raylib_support_args = yy__array_new(4, yk__sdsdup(t__0), yk__sdsdup(t__1), yk__sdsdup(t__2), yk__sdsdup(t__3));
    yk__sds t__4 = yk__sdsnew("-I");
    yk__sds t__5 = yk__sdscatsds(yk__sdsdup(t__4), yy__raylib_support_src_path);
    yk__arrput(yy__raylib_support_args, yk__sdsdup(t__5));
    yk__sds t__6 = yk__sdsnew("external");
    yk__sds t__7 = yy__path_join(yk__sdsdup(yy__raylib_support_src_path), yk__sdsdup(t__6));
    yk__sds yy__raylib_support_external = yk__sdsdup((t__7));
    yk__sds t__8 = yk__sdsnew("glfw");
    yk__sds t__9 = yy__path_join(yk__sdsdup(yy__raylib_support_external), yk__sdsdup(t__8));
    yk__sds yy__raylib_support_glfw = yk__sdsdup((t__9));
    yk__sds t__10 = yk__sdsnew("-I");
    yk__sds t__11 = yk__sdsnew("include");
    yk__sds t__12 = yy__path_join(yk__sdsdup(yy__raylib_support_glfw), yk__sdsdup(t__11));
    yk__sds t__13 = yk__sdscatsds(yk__sdsdup(t__10), (t__12));
    yk__arrput(yy__raylib_support_args, yk__sdsdup(t__13));
    if (yy__os_is_windows())
    {
        yk__sds t__14 = yk__sdsnew("-I");
        yk__sds t__15 = yk__sdsnew("deps");
        yk__sds t__16 = yy__path_join(yk__sdsdup(yy__raylib_support_glfw), yk__sdsdup(t__15));
        yk__sds t__17 = yk__sdsnew("mingw");
        yk__sds t__18 = yy__path_join(yk__sdsdup((t__16)), yk__sdsdup(t__17));
        yk__sds t__19 = yk__sdscatsds(yk__sdsdup(t__14), (t__18));
        yk__arrput(yy__raylib_support_args, yk__sdsdup(t__19));
        yk__sdsfree(t__19);
        yk__sdsfree(t__18);
        yk__sdsfree(t__17);
        yk__sdsfree(t__16);
        yk__sdsfree(t__15);
        yk__sdsfree(t__14);
    }
    yk__sds t__20 = yk__sdsnew("rglfw");
    if ((yy__os_is_macos() && (yk__sdscmp(yy__raylib_support_c->yy__raylib_support_base_name , t__20) == 0)))
    {
        yk__sds t__21 = yk__sdsnew("-ObjC");
        yk__arrput(yy__raylib_support_args, yk__sdsdup(t__21));
        yk__sdsfree(t__21);
    }
    yk__arrput(yy__raylib_support_args, yk__sdsdup(yy__raylib_support_c->yy__raylib_support_c_file));
    yk__sds t__22 = yk__sdsnew("-o");
    yk__arrput(yy__raylib_support_args, yk__sdsdup(t__22));
    yk__arrput(yy__raylib_support_args, yk__sdsdup(yy__raylib_support_c->yy__raylib_support_o_file));
    yy__raylib_support_c->yy__raylib_support_args = yy__raylib_support_args;
    struct yy__raylib_support_CObject* t__23 = yy__raylib_support_c;
    yk__sdsfree(t__22);
    yk__sdsfree(t__20);
    yk__sdsfree(t__13);
    yk__sdsfree(t__12);
    yk__sdsfree(t__11);
    yk__sdsfree(t__10);
    yk__sdsfree(yy__raylib_support_glfw);
    yk__sdsfree(t__9);
    yk__sdsfree(t__8);
    yk__sdsfree(yy__raylib_support_external);
    yk__sdsfree(t__7);
    yk__sdsfree(t__6);
    yk__sdsfree(t__5);
    yk__sdsfree(t__4);
    yk__sdsfree(t__3);
    yk__sdsfree(t__2);
    yk__sdsfree(t__1);
    yk__sdsfree(t__0);
    yk__sdsfree(yy__raylib_support_src_path);
    return t__23;
}
struct yy__raylib_support_CObject* yy__raylib_support_fill_web_arguments(yk__sds yy__raylib_support_src_path, struct yy__raylib_support_CObject* yy__raylib_support_c) 
{
    yk__sds t__24 = yk__sdsnew("-std=gnu99");
    yk__sds t__25 = yk__sdsnew("-DPLATFORM_WEB");
    yk__sds t__26 = yk__sdsnew("-DGRAPHICS_API_OPENGL_ES2");
    yk__sds t__27 = yk__sdsnew("-Oz");
    yk__sds* yy__raylib_support_args = yy__array_new(4, yk__sdsdup(t__24), yk__sdsdup(t__25), yk__sdsdup(t__26), yk__sdsdup(t__27));
    yk__arrput(yy__raylib_support_args, yk__sdsdup(yy__raylib_support_c->yy__raylib_support_c_file));
    yk__sds t__28 = yk__sdsnew("-o");
    yk__arrput(yy__raylib_support_args, yk__sdsdup(t__28));
    yk__arrput(yy__raylib_support_args, yk__sdsdup(yy__raylib_support_c->yy__raylib_support_o_file));
    yy__raylib_support_c->yy__raylib_support_args = yy__raylib_support_args;
    struct yy__raylib_support_CObject* t__29 = yy__raylib_support_c;
    yk__sdsfree(t__28);
    yk__sdsfree(t__27);
    yk__sdsfree(t__26);
    yk__sdsfree(t__25);
    yk__sdsfree(t__24);
    yk__sdsfree(yy__raylib_support_src_path);
    return t__29;
}
struct yy__raylib_support_CObject* yy__raylib_support_co(yk__sds yy__raylib_support_filename, yk__sds yy__raylib_support_src_path, yk__sds yy__raylib_support_target_path, bool yy__raylib_support_web) 
{
    struct yy__raylib_support_CObject* yy__raylib_support_obj = calloc(1, sizeof(struct yy__raylib_support_CObject));
    yk__sds t__30 = yk__sdsnew(".c");
    yk__sds t__31 = yk__sdscatsds(yk__sdsdup(yy__raylib_support_filename), t__30);
    yk__sds t__32 = yy__path_join(yk__sdsdup(yy__raylib_support_src_path), yk__sdsdup(t__31));
    yk__sdsfree(yy__raylib_support_obj->yy__raylib_support_c_file);
    yy__raylib_support_obj->yy__raylib_support_c_file = yk__sdsdup((t__32));
    if (yy__raylib_support_web)
    {
        yk__sds t__33 = yk__sdsnew("web-");
        yk__sds t__34 = yk__sdscatsds(yk__sdsdup(t__33), yy__raylib_support_filename);
        yk__sdsfree(yy__raylib_support_obj->yy__raylib_support_base_name);
        yy__raylib_support_obj->yy__raylib_support_base_name = yk__sdsdup(t__34);
        yk__sds t__35 = yk__sdsnew(".o");
        yk__sds t__36 = yk__sdscatsds(yk__sdsdup(yy__raylib_support_obj->yy__raylib_support_base_name), t__35);
        yk__sds t__37 = yy__path_join(yk__sdsdup(yy__raylib_support_target_path), yk__sdsdup(t__36));
        yk__sdsfree(yy__raylib_support_obj->yy__raylib_support_o_file);
        yy__raylib_support_obj->yy__raylib_support_o_file = yk__sdsdup((t__37));
        yy__raylib_support_obj = yy__raylib_support_fill_web_arguments(yk__sdsdup(yy__raylib_support_src_path), yy__raylib_support_obj);
        yk__sdsfree(t__37);
        yk__sdsfree(t__36);
        yk__sdsfree(t__35);
        yk__sdsfree(t__34);
        yk__sdsfree(t__33);
    }
    else
    {
        yk__sdsfree(yy__raylib_support_obj->yy__raylib_support_base_name);
        yy__raylib_support_obj->yy__raylib_support_base_name = yk__sdsdup(yy__raylib_support_filename);
        yk__sds t__38 = yk__sdsnew(".o");
        yk__sds t__39 = yk__sdscatsds(yk__sdsdup(yy__raylib_support_filename), t__38);
        yk__sds t__40 = yy__path_join(yk__sdsdup(yy__raylib_support_target_path), yk__sdsdup(t__39));
        yk__sdsfree(yy__raylib_support_obj->yy__raylib_support_o_file);
        yy__raylib_support_obj->yy__raylib_support_o_file = yk__sdsdup((t__40));
        yy__raylib_support_obj = yy__raylib_support_fill_arguments(yk__sdsdup(yy__raylib_support_src_path), yy__raylib_support_obj);
        yk__sdsfree(t__40);
        yk__sdsfree(t__39);
        yk__sdsfree(t__38);
    }
    struct yy__raylib_support_CObject* t__41 = yy__raylib_support_obj;
    yk__sdsfree(t__32);
    yk__sdsfree(t__31);
    yk__sdsfree(t__30);
    yk__sdsfree(yy__raylib_support_target_path);
    yk__sdsfree(yy__raylib_support_src_path);
    yk__sdsfree(yy__raylib_support_filename);
    return t__41;
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
    if ((yk__arrlen(yy__raylib_support_x) == 0))
    {
        yk__arrfree(yy__raylib_support_x);
        return;
    }
    int32_t yy__raylib_support_pos = 0;
    int32_t yy__raylib_support_length = yk__arrlen(yy__raylib_support_x);
    while (1) {
        if (!((yy__raylib_support_pos < yy__raylib_support_length))) { break; } // Check
        // Body of while loop

        {
            yy__raylib_support_del_c_object(yy__raylib_support_x[yy__raylib_support_pos]);
            yy__raylib_support_pos = (yy__raylib_support_pos + 1);
        }
    }
    yk__arrfree(yy__raylib_support_x);
    return;
}
struct yy__raylib_support_CObject** yy__raylib_support_get_objects(yk__sds yy__raylib_support_raylib_src_path, yk__sds yy__raylib_support_gui_path, yk__sds yy__raylib_support_extra_path, yk__sds yy__raylib_support_build_path, bool yy__raylib_support_web) 
{
    struct yy__raylib_support_CObject** yy__raylib_support_objects = NULL;
    if ((! (yy__raylib_support_web)))
    {
        yk__sds t__42 = yk__sdsnew("rglfw");
        yk__arrput(yy__raylib_support_objects, yy__raylib_support_co(yk__sdsdup(t__42), yk__sdsdup(yy__raylib_support_raylib_src_path), yk__sdsdup(yy__raylib_support_build_path), yy__raylib_support_web));
        yk__sdsfree(t__42);
    }
    yk__sds t__43 = yk__sdsnew("raudio");
    yk__arrput(yy__raylib_support_objects, yy__raylib_support_co(yk__sdsdup(t__43), yk__sdsdup(yy__raylib_support_raylib_src_path), yk__sdsdup(yy__raylib_support_build_path), yy__raylib_support_web));
    yk__sds t__44 = yk__sdsnew("rcore");
    yk__arrput(yy__raylib_support_objects, yy__raylib_support_co(yk__sdsdup(t__44), yk__sdsdup(yy__raylib_support_raylib_src_path), yk__sdsdup(yy__raylib_support_build_path), yy__raylib_support_web));
    yk__sds t__45 = yk__sdsnew("rmodels");
    yk__arrput(yy__raylib_support_objects, yy__raylib_support_co(yk__sdsdup(t__45), yk__sdsdup(yy__raylib_support_raylib_src_path), yk__sdsdup(yy__raylib_support_build_path), yy__raylib_support_web));
    yk__sds t__46 = yk__sdsnew("rshapes");
    yk__arrput(yy__raylib_support_objects, yy__raylib_support_co(yk__sdsdup(t__46), yk__sdsdup(yy__raylib_support_raylib_src_path), yk__sdsdup(yy__raylib_support_build_path), yy__raylib_support_web));
    yk__sds t__47 = yk__sdsnew("rtext");
    yk__arrput(yy__raylib_support_objects, yy__raylib_support_co(yk__sdsdup(t__47), yk__sdsdup(yy__raylib_support_raylib_src_path), yk__sdsdup(yy__raylib_support_build_path), yy__raylib_support_web));
    yk__sds t__48 = yk__sdsnew("rtextures");
    yk__arrput(yy__raylib_support_objects, yy__raylib_support_co(yk__sdsdup(t__48), yk__sdsdup(yy__raylib_support_raylib_src_path), yk__sdsdup(yy__raylib_support_build_path), yy__raylib_support_web));
    yk__sds t__49 = yk__sdsnew("utils");
    yk__arrput(yy__raylib_support_objects, yy__raylib_support_co(yk__sdsdup(t__49), yk__sdsdup(yy__raylib_support_raylib_src_path), yk__sdsdup(yy__raylib_support_build_path), yy__raylib_support_web));
    yk__sds t__50 = yk__sdsnew("rayextras");
    struct yy__raylib_support_CObject* yy__raylib_support_extra = yy__raylib_support_co(yk__sdsdup(t__50), yk__sdsdup(yy__raylib_support_extra_path), yk__sdsdup(yy__raylib_support_build_path), yy__raylib_support_web);
    yk__sds t__51 = yk__sdsnew("-I");
    yk__sds t__52 = yk__sdscatsds(yk__sdsdup(t__51), yy__raylib_support_raylib_src_path);
    yk__arrput(yy__raylib_support_extra->yy__raylib_support_args, yk__sdsdup(t__52));
    yk__sds t__53 = yk__sdsnew("-I");
    yk__sds t__54 = yk__sdscatsds(yk__sdsdup(t__53), yy__raylib_support_gui_path);
    yk__arrput(yy__raylib_support_extra->yy__raylib_support_args, yk__sdsdup(t__54));
    yk__arrput(yy__raylib_support_objects, yy__raylib_support_extra);
    struct yy__raylib_support_CObject** t__55 = yy__raylib_support_objects;
    yk__sdsfree(t__54);
    yk__sdsfree(t__53);
    yk__sdsfree(t__52);
    yk__sdsfree(t__51);
    yk__sdsfree(t__50);
    yk__sdsfree(t__49);
    yk__sdsfree(t__48);
    yk__sdsfree(t__47);
    yk__sdsfree(t__46);
    yk__sdsfree(t__45);
    yk__sdsfree(t__44);
    yk__sdsfree(t__43);
    yk__sdsfree(yy__raylib_support_build_path);
    yk__sdsfree(yy__raylib_support_extra_path);
    yk__sdsfree(yy__raylib_support_gui_path);
    yk__sdsfree(yy__raylib_support_raylib_src_path);
    return t__55;
}
yk__sds* yy__raylib_support_get_external_libs() 
{
    yk__sds* yy__raylib_support_external_libs = NULL;
    if (yy__os_is_windows())
    {
        yk__sds t__56 = yk__sdsnew("-lwinmm");
        yk__sds t__57 = yk__sdsnew("-lgdi32");
        yk__sds t__58 = yk__sdsnew("-lopengl32");
        yy__raylib_support_external_libs = yy__array_new(3, yk__sdsdup(t__56), yk__sdsdup(t__57), yk__sdsdup(t__58));
        yk__sdsfree(t__58);
        yk__sdsfree(t__57);
        yk__sdsfree(t__56);
    }
    else
    {
        if (yy__os_is_macos())
        {
            yk__sds t__59 = yk__sdsnew("-framework");
            yk__sds t__60 = yk__sdsnew("Foundation");
            yk__sds t__61 = yk__sdsnew("-framework");
            yk__sds t__62 = yk__sdsnew("OpenGL");
            yk__sds t__63 = yk__sdsnew("-framework");
            yk__sds t__64 = yk__sdsnew("OpenAL");
            yk__sds t__65 = yk__sdsnew("-framework");
            yk__sds t__66 = yk__sdsnew("IOKit");
            yk__sds t__67 = yk__sdsnew("-framework");
            yk__sds t__68 = yk__sdsnew("CoreVideo");
            yk__sds t__69 = yk__sdsnew("-framework");
            yk__sds t__70 = yk__sdsnew("Cocoa");
            yy__raylib_support_external_libs = yy__array_new(12, yk__sdsdup(t__59), yk__sdsdup(t__60), yk__sdsdup(t__61), yk__sdsdup(t__62), yk__sdsdup(t__63), yk__sdsdup(t__64), yk__sdsdup(t__65), yk__sdsdup(t__66), yk__sdsdup(t__67), yk__sdsdup(t__68), yk__sdsdup(t__69), yk__sdsdup(t__70));
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
        }
        else
        {
            yk__sds t__71 = yk__sdsnew("-lGL");
            yk__sds t__72 = yk__sdsnew("-lrt");
            yk__sds t__73 = yk__sdsnew("-ldl");
            yk__sds t__74 = yk__sdsnew("-lm");
            yk__sds t__75 = yk__sdsnew("-lX11");
            yy__raylib_support_external_libs = yy__array_new(5, yk__sdsdup(t__71), yk__sdsdup(t__72), yk__sdsdup(t__73), yk__sdsdup(t__74), yk__sdsdup(t__75));
            yk__sdsfree(t__75);
            yk__sdsfree(t__74);
            yk__sdsfree(t__73);
            yk__sdsfree(t__72);
            yk__sdsfree(t__71);
        }
    }
    yk__sds* t__76 = yy__raylib_support_external_libs;
    return t__76;
}
yk__sds* yy__raylib_support_get_web_args() 
{
    yk__sds t__77 = yk__sdsnew("-s");
    yk__sds t__78 = yk__sdsnew("USE_GLFW=3");
    yk__sds t__79 = yk__sdsnew("-s");
    yk__sds t__80 = yk__sdsnew("ASYNCIFY");
    yk__sds t__81 = yk__sdsnew("-DPLATFORM_WEB");
    yk__sds* yy__raylib_support_web_args = yy__array_new(5, yk__sdsdup(t__77), yk__sdsdup(t__78), yk__sdsdup(t__79), yk__sdsdup(t__80), yk__sdsdup(t__81));
    yk__sds* t__82 = yy__raylib_support_web_args;
    yk__sdsfree(t__81);
    yk__sdsfree(t__80);
    yk__sdsfree(t__79);
    yk__sdsfree(t__78);
    yk__sdsfree(t__77);
    return t__82;
}
bool yy__raylib_support_produce_object(struct yy__raylib_support_CObject* yy__raylib_support_c, struct yy__configuration_Config* yy__raylib_support_conf) 
{
    yk__sds t__83 = yk__sdsnew("raylib::");
    yy__console_cyan(yk__sdsdup(t__83));
    yy__console_yellow(yk__sdsdup(yy__raylib_support_c->yy__raylib_support_base_name));
    yk__sds t__84 = yk__sdsnew(" := ");
    yy__console_cyan(yk__sdsdup(t__84));
    if (yy__path_readable(yk__sdsdup(yy__raylib_support_c->yy__raylib_support_o_file)))
    {
        yk__sds t__85 = yk__sdsnew("prebuilt.\n");
        yy__console_green(yk__sdsdup(t__85));
        yk__sdsfree(t__85);
        yk__sdsfree(t__84);
        yk__sdsfree(t__83);
        return true;
        yk__sdsfree(t__85);
    }
    yk__sds* yy__raylib_support_cmd = NULL;
    if (yy__raylib_support_conf->yy__configuration_compilation->yy__configuration_web)
    {
        yk__sds t__86 = yk__sdsnew("-c");
        yk__sds t__87 = yk__sdsnew("-Oz");
        yy__raylib_support_cmd = yy__array_new(3, yk__sdsdup(yy__raylib_support_conf->yy__configuration_emcc_compiler_path), yk__sdsdup(t__86), yk__sdsdup(t__87));
        yk__sdsfree(t__87);
        yk__sdsfree(t__86);
    }
    else
    {
        yk__sds t__88 = yk__sdsnew("cc");
        yk__sds t__89 = yk__sdsnew("-c");
        yk__sds t__90 = yk__sdsnew("-Oz");
        yy__raylib_support_cmd = yy__array_new(4, yk__sdsdup(yy__raylib_support_conf->yy__configuration_zig_compiler_path), yk__sdsdup(t__88), yk__sdsdup(t__89), yk__sdsdup(t__90));
        yk__sdsfree(t__90);
        yk__sdsfree(t__89);
        yk__sdsfree(t__88);
    }
    yy__raylib_support_cmd = yy__array_extend(yy__raylib_support_cmd, yy__raylib_support_c->yy__raylib_support_args);
    yy__os_ProcessResult yy__raylib_support_pr = yy__os_run(yy__raylib_support_cmd);
    if (yy__raylib_support_pr->ok)
    {
        yk__sds t__91 = yk__sdsnew("done.\n");
        yy__console_green(yk__sdsdup(t__91));
        yy__os_del_process_result(yy__raylib_support_pr);
        yy__array_del_str_array(yy__raylib_support_cmd);
        yk__sdsfree(t__91);
        yk__sdsfree(t__84);
        yk__sdsfree(t__83);
        return true;
        yk__sdsfree(t__91);
    }
    yk__sds t__92 = yk__sdsnew("failed.\n");
    yy__console_red(yk__sdsdup(t__92));
    yk__sds t__93 = yk__sdsnew("--c compiler output---\n");
    yy__console_cyan(yk__sdsdup(t__93));
    yk__sds t__94 = yk__sdsnew("command := ");
    yy__console_red(yk__sdsdup(t__94));
    yk__sds t__95 = yk__sdsnew(" ");
    yk__sds t__96 = yy__array_join(yy__raylib_support_cmd, yk__sdsdup(t__95));
    yk__sds t__97 = yk__sdsnew("\n");
    yk__sds t__98 = yk__sdscatsds(yk__sdsdup((t__96)), t__97);
    yy__console_cyan(yk__sdsdup(t__98));
    yy__console_red(yk__sdsdup(yy__raylib_support_pr->output));
    yk__sds t__99 = yk__sdsnew("--end c compiler output---\n");
    yy__console_cyan(yk__sdsdup(t__99));
    yy__os_del_process_result(yy__raylib_support_pr);
    yy__array_del_str_array(yy__raylib_support_cmd);
    yk__sdsfree(t__99);
    yk__sdsfree(t__98);
    yk__sdsfree(t__97);
    yk__sdsfree(t__96);
    yk__sdsfree(t__95);
    yk__sdsfree(t__94);
    yk__sdsfree(t__93);
    yk__sdsfree(t__92);
    yk__sdsfree(t__84);
    yk__sdsfree(t__83);
    return false;
}
yk__sds* yy__raylib_support_get_raylib_args(struct yy__configuration_Config* yy__raylib_support_conf) 
{
    yk__sds* yy__raylib_support_arguments = NULL;
    yk__sds yy__raylib_support_runtime_path = yk__sdsdup(yy__raylib_support_conf->yy__configuration_runtime_path);
    yk__sds t__100 = yy__os_cwd();
    yk__sds t__101 = yk__sdsnew("build");
    yk__sds t__102 = yy__path_join(yk__sdsdup((t__100)), yk__sdsdup(t__101));
    yk__sds yy__raylib_support_build_path = yk__sdsdup((t__102));
    yy__path_mkdir(yk__sdsdup(yy__raylib_support_build_path));
    yk__sds t__103 = yk__sdsnew("raylib");
    yk__sds t__104 = yy__path_join(yk__sdsdup(yy__raylib_support_runtime_path), yk__sdsdup(t__103));
    yk__sds t__105 = yk__sdsnew("src");
    yk__sds t__106 = yy__path_join(yk__sdsdup((t__104)), yk__sdsdup(t__105));
    yk__sds yy__raylib_support_raylib_path = yk__sdsdup((t__106));
    yk__sds t__107 = yk__sdsnew("raygui");
    yk__sds t__108 = yy__path_join(yk__sdsdup(yy__raylib_support_runtime_path), yk__sdsdup(t__107));
    yk__sds t__109 = yk__sdsnew("src");
    yk__sds t__110 = yy__path_join(yk__sdsdup((t__108)), yk__sdsdup(t__109));
    yk__sds yy__raylib_support_raygui_path = yk__sdsdup((t__110));
    yk__sds t__111 = yk__sdsnew("raylib_additional");
    yk__sds t__112 = yy__path_join(yk__sdsdup(yy__raylib_support_runtime_path), yk__sdsdup(t__111));
    yk__sds yy__raylib_support_rayextra_path = yk__sdsdup((t__112));
    struct yy__raylib_support_CObject** yy__raylib_support_objects = yy__raylib_support_get_objects(yk__sdsdup(yy__raylib_support_raylib_path), yk__sdsdup(yy__raylib_support_raygui_path), yk__sdsdup(yy__raylib_support_rayextra_path), yk__sdsdup(yy__raylib_support_build_path), yy__raylib_support_conf->yy__configuration_compilation->yy__configuration_web);
    yk__sds* yy__raylib_support_o_files = NULL;
    int32_t yy__raylib_support_object_count = yk__arrlen(yy__raylib_support_objects);
    int32_t yy__raylib_support_pos = 0;
    bool yy__raylib_support_fail = false;
    yk__sds t__113 = yk__sdsnew("\nbuilding raylib ...");
    yk__printlnstr((t__113));
    while (1) {
        if (!((yy__raylib_support_pos < yy__raylib_support_object_count))) { break; } // Check
        // Body of while loop

        {
            struct yy__raylib_support_CObject* yy__raylib_support_object = yy__raylib_support_objects[yy__raylib_support_pos];
            if (yy__raylib_support_produce_object(yy__raylib_support_object, yy__raylib_support_conf))
            {
                yk__arrput(yy__raylib_support_o_files, yk__sdsdup(yy__raylib_support_object->yy__raylib_support_o_file));
            }
            else
            {
                yy__raylib_support_fail = true;
                break;
            }
            yy__raylib_support_pos = (yy__raylib_support_pos + 1);
        }
    }
    if (yy__raylib_support_fail)
    {
        yk__sds* t__114 = yy__raylib_support_arguments;
        yy__raylib_support_del_objects(yy__raylib_support_objects);
        yy__array_del_str_array(yy__raylib_support_o_files);
        yk__sdsfree(t__113);
        yk__sdsfree(yy__raylib_support_rayextra_path);
        yk__sdsfree(t__112);
        yk__sdsfree(t__111);
        yk__sdsfree(yy__raylib_support_raygui_path);
        yk__sdsfree(t__110);
        yk__sdsfree(t__109);
        yk__sdsfree(t__108);
        yk__sdsfree(t__107);
        yk__sdsfree(yy__raylib_support_raylib_path);
        yk__sdsfree(t__106);
        yk__sdsfree(t__105);
        yk__sdsfree(t__104);
        yk__sdsfree(t__103);
        yk__sdsfree(yy__raylib_support_build_path);
        yk__sdsfree(t__102);
        yk__sdsfree(t__101);
        yk__sdsfree(t__100);
        yk__sdsfree(yy__raylib_support_runtime_path);
        return t__114;
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
            yk__sds t__115 = yk__sdsnew("-Wl,--subsystem,windows");
            yk__arrput(yy__raylib_support_arguments, yk__sdsdup(t__115));
            yk__sds t__116 = yk__sdsnew("-DYK__WINDOWS_HIDE_CONSOLE");
            yk__arrput(yy__raylib_support_arguments, yk__sdsdup(t__116));
            yk__sdsfree(t__116);
            yk__sdsfree(t__115);
        }
    }
    yk__sds t__117 = yk__sdsnew("-I");
    yk__sds t__118 = yk__sdscatsds(yk__sdsdup(t__117), yy__raylib_support_raylib_path);
    yk__arrput(yy__raylib_support_arguments, yk__sdsdup(t__118));
    yk__sds t__119 = yk__sdsnew("-I");
    yk__sds t__120 = yk__sdscatsds(yk__sdsdup(t__119), yy__raylib_support_raygui_path);
    yk__arrput(yy__raylib_support_arguments, yk__sdsdup(t__120));
    yk__sds t__121 = yk__sdsnew("-I");
    yk__sds t__122 = yk__sdscatsds(yk__sdsdup(t__121), yy__raylib_support_rayextra_path);
    yk__arrput(yy__raylib_support_arguments, yk__sdsdup(t__122));
    yk__sds* t__123 = yy__raylib_support_arguments;
    yy__raylib_support_del_objects(yy__raylib_support_objects);
    yy__array_del_str_array(yy__raylib_support_o_files);
    yk__sdsfree(t__122);
    yk__sdsfree(t__121);
    yk__sdsfree(t__120);
    yk__sdsfree(t__119);
    yk__sdsfree(t__118);
    yk__sdsfree(t__117);
    yk__sdsfree(t__113);
    yk__sdsfree(yy__raylib_support_rayextra_path);
    yk__sdsfree(t__112);
    yk__sdsfree(t__111);
    yk__sdsfree(yy__raylib_support_raygui_path);
    yk__sdsfree(t__110);
    yk__sdsfree(t__109);
    yk__sdsfree(t__108);
    yk__sdsfree(t__107);
    yk__sdsfree(yy__raylib_support_raylib_path);
    yk__sdsfree(t__106);
    yk__sdsfree(t__105);
    yk__sdsfree(t__104);
    yk__sdsfree(t__103);
    yk__sdsfree(yy__raylib_support_build_path);
    yk__sdsfree(t__102);
    yk__sdsfree(t__101);
    yk__sdsfree(t__100);
    yk__sdsfree(yy__raylib_support_runtime_path);
    return t__123;
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
    int32_t yy__building_length = 0;
    int32_t yy__building_x = 0;
    yy__building_length = yk__arrlen(yy__building_c->yy__configuration_c_code->yy__configuration_defines);
    yy__building_x = 0;
    while (1) {
        if (!((yy__building_x < yy__building_length))) { break; } // Check
        // Body of while loop

        {
            yk__sds t__0 = yk__sdsnew("#define ");
            yk__sds t__1 = yk__sdscatsds(yk__sdsdup(t__0), yy__building_c->yy__configuration_c_code->yy__configuration_defines[yy__building_x]);
            yk__sds t__2 = yk__sdsnew("\n");
            yk__sds t__3 = yk__sdscatsds(yk__sdsdup(t__1), t__2);
            yy__buffer_append(yy__building_buf, yk__sdsdup(t__3));
            yy__building_x = (yy__building_x + 1);
            yk__sdsfree(t__3);
            yk__sdsfree(t__2);
            yk__sdsfree(t__1);
            yk__sdsfree(t__0);
        }
    }
    yy__building_length = yk__arrlen(yy__building_c->yy__configuration_c_code->yy__configuration_system_includes);
    yy__building_x = 0;
    while (1) {
        if (!((yy__building_x < yy__building_length))) { break; } // Check
        // Body of while loop

        {
            yk__sds t__4 = yk__sdsnew("#include <");
            yk__sds t__5 = yk__sdscatsds(yk__sdsdup(t__4), yy__building_c->yy__configuration_c_code->yy__configuration_system_includes[yy__building_x]);
            yk__sds t__6 = yk__sdsnew(">\n");
            yk__sds t__7 = yk__sdscatsds(yk__sdsdup(t__5), t__6);
            yy__buffer_append(yy__building_buf, yk__sdsdup(t__7));
            yy__building_x = (yy__building_x + 1);
            yk__sdsfree(t__7);
            yk__sdsfree(t__6);
            yk__sdsfree(t__5);
            yk__sdsfree(t__4);
        }
    }
    yy__building_length = yk__arrlen(yy__building_c->yy__configuration_c_code->yy__configuration_includes);
    yy__building_x = 0;
    while (1) {
        if (!((yy__building_x < yy__building_length))) { break; } // Check
        // Body of while loop

        {
            yk__sds t__8 = yk__sdsnew("#include \"");
            yk__sds t__9 = yk__sdscatsds(yk__sdsdup(t__8), yy__building_c->yy__configuration_c_code->yy__configuration_includes[yy__building_x]);
            yk__sds t__10 = yk__sdsnew("\"\n");
            yk__sds t__11 = yk__sdscatsds(yk__sdsdup(t__9), t__10);
            yy__buffer_append(yy__building_buf, yk__sdsdup(t__11));
            yy__building_x = (yy__building_x + 1);
            yk__sdsfree(t__11);
            yk__sdsfree(t__10);
            yk__sdsfree(t__9);
            yk__sdsfree(t__8);
        }
    }
    if (yy__building_c->yy__configuration_compilation->yy__configuration_raylib)
    {
        yk__sds t__12 = yk__sdsnew("#include \"raylib.h\"\n");
        yy__buffer_append(yy__building_buf, yk__sdsdup(t__12));
        yk__sds t__13 = yk__sdsnew("#include \"raygui.h\"\n");
        yy__buffer_append(yy__building_buf, yk__sdsdup(t__13));
        yk__sds t__14 = yk__sdsnew("#include \"raymath.h\"\n");
        yy__buffer_append(yy__building_buf, yk__sdsdup(t__14));
        yk__sds t__15 = yk__sdsnew("#include \"rlgl.h\"\n");
        yy__buffer_append(yy__building_buf, yk__sdsdup(t__15));
        yk__sds t__16 = yk__sdsnew("#include \"rayextras.h\"\n");
        yy__buffer_append(yy__building_buf, yk__sdsdup(t__16));
        yk__sdsfree(t__16);
        yk__sdsfree(t__15);
        yk__sdsfree(t__14);
        yk__sdsfree(t__13);
        yk__sdsfree(t__12);
    }
    yy__buffer_append(yy__building_buf, yk__sdsdup(yy__building_code));
    yk__sds t__17 = yk__sdsnew("\n");
    yy__buffer_append(yy__building_buf, yk__sdsdup(t__17));
    yk__sds t__18 = yy__buffer_to_str(yy__building_buf);
    yk__sds yy__building_result = yk__sdsdup((t__18));
    yk__sds t__19 = yy__building_result;
    yy__buffer_del_buf(yy__building_buf);
    yk__sdsfree(t__18);
    yk__sdsfree(t__17);
    yk__sdsfree(yy__building_code);
    return t__19;
}
bool yy__building_is_target_macos(yk__sds yy__building_target_to_check) 
{
    bool yy__building_native = (yk__sdslen(yy__building_target_to_check) == 0);
    if (yy__building_native)
    {
        bool t__20 = yy__os_is_macos();
        yk__sdsfree(yy__building_target_to_check);
        return t__20;
    }
    yk__sds t__21 = yk__sdsnew("macos");
    bool t__22 = yy__strings_contains(yk__sdsdup(yy__building_target_to_check), yk__sdsdup(t__21));
    yk__sdsfree(t__21);
    yk__sdsfree(yy__building_target_to_check);
    return t__22;
}
bool yy__building_is_target_windows(yk__sds yy__building_target_to_check) 
{
    bool yy__building_native = (yk__sdslen(yy__building_target_to_check) == 0);
    if (yy__building_native)
    {
        bool t__23 = yy__os_is_windows();
        yk__sdsfree(yy__building_target_to_check);
        return t__23;
    }
    yk__sds t__24 = yk__sdsnew("windows");
    bool t__25 = yy__strings_contains(yk__sdsdup(yy__building_target_to_check), yk__sdsdup(t__24));
    yk__sdsfree(t__24);
    yk__sdsfree(yy__building_target_to_check);
    return t__25;
}
yk__sds* yy__building_create_args(struct yy__configuration_Config* yy__building_c, yk__sds yy__building_code_path, yk__sds yy__building_build_path, yk__sds yy__building_target, yk__sds* yy__building_raylib_args) 
{
    bool yy__building_native = (yk__sdslen(yy__building_target) == 0);
    yk__sds* yy__building_args = NULL;
    if (yy__building_c->yy__configuration_compilation->yy__configuration_web)
    {
        yk__sds t__26 = yk__sdsnew("-std=c99");
        yk__sds t__27 = yk__sdsnew("-Oz");
        yk__sds t__28 = yk__sdsnew("-Wno-newline-eof");
        yk__sds t__29 = yk__sdsnew("-Wno-parentheses-equality");
        yy__building_args = yy__array_new(5, yk__sdsdup(yy__building_c->yy__configuration_emcc_compiler_path), yk__sdsdup(t__26), yk__sdsdup(t__27), yk__sdsdup(t__28), yk__sdsdup(t__29));
        yk__sdsfree(t__29);
        yk__sdsfree(t__28);
        yk__sdsfree(t__27);
        yk__sdsfree(t__26);
    }
    else
    {
        yk__sds t__30 = yk__sdsnew("cc");
        yk__sds t__31 = yk__sdsnew("-std=c99");
        yk__sds t__32 = yk__sdsnew("-Oz");
        yk__sds t__33 = yk__sdsnew("-pedantic");
        yk__sds t__34 = yk__sdsnew("-Wall");
        yk__sds t__35 = yk__sdsnew("-Wno-newline-eof");
        yk__sds t__36 = yk__sdsnew("-fPIC");
        yk__sds t__37 = yk__sdsnew("-Wno-parentheses-equality");
        yy__building_args = yy__array_new(9, yk__sdsdup(yy__building_c->yy__configuration_zig_compiler_path), yk__sdsdup(t__30), yk__sdsdup(t__31), yk__sdsdup(t__32), yk__sdsdup(t__33), yk__sdsdup(t__34), yk__sdsdup(t__35), yk__sdsdup(t__36), yk__sdsdup(t__37));
        yk__sdsfree(t__37);
        yk__sdsfree(t__36);
        yk__sdsfree(t__35);
        yk__sdsfree(t__34);
        yk__sdsfree(t__33);
        yk__sdsfree(t__32);
        yk__sdsfree(t__31);
        yk__sdsfree(t__30);
    }
    yy__building_args = yy__array_extend(yy__building_args, yy__building_raylib_args);
    if ((! (yy__building_is_target_macos(yk__sdsdup(yy__building_target)))))
    {
        yk__sds t__38 = yk__sdsnew("-flto=full");
        yk__arrput(yy__building_args, yk__sdsdup(t__38));
        yk__sdsfree(t__38);
    }
    int32_t yy__building_length = 0;
    int32_t yy__building_x = 0;
    yy__building_length = yk__arrlen(yy__building_c->yy__configuration_c_code->yy__configuration_include_paths);
    yy__building_x = 0;
    while (1) {
        if (!((yy__building_x < yy__building_length))) { break; } // Check
        // Body of while loop

        {
            yk__sds t__39 = yk__sdsnew("-I");
            yk__sds t__40 = yk__sdscatsds(yk__sdsdup(t__39), yy__building_c->yy__configuration_c_code->yy__configuration_include_paths[yy__building_x]);
            yk__sds yy__building_include = yk__sdsdup(t__40);
            yk__arrput(yy__building_args, yk__sdsdup(yy__building_include));
            yy__building_x = (yy__building_x + 1);
            yk__sdsfree(yy__building_include);
            yk__sdsfree(t__40);
            yk__sdsfree(t__39);
        }
    }
    yy__building_length = yk__arrlen(yy__building_c->yy__configuration_c_code->yy__configuration_compiler_defines);
    yy__building_x = 0;
    while (1) {
        if (!((yy__building_x < yy__building_length))) { break; } // Check
        // Body of while loop

        {
            yk__sds t__41 = yk__sdsnew("-D");
            yk__sds t__42 = yk__sdscatsds(yk__sdsdup(t__41), yy__building_c->yy__configuration_c_code->yy__configuration_compiler_defines[yy__building_x]);
            yk__sds yy__building_cdefine = yk__sdsdup(t__42);
            yk__arrput(yy__building_args, yk__sdsdup(yy__building_cdefine));
            yy__building_x = (yy__building_x + 1);
            yk__sdsfree(yy__building_cdefine);
            yk__sdsfree(t__42);
            yk__sdsfree(t__41);
        }
    }
    yy__building_length = yk__arrlen(yy__building_c->yy__configuration_c_code->yy__configuration_c_code);
    yy__building_x = 0;
    while (1) {
        if (!((yy__building_x < yy__building_length))) { break; } // Check
        // Body of while loop

        {
            yk__sds yy__building_cc = yk__sdsdup(yy__building_c->yy__configuration_c_code->yy__configuration_c_code[yy__building_x]);
            yk__arrput(yy__building_args, yk__sdsdup(yy__building_cc));
            yy__building_x = (yy__building_x + 1);
            yk__sdsfree(yy__building_cc);
        }
    }
    yk__arrput(yy__building_args, yk__sdsdup(yy__building_code_path));
    yk__sds t__43 = yk__sdsnew("yk__main.c");
    yk__sds t__44 = yy__path_join(yk__sdsdup(yy__building_c->yy__configuration_runtime_path), yk__sdsdup(t__43));
    yk__sds yy__building_the_yk_main = yk__sdsdup((t__44));
    yk__arrput(yy__building_args, yk__sdsdup(yy__building_the_yk_main));
    yk__sds t__45 = yk__sdsnew("web");
    if (((! (yy__building_native)) && (yk__sdscmp(yy__building_target , t__45) != 0)))
    {
        yk__sds t__46 = yk__sdsnew("-target");
        yk__arrput(yy__building_args, yk__sdsdup(t__46));
        yk__arrput(yy__building_args, yk__sdsdup(yy__building_target));
        yk__sdsfree(t__46);
    }
    yk__sds t__47 = yk__sdsnew("-o");
    yk__arrput(yy__building_args, yk__sdsdup(t__47));
    yk__sds yy__building_binary = yk__sdsdup(yy__building_c->yy__configuration_project->yy__configuration_name);
    yk__sds t__48 = yk__sdsnew("web");
    if (((! (yy__building_native)) && (yk__sdscmp(yy__building_target , t__48) != 0)))
    {
        yk__sds t__49 = yk__sdsnew("-");
        yk__sds t__50 = yk__sdscatsds(yk__sdsdup(yy__building_binary), t__49);
        yk__sds t__51 = yk__sdscatsds(yk__sdsdup(t__50), yy__building_target);
        yk__sdsfree(yy__building_binary);
        yy__building_binary = yk__sdsdup(t__51);
        yk__sdsfree(t__51);
        yk__sdsfree(t__50);
        yk__sdsfree(t__49);
    }
    if (yy__building_is_target_windows(yk__sdsdup(yy__building_target)))
    {
        yk__sds t__52 = yk__sdsnew(".exe");
        yk__sds t__53 = yk__sdscatsds(yk__sdsdup(yy__building_binary), t__52);
        yk__sdsfree(yy__building_binary);
        yy__building_binary = yk__sdsdup(t__53);
        yk__sdsfree(t__53);
        yk__sdsfree(t__52);
    }
    yk__sds t__54 = yk__sdsnew("web");
    if ((yk__sdscmp(yy__building_target , t__54) == 0))
    {
        yk__sds t__55 = yk__sdsnew(".html");
        yk__sds t__56 = yk__sdscatsds(yk__sdsdup(yy__building_binary), t__55);
        yk__sdsfree(yy__building_binary);
        yy__building_binary = yk__sdsdup(t__56);
        yk__sdsfree(t__56);
        yk__sdsfree(t__55);
    }
    yk__sds t__57 = yy__path_join(yk__sdsdup(yy__building_build_path), yk__sdsdup(yy__building_binary));
    yk__sdsfree(yy__building_binary);
    yy__building_binary = yk__sdsdup((t__57));
    yk__arrput(yy__building_args, yk__sdsdup(yy__building_binary));
    yk__sds* t__58 = yy__building_args;
    yk__sdsfree(t__57);
    yk__sdsfree(t__54);
    yk__sdsfree(t__48);
    yk__sdsfree(yy__building_binary);
    yk__sdsfree(t__47);
    yk__sdsfree(t__45);
    yk__sdsfree(yy__building_the_yk_main);
    yk__sdsfree(t__44);
    yk__sdsfree(t__43);
    yk__sdsfree(yy__building_target);
    yk__sdsfree(yy__building_build_path);
    yk__sdsfree(yy__building_code_path);
    return t__58;
}
int32_t yy__building_build_target(struct yy__configuration_Config* yy__building_c, yk__sds yy__building_code_path, yk__sds yy__building_build_path, yk__sds yy__building_target, yk__sds* yy__building_raylib_args) 
{
    bool yy__building_native = (yk__sdslen(yy__building_target) == 0);
    yk__sds* yy__building_a = yy__building_create_args(yy__building_c, yk__sdsdup(yy__building_code_path), yk__sdsdup(yy__building_build_path), yk__sdsdup(yy__building_target), yy__building_raylib_args);
    yy__os_ProcessResult yy__building_result = yy__os_run(yy__building_a);
    if (yy__building_native)
    {
        yk__sds t__59 = yk__sdsnew("native");
        yy__console_yellow(yk__sdsdup(t__59));
        yk__sdsfree(t__59);
    }
    else
    {
        yy__console_yellow(yk__sdsdup(yy__building_target));
    }
    yk__sds t__60 = yk__sdsnew(" := ");
    yy__console_cyan(yk__sdsdup(t__60));
    if (yy__building_result->ok)
    {
        yk__sds t__61 = yk__sdsnew("done.\n");
        yy__console_green(yk__sdsdup(t__61));
        yy__os_del_process_result(yy__building_result);
        yy__array_del_str_array(yy__building_a);
        yk__sdsfree(t__61);
        yk__sdsfree(t__60);
        yk__sdsfree(yy__building_target);
        yk__sdsfree(yy__building_build_path);
        yk__sdsfree(yy__building_code_path);
        return 0;
        yk__sdsfree(t__61);
    }
    else
    {
        yk__sds t__62 = yk__sdsnew("failed.\n");
        yy__console_red(yk__sdsdup(t__62));
        yk__sds t__63 = yk__sdsnew("-------\n");
        yy__console_cyan(yk__sdsdup(t__63));
        yk__sds t__64 = yk__sdsnew("command := ");
        yy__console_red(yk__sdsdup(t__64));
        yk__sds t__65 = yk__sdsnew(" ");
        yk__sds t__66 = yy__array_join(yy__building_a, yk__sdsdup(t__65));
        yy__console_yellow(yk__sdsdup((t__66)));
        yk__sds t__67 = yk__sdsnew("\n-------\n");
        yy__console_cyan(yk__sdsdup(t__67));
        yy__console_red(yk__sdsdup(yy__building_result->output));
        yy__os_del_process_result(yy__building_result);
        yy__array_del_str_array(yy__building_a);
        yk__sdsfree(t__67);
        yk__sdsfree(t__66);
        yk__sdsfree(t__65);
        yk__sdsfree(t__64);
        yk__sdsfree(t__63);
        yk__sdsfree(t__62);
        yk__sdsfree(t__60);
        yk__sdsfree(yy__building_target);
        yk__sdsfree(yy__building_build_path);
        yk__sdsfree(yy__building_code_path);
        return 1;
        yk__sdsfree(t__67);
        yk__sdsfree(t__66);
        yk__sdsfree(t__65);
        yk__sdsfree(t__64);
        yk__sdsfree(t__63);
        yk__sdsfree(t__62);
    }
}
int32_t yy__building_build(struct yy__configuration_Config* yy__building_c, yk__sds yy__building_code) 
{
    int32_t yy__building_target_count = yk__arrlen(yy__building_c->yy__configuration_compilation->yy__configuration_targets);
    yk__sds* yy__building_raylib_args = NULL;
    if (((yy__building_target_count != 0) && yy__building_c->yy__configuration_compilation->yy__configuration_raylib))
    {
        yk__sds t__68 = yk__sdsnew("raylib build only support native builds.\n");
        yy__console_red(yk__sdsdup(t__68));
        yk__sds t__69 = yk__sdsnew("Hint: You need to keep [compilation].targets empty\n");
        yy__console_cyan(yk__sdsdup(t__69));
        int32_t t__70 = (- (1));
        yy__array_del_str_array(yy__building_raylib_args);
        yk__sdsfree(t__69);
        yk__sdsfree(t__68);
        yk__sdsfree(yy__building_code);
        return t__70;
        yk__sdsfree(t__69);
        yk__sdsfree(t__68);
    }
    if (yy__building_c->yy__configuration_compilation->yy__configuration_raylib)
    {
        yy__building_raylib_args = yy__raylib_support_get_raylib_args(yy__building_c);
    }
    yk__sds t__71 = yk__sdsnew("\nbuilding ");
    yk__printstr((t__71));
    yk__printint(((intmax_t)(yy__building_target_count + 1)));
    yk__sds t__72 = yk__sdsnew(" target(s) ...");
    yk__printlnstr((t__72));
    yk__sds t__73 = yy__os_cwd();
    yk__sds t__74 = yk__sdsnew("build");
    yk__sds t__75 = yy__path_join(yk__sdsdup((t__73)), yk__sdsdup(t__74));
    yk__sds yy__building_build_path = yk__sdsdup((t__75));
    yy__path_mkdir(yk__sdsdup(yy__building_build_path));
    yk__sds t__76 = yk__sdsnew("program_code.c");
    yk__sds t__77 = yy__path_join(yk__sdsdup(yy__building_build_path), yk__sdsdup(t__76));
    yk__sds yy__building_code_path = yk__sdsdup((t__77));
    yk__sds t__78 = yy__building_prepare_code(yy__building_c, yk__sdsdup(yy__building_code));
    if ((! (yy__io_writefile(yk__sdsdup(yy__building_code_path), yk__sdsdup((t__78))))))
    {
        yk__sds t__79 = yk__sdsnew("Failed to write file:");
        yy__console_red(yk__sdsdup(t__79));
        yk__printlnstr((yy__building_code_path));
        int32_t t__80 = (- (1));
        yy__array_del_str_array(yy__building_raylib_args);
        yk__sdsfree(t__79);
        yk__sdsfree(t__78);
        yk__sdsfree(yy__building_code_path);
        yk__sdsfree(t__77);
        yk__sdsfree(t__76);
        yk__sdsfree(yy__building_build_path);
        yk__sdsfree(t__75);
        yk__sdsfree(t__74);
        yk__sdsfree(t__73);
        yk__sdsfree(t__72);
        yk__sdsfree(t__71);
        yk__sdsfree(yy__building_code);
        return t__80;
        yk__sdsfree(t__79);
    }
    int32_t yy__building_failed_count = 0;
    yk__sds t__81 = yk__sdsempty();
    yy__building_failed_count = (yy__building_failed_count + yy__building_build_target(yy__building_c, yk__sdsdup(yy__building_code_path), yk__sdsdup(yy__building_build_path), yk__sdsdup(t__81), yy__building_raylib_args));
    int32_t yy__building_cnt = 0;
    while (1) {
        if (!((yy__building_cnt < yk__arrlen(yy__building_c->yy__configuration_compilation->yy__configuration_targets)))) { break; } // Check
        // Body of while loop

        {
            yk__sds yy__building_target = yk__sdsdup(yy__building_c->yy__configuration_compilation->yy__configuration_targets[yy__building_cnt]);
            yy__building_failed_count = (yy__building_failed_count + yy__building_build_target(yy__building_c, yk__sdsdup(yy__building_code_path), yk__sdsdup(yy__building_build_path), yk__sdsdup(yy__building_target), yy__building_raylib_args));
            yy__building_cnt = (yy__building_cnt + 1);
            yk__sdsfree(yy__building_target);
        }
    }
    yk__sds t__82 = yk__sdsnew("\n");
    yk__printstr((t__82));
    if ((yy__building_failed_count > 0))
    {
        int32_t t__83 = (- (1));
        yy__array_del_str_array(yy__building_raylib_args);
        yk__sdsfree(t__82);
        yk__sdsfree(t__81);
        yk__sdsfree(t__78);
        yk__sdsfree(yy__building_code_path);
        yk__sdsfree(t__77);
        yk__sdsfree(t__76);
        yk__sdsfree(yy__building_build_path);
        yk__sdsfree(t__75);
        yk__sdsfree(t__74);
        yk__sdsfree(t__73);
        yk__sdsfree(t__72);
        yk__sdsfree(t__71);
        yk__sdsfree(yy__building_code);
        return t__83;
    }
    yy__array_del_str_array(yy__building_raylib_args);
    yk__sdsfree(t__82);
    yk__sdsfree(t__81);
    yk__sdsfree(t__78);
    yk__sdsfree(yy__building_code_path);
    yk__sdsfree(t__77);
    yk__sdsfree(t__76);
    yk__sdsfree(yy__building_build_path);
    yk__sdsfree(t__75);
    yk__sdsfree(t__74);
    yk__sdsfree(t__73);
    yk__sdsfree(t__72);
    yk__sdsfree(t__71);
    yk__sdsfree(yy__building_code);
    return 0;
}
int32_t yy__building_build_simple(struct yy__configuration_Config* yy__building_c, yk__sds yy__building_code) 
{
    yk__sds t__84 = yy__os_cwd();
    yk__sds t__85 = yk__sdsnew(".c");
    yk__sds t__86 = yk__sdscatsds(yk__sdsdup(yy__building_c->yy__configuration_project->yy__configuration_name), t__85);
    yk__sds t__87 = yy__path_join(yk__sdsdup((t__84)), yk__sdsdup(t__86));
    yk__sds yy__building_code_path = yk__sdsdup((t__87));
    yk__sds* yy__building_raylib_args = NULL;
    yk__sds t__88 = yk__sdsempty();
    yk__sds yy__building_target = yk__sdsdup(t__88);
    if (yy__building_c->yy__configuration_compilation->yy__configuration_raylib)
    {
        yy__building_raylib_args = yy__raylib_support_get_raylib_args(yy__building_c);
    }
    if (yy__building_c->yy__configuration_compilation->yy__configuration_web)
    {
        yk__sds t__89 = yk__sdsnew("web");
        yk__sdsfree(yy__building_target);
        yy__building_target = yk__sdsdup(t__89);
        yk__sdsfree(t__89);
    }
    yk__sds t__90 = yy__building_prepare_code(yy__building_c, yk__sdsdup(yy__building_code));
    if ((! (yy__io_writefile(yk__sdsdup(yy__building_code_path), yk__sdsdup((t__90))))))
    {
        yk__sds t__91 = yk__sdsnew("Failed to write file:");
        yy__console_red(yk__sdsdup(t__91));
        yk__printlnstr((yy__building_code_path));
        int32_t t__92 = (- (1));
        yk__sdsfree(t__91);
        yk__sdsfree(t__90);
        yk__sdsfree(yy__building_target);
        yk__sdsfree(t__88);
        yk__sdsfree(yy__building_code_path);
        yk__sdsfree(t__87);
        yk__sdsfree(t__86);
        yk__sdsfree(t__85);
        yk__sdsfree(t__84);
        yk__sdsfree(yy__building_code);
        return t__92;
        yk__sdsfree(t__91);
    }
    yk__sds t__93 = yy__os_cwd();
    int32_t yy__building_failed_count = yy__building_build_target(yy__building_c, yk__sdsdup(yy__building_code_path), yk__sdsdup((t__93)), yk__sdsdup(yy__building_target), yy__building_raylib_args);
    if ((yy__building_failed_count > 0))
    {
        int32_t t__94 = (- (1));
        yk__sdsfree(t__93);
        yk__sdsfree(t__90);
        yk__sdsfree(yy__building_target);
        yk__sdsfree(t__88);
        yk__sdsfree(yy__building_code_path);
        yk__sdsfree(t__87);
        yk__sdsfree(t__86);
        yk__sdsfree(t__85);
        yk__sdsfree(t__84);
        yk__sdsfree(yy__building_code);
        return t__94;
    }
    yk__sdsfree(t__93);
    yk__sdsfree(t__90);
    yk__sdsfree(yy__building_target);
    yk__sdsfree(t__88);
    yk__sdsfree(yy__building_code_path);
    yk__sdsfree(t__87);
    yk__sdsfree(t__86);
    yk__sdsfree(t__85);
    yk__sdsfree(t__84);
    yk__sdsfree(yy__building_code);
    return 0;
}
void yy__configuration_find_runtime_path(struct yy__configuration_Config* yy__configuration_c) 
{
    yk__sds t__0 = yy__os_exe_path();
    yk__sds yy__configuration_exe_parent = yk__sdsdup((t__0));
    yk__sds t__1 = yy__path_dirname(yk__sdsdup(yy__configuration_exe_parent));
    yk__sds t__2 = yk__sdsnew("runtime");
    yk__sds t__3 = yy__path_join(yk__sdsdup((t__1)), yk__sdsdup(t__2));
    yk__sds yy__configuration_l1 = yk__sdsdup((t__3));
    yk__sds t__4 = yy__path_dirname(yk__sdsdup(yy__configuration_exe_parent));
    yk__sds t__5 = yy__path_dirname(yk__sdsdup((t__4)));
    yk__sds t__6 = yk__sdsnew("runtime");
    yk__sds t__7 = yy__path_join(yk__sdsdup((t__5)), yk__sdsdup(t__6));
    yk__sds yy__configuration_l2 = yk__sdsdup((t__7));
    yk__sds t__8 = yk__sdsnew("runtime");
    yk__sds t__9 = yy__path_join(yk__sdsdup(yy__configuration_exe_parent), yk__sdsdup(t__8));
    yk__sds yy__configuration_l3 = yk__sdsdup((t__9));
    yk__sds t__10 = yk__sdsnew("yk__lib.h");
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
    yk__sds t__12 = yk__sdsnew("yk__lib.h");
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
    yk__sds t__14 = yk__sdsnew("yk__lib.h");
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
    yk__sds t__16 = yk__sdsnew("Failed to find runtime library in :");
    yk__sds t__17 = yk__sdscatsds(yk__sdsdup(t__16), yy__configuration_l1);
    yk__arrput(yy__configuration_c->yy__configuration_errors, yk__sdsdup(t__17));
    yk__sds t__18 = yk__sdsnew("Failed to find runtime library in :");
    yk__sds t__19 = yk__sdscatsds(yk__sdsdup(t__18), yy__configuration_l2);
    yk__arrput(yy__configuration_c->yy__configuration_errors, yk__sdsdup(t__19));
    yk__sds t__20 = yk__sdsnew("Failed to find runtime library in :");
    yk__sds t__21 = yk__sdscatsds(yk__sdsdup(t__20), yy__configuration_l3);
    yk__arrput(yy__configuration_c->yy__configuration_errors, yk__sdsdup(t__21));
    yk__sds t__22 = yk__sdsnew("<not found>");
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
    yk__sds t__25 = yk__sdsnew("libs");
    yk__sds t__26 = yy__path_join(yk__sdsdup((t__24)), yk__sdsdup(t__25));
    yk__sds yy__configuration_l1 = yk__sdsdup((t__26));
    yk__sds t__27 = yy__path_dirname(yk__sdsdup(yy__configuration_exe_parent));
    yk__sds t__28 = yy__path_dirname(yk__sdsdup((t__27)));
    yk__sds t__29 = yk__sdsnew("libs");
    yk__sds t__30 = yy__path_join(yk__sdsdup((t__28)), yk__sdsdup(t__29));
    yk__sds yy__configuration_l2 = yk__sdsdup((t__30));
    yk__sds t__31 = yk__sdsnew("libs");
    yk__sds t__32 = yy__path_join(yk__sdsdup(yy__configuration_exe_parent), yk__sdsdup(t__31));
    yk__sds yy__configuration_l3 = yk__sdsdup((t__32));
    yk__sds t__33 = yk__sdsnew("libs.yaka");
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
    yk__sds t__35 = yk__sdsnew("libs.yaka");
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
    yk__sds t__37 = yk__sdsnew("libs.yaka");
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
    yk__sds t__39 = yk__sdsnew("Failed to find std library in :");
    yk__sds t__40 = yk__sdscatsds(yk__sdsdup(t__39), yy__configuration_l1);
    yk__arrput(yy__configuration_c->yy__configuration_errors, yk__sdsdup(t__40));
    yk__sds t__41 = yk__sdsnew("Failed to find std library in :");
    yk__sds t__42 = yk__sdscatsds(yk__sdsdup(t__41), yy__configuration_l2);
    yk__arrput(yy__configuration_c->yy__configuration_errors, yk__sdsdup(t__42));
    yk__sds t__43 = yk__sdsnew("Failed to find std library in :");
    yk__sds t__44 = yk__sdscatsds(yk__sdsdup(t__43), yy__configuration_l3);
    yk__arrput(yy__configuration_c->yy__configuration_errors, yk__sdsdup(t__44));
    yk__sds t__45 = yk__sdsnew("<not found>");
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
    yk__sds t__47 = yk__sdsnew("yakshac");
    yk__sds t__48 = yy__path_join(yk__sdsdup(yy__configuration_exe_parent), yk__sdsdup(t__47));
    yk__sds yy__configuration_l1 = yk__sdsdup((t__48));
    if (yy__os_is_windows())
    {
        yk__sds t__49 = yk__sdsnew(".exe");
        yk__sds t__50 = yk__sdscatsds(yk__sdsdup(yy__configuration_l1), t__49);
        yk__sdsfree(yy__configuration_l1);
        yy__configuration_l1 = yk__sdsdup(t__50);
        yk__sdsfree(t__50);
        yk__sdsfree(t__49);
    }
    yk__sds t__51 = yy__path_dirname(yk__sdsdup(yy__configuration_exe_parent));
    yk__sds t__52 = yy__path_dirname(yk__sdsdup((t__51)));
    yk__sds t__53 = yk__sdsnew("bin");
    yk__sds t__54 = yy__path_join(yk__sdsdup((t__52)), yk__sdsdup(t__53));
    yk__sds yy__configuration_l2 = yk__sdsdup((t__54));
    yk__sds t__55 = yk__sdsnew("yakshac");
    yk__sds t__56 = yy__path_join(yk__sdsdup(yy__configuration_l2), yk__sdsdup(t__55));
    yk__sdsfree(yy__configuration_l2);
    yy__configuration_l2 = yk__sdsdup((t__56));
    if (yy__os_is_windows())
    {
        yk__sds t__57 = yk__sdsnew(".exe");
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
    yk__sds t__59 = yk__sdsnew("yakshac");
    yk__sds t__60 = yy__os_which(yk__sdsdup(t__59));
    yk__sds yy__configuration_fallback = yk__sdsdup((t__60));
    if ((yk__sdslen(yy__configuration_fallback) > 0))
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
    yk__sds t__61 = yk__sdsnew("Failed to find yakshac in :");
    yk__sds t__62 = yk__sdscatsds(yk__sdsdup(t__61), yy__configuration_l1);
    yk__arrput(yy__configuration_c->yy__configuration_errors, yk__sdsdup(t__62));
    yk__sds t__63 = yk__sdsnew("Failed to find yakshac in :");
    yk__sds t__64 = yk__sdscatsds(yk__sdsdup(t__63), yy__configuration_l2);
    yk__arrput(yy__configuration_c->yy__configuration_errors, yk__sdsdup(t__64));
    yk__sds t__65 = yk__sdsnew("Failed to find yakshac in PATH");
    yk__arrput(yy__configuration_c->yy__configuration_errors, yk__sdsdup(t__65));
    yk__sds t__66 = yk__sdsnew("<not found>");
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
    yk__sds t__67 = yk__sdsnew("zig");
    yk__sds t__68 = yy__os_which(yk__sdsdup(t__67));
    yk__sds yy__configuration_zig = yk__sdsdup((t__68));
    if ((yk__sdslen(yy__configuration_zig) > 0))
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
        yk__sds t__69 = yk__sdsnew("Failed to find zig in PATH");
        yk__arrput(yy__configuration_c->yy__configuration_errors, yk__sdsdup(t__69));
        yk__sdsfree(t__69);
    }
    yk__sds t__70 = yk__sdsnew("<not found>");
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
    yk__sds t__71 = yk__sdsnew("emcc");
    yk__sds t__72 = yy__os_which(yk__sdsdup(t__71));
    yk__sds yy__configuration_emcc = yk__sdsdup((t__72));
    yk__sds t__73 = yk__sdsnew("emrun");
    yk__sds t__74 = yy__os_which(yk__sdsdup(t__73));
    yk__sds yy__configuration_emrun = yk__sdsdup((t__74));
    bool yy__configuration_not_found = ((yk__sdslen(yy__configuration_emcc) == 0) || (yk__sdslen(yy__configuration_emrun) == 0));
    if ((yy__configuration_c->yy__configuration_compilation->yy__configuration_web && yy__configuration_not_found))
    {
        yk__sds t__75 = yk__sdsnew("Failed to find emsdk (emcc, emrun) in PATH");
        yk__arrput(yy__configuration_c->yy__configuration_errors, yk__sdsdup(t__75));
        yk__sds t__76 = yk__sdsnew("<not found>");
        yk__sdsfree(yy__configuration_c->yy__configuration_emcc_compiler_path);
        yy__configuration_c->yy__configuration_emcc_compiler_path = yk__sdsdup(t__76);
        yk__sds t__77 = yk__sdsnew("<not found>");
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
struct yy__configuration_Project* yy__configuration_load_project(yy__toml_Table yy__configuration_conf, struct yy__configuration_Config* yy__configuration_c) 
{
    struct yy__configuration_Project* yy__configuration_p = calloc(1, sizeof(struct yy__configuration_Project));
    yk__sds t__78 = yk__sdsnew("project");
    yy__toml_Table yy__configuration_project = yy__toml_get_table(yy__configuration_conf, yk__sdsdup(t__78));
    if ((! (yy__toml_valid_table(yy__configuration_project))))
    {
        yk__sds t__79 = yk__sdsnew("Failed to read \'[project]\'");
        yk__arrput(yy__configuration_c->yy__configuration_errors, yk__sdsdup(t__79));
        struct yy__configuration_Project* t__80 = yy__configuration_p;
        yk__sdsfree(t__79);
        yk__sdsfree(t__78);
        return t__80;
        yk__sdsfree(t__79);
    }
    yk__sds t__81 = yk__sdsnew("main");
    yk__sds t__82 = yy__toml_get_string(yy__configuration_project, yk__sdsdup(t__81));
    yk__sds yy__configuration_main_code_file = yk__sdsdup((t__82));
    yk__sds t__83 = yk__sdsnew("name");
    yk__sds t__84 = yy__toml_get_string(yy__configuration_project, yk__sdsdup(t__83));
    yk__sds yy__configuration_project_name = yk__sdsdup((t__84));
    yk__sds t__85 = yk__sdsnew("author");
    yk__sds t__86 = yy__toml_get_string(yy__configuration_project, yk__sdsdup(t__85));
    yk__sds yy__configuration_project_author = yk__sdsdup((t__86));
    yk__sds t__87 = yk__sdsempty();
    if ((yk__sdscmp(yy__configuration_main_code_file , t__87) == 0))
    {
        yk__sds t__88 = yk__sdsnew("Invalid \'[project].main\'");
        yk__arrput(yy__configuration_c->yy__configuration_errors, yk__sdsdup(t__88));
        yk__sdsfree(t__88);
    }
    yk__sds t__89 = yk__sdsempty();
    if ((yk__sdscmp(yy__configuration_project_name , t__89) == 0))
    {
        yk__sds t__90 = yk__sdsnew("Invalid \'[project].name\'");
        yk__arrput(yy__configuration_c->yy__configuration_errors, yk__sdsdup(t__90));
        yk__sdsfree(t__90);
    }
    yk__sds t__91 = yk__sdsempty();
    if ((yk__sdscmp(yy__configuration_project_author , t__91) == 0))
    {
        yk__sds t__92 = yk__sdsnew("Invalid \'[project].author\'");
        yk__arrput(yy__configuration_c->yy__configuration_errors, yk__sdsdup(t__92));
        yk__sdsfree(t__92);
    }
    yk__sdsfree(yy__configuration_p->yy__configuration_main);
    yy__configuration_p->yy__configuration_main = yk__sdsdup(yy__configuration_main_code_file);
    yk__sdsfree(yy__configuration_p->yy__configuration_author);
    yy__configuration_p->yy__configuration_author = yk__sdsdup(yy__configuration_project_author);
    yk__sdsfree(yy__configuration_p->yy__configuration_name);
    yy__configuration_p->yy__configuration_name = yk__sdsdup(yy__configuration_project_name);
    struct yy__configuration_Project* t__93 = yy__configuration_p;
    yk__sdsfree(t__91);
    yk__sdsfree(t__89);
    yk__sdsfree(t__87);
    yk__sdsfree(yy__configuration_project_author);
    yk__sdsfree(t__86);
    yk__sdsfree(t__85);
    yk__sdsfree(yy__configuration_project_name);
    yk__sdsfree(t__84);
    yk__sdsfree(t__83);
    yk__sdsfree(yy__configuration_main_code_file);
    yk__sdsfree(t__82);
    yk__sdsfree(t__81);
    yk__sdsfree(t__78);
    return t__93;
}
struct yy__configuration_CCode* yy__configuration_load_c_code(yy__toml_Table yy__configuration_conf, struct yy__configuration_Config* yy__configuration_c) 
{
    struct yy__configuration_CCode* yy__configuration_cc = calloc(1, sizeof(struct yy__configuration_CCode));
    yk__sds t__94 = yk__sdsnew("ccode");
    yy__toml_Table yy__configuration_cc_data = yy__toml_get_table(yy__configuration_conf, yk__sdsdup(t__94));
    if ((! (yy__toml_valid_table(yy__configuration_cc_data))))
    {
        struct yy__configuration_CCode* t__95 = yy__configuration_cc;
        yk__sdsfree(t__94);
        return t__95;
    }
    yk__sds t__96 = yk__sdsnew("include_paths");
    yy__configuration_cc->yy__configuration_include_paths = yy__toml_get_string_array(yy__configuration_cc_data, yk__sdsdup(t__96));
    yk__sds t__97 = yk__sdsnew("defines");
    yy__configuration_cc->yy__configuration_defines = yy__toml_get_string_array(yy__configuration_cc_data, yk__sdsdup(t__97));
    yk__sds t__98 = yk__sdsnew("compiler_defines");
    yy__configuration_cc->yy__configuration_compiler_defines = yy__toml_get_string_array(yy__configuration_cc_data, yk__sdsdup(t__98));
    yk__sds t__99 = yk__sdsnew("includes");
    yy__configuration_cc->yy__configuration_includes = yy__toml_get_string_array(yy__configuration_cc_data, yk__sdsdup(t__99));
    yk__sds t__100 = yk__sdsnew("system_includes");
    yy__configuration_cc->yy__configuration_system_includes = yy__toml_get_string_array(yy__configuration_cc_data, yk__sdsdup(t__100));
    yk__sds t__101 = yk__sdsnew("c_code");
    yy__configuration_cc->yy__configuration_c_code = yy__toml_get_string_array(yy__configuration_cc_data, yk__sdsdup(t__101));
    yk__sds t__102 = yk__sdsnew("cpp_code");
    yy__configuration_cc->yy__configuration_cpp_code = yy__toml_get_string_array(yy__configuration_cc_data, yk__sdsdup(t__102));
    struct yy__configuration_CCode* t__103 = yy__configuration_cc;
    yk__sdsfree(t__102);
    yk__sdsfree(t__101);
    yk__sdsfree(t__100);
    yk__sdsfree(t__99);
    yk__sdsfree(t__98);
    yk__sdsfree(t__97);
    yk__sdsfree(t__96);
    yk__sdsfree(t__94);
    return t__103;
}
struct yy__configuration_Compilation* yy__configuration_load_compilation(yy__toml_Table yy__configuration_conf, struct yy__configuration_Config* yy__configuration_c) 
{
    struct yy__configuration_Compilation* yy__configuration_co = calloc(1, sizeof(struct yy__configuration_Compilation));
    yk__sds t__104 = yk__sdsnew("compilation");
    yy__toml_Table yy__configuration_co_data = yy__toml_get_table(yy__configuration_conf, yk__sdsdup(t__104));
    if ((! (yy__toml_valid_table(yy__configuration_co_data))))
    {
        struct yy__configuration_Compilation* t__105 = yy__configuration_co;
        yk__sdsfree(t__104);
        return t__105;
    }
    yk__sds t__106 = yk__sdsnew("targets");
    yy__configuration_co->yy__configuration_targets = yy__toml_get_string_array(yy__configuration_co_data, yk__sdsdup(t__106));
    yk__sds t__107 = yk__sdsnew("raylib");
    yy__configuration_co->yy__configuration_raylib = yy__toml_get_bool_default(yy__configuration_co_data, yk__sdsdup(t__107), false);
    yk__sds t__108 = yk__sdsnew("web");
    yy__configuration_co->yy__configuration_web = yy__toml_get_bool_default(yy__configuration_co_data, yk__sdsdup(t__108), false);
    struct yy__configuration_Compilation* t__109 = yy__configuration_co;
    yk__sdsfree(t__108);
    yk__sdsfree(t__107);
    yk__sdsfree(t__106);
    yk__sdsfree(t__104);
    return t__109;
}
struct yy__configuration_CCode* yy__configuration_inject_c_code_defaults(struct yy__configuration_CCode* yy__configuration_cc, struct yy__configuration_Config* yy__configuration_c) 
{
    yk__sds t__110 = yy__os_cwd();
    yk__sds t__111 = yy__path_dirname(yk__sdsdup((t__110)));
    yk__sds yy__configuration_current_dir = yk__sdsdup((t__111));
    yk__sds t__112 = yk__sdsnew("build");
    yk__sds t__113 = yy__path_join(yk__sdsdup(yy__configuration_current_dir), yk__sdsdup(t__112));
    yk__sds* yy__configuration_df_include_paths = yy__array_new(2, yk__sdsdup(yy__configuration_c->yy__configuration_runtime_path), yk__sdsdup((t__113)));
    yk__sds* yy__configuration_orig_include_paths = yy__configuration_cc->yy__configuration_include_paths;
    yy__configuration_cc->yy__configuration_include_paths = yy__array_extend(yy__configuration_df_include_paths, yy__configuration_cc->yy__configuration_include_paths);
    yk__sds t__114 = yk__sdsnew("UTF8PROC_STATIC");
    yk__sds* yy__configuration_df_compiler_defines = yy__array_new(1, yk__sdsdup(t__114));
    yk__sds* yy__configuration_orig_compiler_defines = yy__configuration_cc->yy__configuration_compiler_defines;
    yy__configuration_cc->yy__configuration_compiler_defines = yy__array_extend(yy__configuration_df_compiler_defines, yy__configuration_cc->yy__configuration_compiler_defines);
    yk__sds t__115 = yk__sdsnew("whereami.h");
    yk__sds t__116 = yk__sdsnew("yk__system.h");
    yk__sds t__117 = yk__sdsnew("utf8proc.h");
    yk__sds t__118 = yk__sdsnew("yk__utf8iter.h");
    yk__sds t__119 = yk__sdsnew("toml.h");
    yk__sds t__120 = yk__sdsnew("yk__console.h");
    yk__sds t__121 = yk__sdsnew("mpc.h");
    yk__sds t__122 = yk__sdsnew("yk__arrayutils.h");
    yk__sds t__123 = yk__sdsnew("yk__process.h");
    yk__sds t__124 = yk__sdsnew("yk__graphic_utils.h");
    yk__sds t__125 = yk__sdsnew("yk__argparse.h");
    yk__sds t__126 = yk__sdsnew("argparse.h");
    yk__sds* yy__configuration_df_includes = yy__array_new(12, yk__sdsdup(t__115), yk__sdsdup(t__116), yk__sdsdup(t__117), yk__sdsdup(t__118), yk__sdsdup(t__119), yk__sdsdup(t__120), yk__sdsdup(t__121), yk__sdsdup(t__122), yk__sdsdup(t__123), yk__sdsdup(t__124), yk__sdsdup(t__125), yk__sdsdup(t__126));
    yk__sds* yy__configuration_orig_includes = yy__configuration_cc->yy__configuration_includes;
    yy__configuration_cc->yy__configuration_includes = yy__array_extend(yy__configuration_df_includes, yy__configuration_cc->yy__configuration_includes);
    yk__sds* yy__configuration_df_c_code = NULL;
    if (yy__configuration_c->yy__configuration_compilation->yy__configuration_web)
    {
        yk__sds t__127 = yk__sdsnew("yk__fake_whereami.c");
        yk__sds t__128 = yy__path_join(yk__sdsdup(yy__configuration_c->yy__configuration_runtime_path), yk__sdsdup(t__127));
        yk__arrput(yy__configuration_df_c_code, yk__sdsdup((t__128)));
        yk__sdsfree(t__128);
        yk__sdsfree(t__127);
    }
    else
    {
        yk__sds t__129 = yk__sdsnew("whereami.c");
        yk__sds t__130 = yy__path_join(yk__sdsdup(yy__configuration_c->yy__configuration_runtime_path), yk__sdsdup(t__129));
        yk__arrput(yy__configuration_df_c_code, yk__sdsdup((t__130)));
        yk__sdsfree(t__130);
        yk__sdsfree(t__129);
    }
    yk__sds t__131 = yk__sdsnew("yk__system.c");
    yk__sds t__132 = yy__path_join(yk__sdsdup(yy__configuration_c->yy__configuration_runtime_path), yk__sdsdup(t__131));
    yk__arrput(yy__configuration_df_c_code, yk__sdsdup((t__132)));
    yk__sds t__133 = yk__sdsnew("utf8proc.c");
    yk__sds t__134 = yy__path_join(yk__sdsdup(yy__configuration_c->yy__configuration_runtime_path), yk__sdsdup(t__133));
    yk__arrput(yy__configuration_df_c_code, yk__sdsdup((t__134)));
    yk__sds t__135 = yk__sdsnew("toml.c");
    yk__sds t__136 = yy__path_join(yk__sdsdup(yy__configuration_c->yy__configuration_runtime_path), yk__sdsdup(t__135));
    yk__arrput(yy__configuration_df_c_code, yk__sdsdup((t__136)));
    yk__sds t__137 = yk__sdsnew("mpc.c");
    yk__sds t__138 = yy__path_join(yk__sdsdup(yy__configuration_c->yy__configuration_runtime_path), yk__sdsdup(t__137));
    yk__arrput(yy__configuration_df_c_code, yk__sdsdup((t__138)));
    yk__sds t__139 = yk__sdsnew("yk__console.c");
    yk__sds t__140 = yy__path_join(yk__sdsdup(yy__configuration_c->yy__configuration_runtime_path), yk__sdsdup(t__139));
    yk__arrput(yy__configuration_df_c_code, yk__sdsdup((t__140)));
    yk__sds t__141 = yk__sdsnew("yk__arrayutils.c");
    yk__sds t__142 = yy__path_join(yk__sdsdup(yy__configuration_c->yy__configuration_runtime_path), yk__sdsdup(t__141));
    yk__arrput(yy__configuration_df_c_code, yk__sdsdup((t__142)));
    yk__sds t__143 = yk__sdsnew("yk__process.c");
    yk__sds t__144 = yy__path_join(yk__sdsdup(yy__configuration_c->yy__configuration_runtime_path), yk__sdsdup(t__143));
    yk__arrput(yy__configuration_df_c_code, yk__sdsdup((t__144)));
    yk__sds t__145 = yk__sdsnew("yk__graphic_utils.c");
    yk__sds t__146 = yy__path_join(yk__sdsdup(yy__configuration_c->yy__configuration_runtime_path), yk__sdsdup(t__145));
    yk__arrput(yy__configuration_df_c_code, yk__sdsdup((t__146)));
    yk__sds t__147 = yk__sdsnew("yk__argparse.c");
    yk__sds t__148 = yy__path_join(yk__sdsdup(yy__configuration_c->yy__configuration_runtime_path), yk__sdsdup(t__147));
    yk__arrput(yy__configuration_df_c_code, yk__sdsdup((t__148)));
    yk__sds t__149 = yk__sdsnew("argparse.c");
    yk__sds t__150 = yy__path_join(yk__sdsdup(yy__configuration_c->yy__configuration_runtime_path), yk__sdsdup(t__149));
    yk__arrput(yy__configuration_df_c_code, yk__sdsdup((t__150)));
    yk__sds* yy__configuration_orig_c_code = yy__configuration_cc->yy__configuration_c_code;
    yy__configuration_cc->yy__configuration_c_code = yy__array_extend(yy__configuration_df_c_code, yy__configuration_cc->yy__configuration_c_code);
    struct yy__configuration_CCode* t__151 = yy__configuration_cc;
    yy__array_del_str_array(yy__configuration_orig_c_code);
    yy__array_del_str_array(yy__configuration_orig_includes);
    yy__array_del_str_array(yy__configuration_orig_compiler_defines);
    yy__array_del_str_array(yy__configuration_orig_include_paths);
    yk__sdsfree(t__150);
    yk__sdsfree(t__149);
    yk__sdsfree(t__148);
    yk__sdsfree(t__147);
    yk__sdsfree(t__146);
    yk__sdsfree(t__145);
    yk__sdsfree(t__144);
    yk__sdsfree(t__143);
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
    yk__sdsfree(t__126);
    yk__sdsfree(t__125);
    yk__sdsfree(t__124);
    yk__sdsfree(t__123);
    yk__sdsfree(t__122);
    yk__sdsfree(t__121);
    yk__sdsfree(t__120);
    yk__sdsfree(t__119);
    yk__sdsfree(t__118);
    yk__sdsfree(t__117);
    yk__sdsfree(t__116);
    yk__sdsfree(t__115);
    yk__sdsfree(t__114);
    yk__sdsfree(t__113);
    yk__sdsfree(t__112);
    yk__sdsfree(yy__configuration_current_dir);
    yk__sdsfree(t__111);
    yk__sdsfree(t__110);
    return t__151;
}
struct yy__configuration_Config* yy__configuration_load_config() 
{
    struct yy__configuration_Config* yy__configuration_c = calloc(1, sizeof(struct yy__configuration_Config));
    yk__sds t__152 = yy__os_cwd();
    yk__sds t__153 = yk__sdsnew("yaksha.toml");
    yk__sds t__154 = yy__path_join(yk__sdsdup((t__152)), yk__sdsdup(t__153));
    yk__sds yy__configuration_configf = yk__sdsdup((t__154));
    yk__sds t__155 = yy__io_readfile(yk__sdsdup(yy__configuration_configf));
    yk__sds yy__configuration_config_text = yk__sdsdup((t__155));
    yy__toml_Table yy__configuration_conf = yy__toml_from_str(yk__sdsdup(yy__configuration_config_text));
    if ((! (yy__toml_valid_table(yy__configuration_conf))))
    {
        yk__sds t__156 = yk__sdsnew("Failed to read config file");
        yk__arrput(yy__configuration_c->yy__configuration_errors, yk__sdsdup(t__156));
        struct yy__configuration_Config* t__157 = yy__configuration_c;
        yk__sdsfree(t__156);
        yk__sdsfree(yy__configuration_config_text);
        yk__sdsfree(t__155);
        yk__sdsfree(yy__configuration_configf);
        yk__sdsfree(t__154);
        yk__sdsfree(t__153);
        yk__sdsfree(t__152);
        return t__157;
        yk__sdsfree(t__156);
    }
    yy__configuration_c->yy__configuration_compilation = yy__configuration_load_compilation(yy__configuration_conf, yy__configuration_c);
    yy__configuration_find_yaksha_compiler(yy__configuration_c);
    if ((yk__arrlen(yy__configuration_c->yy__configuration_errors) > 0))
    {
        struct yy__configuration_Config* t__158 = yy__configuration_c;
        yy__toml_del_table(yy__configuration_conf);
        yk__sdsfree(yy__configuration_config_text);
        yk__sdsfree(t__155);
        yk__sdsfree(yy__configuration_configf);
        yk__sdsfree(t__154);
        yk__sdsfree(t__153);
        yk__sdsfree(t__152);
        return t__158;
    }
    yy__configuration_find_zig_compiler(yy__configuration_c);
    if ((yk__arrlen(yy__configuration_c->yy__configuration_errors) > 0))
    {
        struct yy__configuration_Config* t__159 = yy__configuration_c;
        yy__toml_del_table(yy__configuration_conf);
        yk__sdsfree(yy__configuration_config_text);
        yk__sdsfree(t__155);
        yk__sdsfree(yy__configuration_configf);
        yk__sdsfree(t__154);
        yk__sdsfree(t__153);
        yk__sdsfree(t__152);
        return t__159;
    }
    yy__configuration_find_emsdk(yy__configuration_c);
    if ((yk__arrlen(yy__configuration_c->yy__configuration_errors) > 0))
    {
        struct yy__configuration_Config* t__160 = yy__configuration_c;
        yy__toml_del_table(yy__configuration_conf);
        yk__sdsfree(yy__configuration_config_text);
        yk__sdsfree(t__155);
        yk__sdsfree(yy__configuration_configf);
        yk__sdsfree(t__154);
        yk__sdsfree(t__153);
        yk__sdsfree(t__152);
        return t__160;
    }
    yy__configuration_find_runtime_path(yy__configuration_c);
    if ((yk__arrlen(yy__configuration_c->yy__configuration_errors) > 0))
    {
        struct yy__configuration_Config* t__161 = yy__configuration_c;
        yy__toml_del_table(yy__configuration_conf);
        yk__sdsfree(yy__configuration_config_text);
        yk__sdsfree(t__155);
        yk__sdsfree(yy__configuration_configf);
        yk__sdsfree(t__154);
        yk__sdsfree(t__153);
        yk__sdsfree(t__152);
        return t__161;
    }
    yy__configuration_find_libs_path(yy__configuration_c);
    if ((yk__arrlen(yy__configuration_c->yy__configuration_errors) > 0))
    {
        struct yy__configuration_Config* t__162 = yy__configuration_c;
        yy__toml_del_table(yy__configuration_conf);
        yk__sdsfree(yy__configuration_config_text);
        yk__sdsfree(t__155);
        yk__sdsfree(yy__configuration_configf);
        yk__sdsfree(t__154);
        yk__sdsfree(t__153);
        yk__sdsfree(t__152);
        return t__162;
    }
    yy__configuration_c->yy__configuration_project = yy__configuration_load_project(yy__configuration_conf, yy__configuration_c);
    if ((yk__arrlen(yy__configuration_c->yy__configuration_errors) > 0))
    {
        struct yy__configuration_Config* t__163 = yy__configuration_c;
        yy__toml_del_table(yy__configuration_conf);
        yk__sdsfree(yy__configuration_config_text);
        yk__sdsfree(t__155);
        yk__sdsfree(yy__configuration_configf);
        yk__sdsfree(t__154);
        yk__sdsfree(t__153);
        yk__sdsfree(t__152);
        return t__163;
    }
    if ((! (yy__path_exists(yk__sdsdup(yy__configuration_c->yy__configuration_project->yy__configuration_main)))))
    {
        yk__sds t__164 = yk__sdsnew("Project main file not found");
        yk__arrput(yy__configuration_c->yy__configuration_errors, yk__sdsdup(t__164));
        struct yy__configuration_Config* t__165 = yy__configuration_c;
        yy__toml_del_table(yy__configuration_conf);
        yk__sdsfree(t__164);
        yk__sdsfree(yy__configuration_config_text);
        yk__sdsfree(t__155);
        yk__sdsfree(yy__configuration_configf);
        yk__sdsfree(t__154);
        yk__sdsfree(t__153);
        yk__sdsfree(t__152);
        return t__165;
        yk__sdsfree(t__164);
    }
    yy__configuration_c->yy__configuration_c_code = yy__configuration_inject_c_code_defaults(yy__configuration_load_c_code(yy__configuration_conf, yy__configuration_c), yy__configuration_c);
    if ((yk__arrlen(yy__configuration_c->yy__configuration_errors) > 0))
    {
        struct yy__configuration_Config* t__166 = yy__configuration_c;
        yy__toml_del_table(yy__configuration_conf);
        yk__sdsfree(yy__configuration_config_text);
        yk__sdsfree(t__155);
        yk__sdsfree(yy__configuration_configf);
        yk__sdsfree(t__154);
        yk__sdsfree(t__153);
        yk__sdsfree(t__152);
        return t__166;
    }
    struct yy__configuration_Config* t__167 = yy__configuration_c;
    yy__toml_del_table(yy__configuration_conf);
    yk__sdsfree(yy__configuration_config_text);
    yk__sdsfree(t__155);
    yk__sdsfree(yy__configuration_configf);
    yk__sdsfree(t__154);
    yk__sdsfree(t__153);
    yk__sdsfree(t__152);
    return t__167;
}
struct yy__configuration_Config* yy__configuration_create_adhoc_config(yk__sds yy__configuration_name, yk__sds yy__configuration_file_path, bool yy__configuration_use_raylib, bool yy__configuration_use_web) 
{
    struct yy__configuration_Config* yy__configuration_c = calloc(1, sizeof(struct yy__configuration_Config));
    yy__configuration_c->yy__configuration_compilation = calloc(1, sizeof(struct yy__configuration_Compilation));
    yk__sds t__168 = yk__sdsnew("native");
    yy__configuration_c->yy__configuration_compilation->yy__configuration_targets = yy__array_new(1, yk__sdsdup(t__168));
    yy__configuration_c->yy__configuration_compilation->yy__configuration_raylib = yy__configuration_use_raylib;
    yy__configuration_c->yy__configuration_compilation->yy__configuration_web = yy__configuration_use_web;
    yy__configuration_find_yaksha_compiler(yy__configuration_c);
    if ((yk__arrlen(yy__configuration_c->yy__configuration_errors) > 0))
    {
        struct yy__configuration_Config* t__169 = yy__configuration_c;
        yk__sdsfree(t__168);
        yk__sdsfree(yy__configuration_file_path);
        yk__sdsfree(yy__configuration_name);
        return t__169;
    }
    yy__configuration_find_zig_compiler(yy__configuration_c);
    if ((yk__arrlen(yy__configuration_c->yy__configuration_errors) > 0))
    {
        struct yy__configuration_Config* t__170 = yy__configuration_c;
        yk__sdsfree(t__168);
        yk__sdsfree(yy__configuration_file_path);
        yk__sdsfree(yy__configuration_name);
        return t__170;
    }
    yy__configuration_find_emsdk(yy__configuration_c);
    if ((yk__arrlen(yy__configuration_c->yy__configuration_errors) > 0))
    {
        struct yy__configuration_Config* t__171 = yy__configuration_c;
        yk__sdsfree(t__168);
        yk__sdsfree(yy__configuration_file_path);
        yk__sdsfree(yy__configuration_name);
        return t__171;
    }
    yy__configuration_find_runtime_path(yy__configuration_c);
    if ((yk__arrlen(yy__configuration_c->yy__configuration_errors) > 0))
    {
        struct yy__configuration_Config* t__172 = yy__configuration_c;
        yk__sdsfree(t__168);
        yk__sdsfree(yy__configuration_file_path);
        yk__sdsfree(yy__configuration_name);
        return t__172;
    }
    yy__configuration_find_libs_path(yy__configuration_c);
    if ((yk__arrlen(yy__configuration_c->yy__configuration_errors) > 0))
    {
        struct yy__configuration_Config* t__173 = yy__configuration_c;
        yk__sdsfree(t__168);
        yk__sdsfree(yy__configuration_file_path);
        yk__sdsfree(yy__configuration_name);
        return t__173;
    }
    yy__configuration_c->yy__configuration_project = calloc(1, sizeof(struct yy__configuration_Project));
    yk__sdsfree(yy__configuration_c->yy__configuration_project->yy__configuration_main);
    yy__configuration_c->yy__configuration_project->yy__configuration_main = yk__sdsdup(yy__configuration_file_path);
    yk__sds t__174 = yk__sdsnew("unknown");
    yk__sdsfree(yy__configuration_c->yy__configuration_project->yy__configuration_author);
    yy__configuration_c->yy__configuration_project->yy__configuration_author = yk__sdsdup(t__174);
    yk__sdsfree(yy__configuration_c->yy__configuration_project->yy__configuration_name);
    yy__configuration_c->yy__configuration_project->yy__configuration_name = yk__sdsdup(yy__configuration_name);
    yy__configuration_c->yy__configuration_c_code = yy__configuration_inject_c_code_defaults(calloc(1, sizeof(struct yy__configuration_CCode)), yy__configuration_c);
    if ((yk__arrlen(yy__configuration_c->yy__configuration_errors) > 0))
    {
        struct yy__configuration_Config* t__175 = yy__configuration_c;
        yk__sdsfree(t__174);
        yk__sdsfree(t__168);
        yk__sdsfree(yy__configuration_file_path);
        yk__sdsfree(yy__configuration_name);
        return t__175;
    }
    struct yy__configuration_Config* t__176 = yy__configuration_c;
    yk__sdsfree(t__174);
    yk__sdsfree(t__168);
    yk__sdsfree(yy__configuration_file_path);
    yk__sdsfree(yy__configuration_name);
    return t__176;
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
    }
    yy__array_del_str_array(yy__configuration_c->yy__configuration_errors);
    if ((yy__configuration_c->yy__configuration_compilation != NULL))
    {
        yy__array_del_str_array(yy__configuration_c->yy__configuration_compilation->yy__configuration_targets);
        yk__sdsfree(yy__configuration_c->yy__configuration_compilation->yy__configuration_libc);
        yk__sdsfree(yy__configuration_c->yy__configuration_compilation->yy__configuration_compiler);
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
    free(yy__configuration_c);
    return;
}
yy__argparse_ArgParse yy__argparse_new_ex(yy__argparse_Option* nn__options, yk__sds* nn__usages, int32_t nn__flag) { return yk__newargparse(nn__options, nn__usages, nn__flag); }
yy__argparse_ArgParse yy__argparse_new(yy__argparse_Option* yy__argparse_options, yk__sds* yy__argparse_usages) 
{
    yy__argparse_ArgParse t__0 = yy__argparse_new_ex(yy__argparse_options, yy__argparse_usages, yy__argparse_ARGPARSE_DEFAULT);
    return t__0;
}
void yy__argparse_set_description(yy__argparse_ArgParse nn__argp, yk__sds nn__description, yk__sds nn__epilog) { argparse_describe(nn__argp, nn__description, nn__epilog); }
void yy__argparse_del_argparse(yy__argparse_ArgParse nn__object) { yk__delargparse(nn__object); }
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
yy__argparse_Option yy__argparse_opt_string(yk__sds nn__short, yk__sds nn__large, yy__c_CStr nn__result, yk__sds nn__help) 
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
    yy__console_set_color(0);
    yk__sdsfree(yy__console_x);
    return;
}
void yy__console_red(yk__sds yy__console_x) 
{
    yy__console_color_print(1, yk__sdsdup(yy__console_x));
    yk__sdsfree(yy__console_x);
    return;
}
void yy__console_green(yk__sds yy__console_x) 
{
    yy__console_color_print(2, yk__sdsdup(yy__console_x));
    yk__sdsfree(yy__console_x);
    return;
}
void yy__console_white(yk__sds yy__console_x) 
{
    yy__console_color_print(3, yk__sdsdup(yy__console_x));
    yk__sdsfree(yy__console_x);
    return;
}
void yy__console_blue(yk__sds yy__console_x) 
{
    yy__console_color_print(4, yk__sdsdup(yy__console_x));
    yk__sdsfree(yy__console_x);
    return;
}
void yy__console_purple(yk__sds yy__console_x) 
{
    yy__console_color_print(5, yk__sdsdup(yy__console_x));
    yk__sdsfree(yy__console_x);
    return;
}
void yy__console_yellow(yk__sds yy__console_x) 
{
    yy__console_color_print(6, yk__sdsdup(yy__console_x));
    yk__sdsfree(yy__console_x);
    return;
}
void yy__console_cyan(yk__sds yy__console_x) 
{
    yy__console_color_print(7, yk__sdsdup(yy__console_x));
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
    int32_t yy__toml_c = 0;
    while (1) {
        if (!((yy__toml_c < yy__toml_length))) { break; } // Check
        // Body of while loop

        {
            yk__sds t__1 = yy__toml_string_at(yy__toml_arr, yy__toml_c);
            yk__arrput(yy__toml_str_array, yk__sdsdup((t__1)));
            yy__toml_c = (yy__toml_c + 1);
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
    if ((yy__path_length < 1))
    {
        yk__sdsfree(yy__path_a);
        return false;
    }
    int32_t yy__path_chr = (yy__path_a[(yy__path_length - 1)]);
    bool yy__path_x = ((yy__path_chr == 47) || (yy__path_chr == 92));
    bool t__0 = yy__path_x;
    yk__sdsfree(yy__path_a);
    return t__0;
}
bool yy__path_end_with_dot(yk__sds yy__path_a) 
{
    int32_t yy__path_length = yk__sdslen(yy__path_a);
    if ((yy__path_length < 1))
    {
        yk__sdsfree(yy__path_a);
        return false;
    }
    int32_t yy__path_chr = (yy__path_a[(yy__path_length - 1)]);
    bool yy__path_x = (yy__path_chr == 46);
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
        yk__sds t__4 = yk__sdsnew("\\");
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
        yk__sds t__7 = yk__sdsnew("/");
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
    if ((yy__path_length < 1))
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
        if (!((yy__path_length > 0))) { break; } // Check
        // Body of while loop

        {
            yy__path_length = (yy__path_length - 1);
            int32_t yy__path_chr = yy__strings_get_cstr(yy__path_x, yy__path_length);
            bool yy__path_is_slash = ((yy__path_chr == 47) || (yy__path_chr == 92));
            if (yy__path_is_slash)
            {
                break;
            }
        }
    }
    if ((yy__path_length <= 0))
    {
        yk__sds t__13 = yy__path_p;
        yy__strings_del_str(yy__path_x);
        return t__13;
    }
    yk__sds t__14 = yy__strings_from_cstrlen_after(yy__path_x, ((yy__path_full_length - yy__path_length) - 1), (yy__path_length + 1));
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
    if ((yy__path_length <= 2))
    {
        yk__sds t__16 = yy__path_p;
        return t__16;
    }
    if (yy__path_end_with_slash(yk__sdsdup(yy__path_p)))
    {
        yy__path_length = (yy__path_length - 1);
    }
    yy__c_CStr yy__path_x = yy__strings_to_cstr(yk__sdsdup(yy__path_p));
    while (1) {
        if (!((yy__path_length > 0))) { break; } // Check
        // Body of while loop

        {
            yy__path_length = (yy__path_length - 1);
            int32_t yy__path_chr = yy__strings_get_cstr(yy__path_x, yy__path_length);
            bool yy__path_is_slash = ((yy__path_chr == 47) || (yy__path_chr == 92));
            if (yy__path_is_slash)
            {
                break;
            }
        }
    }
    if ((yy__path_length <= 0))
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
    if ((yy__path_length <= 1))
    {
        yk__sds t__20 = yy__path_p;
        return t__20;
    }
    if (yy__path_end_with_slash(yk__sdsdup(yy__path_p)))
    {
        yy__path_length = (yy__path_length - 1);
    }
    yy__c_CStr yy__path_x = yy__strings_to_cstr(yk__sdsdup(yy__path_p));
    while (1) {
        if (!((yy__path_length > 0))) { break; } // Check
        // Body of while loop

        {
            yy__path_length = (yy__path_length - 1);
            int32_t yy__path_chr = yy__strings_get_cstr(yy__path_x, yy__path_length);
            bool yy__path_is_dot = (yy__path_chr == 46);
            if (yy__path_is_dot)
            {
                break;
            }
        }
    }
    if ((yy__path_length <= 0))
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
    yk__sdsfree(nn__s);
    return x;
}
int32_t yy__strings_ord_cstr(yy__c_CStr nn__s) 
{
    return (int32_t)nn__s[0];
}
int32_t yy__strings_ord(yk__sds yy__strings_s) 
{
    int32_t t__0 = yy__strings_get(yk__sdsdup(yy__strings_s), 0);
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
yy__strings_Utf8IterateState yy__strings_new_iter(yk__sds nn__s) 
{
    struct utf8proc_iter_state* x = calloc(1, sizeof(struct utf8proc_iter_state));
    if (x == NULL) return x;
    x->str_original = (utf8proc_uint8_t *) nn__s;
    x->str_position = (utf8proc_uint8_t *) nn__s;
    x->length = yk__sdslen(nn__s);
    x->step_size = 0;
    x->codepoint = -1;
    return x;
}
void yy__strings_del_iter(yy__strings_Utf8IterateState nn__s) 
{
    yk__sdsfree((yk__sds)nn__s->str_original);
    free(nn__s);
}
bool yy__strings_iterate(yy__strings_Utf8IterateState nn__s) 
{
    if (nn__s->length <= 0) { return false; }
    utf8proc_int32_t val;
    utf8proc_ssize_t read_bytes = utf8proc_iterate(nn__s->str_position, nn__s->length, &val);
    if (read_bytes <= 0) {
        return false;
    } 
    nn__s->str_position += read_bytes;
    nn__s->length -= read_bytes;
    nn__s->step_size = read_bytes;
    nn__s->codepoint = val;
    return true;
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
    yk__sds yy__os_actual_bin = yk__sdsdup(yy__os_binary);
    yk__sds t__0 = yk__sdsnew("PATH");
    yk__sds t__1 = yy__os_getenv(yk__sdsdup(t__0));
    yk__sds yy__os_env = yk__sdsdup((t__1));
    yk__sds t__2 = yk__sdsnew(":");
    yk__sds yy__os_sep = yk__sdsdup(t__2);
    if (yy__os_is_windows())
    {
        yk__sds t__3 = yk__sdsnew(";");
        yk__sdsfree(yy__os_sep);
        yy__os_sep = yk__sdsdup(t__3);
        yk__sds t__4 = yk__sdsnew(".exe");
        yk__sds t__5 = yk__sdscatsds(yk__sdsdup(yy__os_actual_bin), t__4);
        yk__sdsfree(yy__os_actual_bin);
        yy__os_actual_bin = yk__sdsdup(t__5);
        yk__sdsfree(t__5);
        yk__sdsfree(t__4);
        yk__sdsfree(t__3);
    }
    yk__sds* yy__os_paths = yy__strings_split(yk__sdsdup(yy__os_env), yk__sdsdup(yy__os_sep));
    int32_t yy__os_length = yk__arrlen(yy__os_paths);
    while (1) {
        if (!((yy__os_length > 0))) { break; } // Check
        // Body of while loop

        {
            yy__os_length = (yy__os_length - 1);
            yk__sds yy__os_cur_path = yk__sdsdup(yy__os_paths[yy__os_length]);
            yk__sds t__6 = yy__path_join(yk__sdsdup(yy__os_cur_path), yk__sdsdup(yy__os_actual_bin));
            yk__sds yy__os_full_path = yk__sdsdup((t__6));
            if (yy__path_executable(yk__sdsdup(yy__os_full_path)))
            {
                yk__sds t__7 = yy__os_full_path;
                yy__array_del_str_array(yy__os_paths);
                yk__sdsfree(t__6);
                yk__sdsfree(yy__os_cur_path);
                yk__sdsfree(yy__os_sep);
                yk__sdsfree(t__2);
                yk__sdsfree(yy__os_env);
                yk__sdsfree(t__1);
                yk__sdsfree(t__0);
                yk__sdsfree(yy__os_actual_bin);
                yk__sdsfree(yy__os_binary);
                return t__7;
            }
            yk__sdsfree(yy__os_full_path);
            yk__sdsfree(t__6);
            yk__sdsfree(yy__os_cur_path);
        }
    }
    yk__sds t__8 = yy__os_cwd();
    yk__sds t__9 = yy__path_join(yk__sdsdup((t__8)), yk__sdsdup(yy__os_actual_bin));
    yk__sds yy__os_special = yk__sdsdup((t__9));
    if (yy__path_executable(yk__sdsdup(yy__os_special)))
    {
        yk__sds t__10 = yy__os_special;
        yy__array_del_str_array(yy__os_paths);
        yk__sdsfree(t__9);
        yk__sdsfree(t__8);
        yk__sdsfree(yy__os_sep);
        yk__sdsfree(t__2);
        yk__sdsfree(yy__os_env);
        yk__sdsfree(t__1);
        yk__sdsfree(t__0);
        yk__sdsfree(yy__os_actual_bin);
        yk__sdsfree(yy__os_binary);
        return t__10;
    }
    yk__sds t__11 = yy__os_exe_path();
    yk__sds t__12 = yy__path_join(yk__sdsdup((t__11)), yk__sdsdup(yy__os_actual_bin));
    yk__sdsfree(yy__os_special);
    yy__os_special = yk__sdsdup((t__12));
    if (yy__path_executable(yk__sdsdup(yy__os_special)))
    {
        yk__sds t__13 = yy__os_special;
        yy__array_del_str_array(yy__os_paths);
        yk__sdsfree(t__12);
        yk__sdsfree(t__11);
        yk__sdsfree(t__9);
        yk__sdsfree(t__8);
        yk__sdsfree(yy__os_sep);
        yk__sdsfree(t__2);
        yk__sdsfree(yy__os_env);
        yk__sdsfree(t__1);
        yk__sdsfree(t__0);
        yk__sdsfree(yy__os_actual_bin);
        yk__sdsfree(yy__os_binary);
        return t__13;
    }
    yk__sds t__14 = yk__sdsempty();
    yy__array_del_str_array(yy__os_paths);
    yk__sdsfree(t__12);
    yk__sdsfree(t__11);
    yk__sdsfree(yy__os_special);
    yk__sdsfree(t__9);
    yk__sdsfree(t__8);
    yk__sdsfree(yy__os_sep);
    yk__sdsfree(t__2);
    yk__sdsfree(yy__os_env);
    yk__sdsfree(t__1);
    yk__sdsfree(t__0);
    yk__sdsfree(yy__os_actual_bin);
    yk__sdsfree(yy__os_binary);
    return t__14;
}
yk__sds yy__libs_version() 
{
    yk__sds t__0 = yk__sdsnew("0.1");
    return t__0;
}
void yy__print_banner() 
{
    yk__sds t__0 = yk__sdsnew("\n    ╔═╗┌─┐┬─┐╔═╗┌┐┌┌┬┐┬─┐\n    ║  ├─┤├┬┘╠═╝│││ │ ├┬┘\n    ╚═╝┴ ┴┴└─╩  ┘└┘ ┴ ┴└─\n    ");
    yk__sds yy__art = yk__sdsdup(t__0);
    yk__sds t__1 = yk__sdsnew("\n    Tool for building Yaksha \n    Projects\n    ");
    yk__sds yy__text = yk__sdsdup(t__1);
    yk__sds t__2 = yk__sdsnew("\n       ,\n      /(  ___________\n     |  >:===========`\n      )(\n      \"\"\n");
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
    int32_t yy__x = 0;
    while (1) {
        if (!((yy__x < yy__length))) { break; } // Check
        // Body of while loop

        {
            yk__sds t__3 = yk__sdsnew("\n");
            yk__sds t__4 = yk__sdscatsds(yk__sdsdup(yy__er[yy__x]), t__3);
            yy__console_red(yk__sdsdup(t__4));
            yy__x = (yy__x + 1);
            yk__sdsfree(t__4);
            yk__sdsfree(t__3);
        }
    }
    return;
}
void yy__printkv(yk__sds yy__k, yk__sds yy__v) 
{
    yy__console_cyan(yk__sdsdup(yy__k));
    yk__sds t__5 = yk__sdsnew(" := ");
    yy__console_red(yk__sdsdup(t__5));
    if ((yk__sdslen(yy__v) == 0))
    {
        yk__sds t__6 = yk__sdsnew("<not found>");
        yy__console_green(yk__sdsdup(t__6));
        yk__sdsfree(t__6);
    }
    else
    {
        yy__console_green(yk__sdsdup(yy__v));
    }
    yk__sds t__7 = yk__sdsnew("\n");
    yk__printstr((t__7));
    yk__sdsfree(t__7);
    yk__sdsfree(t__5);
    yk__sdsfree(yy__v);
    yk__sdsfree(yy__k);
    return;
}
void yy__print_config(struct yy__configuration_Config* yy__config) 
{
    yk__sds t__8 = yk__sdsnew("libs");
    yy__printkv(yk__sdsdup(t__8), yk__sdsdup(yy__config->yy__configuration_libs_path));
    yk__sds t__9 = yk__sdsnew("runtime");
    yy__printkv(yk__sdsdup(t__9), yk__sdsdup(yy__config->yy__configuration_runtime_path));
    yk__sds t__10 = yk__sdsnew("compiler");
    yy__printkv(yk__sdsdup(t__10), yk__sdsdup(yy__config->yy__configuration_compiler_path));
    yk__sds t__11 = yk__sdsnew("zig compiler");
    yy__printkv(yk__sdsdup(t__11), yk__sdsdup(yy__config->yy__configuration_zig_compiler_path));
    yk__sds t__12 = yk__sdsnew("emcc compiler");
    yy__printkv(yk__sdsdup(t__12), yk__sdsdup(yy__config->yy__configuration_emcc_compiler_path));
    yk__sds t__13 = yk__sdsnew("emrun");
    yy__printkv(yk__sdsdup(t__13), yk__sdsdup(yy__config->yy__configuration_emrun_path));
    yk__sds t__14 = yk__sdsnew("standard library version");
    yk__sds t__15 = yy__libs_version();
    yy__printkv(yk__sdsdup(t__14), yk__sdsdup((t__15)));
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
    int32_t yy__return_val = 0;
    yk__sds* yy__yk_args = yy__array_new(3, yk__sdsdup(yy__config->yy__configuration_compiler_path), yk__sdsdup(yy__config->yy__configuration_project->yy__configuration_main), yk__sdsdup(yy__config->yy__configuration_libs_path));
    yy__os_ProcessResult yy__result = yy__os_run(yy__yk_args);
    if ((! (yy__result->ok)))
    {
        yk__sds t__16 = yk__sdsnew("---- running Yaksha compiler ---\n");
        yy__console_cyan(yk__sdsdup(t__16));
        yk__sds t__17 = yk__sdsnew("Failed to execute: ");
        yy__console_red(yk__sdsdup(t__17));
        yk__sds t__18 = yk__sdsnew(" ");
        yk__sds t__19 = yy__array_join(yy__yk_args, yk__sdsdup(t__18));
        yy__console_yellow(yk__sdsdup((t__19)));
        yk__sds t__20 = yk__sdsnew("\n");
        yk__printstr((t__20));
        yy__console_red(yk__sdsdup(yy__result->output));
        yk__sds t__21 = yk__sdsnew("\n");
        yk__printstr((t__21));
        yy__return_val = (- (1));
        yk__sds t__22 = yk__sdsnew("---- end of compiler run ---\n");
        yy__console_cyan(yk__sdsdup(t__22));
        yk__sdsfree(t__22);
        yk__sdsfree(t__21);
        yk__sdsfree(t__20);
        yk__sdsfree(t__19);
        yk__sdsfree(t__18);
        yk__sdsfree(t__17);
        yk__sdsfree(t__16);
    }
    else
    {
        yk__sds t__23 = yk__sdsnew("// YK");
        if (yy__strings_startswith(yk__sdsdup(yy__result->output), yk__sdsdup(t__23)))
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
            yk__sds t__24 = yk__sdsnew("---- running Yaksha compiler ---\n");
            yy__console_cyan(yk__sdsdup(t__24));
            yy__console_red(yk__sdsdup(yy__result->output));
            yk__sds t__25 = yk__sdsnew("\n");
            yk__printstr((t__25));
            yy__return_val = (- (1));
            yk__sds t__26 = yk__sdsnew("---- end of compiler run ---\n");
            yy__console_cyan(yk__sdsdup(t__26));
            yk__sdsfree(t__26);
            yk__sdsfree(t__25);
            yk__sdsfree(t__24);
        }
        yk__sdsfree(t__23);
    }
    int32_t t__27 = yy__return_val;
    yy__os_del_process_result(yy__result);
    yy__array_del_str_array(yy__yk_args);
    return t__27;
}
int32_t yy__perform_build() 
{
    struct yy__configuration_Config* yy__config = yy__configuration_load_config();
    if ((yk__arrlen(yy__config->yy__configuration_errors) > 0))
    {
        yy__print_errors(yy__config->yy__configuration_errors);
        int32_t t__28 = (- (1));
        yy__configuration_del_config(yy__config);
        return t__28;
    }
    yy__print_config(yy__config);
    int32_t yy__ret = yy__build_from_config(yy__config, false);
    int32_t t__29 = yy__ret;
    yy__configuration_del_config(yy__config);
    return t__29;
}
int32_t yy__perform_run(yk__sds yy__filename, bool yy__use_raylib, bool yy__use_web) 
{
    yk__sds t__30 = yy__path_basename(yk__sdsdup(yy__filename));
    yk__sds t__31 = yy__path_remove_extension(yk__sdsdup((t__30)));
    yk__sds yy__name = yk__sdsdup((t__31));
    struct yy__configuration_Config* yy__config = yy__configuration_create_adhoc_config(yk__sdsdup(yy__name), yk__sdsdup(yy__filename), yy__use_raylib, yy__use_web);
    if ((yk__arrlen(yy__config->yy__configuration_errors) > 0))
    {
        yy__print_errors(yy__config->yy__configuration_errors);
        int32_t t__32 = (- (1));
        yy__configuration_del_config(yy__config);
        yk__sdsfree(yy__name);
        yk__sdsfree(t__31);
        yk__sdsfree(t__30);
        yk__sdsfree(yy__filename);
        return t__32;
    }
    yy__print_config(yy__config);
    int32_t yy__ret = yy__build_from_config(yy__config, true);
    if ((yy__ret != 0))
    {
        int32_t t__33 = yy__ret;
        yy__configuration_del_config(yy__config);
        yk__sdsfree(yy__name);
        yk__sdsfree(t__31);
        yk__sdsfree(t__30);
        yk__sdsfree(yy__filename);
        return t__33;
    }
    yk__sds t__34 = yk__sdsnew("-----------------------------");
    yy__console_cyan(yk__sdsdup(t__34));
    yk__sds t__35 = yk__sdsnew("\n");
    yk__printstr((t__35));
    yk__sds yy__binary = yk__sdsdup(yy__name);
    if (yy__use_web)
    {
        yk__sds t__36 = yk__sdsnew(".html");
        yk__sds t__37 = yk__sdscatsds(yk__sdsdup(yy__binary), t__36);
        yk__sdsfree(yy__binary);
        yy__binary = yk__sdsdup(t__37);
        yk__sds t__38 = yy__os_cwd();
        yk__sds t__39 = yy__path_join(yk__sdsdup((t__38)), yk__sdsdup(yy__binary));
        yk__sds* yy__em_args = yy__array_new(2, yk__sdsdup(yy__config->yy__configuration_emrun_path), yk__sdsdup((t__39)));
        yy__os_run(yy__em_args);
        yy__array_del_str_array(yy__em_args);
        yk__sdsfree(t__39);
        yk__sdsfree(t__38);
        yk__sdsfree(t__37);
        yk__sdsfree(t__36);
    }
    else
    {
        if (yy__os_is_windows())
        {
            yk__sds t__40 = yk__sdsnew(".exe");
            yk__sds t__41 = yk__sdscatsds(yk__sdsdup(yy__binary), t__40);
            yk__sdsfree(yy__binary);
            yy__binary = yk__sdsdup(t__41);
            yk__sdsfree(t__41);
            yk__sdsfree(t__40);
        }
        else
        {
            yk__sds t__42 = yk__sdsnew("./");
            yk__sds t__43 = yk__sdscatsds(yk__sdsdup(t__42), yy__binary);
            yk__sdsfree(yy__binary);
            yy__binary = yk__sdsdup(t__43);
            yk__sdsfree(t__43);
            yk__sdsfree(t__42);
        }
        yy__c_CStr yy__binary_cstr = yy__strings_to_cstr(yk__sdsdup(yy__binary));
        yy__c_system(yy__binary_cstr);
    }
    yy__configuration_del_config(yy__config);
    yk__sdsfree(yy__binary);
    yk__sdsfree(t__35);
    yk__sdsfree(t__34);
    yk__sdsfree(yy__name);
    yk__sdsfree(t__31);
    yk__sdsfree(t__30);
    yk__sdsfree(yy__filename);
    return 0;
}
int32_t yy__handle_args(yy__os_arguments yy__args) 
{
    yy__argparse_Option* yy__options = NULL;
    yk__sds t__44 = yk__sdsnew("carpntr");
    yk__sds t__45 = yk__sdsnew("carpntr [options] file");
    yk__sds* yy__usages = yy__array_new(2, yk__sdsdup(t__44), yk__sdsdup(t__45));
    int32_t yy__run = 0;
    int32_t yy__raylib = 0;
    int32_t yy__web = 0;
    yk__arrput(yy__options, yy__argparse_opt_help());
    yk__sds t__46 = yk__sdsnew("R");
    yk__sds t__47 = yk__sdsnew("run");
    yk__sds t__48 = yk__sdsnew("run a single file");
    yk__arrput(yy__options, yy__argparse_opt_boolean(yk__sdsdup(t__46), yk__sdsdup(t__47), (&(yy__run)), yk__sdsdup(t__48)));
    yk__sds t__49 = yk__sdsnew("r");
    yk__sds t__50 = yk__sdsnew("raylib");
    yk__sds t__51 = yk__sdsnew("enable raylib (works only with run)");
    yk__arrput(yy__options, yy__argparse_opt_boolean(yk__sdsdup(t__49), yk__sdsdup(t__50), (&(yy__raylib)), yk__sdsdup(t__51)));
    yk__sds t__52 = yk__sdsnew("w");
    yk__sds t__53 = yk__sdsnew("web");
    yk__sds t__54 = yk__sdsnew("build for web (works only with run & raylib)");
    yk__arrput(yy__options, yy__argparse_opt_boolean(yk__sdsdup(t__52), yk__sdsdup(t__53), (&(yy__web)), yk__sdsdup(t__54)));
    yk__arrput(yy__options, yy__argparse_opt_end());
    yy__argparse_ArgParse yy__a = yy__argparse_new(yy__options, yy__usages);
    yy__argparse_ArgParseRemainder yy__remainder = yy__argparse_parse(yy__a, yy__args->argv);
    if ((yy__remainder->argc != 1))
    {
        yk__sds t__55 = yk__sdsnew("One file must be preset for excution");
        yk__printlnstr((t__55));
        yy__argparse_del_remainder(yy__remainder);
        yy__argparse_del_argparse(yy__a);
        yy__array_del_str_array(yy__usages);
        yk__arrfree(yy__options);
        yk__sdsfree(t__55);
        yk__sdsfree(t__54);
        yk__sdsfree(t__53);
        yk__sdsfree(t__52);
        yk__sdsfree(t__51);
        yk__sdsfree(t__50);
        yk__sdsfree(t__49);
        yk__sdsfree(t__48);
        yk__sdsfree(t__47);
        yk__sdsfree(t__46);
        yk__sdsfree(t__45);
        yk__sdsfree(t__44);
        return 1;
        yk__sdsfree(t__55);
    }
    yk__sds yy__single_file = yk__sdsdup(yy__remainder->remainder[0]);
    if (((yy__web == 1) && (yy__raylib != 1)))
    {
        yk__sds t__56 = yk__sdsnew("Web is only supported with raylib");
        yk__printlnstr((t__56));
        yy__argparse_del_remainder(yy__remainder);
        yy__argparse_del_argparse(yy__a);
        yy__array_del_str_array(yy__usages);
        yk__arrfree(yy__options);
        yk__sdsfree(t__56);
        yk__sdsfree(yy__single_file);
        yk__sdsfree(t__54);
        yk__sdsfree(t__53);
        yk__sdsfree(t__52);
        yk__sdsfree(t__51);
        yk__sdsfree(t__50);
        yk__sdsfree(t__49);
        yk__sdsfree(t__48);
        yk__sdsfree(t__47);
        yk__sdsfree(t__46);
        yk__sdsfree(t__45);
        yk__sdsfree(t__44);
        return 1;
        yk__sdsfree(t__56);
    }
    if ((yy__run == 1))
    {
        int32_t t__57 = yy__perform_run(yk__sdsdup(yy__single_file), (yy__raylib == 1), (yy__web == 1));
        yy__argparse_del_remainder(yy__remainder);
        yy__argparse_del_argparse(yy__a);
        yy__array_del_str_array(yy__usages);
        yk__arrfree(yy__options);
        yk__sdsfree(yy__single_file);
        yk__sdsfree(t__54);
        yk__sdsfree(t__53);
        yk__sdsfree(t__52);
        yk__sdsfree(t__51);
        yk__sdsfree(t__50);
        yk__sdsfree(t__49);
        yk__sdsfree(t__48);
        yk__sdsfree(t__47);
        yk__sdsfree(t__46);
        yk__sdsfree(t__45);
        yk__sdsfree(t__44);
        return t__57;
    }
    if ((yy__raylib == 1))
    {
        yk__sds t__58 = yk__sdsnew("Please use -R option for raylib");
        yk__printlnstr((t__58));
        yy__argparse_del_remainder(yy__remainder);
        yy__argparse_del_argparse(yy__a);
        yy__array_del_str_array(yy__usages);
        yk__arrfree(yy__options);
        yk__sdsfree(t__58);
        yk__sdsfree(yy__single_file);
        yk__sdsfree(t__54);
        yk__sdsfree(t__53);
        yk__sdsfree(t__52);
        yk__sdsfree(t__51);
        yk__sdsfree(t__50);
        yk__sdsfree(t__49);
        yk__sdsfree(t__48);
        yk__sdsfree(t__47);
        yk__sdsfree(t__46);
        yk__sdsfree(t__45);
        yk__sdsfree(t__44);
        return 1;
        yk__sdsfree(t__58);
    }
    yy__argparse_del_remainder(yy__remainder);
    yy__argparse_del_argparse(yy__a);
    yy__array_del_str_array(yy__usages);
    yk__arrfree(yy__options);
    yk__sdsfree(yy__single_file);
    yk__sdsfree(t__54);
    yk__sdsfree(t__53);
    yk__sdsfree(t__52);
    yk__sdsfree(t__51);
    yk__sdsfree(t__50);
    yk__sdsfree(t__49);
    yk__sdsfree(t__48);
    yk__sdsfree(t__47);
    yk__sdsfree(t__46);
    yk__sdsfree(t__45);
    yk__sdsfree(t__44);
    return 0;
}
int32_t yy__main() 
{
    yy__os_arguments yy__args = yy__os_get_args();
    yy__print_banner();
    if ((yy__args->argc <= 1))
    {
        int32_t t__59 = yy__perform_build();
        return t__59;
    }
    int32_t t__60 = yy__handle_args(yy__args);
    return t__60;
}
#if defined(YK__MINIMAL_MAIN)
int main(void) { return yy__main(); }
#endif
