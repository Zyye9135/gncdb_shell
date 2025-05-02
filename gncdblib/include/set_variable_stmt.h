#ifndef SET_VARIABLE_STMT_H
#define SET_VARIABLE_STMT_H
#include "stmt.h"
struct SetVariableSqlNode;
typedef struct SetVariableStmt
{
  StmtType            type;
  struct SetVariableSqlNode *setVariableNode;
} SetVariableStmt;

int  SetVariableStmtConstruct(struct SetVariableSqlNode *setVariable, Stmt **stmt);
void SetVariableStmtDestroy(SetVariableStmt *setVariableStmt);
#endif
