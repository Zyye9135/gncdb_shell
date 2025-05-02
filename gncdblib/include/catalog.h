#ifndef _CATALOG_H_
#define _CATALOG_H_

#include "typedefine.h"
#include "vararraylist.h"
#include "hashmap.h"
#include "gncdbconstant.h"
#include "btreecursor.h"

struct RtreeTable;
/* 列约束 */
typedef struct ColumnConstraint 
{
	double minValue, maxValue;		/* 字段最大最小值*/
	int canBeNull;					 /* 可否为NULL*/
	int isPrimaryKey;				 /* 是否为主键*/
}ColumnConstraint; 

/* 列信息 */
typedef struct Column 
{
	FieldType fieldType;					 /* 字段类型 */
	char* fieldName;						 /* 字段名称 */
	ColumnConstraint* columnConstraint;		 /* 字段的约束条件 */
}Column;

/* 表信息 */
typedef struct TableSchema 
{
	int maxRowNum;					/* 最大行数*/
	int columnNum;					/* 列数*/
	int rowId;						/* rowId */
	int tableParam;					/* 表的类型 可读0 可写1 可读可写2 */
	struct varArrayList* columnList;		/* 各列的信息 list*/
}TableSchema;


typedef struct Catalog
{
	struct HashMap* tableMap;							/* 所有表的集合 key tableName, value btreeTable */
    ReadWriteLock tableMapLatch;						/* 保护tableMap */
    struct HashMap* indexMap;							/* 索引的集合*/
    ReadWriteLock indexMapLatch;						/* 保护indexMap */
	struct HashMap* tablePrimaryKeyIndexMap;			/* 主键的列号 key是tablename，value是primarykey的值 */
    ReadWriteLock keyIndexLatch;						/* 保护tablePrimaryKeyIndexMap */
    struct HashMap* tablePrimaryKeyTypeMap;			/* 主键的类型 key是tablename， value是primarykey的类型 */
    ReadWriteLock keyTypeLatch;						/* 保护tablePrimaryKeyTypeMap */
    struct HashMap* indexSchemaMap;					/* 索引schema的集合 */
    ReadWriteLock indexSchemaLatch;						/* 保护indexSchemaMap */
	struct HashMap* tableSchemaMap;					/* 表schema  key tableName, value tableSchema */
    ReadWriteLock tableSchemaLatch;						/* 保护tableSchemaMap */
    int masterCurrentMaxId;						/* master表的最大id */
	struct TableSchema* masterTableSchema;      /* master的表头信息 */
	struct BtreeTable* masterTable;             /* master表 */
    int schemaCurrentMaxIncId;					/* schema最大id */
	struct TableSchema* schemaTableSchema;      /* schema的表头信息 */
	struct BtreeTable* schemaTable;             /* schema表 */
    ReadWriteLock latch;						/* 保护共享资源 */

	struct HashMap* tableStatsMap;				/* 表统计信息 */
}Catalog;

/* 获取主键的下标array */
varArrayList* getPrimaryIndexArray(struct Catalog* catalog, char* tableName);
/* 获取主键的类型array */
varArrayList* getPrimaryTypeArray(struct Catalog* catalog, char* tableName);
/* 创建一个主键下标array */
int createPrimaryIndex(struct varArrayList* primaryIndexArray, struct TableSchema* tableSchema);
/* 创建一个主键类型array */
int createPrimaryType(struct varArrayList* primaryTypeArray, struct TableSchema* tableSchema);
/* 列约束构造函数 */
ColumnConstraint* columnConstraintConstruct(double minValue, double maxValue, int canBeNull, int isPrimaryKey);
/* 列信息构造函数 */
Column* columnConstruct(FieldType fieldType, char* fieldName, struct ColumnConstraint* columnConstraint);
/* 增加masterid */
int masterCurrentMaxIdAdd(struct Catalog* catalog);
/* 增加schemaid */
int schemaCurrentMaxIncIdAdd(struct Catalog* catalog);
/* TableSchema构造函数 */
TableSchema* tableSchemaConstruct(int maxRowNum, int columnNum, varArrayList* columnList);
/* 合并两个表的TableSchema */
int tableSchemaMerge(TableSchema** ts1, TableSchema* ts2, TableSchema* ts3);
/* 获取一个表的TableSchema */
TableSchema* getTableSchema(struct Catalog* catalog, char* tableName);
/* 获取一个表的primaryKeyIndex */
varArrayList* getPrimaryKeyIndex(struct Catalog* catalog, char* tableName);
/* 获取一个表的primaryKeyType */
varArrayList* getPrimaryKeyType(struct Catalog* catalog, char* tableName);
/* catalog构造函数 */
int catalogConstruct(struct GNCDB* db);
/* 列约束销毁函数 */
void columnConstraintDestroy(struct ColumnConstraint* columnConstraint);
/* 列销毁函数 */
void columnDestroy(struct Column* column);
/* TableSchema销毁函数 */
void tableSchemaDestroy(struct TableSchema* tableSchema);
/* catalog销毁函数*/
void catalogDestroy(struct Catalog* catalog);
/* 解析master和schema，为所有表生成对应TableSchema */
int catalogParseMasterAndSchema(struct GNCDB* db, struct Transaction* tx);
/* catalog增加一个表 */
int catalogAddTable(char* name, struct BtreeTable* table, struct Transaction* tx, struct GNCDB* db);
/* catalog销毁表 */
int catalogDeleteTable(char* name, struct Transaction* tx, struct GNCDB* db);
/* 判断表是否存在 */
int catalogIsTableExist(struct Catalog* catalog, char* tableName);
/* 获取master的TableSchema */
int catalogGetMasterTableSchema(struct Catalog* catalog);
/* 获取schema的TableSchema */
int catalogGetSchemaTableSchema(struct Catalog* catalog);
/* 获取一张表 */
int catalogGetTable(struct Catalog* catalog, struct BtreeTable** btreeTable, char* name);
/* 判断fieldname是否存在 */
int columnFindFieldExist(varArrayList* array, char* fieldName);
/* 获取fieldName的下标 */
int columnFindFieldGet(varArrayList* array, char* fieldName);
/* 通过tableSchema获取fieldName的下标 */
int tableSchemaGetIndex(struct TableSchema* tableSchema, char* fieldName);
/* 通过tableSchema获取fieldName的的类型 */
int tableSchemaGetFieldType(struct TableSchema* tableSchema, char* fieldName);
// 总页数增加
void totalPageNumAdd(struct GNCDB* db);

void arrayColumnDestroy(void* arg);
//R树相关接口
int catalogGetRtreeTable(struct Catalog* catalog, struct RtreeTable** rtreeTable, char* name);

TableSchema* getIndexTableSchema(struct Catalog* catalog,char* indexName) ;

int catalogGetIndexName(struct GNCDB* db, struct varArrayList* indexNameArray, char* tableName, 
	struct Transaction* tx);

int catalogAddRtreeTable(struct GNCDB* db, char* tableName, 
	char* indexName, struct RtreeTable* table, struct Transaction* tx);

int catalogGetDependentTableName(struct GNCDB* db, char* indexName, char** tableName, struct Transaction* tx);
void printColumnConstraint(const ColumnConstraint *cc);

char* catalogGetCreateTableSql(TableSchema* tableSchema, char* tableName);

#endif