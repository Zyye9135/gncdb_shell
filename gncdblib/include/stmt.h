#ifndef STMT_H
#define STMT_H
#include "sql_event.h"
typedef enum StmtType
{
  ST_CALC,
  ST_SELECT,
  ST_INSERT,
  ST_UPDATE,
  ST_DELETE,
  ST_CREATE_TABLE,
  ST_DROP_TABLE,
  ST_CREATE_INDEX,
  ST_DROP_INDEX,
  ST_SYNC,
  ST_SHOW_TABLES,
  ST_DESC_TABLE,
  ST_BEGIN,
  ST_COMMIT,
  ST_ROLLBACK,
  ST_LOAD_DATA,
  ST_HELP,
  ST_EXIT,
  ST_EXPLAIN,
  ST_PREDICATE,
  ST_SET_VARIABLE,
  ST_JOIN_TABLES,
  ST_GROUP_BY,
  ST_ORDER_BY,
  ST_LIMIT,
} StmtType;

typedef struct Stmt
{
  StmtType type;
} Stmt;

int  StmtConstruct(SQLStageEvent *sqlEvent, Stmt **stmt);
void StmtDestroy(Stmt *stmt);

#endif /* STMT_H */
