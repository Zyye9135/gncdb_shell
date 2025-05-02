#ifndef JOIN_PHYSICAL_OPERATOR_H
#define JOIN_PHYSICAL_OPERATOR_H
#include "HashMap.h"
#include "exec_tuple.h"
#include "physical_operator.h"
typedef struct NestedLoopJoinPhysicalOperator{
  PhysicalOperatorType type;
  varArrayList* children;        //element type:<PhysicalOperator*>
  AbstractTuple* parentTuple;

  PhysicalOperator *left;
  PhysicalOperator *right;
  AbstractTuple* leftTuple;
  AbstractTuple* rightTuple;
  JoinedTuple joinedTuple;     //! 当前关联的左右两个tuple
  Transaction* trx;
  bool roundDone;              //! 右表遍历的一轮是否结束
  bool rightClosed;            //! 右表算子是否已经关闭

  varArrayList* predicates;     // element type:<Expression*>
}NestedLoopJoinPhysicalOperator;

int NestedLoopJoinPhysOperInit(NestedLoopJoinPhysicalOperator* nextedLoopJoinPhysoper, PhysicalOperatorType type);
int NestedLoopJoinPhysOperOpen(NestedLoopJoinPhysicalOperator* nextedLoopJoinPhysoper,SQLStageEvent* sqlEvent);
int NestedLoopJoinPhysOperNext(NestedLoopJoinPhysicalOperator* nextedLoopJoinPhysoper,SQLStageEvent* sqlEvent);
int NestedLoopJoinPhysOperClose(NestedLoopJoinPhysicalOperator* nextedLoopJoinPhysoper,SQLStageEvent* sqlEvent);
int NestedLoopJoinPhysOperLeftNext(NestedLoopJoinPhysicalOperator* nextedLoopJoinPhysoper,SQLStageEvent* sqlEvent);
int NestedLoopJoinPhysOperRightNext(NestedLoopJoinPhysicalOperator* nextedLoopJoinPhysoper,SQLStageEvent* sqlEvent);
AbstractTuple* NestedLoopJoinPhysOperGetCurrentTuple(NestedLoopJoinPhysicalOperator* oper);
bool NestedLoopJoinPhysOperFilter(NestedLoopJoinPhysicalOperator* oper);
void NestedLoopJoinPhysOperDestroy(NestedLoopJoinPhysicalOperator* nextedLoopJoinPhysoper);
void NestedLoopJoinPhysOperPointerDestroy(void* data);
NestedLoopJoinPhysicalOperator* NestedLoopJoinPhysOperMove(NestedLoopJoinPhysicalOperator** nextedLoopJoinPhysoper);



typedef struct HashJoinPhysicalOperator {
  PhysicalOperatorType type;
  varArrayList* children;
  AbstractTuple* parentTuple;

  FieldExpr *leftJoinField;
  FieldExpr *rightJoinField;
  JoinedTuple joinedTuple;
  Transaction* trx;
  varArrayList* predicates;     // 连接的谓词
  HashMap* hashTable;          
  varArrayList* joinedTuples;  // 存储已经关联的tuple
  int iter;                     
  HashMapValueList* list;
  bool roundDone;              //! 右表遍历的一轮是否结束
  bool rightClosed;            //! 右表算子是否已经关闭
  // 是否使用无条件连接
  bool useNoConditionJoin;
  varArrayList* relLeft;
} HashJoinPhysicalOperator;

int HashJoinPhysOperInit(HashJoinPhysicalOperator* hashJoinPhysOper, PhysicalOperatorType type);
int HashJoinPhysOperOpen(HashJoinPhysicalOperator* hashJoinPhysOper, SQLStageEvent* sqlEvent);
int HashJoinPhysOperNext(HashJoinPhysicalOperator* hashJoinPhysOper, SQLStageEvent* sqlEvent);
int HashJoinPhysOperClose(HashJoinPhysicalOperator* hashJoinPhysOper, SQLStageEvent* sqlEvent);
AbstractTuple* HashJoinPhysOperGetCurrentTuple(HashJoinPhysicalOperator* oper);
int HashJoinPhysOperFindJoinKeys(HashJoinPhysicalOperator* oper);
bool HashJoinPhysOperFilter(HashJoinPhysicalOperator* oper);
void HashJoinPhysOperDestroy(HashJoinPhysicalOperator* hashJoinPhysOper);
void HashJoinPhysOperPointerDestroy(void* data);
HashJoinPhysicalOperator* HashJoinPhysOperMove(HashJoinPhysicalOperator** hashJoinPhysOper);

typedef struct IntPair{
  int left;
  int right;
}IntPair;
typedef struct SortMergeJoinPhysicalOperator{
  PhysicalOperatorType type;
  varArrayList* children;
  AbstractTuple* parentTuple;

  PhysicalOperator *left;
  PhysicalOperator *right;
  JoinedTuple joinedTuple;
  Transaction* trx;
  varArrayList* predicates; // element type:<Expression*>
  Expression* leftJoinKey; // 连接的左字段
  Expression* rightJoinKey; // 连接的右字段
  int iter;
  varArrayList* relLeft;
  varArrayList* relRight;
  varArrayList* joinedTuples; // 存储已经关联的tuple
  bool useNoConditionJoin;
}SortMergeJoinPhysicalOperator;

int SortMergeJoinPhysOperInit(SortMergeJoinPhysicalOperator* sortMergeJoinPhysOper, PhysicalOperatorType type);
int SortMergeJoinPhysOperOpen(SortMergeJoinPhysicalOperator* sortMergeJoinPhysOper, SQLStageEvent* sqlEvent);
int SortMergeJoinPhysOperNext(SortMergeJoinPhysicalOperator* sortMergeJoinPhysOper, SQLStageEvent* sqlEvent);
int SortMergeJoinPhysOperClose(SortMergeJoinPhysicalOperator* sortMergeJoinPhysOper, SQLStageEvent* sqlEvent);
AbstractTuple* SortMergeJoinPhysOperGetCurrentTuple(SortMergeJoinPhysicalOperator* oper);
int SortMergeJoinPhysOperFindJoinKeys(SortMergeJoinPhysicalOperator* oper);
// filter
bool SortMergeJoinPhysOperFilter(SortMergeJoinPhysicalOperator* oper);
void SortMergeJoinPhysOperDestroy(SortMergeJoinPhysicalOperator* sortMergeJoinPhysOper);
void SortMergeJoinPhysOperPointerDestroy(void* data);
SortMergeJoinPhysicalOperator* SortMergeJoinPhysOperMove(SortMergeJoinPhysicalOperator** sortMergeJoinPhysOper);

#endif //JOIN_PHYSICAL_OPERATOR_H