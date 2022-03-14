#include "vec_sparse.h"
#include "stdlib.h"

vec_sparse * vec_sparse_add(const vec_sparse * a, const vec_sparse * b)
{
  return NULL;
}

/* a = -a */
void vec_sparse_negate(vec_sparse * a)
{
  int a_nzmax, i;
  double * a_x;
  
  a_nzmax = a->nzmax;
  a_x = a->x;
  
  for (i = 0; i < a_nzmax; ++i)
    a_x[i] = -a_x[i];
}

vec_sparse * vec_sparse_subtract(const vec_sparse * a, const vec_sparse * b)
{
  return NULL;
}

vec_sparse * vec_sparse_scalar_multiply(const vec_sparse * a, double alpha)
{
  int a_nzmax, i;
  double * a_x, * b_x;
  vec_sparse * b;
  
  a_nzmax = a->nzmax;
  a_x = a->x;
  b = (vec_sparse *) malloc(sizeof(vec_sparse));
  /* NULL pointer check */
  b->nzmax = a_nzmax;
  b->n = a->n;
  b->p = a->p;
  b_x = (double *) malloc(a_nzmax * sizeof(double));
  /* NULL pointer check */
  for (i = 0; i < a_nzmax; ++i)
    b_x[i] = alpha * a_x[i];
  return b;
}

/* a *= alpha */
void vec_sparse_scalar_multiply_with(vec_sparse * a, int alpha)
{
  int a_nzmax, i;
  double * a_x;
  
  a_nzmax = a->nzmax;
  a_x = a->x;
  
  for (i = 0; i < a_nzmax; ++i)
    a_x[i] *= alpha;
}

double vec_sparse_dot_product(const vec_sparse * a, const vec_sparse * b)
{
  /*
  int a_nzmax, b_nzmax, i, j, tmp;
  double res = 0.;
  double * a_x, * b_x, * a_p, * b_p;
  
  if(a->n != b->n)
    return 0.;
  
  a_nzmax = a->nzmax;
  b_nzmax = b->nzmax;
  a_x = a->x;
  b_x = b->x;
  
  j = 0;
  for (i = 0; i < a_nzmax; ++i)
  {
    tmp = a[i];
    while ((b[j] != tmp) && (j < b_nzmax))
      ++j;
    if (j != n2)
    {
      res += x[i] * y[j];
    }
    else
      j = 0;
  }
  return res;
  */
  return 0.;
}

vec_sparse * vec_sparse_matrix_times_vector(const cs * a, const vec_sparse * b)
{
  return NULL;
}
