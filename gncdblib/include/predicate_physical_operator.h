#ifndef PREDICATE_PHSICAL_OPERATOR_H
#define PREDICATE_PHSICAL_OPERATOR_H
#include "physical_operator.h"
typedef struct PredicatePhysicalOperator{
  PhysicalOperatorType type;
  varArrayList* children;// element type:<PhysicalOperator*>
  AbstractTuple* parentTuple;

  Expression* expression;
  // AbstractTuple* tuple;
}PredicatePhysicalOperator;


int PredicatePhysOperInit(PredicatePhysicalOperator* predicatePhysOper, PhysicalOperatorType type);
int PredicatePhysOperOpen(PredicatePhysicalOperator* predicatePhysOper,SQLStageEvent* sqlEvent);
int PredicatePhysOperNext(PredicatePhysicalOperator* predicatePhysOper,SQLStageEvent* sqlEvent);
int PredicatePhysOperClose(PredicatePhysicalOperator* predicatePhysOper,SQLStageEvent* sqlEvent);

BtreeCursor* PredicatePhysOperGetScanCursor(PredicatePhysicalOperator* predicatePhysOper);
AbstractTuple* PredicatePhysOperGetCurrentTuple(PredicatePhysicalOperator* predicatePhysOper);

void PredicatePhysOperDestroy(PredicatePhysicalOperator* predicatePhysOper);
void PredicatePhysOperPointerDestroy(void* data);
PredicatePhysicalOperator* PredicatePhysOperMove(PredicatePhysicalOperator** predicatePhysOper);

#endif // PREDICATE_PHSICAL_OPERATOR_H