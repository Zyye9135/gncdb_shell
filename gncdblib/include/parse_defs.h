#ifndef PARSE_DEFS_H
#define PARSE_DEFS_H
#include "varArrayList.h"
#include "value.h"
typedef struct Expression Expression;
typedef struct ParsedSqlNode ParsedSqlNode;
// 描述一个属性
typedef struct RelAttrSqlNode {
    char *relationName;   // 表名
    char *attributeName;  // 属性名
} RelAttrSqlNode;


/* 描述比较运算符 */
typedef enum CompOp{
    CMPOP_INVALID,     // "="
    CMPOP_EQUAL_TO,     // "="
    CMPOP_LESS_EQUAL,   // "<="
    CMPOP_NOT_EQUAL,    // "<>"
    CMPOP_LESS_THAN,    // "<"
    CMPOP_GREAT_EQUAL,  // ">="
    CMPOP_GREAT_THAN,   // ">"
    CMPOP_LIKE_OP,      // like
    CMPOP_NOT_LIKE_OP,  // not like
    CMPOP_IN_OP,        ///< in (sub query)
    CMPOP_NOT_IN_OP,    ///< not in (sub query)
    CMPOP_EXISTS_OP,    ///< exists (sub query)
    CMPOP_NOT_EXISTS_OP,///< not exists (sub query)
    CMPOP_NO_OP,
} CompOp;

/**
 * @brief 表示一个条件比较
 * @ingroup SQLParser
 * @details 条件比较就是SQL查询中的 where a>b 这种。
 * 一个条件比较是有两部分组成的，称为左边和右边。
 * 左边和右边理论上都可以是任意的数据，比如是字段（属性，列），也可以是数值常量。
 * 这个结构中记录的仅仅支持字段和值。
 */
typedef struct ConditionSqlNode
{
  Expression *lhs;
  CompOp      comp;            ///< comparison operator
  Expression *rhs;
}ConditionSqlNode;



typedef struct OrderBySqlNode
{
  Expression * expr;
  bool isAsc;
}OrderBySqlNode;



/* <name, alias> */
typedef struct StringPair{
    char* name;
    char* alias;
} StringPair;
/**
 * @brief 描述一串 inner join
 * @ingroup SQLParser
 * @details t1 inner join t2 on cond1 inner join t3 on cond2.....
 */
typedef struct InnerJoinSqlNode
{
  StringPair* baseRelation;                 /* 例：t1 */
  varArrayList* joinRelations;              /* element type : <char*> */
                                            /* 例：t2,t3 */
  varArrayList* conditions;                 /* element type : <char*> */
                                            /* 例：cond1,cond2 */
}InnerJoinSqlNode;


typedef struct LimitSqlNode
{
  int offset; // 偏移量
  int limit;  // 限制数量
}LimitSqlNode;


// 描述一个select语句
typedef struct SelectSqlNode {
    varArrayList *projectExprs; // attributes in select clause,element type:<Expression *>
    varArrayList *relations;     // 查询的表,element type : <InnerJoinSqlNode>
    Expression   *conditions;    // 查询条件
    varArrayList* groupbyExprs; // element type : <Expression *>
    varArrayList* orderbyExprs; // element type : <OrderBySqlNode*>
    Expression *  havingConditions;  // having clause
    LimitSqlNode* limit;         // limit clause
    bool isDistinct;
} SelectSqlNode;


// 算术表达式计算的语法树
typedef struct CalcSqlNode {
    varArrayList *expressions;  // calc clause
} CalcSqlNode;


// 描述一个insert语句
typedef struct InsertSqlNode {
    char *relationName;  // Relation to insert into
    varArrayList* attributes; // element type :  <char *>
    varArrayList* valuelists; // element type : <varArrayList *>,element type : <Value>
} InsertSqlNode;


// 描述一个delete语句
typedef struct DeleteSqlNode {
    char *relationName;        // Relation to delete from
    Expression *conditions;
} DeleteSqlNode;


// 描述一个update语句
typedef struct UpdateKV
{
  char* attrName;
  Expression* value;
}UpdateKV;

typedef struct UpdateSqlNode {
    char *relationName;        
    varArrayList* attributeNames;
    varArrayList* values;
    Expression *conditions;
} UpdateSqlNode;



// 描述一个属性
typedef struct AttrInfoSqlNode {
    AttrType type;      
    char *name;         
    int length;         /* 字符串类型的长度 */
    bool isPrimaryKey;  
    bool canBeNull;   
} AttrInfoSqlNode;


// 描述一个create table语句
typedef struct CreateTableSqlNode {
    char *relationName;            // Relation name
    varArrayList *attrInfos;    // attributes
} CreateTableSqlNode;



// 描述一个drop table语句
typedef struct DropTableSqlNode {
    char *relationName;
    bool ifExists; /* 新增加的 'if_exists' 标志 */
} DropTableSqlNode;

// 描述一个create index语句
typedef struct CreateIndexSqlNode {
    char *indexName;       // Index name
    char *relationName;    // Relation name
    char *attributeName;   // Attribute name
} CreateIndexSqlNode;

// 描述一个drop index语句
typedef struct DropIndexSqlNode {
    char *indexName;      // Index name
    char *relationName;   // Relation name
} DropIndexSqlNode;


// 描述一个desc table语句
typedef struct DescTableSqlNode {
    char *relationName;
} DescTableSqlNode;


// 描述一个load data语句
typedef struct LoadDataSqlNode {
    char *relationName;
    char *fileName;
} LoadDataSqlNode;


// 设置变量的值
typedef struct SetVariableSqlNode {
    char *name;
    Value* value;
} SetVariableSqlNode;




// 描述一个explain语句
typedef struct ExplainSqlNode {
    ParsedSqlNode *sqlNode;
} ExplainSqlNode;




// 解析SQL语句出现了错误
typedef struct ErrorSqlNode {
    char *errorMsg;
    int line;
    int column;
} ErrorSqlNode;


// 表示一个SQL语句的类型
typedef enum SqlCommandFlag{
    SCF_ERROR = 0,
    SCF_CALC,
    SCF_SELECT,
    SCF_INSERT,
    SCF_UPDATE,
    SCF_DELETE,
    SCF_CREATE_TABLE,
    SCF_DROP_TABLE,
    SCF_CREATE_INDEX,
    SCF_DROP_INDEX,
    SCF_SYNC,
    SCF_SHOW_TABLES,
    SCF_DESC_TABLE,
    SCF_BEGIN,
    SCF_COMMIT,
    SCF_CLOG_SYNC,
    SCF_ROLLBACK,
    SCF_LOAD_DATA,
    SCF_HELP,
    SCF_EXIT,
    SCF_EXPLAIN,
    SCF_SET_VARIABLE,
} SqlCommandFlag;

// 表示一个SQL语句
typedef struct ParsedSqlNode {
    SqlCommandFlag flag;
    ErrorSqlNode* error;
    CalcSqlNode* calc;
    SelectSqlNode* selection;
    InsertSqlNode* insertion;
    DeleteSqlNode* deletion;
    UpdateSqlNode* update;
    CreateTableSqlNode* createTable;
    DropTableSqlNode* dropTable;
    CreateIndexSqlNode* createIndex;
    DropIndexSqlNode* dropIndex;
    DescTableSqlNode* descTable;
    LoadDataSqlNode* loadData;
    ExplainSqlNode* explain;
    SetVariableSqlNode* setVariable;
} ParsedSqlNode;

// 表示语法解析后的数据
typedef struct ParsedSqlResult {
    varArrayList *sqlNodes;
    size_t count;
} ParsedSqlResult;


void RelAttrSqlNodeInit(RelAttrSqlNode* sqlNode);
void ConditionSqlNodeInit(ConditionSqlNode* sqlNode);
void SelectSqlNodeInit(SelectSqlNode* sqlNode);
void CalcSqlNodeInit(CalcSqlNode* sqlNode);
void InsertSqlNodeInit(InsertSqlNode* sqlNode);
void DeleteSqlNodeInit(DeleteSqlNode* sqlNode);
void UpdateSqlNodeInit(UpdateSqlNode* sqlNode);
void AttrInfoSqlNodeInit(AttrInfoSqlNode* sqlNode);
void CreateTableSqlNodeInit(CreateTableSqlNode* sqlNode);
void DropTableSqlNodeInit(DropTableSqlNode* sqlNode);
void CreateIndexSqlNodeInit(CreateIndexSqlNode* sqlNode);
void DropIndexSqlNodeInit(DropIndexSqlNode* sqlNode);
void DescTableSqlNodeInit(DescTableSqlNode* sqlNode);
void LoadDataSqlNodeInit(LoadDataSqlNode* sqlNode);
void SetVariableSqlNodeInit(SetVariableSqlNode* sqlNode);
void ExplainSqlNodeInit(ExplainSqlNode* sqlNode);
void ErrorSqlNodeInit(ErrorSqlNode* sqlNode);
void ParsedSqlResultInit(ParsedSqlResult* sqlNode);

// parsedSqlNode添加函数
int ParsedSqlResultAdd(ParsedSqlResult *result, ParsedSqlNode *sqlNode);


// 结构体打印函数
void printParsedSqlNode(ParsedSqlNode *node);





/* 结构体指针创建函数 */
RelAttrSqlNode* RelAttrSqlNodeCreate(char* relationName, char* attributeName);
ConditionSqlNode* ConditionSqlNodeCreate(Expression* leftExpr, CompOp comp, Expression* rightExpr);
OrderBySqlNode* OrderBySqlNodeCreate(Expression* expr, bool orderType);
StringPair* StringPairCreate(char* first, char* second);
InnerJoinSqlNode* InnerJoinSqlNodeCreate(StringPair* baseRelation, varArrayList* joinRelations, varArrayList* conditions);
LimitSqlNode* LimitSqlNodeCreate(int limit, int offset);
SelectSqlNode* SelectSqlNodeCreate(varArrayList* projectExprs, varArrayList* relations, Expression* conditions, varArrayList* groupbyExprs, varArrayList* orderbyExprs, Expression* havingConditions, LimitSqlNode* limit);
CalcSqlNode* CalcSqlNodeCreate(varArrayList* expressions);
InsertSqlNode* InsertSqlNodeCreate(char* relationName, varArrayList* attributes, varArrayList* valuelists);
DeleteSqlNode* DeleteSqlNodeCreate(char* relationName, Expression* conditions);
UpdateKV* UpdateKVCreate(char* attrName, Expression* value);
UpdateSqlNode* UpdateSqlNodeCreate(char* relationName, varArrayList* attributeNames, varArrayList* values, Expression* conditions);
AttrInfoSqlNode* AttrInfoSqlNodeCreate(AttrType type, char* name, size_t length, bool is_primary_key, bool canBeNull);
CreateTableSqlNode* CreateTableSqlNodeCreate(char* relationName, varArrayList* attrInfos);
DropTableSqlNode* DropTableSqlNodeCreate(char* relationName, bool ifExists);
CreateIndexSqlNode* CreateIndexSqlNodeCreate(char* indexName, char* relationName, char* attributeName);
DropIndexSqlNode* DropIndexSqlNodeCreate(char* indexName, char* relationName);
DescTableSqlNode* DescTableSqlNodeCreate(char* relationName);
LoadDataSqlNode* LoadDataSqlNodeCreate(char* relationName, char* fileName);
SetVariableSqlNode* SetVariableSqlNodeCreate(char* name, Value* value);
ExplainSqlNode* ExplainSqlNodeCreate(ParsedSqlNode* sqlNode);
ErrorSqlNode* ErrorSqlNodeCreate(char* errorMsg);
ParsedSqlResult* ParsedSqlResultCreate(varArrayList* sqlNodes, size_t count);
ParsedSqlNode* ParsedSqlNodeCreate(SqlCommandFlag flag);

/* 结构体销毁函数 */
void RelAttrSqlNodeDestroy(RelAttrSqlNode* sqlNode);
void ConditionSqlNodeDestroy(ConditionSqlNode* sqlNode);
void OrderBySqlNodeDestroy(OrderBySqlNode* sqlNode);
void StringPairDestroy(StringPair* sqlNode);
void InnerJoinSqlNodeDestroy(InnerJoinSqlNode* sqlNode);
void LimitSqlNodeDestroy(LimitSqlNode* sqlNode);
void SelectSqlNodeDestroy(SelectSqlNode* sqlNode);
void CalcSqlNodeDestroy(CalcSqlNode* sqlNode);
void InsertSqlNodeDestroy(InsertSqlNode* sqlNode);
void DeleteSqlNodeDestroy(DeleteSqlNode* sqlNode);
void UpdateKVDestroy(UpdateKV* sqlNode);
void UpdateSqlNodeDestroy(UpdateSqlNode* sqlNode);
void AttrInfoSqlNodeDestroy(AttrInfoSqlNode* sqlNode);
void CreateTableSqlNodeDestroy(CreateTableSqlNode* sqlNode);
void DropTableSqlNodeDestroy(DropTableSqlNode* sqlNode);
void CreateIndexSqlNodeDestroy(CreateIndexSqlNode* sqlNode);
void DropIndexSqlNodeDestroy(DropIndexSqlNode* sqlNode);
void DescTableSqlNodeDestroy(DescTableSqlNode* sqlNode);
void LoadDataSqlNodeDestroy(LoadDataSqlNode* sqlNode);
void SetVariableSqlNodeDestroy(SetVariableSqlNode* sqlNode);
void ExplainSqlNodeDestroy(ExplainSqlNode* sqlNode);
void ErrorSqlNodeDestroy(ErrorSqlNode* sqlNode);
void ParsedSqlResultDestroy(ParsedSqlResult* sqlNode);
void ParsedSqlNodeDestroy(ParsedSqlNode *node);


/* 结构体指针销毁函数 */
void RelAttrSqlNodePointerDestroy(void* data);
void ConditionSqlNodePointerDestroy(void* data);
void OrderBySqlNodePointerDestroy(void* data);
void StringPairPointerDestroy(void* data);
void InnerJoinSqlNodePointerDestroy(void* data);
void LimitSqlNodePointerDestroy(void* data);
void SelectSqlNodePointerDestroy(void* data);
void CalcSqlNodePointerDestroy(void* data);
void InsertSqlNodePointerDestroy(void* data);
void DeleteSqlNodePointerDestroy(void* data);
void UpdateKVPointerDestroy(void* data);
void UpdateSqlNodePointerDestroy(void* data);
void AttrInfoSqlNodePointerDestroy(void* data);
void CreateTableSqlNodePointerDestroy(void* data);
void DropTableSqlNodePointerDestroy(void* data);
void CreateIndexSqlNodePointerDestroy(void* data);
void DropIndexSqlNodePointerDestroy(void* data);
void DescTableSqlNodePointerDestroy(void* data);
void LoadDataSqlNodePointerDestroy(void* data);
void SetVariableSqlNodePointerDestroy(void* data);
void ExplainSqlNodePointerDestroy(void* data);
void ErrorSqlNodePointerDestroy(void* data);
void ParsedSqlNodePointerDestroy(void*data) ;
void ParsedSqlResultPointerDestroy(void*data);
void valuelistsPointerDestroy(void* data);
void charPointerDestroy(void* data);


/* 结构体深拷贝函数 */
AttrInfoSqlNode* AttrInfoSqlNodeDeepCopy(AttrInfoSqlNode* sqlNode);

/* 指针move函数 */
void* pointerMove(void** data);
RelAttrSqlNode* RelAttrSqlNodeMove(RelAttrSqlNode** sqlNode);
ConditionSqlNode* ConditionSqlNodeMove(ConditionSqlNode** sqlNode);
OrderBySqlNode* OrderBySqlNodeMove(OrderBySqlNode** sqlNode);
StringPair* StringPairMove(StringPair** sqlNode);
InnerJoinSqlNode* InnerJoinSqlNodeMove(InnerJoinSqlNode** sqlNode);
LimitSqlNode* LimitSqlNodeMove(LimitSqlNode** sqlNode);
SelectSqlNode* SelectSqlNodeMove(SelectSqlNode** sqlNode);
CalcSqlNode* CalcSqlNodeMove(CalcSqlNode** sqlNode);
InsertSqlNode* InsertSqlNodeMove(InsertSqlNode** sqlNode);
DeleteSqlNode* DeleteSqlNodeMove(DeleteSqlNode** sqlNode);
UpdateKV* UpdateKVMove(UpdateKV** sqlNode);
UpdateSqlNode* UpdateSqlNodeMove(UpdateSqlNode** sqlNode);
AttrInfoSqlNode* AttrInfoSqlNodeMove(AttrInfoSqlNode** sqlNode);
CreateTableSqlNode* CreateTableSqlNodeMove(CreateTableSqlNode** sqlNode);
DropTableSqlNode* DropTableSqlNodeMove(DropTableSqlNode** sqlNode);
CreateIndexSqlNode* CreateIndexSqlNodeMove(CreateIndexSqlNode** sqlNode);
DropIndexSqlNode* DropIndexSqlNodeMove(DropIndexSqlNode** sqlNode);
DescTableSqlNode* DescTableSqlNodeMove(DescTableSqlNode** sqlNode);
LoadDataSqlNode* LoadDataSqlNodeMove(LoadDataSqlNode** sqlNode);
SetVariableSqlNode* SetVariableSqlNodeMove(SetVariableSqlNode** sqlNode);
ExplainSqlNode* ExplainSqlNodeMove(ExplainSqlNode** sqlNode);
ErrorSqlNode* ErrorSqlNodeMove(ErrorSqlNode** sqlNode);
ParsedSqlResult* ParsedSqlResultMove(ParsedSqlResult** sqlNode);
ParsedSqlNode* ParsedSqlNodeMove(ParsedSqlNode** sqlNode);
    

#endif // PARSE_DEFS_H
