/*
 * @Descripttion: 
 * @version: 
 * @Author: Alan
 * @Date: 2023-01-30 09:19:39
 * @LastEditors: Alan
 * @LastEditTime: 2023-01-30 10:15:22
 */
#ifndef _TRANSACTION_H_
#define _TRANSACTION_H_

#include "gncdbconstant.h"
#include "typedefine.h"
#include "gncdb.h"
#include "vararraylist.h"
#include <time.h>

struct TransactionManager;
struct Page;
struct GNCDB;

struct TransactionManager;

/* oldData，用于事务失败时的回滚 */
typedef struct TidOld {
	int tid;
	void* oldPage;
}TidOld;

/* 事务 */
typedef struct Transaction{
	int id;							/* 事务id */
	TransactionStatus status;		/* 事务的状态 */
	IsolationLevel isolationLevel;	/* 事务的隔离级别 */
	varArrayList* preLSN;			/* 该事务对应的preLSN */
	HashMap* oldPageData;			/* 页的本来数据，key是int pid，value是TidOld，用于回滚 */
	varArrayList* latchedPageSet;	/* 使用物理锁锁住的页的集合（Page*） */
	varArrayList* newCreatedPageSet;/* 插入时新创建的页集合，因为需要维护页的四个指针信息需要频繁获取页进行修改，统计记录避免多次pin操作
									  （unpin是在所有操作完成之后且只有一次） */
	varArrayList* deletedPageSet;	/* 删除操作时发生合并导致某些页需要被删除，放在这里统一处理（Page*） */
	varArrayList* overflowPageSet;	/* 溢出页集合（Page*） */
	/* todo？释放逻辑锁 */
	varArrayList* tidPidArray;		/* 一个事务控制多个页array(id) 逻辑锁锁住的页 */
	HashMap* txFlushMap;			/* flushMap中该事务修改的的页节点 */

    struct TransactionManager* transactionManager;
}Transaction;

/* 创建和销毁 */
Transaction* transcationConstrcut(struct GNCDB* db);
void transcationDestroy(struct Transaction** tx, struct GNCDB* db);

/* 记录加锁的页、需要被删除的页 */
int addIntoLatchedPageSet(struct Transaction* tx, void* page);

varArrayList* getLatchedPageSet(struct Transaction* tx);

int addIntoNewCreatedPageSet(struct Transaction* tx, struct Page* page);

varArrayList* getNewCreatedPageSet(struct Transaction* tx);

int addIntoDeletedPageSet(struct Transaction* tx, struct Page* page);

varArrayList* getDeletedPageSet(struct Transaction* tx);

int addIntoOverflowPageSet(struct Transaction* tx, struct Page* page);

varArrayList* getOverflowPageSet(struct Transaction* tx);

int transactionMemTidPid(int pageId, struct Transaction* tx);

int transactionDelTidPid(int pageId, struct Transaction* tx);

varArrayList* transactionGetTidPidArray(struct Transaction* tx);

int transactionGetStatus(struct Transaction* transaction);

int transactionAddOldData(struct GNCDB* db, struct Transaction* tx, int pid, void* old);

int transactionExsitOldData(struct GNCDB* db, struct Transaction* tx, int pid);

int setBeforeImage(struct Transaction* tx, struct GNCDB* db);

int transactionUpdateStatus(struct Transaction* transaction, TransactionStatus status);

int transactionStart(struct Transaction* tx, struct GNCDB* db);

int transactionCommit(struct Transaction* tx, struct GNCDB* db);

int transactionRollback(struct Transaction* tx, struct GNCDB* db);

bool transactionExistPage(struct Transaction* tx, int pageId);

#endif
