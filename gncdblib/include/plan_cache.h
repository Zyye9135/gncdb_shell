#ifndef PLAN_CACHE_H
#define PLAN_CACHE_H

#include "HashMap.h"
#include "join_optimizer.h"

typedef struct PlanCache{
    HashMap *bestOrders;        // 存储最佳顺序的哈希表 <Set<LogicalJoinNode>,Vector<LogicalJoinNode>>
    HashMap *bestCosts;         // 存储最佳成本的哈希表 <Set<LogicalJoinNode>,Double>
    HashMap *bestCardinalities; // 存储最佳基数的哈希表 <Set<LogicalJoinNode>,Int>
} PlanCache;

// 初始化 PlanCache
void PlanCacheInit(PlanCache *cache);

// 创建 PlanCache
PlanCache* PlanCacheCreate();

// 添加计划到 PlanCache
void PlanCacheAddPlan(PlanCache *cache, varArrayList* subset, double cost, int cardinality, varArrayList *order);

// 获取最佳连接顺序
varArrayList *PlanCacheGetOrder(PlanCache *cache, varArrayList *joinNodes);

// 获取最佳连接顺序的成本
double PlanCacheGetCost(PlanCache *cache, varArrayList *joinNodes);

// 获取最佳连接顺序的基数
int PlanCacheGetCard(PlanCache *cache, varArrayList *joinNodes);

// 释放 PlanCache
void PlanCacheDestroy(PlanCache *cache);

#endif // PLAN_CACHE_H