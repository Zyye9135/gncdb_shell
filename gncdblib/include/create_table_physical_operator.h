#ifndef CREATE_TABLE_PHYSICAL_OPERATOR_H
#define CREATE_TABLE_PHYSICAL_OPERATOR_H
#include "physical_operator.h"
typedef struct CreateTablePhysicalOperator
{
  PhysicalOperatorType type;
  varArrayList        *children;
  AbstractTuple       *parentTuple;
  GNCDB               *db;
  char                *tableName;
  varArrayList        *attrInfos;
} CreateTablePhysicalOperator;
int            CreateTablePhysOperInit(CreateTablePhysicalOperator *createTablePhysOper, PhysicalOperatorType type);
int            CreateTablePhysOperOpen(CreateTablePhysicalOperator *createTablePhysOper, SQLStageEvent *sqlEvent);
int            CreateTablePhysOperNext(CreateTablePhysicalOperator *createTablePhysOper, SQLStageEvent *sqlEvent);
int            CreateTablePhysOperClose(CreateTablePhysicalOperator *createTablePhysOper, SQLStageEvent *sqlEvent);
AbstractTuple *CreateTablePhysOperGetCurrentTuple(CreateTablePhysicalOperator *createTablePhysOper);
void           CreateTablePhysOperDestroy(CreateTablePhysicalOperator *createTablePhysOper);
void           CreateTablePhysOperPointerDestroy(void *data);
CreateTablePhysicalOperator *CreateTablePhysOperMove(CreateTablePhysicalOperator **createTablePhysOper);
#endif  // CREATE_TABLE_PHYSICAL_OPERATOR_H