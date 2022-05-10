#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include "type.h"
#include "func.h"
#include "singly_linked_list.h"

bool LnkListInit(LnkList *l)
{
    *l = (SL_Node *)malloc(sizeof(SL_Node));
    if (!*l)
        return false;
    (*l)->next = NULL;
    return true;
}

void LnkListDestroy(const LnkList l)
{
    SL_Node *ptr = l, *temp = ptr;
    while (ptr)
    {
        temp = ptr;
        ptr = ptr->next;
        free(temp);
    }
}

void LnkListClear(LnkList l)
{
    SL_Node *ptr = l->next, *temp = ptr;
    while (ptr)
    {
        temp = ptr;
        ptr = ptr->next;
        free(temp);
    }
    l->next = NULL;
}

bool LnkListEmpty(const LnkList l)
{
    return NULL == l->next;
}

int LnkListLength(const LnkList l)
{
    SL_Node *ptr = l->next;
    int len = 0;

    while (ptr)
    {
        ptr = ptr->next;
        ++len;
    }
    return len;
}

SL_Node *LnkListRear(const LnkList l)
{
    SL_Node *p = l;
    while (p->next)
    {
        p = p->next;
    }
    return p;
}

bool LnkListGetElem(const LnkList l, const int i, ElemType *const eptr)
{
    SL_Node *ptr = l->next;
    int cnt = 0;

    while (cnt++ < i && ptr)
    {
        ptr = ptr->next;
    }
    if (!ptr)
        return false;
    *eptr = ptr->elem;
    return true;
}

int LnkListLocateElem(const LnkList l, const ElemType e, bool (*compare_func)(const ElemType e1, const ElemType e2))
{
    SL_Node *ptr = l->next;
    int index = 1;

    while (ptr)
    {
        if ((*compare_func)(e, ptr->elem))
            break;
        ++index;
        ptr = ptr->next;
    }
    return index;
}

bool LnkListPriorElem(const LnkList l, const ElemType e, ElemType *const eptr)
{
    SL_Node *ptr = l->next;
    while (ptr->next && ptr)
    {
        if (ptr->next->elem == e)
            break;
    }
    if (!ptr->next)
        return false;
    *eptr = ptr->elem;
    return true;
}

bool LnkListNextElem(const LnkList l, const ElemType e, ElemType *const eptr)
{
    SL_Node *ptr = l->next;
    while (ptr->next && ptr)
    {
        if (e == ptr->elem)
            break;
    }
    if (!ptr->next)
        return false;
    *eptr = ptr->next->elem;
    return true;
}

bool LnkListPtrInsert(LnkList l, SL_Node *const ptr, const ElemType e)
{
    SL_Node *t = NULL;

    t = l;
    while (t)
    {
        if (ptr == t)
            break;
        t = t->next;
    }
    if (!t)
        return false;
    if (NULL == (t = (SL_Node *)calloc(1, sizeof(SL_Node))))
        return false;
    t->elem = e;
    t->next = ptr->next;
    ptr->next = t;
    return true;
}

bool LnkListPtrDelete(LnkList l, SL_Node *const ptr, ElemType *const eptr)
{
    SL_Node *t = NULL;

    t = l;
    while (t)
    {
        if (ptr == t)
            break;
        t = t->next;
    }
    if (!t)
        return false;
    t = ptr->next;
    *eptr = t->elem;
    ptr->next = ptr->next->next;
    free(t);
    return true;
}

bool LnkListPosInsert(LnkList l, const int pos, const ElemType e)
{
    SL_Node *prior = NULL, *t = NULL;
    int cnt = 1;

    prior = l;
    while (prior->next)
    {
        if (pos == cnt)
            break;
        prior = prior->next;
        ++cnt;
    }
    if (!prior)
        return false;
    if (NULL == (t = (SL_Node *)calloc(1, sizeof(SL_Node))))
        return false;
    t->elem = e;
    t->next = prior->next;
    prior->next = t;
    return true;
}

bool LnkListPosDelete(LnkList l, const int pos, ElemType *const eptr)
{
    SL_Node *prior = NULL, *t = NULL;
    int cnt = 1;

    prior = l;
    while (prior->next)
    {
        if (pos == cnt)
            break;
        prior = prior->next;
        ++cnt;
    }
    if (!prior)
        return false;
    t = prior->next;
    *eptr = t->elem;
    prior->next = t->next;
    free(t);
    return true;
}

void LnkListTraverse(const LnkList l)
{
    SL_Node *p = l->next;

    while (p)
    {
        printf("%d ", p->elem);
        p = p->next;
    }
    printf("\n");
}

bool LnkListUnion(const LnkList la, const LnkList lb, LnkList lc)
{
    if (!LnkListAssign(&lc, lb))
        return false;
    int la_len = LnkListLength(la), lb_len = LnkListLength(lb);
    ElemType e;
    for (int i = 0; i < la_len; ++i)
    {
        if (!LnkListGetElem(la, i + 1, &e))
            return false;
        if (0 == LnkListLocateElem(lb, e, Equal))
        {
            if (!LnkListPosInsert(lc, LnkListLength(lc) + 1, e))
                return false;
        }
    }
    return true;
}

bool LnkListMerge(const LnkList la, const LnkList lb, LnkList *lc)
{
    if (!LnkListInit(lc))
        return false;
    SL_Node *pa = la->next, *pb = lb->next;
    int posa = 1, posb = 1;
    while (pa && pb)
    {
        if (pa->elem < pb->elem)
        {
            if (!LnkListPosInsert(*lc, posa++, pa->elem))
                return false;
            pa = pa->next;
        }
        else
        {
            if (!LnkListPosInsert(*lc, posb++, pb->elem))
                return false;
            pb = pb->next;
        }
    }
    while (pa)
    {
        if (!LnkListPosInsert(*lc, posa++, pa->elem))
            return false;
        pa = pa->next;
    }
    while (pb)
    {
        if (!LnkListPosInsert(*lc, posb++, pb->elem))
            return false;
        pb = pb->next;
    }
    return true;
}

bool LnkListAssign(LnkList *la, const LnkList lb)
{
    if (!LnkListEmpty(*la))
        LnkListDestroy(*la);
    SL_Node *t = lb->next;
    int pos = 1;
    while (t)
    {
        if (!LnkListPosInsert(*la, pos++, t->elem))
            return false;
        t = t->next;
    }
    return true;
}
