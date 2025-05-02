#ifndef DELETE_STMT_H
#define DELETE_STMT_H
#include "stmt.h"
#include "filter_stmt.h"
typedef struct DeleteStmt
{
  StmtType    type;
  BtreeTable *table;
  FilterStmt *filterStmt;
} DeleteStmt;

int DeleteStmtConstruct(SQLStageEvent *sqlEvent, DeleteSqlNode *deleteSql, Stmt **stmt);

void DeleteStmtDestroy(DeleteStmt *deleteStmt);
#endif  // DELETE_STMT_H