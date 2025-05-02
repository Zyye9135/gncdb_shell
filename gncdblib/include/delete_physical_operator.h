#ifndef DELETE_PHYSICAL_OPERATOR_H
#define DELETE_PHYSICAL_OPERATOR_H
#include "btreeCursor.h"
#include "physical_operator.h"
typedef struct DeletePhysicalOperator{
    PhysicalOperatorType type;
    varArrayList* children;      // element type:<PhysicalOperator*>
    AbstractTuple* parentTuple;
    
    BtreeTable* table;
    Transaction* txn;
    BtreeCursor* cursor;

}DeletePhysicalOperator;

int DeletePhysOperInit(DeletePhysicalOperator* deletePhysOper, PhysicalOperatorType type);
int DeletePhysOperOpen(DeletePhysicalOperator*deletePhysOper,SQLStageEvent* sqlEvent);
int DeletePhysOperNext(DeletePhysicalOperator* deletePhysOper,SQLStageEvent* sqlEvent);
int DeletePhysOperClose(DeletePhysicalOperator* deletePhysOper,SQLStageEvent* sqlEvent);
AbstractTuple* DeletePhysOperGetCurrentTuple(DeletePhysicalOperator* deletePhysOper);

void DeletePhysOperDestroy(DeletePhysicalOperator* deletePhysOper);
void DeletePhysOperPointerDestory(void* data);
DeletePhysicalOperator* DeletePhysOperMove(DeletePhysicalOperator** deletePhysOper);

#endif // DELETE_PHYSICAL_OPERATOR_H
