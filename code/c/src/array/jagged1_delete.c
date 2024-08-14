#include "jagged.h"

void jagged1_delete(jagged1 * result, const jagged1 * arr, int position)
{
  int i, result_a0;
  int * arr_a1, * result_a1;

  result_a0 = result->a0;
  result_a1 = result->a1;
  arr_a1 = arr->a1;
  for (i = 0; i < position; ++i)
    result_a1[i] = arr_a1[i];
  for (i = position; i < result_a0; ++i)
    result_a1[i] = arr_a1[i + 1];
}
