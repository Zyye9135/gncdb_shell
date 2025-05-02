#ifndef PHYSICAL_PLAN_GENERATOR_H
#define PHYSICAL_PLAN_GENERATOR_H
#include "logical_operator.h"
#include "physical_operator.h"
#include "table_get_logical_operator.h"
#include "project_logical_operator.h"
#include "predicate_logical_operator.h"
#include "insert_logical_operator.h"
#include "delete_logical_operator.h"
#include "explain_logical_operator.h"
#include "join_logical_operator.h"
#include "calc_logical_operator.h"
#include "update_logical_operator.h"
#include "groupby_logical_operator.h"
#include "orderby_logical_operator.h"
#include "create_table_logical_operator.h"
#include "limit_logical_operator.h"
#include "physical_operator.h"
typedef struct NestedLoopJoinPhysicalOperator NestedLoopJoinPhysicalOperator;
int physicalPlanConstruct(SQLStageEvent *sqlEvent, LogicalOperator *logicalOperator, PhysicalOperator **physicalPlan);
int tableGetPhysicalPlanConstruct(
    SQLStageEvent *sqlEvent, TableGetLogicalOperator *tableGetOper, PhysicalOperator **physicalPlan);
int projectPhysicalPlanConstruct(
    SQLStageEvent *sqlEvent, ProjectLogicalOperator *projectOper, PhysicalOperator **physicalPlan);
int PredicatePhysicalPlanConstruct(
    SQLStageEvent *sqlEvent, PredicateLogicalOperator *projectOper, PhysicalOperator **physicalPlan);
int insertPhysicalPlanConstruct(
    SQLStageEvent *sqlEvent, InsertLogicalOperator *insertOper, PhysicalOperator **physicalPlan);
int deletePhysicalPlanConstruct(
    SQLStageEvent *sqlEvent, DeleteLogicalOperator *deleteOper, PhysicalOperator **physicalPlan);
int explainPhysicalPlanConstruct(
    SQLStageEvent *sqlEvent, ExplainLogicalOperator *explainOper, PhysicalOperator **physicalPlan);
int joinPhysicalPlanConstruct(SQLStageEvent *sqlEvent, JoinLogicalOperator *joinOper, PhysicalOperator **physicalPlan);
int calcPhysicalPlanConstruct(SQLStageEvent *sqlEvent, CalcLogicalOperator *calcOper, PhysicalOperator **physicalPlan);
int updatePhysicalPlanConstruct(
    SQLStageEvent *sqlEvent, UpdateLogicalOperator *updateOper, PhysicalOperator **physicalPlan);
int groupByPhysicalPlanConstruct(
    SQLStageEvent *sqlEvent, GroupByLogicalOperator *groupByOper, PhysicalOperator **physicalPlan);
int orderByPhysicalPlanConstruct(
    SQLStageEvent *sqlEvent, OrderByLogicalOperator *orderByOper, PhysicalOperator **physicalPlan);
int createTablePhysicalPlanConstruct(
    SQLStageEvent *sqlEvent, CreateTableLogicalOperator *createTableOper, PhysicalOperator **physicalPlan);
int limitPhysicalPlanConstruct(
    SQLStageEvent *sqlEvent, LimitLogicalOperator *limitOper, PhysicalOperator **physicalPlan);
#endif  // PHYSICAL_PLAN_GENERATOR_H