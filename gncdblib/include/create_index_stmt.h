#ifndef CREATE_INDEX_STMT_H
#define CREATE_INDEX_STMT_H
#include "stmt.h"
#include "parse_defs.h"
typedef struct CreateIndexStmt{
    StmtType type;
}CreateIndexStmt;

int CreateIndexStmtConstruct(GNCDB *db, CreateIndexSqlNode* createIndex, Stmt** stmt);
void CreateIndexStmtDestroy(CreateIndexStmt* createIndexStmt);
#endif