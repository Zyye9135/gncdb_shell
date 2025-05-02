#ifndef GROUPBY_STMT_H
#define GROUPBY_STMT_H
#include "stmt.h"
#include "varArrayList.h"
typedef struct GroupBySqlNode GroupBySqlNode;
typedef struct GroupByStmt{
  StmtType type;

  varArrayList* groupbyFields;          ///< element type:<FieldExpr*>
                                         ///< group by clause
  varArrayList* aggExprs;               ///< element type:<AggrFuncExpr*>
                                         ///< 聚集函数表达式
  varArrayList* fieldExprs;             ///< element type:<FieldExpr*>
                                         ///< 非聚集函数中的字段表达式,需要传递给下层的 order by 算子

}GroupByStmt;
int GroupByStmtConstructor(GNCDB *db, BtreeTable* defaultTable, HashMap* tables, varArrayList* groupbyNode, GroupByStmt** stmt, varArrayList* aggExprs, varArrayList* fieldExprs);
void GroupByStmtDestroy(GroupByStmt* groupbyStmt);
GroupByStmt* GroupByStmtMove(GroupByStmt** groupbyStmt);
#endif //GROUPBY_STMT_H