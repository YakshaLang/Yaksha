#include "yk__lib.h"
// --forward declarations-- 
#define yy__mpc_Mpc mpc_parser_t*
#define yy__mpc_Result mpc_result_t*
#define yy__mpc_new mpc_new
#define yy__mpc_mpca_lang mpca_lang
#define yy__mpc_parse mpc_parse
yy__mpc_Result yy__mpc_new_result();
void yy__mpc_ast_print(yy__mpc_Result);
void yy__mpc_err_print(yy__mpc_Result);
yk__sds yy__io_readfile(yk__sds);
yk__sds yy__io_readline(yk__sds);
int32_t yy__main();
// --structs-- 
// --functions-- 
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
int32_t yy__main() 
{
    yk__sds t__0 = yk__sdsnew("number");
    yy__mpc_Mpc yy__number = yy__mpc_new(yk__sdsdup(t__0));
    yk__sds t__1 = yk__sdsnew("operator");
    yy__mpc_Mpc yy__operator = yy__mpc_new(yk__sdsdup(t__1));
    yk__sds t__2 = yk__sdsnew("expr");
    yy__mpc_Mpc yy__expr = yy__mpc_new(yk__sdsdup(t__2));
    yk__sds t__3 = yk__sdsnew("lispy");
    yy__mpc_Mpc yy__lispy = yy__mpc_new(yk__sdsdup(t__3));
    yk__sds t__4 = yk__sdsnew("\n      number   : /-?[0-9]+/ ;\n      operator : \'+\' | \'-\' | \'*\' | \'/\' ;\n      expr     : <number> | \'(\' <operator> <expr>+ \')\' ;\n      lispy    : /^/ <operator> <expr>+ /$/ ;\n    ");
    yk__sds yy__lang = yk__sdsdup(t__4);
    yy__mpc_mpca_lang(1, yk__sdsdup(yy__lang), yy__number, yy__operator, yy__expr, yy__lispy);
    yk__sds t__5 = yk__sdsnew("Lispy Version 0.0.0.0.2\n");
    printf("%s", (t__5));
    yk__sds t__6 = yk__sdsnew("Press Ctrl+c to Exit\n\n");
    printf("%s", (t__6));
    yk__sds t__7 = yk__sdsnew("<stdin>");
    yk__sds yy__filename = yk__sdsdup(t__7);
    while (1) {
        if (!(true)) { break; } // Check
        // Body of while loop

        {
            yk__sds t__8 = yk__sdsnew("lispy> ");
            yk__sds t__9 = yy__io_readline(yk__sdsdup(t__8));
            yk__sds yy__inp = yk__sdsdup((t__9));
            yy__mpc_Result yy__r = yy__mpc_new_result();
            if (yy__mpc_parse(yk__sdsdup(yy__filename), yk__sdsdup(yy__inp), yy__lispy, yy__r))
            {
                yy__mpc_ast_print(yy__r);
            }
            else
            {
                yy__mpc_err_print(yy__r);
            }
            yk__sdsfree(yy__inp);
            yk__sdsfree(t__9);
            yk__sdsfree(t__8);
        }
    }
    yk__sds t__10 = yk__sdsnew(">>>bye!\n");
    printf("%s", (t__10));
    yk__sdsfree(t__10);
    yk__sdsfree(yy__filename);
    yk__sdsfree(t__7);
    yk__sdsfree(t__6);
    yk__sdsfree(t__5);
    yk__sdsfree(yy__lang);
    yk__sdsfree(t__4);
    yk__sdsfree(t__3);
    yk__sdsfree(t__2);
    yk__sdsfree(t__1);
    yk__sdsfree(t__0);
    return 0;
}
int main(void) { return yy__main(); }