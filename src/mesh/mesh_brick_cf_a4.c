#include <string.h>
#include "int.h"
#include "mesh_brick_private.h"

void mesh_brick_cf_a4(int * m_cf_a4, int d, const int * n)
{
  int bin_d_p, bin_p_q, h, ind, ind_b, comb_ind, comb_passed,
      p, q, u, v, w_ind, w_size, y_ind, y_size;
  int a[MAX_DIM], b[MAX_DIM], b_bar[MAX_DIM], b_copy[MAX_DIM], choices[MAX_DIM],
      l[MAX_DIM], n_bar_p[MAX_DIM], n_bar_u_v[MAX_DIM], positions[MAX_DIM],
      y[MAX_DIM], y_plus_z[MAX_DIM], w[MAX_DIM], z[MAX_DIM];
    
  ind = 0;
  for (p = 1; p <= d; ++p)
  {
    bin_d_p = int_binomial(d, p);
    for (q = 0; q < p; ++q)
    {
      bin_p_q = int_binomial(p, q);
      int_array_assign_constant(choices, p - q, 2);
      w_size = 1 << (p - q);
      int_array_assign_identity(a, p);
      for (u = 0; u < bin_d_p; ++u)
      {
        mesh_brick_assign_n_bar(n_bar_p, d, n, p, a);
        y_size = int_array_total_product(d, n_bar_p);
        int_array_assign_constant(y, d, 0);
        for (y_ind = 0; y_ind < y_size; ++y_ind)
        {
          ind_b = 0;
          h = 0;
          int_array_assign_identity(positions, q);
          for (v = 0; v < bin_p_q; ++v)
          {
            int_array_substitute(b, q, a, positions);
            memcpy(b_copy, b, sizeof(int) * q);
            comb_passed = int_array_combination_index(b_copy, d, q);
            int_array_assign_identity(l, q);
            ind_b = 0;
            for (comb_ind = 0; comb_ind < comb_passed; ++comb_ind)
            {
              mesh_brick_assign_n_bar(n_bar_u_v, d, n, q, l);
              ind_b += int_array_total_product(d, n_bar_u_v);
              int_array_combination_next(l, d, q);
            }
            mesh_brick_assign_n_bar(n_bar_u_v, d, n, q, b);
            int_array_set_difference(b_bar, p, a, q, b);
            int_array_assign_constant(w, p - q, 0);
            for (w_ind = 0; w_ind < w_size; ++w_ind)
            {
              int_array_assign_constant(z, d, 0);
              int_array_substitute_inverse(z, p - q, w, b_bar);
              int_array_sum(y_plus_z, d, y, z);
              m_cf_a4[ind] = 
                ind_b + int_array_flatten_index(d, n_bar_u_v, y_plus_z);
              ++ind;
              if (w_ind < w_size - 1)
                int_array_cartesian_product_next(w, p - q, choices);
            }
            if (v < bin_p_q - 1)
              int_array_combination_next(positions, p, q);
          }
          if (y_ind < y_size - 1)
            int_array_cartesian_product_next(y, d, n_bar_p);
        }
        if (u < bin_d_p - 1)
          int_array_combination_next(a, d, p);
      }
    }
  }
}
