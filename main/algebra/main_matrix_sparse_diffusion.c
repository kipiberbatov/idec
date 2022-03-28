#include <errno.h>
#include <stdlib.h>
#include "double.h"
#include "int.h"
#include "matrix_sparse.h"

int main(int argc, char * argv[])
{
  int N;
  double tau;
  double * lhs, * u_0, * x;
  matrix_sparse * laplacian_0;
  char * laplacian_0_format, * laplacian_0_name, * lhs_format, * lhs_name,
       * out_format, * u_0_format, * u_0_name;
  
  if (argc != 10)
  {
    fputs("main - the number of command-line arguments must be 10\n", stderr);
    goto end;
  }
  
  laplacian_0_name = argv[1];
  laplacian_0_format = argv[2];
  laplacian_0 = 
    matrix_sparse_fscan_by_name(laplacian_0_name, laplacian_0_format);
  if (errno)
  {
    fputs("main - cannot scan laplacian_0\n", stderr);
    goto end;
  }
  
  lhs_name = argv[3];
  lhs_format = argv[4];
  lhs = double_array_fscan_by_name(lhs_name, laplacian_0->rows, lhs_format);
  if (errno)
  {
    fputs("main - cannot scan lhs\n", stderr);
    goto laplacian_0_free;
  }
  
  u_0_name = argv[5];
  u_0_format = argv[6];
  u_0 = double_array_fscan_by_name(u_0_name, laplacian_0->rows, u_0_format);
  if (errno)
  {
    fputs("main - cannot scan u_0\n", stderr);
    goto lhs_free;
  }
  
  tau = double_sscan(argv[7]);
  if (errno)
  {
    fputs("main - cannot scan N\n", stderr);
    goto u_0_free;
  }
  
  N = int_sscan(argv[8]);
  if (errno)
  {
    fputs("main - cannot scan N\n", stderr);
    goto u_0_free;
  }
  
  x = matrix_sparse_diffusion(laplacian_0, lhs, u_0, tau, N);
  if (errno)
  {
    fputs("main - cannot find x\n", stderr);
    goto u_0_free;
  }
  
  out_format = argv[9];
  fprintf(stdout, "%d\n", laplacian_0->rows);
  fprintf(stdout, "%d\n", N + 1);
  double_matrix_fprint(stdout, N + 1, laplacian_0->rows, x, out_format);
  if (errno)
  {
    fputs("main - cannot print x\n", stderr);
    goto x_free;
  }
  
x_free:
  free(x);
u_0_free:
  free(u_0);
lhs_free:
  free(lhs);
laplacian_0_free:
  matrix_sparse_free(laplacian_0);
end:
  return errno;
}
