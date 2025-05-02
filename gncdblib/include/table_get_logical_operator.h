#ifndef TABLE_GET_LOGICAL_OPERATOR_H
#define TABLE_GET_LOGICAL_OPERATOR_H
#include "btreetable.h"
#include "logical_operator.h"
typedef struct TableGetLogicalOperator
{
  LogicalOperatorType type;
  varArrayList       *children;  ///< 子算子
                                 ///< element type:<LogicalOperator*>

  varArrayList *expressions;  ///< 表达式，比如select中的列，where中的谓词等等，都可以使用表达式来表示
                              ///< 表达式能是一个常量，也可以是一个函数，也可以是一个列，也可以是一个子查询等等
                              ///< element type:<Expression*>
  BtreeTable   *table;
  varArrayList *fields;  ///< 字段，比如select中的列，where中的谓词等等，都可以使用字段来表示
                         ///< element type:<FieldInfo>

  bool readOnly;  ///< 是否只读

  varArrayList *predicates;  ///< 与当前表相关的过滤操作，可以尝试在遍历数据时执行
                             ///< 这里的表达式都是比较简单的比较运算，并且左右两边都是取字段表达式或值表达式
                             ///< 不包含复杂的表达式运算，比如加减乘除、或者conjunction expression
                             ///< 如果有多个表达式，他们的关系都是 AND
                             ///< element type:<Expression*>
} TableGetLogicalOperator;
void                     TableGetLogiOperDestroy(TableGetLogicalOperator *tableGetLogiOper);
void                     TableGetLogiOperPointerDestroy(void *data);
TableGetLogicalOperator *TableGetLogiOperMove(TableGetLogicalOperator **tableGetLogiOper);
#endif  // TABLE_GET_LOGICAL_OPERATOR_H