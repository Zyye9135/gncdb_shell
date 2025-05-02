/*
 * @Descripttion: 
 * @version: 
 * @Author: Alan
 * @Date: 2023-01-30 09:19:38
 * @LastEditors: error: error: git config user.name & please set dead value or install git && error: git config user.email & please set dead value or install git & please set dead value or install git
 * @LastEditTime: 2024-08-27 09:46:42
 */
#ifndef _PAGEPOOL_H_
#define _PAGEPOOL_H_

#include "btreepage.h"
#include "hashmap.h"
#include "typedefine.h"
//#include "gncdb.h"
#include "os.h"
#include "rtree.h"
// #include "list.h"
#include <stdbool.h>
#include "tranmanager.h"

struct Page;
//struct GNCDB;
struct Transaction;
struct TransactionManager;
struct FreePage;
struct BtreePage;
struct OverflowPage;
struct RtreePage;
typedef struct _DList DList;

 /* 页逻辑控制结构体 */
typedef struct PageControlNode {
    int tid;                            /* 表示最近修改这个页的tid */
    void* oldPage;                      /* 指向Tx中的oldpagedate->TidOld->oldPage或者NULL */
    void* newPage;                      /* 指向pagepool中的页 */
    ReadWriteLock latch;                // 相当于每页的页锁，用以保证页的互斥访问 */
}PageControlNode;

/* 页状态结构体 */
typedef struct PageStatus
{
    bool dirty;       /* 表示页面是否被修改过 */
    int pin;          /* 是否被顶住 */
    int accessRecord; /* 缓冲池中存放的页被访问的次数 */

    int pageID;             /* 用于遍历下面两个队列时根据 value 找到对应的 key */
    struct PageStatus *pre; /* 用于维护缓存池的 cache 和 history 两个队列 */
    struct PageStatus *next;
} PageStatus;


/* 缓冲池结构体 */
typedef struct PagePool
{
    struct HashMap* pageMap;               /* 缓冲池中所有的页 key是int pid, value是Page */
    struct HashMap* pageStatus;            /* 页的状态 key是 int pid, value是Status */
    DList *cacheList;           /* 缓冲队列队头 */
    DList *historyList;         /* 历史队列队头 */
    // struct varArrayList* cacheArray;       /* 缓冲队列 */
    // struct varArrayList* historyArray;     /* 历史队列 */
    struct HashMap* pageControlMap;        /* <pid, pageControlNode> 所有页的PCNMap*/
    struct HashMap* flushMap;              /* <pid, pageControlNode> 表示一个检查点周期内需要刷入磁盘的页 */
    ReadWriteLock latchFlushMap;           /* 保护flushMap */
    ReadWriteLock latch;          /* 保护共享资源一致性 */
    ReadWriteLock pageControlMaplatch;
    ReadWriteLock latchStatusMap;          /* 保护pagestatusMap */
}PagePool;

/* 页状态的构造函数 */
PageStatus *pageStatusConstruct(int pageID);
void setPageStatusPre(struct PageStatus *status, struct PageStatus *pre);
void setPageStatusNext(struct PageStatus *status, struct PageStatus *next);

/* 页状态的销毁函数 */
void pageStatusDestroy(struct PageStatus* status);
/* 缓冲池构造函数 */
int pagePoolConstruct(struct GNCDB* db);
/* 缓冲池的销毁函数 */
void pagePoolDestroy(struct PagePool* pagePool);
/* 交换两个页的信息 */
int pageExchange(struct PagePool* pagePool, int pageId1, struct Page* page1, int pageId2, struct Page* page2);
/* 获取一个页的状态 */
PageStatus* getPageStatus(struct PagePool* pagePool, int pid);
/* 设置页为脏页 */
int setPageStatusDirty(struct PagePool* pagePool, int pageId);
/* 取消页为脏页 */
int setPageStatusClear(struct PagePool* pagePool, int pageId);
/* pin住一个页 */
int setPageStatusPinUp(struct PagePool* pagePool, int pageId);
/* 解pin */
int setPageStatusPinDown(struct PagePool* pagePool, int pageId);
/* 撤销一个事务的页 */
int cancelTargetedPageofTransaction(struct GNCDB* db, struct Transaction* tx);
/* freePage减少一个页 */
int freePageNumReduce(struct GNCDB* db, int pageId);
/* 获取第一个freepage页 */
int getFirstFreePageId(struct GNCDB* db, int *firstFreePageId,struct Transaction* tx);
/* 获取一个页 */
int pagePoolGetPage(struct Page** page, int pageId,  char* tableName, struct GNCDB* db);
/* 创建一个freepage页 */
int pagePoolCreateFreePage(struct FreePage** page, struct GNCDB* db);
/* 创建一个BtreePage页 */
int pagePoolCreateBtreePage(struct BtreePage** page, PageType pageType, char* tableName, struct GNCDB* db,struct Transaction* tx);
/* 创建一个OverflowPage页 */
int pagePoolCreateOverflowPage(struct OverflowPage** page,  struct GNCDB* db,struct Transaction* tx);
/* 淘汰一个页 */
int pagePoolReplacePage(struct GNCDB* db);
/* 添加一个页 */
int pagePoolAddPage(struct Page* page, int pageId, struct GNCDB* db);

/* 从缓冲池中移除一个页*/
int pagePoolRemovePage(struct PagePool* pagePool, int pageId);
/* 缓冲池刷出一个页 */
int pagePoolFlushPage(int pageId, struct GNCDB* db);
/* 刷出所有的脏页 */
int pagePoolFlushAllDirtyPages(struct GNCDB* db);
/* btreePage转化FreePage */
int btreePageToFreePage(struct BtreePage* btreePage, struct GNCDB* db);
/* overflowPage转化FreePage */
int overflowPageToFreePage(struct OverflowPage* overflowPage, struct GNCDB* db);

int pagePoolAddFlushOld(struct GNCDB* db, struct Transaction* tx, int pid, void* oldPage);

int pagePoolAddFlushNew(struct GNCDB* db, struct Transaction* tx);

int pageControlMapExists(struct PagePool* pagePool, int pid);

int flushMapExists(struct PagePool* pagePool, int pid);

/* CheckPoint刷页 */
int FlushCheckPoint(struct GNCDB* db);

int pagePoolRollBackFlush(struct GNCDB* db, struct Transaction* tx);


/* LRU_K 调整 */
int LRU_Kset(PagePool* pagePool, int pageId, int access);

int pagePoolRemovePCN(PagePool* pagepool, int pid);


/* 输出页的pin */
int printfPagePin(PagePool* pagePool);
int printfHashKey(HashMap* map);
//创建RtreePage页
int pagePoolCreateRtreePage(struct RtreePage** page, PageType pageType,
    char* tableName, int parentPageId, struct GNCDB* db,struct Transaction* tx);
#endif