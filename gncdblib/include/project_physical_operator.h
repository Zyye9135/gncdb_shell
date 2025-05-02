#ifndef PROJECT_PHYSICAL_OPERATOR_H_
#define PROJECT_PHYSICAL_OPERATOR_H_
#include "physical_operator.h"
#include "vararraylist.h"
typedef struct TupleSchema
{
  varArrayList *columnList;
} TupleSchema;
typedef struct ProjectPhysicalOperator
{
  PhysicalOperatorType type;
  varArrayList        *children;  // element type:<PhysicalOperator*>
  AbstractTuple       *parentTuple;
  ProjectTuple        *tuple;
  bool                 isDistinct;
  HashMap             *distinctMap;
  TupleSchema         *schema;
} ProjectPhysicalOperator;
void           ProjectPhysOperInit(ProjectPhysicalOperator *projectPhysOper);
int            ProjectPhysOperOpen(ProjectPhysicalOperator *projectPhysOper, SQLStageEvent *sqlEvent);
int            ProjectPhysOperNext(ProjectPhysicalOperator *projectPhysOper, SQLStageEvent *sqlEvent);
int            ProjectPhysOperClose(ProjectPhysicalOperator *projectPhysOper, SQLStageEvent *sqlEvent);
int            ProjectPhysOperDistinctFilter(ProjectPhysicalOperator *projectPhysOper, char **fieldValues);
AbstractTuple *ProjectPhysOperGetCurrentTuple(ProjectPhysicalOperator *projectPhysOper);
int  ProjectPhysOperGetSchemaTotalSize(ProjectPhysicalOperator *projectPhysOper, SQLStageEvent *sqlEvent, int *len);
void ProjectPhysOperDestroy(ProjectPhysicalOperator *projectPhysOper);
void ProjectPhysOperPointerDestroy(void *data);
ProjectPhysicalOperator *ProjectPhysOperMove(ProjectPhysicalOperator **projectPhysOper);
#endif  // PROJECT_PHYSICAL_OPERATOR_H_.