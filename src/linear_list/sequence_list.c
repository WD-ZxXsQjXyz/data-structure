#include <stdio.h>
#include <stdlib.h>
#include "sequence_list.h"
#include "func.h"
#include "value.h"
#include "type.h"

bool SqListInit(SqList *const l)
{
    l->elem = (ElemType *)calloc(LIST_INIT_SIZE, sizeof(ElemType));
    if (!l->elem)
        return false;
    l->length = 0;
    l->list_size = LIST_INIT_SIZE;
    return true;
}

void SqListDestroy(SqList *const l)
{
    free(l->elem);
    l->elem = NULL;
    l->length = 0;
    l->list_size = 0;
}

void SqListClear(SqList *const l)
{
    l->length = 0;
}

void SqListShrink(SqList *const l)
{
    l->length = (l->length < LIST_INIT_SIZE ? LIST_INIT_SIZE : l->length);
    l->elem = (ElemType *)realloc(l->elem, l->length);
    l->list_size = l->list_size;
}

bool SqListEmpty(const SqList *const l)
{
    return 0 == l->length;
}

int SqListLength(const SqList *const l)
{
    return l->length;
}

bool SqListGetElem(const SqList *const l, const int i, ElemType *const eptr)
{
    if (i < 1 || i > l->length)
        return false;
    *eptr = *(l->elem + (i - 1));
    return true;
}

int SqListLoacteElem(const SqList *const l, const ElemType e, bool (*compare_func)(const ElemType e1, const ElemType e2))
{
    for (int i = 1; i <= l->length; ++i)
        if (compare_func(e, *(l->elem + i - 1)))
            return i;
    return 0;
}

bool SqListPriorElem(const SqList *const l, const ElemType e, ElemType *const eptr)
{
    int pos = SqListLoacteElem(l, e, Equal);
    if (0 == pos)
        return false;
    if (!SqListGetElem(l, pos - 1, eptr))
        return false;
    return true;
}

bool SqListNextElem(const SqList *const l, const ElemType e, ElemType *const eptr)
{
    int pos = SqListLoacteElem(l, e, Equal);
    if (0 == pos)
        return false;
    if (!SqListGetElem(l, pos + 1, eptr))
        return false;
    return true;
}

bool SqListInsert(SqList *const l, const int pos, const ElemType e)
{
    if (pos < 1 || pos > l->length + 1)
        return false;
    if (l->length >= l->list_size)
    {
        l->elem = (ElemType *)realloc(l->elem, sizeof(ElemType) * (l->list_size + LIST_INCREMENT));
        if (!l->elem)
            return false;
        l->list_size += LIST_INCREMENT;
    }
    ElemType *q = l->elem + l->length;
    while (q > l->elem + pos - 1)
    {
        *q = *(q - 1);
        --q;
    }
    *q = e;
    ++l->length;
    return true;
}

bool SqListDelete(SqList *const l, const int pos, ElemType *const eptr)
{
    if (pos < 1 || pos > l->length)
        return false;
    ElemType *p = l->elem + pos - 1;
    while (p < l->elem + l->length)
    {
        *p = *(p + 1);
        ++p;
    }
    --l->length;
    return true;
}

void SqListTraverse(const SqList *const l)
{
    for (int i = 0; i < l->length; ++i)
        printf("%4d ", l->elem[i]);
    printf("\n");
}

bool SqListUnion(const SqList *const la, const SqList *const lb, SqList *const lc)
{
    if (!SqListAssign(lc, lb))
        return false;
    int la_len = SqListLength(la), lb_len = SqListLength(lb);
    ElemType e;
    for (int i = 0; i < la_len; ++i)
    {
        if (!SqListGetElem(la, i + 1, &e))
            return false;
        if (0 == SqListLoacteElem(lb, e, Equal))
        {
            if (!SqListInsert(lc, SqListLength(lc) + 1, e))
                return false;
        }
    }
    return true;
}

bool SqListMerge(const SqList *const la, const SqList *const lb, SqList *const lc)
{
    int i = 1, j = 1, k = 0;
    int la_len = SqListLength(la), lb_len = SqListLength(lb);
    ElemType e1, e2;
    while (i <= la_len && j <= lb_len)
    {
        if (!SqListGetElem(la, i, &e1))
            return false;
        if (!SqListGetElem(lb, j, &e2))
            return false;
        if (e1 < e2)
        {
            if (!SqListInsert(lc, ++k, e1))
                return false;
            ++i;
        }
        else
        {
            if (!SqListInsert(lc, ++k, e2))
                return false;
            ++j;
        }
    }
    while (i <= la_len)
    {
        if (!SqListGetElem(la, i++, &e1))
            return false;
        if (!SqListInsert(lc, ++k, e1))
            return false;
    }
    while (j <= lb_len)
    {
        if (!SqListGetElem(lb, j++, &e2))
            return false;
        if (!SqListInsert(lc, ++k, e2))
            return false;
    }
    return true;
}

void SqListSort(SqList *const l)
{
    QuickSort(l->elem, 0, SqListLength(l) - 1);
}

bool SqListAssign(SqList *const la, const SqList *const lb)
{
    free(la->elem);
    la->elem = (ElemType *)calloc(lb->list_size, sizeof(ElemType));
    if (!la->elem)
        return false;
    for (int i = 0; i < lb->length; ++i)
        la->elem[i] = lb->elem[i];
    la->length = lb->length;
    la->list_size = lb->list_size;
    return true;
}