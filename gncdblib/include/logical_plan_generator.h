#ifndef LOGICAL_PLAN_GENERATOR_H
#define LOGICAL_PLAN_GENERATOR_H
#include "calc_stmt.h"
#include "select_stmt.h"
#include "filter_stmt.h"
#include "insert_stmt.h"
#include "delete_stmt.h"
#include "explain_stmt.h"
#include "logical_operator.h"
#include "update_stmt.h"
int logicalPlanConstruct(SQLStageEvent* sqlEvent, Stmt *stmt, LogicalOperator **logicalOperator);
int calcLogicalPlanConstruct(SQLStageEvent* sqlEvent, CalcStmt *calcStmt, LogicalOperator **logicalOperator);
int selectLogicalPlanConstruct(SQLStageEvent* sqlEvent, SelectStmt *selectStmt, LogicalOperator **logicalOperator);
int filterLogicalPlanConstruct(SQLStageEvent* sqlEvent, FilterStmt *filterStmt, LogicalOperator **logicalOperator);
int insertLogicalPlanConstruct(SQLStageEvent* sqlEvent, InsertStmt *insertStmt, LogicalOperator **logicalOperator);
int deleteLogicalPlanConstruct(SQLStageEvent* sqlEvent, DeleteStmt *deleteStmt, LogicalOperator **logicalOperator);
int explainLogicalPlanConstruct(SQLStageEvent* sqlEvent, ExplainStmt *explainStmt, LogicalOperator **logicalOperator);
int updateLogicalPlanConstruct(SQLStageEvent* sqlEvent, UpdateStmt *updateStmt, LogicalOperator **logicalOperator);
int groupbyLogicalPlanConstruct(SQLStageEvent* sqlEvent, GroupByStmt *groupbyStmt, LogicalOperator **logicalOperator);
int createTableLogicalPlanConstruct(SQLStageEvent* sqlEvent, CreateTableStmt *createTableStmt, LogicalOperator **logicalOperator);
void LogicalPlanInit(LogicalOperator **logicalOperator);
#endif