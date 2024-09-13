#include <stdlib.h>

#include "mesh_qc.h"

/*
********************************* declaration **********************************
Let
  . $d$ be a natural number,
  . $M$ be an oriented quasi-cubical mesh of dimension $d$
    with fundamental class [M].
In the mixed formulation for heat equation we have the operator
$b: C^{d - 1} M * C^0 M -> R$
defined by
$b(y^{d - 1}, x^0) := $(x^0 \_/ delta_{d - 1} y^{d - 1})[K]$.
We are going to calculate the matrix $B$ of $b$
with respect to the standard bases of $C^0 M$ and $C^{d - 1} M$, i.e.,
$b_{i, j} := $b(c^{d - 1, i}, c^{0, j})$.

********************************** definition **********************************
take a node N_j  
  0 F_i is not a boundary of the 3-coboundary of N_j -> b_{i, j} = 0
  1 F_i is a boundary of the 3-coboundary of N_j
      0 N_j is not on the boundary of F_i: let V_k be the common volume
        -> b_{i, j} = 1 / 2^d epsilon(V_k, F_i)
      1 N_j is on the boundary of F_i
          0 F_i is interior -> b_{i, j} = 0
          1 F_i is boundary with coboundary V_k
            -> b_{i, j} = 1 / 2^d epsilon(V_k, F_i)
            which is always 1 / 2^d when d > 1 and orientation is positive

algorithm
  . take a cell N_i
  . count the number of cells F_i satisfying 1.0 or 1.1.1
  . take the indices of those cells
  . calculate the values
    (more precisely, the signs epsilon(V_k, F_i) before 1 / 2^d)
*/

static void 
mesh_qc_matrix_sparse_from_integral_of_basis_0_cup_delta_basis_dm1_cols_total(
  int * b_cols_total,
  const mesh_qc * m);

static void
mesh_qc_matrix_sparse_from_integral_of_basis_0_cup_delta_basis_dm1_row_indices(
  int * b_row_indices,
  const mesh_qc * m);

static void
mesh_qc_matrix_sparse_from_integral_of_basis_0_cup_delta_basis_dm1_values(
  double * b_values,
  const mesh_qc * m,
  const matrix_sparse * m_bd_d);

matrix_sparse *
mesh_qc_matrix_sparse_from_integral_of_basis_0_cup_delta_basis_dm1(
  const mesh_qc * m,
  const matrix_sparse * m_bd_d)
{
  int d, nonzero_max;
  int * m_cn;
  matrix_sparse * b;
 
  d = m->dim;
  m_cn = m->cn;

  b = (matrix_sparse *) malloc(sizeof(matrix_sparse));
  if (b == NULL)
  {
    fprintf(stderr,
      "%s:%d: cannot allocate memory for sparse mtrix b\n", __FILE__, __LINE__);
    goto end;
  }

  b->rows = m_cn[d - 1];
  b->cols = m_cn[0];

  b->cols_total = (int *) malloc(sizeof(int) * (b->cols + 1));
  if (b->cols_total == NULL)
  {
    fprintf(stderr,
      "%s:%d: cannot allocate memory for b->cols_total\n", __FILE__, __LINE__);
    goto b_free;
  }
  mesh_qc_matrix_sparse_from_integral_of_basis_0_cup_delta_basis_dm1_cols_total(
    b->cols_total, m);

  nonzero_max = b->cols_total[b->cols];

  b->row_indices = (int *) malloc(sizeof(int) * nonzero_max);
  if (b->row_indices == NULL)
  {
    fprintf(stderr,
      "%s:%d: cannot allocate memory for b->row_indices\n", __FILE__, __LINE__);
    goto b_cols_total_free;
  }
  mesh_qc_matrix_sparse_from_integral_of_basis_0_cup_delta_basis_dm1_row_indices(
    b->row_indices, m);

  b->values = (double *) malloc(sizeof(double) * nonzero_max);
  if (b->values == NULL)
  {
    fprintf(stderr,
      "%s:%d: cannot allocate memory for b->values\n", __FILE__, __LINE__);
    goto b_row_indices_free;
  }
  mesh_qc_matrix_sparse_from_integral_of_basis_0_cup_delta_basis_dm1_values(
    b->values, m, m_bd_d);

  return b;

  /* cleaning if an error occurs */
b_row_indices_free:
  free(b->row_indices);
b_cols_total_free:
  free(b->cols_total);
b_free:
  free(b);
end:
  return NULL;
}
