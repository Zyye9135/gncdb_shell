#ifndef ORDERBY_PHYSICAL_OPERATOR_H
#define ORDERBY_PHYSICAL_OPERATOR_H
#include "physical_operator.h"
typedef struct SplicedTuple SplicedTuple;
typedef struct OrderByPhysicalOperator{
  PhysicalOperatorType type;
  varArrayList* children;         // element type:<PhysicalOperator*>
  AbstractTuple* parentTuple;


  varArrayList* orderbyUnits;    ///<排序列
                                  ///< element type:<OrderByUnit *>
  varArrayList* values;           ///< element type:<varArrayList* element type:Value>
  SplicedTuple tuple;             
  varArrayList* orderedIndex;    ///< element type:<int>
  int iter;                        
}OrderByPhysicalOperator;

// 用于比较的结构体
typedef struct {
  varArrayList* cells; // 用于排序的values
  int index;          // 用于排序的index
} CmpPair;
int OrderByPhysOperInit(OrderByPhysicalOperator* orderbyPhysOper, PhysicalOperatorType type);
int OrderByPhysOperOpen(OrderByPhysicalOperator* orderbyPhysOper, SQLStageEvent* sqlEvent);
int OrderByPhysOperNext(OrderByPhysicalOperator* orderbyPhysOper, SQLStageEvent* sqlEvent);
int OrderByPhysOperClose(OrderByPhysicalOperator* orderbyPhysOper,SQLStageEvent* sqlEvent);

AbstractTuple* OrderByPhysOperGetCurrentTuple(OrderByPhysicalOperator* orderbyPhysOper);

void OrderByPhysOperDestroy(OrderByPhysicalOperator* orderbyPhysOper);
void OrderByPhysOperPointerDestroy(void* data);
OrderByPhysicalOperator* OrderByPhysOperMove(OrderByPhysicalOperator** orderbyPhysOper);

#endif // ORDERBY_PHYSICAL_OPERATOR_H