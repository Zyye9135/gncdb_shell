#ifndef QUERYEXECUTOR_H
#define QUERYEXECUTOR_H

#include "gncdb.h"
#include "transaction.h"
#include "queryplan.h"
#include "rtree.h"



int executorCreateTable(struct GNCDB* db, char* tableName, struct TableSchema* tableSchema, varArrayList* primaryKeyIndex, varArrayList* primaryKeyType, struct Transaction* tx);

int executorDropeTable(struct GNCDB* db, char* tableName, struct Transaction* tx);

int executorInsert(struct GNCDB* db, int* affectedRows, char* tableName,struct BtreeTable* table, struct TableSchema* tableSchema, struct Tuple* tuple, struct Transaction* tx);

int executorUpdate(struct GNCDB* db, int* affectedRows, char* tableName, varArrayList* updateAttrArray, varArrayList* updateFieldArray, struct varArrayList* conditionArray, struct Transaction* tx);

int executorDelete(struct GNCDB* db, int* affectedRows, char* tableName, struct varArrayList* conditionArray, struct Transaction* tx);

int executorSelect(struct GNCDB* db, CallBack2 callback, int* affectedRows, void* data, struct varArrayList* tableArray, struct varArrayList* columnNameArray, struct varArrayList* conditionArray, struct Transaction* tx);

int exectorParseCondition(struct TableSchema* tableSchema, struct Condition* condition);

int executorSetBlob(struct GNCDB* db, char* tableName, int columnNum, struct varArrayList* keyValueArray, BYTE* buf, int size, struct Transaction* tx);

int executorGetBlob(struct GNCDB* db, char* tableName, int columnNum, struct varArrayList* keyValueArray, BYTE* buf, int size, struct Transaction* tx);

int executorDeleteBlob(struct GNCDB* db, char* tableName, int columnNum, struct varArrayList* keyValueArray, struct Transaction* tx);

int executorSetTableParam(struct GNCDB* db, char* tableName, struct TableSchema* tableSchema, struct Transaction* tx);
/* RTree */
int executorRtreeInsert(struct GNCDB* db, char* tableName, char* indexName, struct Tuple* tuple, struct Transaction* tx);

int executorCreateRtreeIndex(struct GNCDB* db, char* tableName, char* indexName, int v_si32_dim, int maxrownum, 
							 struct TableSchema* indexSchema, struct Transaction* tx);

int executorDropeRtreeTable(struct GNCDB* db, char* indexName, struct Transaction* tx);

int executorRtreeDelete(struct GNCDB* db, char* tableName, Tuple* tuple, struct Transaction* tx);

int executorUpdateRtree(struct GNCDB* db, char* tableName, struct varArrayList* updateAttrArray, struct varArrayList* updateFieldArray,
						Tuple* tuple, struct Transaction* tx);
						
// todo:更改rtree的select接口
int executorRtreeSelect(struct GNCDB* db, CallBack callback, int* affectedRows, struct varArrayList* tableArray, struct varArrayList* columnNameArray,
	struct varArrayList* conditionArray, struct Transaction* tx);

int getRtreeSearchValue(varArrayList* conditionArray, varArrayList* searchvalue, char* indexName, TableSchema* indexSchema);
#endif
