#ifndef CALC_LOGICAL_OPERATOR_H
#define CALC_LOGICAL_OPERATOR_H
#include "logical_operator.h"
typedef struct CalcLogicalOperator {
  LogicalOperatorType type;
  varArrayList *children;     ///< 子算子/* element type:<LogicalOperator*>
  varArrayList *expressions;  ///< 表达式，比如select中的列，where中的谓词等等，都可以使用表达式来表示
} CalcLogicalOperator;

void CalcLogicalOperatorDestroy(CalcLogicalOperator *calcLogiOper);
void CalcLogicalOperatorPointerDestroy(void *data);

CalcLogicalOperator* CalcLogicalOperatorMove(CalcLogicalOperator **calcLogiOper);
#endif // CALC_LOGICAL_OPERATOR_H