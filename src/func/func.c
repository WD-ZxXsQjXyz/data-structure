#include "func.h"

bool Equal(const ElemType e1, const ElemType e2)
{
    return e1 == e2;
}

bool GreaterThan(const ElemType e1, const ElemType e2)
{
    return e1 > e2;
}

bool LessThan(const ElemType e1, const ElemType e2)
{
    return e1 < e2;
}

void QuickSort(ElemType ary[], int l, int r)
{
    if (l >= r)
        return;
    int i = l - 1, j = r + 1, pivot = ary[(l + r) / 2], temp = 0;
    while (i < j)
    {
        do
            i++;
        while (ary[i] < pivot);
        do
        {
            j--;
        } while (ary[j] > pivot);
        if (i < j)
        {
            temp = ary[i];
            ary[i] = ary[j];
            ary[j] = temp;
        }
    }
    QuickSort(ary, l, j);
    QuickSort(ary, j + 1, r);
}