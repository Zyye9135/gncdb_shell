
/**
 * @file operator.h
 * @author xdb
 * @brief 为用户提供算子模型，供用户输入，
 * 然后将被组织到执行计划中进行执行
 * @date 2023-02-14
 *
 * @copyright Copyright (c) 2023
 */


#ifndef _OPERATOR_H_
#define _OPERATOR_H_

#include "rtree.h"
#include "vararraylist.h"
#include "typedefine.h"
#include "gncdb.h"
#include "tuple.h"

/* 算子类型 */
typedef struct Operator
{
	enum OperatorType type;
}Operator;

/* 构建一个算子类型 */
Operator* operatorConstruct(enum OperatorType type);
/* 销毁一个算子类型 */
int operatorDestroy(struct Operator* operator);

/* SCAN算子 */
typedef struct Scan
{
	Operator* baseinfo;
	char* tableName;
	bool isEnd;
	varArrayList* startKeyValue;
	varArrayList* maxValue;
	BtreeCursor* cursor;		/* 遍历游标 */
}Scan;

/* RTREESCAN算子 */
typedef struct RtreeScan
{
	Operator* baseinfo;
	char* tableName;
	varArrayList* searchvalue;
	RtreeCursor* cursor;		/* 遍历游标 */
}RtreeScan;

/* scan算子构造函数 */ 
Scan* scanConstruct(struct GNCDB* db, char* tableName, varArrayList* startKeyValue, varArrayList* maxValue, struct Transaction* tx);
/* 重置cursor,用于join时重复遍历 */
int resetScan(Scan* scan, struct GNCDB* db, struct Transaction* tx);
/* 判断是否有下一条记录 */ 
bool hasNextTuple(Scan* scan);
/* 获取下一条记录 */ 
Tuple* operatorScan(struct GNCDB* db, Scan* scan);
/* scan算子销毁函数 */ 
void scanDestroy(Scan* scan);

/* 过滤条件 */
typedef struct Condition 
{
	void* value;				/* 比较值 */
	char* fieldName;			/* 字段名称 */
	Predicate predicate;		/* 比较符号 */
}Condition;

struct Condition* conditionConstruct(void* value, char* fieldName, Predicate predicate);
void conditonDestroy(void* data);


/* Filter 算子 */
typedef struct Filter
{
	Operator* baseinfo;
	char* tableName;
	varArrayList* conditionArray;
}Filter;

/* 创建一个filter算子并初始化 */
Filter* filterConstruct(struct GNCDB* db, struct varArrayList* conditionArray, char* tableName);
/* filter算子的实现 */
bool operatorFilter(Filter* filter, Tuple* tuple, TableSchema* tableSchema);
/* 销毁一个filter算子 */
int filterDestroy(struct Filter* filter);

/* Join 算子 */
typedef struct Join
{
	Operator* baseinfo;
	char* tableName1;
	char* tableName2;
	varArrayList* conditionArray;
}Join;

/* 构造一个Join算子并进行初始化 */
Join* joinConstruct(GNCDB* db, char* tableName1, char* tableName2, varArrayList* conditionArray);
/* join算子的实现 */
int operatorJoin(GNCDB* db, Tuple** newTuple, TableSchema* tableSchema1, struct Tuple* tuple1, TableSchema* tableSchema2, struct Tuple* tuple2, Join* join, struct Transaction* tx);
/* 销毁一个Join算子 */
int joinDestroy(struct Join* join);

/* Projection 算子 */
typedef struct Projection
{
	Operator* baseinfo;
	varArrayList* fieldNameArray;
}Projection;

/* 构造一个projection算子 */
Projection* projectionConstruct(struct GNCDB* db, varArrayList* array);
/* projection算子的实现 */
int operatorProjection(struct GNCDB* db, struct TableSchema* tableSchema, struct Tuple** pNewTuple, struct Tuple* tuple, struct Projection* projection, struct Transaction* tx);
/* 销毁一个projection算子 */
int projectionDestroy(struct Projection* projection);

//RTree
RtreeScan* rtreeScanConstruct(struct GNCDB* db, char* tableName, struct varArrayList* searchvalue, struct Transaction* tx);

int resetRtreeScan(RtreeScan* scan, struct GNCDB* db, struct Transaction* tx);

bool rtreeHasNextTuple(RtreeScan* scan);

Tuple* operatorRtreeScan(struct GNCDB* db, RtreeScan* scan);

void RtreeScanDestroy(RtreeScan* scan);

#endif // !_OPERATOR_H_


