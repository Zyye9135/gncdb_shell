#ifndef CREATE_TABLE_LOGICAL_OPERATOR_H
#define CREATE_TABLE_LOGICAL_OPERATOR_H
#include "logical_operator.h"
typedef struct CreateTableLogicalOperator{
    LogicalOperatorType type;
    varArrayList* children;       
    varArrayList* expressions;    

    GNCDB* db;                    
    char* tableName;             
    varArrayList* attrInfos;    
}CreateTableLogicalOperator;

void CreateTableLogiOperDestroy(CreateTableLogicalOperator* createTableLogiOper);
void CreateTableLogiOperPointerDestroy(void* data);
CreateTableLogicalOperator* CreateTableLogiOperMove(CreateTableLogicalOperator** createTableLogiOper);
#endif  // CREATE_TABLE_LOGICAL_OPERATOR_H