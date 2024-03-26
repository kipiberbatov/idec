#include <errno.h>
#include <stdlib.h>

#include "mesh.h"

/* p = d - 1 */
/********************* mesh_boundary_cells_of_hyperfaces **********************/
static int mesh_boundary_cells_of_hyperfaces_size(const mesh * m)
{
  int d, i, m_cn_p, size;
  jagged1 m_fc_p_d_i;
  jagged2 m_fc_p_d;
  
  d = m->dim;
  m_cn_p = m->cn[d - 1];
  mesh_fc_part2(&m_fc_p_d, m, d - 1, d);
  
  size = 0;
  for (i = 0; i < m_cn_p; ++i)
  {
    jagged2_part1(&m_fc_p_d_i, &m_fc_p_d, i);
    if (m_fc_p_d_i.a0 == 1)
      ++size;
  }
  return size;
}

static void
mesh_boundary_cells_of_hyperfaces_values(int * values, const mesh * m)
{
  int d, i, index, m_cn_p;
  jagged1 m_fc_p_d_i;
  jagged2 m_fc_p_d;
  
  d = m->dim;
  m_cn_p = m->cn[d - 1];
  mesh_fc_part2(&m_fc_p_d, m, d - 1, d);
  
  index = 0;
  for (i = 0; i < m_cn_p; ++i)
  {
    jagged2_part1(&m_fc_p_d_i, &m_fc_p_d, i);
    if (m_fc_p_d_i.a0 == 1)
    {
      values[index] = m_fc_p_d_i.a1[0];
      ++index;
    }
  }
}

jagged1 * mesh_boundary_cells_of_hyperfaces(const mesh * m)
{
  jagged1 * result;
  
  result = (jagged1 *) malloc(sizeof(jagged1));
  if (errno)
  {
    fprintf(stderr, "Error in %s: cannot allocate memory", __func__);
    return NULL;
  }
  result->a0 = mesh_boundary_cells_of_hyperfaces_size(m);
  
  result->a1 = (int *) malloc(sizeof(int) * result->a0);
  if (errno)
  {
    fprintf(stderr, "Error in %s: cannot allocate memory", __func__);
    free(result);
    return NULL;
  }
  mesh_boundary_cells_of_hyperfaces_values(result->a1, m);
  
  return result;
}

/******************* mesh_boundary_cells_of_non_hyperfaces ********************/
// jagged1 * mesh_boundary_cells(const mesh * m, int p)
// {
//   jagged1 * result;
//
//   if (p == m->dim - 1)
//   {
//     result = mesh_boundary_cells_of_hyperfaces(m);
//     if (errno)
//       fprintf(stderr, "Error in %s: cannot calculate result", __func__);
//   }
//   else
//   {
//     result = mesh_boundary_cells_of_non_hyperfaces(m, p);
//     if (errno)
//       fprintf(stderr, "Error in %s: cannot calculate result", __func__);
//   }
//   return result;
// }
