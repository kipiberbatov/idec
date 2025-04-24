#include "int.h"
#include "jagged.h"

int jagged4_part4(const jagged4 * arr, int i1, int i2, int i3, int i4)
{
  int p1, p2, p3, p4;

  /* undefined behaviour if (i1 < 0 || i1 >= arr->a0) */
  p1 = int_array_total_sum(i1, arr->a1);

  /* undefined behaviour if (i2 < 0 || i2 >= arr->a1[i1]) */
  p2 = int_array_total_sum(p1 + i2, arr->a2);

  /* undefined behaviour if (i3 < 0 || i3 >= arr->a2[p1 + i2]) */
  p3 = int_array_total_sum(p2 + i3, arr->a3);

  /* undefined behaviour if (i4 < 0 || i4 >= arr->a3[p2 + i3]) */
  p4 = arr->a4[p3 + i4];

  return p4;
}
