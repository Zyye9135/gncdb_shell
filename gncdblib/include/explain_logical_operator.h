#ifndef EXPLAIN_LOGICAL_OPERATOR_H
#define EXPLAIN_LOGICAL_OPERATOR_H
#include "logical_operator.h"
typedef struct ExplainLogicalOperator{
    LogicalOperatorType type;
    varArrayList* children;       ///< 子算子
                                  ///< element type:<LogicalOperator*>
    varArrayList* expressions;    ///< 表达式，比如select中的列，where中的谓词等等，都可以使用表达式来表示
                                  ///< element type:<Expression*>
    
}ExplainLogicalOperator;

#endif // EXPLAIN_LOGICAL_OPERATOR_H