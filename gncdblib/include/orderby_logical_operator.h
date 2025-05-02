#ifndef ORDERBY_LOGICAL_OPERATOR_H
#define ORDERBY_LOGICAL_OPERATOR_H
#include "logical_operator.h"

typedef struct OrderByLogicalOperator
{
  LogicalOperatorType type;
  varArrayList       *children;  ///< 子算子element type:<LogicalOperator*>
  varArrayList       *expressions;  ///< 表达式，比如select中的列，where中的谓词等等，都可以使用表达式来表示element
                              ///< type:<Expression*>
                              ///< 表达式能是一个常量，也可以是一个函数，也可以是一个列，也可以是一个子查询等等

  varArrayList *orderbyUnits;  ///< 排序的列
                               ///< element type:<OrderByUnit*>

  varArrayList *exprs;  ///< 在 create order by stmt 之前提取 select clause 后的 field_expr (非agg_expr 中的)和 agg_expr
                        ///< element type:<Expression*>
} OrderByLogicalOperator;
void                    OrderByLogiOperDestroy(OrderByLogicalOperator *orderbyLogiOper);
void                    OrderByLogiOperPointerDestroy(void *data);
OrderByLogicalOperator *OrderByLogiOperMove(OrderByLogicalOperator **orderbyLogiOper);
#endif  // ORDERBY_LOGICAL_OPERATOR_H