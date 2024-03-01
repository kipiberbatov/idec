#include "matrix_sparse_private.h"

void matrix_sparse_to_cs(cs * a0, const matrix_sparse * a)
{
  a0->nzmax = a->cols_total[a->cols];
  a0->m = a->rows;
  a0->n = a->cols;
  a0->p = a->cols_total;
  a0->i = a->row_indices;
  a0->x = a->values;
  a0->nz = -1;
}

void matrix_sparse_from_cs(matrix_sparse * a, const cs * a0)
{
  a->rows = a0->m;
  a->cols = a0->n;
  a->cols_total = a0->p;
  a->row_indices = a0->i;
  a->values = a0->x;
}
