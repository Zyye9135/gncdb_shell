#ifndef INDEX_SCAN_PHYSICAL_OPERATOR_H
#define INDEX_SCAN_PHYSICAL_OPERATOR_H
#include "btreecursor.h"
#include "physical_operator.h"

typedef struct IndexScanPhysicalOperator
{
  PhysicalOperatorType type;
  varArrayList        *children;  // element type:<PhysicalOperator*>
  AbstractTuple       *parentTuple;

  Transaction  *txn;
  BtreeTable   *table;
  varArrayList *startKeyValue;
  BtreeCursor  *cursor;      /* 遍历游标 */
  varArrayList *predicates;  //  element type:<Expression*>
  RowTuple     *tuple;
  int           found;
} IndexScanPhysicalOperator;
void IndexScanPhysOperInit(IndexScanPhysicalOperator *indexScanPhysOper);
int  IndexScanPhysOperOpen(IndexScanPhysicalOperator *indexScanPhysOper, SQLStageEvent *sqlEvent);
int  IndexScanPhysOperNext(IndexScanPhysicalOperator *indexScanPhysOper, SQLStageEvent *sqlEvent);
int  IndexScanPhysOperClose(IndexScanPhysicalOperator *indexScanPhysOper, SQLStageEvent *sqlEvent);
int  indexScanPhysOperFilter(IndexScanPhysicalOperator *indexScanPhysOper, AbstractTuple *tuple, bool *result);
AbstractTuple             *IndexScanPhysOperGetCurrentTuple(IndexScanPhysicalOperator *indexScanPhysOper);
BtreeCursor               *IndexScanPhysOperGetScanCursor(IndexScanPhysicalOperator *indexScanPhysOper);
void                       IndexScanPhysOperDestroy(IndexScanPhysicalOperator *indexScanPhysOper);
void                       IndexScanPhysOperPointerDestroy(void *data);
IndexScanPhysicalOperator *IndexScanPhysOperMove(IndexScanPhysicalOperator **indexScanPhysOper);

#endif  // INDEX_SCAN_PHYSICAL_OPERATOR_H
