#include "int.h"
#include "jagged.h"

void jagged2_part1(jagged1 * res, const jagged2 * arr, int i1)
{
  int p1;

  /* undefined behaviour if (i1 < 0 || i1 >= arr->a0) */
  p1 = int_array_total_sum(i1, arr->a1);

  res->a0 = arr->a1[i1];
  res->a1 = arr->a2 + p1;
}
