#ifndef SELECT_STMT_H
#define SELECT_STMT_H
#include "stmt.h"
#include "filter_stmt.h"
#include "varArrayList.h"
#include "groupby_stmt.h"
#include "orderby_stmt.h"
#include "limit_stmt.h"
#include <stdarg.h>
typedef struct JoinTables{
  StmtType type;
  varArrayList* tables; // element type:<BtreeTable*>
  varArrayList* onConds; // element type:<FilterStmt*>
}JoinTables;
void JoinTablesDestroy(JoinTables* joinTables);
void JoinTablesPointerDestroy(void* data);
JoinTables* JoinTablesMove(JoinTables** joinTables);

typedef struct SelectStmt{
  StmtType type;
  varArrayList* queryFields; // element type:<Expression*>
  varArrayList* joinTables;// element type:<JoinTables>
  FilterStmt* filterStmt;
  GroupByStmt * groupbyStmt;
  OrderByStmt * orderbyStmt;
  FilterStmt *havingStmt;
  LimitStmt* limitStmt;
  int isDistinct;
}SelectStmt;

int SelectStmtConstruct(SQLStageEvent* sqlEvent, Stmt ** stmt, HashMap* parentTableMap);
void SelectStmtDestroy(SelectStmt* stmt);
#endif