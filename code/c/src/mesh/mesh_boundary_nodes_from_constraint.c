#include <errno.h>
#include <stdlib.h>

#include "mesh.h"

static int mesh_boundary_nodes_from_constraint_size(
  int m_cn_0,
  int m_dim_embedded,
  const double * m_coord,
  int (*constraint)(const double *))
{
  int i, size;  

  size = 0;
  for (i = 0; i < m_cn_0; ++i)
    if (constraint(m_coord + m_dim_embedded * i))
      ++size;
  return size;
}

static void mesh_boundary_nodes_from_constraint_values(
  int * values,
  int m_cn_0,
  int m_dim_embedded,
  const double * m_coord,
  int (*constraint)(const double *))
{
  int i, index;

  index = 0;
  for (i = 0; i < m_cn_0; ++i)
    if (constraint(m_coord + m_dim_embedded * i))
    {
      values[index] = i;
      ++index;
    }
}

jagged1 * mesh_boundary_nodes_from_constraint(
  const mesh * m,
  int (*constraint)(const double *))
{
  int m_cn_0, m_dim_embedded;
  double * m_coord;
  jagged1 * result;

  result = (jagged1 *) malloc(sizeof(jagged1));
  if (errno)
  {
    fprintf(stderr, "Error: cannot allocate memory for result\n");
    return NULL;
  }

  m_dim_embedded = m->dim_embedded;
  m_cn_0 = m->cn[0];
  m_coord = m->coord;
  result->a0 = mesh_boundary_nodes_from_constraint_size(
    m_cn_0, m_dim_embedded, m_coord, constraint);

  result->a1 = (int *) malloc(sizeof(int) * result->a0);
  if (errno)
  {
    fprintf(stderr, "Error: cannot allocate memory for result->a1\n");
    jagged1_free(result);
    return NULL;
  }
  mesh_boundary_nodes_from_constraint_values(
    result->a1, m_cn_0,  m_dim_embedded, m_coord, constraint);
  return result;
}
