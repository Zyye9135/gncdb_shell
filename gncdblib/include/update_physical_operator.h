#ifndef UPDATE_PHYSICAL_OPERATOR_H
#define UPDATE_PHYSICAL_OPERATOR_H
#include "physical_operator.h"
typedef struct UpdatePhysicalOperator
{
  PhysicalOperatorType type;
  varArrayList        *children;  // element type:<PhysicalOperator*>
  AbstractTuple       *parentTuple;
  varArrayList        *updateValues;      // element type:<Value>
  varArrayList        *updateFieldNames;  // element type:<char*>
} UpdatePhysicalOperator;
void                    UpdatePhysOperInit(UpdatePhysicalOperator *updatePhysicalOperator);
int                     UpdatePhysOperOpen(UpdatePhysicalOperator *updatePhysicalOperator, SQLStageEvent *sqlEvent);
int                     UpdatePhysOperNext(UpdatePhysicalOperator *updatePhysicalOperator, SQLStageEvent *sqlEvent);
int                     UpdatePhysOperClose(UpdatePhysicalOperator *updatePhysicalOperator, SQLStageEvent *sqlEvent);
AbstractTuple          *UpdatePhysOperGetCurrentTuple(UpdatePhysicalOperator *updatePhysicalOperator);
void                    UpdatePhysOperDestroy(UpdatePhysicalOperator *updatePhysicalOperator);
void                    UpdatePhysOperPointerDestroy(void *data);
UpdatePhysicalOperator *UpdatePhysicalOperatorMove(UpdatePhysicalOperator **updatePhysicalOperator);
#endif  // UPDATE_PHYSICAL_OPERATOR_H