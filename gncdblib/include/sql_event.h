#ifndef SQL_EVENT_H
#define SQL_EVENT_H
#include "exec_tuple.h"
typedef struct Stmt Stmt;
typedef struct PhysicalOperator PhysicalOperator;
typedef struct GNCDB GNCDB;
typedef struct Transaction Transaction;

typedef struct SqlResult {
  char **fieldNames;  ///< 字段名
  char **fieldValues; ///< 字段值
  int fieldCount;     ///< 字段数
} SqlResult;
void SqlResultReset(SqlResult *res);
void SqlResultDestroy(SqlResult **res);

// Q: 将SQLStageEvent改成Context是否更合理？？
typedef struct SQLStageEvent {
  const char *sql;        ///< 处理的SQL语句
  ParsedSqlNode *sqlNode; ///< 语法解析后的SQL命令
  Stmt *stmt;             ///< Resolver之后生成的数据结构
  PhysicalOperator *plan; ///< 生成的执行计划，也可能没有
  SqlResult *res;         ///< SQL执行结果，用于步骤执行
  GNCDB *db;
  Transaction *txn;
  int affectedRows;       ///< 影响的行数
  CallBack2 callback;      ///< 回调函数
  int subQueryLevel;      ///< 子查询的深度
  int isStep;             ///< 是否是步骤执行
  int isOpen;             ///< 是否是打开操作

  // 额外参数
  void* data;           ///< db_exec() 的第四个参数中提供的数据, 用于回调函数
  char** errmsg;        ///< 错误信息
} SQLStageEvent;

SQLStageEvent *SQLStageEventCreate();
void SQLStageEventReset(SQLStageEvent* sqlEvent);
void SQLStageEventInit(SQLStageEvent* sqlEvent);
void SQLStageEventDestroy(SQLStageEvent *sqlEvent);
#endif