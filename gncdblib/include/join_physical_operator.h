/*
 * @Author: zql 1901227828@qq.com
 * @Date: 2025-02-25 09:31:58
 * @LastEditors: zql 1901227828@qq.com
 * @LastEditTime: 2025-02-26 16:45:17
 * @FilePath: /gncdbflr/linux_dev/src/queryprocess/operator/join_physical_operator.h
 * @Description: 这是默认设置,请设置`customMade`, 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 */
#ifndef JOIN_PHYSICAL_OPERATOR_H
#define JOIN_PHYSICAL_OPERATOR_H
#include "hashmap.h"
#include "exec_tuple.h"
#include "physical_operator.h"
typedef struct NestedLoopJoinPhysicalOperator
{
  PhysicalOperatorType type;         // 算子类型
  varArrayList        *children;     // PhysicalOperator*
  AbstractTuple       *parentTuple;  // 父元组，用于复杂子查询
  PhysicalOperator    *left;         // 左表算子
  PhysicalOperator    *right;        // 右表算子
  varArrayList        *leftBlock;   // 左表元组组成的逻辑块
  AbstractTuple       *leftTuple;    // 左表当前元组
  AbstractTuple       *rightTuple;   // 右表当前元组
  JoinedTuple          joinedTuple;  // 返回的连接元组
  Transaction         *trx;          // 事务
  bool                 roundDone;    // 右表遍历的一轮是否结束
  bool                 leftBlkDone;  // 左表块是否遍历结束
  bool                 rightClosed;  // 右表算子是否已经关闭
  varArrayList        *predicates;   // Expression*
} NestedLoopJoinPhysicalOperator;
int NestedLoopJoinPhysOperInit(NestedLoopJoinPhysicalOperator *nextedLoopJoinPhysoper, PhysicalOperatorType type);
int NestedLoopJoinPhysOperOpen(NestedLoopJoinPhysicalOperator *nextedLoopJoinPhysoper, SQLStageEvent *sqlEvent);
int NestedLoopJoinPhysOperNext(NestedLoopJoinPhysicalOperator *nextedLoopJoinPhysoper, SQLStageEvent *sqlEvent);
int NestedLoopJoinPhysOperClose(NestedLoopJoinPhysicalOperator *nextedLoopJoinPhysoper, SQLStageEvent *sqlEvent);
int NestedLoopJoinPhysOperLeftNext(NestedLoopJoinPhysicalOperator *nextedLoopJoinPhysoper, SQLStageEvent *sqlEvent);
int NestedLoopJoinPhysOperRightNext(NestedLoopJoinPhysicalOperator *nextedLoopJoinPhysoper, SQLStageEvent *sqlEvent);
AbstractTuple                  *NestedLoopJoinPhysOperGetCurrentTuple(NestedLoopJoinPhysicalOperator *oper);
bool                            NestedLoopJoinPhysOperFilter(NestedLoopJoinPhysicalOperator *oper);
void                            NestedLoopJoinPhysOperDestroy(NestedLoopJoinPhysicalOperator *nextedLoopJoinPhysoper);
void                            NestedLoopJoinPhysOperPointerDestroy(void *data);
NestedLoopJoinPhysicalOperator *NestedLoopJoinPhysOperMove(NestedLoopJoinPhysicalOperator **nextedLoopJoinPhysoper);
typedef struct HashJoinPhysicalOperator
{
  PhysicalOperatorType type;                // 算子类型
  varArrayList        *children;            // PhysicalOperator*
  AbstractTuple       *parentTuple;         // 父元组，用于复杂子查询
  FieldExpr           *leftJoinField;       // 连接的左字段
  FieldExpr           *rightJoinField;      // 连接的右字段
  JoinedTuple          joinedTuple;         // 返回的连接元组
  Transaction         *trx;                 // 事务
  varArrayList        *predicates;          // 连接的谓词
  HashMap             *hashTable;           // 哈希表
  varArrayList        *joinedTuples;        // 存储已经关联的tuple
  int                  iter;                // 迭代器
  HashMapValueList    *list;                // 哈希表的值列表
  bool                 roundDone;           // 右表遍历的一轮是否结束
  bool                 rightClosed;         // 右表算子是否已经关闭
  bool                 useNoConditionJoin;  // 是否使用无条件连接
} HashJoinPhysicalOperator;
int                       HashJoinPhysOperInit(HashJoinPhysicalOperator *hashJoinPhysOper, PhysicalOperatorType type);
int                       HashJoinPhysOperOpen(HashJoinPhysicalOperator *hashJoinPhysOper, SQLStageEvent *sqlEvent);
int                       HashJoinPhysOperNext(HashJoinPhysicalOperator *hashJoinPhysOper, SQLStageEvent *sqlEvent);
int                       HashJoinPhysOperClose(HashJoinPhysicalOperator *hashJoinPhysOper, SQLStageEvent *sqlEvent);
AbstractTuple            *HashJoinPhysOperGetCurrentTuple(HashJoinPhysicalOperator *oper);
int                       HashJoinPhysOperFindJoinKeys(HashJoinPhysicalOperator *oper);
bool                      HashJoinPhysOperFilter(HashJoinPhysicalOperator *oper);
void                      HashJoinPhysOperDestroy(HashJoinPhysicalOperator *hashJoinPhysOper);
void                      HashJoinPhysOperPointerDestroy(void *data);
HashJoinPhysicalOperator *HashJoinPhysOperMove(HashJoinPhysicalOperator **hashJoinPhysOper);

typedef struct IntPair
{
  int left;
  int right;
} IntPair;
typedef struct SortMergeJoinPhysicalOperator
{
  PhysicalOperatorType type;
  varArrayList        *children;
  AbstractTuple       *parentTuple;
  PhysicalOperator    *left;
  PhysicalOperator    *right;
  JoinedTuple          joinedTuple;
  Transaction         *trx;
  varArrayList        *predicates;    // element type:<Expression*>
  Expression          *leftJoinKey;   // 连接的左字段
  Expression          *rightJoinKey;  // 连接的右字段
  int                  iter;
  varArrayList        *relLeft;
  varArrayList        *relRight;
  varArrayList        *joinedTuples;  // 存储已经关联的tuple
  bool                 useNoConditionJoin;
} SortMergeJoinPhysicalOperator;
int SortMergeJoinPhysOperInit(SortMergeJoinPhysicalOperator *sortMergeJoinPhysOper, PhysicalOperatorType type);
int SortMergeJoinPhysOperOpen(SortMergeJoinPhysicalOperator *sortMergeJoinPhysOper, SQLStageEvent *sqlEvent);
int SortMergeJoinPhysOperNext(SortMergeJoinPhysicalOperator *sortMergeJoinPhysOper, SQLStageEvent *sqlEvent);
int SortMergeJoinPhysOperClose(SortMergeJoinPhysicalOperator *sortMergeJoinPhysOper, SQLStageEvent *sqlEvent);
AbstractTuple                 *SortMergeJoinPhysOperGetCurrentTuple(SortMergeJoinPhysicalOperator *oper);
int                            SortMergeJoinPhysOperFindJoinKeys(SortMergeJoinPhysicalOperator *oper);
bool                           SortMergeJoinPhysOperFilter(SortMergeJoinPhysicalOperator *oper);
void                           SortMergeJoinPhysOperDestroy(SortMergeJoinPhysicalOperator *sortMergeJoinPhysOper);
void                           SortMergeJoinPhysOperPointerDestroy(void *data);
SortMergeJoinPhysicalOperator *SortMergeJoinPhysOperMove(SortMergeJoinPhysicalOperator **sortMergeJoinPhysOper);
#endif  // JOIN_PHYSICAL_OPERATOR_H