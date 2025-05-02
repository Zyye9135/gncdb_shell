#ifndef OPTIMIZE_STAGE_H
#define OPTIMIZE_STAGE_H
typedef struct LogicalOperator LogicalOperator;
#include "sql_event.h"
int OptimizeStageHandleRequest(SQLStageEvent* sqlEvent);
int ruleBasedOptimization(LogicalOperator* logicalOperator);
#endif // OPTIMIZE_STAGE_H