/*
* @ProjectName: HashMap.h
*
* @Author: xidb
* @Createtime: 2023-1-31  13:30
* @LastEditor: xidb
* @LastEditTime:
*/

#ifndef _HASHMAP_H_
#define _HASHMAP_H_

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include "gncdbConstant.h"

/* key值类型 */
#define INTKEY 1
#define STRKEY 2
// 自定义key值类型
#define CUSTOMKEY 3
/* 默认初始值为可保存10个键值对 */
#define DEFAULTCAPACITY 10
/* 可缩容至最小的容量 */
#define MINCAPACITY  5

#define HASH_EXPAND(cap) (2*cap)				/* 扩大内存 */
#define HSAH_REDUCE(cap) (cap/2)				/* 缩小内存 */

struct HashMap;
/* 哈希函数类型 */
typedef int(*HashCode)(struct HashMap* hashMap, void* key);
/* 判等函数类型 */
typedef bool(*Equal)(void* key1, void* key2);

/* 键值对结构体 */
typedef struct Entry 
{
	void* key;					/* 键 */
	void* value;				/* 值 */ 
	struct Entry* next;			/* 冲突链表 */ 
}Entry;

// 哈希结构体
typedef struct HashMap
{
	int bucketNum;				/* 空间大小 */ 
	int entryCount;				/* 当前大小 */
	int keyType;				/* key值类型 */
	struct Entry* bucketList;	/* 存储区域 */

	bool autoAssign;			/* 设定是否根据当前数据量动态调整内存大小，默认开启 */

	HashCode hashCode;			/* 哈希函数 */
	Equal equal;				/* 判等函数 */
}HashMap;

/* 迭代器结构体 */
typedef struct HashMapIterator {
	struct Entry* entry;				/* 迭代器当前指向 */
	int count;					/* 迭代次数 */
	int index;				/* 键值对的哈希值 */
	struct HashMap* hashMap;
}HashMapIterator;

 /* 存储值列表 */
typedef struct HashMapValueList {
    void** values;   /* 指向值数组的指针 */
    int size;        /* 值的数量 */
} HashMapValueList;

// 创建一个哈希结构
HashMap* hashMapCreate(int keyType, int fixBuck, HashCode hashCode);
// 销毁map
void hashMapDestroy(HashMap** hashMap);
// 默认哈希函数
//static int defaultHashCode(HashMap* hashMap, void* key);
// 判断键是否存在
bool hashMapExists(HashMap* hashMap, void* key);
// 添加键值对
int hashMapPut(HashMap* hashMap, void* key, void* value);
// 获取键对应值
void* hashMapGet(HashMap* hashMap, void* key);
// 删除键
int hashMapRemove(HashMap* hashMap, void* key);
// 清空Map
void hashMapClear(HashMap* hashMap);
// 将哈希表重新构建
void hashMapReset(HashMap* hashMap, int listSize);

// 创建哈希结构迭代器
HashMapIterator* createHashMapIterator(HashMap* hashMap);
// 迭代器是否有下一个
bool hasNextHashMapIterator(HashMapIterator* iterator);
// 迭代到下一次
HashMapIterator* nextHashMapIterator(HashMapIterator* iterator);
// 释放迭代器内存
void freeHashMapIterator(HashMapIterator** iterator);

int myHashMapPut(HashMap* hashMap, void* key, void* value);
HashMapValueList* myHashMapGet(HashMap* hashMap, void* key);
int myhashMapCount(HashMap* hashMap, void* key);
#endif // 
