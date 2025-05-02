/*
 * @Descripttion:
 * @version:
 * @Author: Alan
 * @Date: 2023-01-30 09:19:38
 * @LastEditors: Alan
 * @LastEditTime: 2023-01-31 09:39:44
 */
#ifndef TYPE_DEFINE_H_
#define TYPE_DEFINE_H_

#include "readwriteLock.h"
#include "condVariable.h"

typedef unsigned char BYTE;
typedef enum FieldType FieldType;
typedef enum PageType PageType;
typedef enum Predicate Predicate;
typedef enum LockType LockType;
typedef enum TableType TableType;
typedef enum OperatorType OperatorType;
typedef enum TransactionStatus TransactionStatus;
typedef enum IsolationLevel IsolationLevel;
typedef enum LogType LogType;
typedef enum OperationType OperationType;
typedef enum LogLockObjType LogLockObjType;
typedef enum LogLockType LogLockType;

typedef int (*CallBack)(int, char **, char **);
typedef int (*CallBack2)(void*, int, char **, char **);

/* 定义不同的操作类型，
主要是针对btreeTableFindTupleInLeafPage函数，可以根据不同的操作类型进行不同的加锁思路 */
enum OperationType
{
    OP_SEARCH,
    OP_INSERT,
    OP_DELETE,
    OP_UPDATE,
    OP_BLOB_SET,
    OP_BLOB_GET,
    OP_BLOB_DELETE
};
/* 日志加解锁对象类别 */
enum LogLockObjType
{
    TABLE_LOCK,
    PAGE_LOCK,
    DATABASE_LOCK,
    LOGGER_LOCK,
    CATALOG_LOCK,
    PAGEPOOL_LOCK,
    TXMANAGER_LOCK,
};
/* 锁类别 */
enum LogLockType
{
    LOCK_ING,
    UNLOCK_ING,
    LOCK_END,
    UNLOCK_END,
};
/*  事务状态 */
enum TransactionStatus
{
    GROWING,
    SHRINKING,
    COMMITTED,
    ABORTED
};

/* 事务的隔离级别 */
enum IsolationLevel
{ /* 默认只实现读已提交这一种隔离级别 */
  READ_COMMITTED
};

enum PageType
{
    LEAF_PAGE,
    INTERNAL_PAGE,
    OVERFLOW_PAGE,
    FREE_PAGE
};

enum FieldType
{   
    FIELDTYPE_INVALID,
    FIELDTYPE_INTEGER,
    FIELDTYPE_REAL,    // 浮点类型
    FIELDTYPE_VARCHAR, // 字符串
    FIELDTYPE_BLOB,
    FIELDTYPE_DATE,
    FIELDTYPE_DATETIME,
    FIELDTYPE_TEXT,
};

enum Predicate
{
    EQUAL,
    GREATER_THAN,
    GREATER_THAN_OR_EQUAL,
    NOT_EQUAL,
    LESS_THAN,
    LESS_THAN_OR_EQUAL
};

// enum LockStatus
// {
//     LOCK_UP,
//     LOCK_UN
// };

enum LockType
{
    SHARD,
    EXCLUSIVE,
    UNKNOW
};

enum TableType
{
    TableType_TABLE,
    TableType_INDEX
};

enum OperatorType
{
    OperatorType_SELECT,
    OperatorType_FILTER,
    OperatorType_JOIN,
    OperatorType_PROJECTION,
    OperatorType_SCAN
};
#endif