#ifndef EXIT_STMT_H
#define EXIT_STMT_H
#include "stmt.h"
typedef struct ExitStmt
{
  StmtType type;
} ExitStmt;

int  ExitStmtConstruct(Stmt **stmt);
void ExitStmtDestroy(ExitStmt *exitStmt);
#endif
