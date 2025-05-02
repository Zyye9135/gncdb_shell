#ifndef LOAD_DATA_STMT_H
#define LOAD_DATA_STMT_H
#include "btreepage.h"
#include "stmt.h"
struct LoadDataSqlNode;
typedef struct LoadDataStmt
{
  StmtType    type;
  BtreeTable *table;
  char       *filename;
} LoadDataStmt;
int  LoadDataStmtConstruct(GNCDB *db, struct LoadDataSqlNode *loadData, Stmt **stmt);
void LoadDataStmtDestroy(LoadDataStmt *loadDataStmt);
#endif