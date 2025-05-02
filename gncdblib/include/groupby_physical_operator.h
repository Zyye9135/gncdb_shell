#ifndef GROUPBY_PHYSICAL_OPERATOR_H
#define GROUPBY_PHYSICAL_OPERATOR_H
#include "physical_operator.h"
typedef struct GroupTuple GroupTuple;
typedef struct GroupByPhysicalOperator{
  PhysicalOperatorType type;
  varArrayList* children;       // element type :<PhysicalOperator*>
  AbstractTuple* parentTuple;

  bool isFirst;
  bool isNewGroup;
  bool isRecordEof;
  varArrayList* groupbyFields; // element type :<FieldExpr*>
  varArrayList* preValues;     // element type :<Value>
  GroupTuple tuple;
}GroupByPhysicalOperator;
int GroupByPhysOperInit(GroupByPhysicalOperator* groupbyPhysOper, PhysicalOperatorType type);
void GroupByGetParmsValues(GroupByPhysicalOperator* groupbyPhysOper, varArrayList*groupbyFields, varArrayList* aggExprs, varArrayList*fieldExprs);
int GroupByPhysOperOpen(GroupByPhysicalOperator*groupbyPhysOper,SQLStageEvent* sqlEvent);
int GroupByPhysOperNext(GroupByPhysicalOperator* groupbyPhysOper,SQLStageEvent* sqlEvent);
int GroupByPhysOperClose(GroupByPhysicalOperator* groupbyPhysOper,SQLStageEvent* sqlEvent);
AbstractTuple* GroupByPhysOperGetCurrentTuple(GroupByPhysicalOperator* groupbyPhysOper);
void GroupByPhysOperDestroy(GroupByPhysicalOperator* groupbyPhysOper);
void GroupByPhysOperPointerDestory(void* data);
GroupByPhysicalOperator* GroupByPhysOperMove(GroupByPhysicalOperator** groupbyPhysOper);
#endif // GROUPBY_PHYSICAL_OPERATOR_H