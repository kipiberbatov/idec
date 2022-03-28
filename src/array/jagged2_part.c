#include "int.h"
#include "jagged.h"

void jagged2_part1(jagged1 * res, const jagged2 * arr, int i1)
{
  int p2;
  
  /* if (i1 < 0 || i1 >= arr->a0) error_handle(); */
  res->a0 = arr->a1[i1];
  p2 = int_array_total_sum(i1, arr->a1);
  res->a1 = arr->a2 + p2;
}

int jagged2_part2(const jagged2 * arr, int i1, int i2)
{
  int p2;
  
  /* if (i1 < 0 || i1 >= arr->a0) error_handle(); */
  /* if (i2 < 0 || i2 >= arr->a1[i1]) error_handle(); */
  p2 = int_array_total_sum(i1, arr->a1);
  return arr->a2[p2 + i2];
}
