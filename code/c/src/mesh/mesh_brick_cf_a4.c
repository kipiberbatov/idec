#include <string.h>
#include "int.h"
#include "mesh_brick_private.h"

void mesh_brick_cf_a4(int * m_cf_a4, int d, const int * partitions)
{
  int bin_d_p, bin_p_q, index, index_b, comb_index, comb_passed,
      p, q, u, v, w_index, w_size, y_index, y_size;
  int a[MAX_DIM], b[MAX_DIM], b_bar[MAX_DIM], b_copy[MAX_DIM], choices[MAX_DIM],
      l[MAX_DIM], n_bar_p[MAX_DIM], n_bar_u_v[MAX_DIM], positions[MAX_DIM],
      y[MAX_DIM], y_plus_z[MAX_DIM], w[MAX_DIM], z[MAX_DIM];

  index = 0;
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
        mesh_brick_assign_n_bar(n_bar_p, d, partitions, p, a);
        y_size = int_array_total_product(d, n_bar_p);
        int_array_assign_constant(y, d, 0);
        for (y_index = 0; y_index < y_size; ++y_index)
        {
          index_b = 0;
          int_array_assign_identity(positions, q);
          for (v = 0; v < bin_p_q; ++v)
          {
            int_array_compress_to_sparse_array(b, q, positions, a);
            memcpy(b_copy, b, sizeof(int) * q);
            comb_passed = int_array_combination_index(b_copy, d, q);
            int_array_assign_identity(l, q);
            index_b = 0;
            for (comb_index = 0; comb_index < comb_passed; ++comb_index)
            {
              mesh_brick_assign_n_bar(n_bar_u_v, d, partitions, q, l);
              index_b += int_array_total_product(d, n_bar_u_v);
              int_array_combination_next(l, d, q);
            }
            mesh_brick_assign_n_bar(n_bar_u_v, d, partitions, q, b);
            int_array_set_difference(b_bar, p, a, q, b);
            int_array_assign_constant(w, p - q, 0);
            for (w_index = 0; w_index < w_size; ++w_index)
            {
              int_array_assign_constant(z, d, 0);
              int_array_assemble_from_sparse_array(z, p - q, b_bar, w);
              int_array_sum(y_plus_z, d, y, z);
              m_cf_a4[index] =
                index_b + int_array_flatten_index(d, n_bar_u_v, y_plus_z);
              ++index;
              if (w_index < w_size - 1)
                int_array_cartesian_product_next(w, p - q, choices);
            }
            if (v < bin_p_q - 1)
              int_array_combination_next(positions, p, q);
          }
          if (y_index < y_size - 1)
            int_array_cartesian_product_next(y, d, n_bar_p);
        }
        if (u < bin_d_p - 1)
          int_array_combination_next(a, d, p);
      }
    }
  }
}
