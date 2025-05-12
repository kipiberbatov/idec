#include <errno.h>
#include <stdlib.h>
#include <stdio.h>
#include "forman.h"

/* p_f = 1 */
static void forman_boundary_values_on_edges(double * m_boundary_values,
  const mesh * m, matrix_sparse ** m_bd)
{
  int d, i, index, l, l_local, m_cn_p, p;
  int * m_cf_p_pm1_i, * m_cn;
  matrix_sparse * m_bd_p;
  jagged2 m_cf_p_pm1;

  d = m->dim;
  m_cn = m->cn;
  index = 0;

  for (p = 1; p <= d; ++p)
  {
    m_bd_p = m_bd[p - 1];
    m_cn_p = m_cn[p];
    mesh_cf_part2(&m_cf_p_pm1, m, p, p - 1);
    m_cf_p_pm1_i = m_cf_p_pm1.a2;
    for (i = 0; i < m_cn_p; ++i)
    {
      for (l_local = 0; l_local < m_cf_p_pm1.a1[i]; ++l_local)
      {
        l = m_cf_p_pm1_i[l_local];
        m_boundary_values[index] = matrix_sparse_part(m_bd_p, l, i);
        m_boundary_values[index + 1] = -m_boundary_values[index];
        index += 2;
      }
      m_cf_p_pm1_i += m_cf_p_pm1.a1[i];
    }
  }
}

static void forman_boundary_values_general_l3_begin(
  double * m_boundary_values, int * index,
  const mesh * m,
  const matrix_sparse * m_bd_p,
  const jagged2 * m_cf_pm1_s,
  const jagged1 * m_cf_p_pm1_i,
  int i,
  int l)
{
  int _index, j, j_local, m_cf_p_pm1_i_a0;
  int * m_cf_p_pm1_i_a1;
  jagged1 m_cf_pm1_s_j;

  m_cf_p_pm1_i_a0 = m_cf_p_pm1_i->a0;
  m_cf_p_pm1_i_a1 = m_cf_p_pm1_i->a1;

  _index = *index;
  for (j_local = 0; j_local < m_cf_p_pm1_i_a0; ++j_local)
  {
    j = m_cf_p_pm1_i_a1[j_local];
    jagged2_part1(&m_cf_pm1_s_j, m_cf_pm1_s, j);
    if (jagged1_member(&m_cf_pm1_s_j, l))
    {
      m_boundary_values[_index] = matrix_sparse_part(m_bd_p, j, i);
      ++_index;
    }
  }
  *index = _index;
}

static void forman_boundary_values_general_l3_end(
  double * m_boundary_values,
  int * index,
  const mesh * m,
  const matrix_sparse * m_bd_sp1,
  const jagged2 * m_cf_sp1_s,
  const jagged1 * m_cf_p_sp1_i,
  int l,
  int sign)
{
  int _index, k, k_local, m_cf_p_sp1_i_a0;
  int * m_cf_p_sp1_i_a1;
  jagged1 m_cf_sp1_s_k;

  m_cf_p_sp1_i_a0 = m_cf_p_sp1_i->a0;
  m_cf_p_sp1_i_a1 = m_cf_p_sp1_i->a1;

  _index = *index;
  for (k_local = 0; k_local < m_cf_p_sp1_i_a0; ++k_local)
  {
    k = m_cf_p_sp1_i_a1[k_local];
    jagged2_part1(&m_cf_sp1_s_k, m_cf_sp1_s, k);
    if (jagged1_member(&m_cf_sp1_s_k, l))
    {
      m_boundary_values[_index] = sign * matrix_sparse_part(m_bd_sp1, l, k);
      ++_index;
    }
  }
  *index = _index;
}

/* p_f >= 2 */
static void forman_boundary_values_general(double * m_boundary_values,
  const mesh * m, matrix_sparse ** m_bd, int p_f)
{
  int d, i, index, l_local, l, m_cn_p, p, s;
  int * m_cf_p_s_i, * m_cn;
  double sign;
  jagged1 m_cf_p_pm1_i, m_cf_p_sp1_i;
  jagged2 m_cf_p_pm1, m_cf_p_s, m_cf_p_sp1, m_cf_pm1_s, m_cf_sp1_s;
  matrix_sparse * m_bd_p, * m_bd_sp1;

  d = m->dim;
  m_cn = m->cn;
  sign = (p_f % 2 ? -1. : 1.); /* sign = (-1)^{p_f} */
  index = 0;

  for (p = p_f; p <= d; ++p)
  {
    m_bd_p = m_bd[p - 1];
    m_cn_p = m_cn[p];
    s = p - p_f;
    m_bd_sp1 = m_bd[s];
    mesh_cf_part2(&m_cf_p_pm1, m, p, p - 1);
    mesh_cf_part2(&m_cf_p_sp1, m, p, s + 1);
    mesh_cf_part2(&m_cf_p_s, m, p, s);
    mesh_cf_part2(&m_cf_pm1_s, m, p - 1, s);
    mesh_cf_part2(&m_cf_sp1_s, m, s + 1, s);
    m_cf_p_s_i = m_cf_p_s.a2;

    m_cf_p_pm1_i.a1 = m_cf_p_pm1.a2;
    m_cf_p_sp1_i.a1 = m_cf_p_sp1.a2;
    for (i = 0; i < m_cn_p; ++i)
    {
      m_cf_p_pm1_i.a0 = m_cf_p_pm1.a1[i];
      m_cf_p_sp1_i.a0 = m_cf_p_sp1.a1[i];
      for (l_local = 0; l_local < m_cf_p_s.a1[i]; ++l_local)
      {
        l = m_cf_p_s_i[l_local];
        forman_boundary_values_general_l3_begin(m_boundary_values, &index,
          m, m_bd_p, &m_cf_pm1_s, &m_cf_p_pm1_i, i, l);
        forman_boundary_values_general_l3_end(m_boundary_values, &index,
          m, m_bd_sp1, &m_cf_sp1_s, &m_cf_p_sp1_i, l, sign);
      }
      m_cf_p_s_i += m_cf_p_s.a1[i];
      m_cf_p_pm1_i.a1 += m_cf_p_pm1.a1[i];
      m_cf_p_sp1_i.a1 += m_cf_p_sp1.a1[i];
    }
  }
}

static matrix_sparse * forman_boundary_single(
  const mesh * m, const mesh * m_forman, matrix_sparse ** m_bd, int p_f)
{
  int m_forman_boundary_p_f_nonzero_max;
  int * m_forman_cn;
  matrix_sparse * m_forman_boundary_p_f;

  m_forman_cn = m_forman->cn;
  m_forman_boundary_p_f = (matrix_sparse *) malloc(sizeof(matrix_sparse));
  if (errno)
  {
    fputs("Runtime error! Stack trace:\n", stderr);
    fputs("  forman_boundary_single: "
      "cannot allocate memory for m_forman_boundary_p_f\n", stderr);
    goto end;
  }
  m_forman_boundary_p_f_nonzero_max = mesh_boundary_nonzero_max(m_forman, p_f);
  m_forman_boundary_p_f->rows = m_forman_cn[p_f - 1];
  m_forman_boundary_p_f->cols = m_forman_cn[p_f];

  m_forman_boundary_p_f->cols_total
  = (int *) malloc((m_forman_boundary_p_f->cols + 1) * sizeof(int));
  if (errno)
  {
    fputs("Runtime error! Stack trace:\n", stderr);
    fputs("  forman_boundary_single: "
      "cannot allocate memory for m_forman_boundary_p_f->cols_total\n",
      stderr);
    goto m_forman_boundary_p_f_free;
  }
  mesh_boundary_cols_total(m_forman_boundary_p_f->cols_total, m_forman, p_f);

  m_forman_boundary_p_f->row_indices
  = (int *) malloc(sizeof(int) * m_forman_boundary_p_f_nonzero_max);
  if (errno)
  {
    fputs("Runtime error! Stack trace:\n", stderr);
    fputs("  forman_boundary_single: "
      "cannot allocate memory for m_forman_boundary_p_f->row_indices\n",
      stderr);
    goto m_forman_boundary_p_f_p_free;
  }
  mesh_boundary_row_indices(m_forman_boundary_p_f->row_indices, m_forman, p_f);

  m_forman_boundary_p_f->values
  = (double *) malloc(sizeof(double) * m_forman_boundary_p_f_nonzero_max);
  if (errno)
  {
    fputs("Runtime error! Stack trace:\n", stderr);
    fputs("  forman_boundary_single: "
      "cannot allocate memory for m_forman_boundary_p_f->values\n",
      stderr);
    goto m_forman_boundary_p_f_i_free;
  }
  if (p_f == 1)
    forman_boundary_values_on_edges(m_forman_boundary_p_f->values, m, m_bd);
  else
    forman_boundary_values_general(m_forman_boundary_p_f->values, m, m_bd, p_f);

  return m_forman_boundary_p_f;

  /* cleaning if an error occurs */
m_forman_boundary_p_f_i_free:
  free(m_forman_boundary_p_f->row_indices);
m_forman_boundary_p_f_p_free:
  free(m_forman_boundary_p_f->cols_total);
m_forman_boundary_p_f_free:
  free(m_forman_boundary_p_f);
end:
  return NULL;
}

matrix_sparse **
forman_boundary(const mesh * m, const mesh * m_forman, matrix_sparse ** m_bd)
{
  int d, p_f;
  matrix_sparse ** m_forman_boundary;

  d = m->dim;

  m_forman_boundary = (matrix_sparse **) malloc(sizeof(matrix_sparse *) * d);
  if (errno)
  {
    fprintf(stderr,
      "forman_boundary: cannot allocate memory for m_forman_boundary\n");
    goto end;
  }
  for (p_f = 1; p_f <= d; ++p_f)
  {
    m_forman_boundary[p_f - 1] = forman_boundary_single(m, m_forman, m_bd, p_f);
    if (errno)
    {
      fprintf(stderr,
        "forman_boundary: cannot calculate m_forman_boundary[%d]\n", p_f - 1);
      goto m_forman_boundary_p_f_free;
    }
  }
  return m_forman_boundary;

  /* cleaning if an error occurs */
m_forman_boundary_p_f_free:
  matrix_sparse_array_free(m_forman_boundary, p_f - 1);
  free(m_forman_boundary);
end:
  return NULL;
}
