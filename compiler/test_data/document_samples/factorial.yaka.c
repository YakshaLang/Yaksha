// YK:console#
#include "yk__lib.h"
void yy__console_set_color(int32_t);
void yy__console_color_print(int32_t, struct yk__bstr);
void yy__console_red(struct yk__bstr);
void yy__console_cyan(struct yk__bstr);
int32_t yy__factorial(int32_t);
int32_t yy__main();
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
void yy__console_cyan(struct yk__bstr yy__console_x) 
{
    yy__console_color_print(INT32_C(7), yy__console_x);
    return;
}
int32_t yy__factorial(int32_t yy__x) 
{
    if (yy__x <= INT32_C(0))
    {
        return INT32_C(1);
    }
    int32_t t__0 = (yy__x * yy__factorial((yy__x - INT32_C(1))));
    return t__0;
}
int32_t yy__main() 
{
    int32_t yy__a = INT32_C(0);
    while (true)
    {
        if (!(((yy__a < INT32_C(10)))))
        {
            break;
        }
        yy__console_cyan(yk__bstr_s("factorial", 9));
        yy__console_red(yk__bstr_s("(", 1));
        yk__printint((intmax_t)yy__a);
        yy__console_red(yk__bstr_s(") = ", 4));
        yk__printlnint((intmax_t)yy__factorial(yy__a));
        yy__a = (yy__a + INT32_C(1));
    }
    return INT32_C(0);
}
#if defined(YK__MINIMAL_MAIN)
int main(void) { return yy__main(); }
#endif