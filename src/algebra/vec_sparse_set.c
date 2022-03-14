#include "vec_sparse.h"

void vec_sparse_set(
  vec_sparse * a, int a_nzmax, int a_n, int * a_p, double * a_x)
{
  a->nzmax = a_nzmax;
  a->n = a_n;
  a->p = a_p;
  a->x = a_x;
}