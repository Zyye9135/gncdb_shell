#ifndef CALC_STMT_H
#define CALC_STMT_H
#include "stmt.h"
#include "varArrayList.h"
typedef struct CalcStmt{
  StmtType type;
  varArrayList* expressions;  /* element type:<Expression*> */
}CalcStmt;

int CalcStmtConstruct(CalcSqlNode *calcSql, Stmt **stmt);
void CalcStmtDestroy(CalcStmt *calcStmt);
#endif





