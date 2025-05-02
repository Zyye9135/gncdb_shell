#ifndef DROP_TABLE_STMT_H
#define DROP_TABLE_STMT_H
#include "sql_event.h"
#include "stmt.h"
typedef struct DropTableStmt
{
  StmtType type;
  char    *tableName;
  int      ifExist;
} DropTableStmt;

int  DropTableStmtConstruct(SQLStageEvent *sqlEvent, Stmt **stmt);
void DropTableStmtDestroy(DropTableStmt *dropTableStmt);
#endif  // DROP_TABLE_STMT_H