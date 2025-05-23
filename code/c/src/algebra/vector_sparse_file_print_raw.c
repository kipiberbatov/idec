#include "double_array.h"
#include "int.h"
#include "vector_sparse_private.h"

void vector_sparse_file_print_raw(FILE * out, const vector_sparse * a)
{
  fprintf(out, "%d\n", a->length);
  fprintf(out, "%d\n", a->nonzero_max);
  int_array_file_print(out, a->nonzero_max, a->positions, "--raw");
  double_array_file_print(out, a->nonzero_max, a->values, "--raw");
}
