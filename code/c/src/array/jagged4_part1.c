#include "int.h"
#include "jagged.h"

void jagged4_part1(jagged3 * res, const jagged4 * arr, int i1)
{
  int p2, p3, p4;

  /* if (i1 < 0 || i1 >= arr->a0) error_handle(); */
  res->a0 = arr->a1[i1];
  p2 = int_array_total_sum(i1, arr->a1);
  res->a1 = arr->a2 + p2;
  p3 = int_array_total_sum(p2, arr->a2);
  res->a2 = arr->a3 + p3;
  p4 = int_array_total_sum(p3, arr->a3);
  res->a3 = arr->a4 + p4;
}
