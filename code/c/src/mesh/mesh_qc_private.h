#ifndef _mesh_qc_private_h
#define _mesh_qc_private_h

#include "mesh_qc.h"

double mesh_qc_cup_product_sign(
  matrix_sparse ** m_bd, int node, int p, int i, int q, int j, int r, int k);

void mesh_qc_perpendicular(
  int * nodes, int * perp, const jagged2 * m_cf_d_q, const jagged2 * m_cf_p_0,
  const jagged2 * m_cf_q_0, int i, int k);

void mesh_qc_hodge_p_cols_total(
  int * m_hodge_p_cols_total, const mesh * m, int p);

void mesh_qc_hodge_p_row_indices(
  int * m_hodge_p_row_indices, const mesh * m, int p);

void mesh_qc_hodge_p_values(
  double * m_hodge_p_values, const mesh * m, matrix_sparse ** m_bd, int p,
  const double * m_inner_q, const double * m_coeff_q);

#endif /* _mesh_qc_private_h */
