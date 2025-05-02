#ifndef _VARARRAYLIST_H_
#define _VARARRAYLIST_H_

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "gncdbConstant.h"
typedef struct Value Value;

/* 默认初始容量 */
#define DEFAULTCAPACITY 10
/* 容量最小限制 */ 
#define MINCAPACITY 5

/* 标记 */
#define ORDER 1
#define DISORDER 0

/* 内存管理标记 */
#define EXPAND 4								/* 内存不足 */
#define REDUCE 5								/* 内存冗余 */
#define MEM_EXPAND(cap) (cap*1.5)				/* 扩大内存 */
#define MEM_REDUCE(cap) (cap*0.5)				/* 缩小内存 */

struct varArrayList;
/* 比较函数和销毁函数类型 */
typedef int (*Compare)(struct varArrayList*, void*, void*);
typedef void (*Destroy)(void*);

typedef enum NodeTag
{
	T_Invalid = 0,
	T_Struct_Array,
	T_Pointer_Array,
	T_RelAttrSqlNode,
	T_ConditionSqlNode,
	T_Expression,
	T_Value,
	T_AttrInfoSqlNode,
	T_ParsedSqlNode,
	T_ParsedSqlNodePtr,
	T_String,
	T_ExpressionPtr,
} NodeTag;

/* varArrayList结构体 */
typedef struct varArrayList
{
	NodeTag		type;						    /* 存储的类型 */							
	int capacity;								/* varArrayList容量 */ 
	int elementSize;							/* 一个元素的大小 */ 
	int elementCount;							/* 实际容纳的元素数量 */ 
	void* dataBuffer;							/* 数据指针 */
	bool orderly;								/* 设定是否有序 */
	bool fiexdCap;								/* 设定是否根据当前数据量动态调整内存大小 */
	void* reserve;								/* 预留开发位 */

	Compare compare;							/* 比较函数指针 */
	Destroy destroy;							/* 销毁函数指针 */
}varArrayList;

/* 外部接口 */

/* int型比较函数 */
int intCompare(varArrayList* array, void* data1, void* data2);
/* double型比较函数 */
int doubleCompare(varArrayList* array, void* data1, void* data2);
/* str比较函数 */
int stringCompare(varArrayList* array, void* data1, void* data2);

// /* value比较函数 */
// int valueCompare(varArrayList* array, void* left, void* right);

/* tuple比较函数 */
// int tupleCompareByField()

/* 构造函数  创建一个varArrayList */
varArrayList* varArrayListCreate(int flag, int elementSize, int capacity, Compare compare, Destroy destroy);
/* 获取元素数量 */
int varArrayListGetCount(varArrayList* array);
/* 对一个OrderArratList进行插入数据 */
int varArrayListAdd(varArrayList* array, void* data);
/* 在尾部插入一个数据 */
int varArrayListAddTail(varArrayList* array, void* data);
/* 查询函数，查找获取下标 */
int varArrayListIndexOf(varArrayList* array, void* data);
/* 查询函数，根据下标获取数据 */
void* varArrayListGet(varArrayList* array, int index);
/* 将first中下标index至尾部的数据移动至second的头部 */
int varArrayListRemoveTail(varArrayList* arrayFirst, varArrayList* arraySecond, int index);
/* 将first中下标0至index的数据移动至second的尾部 */
int varArrayListRemoveHead(varArrayList* arrayFirst, varArrayList* arraySecond, int index);
/* 对数据进行单次删除 */
int varArrayListRemove(varArrayList* array, void* data);
/* varArrayList根据数据删除元素,若出现多个则全部删除 */
int varArrayListRemoveAll(varArrayList* array, void* data);
/* 根据下标删除数据 */
int varArrayListRemoveByIndex(varArrayList* array, int index);
/* 对指定的数据进行单次删除 */
int varArrayListSet(varArrayList* array, void* data1, void* data2);
/* 对指定的数据进行更新 若出现多个则全部更新*/
int varArrayListSetAll(varArrayList* array, void* data1, void* data2);
/* 对指定下标进行更新 */
int varArrayListSetByIndex(varArrayList* array, int index, void* data);
/* 清空一个varArrayList */
int varArrayListClear(varArrayList* array);
/* 销毁一个varArrayList */
void varArrayListDestroy(varArrayList** array);


/* 输出int array的值, 用于调试 */
void printfArrayIntValue(varArrayList* array);

/* 指针函数接口 */
int varArrayListAddPointer(varArrayList* array, void* pointer);
int varArrayListAddPointerTail(varArrayList* array, void* pointer);
int varArrayListRemovePointer(varArrayList* array, void* pointer);
int varArrayListRemoveByIndexPointer(varArrayList* array, int index);
void* varArrayListGetPointer(varArrayList* array, int index);
void* varArrayListMovePointer(varArrayList* array, int index);
int varArrayListIndexOfPointer(varArrayList* array, void* pointer);
int varArrListSetPointer(varArrayList* array, void* pointer1, void* pointer2);
int varArrayListSetByIndexPointer(varArrayList* array, int index, void* pointer);
int varArrayListExistPointer(varArrayList* array, void* pointer);

/* 反转varArrayList */
void varArrayListReverse(varArrayList* array);
/* 对varArrayList进行拷贝 */
varArrayList* varArrayListCopy(varArrayList* array);

/* 将srcList中的数据拷贝至destList */
int varArrayListCopyTo(varArrayList* srcList, varArrayList* destList);


/* move varArrayList */
varArrayList* varArrayListMove(varArrayList** array);

/* valArrayList结构体指针销毁函数 */
void varArrayListPointerDestroy(void* data);



#endif 
