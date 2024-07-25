#include <errno.h>
#include <stdlib.h>
#include "matrix_sparse.h"

matrix_sparse * matrix_sparse_laplacian_0(
  const matrix_sparse * a_0, const matrix_sparse * b_1)
{
  matrix_sparse * delta_0;
  
  delta_0 = matrix_sparse_product(b_1, a_0);
  if (errno)
  {
    perror("Cannot multiply matrices");
    matrix_sparse_free(delta_0);
    return NULL;
  }
  return delta_0;
}

matrix_sparse * matrix_sparse_laplacian_p(
  const matrix_sparse * a_p_minus_1, const matrix_sparse * a_p, 
  const matrix_sparse * b_p, const matrix_sparse * b_p_plus_1)
{
  matrix_sparse * delta_p, * tmp1, * tmp2;
  
  delta_p = NULL;
  tmp1 = matrix_sparse_product(b_p_plus_1, a_p);
  if (errno)
  {
    perror("Cannot multiply matrices");
    goto tmp1_free;
  }
  tmp2 = matrix_sparse_product(a_p_minus_1, b_p);
  if (errno)
  {
    perror("Cannot multiply matrices");
    goto tmp2_free;
  }
  delta_p = matrix_sparse_add(tmp1, tmp2);
  if (errno)
  {
    perror("Cannot add matrices");
    goto tmp2_free;
  }
tmp2_free:
  free(tmp2);
tmp1_free:
  free(tmp1);
  return delta_p;
}

matrix_sparse * matrix_sparse_laplacian_d(
  const matrix_sparse * a_d_minus_1, const matrix_sparse * b_d)
{
  matrix_sparse * delta_d;
  
  delta_d = matrix_sparse_product(a_d_minus_1, b_d);
  if (errno)
  {
    perror("Cannot multiply matrices");
    matrix_sparse_free(delta_d);
    return NULL;
  }
  return delta_d;
}

matrix_sparse ** matrix_sparse_laplacian(
  int d, matrix_sparse ** a, matrix_sparse ** b)
{
  int p;
  matrix_sparse ** delta;
  
  delta = (matrix_sparse **) malloc((d + 1) * sizeof(matrix_sparse *));
  if (errno)
  {
    perror("Cannot allocate memory for laplacians");
    free(delta);
    return NULL;
  }
  delta[0] = matrix_sparse_product(b[0], a[0]);
  if (errno)
  {
    perror("Cannot calculate 0-laplacian");
    matrix_sparse_array_free(delta, 1);
    return NULL;
  }
  for (p = 1; p < d; ++p)
  {
    delta[p] = matrix_sparse_laplacian_p(a[p - 1], a[p], b[p - 1], b[p]);
    if (errno)
    {
      fprintf(stderr, "Cannot calculate %d-laplacian: ", p);
      perror("");
      matrix_sparse_array_free(delta, p + 1);
      return NULL;
    }
  }
  delta[d] = matrix_sparse_product(a[d - 1], b[d - 1]);
  if (errno)
  {
    fprintf(stderr, "Cannot calculate %d-laplacian: ", d);
    perror("");
    matrix_sparse_array_free(delta, d + 1);
    return NULL;
  }
  return delta;
}

static void matrix_sparse_laplacian_error_handling(
  matrix_sparse * delta_p, int p)
{
  fprintf(stderr, "Cannot calculate %d-laplacian: ", p);
  perror("");
  free(delta_p);
}

void matrix_sparse_laplacian_file_print(
  FILE * out, int d, matrix_sparse ** a, matrix_sparse ** b,
  const char * format)
{
  int p;
  matrix_sparse * delta_p;
  
  p = 0;
  delta_p = matrix_sparse_product(b[p], a[p]);
  if (errno)
  {
    matrix_sparse_laplacian_error_handling(delta_p, p);
    return;
  }
  matrix_sparse_file_print(out, delta_p, format);
  if (errno)
  {
    perror(format);
    matrix_sparse_free(delta_p);
    return;
  }
  matrix_sparse_free(delta_p);
  fputc('\n', out);
  /* p = 1 ... d - 1 */
  for (p = 1; p < d; ++p)
  {
    delta_p = matrix_sparse_laplacian_p(a[p - 1], a[p], b[p - 1], b[p]);
    if (errno)
    {
      matrix_sparse_laplacian_error_handling(delta_p, p);
      return;
    }
    matrix_sparse_file_print(out, delta_p, format);
    if (errno)
    {
      perror(format);
      matrix_sparse_free(delta_p);
      return;
    }
    matrix_sparse_free(delta_p);
    fputc('\n', out);
  }
  /* p = d */
  delta_p = matrix_sparse_product(a[p - 1], b[p - 1]);
  if (errno)
  {
    matrix_sparse_laplacian_error_handling(delta_p, p);
    return;
  }
  matrix_sparse_file_print(out, delta_p, format);
  if (errno)
  {
    perror(format);
    matrix_sparse_free(delta_p);
    return;
  }
  matrix_sparse_free(delta_p);
}
