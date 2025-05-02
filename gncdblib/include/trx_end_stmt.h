#ifndef TRX_END_STMT_H
#define TRX_END_STMT_H
#include "stmt.h"
typedef struct TrxEndStmt{
  StmtType type;
}TrxEndStmt;

int TrxEndStmtConstruct(SqlCommandFlag flag, Stmt **stmt);

void TrxEndStmtDestroy(TrxEndStmt* trxEndStmt);
#endif