/*
 * @Author: zql 1901227828@qq.com
 * @Date: 2025-01-08 20:36:56
 * @LastEditors: zql 1901227828@qq.com
 * @LastEditTime: 2025-02-26 11:09:59
 * @FilePath: /linux_dev/query_processing/sql/optimizer/table_stats.h
 * @Description: 统计计算表的基数和代价的相关结构体和函数接口
 */
#ifndef TABLE_STATS_H
#define TABLE_STATS_H
#include "gncdb.h"
#include "histogram.h"
#include "vararraylist.h"
#include "btreetable.h"
#include <math.h>

#define DEFAULT_IO_COST_PER_PAGE 1000
#define DEFAULT_NUM_HIST_BINS 100

typedef struct TableStats
{
  GNCDB        *db;
  int           page_count;       //* 页面数量
  double        in_mem_rate;      //* 内存占比
  int           tuple_count;      //* 元组数量
  varArrayList *histograms;       //* 每个字段一个直方图
  varArrayList *field_max;        //* 每个字段最大值
  varArrayList *field_min;        //* 每个字段最小值
} TableStats;

/**
 * @description: 创建表统计信息：获取页面数量、元组数量、字段最大最小值、将数据填充到直方图
 * @param {TableStats} * 表统计信息结构体二重指针
 * @param {char} *table_name 表名
 * @param {int} io_cost_per_page 每页IO代价
 * @param {GNCDB} *db 数据库实例指针
 * @param {Transaction} *tx 事务结构体指针
 * @return {*} 状态码
 */
int create_table_stats(TableStats **stats, char *table_name, GNCDB *db, Transaction *tx);

/**
 * @description: 销毁表统计信息，此处将直方图、最大、最小值全部释放
 * @param {TableStats} * 表统计信息结构体二重指针
 * @return {*} 无
 */
void destroy_table_stats(TableStats **stats);

/**
 * @description: 估计表扫描的代价
 * @param {TableStats} *stats 表统计信息结构体指针
 * @return {*} 代价
 */
int tableStatsEstimateScanCost(TableStats *stats);

/**
 * @description: 估计表的基数
 * @param {TableStats} *stats 表统计信息结构体指针
 * @param {double} filterSelectivities 选择的比例
 * @return {*} 基数
 */
int tableStatsEstimateCardinality(TableStats *stats, double filterSelectivities);

/**
 * @description: 估计表的col_index列的选择比列
 * @param {TableStats} *stats 表统计信息结构体指针
 * @param {int} col_index 列索引
 * @param {CompOp} op 比较操作符
 * @param {void} *value 比较的值
 * @return {*} 选择比例
 */
double tableStatsEstimateSelectivity(TableStats *stats, int col_index, CompOp op, void *value);
#endif  // TABLE_STATS_H