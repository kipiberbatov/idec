#include "jagged.h"

int jagged1_part1(const jagged1 * arr, int i1)
{
  /* if (i1 < 0 || i1 >= arr->a0) error_handle(); */
  return arr->a1[i1];
}
