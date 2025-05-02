#ifndef INSERT_LOGICAL_OPERATOR_H
#define INSERT_LOGICAL_OPERATOR_H
#include "btreetable.h"
#include "logical_operator.h"
typedef struct InsertLogicalOperator{
    LogicalOperatorType type;
    varArrayList* children;       ///< 子算子 element type:<LogicalOperator*>
    varArrayList* expressions;    ///< 表达式，比如select中的列，where中的谓词等等，都可以使用表达式来表示 element type:<Expression*>
    
    BtreeTable* table;            
    varArrayList* valuelists;         ///< 插入的值
                                  ///< element type:<Value> ;
}InsertLogicalOperator;


void InsertLogiOperDestroy(InsertLogicalOperator* insertLogiOper);
void InsertLogiOperPointerDestroy(void* data);
InsertLogicalOperator* InsertLogiOperMove(InsertLogicalOperator** insertLogiOper);
#endif // INSERT_LOGICAL_OPERATOR_H