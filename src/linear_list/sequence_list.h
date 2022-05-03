#ifndef SEQUENCE_LIST_H
#define SEQUENCE_LIST_H

#include <stdbool.h>
#include "type.h"

#define LIST_INIT_SIZE 100 //线性表存储空间的初始分配量
#define LIST_INCREMENT 10  //线性表存储空间的分配增量

typedef struct
{
    ElemType *elem; //存储空间基址
    int length;     //当前长度（元素的数量）
    int list_size;  //当前分配的容量（以sizeof(ElemType为单位）
} SqList;

bool SqListInit(SqList *const l);

void SqListDestroy(SqList *const l);

void SqListClear(SqList *const l);

void SqListShrink(SqList *const l);

bool SqListEmpty(const SqList *const l);

int SqListLength(const SqList *const l);

bool SqListGetElem(const SqList *const l, const int i, ElemType *const eptr);

int SqListLoacteElem(const SqList *const l, const ElemType e, bool (*compare_func)(const ElemType e1, const ElemType e2));

bool SqListPriorElem(const SqList *const l, const ElemType e, ElemType *const eptr);

bool SqListNextElem(const SqList *const l, const ElemType e, ElemType *const eptr);

bool SqListInsert(SqList *const l, const int pos, const ElemType e);

bool SqListDelete(SqList *const l, const int pos, ElemType *const eptr);

void SqListTraverse(const SqList *const l);

bool SqListUnion(const SqList *const la, const SqList *const lb, SqList *const lc);

bool SqListMerge(const SqList *const la, const SqList *const lb, SqList *const lc);

void SqListSort(SqList *const l);

bool SqListAssign(SqList *const la, const SqList *const lb);

#endif