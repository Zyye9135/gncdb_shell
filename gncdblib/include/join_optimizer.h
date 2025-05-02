#ifndef JOIN_OPTIMIZER_H
#define JOIN_OPTIMIZER_H
#include "HashMap.h"
#include "parse_defs.h"
#include "varArrayList.h"
typedef struct PlanCache PlanCache;
typedef struct LogicalJoinNode{
    char* tableName1;
    char* tableName2;

    
    char* f1PureName;       // 在 t1 中用于连接的字段名。它是字段的纯名称，而不是别名.字段
    char* f2PureName;       // 在 t2 中用于连接的字段名。它是字段的纯名称，而不是别名.字段
    CompOp op;              // 连接的比较操作符
}LogicalJoinNode;
LogicalJoinNode* LogicalJoinNodeCreate(char* tableName1, char* tableName2, char* f1PureName, char* f2PureName, CompOp op);
/* 交换node的左右 */
LogicalJoinNode* LogicalJoinNodeGetSwap(LogicalJoinNode* node);
/* 比较两个LogicalJoinNode的指针，用于varArrayList元素的compare */
int LogicalJoinNodePointerCompare(varArrayList* array, void* a, void* b);
void LogicalJoinNodeDestroy(LogicalJoinNode** node);

typedef struct CostCard{
    double          cost;
    int             card;
    varArrayList*   plan; // 为list分配了内存，而不是引用其他list指针
}CostCard;
CostCard* CostCardCreate();
void CostCardDestroy(CostCard** costCard);

typedef struct JoinOptimizer{
    varArrayList*   joins; // LogicalJoinNode
}JoinOptimizer;

/* 枚举集合的子集 */
varArrayList* enumerateSubsets(varArrayList* joinList, int size);
/* 计算连接的代价 */
CostCard *computeCostAndCardOfSubplan(HashMap *stats, HashMap *filterSelectivities, LogicalJoinNode *joinToRemove, varArrayList *joinSet, double bestCostSoFar, PlanCache *pc);
/* 将stmt生成的joinTables转换成joinList */
varArrayList* getJoinList(varArrayList* joinTables);
/* 根据代价模型计算连接代价，选择最优的连接顺序 */
varArrayList* orderJoins(varArrayList* joinList);
/* 进行连接顺序优化 */
varArrayList* doJoinOptimization(varArrayList* joinTables);
#endif // JOIN_OPTIMIZER_H