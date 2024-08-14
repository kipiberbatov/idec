#include "int.h"
#include "jagged.h"

int jagged1_total_sum(const jagged1 * arr)
{
  return int_array_total_sum(arr->a0, arr->a1);
}
