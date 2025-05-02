#ifndef PREDICATE_PUSHDOWN_REWRITER_H
#define PREDICATE_PUSHDOWN_REWRITER_H
#include "expression.h"
#include "rewriter.h"
int PredicatePushdownRewriter(LogicalOperator* oper, bool* changeMade);
int tryExprsPushdown(varArrayList* exprs, LogicalOperator* child, bool* changeMade);
#endif // PREDICATE_PUSHDOWN_REWRITER_H