/*
 * @Descripttion: 
 * @version: 
 * @Author: Alan
 * @Date: 2023-01-30 09:19:38
 * @LastEditors: Alan
 * @LastEditTime: 2023-02-03 13:54:23
 */
#ifndef _GNCDB_H_
#define _GNCDB_H_

#include "catalog.h"
// #include "pagepool.h"
// #include "tranmanager.h"
#include "parse_defs.h"
#include "varArrayList.h"
typedef struct CreateTableStmt CreateTableStmt;
typedef enum FieldType FieldType;
struct PagePool;
struct Catalog;
struct TransactionManager;
struct ReadWriteLock;

typedef struct GNCDB
{
    char *fileName;                             /* 文件名称 */
    FILE *dbFile;                               /* 文件句柄 */
    BYTE dbOverview[BYTES32 +1];                /* 数据库概述 限长32*/
    BYTE dbVersion[BYTES32 +1];                 /* 数据库版本 限长32*/
    //注：文件中1号page存配置信息，2、3号存master，schema表
    int totalPageNum;                           /* 数据库总页数 */ 
    int firstFreePid;                           /* 第一个空页的页号 */
    //int totalFreePageNum;                       /* 总的空页数 */
    struct PagePool *pagePool;
    struct Catalog *catalog;
    struct TransactionManager* transactionManager;
    struct DBLog* dbLog;
    struct ReadWriteLock latch;
    struct ReadWriteLock latchSQLParse;
}GNCDB;
int dbInstanceReadFileHeader(struct GNCDB* db);
/* 外部接口*/
int GNCDB_open(struct GNCDB **db, char *fileName);
int GNCDB_select(GNCDB* db, CallBack2 callback, int* affectedRows,void* data, int tableNum, int columnNum, int filterNum, ...);
int GNCDB_createTable(struct GNCDB* db, char* tableName, int columnNum, ...);
int GNCDB_dropTable(GNCDB* db, char* tableName);
int GNCDB_insert(struct GNCDB* db, int* affectedRows, char* tableName, ...);
int GNCDB_delete(struct GNCDB* db, int* affectedRows, char* tableName, int filterNum, ...);
int GNCDB_update(struct GNCDB* db, int* affectedRows, char* tableName, int setNum, int filterNum, ...);
/* 这里的buf由用户分配 */
int GNCDB_setBlob(struct GNCDB* db, char* tableName, int columnNum, BYTE* buf, int size, int keyValueNum, ...);
int GNCDB_getBlob(struct GNCDB* db, char* tableName, int columnNum, BYTE* buf, int size, int keyValueNum, ...);
int GNCDB_deleteBlob(struct GNCDB* db, char* tableName, int columnNum, int keyValueNum, ...);

int GNCDB_setTableParam(struct GNCDB* db, char* tableName);

int GNCDB_close(struct GNCDB** db);

////////////////////////////////SQL///////////////////////////////////////
/* R树索引内容 */
int GNCDB_createRtreeIndex(struct GNCDB* db, char* tableName, char* indexName, int v_si32_dim, ...);

int GNCDB_dropRtreeTable(GNCDB* db, char* tableName);

int GNCDB_selectRtreeIndex(GNCDB* db, CallBack callback, int* affectedRows, int tableNum, int columnNum, int filterNum, ...);

#endif