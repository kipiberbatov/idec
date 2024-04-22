#include "jagged.h"

int jagged2_subset_maximal_size(const jagged1 * subset, const jagged2 * arr)
{
  int i, i_local, subset_a0, size_i, size_max;
  int * subset_a1;
  jagged1 arr_i;
    
  subset_a0 = subset->a0;
  subset_a1 = subset->a1;
  size_max = 0;
  
  for (i_local = 0; i_local < subset_a0; ++i_local)
  {
    i = subset_a1[i_local];
    jagged2_part1(&arr_i, arr, i);
    size_i = arr_i.a0;
    if (size_i > size_max)
      size_max = size_i;
  }
  return size_max;
}
