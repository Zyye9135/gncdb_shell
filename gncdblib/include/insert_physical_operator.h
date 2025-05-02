#ifndef INSERT_PHYSICAL_OPERATOR_H
#define INSERT_PHYSICAL_OPERATOR_H
#include "physical_operator.h"
typedef struct InsertPhysicalOperator{
    PhysicalOperatorType type;
    varArrayList* children;         // element type:<PhysicalOperator*>
    AbstractTuple* parentTuple;

    BtreeTable* table;
    varArrayList* valuelists;       // element type:<varArrayList>
}InsertPhysicalOperator;

int InsertPhysOperInit(InsertPhysicalOperator* insertPhysOper);
int InsertPhysOperOpen(InsertPhysicalOperator* insertPhysOper,SQLStageEvent* sqlEvent);
int InsertPhysOperNext(InsertPhysicalOperator* insertPhysOper,SQLStageEvent* sqlEvent );
int InsertPhysOperClose(InsertPhysicalOperator* insertPhysOper,SQLStageEvent* sqlEvent);

void InsertPhysOperDestroy(InsertPhysicalOperator* insertPhysOper);
void InsertPhysOperPointerDestroy(void* data);
InsertPhysicalOperator* InsertPhysOperMove(InsertPhysicalOperator** insertPhysOper);
#endif // INSERT_PHYSICAL_OPERATOR_H