#ifndef LOGICAL_OPERATOR_H
#define LOGICAL_OPERATOR_H
#include "expression.h"
#include "varArrayList.h"
typedef enum LogicalOperatorType
{
    LO_CALC,
    LO_TABLE_GET,  ///< 从表中获取数据
    LO_PREDICATE,  ///< 过滤，就是谓词
    LO_PROJECTION, ///< 投影，就是select
    LO_JOIN,       ///< 连接
    LO_INSERT,     ///< 插入
    LO_DELETE,     ///< 删除，删除可能会有子查询
    LO_EXPLAIN,    ///< 查看执行计划
    LO_UPDATE,     ///< 更新
    LO_GROUPBY,    ///< 分组
    LO_ORDERBY,    ///< 排序
    LO_CREATE_TABLE, ///< 创建表
    LO_LIMIT,      ///< 限制返回的行数
} LogicalOperatorType;

typedef struct LogicalOperator{
    LogicalOperatorType type;
    varArrayList* children;       ///< 子算子element type:<LogicalOperator*>
    varArrayList* expressions;    ///< 表达式，比如select中的列，where中的谓词等等，都可以使用表达式来表示element type:<Expression*>
                                    ///< 表达式能是一个常量，也可以是一个函数，也可以是一个列，也可以是一个子查询等等
}LogicalOperator;


void LogicalOperatorToString(LogicalOperator* logical_operator, int depth);
void LogicalOperatorDestroy(LogicalOperator* logical_operator);
void LogicalOperatorPointerDestroy(void* data);
void LogicalPlanDestroy(LogicalOperator* logOper);
LogicalOperator* LogicalOperatorMove(LogicalOperator** logical_operator);
#endif // LOGICAL_OPERATOR_H