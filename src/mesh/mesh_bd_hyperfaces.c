#include <stdlib.h>
#include "mesh.h"


#if 0
int mesh_bd_hyperfaces_size(const mesh * m)
{
  int i, j, m_bd_hyperfaces_size, m_dim, m_fc;
  int * m_cn;
  jagged1 m_hyperfaces_to_cells_sizes;
  
  m_dim = m->dim;
  m_cn = m->cn;
  mesh_fcn_part2(&m_hyperfaces_to_cells_sizes, m, m_dim - 1, m_dim);
  m_bd_hyperfaces_size = 0;
  for (j = 0; j < m_cn[m_dim - 1]; ++j)
    if (m_hyperfaces_to_cells_sizes.a1[j] == 1)
      ++m_bd_hyperfaces_size;
  return m_bd_hyperfaces_size;
}

int * mesh_bd_hyperfaces(const mesh * m, int m_bd_hyperfaces_size)
{
  int i, ind, j, m_dim, m_fc;
  int * m_bd_hyperfaces, * m_cn;
  jagged1 m_hyperfaces_to_cells_sizes; 
  
  m_dim = m->dim;
  m_cn = m->cn;
  mesh_fcn_part2(&m_hyperfaces_to_cells_sizes, m, m_dim - 1, m_dim);
  m_bd_hyperfaces = (int *) malloc(m_bd_hyperfaces_size * sizeof(int));
  /* NULL pointer check */
  ind = 0;
  for (j = 0; j < m_cn[m_dim - 1]; ++j)
    if (m_hyperfaces_to_cells_sizes.a1[j] == 1)
    {
      m_bd_hyperfaces[ind] = j;
      ++ind;
    }
  return m_bd_hyperfaces;
}
#endif

jagged1 * mesh_bd_hyperfaces(const mesh * m)
{
  int ind, j, m_dim, m_bd_hyperfaces_a0;
  int * m_bd_hyperfaces_a1;
  jagged1 m_hyperfaces_to_cells_sizes;
  jagged1 * m_bd_hyperfaces;
  
  m_dim = m->dim;
  mesh_fcn_part2(&m_hyperfaces_to_cells_sizes, m, m_dim - 1, m_dim);
  m_bd_hyperfaces = (jagged1 *) malloc(sizeof(jagged1));
  /* NULL pointer check */
  m_bd_hyperfaces_a0 = 0;
  for (j = 0; j < m_hyperfaces_to_cells_sizes.a0; ++j)
    if (m_hyperfaces_to_cells_sizes.a1[j] == 1)
      ++m_bd_hyperfaces_a0;
  m_bd_hyperfaces->a0 = m_bd_hyperfaces_a0;
  
  m_bd_hyperfaces_a1 = (int *) malloc(m_bd_hyperfaces_a0 * sizeof(int));
  /* NULL pointer check */
  ind = 0;
  for (j = 0; j < m_hyperfaces_to_cells_sizes.a0; ++j)
    if (m_hyperfaces_to_cells_sizes.a1[j] == 1)
    {
      m_bd_hyperfaces_a1[ind] = j;
      ++ind;
    }
  m_bd_hyperfaces->a1 = m_bd_hyperfaces_a1;
  return m_bd_hyperfaces;
}

jagged1 * mesh_bd_cells(const mesh * m, const jagged1 * m_bd_hyperfaces)
{
  int ind, j, m_dim, m_bd_cells_duplicated_a0, m_bd_hyperfaces_a0;
  int * m_bd_cells_duplicated_a1, * m_bd_hyperfaces_a1;
  jagged1 m_hyperface_to_cells;
  jagged1 * m_bd_cells, * m_bd_cells_duplicated;
  jagged2 m_hyperfaces_to_cells;
  jagged4 * m_fc;
  
  m_dim = m->dim;
  m_fc = m->fc;
  m_bd_hyperfaces_a0 = m_bd_hyperfaces->a0;
  m_bd_hyperfaces_a1 = m_bd_hyperfaces->a1;
  m_bd_cells_duplicated = (jagged1 *) malloc(sizeof(jagged1));
  /* NULL pointer check */
  m_bd_cells_duplicated_a0 = m_bd_hyperfaces_a0;
  m_bd_cells_duplicated->a0 = m_bd_cells_duplicated_a0;
  m_bd_cells_duplicated_a1 = 
    (int *) malloc(sizeof(int) * m_bd_cells_duplicated_a0);
  /* NULL pointer check */
  mesh_fc_part2(&m_hyperfaces_to_cells, m, m_dim - 1, m_dim);
  for (ind = 0; ind < m_bd_cells_duplicated_a0; ++ind)
  {
    j = m_bd_hyperfaces_a1[ind];
    jagged2_part1(&m_hyperface_to_cells, &m_hyperfaces_to_cells, j);
    m_bd_cells_duplicated_a1[ind] = m_hyperface_to_cells.a1[0];
  }
  m_bd_cells_duplicated->a1 = m_bd_cells_duplicated_a1;
  m_bd_cells = jagged1_delete_duplicates(m_bd_cells_duplicated);
  /* NULL pointer check */
  jagged1_free(m_bd_cells_duplicated);
  return m_bd_cells;
}

jagged1 * mesh_almost_bd_cells(
  const mesh * m, const jagged1 * m_bd_cells, int p)
{
  int i, i_loc, ind, j_loc, m_dim, m_bd_cells_a0, node_list_original_a0;
  int * m_bd_cells_a1, * node_list_original_a1;
  jagged1 face;
  jagged1 * node_list, * node_list_original;
  jagged2 faces;
  jagged4 * m_cf;
  
  m_dim = m->dim;
  m_cf = m->cf;
  m_bd_cells_a0 = m_bd_cells->a0;
  m_bd_cells_a1 = m_bd_cells->a1;
  node_list_original = (jagged1 *) malloc(sizeof(jagged1));
  /* NULL pointer check */
  mesh_cf_part2(&faces, m, m_dim, p);
  node_list_original_a0 = 0;
  for (i_loc = 0; i_loc < m_bd_cells_a0; ++i_loc)
  {
    i = m_bd_cells_a1[i_loc];
    jagged2_part1(&face, &faces, i);
    node_list_original_a0 += face.a0;
  }
  node_list_original->a0 = node_list_original_a0;
  node_list_original_a1 = (int *) malloc(node_list_original_a0 * sizeof(int));
  /* NULL pointer check */
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
  /* NULL pointer check */
  jagged1_free(node_list_original);
  return node_list;
}

// matrix_sparse * mesh_modify_laplacian(matrix_sparse * m_laplacian0, jagged1 * m_almost_bd_nodes)
// {
//   int i, i_loc, m_almost_bd_nodes_a0;
//   int * m_almost_bd_nodes_a1;
//   matrix_sparse * m_laplacian0_new;
//
//   m_almost_bd_nodes_a0 = m_almost_bd_nodes->a0;
//   m_almost_bd_nodes_a1 = m_almost_bd_nodes->a1;
//   for (i_loc = 0; i_loc < m_almost_bd_nodes_a0; ++i_loc)
//   {
//     i = m_almost_bd_nodes_a1[i_loc];
//   }
//
//   return m_laplacian0_new;
// }
