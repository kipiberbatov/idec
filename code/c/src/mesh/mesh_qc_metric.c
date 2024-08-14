#include <errno.h>
#include <stdlib.h>
#include <string.h>

#include "double.h"
#include "int.h"
#include "mesh_qc.h"

static vector_sparse * mesh_qc_metric_p_i(
  int m_cn_0, const jagged1 * m_cf_p_0_i, int p, int i, double m_vol_p_i)
{
  double denominator_p_i;
  vector_sparse * m_metric_p_i;

  m_metric_p_i = (vector_sparse *) malloc(sizeof(vector_sparse));
  if (errno)
  {
    fprintf(stderr, "mesh_qc_metric_p_i - cannot allocate memory for "
                    "m_metric[%d][%d]\n", p, i);
    goto end;
  }

  m_metric_p_i->length = m_cn_0;
  m_metric_p_i->nonzero_max = m_cf_p_0_i->a0;

  m_metric_p_i->positions =
    (int *) malloc(sizeof(int) * m_metric_p_i->nonzero_max);
  if (errno)
  {
    fprintf(stderr, "mesh_qc_metric_p_i - cannot allocate memory for "
                    "m_metric[%d][%d]->positions\n", p, i);
    goto m_metric_p_i_free;
  }
  memcpy(m_metric_p_i->positions, m_cf_p_0_i->a1,
         sizeof(int) * m_metric_p_i->nonzero_max);

  m_metric_p_i->values =
    (double *) malloc(sizeof(double) * m_metric_p_i->nonzero_max);
  if (errno)
  {
    fprintf(stderr, "mesh_qc_metric_p_i - cannot allocate memory for "
                    "m_metric[%d][%d]->values\n", p, i);
    goto m_metric_p_i_positions_free;
  }
  denominator_p_i = ((double) m_cf_p_0_i->a0) * (m_vol_p_i * m_vol_p_i);
  double_array_assign_constant(
    m_metric_p_i->values, m_metric_p_i->nonzero_max, 1 / denominator_p_i);

  return m_metric_p_i;

  /* cleaning if an error occurs */
m_metric_p_i_positions_free:
  free(m_metric_p_i->positions);
m_metric_p_i_free:
  free(m_metric_p_i);
end:
  return NULL;
}

vector_sparse ** mesh_qc_metric_p(
  const mesh_qc * m, int p, const double * m_vol_p)
{
  int i, m_cn_p;
  int * m_cn;
  jagged1 m_cf_p_0_i;
  vector_sparse ** m_metric_p;

  m_cn = m->cn;
  m_cn_p = m_cn[p];

  m_metric_p = (vector_sparse **) malloc(sizeof(vector_sparse *) * m_cn_p);
  if (errno)
  {
    fprintf(stderr,
            "mesh_qc_metric_p - cannot allocate memory for m_metric[%d]\n", p);
    return NULL;
  }

  for (i = 0; i < m_cn_p; ++i)
  {
    mesh_cf_part3(&m_cf_p_0_i, m, p, 0, i);
    m_metric_p[i] = mesh_qc_metric_p_i(m_cn[0], &m_cf_p_0_i, p, i, m_vol_p[i]);
    if (errno)
    {
      fprintf(stderr, "mesh_qc_metric_p - cannot calculate "
                      "m_metric[%d][%d]\n", p, i);
      vector_sparse_array_free(m_metric_p, i);
      return NULL;
    }
  }

  return m_metric_p;
}

vector_sparse *** mesh_qc_metric(const mesh_qc * m, double ** m_vol)
{
  int m_dim, p;
  vector_sparse *** m_metric;

  m_dim = m->dim;

  m_metric = (vector_sparse ***) malloc(sizeof(vector_sparse **) * (m_dim + 1));
  if (errno)
  {
    fprintf(stderr, "mesh_qc_metric - cannot allocate memory for m_metric\n");
    return NULL;
  }

  for (p = 0; p <= m_dim; ++p)
  {
    m_metric[p] = mesh_qc_metric_p(m, p, m_vol[p]);
    if (errno)
    {
      fprintf(stderr, "mesh_qc_metric - cannot calculate m_metric[%d]\n", p);
      vector_sparse_array2_free(m_metric, p, m->cn);
      return NULL;
    }
  }

  return m_metric;
}

static vector_sparse * mesh_qc_metric_p_i_file_scan(
  FILE * in, int m_cn_0, const jagged1 * m_cf_p_0_i, int p, int i)
{
  vector_sparse * m_metric_p_i;

  m_metric_p_i = (vector_sparse *) malloc(sizeof(vector_sparse));
  if (errno)
  {
    fprintf(stderr, "mesh_qc_metric_p_i_file_scan - cannot allocate memory for "
                    "m_metric[%d][%d]\n", p, i);
    goto end;
  }

  m_metric_p_i->length = m_cn_0;
  m_metric_p_i->nonzero_max = m_cf_p_0_i->a0;

  m_metric_p_i->positions =
    (int *) malloc(sizeof(int) * m_metric_p_i->nonzero_max);
  if (errno)
  {
    fprintf(stderr, "mesh_qc_metric_p_i_file_scan - cannot allocate memory for "
                    "m_metric[%d][%d]->positions\n", p, i);
    goto m_metric_p_i_free;
  }
  memcpy(m_metric_p_i->positions, m_cf_p_0_i->a1,
         sizeof(int) * m_metric_p_i->nonzero_max);

  m_metric_p_i->values =
    double_array_file_scan(in, m_metric_p_i->nonzero_max, "--raw");
  if (errno)
  {
    fprintf(stderr, "mesh_qc_metric_p_i_file_scan - cannot scan "
                    "m_metric[%d][%d]->values\n", p, i);
    free(m_metric_p_i->positions);
    goto m_metric_p_i_positions_free;
  }

  return m_metric_p_i;

  /* cleaning if an error occurs */
m_metric_p_i_positions_free:
  free(m_metric_p_i->positions);
m_metric_p_i_free:
  free(m_metric_p_i);
end:
  return NULL;
}

vector_sparse ** mesh_qc_metric_p_file_scan(FILE * in, const mesh_qc * m, int p)
{
  int i, m_cn_p;
  int * m_cn;
  jagged1 m_cf_p_0_i;
  vector_sparse ** m_metric_p;

  m_cn = m->cn;
  m_cn_p = m_cn[p];

  m_metric_p = (vector_sparse **) malloc(sizeof(vector_sparse *) * m_cn_p);
  if (errno)
  {
    fprintf(stderr, "mesh_qc_metric_p_file_scan - cannot allocate memory for "
                     "m_metric[%d]\n", p);
    return NULL;
  }

  for (i = 0; i < m_cn_p; ++i)
  {
    mesh_cf_part3(&m_cf_p_0_i, m, p, 0, i);
    m_metric_p[i] = mesh_qc_metric_p_i_file_scan(in, m_cn[0], &m_cf_p_0_i, p, i);
    if (errno)
    {
      fprintf(stderr,
              "mesh_qc_metric_p_file_scan - cannot scan m_metric[%d][%d]\n", p, i);
      vector_sparse_array_free(m_metric_p, i);
      return NULL;
    }
  }

  return m_metric_p;
}

vector_sparse *** mesh_qc_metric_file_scan(FILE * in, const mesh_qc * m)
{
  int m_dim, p;
  vector_sparse *** m_metric;

  m_dim = m->dim;

  m_metric = (vector_sparse ***) malloc(sizeof(vector_sparse **) * (m_dim + 1));
  if (errno)
  {
    fputs("mesh_qc_metric_file_scan - cannot allocate memory for m_metric\n",
          stderr);
    return NULL;
  }

  for (p = 0; p <= m_dim; ++p)
  {
    m_metric[p] = mesh_qc_metric_p_file_scan(in, m, p);
    if (errno)
    {
      fprintf(stderr, "mesh_qc_metric_file_scan - cannot scan m_metric[%d]\n", p);
      vector_sparse_array2_free(m_metric, p, m->cn);
      return NULL;
    }
  }

  return m_metric;
}
