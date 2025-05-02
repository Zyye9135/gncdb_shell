#ifndef DROP_TABLE_STMT_H
#define DROP_TABLE_STMT_H
#include "stmt.h"
typedef struct DropTableStmt{
  StmtType type;
  char* tableName;
  int ifExist; 
}DropTableStmt;

int DropTableStmtConstruct(GNCDB* db, DropTableSqlNode* dropTable, Stmt **stmt);
void DropTableStmtDestroy(DropTableStmt* dropTableStmt);
#endif // DROP_TABLE_STMT_H