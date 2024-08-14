#include <errno.h>
#include <stdlib.h>

#include "int.h"
#include "mesh.h"

int mesh_boundary_nonzero_max(const mesh * m, int p)
{
  int i, m_cn_p;
  int * m_cfn_p_pm1_a1;
  int m_bd_nonzero_max;
  jagged1 m_cfn_p_pm1;

  m_cn_p = m->cn[p];
  mesh_cfn_part2(&m_cfn_p_pm1, m, p, p - 1);
  m_cfn_p_pm1_a1 = m_cfn_p_pm1.a1;

  m_bd_nonzero_max = 0;
  for (i = 0; i < m_cn_p; ++i)
    m_bd_nonzero_max += m_cfn_p_pm1_a1[i];
  return m_bd_nonzero_max;
}

void mesh_boundary_cols_total(int * m_bd_cols_total, const mesh * m, int p)
{
  int i, m_cn_p;
  jagged1 m_cf_p_pm1_i;
  jagged2 m_cf_p_pm1;

  m_cn_p = m->cn[p];
  mesh_cf_part2(&m_cf_p_pm1, m, p, p - 1);

  m_bd_cols_total[0] = 0;
  for (i = 0; i < m_cn_p; ++i)
  {
    jagged2_part1(&m_cf_p_pm1_i, &m_cf_p_pm1, i);
    m_bd_cols_total[i + 1] = m_bd_cols_total[i] + m_cf_p_pm1_i.a0;
  }
}

void mesh_boundary_row_indices(int * m_bd_row_indices, const mesh * m, int p)
{
  int i, ind, j_loc, m_cn_p;
  jagged1 m_cf_p_pm1_i;
  jagged2 m_cf_p_pm1;

  m_cn_p = m->cn[p];
  mesh_cf_part2(&m_cf_p_pm1, m, p, p - 1);

  ind = 0;
  for (i = 0; i < m_cn_p; ++i)
  {
    jagged2_part1(&m_cf_p_pm1_i, &m_cf_p_pm1, i);
    for (j_loc = 0; j_loc < m_cf_p_pm1_i.a0; ++j_loc)
      m_bd_row_indices[ind + j_loc] = m_cf_p_pm1_i.a1[j_loc];
    ind += m_cf_p_pm1_i.a0;
  }
}

static void mesh_boundary_values(double * m_bd_values, const mesh * m, int p)
{
  int m_cf_p_pm1_i_a0, i, ind, j, j_loc, m_cn_p, pos0, pos1, sign;
  int * m_cf_p_pm1_i_a1, * m_cf_pm1_0_j_a1;
  jagged1 m_cf_p_pm1_i, m_cf_p_0_i, m_cf_pm1_0_j;
  jagged2 m_cf_p_pm1, m_cf_p_0, m_cf_pm1_0;

  m_cn_p = m->cn[p];

  mesh_cf_part2(&m_cf_p_pm1, m, p, p - 1);
  mesh_cf_part2(&m_cf_p_0, m, p, 0);

  ind = 0;
  if (p == 1)
  {
    for (i = 0; i < m_cn_p; ++i)
    {
      m_bd_values[ind] = -1;
      m_bd_values[ind + 1] = 1;
      ind += 2;
    }
    return;
  }

  mesh_cf_part2(&m_cf_pm1_0, m, p - 1, 0);
  for (i = 0; i < m_cn_p; ++i)
  {
    jagged2_part1(&m_cf_p_pm1_i, &m_cf_p_pm1, i);
    m_cf_p_pm1_i_a0 = m_cf_p_pm1_i.a0;
    m_cf_p_pm1_i_a1 = m_cf_p_pm1_i.a1;
    jagged2_part1(&m_cf_p_0_i, &m_cf_p_0, i);
    for (j_loc = 0; j_loc < m_cf_p_pm1_i_a0; ++j_loc)
    {
      j = m_cf_p_pm1_i_a1[j_loc];
      jagged2_part1(&m_cf_pm1_0_j, &m_cf_pm1_0, j);
      if (m_cf_p_0_i.a0 == (p + 1)) /* for simplices */
        sign = jagged1_relative_sign(&m_cf_p_0_i, &m_cf_pm1_0_j);
      else /* for polygons */
      {
        m_cf_pm1_0_j_a1 = m_cf_pm1_0_j.a1;
        pos0 = jagged1_position(&m_cf_p_0_i, m_cf_pm1_0_j_a1[0]);
        pos1 = jagged1_position(&m_cf_p_0_i, m_cf_pm1_0_j_a1[1]);
        sign = (((pos1 - pos0 + m_cf_p_0_i.a0) % m_cf_p_0_i.a0) == 1) ? 1 : -1;
      }
      m_bd_values[ind + j_loc] = (double) sign;
    }
    ind += m_cf_p_pm1_i_a0;
  }
}

matrix_sparse * mesh_boundary_single(const mesh * m, int p)
{
  int m_bd_nonzero_max;
  matrix_sparse * m_bd;

  m_bd = (matrix_sparse *) malloc(sizeof(matrix_sparse));
  if (errno)
  {
    fputs("Begin stack trace\n", stderr);
    fputs("  mesh_boundary_single: cannot allocate memory for m_bd\n", stderr);
    goto end;
  }
  m_bd->rows = m->cn[p - 1];
  m_bd->cols = m->cn[p];

  m_bd->cols_total = (int *) malloc(sizeof(int) * (m_bd->cols + 1));
  if (errno)
  {
    fputs("Begin stack trace\n", stderr);
    fputs("  mesh_boundary_single: "
      "cannot allocate memory for m_bd->cols_total\n", stderr);
    goto m_bd_free;
  }
  mesh_boundary_cols_total(m_bd->cols_total, m, p);

  m_bd_nonzero_max = mesh_boundary_nonzero_max(m, p);
  m_bd->row_indices = (int *) malloc(sizeof(int) * m_bd_nonzero_max);
  if (errno)
  {
    fputs("Begin stack trace\n", stderr);
    fputs("  mesh_boundary_single: "
      "cannot allocate memory for m_bd->row_indices\n", stderr);
    goto m_bd_cols_total_free;
  }
  mesh_boundary_row_indices(m_bd->row_indices, m, p);

  m_bd->values = (double *) malloc(sizeof(double) * m_bd_nonzero_max);
  if (errno)
  {
    fputs("Begin stack trace\n", stderr);
    fputs("  mesh_boundary_single: cannot allocate memory for m_bd->values\n",
      stderr);
    goto m_bd_row_indices_free;
  }
  mesh_boundary_values(m_bd->values, m, p);

  return m_bd;

  /* cleaning if an error occurs */
m_bd_row_indices_free:
  free(m_bd->row_indices);
m_bd_cols_total_free:
  free(m_bd->cols_total);
m_bd_free:
  free(m_bd);
end:
  return NULL;
}

matrix_sparse ** mesh_boundary(const mesh * m)
{
  int d, p;
  matrix_sparse ** m_bd;

  d = m->dim;
  m_bd = (matrix_sparse **) malloc(sizeof(matrix_sparse *) * d);
  if (errno)
  {
    fputs("Begin stack trace\n", stderr);
    fputs("  mesh_boundary: cannot allocate memory for m_bd\n", stderr);
    return NULL;
  }

  for (p = 1; p <= d; ++p)
  {
    m_bd[p - 1] = mesh_boundary_single(m, p);
    if (errno)
    {
      fprintf(stderr, "  mesh_boundary: cannot calculate m_bd[%d]\n", p - 1);
      matrix_sparse_array_free(m_bd, p - 1);
      return NULL;
    }
  }
  return m_bd;
}

void mesh_boundary_check(
  FILE * out, int m_dim, matrix_sparse ** m_bd, const char * name)
{
  int p;
  matrix_sparse * m_bd_check;

  for (p = 0; p < m_dim - 1; ++p)
  {
    m_bd_check = matrix_sparse_product(m_bd[p], m_bd[p + 1]);
    if (errno)
    {
      fprintf(stderr,
        "  mesh_boundary_check: cannot find m_bd[%d] * m_bd[%d]\n",
        p, p + 1);
      return;
    }
    fprintf(out, "%s_%d . %s_%d:\n\n", name, p + 1, name, p + 2);
    matrix_sparse_file_print(out, m_bd_check, "-annotated");
    fputs("\n", out);
    free(m_bd_check);
  }
}
