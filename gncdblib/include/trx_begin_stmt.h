#ifndef TRX_BEGIN_STMT_H
#define TRX_BEGIN_STMT_H
#include "stmt.h"
typedef struct TrxBeginStmt{
  StmtType type;
}TrxBeginStmt;

int TrxBeginStmtConstruct(Stmt** stmt);
void TrxBeginStmtDestroy(TrxBeginStmt* txnBeginStmt);
#endif