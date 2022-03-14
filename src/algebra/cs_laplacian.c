#include <errno.h>
#include "cs.h"

cs * cs_laplacian_0(const cs * a_0, const cs * b_1)
{
  cs * delta_0;
  
  delta_0 = cs_multiply(b_1, a_0);
  if (errno)
  {
    perror("Cannot multiply matrices");
    cs_free(delta_0);
    return NULL;
  }
  return delta_0;
}

cs * cs_laplacian_p(const cs * a_p_minus_1, const cs * a_p, 
                    const cs * b_p, const cs * b_p_plus_1)
{
  cs * delta_p, * tmp1, * tmp2;
  
  delta_p = NULL;
  tmp1 = cs_multiply(b_p_plus_1, a_p);
  if (errno)
  {
    perror("Cannot multiply matrices");
    goto tmp1_free;
  }
  tmp2 = cs_multiply(a_p_minus_1, b_p);
  if (errno)
  {
    perror("Cannot multiply matrices");
    goto tmp2_free;
  }
  delta_p = cs_add(tmp1, tmp2, 1., 1.);
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

cs * cs_laplacian_d(const cs * a_d_minus_1, const cs * b_d)
{
  cs * delta_d;
  
  delta_d = cs_multiply(a_d_minus_1, b_d);
  if (errno)
  {
    perror("Cannot multiply matrices");
    cs_free(delta_d);
    return NULL;
  }
  return delta_d;
}

cs ** cs_laplacian(int d, cs ** a, cs ** b)
{
  int p;
  cs ** delta;
  
  delta = (cs **) malloc((d + 1) * sizeof(cs *));
  if (errno)
  {
    perror("Cannot allocate memory for laplacians");
    free(delta);
    return NULL;
  }
  delta[0] = cs_multiply(b[0], a[0]);
  if (errno)
  {
    perror("Cannot calculate 0-laplacian");
    cs_free_array(delta, 1);
    return NULL;
  }
  for (p = 1; p < d; ++p)
  {
    delta[p] = cs_laplacian_p(a[p - 1], a[p], b[p - 1], b[p]);
    if (errno)
    {
      fprintf(stderr, "Cannot calculate %d-laplacian", p);
      perror("");
      cs_free_array(delta, p + 1);
      return NULL;
    }
  }
  delta[d] = cs_multiply(a[d - 1], b[d - 1]);
  if (errno)
  {
    fprintf(stderr, "Cannot calculate %d-laplacian", d);
    perror("");
    cs_free_array(delta, d + 1);
    return NULL;
  }
  return delta;
}

static void cs_laplacian_error_handling(cs * delta_p, int p)
{
  fprintf(stderr, "Cannot calculate %d-laplacian", p);
  perror("");
  free(delta_p);
}

void cs_laplacian_fprint(FILE * out, int d, cs ** a, cs ** b,
                         const char * format)
{
  int p;
  cs * delta_p;
  
  p = 0;
  delta_p = cs_multiply(b[p], a[p]);
  if (errno)
  {
    cs_laplacian_error_handling(delta_p, p);
    return;
  }
  cs_fprint(out, delta_p, format);
  if (errno)
  {
    perror(format);
    cs_free(delta_p);
    return;
  }
  cs_free(delta_p);
  fputc('\n', out);
  /* p = 1 ... d - 1 */
  for (p = 1; p < d; ++p)
  {
    delta_p = cs_laplacian_p(a[p - 1], a[p], b[p - 1], b[p]);
    if (errno)
    {
      cs_laplacian_error_handling(delta_p, p);
      return;
    }
    cs_fprint(out, delta_p, format);
    if (errno)
    {
      perror(format);
      cs_free(delta_p);
      return;
    }
    cs_free(delta_p);
    fputc('\n', out);
  }
  /* p = d */
  delta_p = cs_multiply(a[p - 1], b[p - 1]);
  if (errno)
  {
    cs_laplacian_error_handling(delta_p, p);
    return;
  }
  cs_fprint(out, delta_p, format);
  if (errno)
  {
    perror(format);
    cs_free(delta_p);
    return;
  }
  cs_free(delta_p);
}
