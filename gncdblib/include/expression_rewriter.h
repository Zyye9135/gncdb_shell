#ifndef EXPRESSION_REWRITER_H
#define EXPRESSION_REWRITER_H
#include "logical_operator.h"
int ExpressionRewriter(LogicalOperator *oper, bool *changeMade);
int RewriteExpression(void *expr_ptr, Expression **expr, bool *changeMade);
#endif  // EXPRESSION_REWRITER_H