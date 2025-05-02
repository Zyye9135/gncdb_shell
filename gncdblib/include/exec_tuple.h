#ifndef EXEC_TUPLE_H
#define EXEC_TUPLE_H
#include "catalog.h"
#include "tuple.h"
// #include "gncdb.h"
typedef struct FieldExpr    FieldExpr;
typedef struct AggrFuncExpr AggrFuncExpr;
/*其他tuple的定义*/
typedef enum TupleType
{
  INVALID_TUPLE,    /* 无效的元组 */
  ROW_TUPLE,        /* 一行数据的元组 */
  PROJECT_TUPLE,    /* 一行数据的投影元组 */
  EXPRESSION_TUPLE, /* 表达式元组 */
  VALUELIST_TUPLE,  /* 一些常量值组成的Tuple */
  JOINED_TUPLE,     /* 连接的元组 */
  GROUP_TUPLE,      /* 分组的元组 */
  SPLICED_TUPLE,
  SUBQUERY_TUPLE,
} TupleType;

typedef struct AbstractTuple
{
  TupleType type; /* 元组的类型 */
} AbstractTuple;

typedef struct RowTuple
{
  TupleType type; /* 元组的类型 */

  Tuple *tuple; /* 元组的内容 */
  // GNCDB* db;					/* 元组所属的数据库 */
  char        *tableName;
  TableSchema *tableSchema; /* 元组所属的表的schema */
} RowTuple;

typedef struct ProjectTuple
{
  TupleType type; /* 元组的类型 */

  varArrayList  *exprs; /* element type:<Expression*> */
  AbstractTuple *tuple; /* 元组的内容 */
} ProjectTuple;

typedef struct ExpressionTuple
{
  TupleType type; /* 元组的类型 */

  varArrayList *expressions; /* element type:<Expression*> */
} ExpressionTuple;

typedef struct ValueListTuple
{
  TupleType type; /* 元组的类型 */

  varArrayList *cells; /* element type:<Value> */
} ValueListTuple;

typedef struct JoinedTuple
{
  TupleType type; /* 元组的类型 */

  AbstractTuple *left;  /* 连接的左元组 */
  AbstractTuple *right; /* 连接的右元组 */
} JoinedTuple;

typedef struct AggrExprResults
{

  AggrFuncExpr *expr;    /* 聚合函数 */
  Value        *result;  /* 聚合函数的结果 */
  int           count;   /* 聚合函数的计数 */
  bool          allNull; /* 是否全为空 */
} AggrExprResults;

typedef struct FieldExprResults
{
  FieldExpr *expr;   /* 字段表达式 */
  Value     *result; /* 字段表达式的结果 */
} FieldExprResults;

typedef struct GroupTuple
{
  TupleType type; /* 元组的类型 */

  int            count;        /* 元组的计数 */
  varArrayList  *aggrResults;  /* element type:<AggrExprResults> */
  varArrayList  *fieldResults; /* element type:<FieldExprResults> */
  AbstractTuple *tuple;        /* 元组的内容 */
} GroupTuple;

typedef struct SplicedTuple
{
  TupleType type; /* 元组的类型 */

  varArrayList *cells; /* element type:<Value>  */

  varArrayList *exprs;  //在 create order by stmt 之前提取的  select clause 后的 field_expr (非a gg_expr 中的)和
                        //agg_expr
  /*element type:<Expression*> */
} SplicedTuple;

/* 针对子查询的tuple */
typedef struct SubQueryTuple
{
  TupleType type; /* 元组的类型 */

  AbstractTuple *parentTuple;
  AbstractTuple *childTuple;
} SubQueryTuple;

/*其他tuple的函数*/
int tupleFindCell(AbstractTuple *tuple, TupleCellSpec *spec, Value *cell);
int tupleCellAt(AbstractTuple *tuple, int index, Value *cell);

int       rowTupleFindCell(RowTuple *rowTuple, TupleCellSpec *spec, Value *cell);
int       rowTupleCellAt(RowTuple *rowTuple, int index, Value *cell);
RowTuple *RowTupleConstructUseTuple(Tuple *tuple, struct GNCDB *db, struct BtreeTable *table);

int projectTupleCellAt(ProjectTuple *projectTuple, int index, Value *cell);
int projectTupleFindCell(ProjectTuple *projectTuple, TupleCellSpec *spec, Value *cell);

GroupTuple *groupTupleCreate();
int         groupTupleCellAt(GroupTuple *groupTuple, int index, Value *cell);
int         GroupTupleFindIndexByAlias(GroupTuple *groupTuple, char *exprName);
int         groupTupleFindCellByAlias(GroupTuple *groupTuple, char *exprName, Value *cell);
int         groupTupleFindCell(GroupTuple *groupTuple, TupleCellSpec *spec, Value *cell);
void        groupTupleInit(GroupTuple *groupTuple, varArrayList *aggrExprs, varArrayList *fieldExprs);
void        groupTupleDoAggrFirst(GroupTuple *groupTuple);
void        groupTupleDoAggr(GroupTuple *groupTuple);
void        groupTupleDoAggrDone(GroupTuple *groupTuple);

void AggrExprResultsInit(AggrExprResults *aggrResults, AbstractTuple *tuple);
void AggrExprResultsAdvance(AggrExprResults *aggrResults, AbstractTuple *tuple);
void AggrExprResultsFinalize(AggrExprResults *aggrResults);

void FieldExprResultsInit(FieldExprResults *fieldResults, AbstractTuple *tuple);

AbstractTuple *tupleDeepCopy(AbstractTuple *tuple);

int splicedTupleCellAt(SplicedTuple *splicedTuple, int index, Value *cell);
int splicedTupleFindCell(SplicedTuple *splicedTuple, TupleCellSpec *spec, Value *cell);

int SubQueryTupleFindCell(SubQueryTuple *subQueryTuple, TupleCellSpec *spec, Value *cell);
int SubQueryTupleCellAt(SubQueryTuple *subQueryTuple, int index, Value *cell);

/* tuple的创建函数*/
SubQueryTuple *SubQueryTupleCreate(AbstractTuple *parentTuple, AbstractTuple *childTuple);

/* tuple的销毁函数 */
void RowTupleDestroy(RowTuple *rowTuple);
void ProjectTupleDestroy(ProjectTuple *projectTuple);
void ExpressionTupleDestroy(ExpressionTuple *expressionTuple);
void ValueListTupleDestroy(ValueListTuple *valueListTuple);
void JoinedTupleDestroy(JoinedTuple *joinedTuple);
void GroupTupleDestroy(GroupTuple *groupTuple);
void SplicedTupleDestroy(SplicedTuple *splicedTuple);
void SubQueryTupleDestroy(SubQueryTuple *subQueryTuple);
void tupleDestroy(AbstractTuple *tuple);
/* aggrExprResults的销毁函数 */
void AggrExprResultsDestroy(AggrExprResults *aggrResults);

/* fieldExprResults的销毁函数 */
void FieldExprResultsDestroy(FieldExprResults *fieldResults);

/* tuple pointer的销毁函数 */
void RowTuplePointerDestroy(void *data);
void ProjectTuplePointerDestroy(void *data);
void ExpressionTuplePointerDestroy(void *data);
void ValueListTuplePointerDestroy(void *data);
void JoinedTuplePointerDestroy(void *data);
void GroupTuplePointerDestroy(void *data);
void SplicedTuplePointerDestroy(void *data);
void AggrExprResultsPointerDestroy(void *data);
void FieldExprResultsPointerDestroy(void *data);
void SubQueryTuplePointerDestroy(void *data);
void TuplePointerDestroy(void *data);

#endif  // EXEC_TUPLE_H