#ifndef SINGLY_LINKED_LIST
#define SINGLY_LINKED_LIST

#include <stdbool.h>
#include "type.h"

typedef struct singly_linked_list
{
    ElemType elem;
    struct singly_linked_list *next;
} SL_Node, *LnkList;

bool LnkListInit(LnkList *l);

void LnkListDestroy(const LnkList l);

void LnkListClear(LnkList l);

bool LnkListEmpty(const LnkList l);

int LnkListLength(const LnkList l);

SL_Node *LnkListRear(const LnkList l);

bool LnkListGetElem(const LnkList l, const int i, ElemType *const eptr);

int LnkListLocateElem(const LnkList l, const ElemType e, bool (*compare_func)(const ElemType e1, const ElemType e2));

bool LnkListPriorElem(const LnkList l, const ElemType e, ElemType *const eptr);

bool LnkListNextElem(const LnkList l, const ElemType e, ElemType *const eptr);

bool LnkListPtrInsert(LnkList l, SL_Node *const ptr, const ElemType e);

bool LnkListPtrDelete(LnkList l, SL_Node *const ptr, ElemType *const eptr);

bool LnkListPosInsert(LnkList l, const int pos, const ElemType e);

bool LnkListPosDelete(LnkList l, const int pos, ElemType *const eptr);

void LnkListTraverse(const LnkList l);

bool LnkListUnion(const LnkList la, const LnkList lb, LnkList lc);

bool LnkListMerge(const LnkList la, const LnkList lb, LnkList *lc);

bool LnkListAssign(LnkList *la, const LnkList lb);

#endif