#include <stdlib.h>
#include "imath.h"
#include "list.h"
#include "mesh_brick.h"

// int * mesh_brick_cn(int m_dim, int n)
// {
//   int p;
//   int * m_cn;
//
//   m_cn = (int *) malloc((m_dim + 1) * sizeof(int));
//   /* NULL pointer check */
//   for (p = 0; p <= m_dim; ++p)
//     m_cn[p] =
//       imath_binom(m_dim, p) * imath_pow(n + 1, m_dim - p) * imath_pow(n, p);
//   return m_cn;
// }

static void array_set_to_identity(int * a, int n)
{
  int i;
  
  for (i = 0; i < n; ++ i)
    a[i] = i;
}

static int member(int n, const int * a, int element)
{
  int i;
  
  for (i = 0; i < n; ++i)
    if (element == a[i])
      return 1;
  return 0;
}

static void set_n_bar(int * n_bar, int d, const int * n, int p, const int * a)
{
  int r;
  
  for (r = 0; r < d; ++r)
    n_bar[r] = (member(p, a, r)) ? n[r] : (n[r] + 1);
}

int * mesh_brick_cn(int m_dim, const int * n)
{
  int bin_m_dim_p, p, u;
  int a[MAX_DIM], n_bar_p[MAX_DIM];
  int * m_cn;
  
  m_cn = (int *) calloc((m_dim + 1), sizeof(int));
  /* NULL pointer check */
  for (p = 0; p <= m_dim; ++p)
  {
    bin_m_dim_p = imath_binom(m_dim, p);
    array_set_to_identity(a, p);
    for (u = 0; u < bin_m_dim_p; ++u)
    {
      set_n_bar(n_bar_p, m_dim, n, p, a);
      m_cn[p] += list_product(n_bar_p, 0, m_dim);
      if (u < bin_m_dim_p - 1)
        imath_combination_next(a, m_dim, p);
    }
  }
  return m_cn;
}
