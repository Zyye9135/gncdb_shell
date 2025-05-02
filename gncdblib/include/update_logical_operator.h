#ifndef UPDATE_LOGICAL_OPERATOR_H
#define UPDATE_LOGICAL_OPERATOR_H
#include "logical_operator.h"
#include "varArrayList.h"

typedef struct UpdateLogicalOperator{
    LogicalOperatorType type;
    varArrayList* children;       ///< 子算子element type:<LogicalOperator*>
    varArrayList* expressions;    ///< 表达式，比如select中的列，where中的谓词等等，都可以使用表达式来表示element type:<Expression*>
                                    ///< 表达式能是一个常量，也可以是一个函数，也可以是一个列，也可以是一个子查询等等
    varArrayList* updateFieldNames;           ///< 更新的字段名
    varArrayList* updateValues;           ///< 更新的值
}UpdateLogicalOperator;


void UpdateLogiOperDestroy(UpdateLogicalOperator* updateLogiOper);
void UpdateLogiOperPointerDestroy(void* data);
UpdateLogicalOperator* UpdateLogiOperMove(UpdateLogicalOperator** updateLogiOper);

#endif // UPDATE_LOGICAL_OPERATOR_H