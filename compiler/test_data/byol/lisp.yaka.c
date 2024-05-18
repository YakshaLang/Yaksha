// YK
#include "yk__lib.h"
#define yy__numbers_cstr2i atoi
#define yy__c_CStr char*
#define yy__mpc_Ast mpc_ast_t*
#define yy__mpc_Mpc mpc_parser_t*
#define yy__mpc_Result mpc_result_t*
#define yy__mpc_new mpc_new
#define yy__mpc_mpca_lang mpca_lang
#define yy__mpc_cleanup mpc_cleanup
#define yy__mpc_parse mpc_parse
bool yy__strings_startswith(yk__sds, yk__sds);
yk__sds yy__strings_from_cstr(yy__c_CStr);
yy__mpc_Result yy__mpc_new_result();
void yy__mpc_err_print(yy__mpc_Result);
void yy__mpc_ast_del(yy__mpc_Result);
void yy__mpc_err_del(yy__mpc_Result);
yk__sds yy__io_readline(yk__sds);
int32_t yy__eval_op(int32_t, yk__sds, int32_t);
int32_t yy__eval(yy__mpc_Ast);
int32_t yy__main();
bool yy__strings_startswith(yk__sds nn__a, yk__sds nn__b) 
{
    bool x = (strstr(nn__a, nn__b) != NULL);
    yk__sdsfree(nn__a);
    yk__sdsfree(nn__b);
    return x;
}
yk__sds yy__strings_from_cstr(yy__c_CStr nn__a) 
{
    return yk__sdsnewlen(nn__a, strlen(nn__a));
}
yy__mpc_Result yy__mpc_new_result() 
{
    return calloc(1, sizeof(mpc_result_t));
}
void yy__mpc_err_print(yy__mpc_Result nn__r) 
{
    mpc_err_print(nn__r->output);
}
void yy__mpc_ast_del(yy__mpc_Result nn__r) 
{
    mpc_ast_delete(nn__r->output);
}
void yy__mpc_err_del(yy__mpc_Result nn__r) 
{
    mpc_err_delete(nn__r->output);
}
yk__sds yy__io_readline(yk__sds nn__prompt) 
{
    char* input = yk__readline(nn__prompt);
    yk__sds result = yk__sdsnew(input);
    free(input);
    yk__sdsfree(nn__prompt);
    return result;
}
int32_t yy__eval_op(int32_t yy__x, yk__sds yy__op, int32_t yy__y) 
{
    if (yk__cmp_sds_lit(yy__op, "+", 1) == 0)
    {
        int32_t t__0 = (yy__x + yy__y);
        yk__sdsfree(yy__op);
        return t__0;
    }
    if (yk__cmp_sds_lit(yy__op, "-", 1) == 0)
    {
        int32_t t__1 = (yy__x - yy__y);
        yk__sdsfree(yy__op);
        return t__1;
    }
    if (yk__cmp_sds_lit(yy__op, "*", 1) == 0)
    {
        int32_t t__2 = (yy__x * yy__y);
        yk__sdsfree(yy__op);
        return t__2;
    }
    if (yk__cmp_sds_lit(yy__op, "/", 1) == 0)
    {
        int32_t t__3 = (yy__x / yy__y);
        yk__sdsfree(yy__op);
        return t__3;
    }
    yk__sdsfree(yy__op);
    return INT32_C(0);
}
int32_t yy__eval(yy__mpc_Ast yy__t) 
{
    yk__sds t__4 = yy__strings_from_cstr(yy__t->tag);
    if (yy__strings_startswith(yk__sdsdup(t__4), yk__sdsnewlen("number", 6)))
    {
        int32_t t__5 = yy__numbers_cstr2i(yy__t->contents);
        yk__sdsfree(t__4);
        return t__5;
    }
    yk__sds t__6 = yy__strings_from_cstr(yy__t->children[INT32_C(1)]->contents);
    yk__sds yy__op = yk__sdsdup(t__6);
    int32_t yy__x = yy__eval(yy__t->children[INT32_C(2)]);
    int32_t yy__i = INT32_C(3);
    while (true)
    {
        yk__sds t__7 = yy__strings_from_cstr(yy__t->children[yy__i]->tag);
        if (yy__strings_startswith(yk__sdsdup(t__7), yk__sdsnewlen("expr", 4)))
        {
            yy__x = yy__eval_op(yy__x, yk__sdsdup(yy__op), yy__eval(yy__t->children[yy__i]));
            yy__i = (yy__i + INT32_C(1));
        }
        else
        {
            yk__sdsfree(t__7);
            break;
        }
        yk__sdsfree(t__7);
    }
    int32_t t__8 = yy__x;
    yk__sdsfree(yy__op);
    yk__sdsfree(t__6);
    yk__sdsfree(t__4);
    return t__8;
}
int32_t yy__main() 
{
    yy__mpc_Mpc yy__number = yy__mpc_new(yk__sdsnewlen("number", 6));
    yy__mpc_Mpc yy__operator = yy__mpc_new(yk__sdsnewlen("operator", 8));
    yy__mpc_Mpc yy__expr = yy__mpc_new(yk__sdsnewlen("expr", 4));
    yy__mpc_Mpc yy__lispy = yy__mpc_new(yk__sdsnewlen("lispy", 5));
    yk__sds yy__lang = yk__sdsnewlen("\n      number   : /-\?[0-9]+/ ;\n      operator : \'+\' | \'-\' | \'*\' | \'/\' ;\n      expr     : <number> | \'(\' <operator> <expr>+ \')\' ;\n      lispy    : /^/ <operator> <expr>+ /$/ ;\n    " , 179);
    yy__mpc_mpca_lang(INT32_C(0), yk__sdsdup(yy__lang), yy__number, yy__operator, yy__expr, yy__lispy);
    yk__printstr("Lispy Version 0.0.0.0.2\n");
    yk__printstr("Type just \'q\' to exit.\n\n");
    yk__sds yy__filename = yk__sdsnewlen("<stdin>" , 7);
    yy__mpc_Result yy__r = yy__mpc_new_result();
    while (true)
    {
        yk__sds t__9 = yy__io_readline(yk__sdsnewlen("lispy> ", 7));
        yk__sds yy__inp = yk__sdsdup(t__9);
        if (yk__cmp_sds_lit(yy__inp, "q", 1) == 0)
        {
            free(yy__r);
            free(yy__lispy);
            free(yy__expr);
            free(yy__operator);
            free(yy__number);
            yk__sdsfree(yy__inp);
            yk__sdsfree(t__9);
            yk__sdsfree(yy__filename);
            yk__sdsfree(yy__lang);
            return INT32_C(0);
        }
        if (yy__mpc_parse(yk__sdsdup(yy__filename), yk__sdsdup(yy__inp), yy__lispy, yy__r))
        {
            yk__printlnint((intmax_t)yy__eval(yy__r->output));
            yy__mpc_ast_del(yy__r);
        }
        else
        {
            yy__mpc_err_print(yy__r);
            yy__mpc_err_del(yy__r);
        }
        yk__sdsfree(yy__inp);
        yk__sdsfree(t__9);
    }
    yy__mpc_cleanup(INT32_C(4), yy__number, yy__operator, yy__expr, yy__lispy);
    yk__printstr(">>>bye!\n");
    free(yy__r);
    free(yy__lispy);
    free(yy__expr);
    free(yy__operator);
    free(yy__number);
    yk__sdsfree(yy__filename);
    yk__sdsfree(yy__lang);
    return INT32_C(0);
}
#if defined(YK__MINIMAL_MAIN)
int main(void) { return yy__main(); }
#endif