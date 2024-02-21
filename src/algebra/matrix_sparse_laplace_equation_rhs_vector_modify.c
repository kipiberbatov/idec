#include "matrix_sparse.h"

/*
Modifies the right-hand side vector of Laplace equation with Dirichlet boundary
conditions by using the known values on the boundary.
The variables have the following meanings:
  . b_in is the vector corresponding to interior nodes;
  . m_laplacian is the Laplacian matrix in the chosen basis;
  . m_nodes_in are the indices of interior nodes;
  . m_nodes_bd are the indices of Dirichlet boundary nodes;
  . b_bd is the known vector representing Dirichlet boundary conditions.
*/

void matrix_sparse_laplace_equation_rhs_vector_modify(
  double * b_in,
  const matrix_sparse * m_laplacian,
  const jagged1 * m_nodes_in,
  const jagged1 * m_nodes_bd,
  const double * b_bd)
{
  int i, i_loc, j, j_loc, m_nodes_bd_a0, nonzeroes_j, position;
  int * m_laplacian_cols_total, * m_laplacian_row_indices,
      * m_laplacian_row_indices_col_j, * m_nodes_bd_a1;
  double m_laplacian_values_i_j;
  double * m_laplacian_values, * m_laplacian_values_col_j;
  
  m_nodes_bd_a0 = m_nodes_bd->a0;
  m_nodes_bd_a1 = m_nodes_bd->a1;
  m_laplacian_cols_total = m_laplacian->cols_total;
  m_laplacian_row_indices = m_laplacian->row_indices;
  m_laplacian_values = m_laplacian->values;
  
  for (j_loc = 0; j_loc < m_nodes_bd_a0; ++j_loc)
  {
    j = m_nodes_bd_a1[j_loc];
    m_laplacian_row_indices_col_j = 
      m_laplacian_row_indices + m_laplacian_cols_total[j];
    m_laplacian_values_col_j = m_laplacian_values + m_laplacian_cols_total[j];
    nonzeroes_j = m_laplacian_cols_total[j + 1] - m_laplacian_cols_total[j];
    for (i_loc = 0; i_loc < nonzeroes_j; ++i_loc)
    {
      i = m_laplacian_row_indices_col_j[i_loc];
      position = jagged1_position(m_nodes_in, i);
      if (position != -1)
      {
        m_laplacian_values_i_j = m_laplacian_values_col_j[i_loc];
        b_in[position] -= m_laplacian_values_i_j * b_bd[j_loc];
      }
    }
  }
}
