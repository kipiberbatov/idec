#include <errno.h>
#include "cs.h"
#include "double.h"

static void cs_diffusion_fprint(
  FILE * out, const cs * laplacian_0, const double * u_0, double tau, int N)
{
  double * x;
  
  x = cs_diffusion(laplacian_0, u_0, tau, N);
  if (errno)
  {
    perror("Cannot apply cs_diffusion");
    goto x_free;
  }
  fprintf(out, "%d\n", laplacian_0->m);
  double_fprint_array(out, laplacian_0->m, x);
x_free:
  free(x);
}

int main(int argc, char * argv[])
{
  int m_dim, N;
  double tau;
  double * u_0;
  cs * laplacian_0;
  cs ** laplacian;
  FILE * in, * out;
  
  out = stdout;
  in = stdin;
  m_dim = atoi(argv[1]);
  N = atoi(argv[2]);
  //fprintf(out, "N = %d\n", N);
  tau = atof(argv[3]);
  //fprintf(out, "tau = %g\n", tau);
  laplacian = cs_fscan_array(in, m_dim + 1);
  if (errno)
  {
    perror("Cannot scan left-hand side");
    goto laplacian_free;
  }
  laplacian_0 = laplacian[0];
  //cs_fprint(out, laplacian, "--raw");
  u_0 = double_fscan_array(in, laplacian_0->n);
  //double_fprint_array_raw(out, laplacian->n, u_0);
  if (errno)
  {
    perror("Cannot scan right-hand side");
    goto u_0_free;
  }
  cs_diffusion_fprint(out, laplacian_0, u_0, tau, N);
  if (errno)
  {
    perror("During calculation of cs_constrained_cholsol_fprint");
    goto u_0_free;
  }
u_0_free:
  free(u_0);
laplacian_free:
  cs_free_array(laplacian, m_dim + 1);
  return errno;
}
