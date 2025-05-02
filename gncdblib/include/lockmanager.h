/*
 * @Descripttion: 
 * @version: 
 * @Author: Alan
 * @Date: 2023-01-30 09:19:39
 * @LastEditors: Alan
 * @LastEditTime: 2023-02-03 14:03:30
 */
#ifndef _LOCKMANAGE_H_
#define _LOCKMANAGE_H_

#include "gncdbconstant.h"
#include "hashmap.h"
#include "vararraylist.h"
#include "typedefine.h"
// #include "transaction.h"
#include "readwritelock.h"
#include "condvariable.h"
struct Transaction;

/* 一个锁结构 */
typedef struct LockEntry {
	int tid;					/* 事务id */
	LockType lockType;			/* 锁的类型 */
	bool isWait;				/* 是否等待 */
}LockEntry;

/* 锁表项 */
typedef struct LockTableEntry {
	int upgrading;				/* 标记当前是否有事务正在该请求队列上进行锁升级（记录锁升级的事务id），限制只能有一个事务进行锁升级，避免发生死锁 */
	varArrayList* lockEntryArray;	/* 对该页所有加锁的事务信息（存放的是LockEntry指针，即不同事务对当前页的加锁信息） */
	/*  pthread_cond_t cond;		条件变量（实现线程间的同步：阻塞和唤醒） */
	/*  pthread_mutex_t latch;		互斥锁 */
	Semaphore semaphore;
}LockTableEntry;

/* 锁管理器 */
typedef struct LockManager{
	ReadWriteLock latch;		/* 互斥锁，保护共享资源的一致性 */
	HashMap* pageTransactionLock;	/* 一个页被哪些事务锁住<pageId,lockTableEntry> */
}LockManager;

/* LockEntry */
struct LockEntry* lockEntryConstruct(int tid, LockType lockType, bool isWait);
void lockEntryDestroy(struct LockEntry** lockEntry);

/* LockTableEntry */
struct LockTableEntry* lockTableEntryConstruct();
void lockTableEntryDestroy(struct LockTableEntry** lockTableEntry);

/* LockManager */
struct LockManager* lockManagerConstruct();
void lockManagerDestroy(struct LockManager** lockManager);

int lockManagerAcquireLock(struct LockManager* lockManager, struct Transaction* tx, int pid, LockType lockType);
int lockManagerReleaseLock(struct LockManager* lockManager, struct Transaction* tx, int pid, LockType lockType);
int lockManagerReleaseAllLock(struct LockManager* lockManager, struct Transaction* tx);
int lockManagerInternalPageLock(struct LockManager* lockManager, struct Transaction* tx);

void lockManagerDestroyTableEntryByPageID(struct LockManager* lockManager, int pid);

bool isCompatiable(LockType lockTypeBefore, LockType lockTypeAfter); /* 是否满足锁升级的条件 */
bool grantCompatiable(LockType lockTypeFirst, LockType lockTypeSecond); /* 锁的授予是否满足兼容性*/
int unLockChangeState(struct Transaction* tx,LockType lockType); /* 事务释放锁了之后，其所处的状态可能需要发生相应的改变 */

LockTableEntry* getLockTableEntry(struct LockManager* lockManager,int pid);
int bookKeeping(struct Transaction* tx, int pid);
int bookKeepingRemove(struct Transaction* tx, int pid);
int updateLock(struct LockManager* lockManager, struct Transaction* tx, int pid, LockType lockType);
int grantLock(struct LockManager* lockManager, struct Transaction* tx, int pid, LockType lockType);
 
int lockEntryCompare(struct varArrayList* array, void* data1, void* data2);

#endif /* !_LOCKMANAGE_H_ */
