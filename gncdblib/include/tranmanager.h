/*
 * @Descripttion:
 * @version:
 * @Author: Alan
 * @Date: 2023-01-30 09:19:39
 * @LastEditors: Alan
 * @LastEditTime: 2023-02-03 13:55:37
 */
#ifndef _TRANMANAGER_H_
#define _TRANMANAGER_H_


#include "gncdb.h"
#include "lockmanager.h"
#include "logger.h"


 /* 事务管理器 */
typedef struct TransactionManager {
    struct LockManager* lockManager;	/* 锁管理器 */
    struct Logger* logger;				/* 日志 */
    HashMap* txMap;				        /* 所有事务的集合 */
    int tid;                            /* 分配事务tid */
    ReadWriteLock latch;			    /* 互斥锁，保护共享资源 */
    ReadWriteLock tidLatch;			/* 互斥锁，保护tid */
}TransactionManager;

TransactionManager* txManagerConstruct(struct GNCDB* db);

void txManagerDestroy(struct TransactionManager** txManager);

int transrManageGetMemPage(struct TransactionManager* transrMan, varArrayList** page_array, struct Transaction* tx);

int transrManageMenTransaction(struct TransactionManager* transrMan, struct Transaction* tx);

int transrManageDelTransaction(struct TransactionManager* transrMan, struct Transaction* tx);

int transrManageGetTransaction(struct TransactionManager* transrMan, struct Transaction** tx, int tid);

int transrManageGetPreLogger(struct TransactionManager* transrMan, int** preLogger, struct Transaction* tx);

#endif
