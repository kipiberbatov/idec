#include <stdio.h>
#include "double.h"
#include "int.h"
#include "vec_sparse.h"

void vec_sparse_fprint_annotated(FILE * out, const vec_sparse * a)
{
  int a_nzmax, i;
  int * a_p;
  double * a_x;
  
  a_nzmax = a->nzmax;
  a_p = a->p;
  a_x = a->x;
  for (i = 0; i < a_nzmax; ++i)
    fprintf(out, "  %d : %g\n", a_p[i], a_x[i]);
  fputs("\n", out);
}

void vec_sparse_fprint(FILE * out, const vec_sparse * a)
{
  int a_n, a_nzmax;
  int * a_p;
  double * a_x;
  
  a_nzmax = a->nzmax;
  a_n = a->n;
  a_p = a->p;
  a_x = a->x;
  fprintf(out, "%d\n", a_nzmax);
  fprintf(out, "%d\n", a_n);
  int_fprint_array_raw(out, a_nzmax, a_p);
  double_fprint_array_raw(out, a_nzmax, a_x);
}

void vec_sparse_fprint_array(FILE * out, int a0, vec_sparse ** arr)
{
  int i;
  
  for (i = 0; i < a0; ++i)
    vec_sparse_fprint(out, arr[i]);
}

void vec_sparse_fprint_array2(FILE * out, int a0, const int * a1,
                              vec_sparse *** arr)
{
  int i;
  
  for (i = 0; i < a0; ++i)
    vec_sparse_fprint_array(out, a1[i], arr[i]);
}
