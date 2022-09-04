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
#include "tinycthread.h"
// YK
#include "yk__lib.h"
// --forward declarations-- 
const int32_t yy__thread_THRD_ERROR = 0;
const int32_t yy__thread_THRD_SUCCESS = 1;
const int32_t yy__thread_THRD_TIMEOUT = 2;
const int32_t yy__thread_THRD_BUSY = 3;
const int32_t yy__thread_THRD_NOMEM = 4;
const int32_t yy__thread_MTX_PLAIN = 0;
const int32_t yy__thread_MTX_TIMED = 1;
const int32_t yy__thread_MTX_RECURSIVE = 2;
#define yy__thread_Mutex mtx_t
#define yy__thread_Condition cnd_t
#define yy__thread_Thread thrd_t
#define yy__thread_Data void*
typedef int32_t (*ykfncptr0)(yy__thread_Data);
int32_t yy__thread_mtx_init(yy__thread_Mutex*, int32_t);
void yy__thread_mtx_destroy(yy__thread_Mutex*);
int32_t yy__thread_mtx_lock(yy__thread_Mutex*);
int32_t yy__thread_mtx_trylock(yy__thread_Mutex*);
int32_t yy__thread_mtx_unlock(yy__thread_Mutex*);
int32_t yy__thread_cnd_init(yy__thread_Condition*);
void yy__thread_cnd_destroy(yy__thread_Condition*);
int32_t yy__thread_cnd_signal(yy__thread_Condition*);
int32_t yy__thread_cnd_broadcast(yy__thread_Condition*);
int32_t yy__thread_cnd_wait(yy__thread_Condition*, yy__thread_Mutex*);
int32_t yy__thread_thrd_create_with_arg(yy__thread_Thread*, ykfncptr0, yy__thread_Data);
int32_t yy__thread_thrd_create(yy__thread_Thread*, ykfncptr0);
yy__thread_Thread yy__thread_thrd_current();
int32_t yy__thread_thrd_detach(yy__thread_Thread);
int32_t yy__thread_thrd_equal(yy__thread_Thread, yy__thread_Thread);
void yy__thread_thrd_exit(int32_t);
int32_t yy__thread_thrd_join_with_result(yy__thread_Thread, int32_t*);
int32_t yy__thread_thrd_join(yy__thread_Thread);
void yy__thread_thrd_yield();
int32_t yy__my_thread(yy__thread_Data);
int32_t yy__main();
// --structs-- 
// --functions-- 
int32_t yy__thread_mtx_init(yy__thread_Mutex* nn__mtx, int32_t nn__type) { return mtx_init(nn__mtx, nn__type); }
void yy__thread_mtx_destroy(yy__thread_Mutex* nn__mtx) { mtx_destroy(nn__mtx); }
int32_t yy__thread_mtx_lock(yy__thread_Mutex* nn__mtx) { return mtx_lock(nn__mtx); }
int32_t yy__thread_mtx_trylock(yy__thread_Mutex* nn__mtx) { return mtx_trylock(nn__mtx); }
int32_t yy__thread_mtx_unlock(yy__thread_Mutex* nn__mtx) { return mtx_unlock(nn__mtx); }
int32_t yy__thread_cnd_init(yy__thread_Condition* nn__cnd) { return cnd_init(nn__cnd); }
void yy__thread_cnd_destroy(yy__thread_Condition* nn__cnd) { cnd_destroy(nn__cnd); }
int32_t yy__thread_cnd_signal(yy__thread_Condition* nn__cnd) { return cnd_signal(nn__cnd); }
int32_t yy__thread_cnd_broadcast(yy__thread_Condition* nn__cnd) { return cnd_broadcast(nn__cnd); }
int32_t yy__thread_cnd_wait(yy__thread_Condition* nn__cnd, yy__thread_Mutex* nn__mtx) { return cnd_wait(nn__cnd, nn__mtx); }
int32_t yy__thread_thrd_create_with_arg(yy__thread_Thread* nn__thr, ykfncptr0 nn__func, yy__thread_Data nn__arg) { return thrd_create(nn__thr, nn__func, nn__arg); }
int32_t yy__thread_thrd_create(yy__thread_Thread* nn__thr, ykfncptr0 nn__func) 
{
    return thrd_create(nn__thr, nn__func, NULL);
}
yy__thread_Thread yy__thread_thrd_current() { return thrd_current(); }
int32_t yy__thread_thrd_detach(yy__thread_Thread nn__thr) { return thrd_detach(nn__thr); }
int32_t yy__thread_thrd_equal(yy__thread_Thread nn__thr1, yy__thread_Thread nn__thr2) { return thrd_equal(nn__thr1, nn__thr2); }
void yy__thread_thrd_exit(int32_t nn__res) { thrd_exit(nn__res); }
int32_t yy__thread_thrd_join_with_result(yy__thread_Thread nn__thr, int32_t* nn__res) { return thrd_join(nn__thr, nn__res); }
int32_t yy__thread_thrd_join(yy__thread_Thread nn__thr) 
{
    return thrd_join(nn__thr, NULL);
}
void yy__thread_thrd_yield() { thrd_yield(); }
int32_t yy__my_thread(yy__thread_Data yy__arg) 
{
    yk__sds t__0 = yk__sdsnew("Hello from Thread");
    yk__printlnstr((t__0));
    yk__sdsfree(t__0);
    return 0;
}
int32_t yy__main() 
{
    yy__thread_Thread yy__t;
    if ((yy__thread_thrd_create((&(yy__t)), yy__my_thread) == yy__thread_THRD_SUCCESS))
    {
        yy__thread_thrd_join(yy__t);
    }
    return 0;
}
#if defined(YK__MINIMAL_MAIN)
int main(void) { return yy__main(); }
#endif
