#ifndef COMPARISON_SIMPLIFICATION_RULE_H
#define COMPARISON_SIMPLIFICATION_RULE_H
#include "expression.h"
int ComparisonSimplificationRewriter(void *exprPtr, Expression **expr, bool *changeMade);
#endif  // COMPARISON_SIMPLIFICATION_RULE_H