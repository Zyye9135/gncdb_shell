#ifndef SET_VARIABLE_STMT_H
#define SET_VARIABLE_STMT_H
#include "stmt.h"
typedef struct SetVariableStmt{
  StmtType type;
  SetVariableSqlNode* setVariableNode;
}SetVariableStmt;

int SetVariableStmtConstruct(SetVariableSqlNode *setVariable, Stmt** stmt);

void SetVariableStmtDestroy(SetVariableStmt* setVariableStmt);
#endif
