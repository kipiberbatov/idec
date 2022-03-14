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

int * mesh_brick_cf_a4(int m_cf_a4_size, int d, const int * n)
{
  int bin_d_p, bin_p_q, h, ind, ind_b, comb_passed, comb_ind,
      p, q, u, v, w_ind, w_size, y_ind, y_size;
  int a[MAX_DIM], b[MAX_DIM], b_copy[MAX_DIM], b_bar[MAX_DIM], choices[MAX_DIM],
      k[MAX_DIM], l[MAX_DIM], n_bar_p[MAX_DIM], n_bar_u_v[MAX_DIM],
      w[MAX_DIM], y[MAX_DIM], y_plus_z[MAX_DIM], z[MAX_DIM];
  int * m_cf_a4;
    
  m_cf_a4 = (int *) malloc(sizeof(int) * m_cf_a4_size);
  if (errno)
  {
    perror("Cannot allocate memory for m->cf->a4");
    return NULL;
  }
  ind = 0;
  for (p = 1; p <= d; ++p)
  {
    bin_d_p = imath_binom(d, p);
    for (q = 0; q < p; ++q)
    {
      bin_p_q = imath_binom(p, q);
      int_array_assign_integer(choices, p - q, 2);
      w_size = 1 << (p - q);
      int_array_assign_identity(a, p);
      for (u = 0; u < bin_d_p; ++u)
      {
        set_n_bar(n_bar_p, d, n, p, a);
        y_size = int_array_total_product(n_bar_p, 0, d);
        int_array_assign_integer(y, d, 0);
        for (y_ind = 0; y_ind < y_size; ++y_ind)
        {
          ind_b = 0;
          h = 0;
          int_array_assign_identity(k, q);
          for (v = 0; v < bin_p_q; ++v)
          {
            int_array_substitute(b, q, a, k);
            memcpy(b_copy, b, sizeof(int) * q);
            comb_passed = imath_combination_index(b_copy, d, q);
            int_array_assign_identity(l, q);
            ind_b = 0;
            for (comb_ind = 0; comb_ind < comb_passed; ++comb_ind)
            {
              set_n_bar(n_bar_u_v, d, n, q, l);
              ind_b += int_array_total_product(n_bar_u_v, 0, d);
              imath_combination_next(l, d, q);
            }
            set_n_bar(n_bar_u_v, d, n, q, b);
            int_array_set_difference(b_bar, p, a, q, b);
            int_array_assign_integer(w, p - q, 0);
            for (w_ind = 0; w_ind < w_size; ++w_ind)
            {
              int_array_assign_integer(z, d, 0);
              int_array_substitute_inverse(z, p - q, b_bar, w);
              int_array_sum(y_plus_z, d, y, z);
              m_cf_a4[ind] = 
                ind_b + int_array_flatten_index(d, n_bar_u_v, y_plus_z);
              ++ind;
              if (w_ind < w_size - 1)
                imath_cartesian_product_next(w, p - q, choices);
            }
            if (v < bin_p_q - 1)
              imath_combination_next(k, p, q);
          }
          if (y_ind < y_size - 1)
            imath_cartesian_product_next(y, d, n_bar_p);
        }
        if (u < bin_d_p - 1)
          imath_combination_next(a, d, p);
      }
    }
  }
  return m_cf_a4;
}
