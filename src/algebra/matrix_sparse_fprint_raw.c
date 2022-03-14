#include <errno.h>
#include "double.h"
#include "int.h"
#include "matrix_sparse_private.h"

void matrix_sparse_fprint_raw(FILE * out, const matrix_sparse * a)
{
  fprintf(out, "%d\n", a->rows);
  fprintf(out, "%d\n", a->cols);
  int_fprint_array_raw(out, (a->cols + 1), a->cols_total);
  int_fprint_array_raw(out, a->cols_total[a->cols], a->row_indices);
  double_fprint_array_raw(out, a->cols_total[a->cols], a->values);
}
