// YK
#include "yk__lib.h"
int32_t yy__main();
int32_t yy__main() 
{
    int32_t yy__c = INT32_C(0);
    while (true)
    {
        if (yy__c == INT32_C(2))
        {
            break;
        }
        yk__printlnint((intmax_t)INT32_C(1));
        yy__c += INT32_C(1);
    }
    return INT32_C(0);
}
#if defined(YK__MINIMAL_MAIN)
int main(void) { return yy__main(); }
#endif