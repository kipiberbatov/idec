#include <string.h>
#include "array_indexed.h"
#include "double.h"
#include "int.h"
#include "mesh_qc.h"

vec_sparse ** mesh_qc_metric_corrected_p(
  const mesh_qc * m, int p, const double * m_vol_p, double * node_curvatures)
{
  int i, j, j_loc, m_cn_p, m_dim, m_metric_p_i_nzmax;
  int * m_metric_p_i_p, * m_cn;
  double node_curvature, denominator, m_vol_p_i;
  double * m_metric_p_i_x, * m_metric_p_i_x_tmp;
  jagged1 m_cell_nodes, volumes;
  vec_sparse ** m_metric_p;
  array_indexed a;

  m_dim = m->dim;
  m_cn = m->cn;
  m_cn_p = m_cn[p];
  m_metric_p = (vec_sparse **) malloc(m_cn_p * sizeof(vec_sparse *));
  /* NULL pointer check */
  for (i = 0; i < m_cn_p; ++i)
  {
    m_vol_p_i = m_vol_p[i];
    mesh_cf_part3(&m_cell_nodes, m, p, 0, i);
    denominator = ((double) m_cell_nodes.a0) * (m_vol_p_i * m_vol_p_i);
    m_metric_p_i_nzmax = m_cell_nodes.a0;
    m_metric_p_i_p = (int *) malloc(m_metric_p_i_nzmax * sizeof(int));
    /* NULL pointer check */
    memcpy(m_metric_p_i_p, m_cell_nodes.a1, sizeof(int) * m_cell_nodes.a0);
    m_metric_p_i_x = (double *) malloc(m_metric_p_i_nzmax * sizeof(double));
    /* NULL pointer check */
    for(j_loc = 0; j_loc < m_metric_p_i_nzmax; ++j_loc)
    {
      j = m_metric_p_i_p[j_loc];
      mesh_fc_part3(&volumes, m, 0, m_dim, j);
      //node_curvature = (1 << m_dim) / ((double) volumes.a0);
      node_curvature = node_curvatures[j];
      m_metric_p_i_x[j_loc] = node_curvature / denominator;
    }
    a.positions = (int *) malloc(m_metric_p_i_nzmax * sizeof(int));
    /* NULL pointer check */
    int_array_assign_identity(a.positions, m_metric_p_i_nzmax);
    a.values = m_metric_p_i_p;
    array_indexed_merge_sort(&a, m_metric_p_i_nzmax);
    /* NULL pointer check because merge sort uses temporary array copy */
    m_metric_p_i_x_tmp = (double *) malloc(m_metric_p_i_nzmax * sizeof(double));
    /* NULL pointer check */
    for (j_loc = 0; j_loc < m_metric_p_i_nzmax; ++j_loc)
      m_metric_p_i_x_tmp[j_loc] = m_metric_p_i_x[a.positions[j_loc]];
    for (j_loc = 0; j_loc < m_metric_p_i_nzmax; ++j_loc)
       m_metric_p_i_x[j_loc] = m_metric_p_i_x_tmp[j_loc];
    free(m_metric_p_i_x_tmp);
    free(a.positions);
    m_metric_p[i] = vec_sparse_new(m_metric_p_i_nzmax, m_cn[0],
                                   m_metric_p_i_p, m_metric_p_i_x);
  }
  return m_metric_p;
}

vec_sparse *** mesh_qc_metric_corrected(
  const mesh_qc * m, double ** m_vol, double * node_curvatures)
{
  int m_dim, p;
  vec_sparse *** m_metric;
  
  m_dim = m->dim;
  m_metric = (vec_sparse ***) malloc((m_dim + 1) * sizeof(vec_sparse **));
  /* NULL pointer check */
  for (p = 0; p <= m_dim; ++p)
  {
    m_metric[p] = 
      mesh_qc_metric_corrected_p(m, p, m_vol[p], node_curvatures);
    /* NULL pointer check */
  }
  return m_metric;
}

vec_sparse ** mesh_qc_metric_corrected_p_fscan(
  FILE * in, const mesh_qc * m, int p)
{
  int i, m_metric_p_i_nzmax, m_cn_p;
  int * m_metric_p_i_p, * m_cn;
  double * m_metric_p_i_x;
  jagged1 m_cell_nodes;
  vec_sparse ** m_metric_p;
  
  m_cn = m->cn;
  m_cn_p = m_cn[p];
  m_metric_p = (vec_sparse **) malloc(m_cn_p * sizeof(vec_sparse *));
  /* NULL pointer check */
  for (i = 0; i < m_cn_p; ++i)
  {
    mesh_cf_part3(&m_cell_nodes, m, p, 0, i);
    m_metric_p_i_nzmax = m_cell_nodes.a0;
    m_metric_p_i_p = (int *) malloc(m_metric_p_i_nzmax * sizeof(int));
    /* NULL pointer check */
    memcpy(m_metric_p_i_p, m_cell_nodes.a1, sizeof(int) * m_cell_nodes.a0);
    m_metric_p_i_x = double_fscan_array(in, m_metric_p_i_nzmax);
    m_metric_p[i] = vec_sparse_new(m_metric_p_i_nzmax, m_cn[0],
                                   m_metric_p_i_p, m_metric_p_i_x);
  }
  return m_metric_p;
  
}

vec_sparse *** mesh_qc_metric_corrected_fscan(FILE * in, const mesh_qc * m)
{
  int m_dim, p;
  vec_sparse *** m_metric;
  
  m_dim = m->dim;
  m_metric = (vec_sparse ***) malloc((m_dim + 1) * sizeof(vec_sparse **));
  /* NULL pointer check */
  for (p = 0; p <= m_dim; ++p)
  {
    m_metric[p] = mesh_qc_metric_corrected_p_fscan(in, m, p);
    /* NULL pointer check */
  }
  return m_metric;
}
