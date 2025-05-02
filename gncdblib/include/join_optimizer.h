#ifndef JOIN_OPTIMIZER_H
#define JOIN_OPTIMIZER_H
#include "hashmap.h"
#include "join_logical_operator.h"
#include "parse_defs.h"
#include "table_stats.h"
#include "value.h"
#include "vararraylist.h"
typedef struct PlanCache PlanCache;
typedef struct LogicalJoinNode
{
  char       *tableName1;
  char       *tableName2;
  char       *f1PureName;  // 在 t1 中用于连接的字段名。它是字段的纯名称，而不是别名.字段
  char       *f2PureName;  // 在 t2 中用于连接的字段名。它是字段的纯名称，而不是别名.字段
  CompOp      op;          // 连接的比较操作符
  JoinType    joinType;    // 连接的类型，如nested loop, hash, merge，需要计算后确定
  Expression *origExpr;  // 原始的连接条件表达式(用于处理连接条件on中除了等值连接的其他情况，这种情况暂时无法进行优化)
} LogicalJoinNode;
/* 判断是否可以优化 */
LogicalJoinNode *LogicalJoinNodeCreate(
    char *tableName1, char *tableName2, char *f1PureName, char *f2PureName, CompOp op);
/* deep copy */
LogicalJoinNode *LogicalJoinNodeCopy(LogicalJoinNode *node);
/* 交换node的左右 */
LogicalJoinNode *LogicalJoinNodeGetSwap(LogicalJoinNode *node);
/* 打印node */
void LogicalJoinNodePrint(LogicalJoinNode *node);
/* 打印nodelist */
void LogicalJoinNodeListPrint(varArrayList *list);
/* 比较两个LogicalJoinNode的指针，用于varArrayList元素的compare */
int  LogicalJoinNodePointerCompare(varArrayList *array, void *a, void *b);
void LogicalJoinNodeDestroy(LogicalJoinNode **node);
void LogicalJoinNodePointerDestroy(void *node);

CompOp swapOp(CompOp op);

typedef struct CostCard
{
  double        cost;  // 代价
  int           card;  // 基数
  varArrayList *plan;  // 连接计划(为list分配了内存，需要free)
} CostCard;
CostCard *CostCardCreate();
void      CostCardDestroy(CostCard **costCard);
// 存储用于基数估计与代价计算相关的信息
typedef struct SpecialJoinInfo
{
  varArrayList *filterList;     // 用于估计基数的过滤器列表(由create创建，需要free)
  PlanCache    *planCache;      // 用于存储计划缓存的列表(由create创建，需要free)
  HashMap      *stats;          // 用于存储表统计信息的哈希表(来自catalog，不需要free)
  HashMap      *selectivities;  // 用于存储选择性的哈希表(需要free)
} SpecialJoinInfo;
SpecialJoinInfo *SpecialJoinInfoCreate();
void             SpecialJoinInfoDestroy(SpecialJoinInfo **info);

typedef struct JoinOptimizer
{
  varArrayList *joins;  // LogicalJoinNode
} JoinOptimizer;

/* 枚举集合的子集 */
varArrayList *enumerateSubsets(varArrayList *joinList, int size);
/* 计算连接的代价 */
CostCard *computeCostAndCardOfSubplan(HashMap *stats, HashMap *filterSelectivities, LogicalJoinNode *joinToRemove,
    varArrayList *joinSet, double bestCostSoFar, PlanCache *pc, GNCDB *db);
/* 将stmt生成的joinTables转换成joinList */
varArrayList *getJoinList(varArrayList *joinTables);
/* 根据代价模型计算连接代价，选择最优的连接顺序 */
varArrayList *orderJoins(varArrayList *joinList, SpecialJoinInfo *sji, GNCDB *db);
/* 进行连接优化 */
varArrayList *doJoinOptimization(varArrayList *joinTables, Expression *whereClause, GNCDB *db);
#endif  // JOIN_OPTIMIZER_H