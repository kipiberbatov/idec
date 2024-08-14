#include "jagged.h"

int jagged1_couple_other_object(const jagged1 * arr, int i)
{
  if (arr->a1[0] == i)
    return arr->a1[1];
  return arr->a1[0];
}
