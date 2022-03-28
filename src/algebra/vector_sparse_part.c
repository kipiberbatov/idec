#include "vector_sparse.h"

double vector_sparse_part(const vector_sparse * a, int i)
{
  int a_nonzero_max, i_loc;
  int * a_positions;
  double * a_values;
  
  a_nonzero_max = a->nonzero_max;
  a_positions = a->positions;
  a_values = a->values;
  for (i_loc = 0; i_loc < a_nonzero_max; ++i_loc)
    if (a_positions[i_loc] == i)
      return a_values[i_loc];
  return 0.;
}
