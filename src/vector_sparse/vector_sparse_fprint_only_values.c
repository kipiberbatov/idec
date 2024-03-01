#include "double.h"
#include "int.h"
#include "vector_sparse_private.h"

void vector_sparse_fprint_only_values(FILE * out, const vector_sparse * a)
{
  double_array_fprint(out, a->nonzero_max, a->values, "--raw");
}
