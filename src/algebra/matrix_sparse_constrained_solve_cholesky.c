#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include "double.h"
#include "int.h"
#include "matrix_sparse.h"

// static double * double_array_restrict(
//   int m, const double * b, const jagged1 * rows_complement)
// {
//   double * b_restrict;
//   int i, i_loc;
//
//   b_restrict = (double *) malloc(sizeof(double) * rows_complement->a0);
//   if (errno)
//   {
//     fputs("double_array_restrict - cannot allocate memory for b_restrict\n",
//           stderr);
//     return NULL;
//   }
//   // double_array_substitute(b_restrict, m, b, rows_complement->a1);
//   for (i_loc = 0; i_loc < m; ++i_loc)
//   {
//     i = rows_complement->a1[i_loc];
//     b_restrict[i_loc] = b[i];
//   }
//   return b_restrict;
// }

static double * double_array_constrain(
  const matrix_sparse * a, const double * b, const jagged1 * cols,
  const jagged1 * rows_complement)
{
  int cols_a0, i, i_loc, j, j_loc, rows_complement_a0;
  int * a_cols_total, * cols_a1, * rows_complement_a1;
  double * a_values, * a_values_j, * b_restrict;
  
  a_cols_total = a->cols_total;
  a_values = a->values;
  cols_a0 = cols->a0;
  cols_a1 = cols->a1;
  rows_complement_a0 = rows_complement->a0;
  rows_complement_a1 = rows_complement->a1;
  
  b_restrict = (double *) malloc(sizeof(double) * rows_complement_a0);
  if (errno)
  {
    fputs("double_array_constrain - cannot allocate memory for b_restrict\n",
          stderr);
    return NULL;
  }
  double_array_substitute(b_restrict, rows_complement_a0, b,
                          rows_complement_a1);
  //b_restrict = double_array_restrict(a->rows, b, rows_complement);
  // if (errno)
  // {
  //   fputs("double_array_constrain - cannot calculate b_restrict\n", stderr);
  //   return NULL;
  // }
  
  for (j_loc = 0; j_loc < cols_a0; ++j_loc)
  {
    j = cols_a1[j_loc];
    a_values_j = a_values + a_cols_total[j];
    for (i_loc = 0; i_loc < rows_complement_a0; ++i_loc)
    {
      i = rows_complement_a1[i_loc];
      b_restrict[j] -= a_values_j[i] * b[i];
    }
  }
  return b_restrict;
}

// static void matrix_sparse_fill(
//   double * x, const double * b, const jagged1 * rows)
// {
//   int i, i_loc, rows_a0;
//   int * rows_a1;
//
//   rows_a0 = rows->a0;
//   rows_a1 = rows->a1;
//   for (i_loc = 0; i_loc < rows_a0; ++i_loc)
//   {
//     i = rows_a1[i_loc];
//     x[i] = b[i_loc];
//   }
// }

double * matrix_sparse_constrained_solve_cholesky(
  const matrix_sparse * a, const double * b, const jagged1 * rows)
{
  int a_m;
  double * b_restrict, * x = NULL;
  matrix_sparse * a_restrict;
  jagged1 * rows_complement;
  
  a_m = a->rows;
  
  rows_complement = jagged1_complement(a_m, rows);
  if (errno)
  {
    fputs("matrix_sparse_constrained_solve_cholesky - cannot calculate "
          "rows_complement\n", stderr);
    goto end;
  }
  
  a_restrict = matrix_sparse_remove(a, rows_complement, rows_complement);
  if (errno)
  {
    fputs("matrix_sparse_constrained_solve_cholesky - cannot calculate "
          "a_restrict\n", stderr);
   goto rows_complement_free;
  }
  
  b_restrict = double_array_constrain(a, b, rows, rows_complement);
  if (errno)
  {
    fputs("matrix_sparse_constrained_solve_cholesky - cannot calculate "
          "b_restrict\n", stderr);
    goto a_restrict_free;
  }
  
  matrix_sparse_linear_solve(a_restrict, b_restrict, "--cholesky");
  if (errno)
  {
    fputs("matrix_sparse_constrained_solve_cholesky - solve and mutate for "
          "b_restrict\n", stderr);
    goto b_restrict_free;
  }
  
  x = (double *) malloc(sizeof(double) * a_m);
  if (errno)
  {
    fputs("matrix_sparse_constrained_solve_cholesky - cannot allocate memory "
          "for x\n", stderr);
    goto b_restrict_free;
  }
  
  double_array_substitute_inverse(x, rows->a0, b, rows->a1);
  
  double_array_substitute_inverse(x, rows_complement->a0, b_restrict,
                                  rows_complement->a1);
  // matrix_sparse_fill(x, b, rows);
  // matrix_sparse_fill(x, b_restrict, rows_complement);

b_restrict_free:  
  free(b_restrict);
a_restrict_free:
  matrix_sparse_free(a_restrict);
rows_complement_free:
  jagged1_free(rows_complement);
end:
  return x;
}
