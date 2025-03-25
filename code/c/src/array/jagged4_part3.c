#include "int.h"
#include "jagged.h"

void jagged4_part3(jagged1 * res, const jagged4 * arr, int i1, int i2, int i3)
{
  int p2, p3, p4;

  /* if (i1 < 0 || i1 >= arr->a0) error_handle(); */
  /* if (i2 < 0 || i2 >= arr->a1[i1])  error_handle(); */
  p2 = int_array_total_sum(i1, arr->a1);
  /* if (i3 < 0 || i3 >= arr->a2[p2 + i2]) error_handle(); */
  p3 = int_array_total_sum(p2 + i2, arr->a2);
  res->a0 = arr->a3[p3 + i3];
  p4 = int_array_total_sum(p3 + i3, arr->a3);
  res->a1 = arr->a4 + p4;
}
