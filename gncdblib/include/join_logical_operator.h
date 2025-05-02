#ifndef JOIN_LOGICAL_OPERATOR_H
#define JOIN_LOGICAL_OPERATOR_H
#include "logical_operator.h"
typedef enum JoinType
{
  JT_INVALID,
  JT_CROSS,
  JT_NESTED_LOOP,
  JT_HASH,
  JT_SORT_MERGE,
} JoinType;
typedef struct JoinLogicalOperator
{
  LogicalOperatorType type;
  varArrayList       *children;  ///< 子算子
                                 ///< LogicalOperator*

  varArrayList *expressions;  ///< 表达式，比如select中的列，where中的谓词等等，都可以使用表达式来表示element
                              ///< type:<Expression*>
                              ///< 表达式能是一个常量，也可以是一个函数，也可以是一个列，也可以是一个子查询等等
                              ///< Expression*
  JoinType joinType;  ///< 对应的物理连接的类型，如nested loop, hash, merge
} JoinLogicalOperator;

void                 JoinLogiOperDestroy(JoinLogicalOperator *joinLogiOper);
void                 JoinLogiOperPointerDestroy(void *data);
JoinLogicalOperator *JoinLogiOperMove(JoinLogicalOperator **joinLogiOper);
#endif  // JOIN_LOGICAL_OPERATOR_H