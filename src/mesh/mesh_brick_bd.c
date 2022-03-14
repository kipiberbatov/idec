#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include "imath.h"
#include "int.h"
#include "mesh_brick.h"

static void set_n_bar(int * n_bar, int d, const int * n, int p, const int * a)
{
  int r;
  
  for (r = 0; r < d; ++r)
    n_bar[r] = (int_array_member(p, a, r)) ? n[r] : (n[r] + 1);
}

int ** mesh_brick_bd(int d, const int * n, const int * m_bd_sizes)
{
  int bin_d_p, ind, p, sign_p, sign_v, u, v, y_ind, y_size;
  int a[MAX_DIM], n_bar_p[MAX_DIM];
  int * m_bd_p;
  int ** m_bd;
  
  m_bd = (int **) malloc(sizeof(int *) * d);
  if (errno)
  {
    perror("Cannot allocate memory for m->bd");
    goto end;
  }
  sign_p = 1;
  for (p = 1; p <= d; ++p)
  {
    ind = 0;
    bin_d_p = imath_binom(d, p);
    m_bd_p = (int *) malloc(sizeof(int) * m_bd_sizes[p - 1]);
    if (errno)
    {
      fprintf(stderr, "Cannot allocate memory for m->bd[%d]: %s",
              p - 1, strerror(errno));
      goto m_bd_p_free;
    }
    int_array_assign_identity(a, p);
    for (u = 0; u < bin_d_p; ++u)
    {
      set_n_bar(n_bar_p, d, n, p, a);
      y_size = int_array_total_product(n_bar_p, 0, d);
      for (y_ind = 0; y_ind < y_size; ++y_ind)
      {
        sign_v = 1;
        for (v = 0; v < p; ++v)
        {
          m_bd_p[ind] = -sign_p * sign_v;
          m_bd_p[ind + 1] = sign_p * sign_v;
          ind += 2;
          sign_v *= -1;
        }
      }
      if (u < bin_d_p - 1)
        imath_combination_next(a, d, p);
    }
    sign_p *= -1;
    m_bd[p - 1] = m_bd_p;
  }
  return m_bd;

  /* cleaning if an error occurs */
m_bd_p_free:
  int_free_array2(m_bd, p - 1);
end:
  return NULL;
}
