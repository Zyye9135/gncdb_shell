#ifndef _LOGGER_H_
#define _LOGGER_H_

#include "stdbool.h"
#include "btreepage.h"
#include "gncdb.h"
#include "lockmanager.h"


typedef struct BEGINLOG {
    char type;
    int LSN;
    int preLSN;
    int tid;
    int offset;
    int size;
}BEGINLOG;

typedef struct ROLLBACKLOG {
    char type;
    int LSN;
    int preLSN;
    int tid;
    int offset;
    int size;
}ROLLBACKLOG;

typedef struct COMMITLOG {
    char type;
    int LSN;
    int preLSN;
    int tid;
    int offset;
    int size;
}COMMITLOG;

typedef struct UPDATELOG {
    char type;
    int pageId;
    int LSN;
    int preLSN;
    int tid;
    int offset;
    //BYTE* oldData;
    BYTE* newData;
    int size;
}UPDATELOG;

typedef struct CHECKLOG {
    char type;
    int LSN;
    char status;
    int size;
}CHECKLOG;

typedef struct Logger
{
    int tid;                    /* 事务id */
    int LSN;                    /* 当前日志条数 */
    int offset;                 /* 记录日志文件当前末尾的偏移量 */ 
    HashMap* Toffset;           /* TODO 无使用价值，待删除 */
    char logFileName[64]; 
    FILE* logFile;
    ReadWriteLock latch;
}Logger;

Logger* loggerConstruct(struct GNCDB* db);

void loggerDestroy(struct Logger** logger);

int loggerBegin(struct Logger* logger, struct GNCDB* db, struct Transaction* tx);

int loggerRollback(struct Logger* logger, struct Transaction* tx, struct GNCDB* db);

int loggerCommit(struct Logger* logger, struct Transaction* tx, struct GNCDB* db);

int loggerReplace(struct Logger* logger, struct Transaction* tx, int pageId, struct GNCDB* db);

int loggerRecover(struct Logger* logger, struct GNCDB* db);

int loggerCheckpoint(struct Logger* logger, char sta);

int loggerDelete(struct Logger* logger);

int loggerDeleteRecover(struct Logger* logger);

#endif
