#ifndef CREATE_TABLE_STMT_H
#define CREATE_TABLE_STMT_H
#include "stmt.h"
struct CreateTableSqlNode;
struct SelectSqlNode;
typedef struct CreateTableStmt
{
  StmtType      type;
  char         *tableName;
  varArrayList *attrInfos;  // element type: AttrInfoSqlNode*
  Stmt         *selectStmt;
} CreateTableStmt;
CreateTableStmt *CreateTableStmtCreate();
int              CreateTableStmtConstruct(
                 SQLStageEvent *sqlEvent, struct CreateTableSqlNode *createTable, Stmt **stmt, struct SelectSqlNode *select);
void CreateTableStmtDestroy(CreateTableStmt *createTableStmt);
#endif