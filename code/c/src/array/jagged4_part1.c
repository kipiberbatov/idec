#include "int.h"
#include "jagged.h"

void jagged4_part1(jagged3 * res, const jagged4 * arr, int i1)
{
  int p1, p2, p3;

  /* undefined behaviour if (i1 < 0 || i1 >= arr->a0) */
  p1 = int_array_total_sum(i1, arr->a1);

  p2 = int_array_total_sum(p1, arr->a2);
  p3 = int_array_total_sum(p2, arr->a3);

  res->a0 = arr->a1[i1];
  res->a1 = arr->a2 + p1;
  res->a2 = arr->a3 + p2;
  res->a3 = arr->a4 + p3;
}
