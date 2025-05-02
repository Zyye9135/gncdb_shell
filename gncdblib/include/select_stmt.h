#ifndef SELECT_STMT_H
#define SELECT_STMT_H
#include "stmt.h"
#include "filter_stmt.h"
#include "vararraylist.h"
#include "groupby_stmt.h"
#include "orderby_stmt.h"
#include "limit_stmt.h"
#include <stdarg.h>
/**
 * @brief 表示一串（inner）连接的表,例如  t1 inner join t2 on t1.a = t2.b inner join t3 on t2.c = t3.d
 * 第一个onConds元素默认为空，第二个开始每个元素表示对应的连接条件，对应上面的例子，第二个元素表示t1.a =
 * t2.b，第三个元素表示t2.c = t3.d
 *
 */
typedef struct JoinTables
{
  StmtType      type;
  varArrayList *tables;   // element type:<BtreeTable*>
  varArrayList *onConds;  // element type:<joinNode*>
} JoinTables;
JoinTables *JoinTablesCreate();
void        JoinTablesDestroy(JoinTables *joinTables);
void        JoinTablesPointerDestroy(void *data);
JoinTables *JoinTablesMove(JoinTables **joinTables);

typedef struct SelectStmt
{
  StmtType      type;
  varArrayList *queryFields;
  varArrayList *joinTables;
  FilterStmt   *filterStmt;
  GroupByStmt  *groupbyStmt;
  OrderByStmt  *orderbyStmt;
  FilterStmt   *havingStmt;
  LimitStmt    *limitStmt;
  int           isDistinct;
} SelectStmt;
SelectStmt *SelectStmtCreate();
int         SelectStmtConstruct(SQLStageEvent *sqlEvent, Stmt **stmt, HashMap *parentTableMap);
void        SelectStmtDestroy(SelectStmt *stmt);
#endif