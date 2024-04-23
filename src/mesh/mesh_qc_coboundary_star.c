#include <math.h>
#include <stdlib.h>
#include "mesh_qc.h"

/* q = p - 1 */
static double * mesh_qc_coboundary_star_p_x(
  const mesh_qc * m, int p, const matrix_sparse * m_bd_p,
  const double * m_inner_p, const double * m_inner_q)
{
  int i, ind, j, j_loc, m_bd_p_nonzero_max, m_cn_p;
  double sign, m_inner_p_i;
  double * m_bd_p_x, * m_cbd_star_p_x;
  jagged1 m_cf_p_q_i;
  jagged2 m_cf_p_q;

  m_cn_p = m->cn[p];
  m_bd_p_x = m_bd_p->values;
  m_bd_p_nonzero_max = m_bd_p->cols_total[m_bd_p->cols];
  m_cbd_star_p_x = (double *) malloc(sizeof(double) * m_bd_p_nonzero_max);
  /* NULL pointer check */
  mesh_cf_part2(&m_cf_p_q, m, p, p - 1);
  ind = 0;
  for (i = 0; i < m_cn_p; ++i)
  {
    jagged2_part1(&m_cf_p_q_i, &m_cf_p_q, i);
    m_inner_p_i = m_inner_p[i];
    for (j_loc = 0; j_loc < m_cf_p_q_i.a0; ++j_loc)
    {
      sign = m_bd_p_x[ind + j_loc];
      j = m_cf_p_q_i.a1[j_loc];
      m_cbd_star_p_x[ind + j_loc] = sign * m_inner_p_i / m_inner_q[j];
    }
    ind += m_cf_p_q_i.a0;
  }
  return m_cbd_star_p_x;
}

/* q = p - 1 */
matrix_sparse * mesh_qc_coboundary_star_p(
  const mesh_qc * m, int p, const matrix_sparse * m_bd_p,
  const double * m_inner_p, const double * m_inner_q)
{
  matrix_sparse * m_cbd_star_p;
  
  m_cbd_star_p = (matrix_sparse *) malloc(sizeof(matrix_sparse));
  /* NULL pointer check */
  //m_cbd_star_p->nzmax = m_bd_p->nzmax;
  m_cbd_star_p->rows = m_bd_p->rows;
  m_cbd_star_p->cols = m_bd_p->cols;
  m_cbd_star_p->cols_total = m_bd_p->cols_total;
  m_cbd_star_p->row_indices = m_bd_p->row_indices;
  m_cbd_star_p->values = 
    mesh_qc_coboundary_star_p_x(m, p, m_bd_p, m_inner_p, m_inner_q);
  /* NULL pointer check */
  //m_cbd_star_p->nz = m_bd_p->nz;
  return m_cbd_star_p;
}

matrix_sparse ** mesh_qc_coboundary_star(
  const mesh_qc * m, matrix_sparse ** m_bd, double ** m_inner)
{
  int m_dim, p;
  matrix_sparse ** m_cbd_star;
  
  m_dim = m->dim;
  m_cbd_star = (matrix_sparse **) malloc(sizeof(matrix_sparse *) * m_dim);
  /* NULL pointer check */
  for (p = 1; p <= m_dim; ++p)
  {
    m_cbd_star[p - 1] =
      mesh_qc_coboundary_star_p(m, p, m_bd[p - 1], m_inner[p], m_inner[p - 1]);
    /* NULL pointer check */
  }
  return m_cbd_star;
}
