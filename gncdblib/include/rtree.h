/**
 * @file storage
 * @author vera
 * @brief	Rtree简单声明
 * @version 0.1
 * @date 2023-01-30
 *
 * @copyright Copyright (c) 2023
 *
 */



#ifndef _GNCDB_RTREE_PAGE_H_
#define _GNCDB_RTREE_PAGE_H_

#include "typeDefine.h"
#include "gncdbConstant.h"
#include "varArrayList.h"
#include "tuple.h"
#include "catalog.h"
#include "transaction.h"

struct TableSchema;

typedef struct RtreeTable { int rootPageId; char* tableName; }RtreeTable;
typedef struct RtreePage { int id; }RtreePage;
typedef struct RtreeCursor { int i; struct varArrayList* conditionArray;
}RtreeCursor;
typedef struct RtreeLeaf { 
	struct varArrayList* primarykey; 
	struct varArrayList* keyValueArray;
}RtreeLeaf;

typedef struct RtreeTuple {
	struct varArrayList* key;
	struct varArrayList* primkey;
}RtreeTuple;


int rtreeInsert(struct RtreeTable* rtreetable, struct varArrayList* keyValue, struct varArrayList* primValue, int I_si32_pageid,
	struct TableSchema* tableSchema, struct GNCDB* db, struct Transaction* tx, int v_si32_level);
/*删除关键字keyValueArray为被删除的目标key,primKeyArray为被删除的元组的主键*/
int rtreeDelete(struct RtreeTable* rtreetable, struct varArrayList* keyValueArray, struct varArrayList* primkeyArray, struct TableSchema* tableSchema,
	struct GNCDB* db, struct Transaction* tx);
/*在R树中找到keyValueArray应该属于的那个叶子页*/
struct RtreePage* rtreeTableFindTupleInLeafPage(struct RtreeTable* rtreetable, struct varArrayList* keyValueArray, struct TableSchema* tableSchema,
	struct GNCDB* db, int tid, int v_si32_level);
/*构筑RtreeTable v_si32_dim为该Rtree的维度*/
struct RtreeTable* rtreeTableConstruct(char* tableName, int rootPageId, int v_si32_dim, struct TableSchema* tableSchema);
/*构筑R树游标*/
struct RtreeCursor* rtreeCursorConstruct(struct GNCDB* db, struct varArrayList* searchvalue, char* tableName, int flag, struct Transaction* tx);
/*判断游标是否有下一个叶子节点对象*/
int rtreeTableHasNextTuple(struct RtreeCursor* rtreeCursor);
/*游标获取下一个叶子节点*/
//struct RtreeTuple* rtreeTableGetNext(struct RtreeTable* rtreeTable, struct RtreeCursor* rtreeCursor, struct GNCDB* db);



struct RtreePage* rtreePageConstructWithOutData(PageType pageType, int pageId, char* tableName, int parentPageId, struct GNCDB* db);

void rtreePageDestroy(struct RtreePage** RtreePage);

struct RtreePage* freePageToRtreePage(int pageId, PageType pageType, char* tableName, int parentPageId, struct GNCDB* db, struct Transaction* tx);

int pagePoolAddRtreePage(struct GNCDB* db, struct RtreePage* page, int pageId, struct Transaction* tx);

void rtreeCursorDestroy(struct RtreeCursor** btreeCursor);

struct RtreeTuple* rtreeTableGetNextTuple(struct RtreeTable* rtreeTable, struct RtreeCursor* rtreeCursor, struct GNCDB* db);

int rtreeTableDropTable(struct RtreeTable* rtreeTable, struct GNCDB* db, struct Transaction* tx);

int getRtreeDim(char* indexName);

#endif