#include <errno.h>
#include "vector_sparse_private.h"

void vector_sparse_file_print_mathematica_sparse(
  FILE * out, const vector_sparse * a)
{
  int a_nonzero_max, i, i_loc;
  int * a_positions;
  double x;
  double * a_values;

  a_nonzero_max = a->nonzero_max;
  a_positions = a->positions;
  a_values = a->values;

  fputs("SparseArray[{", out);
  for (i_loc = 0; i_loc < a_nonzero_max; ++i_loc)
  {
    i = a_positions[i_loc];
    x = a_values[i_loc];
    fprintf(out, "{%d}->%g", i + 1,  x);
    if (i_loc < a_nonzero_max - 1)
      fputc(',', out);
  }
  fprintf(out, "},{%d}]\n", a_nonzero_max);
}
