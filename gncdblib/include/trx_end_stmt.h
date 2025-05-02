#ifndef TRX_END_STMT_H
#define TRX_END_STMT_H
#include "stmt.h"
enum SqlCommandFlag;
typedef struct TrxEndStmt
{
  StmtType type;
} TrxEndStmt;

int TrxEndStmtConstruct(enum SqlCommandFlag flag, Stmt **stmt);

void TrxEndStmtDestroy(TrxEndStmt *trxEndStmt);
#endif