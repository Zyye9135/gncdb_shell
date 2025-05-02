#ifndef FILTER_STMT_H
#define FILTER_STMT_H
#include "btreetable.h"
#include "parse_defs.h"
typedef struct SQLStageEvent SQLStageEvent;
typedef struct FilterStmt {
  Expression *condition; 
} FilterStmt;
int FilterStmtConstruct(SQLStageEvent* sqlEvent, BtreeTable* defaultTable,varArrayList* tables, HashMap* tableMap, Expression *condition,  FilterStmt** stmt);
void FilterStmtDestroy(FilterStmt *stmt);
void FilterStmtPointerDestroy(void* data);
FilterStmt* FilterStmtMove(FilterStmt** filterStmt);
#endif // FILTER_STMT_H