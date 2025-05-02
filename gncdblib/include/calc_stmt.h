#ifndef CALC_STMT_H
#define CALC_STMT_H
#include "stmt.h"
#include "vararraylist.h"
struct CalcSqlNode;
typedef struct CalcStmt
{
  StmtType      type;
  varArrayList *expressions; /* element type:<Expression*> */
} CalcStmt;
CalcStmt *CalcStmtCreate();
int       CalcStmtConstruct(struct CalcSqlNode *calcSql, Stmt **stmt);
void      CalcStmtDestroy(CalcStmt *calcStmt);
#endif
