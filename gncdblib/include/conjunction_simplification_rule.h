#ifndef CONJUNCTION_SIMPLIFICATION_RULE_H
#define CONJUNCTION_SIMPLIFICATION_RULE_H
#include "expression.h"
int ConjunctionSimplificationRewriter(void* exprPtr,Expression** expr, bool* changeMade);
#endif  // CONJUNCTION_SIMPLIFICATION_RULE_H