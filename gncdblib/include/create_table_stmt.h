#ifndef CREATE_TABLE_STMT_H
#define CREATE_TABLE_STMT_H
#include "stmt.h"
typedef struct CreateTableStmt{
  StmtType type;
  char* tableName;
  varArrayList* attrInfos; // element type: AttrInfoSqlNode*
  Stmt* selectStmt;
}CreateTableStmt;

int CreateTableStmtConstruct(SQLStageEvent *sqlEvent, CreateTableSqlNode* createTable, Stmt **stmt, SelectSqlNode* select);
void CreateTableStmtDestroy(CreateTableStmt* createTableStmt);

#endif