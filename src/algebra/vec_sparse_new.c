#include <stdlib.h>
#include "vec_sparse.h"

vec_sparse * vec_sparse_new(int a_nzmax, int a_n, int * a_p, double * a_x)
{
  vec_sparse * a;
  a = (vec_sparse *) malloc(sizeof(vec_sparse));
  /* NULL pointer check */
  a->nzmax = a_nzmax;
  a->n = a_n;
  a->p = a_p;
  a->x = a_x;
  return a;
}

vec_sparse ** vec_sparse_array_new(
  int n, int * a_nzmax, int * a_n, int ** a_p, double ** a_x)
{
  int i;
  vec_sparse ** a;
  
  a = (vec_sparse **) malloc(n * sizeof(vec_sparse *));
  /* NULL pointer check */
  for (i = 0; i < n; ++i)
    a[i] = vec_sparse_new(a_nzmax[i], a_n[i], a_p[i], a_x[i]);
  return a;
}