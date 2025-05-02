#ifndef DESC_TABLE_STMT_H
#define DESC_TABLE_STMT_H
#include "stmt.h"
struct DescTableSqlNode;
typedef struct DescTableStmt
{
  StmtType type;
  char    *tableName;
} DescTableStmt;

int  DescTableStmtConstruct(GNCDB *db, struct DescTableSqlNode *descTable, Stmt **stmt);
void DescTableStmtDestroy(DescTableStmt *descTableStmt);
#endif