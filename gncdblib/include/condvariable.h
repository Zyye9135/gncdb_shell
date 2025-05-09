/*
* @ProjectName: condVariable.h
*
* @Author: 
* @Createtime: 
* @LastEditor: 
* @LastEditTime:
*/

#ifndef _CONDVARIABLE_H_
#define _CONDVARIABLE_H_

#include "gncdbconstant.h"
#include "readwritelock.h"


#if defined(__linux__) || defined(_WIN32)
    #include <pthread.h>
    #include "utils.h"
    #define LOCK_COND pthread_cond_t
    #define LOCK_MUTEX pthread_mutex_t
    #define ABSTIME struct timespec
#else
    /* 天脉兼容 */
    #define ABSTIME SYSTEM_TIME_TYPE
    #define LOCK_COND Condt*
    #define LOCK_MUTEX ReadWriteLock  
    typedef struct Condt {
        SEMAPHORE_ID_TYPE condtId;
        int flag;  /* 标记这个锁是否被使用了 */
        int index; /* 锁的编号 */
    } Condt;

    typedef struct CondtLockPool {
        struct HashMap* CondtLockMap;  
        ReadWriteLock latch;                   
    } CondtLockPool;

    extern CondtLockPool* global_CondtLockPool;

    void CondtInit(Condt* cond_var, int index , RETURN_CODE_TYPE* return_code);
    int CondtLockPoolInit();
    Condt* CondtLockAcquire();
    int CondtLockRelease(Condt* cond_var);
    void CondtLockDestroy();
#endif

typedef struct Semaphore{
    LOCK_MUTEX lock_mutex;
    LOCK_COND lock_cond;
} Semaphore;

void condVariable_Init(Semaphore* semaphore);

void condVariable_Destroy(Semaphore* semaphore);

int condVariable_Wait(Semaphore* semaphore);

void condVariable_Broadcast(Semaphore* semaphore);

void condVariable_Signal(Semaphore* semaphore);

void condVariable_MutexInit(Semaphore* semaphore);

void condVariable_MutexLock(Semaphore* semaphore);

void condVariable_MutexUnLock(Semaphore* semaphore);

void condVariable_MutexDestroy(Semaphore* semaphore);

#endif