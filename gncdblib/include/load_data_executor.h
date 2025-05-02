#ifndef LOAD_DATA_EXECUTOR_H
#define LOAD_DATA_EXECUTOR_H
#include "sql_event.h"
int LoadDataExecute(SQLStageEvent *sqlEvent);
int loadData(SQLStageEvent *sqlEvent, BtreeTable *table, const char *fileName);
#endif  // LOAD_DATA_EXECUTOR_H