#include "cs.h"
// #include "double_fprint.h"
// #include "int_fprint.h"

static int jagged1_sorted_intersection_length(
  const jagged1 * arr1, const jagged1 * arr2)
{
  int i, j, res;
  
  i = 0; j = 0; res = 0;
  while (i < arr1->a0 && j < arr2->a0)
  {
    if (arr1->a1[i] < arr2->a1[j])
      ++i;
    else if (arr1->a1[i] == arr2->a1[j])
    {
      ++res;
      ++i;
      ++j;
    }
    else
      ++j;
  }
  return res;
}

static void jagged1_sorted_intersection_indices(
  int * res, const jagged1 * arr1, const jagged1 * arr2)
{
  int i, ind, j;
  
  i = 0; j = 0; ind = 0;
  while (i < arr1->a0 && j < arr2->a0)
  {
    if (arr1->a1[i] < arr2->a1[j])
      ++i;
    else if (arr1->a1[i] == arr2->a1[j])
    {
      res[ind] = j;
      ++ind;
      ++i;
      ++j;
    }
    else
      ++j;
  }
}

static int jagged1_subset_index(const jagged1 * arr, int el)
{
  int i;
  
  for (i = 0; i < arr->a0; ++i)
    if (arr->a1[i] == el)
      return i;
  return -1;
}

static int cs_remove_nzmax(const cs * a, const jagged1 * rows_complement,
                           const jagged1 * cols_complement)
{
  int b_nzmax, j, j_loc;
  jagged1 col;
  
  b_nzmax = 0;
  for (j_loc = 0; j_loc < cols_complement->a0; ++j_loc)
  {
    j = cols_complement->a1[j_loc];
    col.a0 = a->p[j + 1] - a->p[j];
    col.a1 = a->i + a->p[j];
    b_nzmax += jagged1_sorted_intersection_length(&col, rows_complement);
  }
  return b_nzmax;
}

static int * cs_remove_p(const cs * a, const jagged1 * rows_complement,
                         const jagged1 * cols_complement)
{
  int j, j_loc;
  int * b_p;
  jagged1 col;
  
  b_p = (int *) malloc((cols_complement->a0 + 1) * sizeof(int));
  /* NULL pointer check */
  b_p[0] = 0;
  for (j_loc = 0; j_loc < cols_complement->a0; ++j_loc)
  {
    j = cols_complement->a1[j_loc];
    col.a0 = a->p[j + 1] - a->p[j];
    col.a1 = a->i + a->p[j];
    b_p[j_loc + 1] = 
      b_p[j_loc] + jagged1_sorted_intersection_length(&col, rows_complement);
  }
  return b_p;
}

static int * cs_remove_i(const cs * a, const jagged1 * rows_complement,
                         const jagged1 * cols_complement, int b_nzmax,
                         const int * b_p)
{
  int j, j_loc;
  int * b_i;
  jagged1 col;
  
  b_i = (int *) malloc(b_nzmax * sizeof(int));
  /* NULL pointer check */
  for (j_loc = 0; j_loc < cols_complement->a0; ++j_loc)
  {
    j = cols_complement->a1[j_loc];
    col.a0 = a->p[j + 1] - a->p[j];
    col.a1 = a->i + a->p[j];
    jagged1_sorted_intersection_indices(
      b_i + b_p[j_loc], &col, rows_complement);
  }
  return b_i;
}

static double * cs_remove_x(const cs * a, const jagged1 * rows_complement,
                            const jagged1 * cols_complement, int b_nzmax,
                            const int * b_p, const int * b_i)
{
  int i, i_loc, j, j_loc;
  double * a_x_j, * b_x;
  jagged1 col;
  
  b_x = (double *) malloc(b_nzmax * sizeof(double));
  /* NULL pointer check */
  for (j_loc = 0; j_loc < cols_complement->a0; ++j_loc)
  {
    j = cols_complement->a1[j_loc];
    col.a0 = a->p[j + 1] - a->p[j];
    col.a1 = a->i + a->p[j];
    a_x_j = a->x + a->p[j];
    for (i_loc = b_p[j_loc]; i_loc < b_p[j_loc + 1]; ++i_loc)
    {
      i = jagged1_subset_index(&col, rows_complement->a1[b_i[i_loc]]);
      b_x[i_loc] = a_x_j[i];
    }
  }
  return b_x;
}

cs * cs_restrict(const cs * a, const jagged1 * rows_complement,
                 const jagged1 * cols_complement)
{
  cs * b;
  
  b = (cs *) malloc(sizeof(cs));
  /* NULL pointer check */
  b->nzmax = cs_remove_nzmax(a, rows_complement, cols_complement);
  // printf("%d\n", b->nzmax);
  b->m = rows_complement->a0;
  // printf("%d\n", b->m);
  b->n = cols_complement->a0;
  // printf("%d\n", b->n);
  b->p = cs_remove_p(a, rows_complement, cols_complement);
  /* NULL pointer check */
  // int_fprint_array_raw(stdout, (b->n + 1), b->p);
  b->i = cs_remove_i(a, rows_complement, cols_complement, b->nzmax, b->p);
  /* NULL pointer check */
  // int_fprint_array_raw(stdout, b->nzmax, b->i);
  b->x = cs_remove_x(a, rows_complement, cols_complement, b->nzmax, b->p, b->i);
  /* NULL pointer check */
  // double_fprint_array_raw(stdout, b->nzmax, b->x);
  b->nz = -1;
  // printf("%d\n", b->nz);
  return b;
}

cs * cs_remove(const cs * a, const jagged1 * rows, const jagged1 * cols)
{
  cs * b;
  jagged1 * rows_complement, * cols_complement;
  
  rows_complement = jagged1_complement(a->m, rows);
  /* NULL pointer check */
  cols_complement = jagged1_complement(a->n, cols);
  /* NULL pointer check */
  b = cs_restrict(a, rows_complement, cols_complement);
  /* NULL pointer check */
  jagged1_free(cols_complement);
  jagged1_free(rows_complement);
  return b;
}

cs * cs_remove_symmetric(const cs * a, const jagged1 * rows)
{
  cs * b;
  jagged1 * rows_complement;
  
  rows_complement = jagged1_complement(a->m, rows);
  /* NULL pointer check */
  b = cs_restrict(a, rows_complement, rows_complement);
  /* NULL pointer check */
  jagged1_free(rows_complement);
  return b;
}
