#ifndef DESC_TABLE_STMT_H
#define DESC_TABLE_STMT_H
#include "stmt.h"
typedef struct DescTableStmt{
  StmtType type;
  char* tableName;
}DescTableStmt;

int DescTableStmtConstruct(GNCDB* db, DescTableSqlNode* descTable, Stmt ** stmt);
void DescTableStmtDestroy(DescTableStmt* descTableStmt);
#endif