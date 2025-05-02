#ifndef EXPRESSION_H
#define EXPRESSION_H
#include "exec_tuple.h"
#include "select_stmt.h"
struct Expression;
typedef struct SelectStmt       SelectStmt;
typedef struct LogicalOperator  LogicalOperator;
typedef struct PhysicalOperator PhysicalOperator;
typedef struct AggrFuncExpr     AggrFuncExpr;
typedef enum
{
  CJET_AND,
  CJET_OR
} ConjunctionExprType;
typedef enum
{
  ADD,
  SUB,
  MUL,
  DIV,
  NEGATIVE
} ArithmeticExprType;
typedef enum
{
  AGG_MAX,
  AGG_MIN,
  AGG_SUM,
  AGG_AVG,
  AGG_COUNT,
  AGGR_FUNC_TYPE_NUM
} AggrFuncType;
typedef enum ExprTag
{
  ETG_BASE = 0,
  ETG_FIELD,
  ETG_VALUE,
  ETG_CAST,
  ETG_COMPARISON,
  ETG_CONJUNCTION,
  ETG_ARITHMETIC,
  ETG_AGGRFUNC,
  ETG_SUBQUERY,
  ETG_EXPRLIST,
} ExprTag;

/* 函数指针类型定义 */
typedef int (*CheckFunc)(Expression *, varArrayList *, int, va_list args);

/* 结构体定义 */
typedef struct Expression
{
  ExprTag type;
  char   *name;  /* 表达式的名字，比如是字段名称，或者用户在执行SQL语句时输入的内容 */
  char   *alias; /* 表达式的别名 */
} Expression;

typedef struct FieldExpr
{
  ExprTag   type;  /* 表达式类型 */
  char     *name;  /* 表达式的名字，比如是字段名称，或者用户在执行SQL语句时输入的内容 */
  char     *alias; /* 表达式的别名 */
  char     *tableName; /* 表名 */
  char     *fieldName; /* 字段名 */
  FieldType fieldType; /* 字段类型 */
} FieldExpr;

typedef struct ValueExpr
{
  ExprTag type;  /* 表达式类型 */
  char   *name;  /* 表达式的名字，比如是字段名称，或者用户在执行SQL语句时输入的内容 */
  char   *alias; /* 表达式的别名 */
  Value  *value; /* 常量值 */
} ValueExpr;

typedef struct CastExpr
{
  ExprTag     type;  /* 表达式类型 */
  char       *name;  /* 表达式的名字，比如是字段名称，或者用户在执行SQL语句时输入的内容 */
  char       *alias; /* 表达式的别名 */
  Expression *child; /* 子表达式 */
  AttrType    castType; /* 转换后的类型 */
} CastExpr;

typedef struct ComparisonExpr
{
  ExprTag     type;  /* 表达式类型 */
  char       *name;  /* 表达式的名字，比如是字段名称，或者用户在执行SQL语句时输入的内容 */
  char       *alias; /* 表达式的别名 */
  CompOp      comp;  /* 比较运算符 */
  Expression *left;  /* 左子表达式 */
  Expression *right; /* 右子表达式 */
} ComparisonExpr;

typedef struct ConjunctionExpr
{
  ExprTag type;  /* 表达式类型 */
  char   *name;  /* 表达式的名字，比如是字段名称，或者用户在执行SQL语句时输入的内容 */
  char   *alias; /* 表达式的别名 */
  ConjunctionExprType conjunctionType; /* 联结类型 */
  varArrayList       *children;        /* 子表达式list，element type: <Expression*> */
} ConjunctionExpr;

typedef struct ArithmeticExpr
{
  ExprTag type;  /* 表达式类型 */
  char   *name;  /* 表达式的名字，比如是字段名称，或者用户在执行SQL语句时输入的内容 */
  char   *alias; /* 表达式的别名 */
  ArithmeticExprType arithmeticType; /* 算术运算类型 */
  Expression        *left;           /* 左子表达式 */
  Expression        *right;          /* 右子表达式 */
} ArithmeticExpr;

typedef struct AggrFuncExpr
{
  ExprTag      type; /* 表达式类型 */
  char        *name; /* 表达式的名字，比如是字段名称，或者用户在执行SQL语句时输入的内容 */
  char        *alias;    /* 表达式的别名 */
  AggrFuncType aggrType; /* 聚合函数类型 */
  Expression  *param;
  bool         paramIsConstexpr;
} AggrFuncExpr;

typedef struct SubQueryExpr
{
  ExprTag           type;
  char             *name;
  char             *alias;
  SelectSqlNode    *sqlNode;
  SelectStmt       *stmt;
  LogicalOperator  *logicalOper;
  PhysicalOperator *physicalOper;
  SQLStageEvent    *subEvent;
} SubQueryExpr;

typedef struct ExprListExpr
{
  ExprTag       type;
  char         *name;
  char         *alias;
  int           curIdx;
  varArrayList *exprs; /* element type: <Expression*> */
} ExprListExpr;

/* 函数声明 */
// TODO: 整理函数声明
// FieldExpr* FieldExprConstruct(FieldInfo* field);
ValueExpr *ValueExprConstruct(Value *value);
void       ConjunctionExprInit(ConjunctionExpr *expr);
void       ExprSetName(Expression *expr, char *str);
int        ComparisonExprCompareValue(CompOp *comp, Value *left, Value *right, bool *value);
int        ComparisonExprTryGetValue(ComparisonExpr *compExpr, Value *cell);
int        exprTryGetValue(Expression *expr, Value *cell);
AttrType   expressionGetValueType(Expression *expr);
int        expressionGetValue(Expression *expr, AbstractTuple *tuple, Value *value);
int        ArithmeticExprTryGetValue(ArithmeticExpr *arithmeticExpr, Value *value);
int        ArithmeticExprCalcValue(ArithmeticExpr *arithmeticExpr, Value *leftValue, Value *rightValue, Value *value);

int      fieldExprCheckField(HashMap *tableMap, varArrayList *tables, GNCDB *db, FieldExpr *fieldExpr,
         BtreeTable *defaultTable, HashMap *tableAliasMap);
bool     exprCheckCanPushDown(Expression *expr, HashMap *tableMap);
int      exprCheckField(HashMap *tableMap, varArrayList *tables, GNCDB *db, Expression *expr, BtreeTable *defaultTable,
         HashMap *tableAliasMap);
int      exprCheckIsConstexpr(Expression *expr);
int      AggrFuncExprGetValue(AggrFuncExpr *expr, AbstractTuple *tuple, Value *value);
AttrType AggrFuncExprGetValueType(AggrFuncExpr *expr);
void     AggrFuncExprInit(AggrFuncExpr *expr, AggrFuncType type, Expression *param);
int      exprTraverseCheckPrepare(
         Expression *expr, CheckFunc checkFunc, varArrayList *fields, int additionalParamsCount, ...);
int exprTraverseCheck(
    Expression *expr, CheckFunc checkFunc, varArrayList *fields, int additionalParamsCount, va_list ap);
Expression *aggrFuncExprDeepCopy(AggrFuncExpr *expr);
Expression *exprDeepCopy(Expression *expr);
bool        SubQueryExprHasMoreRow(SubQueryExpr *subQueryExpr, AbstractTuple *tuple);
int         ExprListExprGetValue(ExprListExpr *expr, AbstractTuple *tuple, Value *value);

/* 表达式创建 */
Expression      *ExpressionCreate(ExprTag type, char *name, char *alias);
FieldExpr       *FieldExprCreate(char *tableName, char *fieldName, char *name, char *alias);
ValueExpr       *ValueExprCreate(Value *value, char *name, char *alias);
CastExpr        *CastExprCreate(AttrType castType, Expression *child, char *name, char *alias);
ComparisonExpr  *ComparisonExprCreate(CompOp comp, Expression *left, Expression *right, char *name, char *alias);
ConjunctionExpr *ConjunctionExprCreate(
    ConjunctionExprType conjunctionType, varArrayList *children, char *name, char *alias);
ArithmeticExpr *ArithmeticExprCreate(
    ArithmeticExprType arithmeticType, Expression *left, Expression *right, char *name, char *alias);
AggrFuncExpr *AggrFuncExprCreate(AggrFuncType aggrType, Expression *param, char *name, char *alias);
SubQueryExpr *SubQueryExprCreate(SelectSqlNode *sqlNode, SQLStageEvent *sqlEvent, char *name, char *alias);
ExprListExpr *ExprListExprCreate(varArrayList *exprs, char *name, char *alias);

/* 表达式销毁 */
void expressionDestroy(Expression *expr);
void FieldExprDestroy(FieldExpr *expr);
void ValueExprDestroy(ValueExpr *expr);
void CastExprDestroy(CastExpr *expr);
void ComparisonExprDestroy(ComparisonExpr *expr);
void ConjunctionExprDestroy(ConjunctionExpr *expr);
void ArithmeticExprDestroy(ArithmeticExpr *expr);
void AggrFuncExprDestroy(AggrFuncExpr *expr);
void SubQueryExprDestroy(SubQueryExpr *expr);
void ExprListExprDestroy(ExprListExpr *expr);

/* 销毁list数组Expression指针 */
void FieldExprPointerDestroy(void *data);
void ValueExprPointerDestroy(void *data);
void CastExprPointerDestroy(void *data);
void ComparisonExprPointerDestroy(void *data);
void ConjunctionExprPointerDestroy(void *data);
void ArithmeticExprPointerDestroy(void *data);
void AggrFuncExprPointerDestroy(void *data);
void SubQueryExprPointerDestroy(void *data);
void ExprListExprPointerDestroy(void *data);
void expressionPointerDestroy(void *data);

void        printExprTag(ExprTag tag);
void        printExpression(Expression *expr);
void        print_ComparisonExpr(ComparisonExpr *expr);
Expression *expressionMove(Expression **expr);
#endif /* EXPRESSION_H */
