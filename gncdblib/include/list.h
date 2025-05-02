//dlist.h
#ifndef __DLIST_H__
#define __DLIST_H__

#include <stdlib.h>
#include "pagepool.h"

typedef struct PageStatus PageStatus;
typedef PageStatus DListNode;

//枚举，函数的返回值类型
typedef enum _DListRet
{
    DLIST_RET_OK,
    DLIST_RET_OOM,
    DLIST_RET_STOP,
    DLIST_RET_PARAMS,
    DLIST_RET_FAIL
}DListRet;

// //DList用于描述整个链表，定义在dlist.cpp中
// struct _DList;
// typedef struct _DList DList;

//销毁节点的回调
typedef void (*DListDataDestroyFunc)(void* ctx, void* data);
//节点数据比较回调
typedef int (*DListDataCompareFunc)(void* ctx, void* data);
//遍历链表时的回调
typedef DListRet (*DListDataVisitFunc)(void* ctx, void* data);

// 链表描述
typedef struct _DList
{
    DListNode *first;
    DListDataDestroyFunc data_destroy;
    void *data_destroy_ctx;
    DListNode *tail;
    int length;
} DList;

// 可供调用者使用的链表操作函数
DList *dlist_create(DListDataDestroyFunc data_destroy, void *data_destroy_ctx);
DListRet dlist_insert(DList *thiz, int index, DListNode *node);
DListRet dlist_prepend(DList *thiz, DListNode *node);
DListRet dlist_append(DList *thiz, DListNode *node);
DListRet dlist_delete(DList *thiz, DListNode *cursor);
DListRet dlist_get_by_index(DList *thiz, int index, int *data);
DListRet dlist_set_by_index(DList *thiz, int index, int data);
int dlist_find(DList *thiz, int target);
DListRet dlist_foreach(DList *thiz, DListDataVisitFunc visit, void *ctx);
void dlist_destroy(DList *thiz);

#endif /* __DLIST_H__ */
