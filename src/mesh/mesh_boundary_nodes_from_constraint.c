#include <errno.h>
#include <stdlib.h>

#include "mesh.h"

jagged1 * mesh_boundary_nodes_from_constraint(
  const mesh * m,
  int (*constraint)(const double *))
{
  int i, index, m_cn_0, m_dim_embedded, size;
  int * values;
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
  
  size = 0;
  for (i = 0; i < m_cn_0; ++i)
    if (constraint(m->coord + m_dim_embedded * i))
      ++size;
  
  values = (int *) malloc(sizeof(int) * size);
  if (errno)
  {
    fprintf(stderr, "Error: cannot allocate memory for result\n");
    jagged1_free(result);
    return NULL;
  }
  index = 0;
  for (i = 0; i < m_cn_0; ++i)
    if (constraint(m_coord + m_dim_embedded * i))
    {
      values[index] = i;
      ++index;
    }
  
  result->a0 = size;
  result->a1 = values;
  return result;
}
