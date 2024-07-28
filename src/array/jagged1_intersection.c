#include "jagged.h"

void jagged1_intersection(
  jagged1 * res, const jagged1 * arr1, const jagged1 * arr2)
{
  int arr1_a0, i, ind;
  int * arr1_a1, * res_a1;

  arr1_a0 = arr1->a0;
  arr1_a1 = arr1->a1;
  res_a1 = res->a1;
  ind = 0;
  for (i = 0; i < arr1_a0; ++i)
  {
    if (jagged1_member(arr2, arr1_a1[i]))
    {
      res_a1[ind] = arr1_a1[i];
      ++ind;
    }
  }
  res->a0 = ind;
}
