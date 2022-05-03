#ifndef FUNC_H_
#define FUNC_H_

#include <stdbool.h>
#include "type.h"

bool Equal(const ElemType e1, const ElemType e2);

bool GreaterThan(const ElemType e1, const ElemType e2);

bool LessThan(const ElemType e1, const ElemType e2);

void QuickSort(ElemType ary[], int l, int r);

#endif
