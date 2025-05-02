#ifndef LIMIT_PHYSICAL_OPERATOR_H
#define LIMIT_PHYSICAL_OPERATOR_H
#include "physical_operator.h"
typedef struct LimitPhysicalOperator
{
  PhysicalOperatorType type;
  varArrayList        *children;  // element type:<PhysicalOperator*>
  AbstractTuple       *parentTuple;
  int                  limit;
  int                  offset;
  int                  currentOffset;
} LimitPhysicalOperator;
int                    LimitPhysOperInit(LimitPhysicalOperator *limitPhysOper, PhysicalOperatorType type);
int                    LimitPhysOperOpen(LimitPhysicalOperator *limitPhysOper, SQLStageEvent *sqlEvent);
int                    LimitPhysOperNext(LimitPhysicalOperator *limitPhysOper, SQLStageEvent *sqlEvent);
int                    LimitPhysOperClose(LimitPhysicalOperator *limitPhysOper, SQLStageEvent *sqlEvent);
AbstractTuple         *LimitPhysOperGetCurrentTuple(LimitPhysicalOperator *limitPhysOper);
void                   LimitPhysOperDestroy(LimitPhysicalOperator *limitPhysOper);
void                   LimitPhysOperDestroyPointerDestroy(void *data);
LimitPhysicalOperator *LimitPhysOperDestroyMove(LimitPhysicalOperator **limitPhysOper);
#endif  // LIMIT_PHYSICAL_OPERATOR_H