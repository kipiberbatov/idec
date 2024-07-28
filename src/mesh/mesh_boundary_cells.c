#include <errno.h>
#include <stdlib.h>

#include "mesh.h"

jagged1 * mesh_boundary_cells(const mesh * m, const jagged1 * m_bd_hyperfaces)
{
  int ind, j, m_dim, m_bd_cells_duplicated_a0, m_bd_hyperfaces_a0;
  int * m_bd_cells_duplicated_a1, * m_bd_hyperfaces_a1;
  jagged1 m_hyperface_to_cells;
  jagged1 * m_bd_cells = NULL, * m_bd_cells_duplicated;
  jagged2 m_hyperfaces_to_cells;

  m_dim = m->dim;
  m_bd_hyperfaces_a0 = m_bd_hyperfaces->a0;
  m_bd_hyperfaces_a1 = m_bd_hyperfaces->a1;
  mesh_fc_part2(&m_hyperfaces_to_cells, m, m_dim - 1, m_dim);

  m_bd_cells_duplicated = (jagged1 *) malloc(sizeof(jagged1));
  if (errno)
  {
    fprintf(stderr,
      "mesh_boundary_cells: "
      "cannot allocate memory for m_bd_cells_duplicated\n");
    goto end;
  }

  m_bd_cells_duplicated_a0 = m_bd_hyperfaces_a0;
  m_bd_cells_duplicated->a0 = m_bd_cells_duplicated_a0;

  m_bd_cells_duplicated_a1 =
    (int *) malloc(sizeof(int) * m_bd_cells_duplicated_a0);
  if (errno)
  {
    fprintf(stderr,
      "mesh_boundary_cells: "
      "cannot allocate memory for m_bd_cells_duplicated_a1\n");
    goto m_bd_cells_duplicated_free;
  }
  for (ind = 0; ind < m_bd_cells_duplicated_a0; ++ind)
  {
    j = m_bd_hyperfaces_a1[ind];
    jagged2_part1(&m_hyperface_to_cells, &m_hyperfaces_to_cells, j);
    m_bd_cells_duplicated_a1[ind] = m_hyperface_to_cells.a1[0];
  }
  m_bd_cells_duplicated->a1 = m_bd_cells_duplicated_a1;

  m_bd_cells = jagged1_delete_duplicates(m_bd_cells_duplicated);
  if (errno)
  {
    fprintf(stderr, "mesh_boundary_cells: cannot delete duplicates\n");
    goto m_bd_cells_duplicated_a1_free;
  }
m_bd_cells_duplicated_a1_free:
  free(m_bd_cells_duplicated_a1);
m_bd_cells_duplicated_free:
  free(m_bd_cells_duplicated);
end:
  return m_bd_cells;
}
