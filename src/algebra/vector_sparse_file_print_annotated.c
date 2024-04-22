#include "double.h"
#include "int.h"
#include "vector_sparse_private.h"

void vector_sparse_file_print_annotated(FILE * out, const vector_sparse * a)
{
  int a_nonzero_max, i;
  int * a_positions;
  double * a_values;
  
  a_nonzero_max = a->nonzero_max;
  a_positions = a->positions;
  a_values = a->values;
  for (i = 0; i < a_nonzero_max; ++i)
    fprintf(out, "  %d : %g\n", a_positions[i], a_values[i]);
  fputc('\n', out);
}
