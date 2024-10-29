#include <stdlib.h>

#include "mesh.h"

jagged1 * mesh_boundary_neumann_minus_dirichlet_nodes(
  const mesh * m,
  int (*boundary_neumann_continuous)(const double *),
  const jagged1 * boundary_dirichlet)
{
  jagged1 * bounday_neumann, * bounday_neumann_with_dirichlet;

  bounday_neumann_with_dirichlet = mesh_boundary_nodes_from_constraint(
    m, boundary_neumann_continuous);
  if (bounday_neumann_with_dirichlet == NULL)
    return NULL;

  bounday_neumann = jagged1_difference(
    bounday_neumann_with_dirichlet, boundary_dirichlet);
  if (bounday_neumann_with_dirichlet == NULL)
  {
    jagged1_free(bounday_neumann_with_dirichlet);
    return NULL;
  }

  jagged1_free(bounday_neumann_with_dirichlet);
  return bounday_neumann;
}
