#ifndef REWRITE_RULE_H
#define REWRITE_RULE_H
typedef enum RewriteRuleType
{
  RewriteRuleType_Invalid,
} RewriteRuleType;

typedef struct RewriteRule
{
  RewriteRuleType type;
} RewriteRule;

typedef enum ExpressionRewriteRuleType
{
  ExpressionRewriteRuleType_Invalid,
} ExpressionRewriteRuleType;
typedef struct ExpressionRewriteRule
{
  ExpressionRewriteRuleType type;
} ExpressionRewriteRule;
#endif  // REWRITE_RULE_H