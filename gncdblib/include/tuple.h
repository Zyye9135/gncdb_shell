/**
 * @file tuple.h
 * @author vera
 * @brief	元组的定义及其相关操作函数的声明
 * @version 0.1
 * @date 2023-01-30
 *
 * @copyright Copyright (c) 2023
 *
 */

#ifndef _GNCDB_TUPLE_H_
#define _GNCDB_TUPLE_H_

#include<stdbool.h>
#include "btreetable.h"
#include"gncdbconstant.h"
#include"vararraylist.h"
#include"typedefine.h"
#include"field.h"
#include"catalog.h"
#include "tuple_cell.h"
#include "value.h"

/* 获取元组bitMap字节数组的大小 */ 
#define GET_BITMAP_LENGTH(columnNum) ((columnNum - 1) / 8 + 1)
struct TableSchema;
struct Catalog;

/* 叶子节点元组的内容 */
typedef struct Tuple {	
	varArrayList* fieldArray;		/* 字段内容 */
	BYTE* bitMap;					/* 记录元组各字段的值是否为空 */
}Tuple;


/* 内部节点的数据内容 */
typedef struct InternalEntry {
	int childPageId;				/* 孩子页id */
	varArrayList* keyValueArray;	/* Tuple主键的值，用于B + 树中的索引 */
}InternalEntry;

/* 叶子节点元组的操作 */
int leafTupleSetBitMap(struct Tuple* tuple, int fieldIndex, int flag);
int leafTupleGetBitMap(struct Tuple* tuple, int fieldIndex);
Tuple* leafTupleConstruct(int columnNum);
int leafTupleAddField(Tuple* tuple, Field* field);
int leafTupleGetKeyValue(varArrayList* keyValueArray,Tuple* tuple, struct TableSchema* tableSchema);
Tuple* leafTupleDeepCopy(varArrayList* fieldArray, struct TableSchema* tableSchema);
void leafTupleDestroy(void* data);
int leafTupleCompareFun(varArrayList* array, void* dataFirst, void* dataSecond);

/* 内部节点Entry的操作 */
InternalEntry* internalEntryConstruct(int childPageId);
int internalEntryAddEntry(InternalEntry* internalEntry, void* entry);
InternalEntry* internalEntryDeepCopy(int childPageId, varArrayList* keyValueArray, char* tableName, struct Catalog* catalog);
void internalEntryDestroy(void* internalEntry);
int internalEntryCompareFun(varArrayList* array, void* dataFirst, void* dataSecond);



/* RTree */
int leafTupleGetIndexKeyValue(struct varArrayList* keyValueArray, struct Tuple* tuple, struct TableSchema* indexSchema);

int leafTupleGetValueByIndex(varArrayList* valueArray, Tuple* tuple, int index);
#endif /* !_GNCDB_TUPLE_H_ */
