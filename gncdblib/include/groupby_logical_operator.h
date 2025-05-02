#ifndef GROUPBY_LOGICAL_OPERATOR_H
#define GROUPBY_LOGICAL_OPERATOR_H
#include "logical_operator.h"
typedef struct GroupByLogicalOperator{
    LogicalOperatorType type;
    varArrayList* children;       ///< 子算子element type:<LogicalOperator*>
    varArrayList* expressions;    ///< 表达式，比如select中的列，where中的谓词等等，都可以使用表达式来表示
                                    ///< 表达式能是一个常量，也可以是一个函数，也可以是一个列，也可以是一个子查询等等


    varArrayList* groupbyFields; ///< 分组字段，比如select a, b, sum(c) from t group by a, b;中的a, b
                                  ///< element type:<FieldExpr*>，FieldExpr是一个字段表达式，包含字段名和表名
    varArrayList* aggExprs;      ///< 聚合函数，比如select a, b, sum(c) from t group by a, b;中的sum(c)
                                  ///< element type:<AggrFuncExpr*>，AggrFuncExpr是一个聚合函数表达式，包含函数名和字段表达式
    varArrayList* fieldExprs;    ///< select中的非聚合列，比如select a, b, sum(c) from t group by a, b;中的a, b
                                  ///< element type:<FieldExpr*>，FieldExpr是一个字段表达式，包含字段名和表名
}GroupByLogicalOperator;

void GroupByLogiOperDestroy(GroupByLogicalOperator* groupbyLogiOper);
void GroupByLogiOperPointerDestroy(void* data);
GroupByLogicalOperator* GroupByLogiOperMove(GroupByLogicalOperator** groupbyLogiOper);
#endif // GROUPBY_LOGICAL_OPERATOR_H

