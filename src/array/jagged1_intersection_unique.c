#include "jagged.h"

/* it is required that jagged1_intersection_count(arr1, arr2) == 1 */
/* otherwise, the function finds the first intersection */
int jagged1_intersection_unique(const jagged1 * arr1, const jagged1 * arr2)
{
  int arr1_a0, i;
  int * arr1_a1;

  arr1_a0 = arr1->a0;
  arr1_a1 = arr1->a1;

  for (i = 0; i < arr1_a0; ++i)
    if (jagged1_member(arr2, arr1_a1[i]))
      return arr1_a1[i];
  return -1;
}
