#ifndef EXPLAIN_STMT_H
#define EXPLAIN_STMT_H
#include "stmt.h"

typedef struct ExplainStmt
{
  StmtType type;
  Stmt* childStmt;
}ExplainStmt;
int ExplainStmtConstruct(SQLStageEvent* sqlEvent, Stmt** stmt);

void ExplainStmtDestroy(ExplainStmt* explainStmt);
#endif