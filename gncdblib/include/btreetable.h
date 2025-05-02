/**
 * @file btreetable.h
 * @author vera
 * @brief	BtreeTable结构体的定义以及有关B+树的操作函数声明
 * @version 0.1
 * @date 2023-01-30
 *
 * @copyright Copyright (c) 2023
 *
 */

#ifndef _GNCDB_BTREE_TABLE_H_
#define _GNCDB_BTREE_TABLE_H_

#include<stdbool.h>
#include"gncdbConstant.h"
#include "typeDefine.h"
#include"varArrayList.h"
#include"catalog.h"
// #include "gncdb.h"
#include "readwriteLock.h"
struct Tuple;
struct Transaction;
struct TableSchema;
struct PagePool;
struct BtreePage;
struct GNCDB;
struct InternalEntry;
struct Page;

 /* 表结构 */
typedef struct BtreeTable {
	char* tableName;			/* 表名 */
	int internalRecordLength;	/* InternalPage中定长记录的长度 */
	int leafRecordLength;		/* LeafPage中定长记录的长度 */
	int rootPageId;  			/* B + 树的根节点页号 */
	int rowNum;	
	ReadWriteLock rwlock_t;	/* 表锁 */
}BtreeTable;

/* btreeTable */
struct  BtreeTable* btreeTableConstruct(char* tableName, int rootPageId, struct TableSchema* tableSchema);
int getLeafTupleMaxCount(struct BtreeTable* btreeTable);
int getLeafTupleMinCount(struct BtreeTable* btreeTable);
int getInternalEntryMaxCount(struct BtreeTable* btreeTable);
int getInternalEntryMinCount(struct BtreeTable* btreeTable);
void btreeTableDestroy(struct BtreeTable** btreeTable);

/* btreeTable的基本操作 */
bool isPageSafe(struct BtreeTable* btreeTable, struct BtreePage* btreePage, OperationType op);
struct BtreePage* getLatchedPage(struct BtreeTable* btreeTable, struct GNCDB* db, int pageId, struct Transaction* tx);
struct BtreePage* createEmptyBtreePage(struct GNCDB* db, struct BtreeTable* btreeTable, PageType pageType, struct Transaction* tx);
int releaseWLatches(struct PagePool* pagePool, struct Transaction* tx, bool isDirty, int* releaseCont);
int unPinNewCreatePages(struct PagePool* pagePool, struct Transaction* tx);
int deletePages(struct PagePool* pagePool, struct Transaction* tx, struct GNCDB* db);
struct BtreePage* btreeTableFindTupleInLeafPage(struct BtreeTable* btreeTable, struct varArrayList* keyValueArray, struct TableSchema* tableSchema,
	struct GNCDB* db, struct Transaction* tx, OperationType op, bool first_pass,int *depth);
int produceOldPageData(struct GNCDB* db, struct Page* page, PageType pageTypeOfDeepCopy, struct Transaction* tx);
int backUpLatchedPage(struct GNCDB* db, struct Transaction* tx);
int updateParentPointer(struct BtreeTable* btreeTable, int pageId, struct GNCDB* db, struct Transaction* tx, int parentPageId);
int btreeTableGetRowNum(char* tableName, struct GNCDB* db, int*rowNum);
int getParentPageIdfromLatchedPage(int *parentPageId, struct Transaction* tx, int depth);


/* btreeTable_Insert */
int btreeTableInsertTuple(struct BtreeTable* btreeTable, struct Tuple* tuple, struct TableSchema* tableSchema, struct GNCDB* db, struct Transaction* tx);
int insertTuple(struct BtreeTable* btreeTable, struct BtreePage* btreePage, struct Tuple* tuple, struct TableSchema* tableSchema, struct GNCDB* db, struct Transaction* tx, int depth);
int btreeTableSplitPage(struct  BtreeTable* btreeTable, struct BtreePage* leftBtreePage, struct BtreePage* rightBtreePage, int index, struct GNCDB* db, struct Transaction* tx);
int btreeTableInsertInParentPage(struct BtreeTable* btreeTable, struct BtreePage* leftBtreePage, struct  InternalEntry* internalEntry,
	struct BtreePage* rightBtreePage, struct TableSchema* tableSchema, struct GNCDB* db, struct Transaction* tx, int depth);

/* btreeTable_delete */
int btreeTableDeleteTuple(struct BtreeTable* btreeTable, struct varArrayList* keyValueArray, struct TableSchema* tableSchema, 
	struct GNCDB* db, struct Transaction* tx,int* updatedPageId);
int deleteTuple(struct BtreeTable* btreeTable, struct BtreePage* btreePage, struct varArrayList* keyValueArray,
	struct TableSchema* tableSchema, struct GNCDB* db, struct Transaction* tx, int* updatedPageId, int depth);
int btreeTableMergePage(struct BtreeTable* btreeTable, struct BtreePage* parentBtreePage,struct BtreePage* leftBtreePage,
	struct BtreePage* rightBtreePage,struct GNCDB* db, struct Transaction* tx);
int btreeTableBorrowEntry(struct BtreeTable* btreeTable, struct BtreePage* parentBtreePage, struct BtreePage* leftBtreePage,
	struct InternalEntry* parentInternalEntry, struct BtreePage* rightBtreePage,
	struct TableSchema* tableSchema, struct GNCDB* db, struct Transaction* tx);
int btreeTableDeleteInParentPage(struct BtreeTable* btreeTable, struct BtreePage* btreePage, struct InternalEntry* firstInternalEntry,
	struct InternalEntry* secondInternalEntry, struct TableSchema* tableSchema, struct GNCDB* db, struct Transaction* tx, int depth, bool* isRootPageChanged);

/* btreeTable_Update */
int btreeTableUpdateTuple(struct BtreeTable* btreeTable, struct varArrayList* fieldNameArray, struct varArrayList* fieldValueArray,
	struct TableSchema* tableSchema, struct Tuple* tuple, struct GNCDB* db, struct Transaction* tx);

/* btreeTable_DropTable*/
int btreeTableDropTable(struct BtreeTable* btreeTable, struct GNCDB* db, struct Transaction* tx);

/* btreeTable_Load */
int btreeTableDfsTraversal(struct BtreeTable* btreeTable, struct GNCDB* db);

/* blob */
int deleteBlobInTuple(struct Tuple* tuple, struct TableSchema* tableSchema);
int checkBlobAndDeleteOverflowPage(struct Tuple* tuple, int columnNum, struct GNCDB* db,struct Transaction* tx);
int btreeTableSetBlob(struct GNCDB* db, struct BtreeTable* btreeTable, BYTE* buf, int size, struct varArrayList* overflowPageIdArray, struct Transaction* tx);
int btreeTableGetBlob(struct GNCDB* db, struct BtreeTable* btreeTable, struct Tuple* tuple, int columnNum, int size, BYTE* buf);
int deleteOverflowPages(struct PagePool* pagePool, struct Transaction* tx, struct GNCDB* db);

/* text */
int btreeTableGetText(struct GNCDB* db, struct BtreeTable* btreeTable, struct Tuple* tuple, int columnNum, int size, BYTE* buf);
/* printBtree */
int printBtree(struct BtreeTable* btreeTable, struct GNCDB* db);
int printBtreeToFile(struct BtreeTable* btreeTable, struct GNCDB* db);

#endif /* !_GNCDB_BTREE_TABLE_H_ */ 
