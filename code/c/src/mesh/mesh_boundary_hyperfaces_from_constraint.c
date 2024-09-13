#include <errno.h>
#include <stdlib.h>

#include "mesh.h"

static int mesh_boundary_hyperfaces_from_constraint_size(
  int m_cn_dm1,
  int m_dim_embedded,
  const double * m_coord,
  const jagged2 * m_cf_dm1_0,
  int (*constraint)(const double *))
{
  int flag, i, j, j_local, size;
  jagged1 m_cf_dm1_0_i;

  size = 0;
  for (i = 0; i < m_cn_dm1; ++i)
  {
    jagged2_part1(&m_cf_dm1_0_i, m_cf_dm1_0, i);
    for (j_local = 0; j_local < m_cf_dm1_0_i.a0; ++j_local)
    {
      j = m_cf_dm1_0_i.a1[j_local];
      flag = 1;
      if (!constraint(m_coord + m_dim_embedded * j))
      {
        flag = 0;
        break;
      }
    }
    if (flag)
      ++size;
  }
  return size;
}

static void mesh_boundary_hyperfaces_from_constraint_values(
  int * values,
  int m_cn_dm1,
  int m_dim_embedded,
  const double * m_coord,
  const jagged2 * m_cf_dm1_0,
  int (*constraint)(const double *))
{
  int flag, i, index, j, j_local;
  jagged1 m_cf_dm1_0_i;

  index = 0;
  for (i = 0; i < m_cn_dm1; ++i)
  {
    jagged2_part1(&m_cf_dm1_0_i, m_cf_dm1_0, i);
    for (j_local = 0; j_local < m_cf_dm1_0_i.a0; ++j_local)
    {
      j = m_cf_dm1_0_i.a1[j_local];
      flag = 1;
      if (!constraint(m_coord + m_dim_embedded * j))
      {
        flag = 0;
        break;
      }
    }
    if (flag)
    {
      values[index] = i;
      ++index;
    }
  }
}

jagged1 * mesh_boundary_hyperfaces_from_constraint(
  const mesh * m,
  int (*constraint)(const double *))
{
  int dm1, m_cn_dm1, m_dim_embedded;
  double * m_coord;
  jagged2 m_cf_dm1_0;
  jagged1 * result;

  result = (jagged1 *) malloc(sizeof(jagged1));
  if (errno)
  {
    fprintf(stderr, "Error: cannot allocate memory for result\n");
    return NULL;
  }

  dm1 = m->dim - 1;
  m_cn_dm1 = m->cn[dm1];
  m_dim_embedded = m->dim_embedded;
  m_coord = m->coord;
  mesh_cf_part2(&m_cf_dm1_0, m, dm1, 0);

  result->a0 = mesh_boundary_hyperfaces_from_constraint_size(
    m_cn_dm1, m_dim_embedded, m_coord, &m_cf_dm1_0, constraint);

  result->a1 = (int *) malloc(sizeof(int) * result->a0);
  if (errno)
  {
    fprintf(stderr, "Error: cannot allocate memory for result->a1\n");
    jagged1_free(result);
    return NULL;
  }
  mesh_boundary_hyperfaces_from_constraint_values(
    result->a1, m_cn_dm1, m_dim_embedded, m_coord, &m_cf_dm1_0, constraint);
  return result;
}
