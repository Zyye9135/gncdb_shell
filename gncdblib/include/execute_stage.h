#ifndef EXECUTE_STAGE_H
#define EXECUTE_STAGE_H
#include "sql_event.h"
int ExecuteStageHandleRequest(SQLStageEvent* sqlEvent);
// int ExecuteStageHandleRequestWithPhysOper(SQLStageEvent* sqlEvent);
int getTupleSchemaAndCount(SQLStageEvent* sqlEvent,char***tupleSchema, int* fieldCount);
int ExecutePhysicalPlan(SQLStageEvent* sqlEvent);
int ExecutePhysicalPlanByStep(SQLStageEvent* sqlEvent);
void PhysicalPlanDestroy(PhysicalOperator* physOper);
int PlanDestroy(SQLStageEvent *sqlEvent);
#endif // EXECUTE_STAGE_H