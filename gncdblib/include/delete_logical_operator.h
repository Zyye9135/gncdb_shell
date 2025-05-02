#ifndef DELETE_LOGICAL_OPERATOR_H
#define DELETE_LOGICAL_OPERATOR_H
#include "logical_operator.h"
typedef struct DeleteLogicalOperator
{
  LogicalOperatorType type;
  varArrayList       *children;  ///< 子算子
                                 ///< element type:<LogicalOperator*>
  varArrayList *expressions;  ///< 表达式，比如select中的列，where中的谓词等等，都可以使用表达式来表示
                              ///原型：element type:<Expression*>

  BtreeTable *table;  ///< btree表对象
} DeleteLogicalOperator;

void                   DeleteLogiOperDestroy(DeleteLogicalOperator *deleteLogiOper);
void                   DeleteLogiOperPointerDestroy(void *data);
DeleteLogicalOperator *DeleteLogiOperMove(DeleteLogicalOperator **deleteLogiOper);
#endif  // DELETE_LOGICAL_OPERATOR_H