#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include "int.h"
#include "double.h"
#include "matrix_sparse.h"

/* Finds the multiplier for the direct Euler method */
static matrix_sparse * matrix_sparse_laplacian_dynamic(
  const matrix_sparse * laplacian_0,
  double tau)
{
  matrix_sparse * id, * l;
  
  id = matrix_sparse_identity(laplacian_0->cols);
  if (errno)
  {
    fputs("matrix_sparse_laplacian_dynamic - cannot calculate id\n", stderr);
    return NULL;
  }
  
  l = matrix_sparse_linear_combination(laplacian_0, id, tau, 1);
  if (errno)
    fputs("matrix_sparse_laplacian_dynamic - cannot calculate l\n", stderr);
  
  matrix_sparse_free(id);
  return l;
}

/* Solve the time-dependent Laplacian problem with explicit Euler method */
// double * matrix_sparse_diffusion(
//   const matrix_sparse * laplacian_0,
//   const double * lhs,
//   const double * u_0,
//   double tau,
//   int N)
// {
//   int i;
//   double * u; /* 2d rectangular array */
//   matrix_sparse * l;
//
//   l = matrix_sparse_laplacian_dynamic(laplacian_0, tau);
//   if (errno)
//   {
//     fputs("matrix_sparse_diffusion - cannot calculate l\n", stderr);
//     goto end;
//   }
//
//   u = (double *) malloc(sizeof(double) * l->cols * (N + 1));
//   if (errno)
//   {
//     fputs("matrix_sparse_diffusion - cannot allocate memory for u\n",
//           stderr);
//     goto l_free;
//   }
//
//   memcpy(u, u_0, sizeof(double) * l->cols);
//   for (i = 1; i <= N; ++i)
//   {
//     memcpy(u + l->cols * i, u + l->cols * (i - 1), sizeof(double) * l->cols);
//     double_array_add_to(u + l->cols * i, l->cols, lhs);
//     // matrix_sparse_linear_solve(l, u + l->cols * i, "--cholesky");
//     matrix_sparse_linear_solve(l, u + l->cols * i, "--lu");
//     if (errno)
//     {
//       fputs("matrix_sparse_diffusion - cannot find u[i]\n", stderr);
//       goto u_free;
//     }
//   }
//
//   matrix_sparse_free(l);
//
//   return u;
//
//   /* cleaning if an error occurs */
// u_free:
//   free(u);
// l_free:
//   matrix_sparse_free(l);
// end:
//   return NULL;
// }
