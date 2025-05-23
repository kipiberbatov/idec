#include "int.h"
#include "jagged.h"

void jagged4_part2(jagged2 * res, const jagged4 * arr, int i1, int i2)
{
  int p1, p2, p3;

  /* undefined behaviour if (i1 < 0 || i1 >= arr->a0) */
  p1 = int_array_total_sum(i1, arr->a1);

  /* undefined behaviour if (i2 < 0 || i2 >= arr->a1[i1]) */
  p2 = int_array_total_sum(p1 + i2, arr->a2);

  p3 = int_array_total_sum(p2, arr->a3);

  res->a0 = arr->a2[p1 +i2];
  res->a1 = arr->a3 + p2;
  res->a2 = arr->a4 + p3;
}
