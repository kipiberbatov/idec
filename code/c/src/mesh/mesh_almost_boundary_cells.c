#include <errno.h>
#include <stdlib.h>

#include "mesh.h"

jagged1 * mesh_almost_boundary_cells(
  const mesh * m, const jagged1 * m_bd_cells, int p)
{
  int i, i_loc, ind, j_loc, m_dim, m_bd_cells_a0, node_list_original_a0;
  int * m_bd_cells_a1, * node_list_original_a1;
  jagged1 face;
  jagged1 * node_list = NULL, * node_list_original;
  jagged2 faces;

  m_dim = m->dim;
  m_bd_cells_a0 = m_bd_cells->a0;
  m_bd_cells_a1 = m_bd_cells->a1;
  mesh_cf_part2(&faces, m, m_dim, p);

  node_list_original = (jagged1 *) malloc(sizeof(jagged1));
  if (errno)
  {
    fprintf(stderr,
      "mesh_almost_boundary_cells: "
      "cannot allocate memory for node_list_original\n");
    goto end;
  }

  node_list_original_a0 = 0;
  for (i_loc = 0; i_loc < m_bd_cells_a0; ++i_loc)
  {
    i = m_bd_cells_a1[i_loc];
    jagged2_part1(&face, &faces, i);
    node_list_original_a0 += face.a0;
  }
  node_list_original->a0 = node_list_original_a0;

  node_list_original_a1 = (int *) malloc(node_list_original_a0 * sizeof(int));
  if (errno)
  {
    fprintf(stderr,
      "mesh_almost_boundary_cells: "
      "cannot allocate memory for node_list_original_a1\n");
    goto node_list_original_free;
  }
  ind = 0;
  for (i_loc = 0; i_loc < m_bd_cells_a0; ++i_loc)
  {
    i = m_bd_cells_a1[i_loc];
    jagged2_part1(&face, &faces, i);
    for (j_loc = 0; j_loc < face.a0; ++j_loc)
    {
      node_list_original_a1[ind] = face.a1[j_loc];
      ++ind;
    }
  }
  node_list_original->a1 = node_list_original_a1;
  node_list = jagged1_delete_duplicates(node_list_original);
  if (errno)
  {
    fprintf(stderr, "mesh_almost_boundary_cells: cannot delete duplicates\n");
    goto node_list_original_a1_free;
  }
node_list_original_a1_free:
  free(node_list_original_a1);
node_list_original_free:
  free(node_list_original);
end:
  return node_list;
}
