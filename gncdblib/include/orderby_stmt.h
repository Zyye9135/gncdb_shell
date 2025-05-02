#ifndef ORDERBY_STMT_H
#define ORDERBY_STMT_H
#include "parse_defs.h"
#include "stmt.h"
typedef struct OrderByUnit{
  bool isAsc;
  Expression* expr;
}OrderByUnit;

void OrderByUnitDestroy(OrderByUnit* unit);
void OrderByUnitPointerDestroy(void* data);
OrderByUnit* OrderByUnitMove(OrderByUnit** unit);

typedef struct OrderByStmt{
  StmtType type;
  varArrayList* orderByUnits;     ///< list of OrderByUnit
                                    ///< element type：<OrderByUnit*>
  varArrayList* exprs;              ///< list of Expression
                                    ///< element type：<Expression*>
}OrderByStmt;
int OrderByStmtConstructor(GNCDB*db, BtreeTable* defaultTable, HashMap* tables, varArrayList* orderbySqlNodes ,OrderByStmt** stmt, varArrayList* exprs, HashMap* aggrAliasSet);
void OrderByStmtDestroy(OrderByStmt* stmt);
#endif // ORDERBY_STMT_H