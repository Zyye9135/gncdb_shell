#ifndef LIMIT_H
#define LIMIT_H
#include "stmt.h"
typedef struct LimitStmt {
    StmtType type;
    int limit;  // -1 means no limit
    int offset; // -1 means no offset
} LimitStmt;


int LimitStmtConstruct(LimitSqlNode* limitNode, LimitStmt **stmt);

void LimitStmtDestroy(LimitStmt *limitStmt);
#endif // LIMIT_H