#include "jagged.h"

int jagged1_member(const jagged1 * arr, int element)
{
  int arr_a0, i;
  int * arr_a1;

  arr_a0 = arr->a0;
  arr_a1 = arr->a1;

  for (i = 0; i < arr_a0; ++i)
    if (element == arr_a1[i])
      return 1;
  return 0;
}
