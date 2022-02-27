#include "yk__lib.h"
// --forward declarations-- 
#define yy__numbers_cstr2i atoi
#define yy__strings_cstr char*
#define yy__mpc_Ast mpc_ast_t*
#define yy__mpc_Mpc mpc_parser_t*
#define yy__mpc_Result mpc_result_t*
#define yy__mpc_new mpc_new
#define yy__mpc_mpca_lang mpca_lang
#define yy__mpc_cleanup mpc_cleanup
#define yy__mpc_parse mpc_parse
bool yy__strings_is_empty_str(yk__sds);
bool yy__strings_startswith(yk__sds, yk__sds);
yk__sds yy__strings_from_cstr(yy__strings_cstr);
yy__mpc_Result yy__mpc_new_result();
void yy__mpc_ast_print(yy__mpc_Result);
void yy__mpc_err_print(yy__mpc_Result);
void yy__mpc_ast_del(yy__mpc_Result);
void yy__mpc_err_del(yy__mpc_Result);
yk__sds yy__io_readfile(yk__sds);
yk__sds yy__io_readline(yk__sds);
int32_t yy__eval_op(int32_t, yk__sds, int32_t);
int32_t yy__eval(yy__mpc_Ast);
int32_t yy__main();
// --structs-- 
// --functions-- 
bool yy__strings_is_empty_str(yk__sds nn__s) 
{
    bool x = yk__sdslen(nn__s) == 0;
    yk__sdsfree(nn__s);
    return x;
}
bool yy__strings_startswith(yk__sds nn__a, yk__sds nn__b) 
{
    bool x = (strstr(nn__a, nn__b) != NULL);
    yk__sdsfree(nn__a);
    yk__sdsfree(nn__b);
    return x;
}
yk__sds yy__strings_from_cstr(yy__strings_cstr nn__a) 
{
    return yk__sdsnewlen(nn__a, strlen(nn__a));
}
yy__mpc_Result yy__mpc_new_result() 
{
    return calloc(1, sizeof(mpc_result_t));
}
void yy__mpc_ast_print(yy__mpc_Result nn__r) 
{
    mpc_ast_print(nn__r->output);
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
yk__sds yy__io_readfile(yk__sds nn__fname) 
{
    size_t ln;
    int err;
    char *out = yk__bhalib_read_file(nn__fname, &ln, &err);
    yk__sdsfree(nn__fname); // clean up filename as it will be copied
    if (err == 0) { return yk__sdsnewlen(out, ln); }
    return yk__sdsempty();
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
    yk__sds t__0 = yk__sdsnew("+");
    if ((yk__sdscmp(yy__op , t__0) == 0))
    {
        yk__sdsfree(t__0);
        yk__sdsfree(yy__op);
        return (yy__x + yy__y);
    }
    yk__sds t__1 = yk__sdsnew("-");
    if ((yk__sdscmp(yy__op , t__1) == 0))
    {
        yk__sdsfree(t__1);
        yk__sdsfree(t__0);
        yk__sdsfree(yy__op);
        return (yy__x - yy__y);
    }
    yk__sds t__2 = yk__sdsnew("*");
    if ((yk__sdscmp(yy__op , t__2) == 0))
    {
        yk__sdsfree(t__2);
        yk__sdsfree(t__1);
        yk__sdsfree(t__0);
        yk__sdsfree(yy__op);
        return (yy__x * yy__y);
    }
    yk__sds t__3 = yk__sdsnew("/");
    if ((yk__sdscmp(yy__op , t__3) == 0))
    {
        yk__sdsfree(t__3);
        yk__sdsfree(t__2);
        yk__sdsfree(t__1);
        yk__sdsfree(t__0);
        yk__sdsfree(yy__op);
        return (yy__x / yy__y);
    }
    yk__sdsfree(t__3);
    yk__sdsfree(t__2);
    yk__sdsfree(t__1);
    yk__sdsfree(t__0);
    yk__sdsfree(yy__op);
    return 0;
}
int32_t yy__eval(yy__mpc_Ast yy__t) 
{
    yk__sds t__4 = yy__strings_from_cstr(yy__t->tag);
    yk__sds t__5 = yk__sdsnew("number");
    if (yy__strings_startswith(yk__sdsdup((t__4)), yk__sdsdup(t__5)))
    {
        yk__sdsfree(t__5);
        yk__sdsfree(t__4);
        return yy__numbers_cstr2i(yy__t->contents);
    }
    yk__sds t__6 = yy__strings_from_cstr(yy__t->children[1]->contents);
    yk__sds yy__op = yk__sdsdup((t__6));
    int32_t yy__x = yy__eval(yy__t->children[2]);
    int32_t yy__i = 3;
    while (1) {
        if (!(true)) { break; } // Check
        // Body of while loop

        {
            yk__sds t__7 = yy__strings_from_cstr(yy__t->children[yy__i]->tag);
            yk__sds t__8 = yk__sdsnew("expr");
            if (yy__strings_startswith(yk__sdsdup((t__7)), yk__sdsdup(t__8)))
            {
                yy__x = yy__eval_op(yy__x, yk__sdsdup(yy__op), yy__eval(yy__t->children[yy__i]));
                yy__i = (yy__i + 1);
            }
            else
            {
                break;
            }
            yk__sdsfree(t__8);
            yk__sdsfree(t__7);
        }
    }
    yk__sdsfree(yy__op);
    yk__sdsfree(t__6);
    yk__sdsfree(t__5);
    yk__sdsfree(t__4);
    return yy__x;
}
int32_t yy__main() 
{
    yk__sds t__9 = yk__sdsnew("number");
    yy__mpc_Mpc yy__number = yy__mpc_new(yk__sdsdup(t__9));
    yk__sds t__10 = yk__sdsnew("operator");
    yy__mpc_Mpc yy__operator = yy__mpc_new(yk__sdsdup(t__10));
    yk__sds t__11 = yk__sdsnew("expr");
    yy__mpc_Mpc yy__expr = yy__mpc_new(yk__sdsdup(t__11));
    yk__sds t__12 = yk__sdsnew("lispy");
    yy__mpc_Mpc yy__lispy = yy__mpc_new(yk__sdsdup(t__12));
    yk__sds t__13 = yk__sdsnew("\n      number   : /-?[0-9]+/ ;\n      operator : \'+\' | \'-\' | \'*\' | \'/\' ;\n      expr     : <number> | \'(\' <operator> <expr>+ \')\' ;\n      lispy    : /^/ <operator> <expr>+ /$/ ;\n    ");
    yk__sds yy__lang = yk__sdsdup(t__13);
    yy__mpc_mpca_lang(0, yk__sdsdup(yy__lang), yy__number, yy__operator, yy__expr, yy__lispy);
    yk__sds t__14 = yk__sdsnew("Lispy Version 0.0.0.0.2\n");
    printf("%s", (t__14));
    yk__sds t__15 = yk__sdsnew("Type just \'q\' to exit.\n\n");
    printf("%s", (t__15));
    yk__sds t__16 = yk__sdsnew("<stdin>");
    yk__sds yy__filename = yk__sdsdup(t__16);
    yy__mpc_Result yy__r = yy__mpc_new_result();
    while (1) {
        if (!(true)) { break; } // Check
        // Body of while loop

        {
            yk__sds t__17 = yk__sdsnew("lispy> ");
            yk__sds t__18 = yy__io_readline(yk__sdsdup(t__17));
            yk__sds yy__inp = yk__sdsdup((t__18));
            yk__sds t__19 = yk__sdsnew("q");
            if ((yk__sdscmp(yy__inp , t__19) == 0))
            {
                yk__sdsfree(t__19);
                yk__sdsfree(yy__inp);
                yk__sdsfree(t__18);
                yk__sdsfree(t__17);
                yk__sdsfree(yy__filename);
                yk__sdsfree(t__16);
                yk__sdsfree(t__15);
                yk__sdsfree(t__14);
                yk__sdsfree(yy__lang);
                yk__sdsfree(t__13);
                yk__sdsfree(t__12);
                yk__sdsfree(t__11);
                yk__sdsfree(t__10);
                yk__sdsfree(t__9);
                return 0;
            }
            if (yy__mpc_parse(yk__sdsdup(yy__filename), yk__sdsdup(yy__inp), yy__lispy, yy__r))
            {
                printf("%jd\n", ((intmax_t)yy__eval(yy__r->output)));
                yy__mpc_ast_del(yy__r);
            }
            else
            {
                yy__mpc_err_print(yy__r);
                yy__mpc_err_del(yy__r);
            }
            yk__sdsfree(t__19);
            yk__sdsfree(yy__inp);
            yk__sdsfree(t__18);
            yk__sdsfree(t__17);
        }
    }
    yy__mpc_cleanup(4, yy__number, yy__operator, yy__expr, yy__lispy);
    yk__sds t__20 = yk__sdsnew(">>>bye!\n");
    printf("%s", (t__20));
    free(yy__r);
    free(yy__lispy);
    free(yy__expr);
    free(yy__operator);
    free(yy__number);
    yk__sdsfree(t__20);
    yk__sdsfree(yy__filename);
    yk__sdsfree(t__16);
    yk__sdsfree(t__15);
    yk__sdsfree(t__14);
    yk__sdsfree(yy__lang);
    yk__sdsfree(t__13);
    yk__sdsfree(t__12);
    yk__sdsfree(t__11);
    yk__sdsfree(t__10);
    yk__sdsfree(t__9);
    return 0;
}
int main(void) { return yy__main(); }