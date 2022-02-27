#include "yk__lib.h"
// --forward declarations-- 
struct yy__mpc_Mpc;
#define yy__mpc_Mpc mpc_parser_t*
#define yy__mpc_new mpc_new
#define yy__mpc_mpca_lang mpca_lang
int32_t yy__main();
// --structs-- 
// --functions-- 
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
    yk__sdsfree(yy__lang);
    yk__sdsfree(t__4);
    yk__sdsfree(t__3);
    yk__sdsfree(t__2);
    yk__sdsfree(t__1);
    yk__sdsfree(t__0);
    return 0;
}
int main(void) { return yy__main(); }