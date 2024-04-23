#include "int.h"

int int_array_flatten_index(int d, const int * dimensions, const int * indices)
{
  int flattened_index, prod, r;
  
  flattened_index = 0;
  for (r = 0; r < d; ++r)
  {
    prod = int_array_total_product(d - (r + 1), dimensions + r + 1);
    flattened_index += prod * indices[r];
  }
  return flattened_index;
}
