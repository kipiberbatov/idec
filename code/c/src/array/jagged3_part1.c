#include "int.h"
#include "jagged.h"

void jagged3_part1(jagged2 * res, const jagged3 * arr, int i1)
{
  int p1, p2;

  /* undefined behaviour if(i1 < 0 || i1 >= arr->a0) */
  p1 = int_array_total_sum(i1, arr->a1);

  p2 = int_array_total_sum(p1, arr->a2);

  res->a0 = arr->a1[i1];
  res->a1 = arr->a2 + p1;
  res->a2 = arr->a3 + p2;
}
