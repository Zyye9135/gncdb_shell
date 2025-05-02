#ifndef OCEANBASE_SQL_OPTIMIZER_REWRITER_H_
#define OCEANBASE_SQL_OPTIMIZER_REWRITER_H_
#include "varArrayList.h"
typedef struct LogicalOperator LogicalOperator;
typedef struct Rewriter{
  varArrayList* rewriteRules; // element type:<RewriteRule*>
}Rewriter;
/**
 * @brief 对逻辑计划进行重写
 * @details 如果重写发生，changeMade为true，否则为false。
 * 通常情况下如果改写发生改变，就会继续重写，直到没有改变为止。
 * @param oper 逻辑计划
 * @param changeMade 当前是否有重写发生
 * @return int 
 */
int LogicalOperatorRewriter(LogicalOperator* oper, bool* changeMade);
#endif

