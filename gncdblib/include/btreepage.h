/**
 * @file btreepage.h
 * @author vera
 * @brief  B+树中页的定义以及有关页操作的函数声明
 * @version 0.1
 * @date 2023-01-30
 *
 * @copyright Copyright (c) 2023
 *
 */

#ifndef _GNCDB_BTREE_PAGE_H_
#define _GNCDB_BTREE_PAGE_H_

#include "typeDefine.h"
#include "gncdbConstant.h"
#include "varArrayList.h"
#include "tuple.h"
// #include "gncdb.h"
#include "catalog.h"
#include "readwriteLock.h"
struct TableSchema;
struct Catalog;
struct Transaction;
struct BtreeTable;
struct Tuple;
struct InternalEntry;

typedef struct Page {
	PageType pageType; 		/* 页的类型 */ 
	int id;   					/* 页的id */ 
	ReadWriteLock rwlock_t;	/* 读写锁 */ 
}Page;

typedef struct BtreePage {
	struct Page page;
	char* tableName; 			/* tableName */ 
	int keyLength; 			/* 主键长度 */ 
	int entryNum;				/* Tuple的数量 */ 
	int nextPageId;			/* 内部节点最右边孩子页号 / 叶子节点右边节点页号（维护一条类似从最左边叶子节点到最右边叶子节点的链表）  */ 
	struct varArrayList* entryArray;		/* 存放当前页所有tuple,并按照主键值从小到大排序 */
}BtreePage;

/* 紧接着溢出页页头后4个字节存放当前页的溢出数据的字节数 */ 
typedef struct OverflowPage {
	Page page;
	int nextPageId;			/* 溢出页是下一溢出页的id */
	BYTE* overflowData;		/* 溢出数据部分 */ 
}OverflowPage;

typedef struct FreePage {
	Page page;				
	int nextPageId;			/* 下一空白页的id  */ 
}FreePage;

/* page */
void pageInit(struct Page* page,int pageId, PageType pageType);

/* btreePage */
int btreePageFillInHeader(struct BtreePage* btreePage, BYTE* buf);
int btreePageReadHeader(struct BtreePage* btreePage, BYTE* buf);
int leafPageSerialzation(char* tableName, struct Catalog* catalog, BYTE* pageData, int offset, struct TableSchema* tableSchema, struct BtreePage* leafPage);
int internalPageSerialzation(char* tableName, struct Catalog* catalog, BYTE* pageData, int offset, struct TableSchema* tableSchema, struct BtreePage* internalPage);
BtreePage* btreePageConstruct(BYTE* pageData, int pageId, char* tableName, struct TableSchema* tableSchema, struct Catalog* catalog);
struct BtreePage* btreePageConstructWithOutData(PageType pageType, int pageId, char* tableName, struct Catalog* catalog);
struct BtreePage* btreePageDeepCopy(struct BtreePage* btreePage, struct Catalog* catalog);
BYTE* btreePageToByte(struct BtreePage* btreePage, struct TableSchema* tableSchema);
void btreePageDestroy(struct BtreePage** btreePage);

int btreePageExchange(struct BtreeTable* btreeTable, struct BtreePage* leftBtreePage, struct BtreePage* parentBtreePage, struct GNCDB* db, struct Transaction* tx);

/*  leafPage */
int leafPageInsertTuple(struct BtreePage* btreePage, struct  Tuple* tuple);
int leafTupleCompareCertainFieldValue(void* valueFirst,void* valueSecond,FieldType fieldType, Predicate predicate) ;
struct Tuple* leafPageFindEntryByKeyvalue(struct BtreePage* btreePage, struct varArrayList* keyValueArray, struct TableSchema* tableSchema, char* tableName, struct Catalog* catalog, Predicate predicate);
int leafPageDeleteTuple(struct BtreePage* btreePage, struct varArrayList* keyValueArray, struct TableSchema* tableSchema, char* tableName, struct Catalog* catalog);

/* internalPage */
int getIndexOfChildPage(struct BtreePage* btreePage, int childPageId);
int internalPageInsertEntry(struct BtreePage* btreePage, struct InternalEntry* internalEntry);
int internalTupleCompareCertainFieldValue(void* valueFirst,void* valueSecond,FieldType fieldType, Predicate predicate);
struct InternalEntry* internalPageFindEntryByKeyvalue(struct BtreePage* btreePage, struct varArrayList* keyValueArray, struct TableSchema* tableSchema, char* tableName, struct Catalog* catalog, Predicate predicate);
int internalPageDeleteEntry(struct BtreePage* btreePage, struct varArrayList* keyValueArray, struct TableSchema* tableSchema, char* tableName, struct Catalog* catalog);

/* overflowPage */
int overflowPageFillInHeader(struct OverflowPage* overflowPage, BYTE* buf);
int overflowPageReadHeader(struct OverflowPage* overflowPage, BYTE* buf);
OverflowPage* overflowPageConstruct(BYTE* pageData, int pageId);
struct OverflowPage* overflowPageConstructWithOutData(int pageId, int nextPageId);
struct OverflowPage* overflowPageDeepCopy(OverflowPage* overflowPage);
BYTE* overflowPageToByte(struct OverflowPage* overflowPage);
void overflowPageDestroy(OverflowPage** overflowPage);

/* freePage */
int freePageFillInHeader(struct FreePage* freePage, BYTE* buf);
int freePageReadHeader(struct FreePage* freePage, BYTE* buf);
struct FreePage* freePageConstruct(BYTE* pageData, int pageId);
struct FreePage* freePageConstructWithOutData(int pageId,int nextPageId);
struct FreePage* freePageDeepCopy(int pageId, int nextPageId);
BYTE* freePageToByte(struct FreePage* freePage);
void freePageDestroy(struct FreePage** freePage);

/* debug */
/* 输出指定页中的tuple主键 */
int printfLeftPageTuplePKey(BtreePage* page);


#endif // !_GNCDB_BTREE_PAGE_H_
