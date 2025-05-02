#ifndef LIMIT_LOGICAL_OPERATOR_H
#define LIMIT_LOGICAL_OPERATOR_H
#include "logical_operator.h"
typedef struct LimitLogicalOperator{
    LogicalOperatorType type;
    varArrayList* children;       ///< 子算子element type:<LogicalOperator*>
    varArrayList* expressions;    ///< 表达式，比如select中的列，where中的谓词等等，都可以使用表达式来表示element type:<Expression*>
                                  ///< 表达式能是一个常量，也可以是一个函数，也可以是一个列，也可以是一个子查询等等
    int offset;                   ///< 偏移量
    int limit;                    ///< 限制返回的行数
}LimitLogicalOperator;

void LimitLogiOperDestroy(LimitLogicalOperator* limitLogiOper);
void LimitLogiOperPointerDestroy(void* data);
LimitLogicalOperator* LimitLogiOperMove(LimitLogicalOperator** limitLogiOper);

#endif // LIMIT_LOGICAL_OPERATOR_H