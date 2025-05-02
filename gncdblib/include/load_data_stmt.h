#ifndef LOAD_DATA_STMT_H
#define LOAD_DATA_STMT_H
#include "btreepage.h"
#include "stmt.h"
typedef struct LoadDataStmt{
  StmtType type;
  BtreeTable* table;
  char* filename;
}LoadDataStmt;
int LoadDataStmtConstruct(GNCDB* db, LoadDataSqlNode* loadData, Stmt **stmt);
void LoadDataStmtDestroy(LoadDataStmt* loadDataStmt);
#endif