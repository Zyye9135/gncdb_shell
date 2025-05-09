/*
 * @Author: zql 1901227828@qq.com
 * @Date: 2025-01-09 09:32:28
 * @LastEditors: zql 1901227828@qq.com
 * @LastEditTime: 2025-01-13 20:34:19
 * @FilePath: /linux_dev/query_processing/sql/optimizer/histogram.h
 * @Description: 统计直方图的结构体和相关函数接口
 */
#ifndef HISTOGRAM_H
#define HISTOGRAM_H

#define MEMORY_LIMIT 100 << 10 << 10  // 100MB

#include "hashmap.h"
#include "btreetable.h"
#include "gncdb.h"
#include "pagepool.h"
#include "parse_defs.h"
#include "transaction.h"
#include "tuple.h"
#include <math.h>

//* 数值型柱状图，当前仅支持int、real、date、datetime（转换为时间戳）
typedef struct NumericalHistogram
{
  FieldType col_type;    //* 列的数据类型
  void     *min;         //* 柱状图最左侧元素的值
  void     *max;         //* 柱状图最右侧元素的值
  void     *width;       //* 柱形宽度
  int       tuple_sum;   //* 元组的总和
  int       bucket_num;  //* 桶数量
  int      *buckets;     //* 桶数组
} NumericalHistogram;

/**
 * @description: 创建一个直方图
 * @param {NumericalHistogram} * 直方图结构体指针
 * @param {FieldType} col_type 列的数据类型
 * @param {int} bucket_num 桶的数量
 * @param {void} *min 列的最小值
 * @param {void} *max 列最大值
 * @return {*} 状态码
 */
int create_numerical_histogram(NumericalHistogram **hist, FieldType col_type, int bucket_num, void *min, void *max);

/**
 * @description: 销毁一个直方图，不对min、max成员进行释放，因为是由上层他table_stats申请分配的
 * @param {void} *ptr 为了适配arrayList的销毁函数，实际上传入的必须是NumericalHistogram **
 * @return {*} 无
 */
void destroy_numerical_histogram(void *ptr);

/**
 * @description:  根据直方图计算选择的比例
 * @param {NumericalHistogram} **hist 直方图结构体指针
 * @param {CompOp} op 比较操作符，当前仅支持 = <> < <= > >=
 * @param {void} *value 比较的值，当前仅支持int、real、date、datetime
 * @return {*} 选择的比例
 */
double estimate_selectivity(NumericalHistogram *hist, CompOp op, void *value);

int add_field_value(NumericalHistogram *hist, Field *field);

#endif
