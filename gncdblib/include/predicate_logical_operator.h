#ifndef PREDICATE_LOGICAL_OPERATOR_H
#define PREDICATE_LOGICAL_OPERATOR_H
#include "logical_operator.h"
typedef struct PredicateLogicalOperator{
    LogicalOperatorType type;
    varArrayList* children;       ///< 子算子element type:<LogicalOperator*>
    varArrayList* expressions;    ///< 表达式，比如select中的列，where中的谓词等等，都可以使用表达式来表示element type:<Expression*>
                                    ///< 表达式能是一个常量，也可以是一个函数，也可以是一个列，也可以是一个子查询等等
           
}PredicateLogicalOperator;


void PredicateLogiOperDestroy(PredicateLogicalOperator* predicateLogiOper);
void PredicateLogiOperPointerDestroy(void* data);
PredicateLogicalOperator* PredicateLogiOperMove(PredicateLogicalOperator** predicateLogiOper);
#endif  // PREDICATE_LOGICAL_OPERATOR_H