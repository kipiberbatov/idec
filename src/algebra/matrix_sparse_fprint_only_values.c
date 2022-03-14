#include <errno.h>
#include "double.h"
#include "matrix_sparse_private.h"

void matrix_sparse_fprint_only_values(FILE * out, const matrix_sparse * a)
{
  fprintf(out, "%d\n%d\n", a->rows, a->cols);
  double_fprint_array_raw(out, a->cols_total[a->cols], a->values);
}
