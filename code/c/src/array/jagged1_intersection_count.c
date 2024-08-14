#include "jagged.h"

int jagged1_intersection_count(const jagged1 * arr1, const jagged1 * arr2)
{
  int arr1_a0, i, res;
  int * arr1_a1;

  arr1_a0 = arr1->a0;
  arr1_a1 = arr1->a1;
  res = 0;
  for (i = 0; i < arr1_a0; ++i)
    res += jagged1_member(arr2, arr1_a1[i]);
  return res;
}
