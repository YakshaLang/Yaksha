// YK:cpu,tinycthread#
#include "yk__lib.h"
#define yy__mutex_Mutex mtx_t
#define yy__condition_Condition cnd_t
#define yy__thread_Thread thrd_t
int32_t const  yy__mutex_PLAIN = INT32_C(0);
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
int32_t const  yy__thread_SUCCESS = INT32_C(1);
struct yy__pool_ThreadPool;
typedef void (*yt_fn_in_any_ptr_out)(void*);
typedef int32_t (*yt_fn_in_any_ptr_out_int)(void*);
struct yt_tuple_fn_in_any_ptr_out_any_ptr { yt_fn_in_any_ptr_out e1; void* e2; };
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
int32_t yy__mutex_init(yy__mutex_Mutex*, int32_t);
void yy__mutex_destroy(yy__mutex_Mutex*);
int32_t yy__mutex_lock(yy__mutex_Mutex*);
int32_t yy__mutex_unlock(yy__mutex_Mutex*);
int32_t yy__condition_init(yy__condition_Condition*);
void yy__condition_destroy(yy__condition_Condition*);
int32_t yy__condition_signal(yy__condition_Condition*);
int32_t yy__condition_broadcast(yy__condition_Condition*);
int32_t yy__condition_wait(yy__condition_Condition*, yy__mutex_Mutex*);
struct yy__pool_ThreadPool* yy__pool_create(uint8_t, uint32_t);
int32_t yy__pool_add(struct yy__pool_ThreadPool*, yt_fn_in_any_ptr_out, void*);
int32_t yy__pool_destroy(struct yy__pool_ThreadPool*, bool);
int32_t yy__pool_internal_del_pool(struct yy__pool_ThreadPool*);
int32_t yy__pool_internal_tpool_work(void*);
int32_t yy__thread_create_with_data(yy__thread_Thread*, yt_fn_in_any_ptr_out_int, void*);
int32_t yy__thread_create(yy__thread_Thread*, yt_fn_in_any_ptr_out_int);
void yy__thread_exit(int32_t);
int32_t yy__thread_join(yy__thread_Thread);
int32_t yy__thread_sleep(int32_t);
int32_t yy__my_thread(void*);
void yy__print_num(void*);
int32_t yy__main();
int32_t yy__mutex_init(yy__mutex_Mutex* nn__mtx, int32_t nn__type) { return mtx_init(nn__mtx, nn__type); }
void yy__mutex_destroy(yy__mutex_Mutex* nn__mtx) { mtx_destroy(nn__mtx); }
int32_t yy__mutex_lock(yy__mutex_Mutex* nn__mtx) { return mtx_lock(nn__mtx); }
int32_t yy__mutex_unlock(yy__mutex_Mutex* nn__mtx) { return mtx_unlock(nn__mtx); }
int32_t yy__condition_init(yy__condition_Condition* nn__cnd) { return cnd_init(nn__cnd); }
void yy__condition_destroy(yy__condition_Condition* nn__cnd) { cnd_destroy(nn__cnd); }
int32_t yy__condition_signal(yy__condition_Condition* nn__cnd) { return cnd_signal(nn__cnd); }
int32_t yy__condition_broadcast(yy__condition_Condition* nn__cnd) { return cnd_broadcast(nn__cnd); }
int32_t yy__condition_wait(yy__condition_Condition* nn__cnd, yy__mutex_Mutex* nn__mtx) { return cnd_wait(nn__cnd, nn__mtx); }
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
int32_t yy__thread_create_with_data(yy__thread_Thread* nn__thr, yt_fn_in_any_ptr_out_int nn__func, void* nn__data) { return thrd_create(nn__thr, nn__func, nn__data); }
int32_t yy__thread_create(yy__thread_Thread* nn__thr, yt_fn_in_any_ptr_out_int nn__func) 
{
    return thrd_create(nn__thr, nn__func, NULL);
}
void yy__thread_exit(int32_t nn__res) { thrd_exit(nn__res); }
int32_t yy__thread_join(yy__thread_Thread nn__thr) 
{
    return thrd_join(nn__thr, NULL);
}
int32_t yy__thread_sleep(int32_t nn__seconds) 
{
    struct timespec t = {0, };
    t.tv_sec = nn__seconds;
    t.tv_nsec = 0;
    return thrd_sleep(&t, &t);
}
int32_t yy__my_thread(void* yy__arg) 
{
    yy__thread_sleep(INT32_C(1));
    yk__printlnstr("Hello from Thread");
    yy__thread_sleep(INT32_C(1));
    yk__printlnstr("Hello from Thread Again");
    return INT32_C(0);
}
void yy__print_num(void* yy__arg) 
{
    int32_t yy__a = ((int32_t)yy__arg);
    yk__printstr("Consumed ");
    yk__printlnint((intmax_t)yy__a);
    yy__thread_sleep(INT32_C(1));
    return;
}
int32_t yy__main() 
{
    yy__thread_Thread yy__t;
    yk__printlnstr("Hello from main thread");
    if (yy__thread_create((&(yy__t)), yy__my_thread) == yy__thread_SUCCESS)
    {
        yy__thread_join(yy__t);
    }
    struct yy__pool_ThreadPool* yy__p = yy__pool_create(UINT8_C(3), UINT32_C(1000));
    if (yy__p == NULL)
    {
        yk__printlnstr("Failed to create thread pool");
        return INT32_C(0);
    }
    int32_t yy__i = INT32_C(0);
    while (true)
    {
        if (!(((yy__i < INT32_C(40)))))
        {
            break;
        }
        yy__pool_add(yy__p, yy__print_num, yy__i);
        yy__i += INT32_C(1);
    }
    yy__pool_destroy(yy__p, true);
    return INT32_C(0);
}
#if defined(YK__MINIMAL_MAIN)
int main(void) { return yy__main(); }
#endif