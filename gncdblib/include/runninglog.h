/*
* @ProjectName: dbLogger.h
*
* @Author: wangjq
* @Createtime: 2023-8-17  15:30
* @LastEditor: wangjq
* @LastEditTime:
*/

#ifndef _DBLOG_H_
#define _DBLOG_H_

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include<time.h>
#include<sys/timeb.h>

struct GNCDB;

typedef struct DBLog
{
    char dbName[16];
    char logFileName[32];          /* 日志格式：DBLog_数据库名.dat */
    FILE* logFile;
    //pthread_mutex_t latch;      /* 需要锁日志？ */
}DBLog;

DBLog* DBLogConstruct(struct GNCDB* db);

void DBLoggerPrint(int logType, char* logStr, const char* fileName, const char* func, const int rowNum);

void DBLoggerDestory(DBLog** dbLog);

#endif
