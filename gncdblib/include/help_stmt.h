#ifndef HELP_STMT_H
#define HELP_STMT_H
#include "stmt.h"

typedef struct HelpStmt
{
  StmtType type;
} HelpStmt;

int  HelpStmtConstruct(Stmt **stmt);
void HelpStmtDestroy(HelpStmt *helpStmt);

#endif