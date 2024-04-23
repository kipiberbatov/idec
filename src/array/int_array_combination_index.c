#include "int.h"

int int_array_combination_index(int * comb, int m, int n)
{
  int i, j, prev, res, a0;
  
  if (n != 0)
  {
    a0 = comb[0];
    prev = 0;
    for (i = 1; i <= a0; ++i)
      prev += int_binomial(m - i, n - 1);
    ++a0;
    for (j = 1; j < n; ++j)
      comb[j] -= a0;
    ++comb;
    res = prev + int_array_combination_index(comb, m - a0, n - 1);
  }
  else
    res = 0;
  return res;
}
