#include <errno.h>
#include <stdlib.h>
#include "int.h"
#include "mesh_brick_private.h"

/* calculation in the case of a regular grid */
/*
void mesh_brick_cn(int * m_cn, int m_dim, int n)
{
  int p;

  for (p = 0; p <= m_dim; ++p)
    m_cn[p] =
      int_binomial(m_dim, p) * int_power(n + 1, m_dim - p) * int_power(n, p);
}
*/

void mesh_brick_cn(int * m_cn, int m_dim, const int * n)
{
  int bin_d_p, p, u;
  int a[MAX_DIM], n_bar_p[MAX_DIM];

  for (p = 0; p <= m_dim; ++p)
  {
    bin_d_p = int_binomial(m_dim, p);
    int_array_assign_identity(a, p);
    for (u = 0; u < bin_d_p; ++u)
    {
      mesh_brick_assign_n_bar(n_bar_p, m_dim, n, p, a);
      m_cn[p] += int_array_total_product(m_dim, n_bar_p);
      if (u < bin_d_p - 1)
        int_array_combination_next(a, m_dim, p);
    }
  }
}
