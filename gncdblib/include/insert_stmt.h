#ifndef INSERT_STMT_H
#define INSERT_STMT_H

#include "btreetable.h"
#include "gncdb.h"
#include "parse_defs.h"
#include "stmt.h"
#include "varArrayList.h"
typedef struct InsertStmt {
    StmtType type;
    BtreeTable *table;
    varArrayList *valuelists; /* 插入的值ValueList */
    int valueCount;
}InsertStmt;

int InsertStmtConstruct(GNCDB *db, InsertSqlNode *inserts, Stmt **stmt);
void InsertStmtDestroy(InsertStmt *stmt);
#endif /* INSERT_STMT_H */
