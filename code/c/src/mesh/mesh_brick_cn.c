#include "int.h"
#include "mesh_brick_private.h"

/* calculation in the case of a regular grid */
/*
void mesh_brick_cn(int * m_cn, int d, int n)
{
  int p;

  for (p = 0; p <= d; ++p)
    m_cn[p] = int_binomial(d, p) * int_power(n + 1, d - p) * int_power(n, p);
}
*/

void mesh_brick_cn(int * m_cn, int d, const int * partitions)
{
  int bin_d_p, p, u;
  int a[MAX_DIM], n_bar_p[MAX_DIM];

  for (p = 0; p <= d; ++p)
  {
    bin_d_p = int_binomial(d, p);
    int_array_assign_identity(a, p);
    for (u = 0; u < bin_d_p; ++u)
    {
      mesh_brick_assign_n_bar(n_bar_p, d, partitions, p, a);
      m_cn[p] += int_array_total_product(d, n_bar_p);
      if (u < bin_d_p - 1)
        int_array_combination_next(a, d, p);
    }
  }
}
