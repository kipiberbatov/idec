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

void jagged4_part2(jagged2 * res, const jagged4 * arr, int i1, int i2)
{
  int p2, p3, p4;
  
  /* if (i1 < 0 || i1 >= arr->a0) error_handle(); */
  /* if (i2 < 0 || i2 >= arr->a1[i1]) error_handle(); */
  p2 = int_array_total_sum(i1, arr->a1);
  res->a0 = arr->a2[p2 +i2];
  p3 = int_array_total_sum(p2 + i2, arr->a2);
  res->a1 = arr->a3 + p3;
  p4 = int_array_total_sum(p3, arr->a3);
  res->a2 = arr->a4 + p4;
}

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

int jagged4_part4(const jagged4 * arr, int i1, int i2, int i3, int i4)
{
  int p2, p3, p4;
  /* if (i1 < 0 || i1 >= arr->a0) error_handle(); */
  /* if (i2 < 0 || i2 >= arr->a1[i1])  error_handle(); */
  p2 = int_array_total_sum(i1, arr->a1);
  /* if (i3 < 0 || i3 >= arr->a2[p2 + i2]) error_handle(); */
  p3 = int_array_total_sum(p2 + i2, arr->a2);
  /* if (i4 < 0 || i4 >= arr->a3[p3 + i3]) error_handle(); */
  p4 = int_array_total_sum(p3 + i3, arr->a3);
  return arr->a4[p4 + i4];
}
