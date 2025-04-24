#include <stdlib.h>

#include "double_array2.h"
#include "mesh_and_boundary.h"

void mesh_and_boundary_free(mesh_and_boundary * m_and_bd)
{
  int d = m_and_bd->_mesh->dim;

  mesh_free(m_and_bd->_mesh);
  double_array2_free(m_and_bd->boundary, d);
  free(m_and_bd);
}
