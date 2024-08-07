#include <errno.h>
#include <math.h>
#include <stdlib.h>
#include "double.h"
#include "mesh.h"

#define EPSILON 0.00001

static int mesh_boundary_nodes_a0(const mesh * m, const double * m_node_curvature)
{
  int m_bd_nodes_a0, i, m_cn_0;

  m_cn_0 = m->cn[0];
  m_bd_nodes_a0 = 0;
  for (i = 0; i < m_cn_0; ++i)
    if (fabs(m_node_curvature[i] - 1) >= EPSILON)
      ++m_bd_nodes_a0;
  return m_bd_nodes_a0;
}

static void mesh_boundary_nodes_a1(
  int * m_bd_nodes_a1, const mesh * m, const double * m_node_curvature)
{
  int i, ind, m_cn_0;

  m_cn_0 = m->cn[0];
  ind = 0;
  for (i = 0; i < m_cn_0; ++i)
  {
    if (fabs(m_node_curvature[i] - 1) >= EPSILON)
    {
      m_bd_nodes_a1[ind] = i;
      ++ind;
    }
  }
}

jagged1 * mesh_boundary_nodes(const mesh * m)
{
  double * m_node_curvature;
  jagged1 * m_bd_nodes;

  m_node_curvature = mesh_node_curvature(m);
  if (errno)
  {
    fputs("mesh_boundary_nodes - cannot calculate m_node_curvature\n", stderr);
    return NULL;
  }

  m_bd_nodes = (jagged1 *) malloc(sizeof(jagged1));
  if (errno)
  {
    fputs("mesh_boundary_nodes - cannot allocate memory for m_bd_nodes\n", stderr);
    free(m_node_curvature);
    return NULL;
  }

  m_bd_nodes->a0 = mesh_boundary_nodes_a0(m, m_node_curvature);

  m_bd_nodes->a1 = (int *) malloc(sizeof(int) * m_bd_nodes->a0);
  if (errno)
  {
    fputs("mesh_boundary_nodes - cannot allocate memory for m_bd_nodes->a1\n",
          stderr);
    free(m_bd_nodes);
    free(m_node_curvature);
    return NULL;
  }
  mesh_boundary_nodes_a1(m_bd_nodes->a1, m, m_node_curvature);

  free(m_node_curvature);

  return m_bd_nodes;
}
