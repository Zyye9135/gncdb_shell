/**
 * @file btreeCursor.h
 * @author vera
 * @brief  定义游标的结构和利用游标实现相关遍历操作的函数定义
 * @version 0.1
 * @date 2023-02-16
 *
 * @copyright Copyright (c) 2023
 *
 */

#ifndef _BTREE_CURSOR_H_
#define _BTREE_CURSOR_H_

#include "typedefine.h"
#include "gncdbconstant.h"
#include "vararraylist.h"
// #include "btreetable.h"
// #include "transaction.h"
struct Transaction;
struct BtreeTable;
typedef struct BtreeCursor {
	struct GNCDB* db;
	struct Transaction* tx;
	struct BtreePage* page;
	int currentLeafPageId;			/* 当前叶子页页号 */ 
	int currentTupleIndex;			/* 在当前叶子页中目前所访问到的元组的index */ 
	
	//bool isCurrentlySatisfied;	/* 判断是否还有下一个tuple */ 
}BtreeCursor;

struct BtreeCursor* btreeCursorConstruct(char* tableName, struct GNCDB* db, struct varArrayList* startKeyValue, struct Transaction* tx);

void btreeCursorDestroy(struct BtreeCursor** btreeCursor);

int updateCursor(struct BtreeCursor* btreeCursor, struct GNCDB* db, char* tableName, int updatePageId);

bool btreeTableHasNextTuple(struct BtreeCursor* btreeCursor);

struct Tuple* btreeTableGetNextTuple(struct BtreeTable* btreeTable, struct BtreeCursor* btreeCursor, struct GNCDB* db);

#endif // !_BTREE_CURSOR_H_
