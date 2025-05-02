#ifndef DB_H
#define DB_H
#include "sql_event.h"
int db_open(char *fileName, GNCDB** db);
int db_exec(GNCDB* db, const char *sql, CallBack2 callback, void* data, char** errmsg);
int db_close(GNCDB** db);

int txnExecuteSQL(SQLStageEvent* sqlEvent, const char *sql);
int txnExecuteSQLStep(SQLStageEvent* sqlEvent, const char *sql);

int executeSQLFile(GNCDB* db, char* fileName);
#endif