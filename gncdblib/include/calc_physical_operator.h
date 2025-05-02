#ifndef CALC_PHYSICAL_OPERATOR_H
#define CALC_PHYSICAL_OPERATOR_H
#include "physical_operator.h"
typedef struct CalcPhysicalOperator
{
  PhysicalOperatorType type;
  varArrayList        *children;     // element type:<PhysicalOperator*>
  varArrayList        *expressions;  // element type:<Expression*>
} CalcPhysicalOperator;
void                  CalcPhysicalOperatorDestroy(CalcPhysicalOperator *calcPhysOper);
void                  CalcPhysicalOperatorPointerDestroy(void *data);
CalcPhysicalOperator *CalcPhysicalOperatorMove(CalcPhysicalOperator **calcPhysOper);
#endif  // CALC_PHYSICAL_OPERATOR_H