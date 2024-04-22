#include "jagged.h"

int jagged1_signature(const jagged1 * arr)
{
  int arr_a0, i, inversions, j;
  int * arr_a1;

  arr_a0 = arr->a0;
  arr_a1 = arr->a1;

  inversions = 0;
  for (i = 0; i < arr_a0 - 1; ++i)
    for (j = i + 1; j < arr_a0; ++j)
      if (arr_a1[i] > arr_a1[j])
        ++inversions;
  return ((inversions % 2 == 0) ? 1 : -1);
}
