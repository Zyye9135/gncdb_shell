#ifndef TABLE_SCAN_PHYSICAL_OPERATOR_H
#define TABLE_SCAN_PHYSICAL_OPERATOR_H
#include "physical_operator.h"
#include "tuple.h"
typedef struct TableScanPhysicalOperator{
    PhysicalOperatorType type;
    varArrayList* children;// element type:<PhysicalOperator*>
    AbstractTuple* parentTuple;

    Transaction* txn;
    BtreeTable* table;
    varArrayList* startKeyValue;
    BtreeCursor* cursor;		/* 遍历游标 */
    varArrayList* predicates; // element type:<Expression*>
    RowTuple tuple;
}TableScanPhysicalOperator;
TableScanPhysicalOperator* TableScanPhysOperCreate();
void TableScanPhysicalOperatorInit(TableScanPhysicalOperator* tableScanPhysOper);
int TableScanPhysOperOpen(TableScanPhysicalOperator*tableScanPhysOper, SQLStageEvent* sqlEvent);
int TableScanPhysOperNext(TableScanPhysicalOperator* tableScanPhysOper, SQLStageEvent* sqlEvent);
int TableScanPhysOperClose(TableScanPhysicalOperator* tableScanPhysOper,SQLStageEvent* sqlEvent);
void setRowTuple(TableScanPhysicalOperator* tableScanPhysOper, Tuple* tuple);
int TableScanPhysOperFilter(TableScanPhysicalOperator* tableScanPhysOper, AbstractTuple* tuple, bool *result);
BtreeCursor* TableScanPhysOperGetScanCursor(TableScanPhysicalOperator* tableScanPhysOper);
AbstractTuple* TableScanPhysOperGetCurrentTuple(TableScanPhysicalOperator* tableScanPhysOper);
void TableScanPhysOperDestroy(TableScanPhysicalOperator* tableScanPhysOper);
void TableScanPhysOperPointerDestroy(void* data);
TableScanPhysicalOperator* TableScanPhysOperMove(TableScanPhysicalOperator** tableScanPhysOper);
#endif // TABLE_SCAN_PHYSICAL_OPERATOR_H