#ifndef PHYSICAL_OPERATOR_H
#define PHYSICAL_OPERATOR_H
#include "exec_tuple.h"
#include "sql_event.h"
#include "varArrayList.h"
typedef enum PhysicalOperatorType
{
  PO_TABLE_SCAN,
  PO_INDEX_SCAN,
  PO_NESTED_LOOP_JOIN,
  PO_EXPLAIN,
  PO_PREDICATE,
  PO_PROJECT,
  PO_CALC,
  PO_STRING_LIST,
  PO_DELETE,
  PO_INSERT,
  PO_UPDATE,
  PO_GROUPBY,
  PO_HASH_JOIN,
  PO_SORT_MERGE_JOIN,
  PO_ORDER_BY,
  PO_CREATE_TABLE,
  PO_LIMIT,
} PhysicalOperatorType;

typedef struct PhysicalOperator{
  PhysicalOperatorType type;
  varArrayList* children;// element type:<PhysicalOperator*>
  AbstractTuple* parentTuple;


}PhysicalOperator;
int PhysicalOperatorInit(PhysicalOperator* physicalOperator, PhysicalOperatorType type);
int PhysicalOperatorOpen(PhysicalOperator*physicalOperator,SQLStageEvent* sqlEvent);
int PhysicalOperatorNext(PhysicalOperator* physicalOperator,SQLStageEvent* sqlEvent);
int PhysicalOperatorClose(PhysicalOperator* physicalOperator,SQLStageEvent* sqlEvent);
AbstractTuple* GetCurrentTuple(PhysicalOperator* physicalOperator);
BtreeCursor* GetScanCursor(PhysicalOperator* physicalOperator);
void setParentTuple(PhysicalOperator* physicalOperator, AbstractTuple* parentTuple);
void PhysicalOperatorToString(PhysicalOperator* physicalOperator, int depth);
void PhysicalOperatorDestroy(PhysicalOperator* physicalOperator);
void PhysicalOperatorPointerDestroy(void* data);
PhysicalOperator* PhysicalOperatorMove(PhysicalOperator** physicalOperator);
#endif // PHYSICAL_OPERATOR_H