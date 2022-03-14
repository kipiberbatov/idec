
#include <string.h>
#include "cs.h"
#include "double.h"

static cs * cs_identity_matrix(int n)
{
  int j;
  cs * a;
  
  a = (cs *) malloc(sizeof(cs));
  /* NULL pointer check */
  a->m = n;
  a->n = n;
  a->nzmax = n;
  a->p = (int *) malloc(sizeof(int) * (n + 1));
  /* NULL pointer check */
  for(j = 0; j <= n; ++j)
    a->p[j] = j;
  a->i = (int *) malloc(sizeof(int) * n);
  /* NULL pointer check */
  for(j = 0; j < n; ++j)
    a->i[j] = j;
  a->x = (double *) malloc(sizeof(double) * n);
  /* NULL pointer check */
  for(j = 0; j < n; ++j)
    a->x[j] = 1;
  a->nz = -1;
  return a;
}

static cs * cs_laplacian_dynamic(const cs * laplacian_0, double tau)
{
  int n;
  cs * id, * l;
  
  n  = laplacian_0->n;
  id = cs_identity_matrix(n);
  //cs_fprint(stdout, id, "--raw");
  /* NULL pointer check */
  l = cs_add(id, laplacian_0, 1, -tau);
  //cs_fprint(stdout, l, "--raw");
  /* NULL pointer check */
  cs_free(id);
  return l;
}

// double * cs_diffusion_next(const cs * laplacian, const double * u, double tau)
// {
//   int n;
//   double * res;
//   cs * l;
//
//   l = cs_laplacian_dynamic(laplacian, tau);
//   /* NULL pointer check */
//   res = cs_cholsol(l, u);
//   /* NULL pointer check */
//   cs_free(l);
//   return res;
// }

double * cs_diffusion(
  const cs * laplacian_0, const double * u_0, double tau, int N)
{
  int i;
  double * u_next;
  cs * l;
  
  //fputs("c\n", stderr);
  //double_fprint_array_raw(stderr, laplacian_0->n, u_0);
  //fputs("\nd\n", stderr);
  l = cs_laplacian_dynamic(laplacian_0, tau);
  cs_fprint(stdout, l, "--matrix-form-curly");
  fputs("\n", stdout);
  /* NULL pointer check */
  u_next = (double *) malloc(sizeof(double) * l->n);
  /* NULL pointer check */
  memcpy(u_next, u_0, sizeof(double) * l->n);
  double_fprint_array(stdout, l->n, u_next);
  fputs("\n", stdout);
  cs_cholsol(1, l, u_next);
  double_fprint_array(stdout, l->n, u_next);
  fputs("\n", stdout);
  for (i = 0; i < N; ++i)
  {
    cs_cholsol(1, l, u_next);
    double_fprint_array_raw(stdout, l->n, u_next);
    /* NULL pointer check */
  }
  //fputs("\ng\n", stderr);
  return u_next;
}
