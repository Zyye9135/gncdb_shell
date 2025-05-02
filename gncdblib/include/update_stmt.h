#ifndef UPDATE_STMT_H
#define UPDATE_STMT_H
#include "sql_event.h"
#include "stmt.h"
#include "filter_stmt.h"
typedef struct UpdateStmt
{
  StmtType      type;
  BtreeTable   *table;
  varArrayList *updateFieldNames;
  varArrayList *updateValues;
  FilterStmt   *filterStmt;
  int           valueCount;
} UpdateStmt;
UpdateStmt *UpdateStmtCreate();
int         UpdateStmtConstruct(SQLStageEvent *sqlEvent, Stmt **stmt);
void        UpdateStmtDestroy(UpdateStmt *updateStmt);
UpdateStmt *UpdateStmtMove(UpdateStmt **updateStmt);
#endif