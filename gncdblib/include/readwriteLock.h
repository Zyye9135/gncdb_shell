/*
* @ProjectName: readwriteLock.h
*
* @Author: vera
* @Createtime: 2024-1-8  13:30
* @LastEditor: vera
* @LastEditTime:
*/

#ifndef _READWRITELOCK_H_
#define _READWRITELOCK_H_

#include "gncdbConstant.h"
#include <pthread.h>
#if defined(__linux__) || defined(_WIN32)
#include <pthread.h>
#endif

extern int lockCount;
extern int unlockCount;
extern int maxLockNum;
extern int currentLock;

#if defined(__linux__) || defined(_WIN32)
#else
    struct Mutex;
#endif

#if defined(__linux__) || defined(_WIN32)
    #include <pthread.h>
    #define LOCK pthread_rwlock_t
#else
    /* @todo 待添加的天脉系统的头文件 */
    #define LOCK Mutex*
    #define TM_MUTEX_NAME_TYPE MUTEX_NAME_TYPE
    #define TM_PRIORITY_TYPE PRIORITY_TYPE
    #define TM_QUEUING_DISCIPLINE_TYPE QUEUING_DISCIPLINE_TYPE
    #define TM_RETURN_CODE_TYPE RETURN_CODE_TYPE
#endif

#if defined(__linux__) || defined(_WIN32)
#else
    typedef struct Mutex {
        SEMAPHORE_ID_TYPE mutex;
        int flag; /* 标记这个锁是否被使用了 */
        int index; /* 锁的编号 */
    } Mutex;

    typedef struct MutexLockPool {
        struct HashMap* MutexLockMap;  /* 缓冲池中所有的页 key是int pid, value是Page */
        Mutex* latch;                   
    } MutexLockPool;

    extern MutexLockPool* global_mutexLockPool;

    void MutexInit(Mutex* mtx, int index , RETURN_CODE_TYPE* return_code);
    void MutexLock(Mutex* mtx, RETURN_CODE_TYPE* return_code);
    void MutexUnLock(Mutex* mtx, RETURN_CODE_TYPE* return_code);

    int MutexLockPoolInit();
    Mutex* MutexLockAcquire();
    int MutexLockRelease(Mutex* mtx);
    void MutexLockDestroy();
#endif

typedef struct ReadWriteLock {
    LOCK lock; /* 如果是pthread的接口，那么就是读写锁，如果是天脉系统，就是互斥锁 */
#if defined(__linux__) || defined(_WIN32)
#else
    LOCK lock_read_cnt; /* 天脉系统下的互斥锁，保护read_cnt变量的 */
    int read_cnt;   /* 已经加读锁个数 */
#endif
} ReadWriteLock;

void ReadWriteLockInit(struct ReadWriteLock* read_write_lock);
void ReadLock(struct ReadWriteLock* read_write_lock);
void ReadUnLock(struct ReadWriteLock* read_write_lock);
void WriteLock(struct ReadWriteLock* read_write_lock);
void WriteUnLock(struct ReadWriteLock* read_write_lock);
void ReadWriteLockDestroy(struct ReadWriteLock* read_write_lock);

#endif