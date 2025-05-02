#ifndef SHOW_TABLES_STMT_H
#define SHOW_TABLES_STMT_H
#include "gncdb.h"
#include "stmt.h"
typedef struct ShowTablesStmt
{
  StmtType type;
} ShowTablesStmt;

int  ShowTablesStmtConstruct(GNCDB *db, Stmt **stmt);
void ShowTablesStmtDestroy(ShowTablesStmt *showTablesStmt);
#endif