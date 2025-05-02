/*
 * @Descripttion: 
 * @version: 
 * @Author: Alan
 * @Date: 2023-01-30 09:19:38
 * @LastEditors: Alan
 * @LastEditTime: 2023-02-01 19:22:57
 */
#ifndef _QUERYPLAN_H_
#define _QUERYPLAN_H_

#include "btreecursor.h"
#include "gncdbconstant.h"
#include "typedefine.h"
#include "tuple.h"
#include "operator.h"

#define INTLEN  13
#define DOUBLELEN  65
#define FIELDNAMELEN 20
typedef struct Transaction Transaction;
typedef struct Queryplan
{

    varArrayList* tableArray;          /* 一条查询计划中所有的表名 */
    HashMap* scanMap;                  /* 扫描算子 */
    HashMap* filterMap;                /* 过滤算子（key 表名，value filter算子 */
    varArrayList* joinArr;             /* join算子 */
    Projection* projection;            /* 投影 */
    CallBack callback;                 /* 回调函数 */
    TableSchema* tableSchema;          /* 结果集的Schema */
    Transaction* tx;                   /* 事务Id */
}Queryplan;
/* 构造一个查询计划 */ 
Queryplan* queryplanConstruct(CallBack callback, varArrayList* tableArray, struct Transaction* tx);
/* 保存scan算子 */
int queryplanPushScanOperator(struct Queryplan* queryplan, char* tableName, struct Scan* scan);
/* 保存filter算子 */ 
int queryplanPushFilterOperator(struct Queryplan* queryplan, char* tableName, struct Filter* filter);
/* 保存join算子 */ 
int queryplanPushJoinOperator(struct Queryplan* queryplan, struct Join* join);
/* 保存投影算子 */ 
int queryplanPushProjectionOperator(struct Queryplan* queryplan, struct Projection* projection);
/* 执行所有算子 */ 
int queryplanExecute(struct Queryplan* queryplan, int* affectedRows, Tuple** tupleReturn, struct GNCDB* db);
/* 销毁一个查询计划 */ 
int queryplanDestroy(struct Queryplan* queryplan);
/* 处理查询结果 */
int processQueryResult(Queryplan* queryplan, struct GNCDB* db, TableSchema* tableSchema, Tuple* tuple);
/* 执行所有算子,R树 */
int queryplanExecuteRtree(struct Queryplan* queryplan, int* affectedRows, Tuple** tupleReturn, struct GNCDB* db);

#endif