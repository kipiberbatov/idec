#include "int.h"

void int_array_set_difference(
  int * b_bar, int p, const int * a, int q, const int * b)
{
  int i, ind;

  ind = 0;
  for (i = 0; i < p; ++i)
    if (!int_array_member(q, b, a[i]))
    {
      b_bar[ind] = a[i];
      ++ind;
    }
}
