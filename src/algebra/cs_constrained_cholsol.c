#include "cs.h"

static double * double_array_restrict(
  int m, const double * b, const jagged1 * rows_complement)
{
  double * b_restrict;
  int i, i_loc;
  
  b_restrict = (double *) malloc(rows_complement->a0 * sizeof(double));
  /* NULL pointer check */
  for (i_loc = 0; i_loc < m; ++i_loc)
  {
    i = rows_complement->a1[i_loc];
    b_restrict[i_loc] = b[i];
  }
  return b_restrict;
}

static double * double_array_constrain(
  const cs * a, const double * b, const jagged1 * cols,
  const jagged1 * rows_complement)
{
  int i, i_loc, j, j_loc;
  double * a_x_j, * b_restrict;
  
  b_restrict = double_array_restrict(a->m, b, rows_complement);
  /* NULL pointer check */
  for (j_loc = 0; j_loc < cols->a0; ++j_loc)
  {
    j = cols->a1[j_loc];
    a_x_j = a->x + a->p[j];
    for (i_loc = 0; i_loc < rows_complement->a0; ++i_loc)
    {
      i = rows_complement->a1[i_loc];
      b_restrict[j] -= a_x_j[i] * b[i];
    }
  }
  return b_restrict;
}

static void cs_fill(double * x, const double * b, const jagged1 * rows)
{
  int i, i_loc, rows_a0;
  int * rows_a1;
  
  rows_a0 = rows->a0;
  rows_a1 = rows->a1;
  for (i_loc = 0; i_loc < rows_a0; ++i_loc)
  {
    i = rows_a1[i];
    x[i] = b[i];
  }
}

double * cs_constrained_cholsol(
  const cs * a, const double * b, const jagged1 * rows)
{
  int a_m;
  double * b_restrict, * x;
  cs * a_restrict;
  jagged1 * rows_complement;
  
  a_m = a->m;
  rows_complement = jagged1_complement(a_m, rows);
  /* NULL pointer check */
  a_restrict = cs_restrict(a, rows_complement, rows_complement);
  /* NULL pointer check */
  b_restrict = double_array_constrain(a, b, rows, rows_complement);
  /* NULL pointer check */
  cs_cholsol(1, a_restrict, b_restrict);
  /* NULL pointer check */
  x = (double *) malloc(a_m * sizeof(double));
  /* NULL pointer check */
  cs_fill(x, b, rows);
  cs_fill(x, b_restrict, rows_complement);
  free(b_restrict);
  cs_free(a_restrict);
  jagged1_free(rows_complement);
  return x;
}
