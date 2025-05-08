#include "mesh_disk_polar.h"

void mesh_disk_polar_boundary_values(double * m_boundary_values, int na, int nd)
{
  int i, index, j, m_cn_1;

  m_cn_1 = 2 * na * nd;
  index = 0;
  for (i = 0; i < m_cn_1; ++i)
  {
    m_boundary_values[index + 0] = - 1.;
    m_boundary_values[index + 1] = 1.;
    index += 2;
  }
  for (j = 0; j < na; ++j)
  {
    m_boundary_values[index + 0] = 1.;
    m_boundary_values[index + 1] = 1.;
    m_boundary_values[index + 2] = -1.;
    index += 3;
  }
  for (i = 1; i < nd; ++i)
  {
    for (j = 0; j < na; ++j)
    {
      m_boundary_values[index + 0] = -1.;
      m_boundary_values[index + 1] = 1.;
      m_boundary_values[index + 2] = 1.;
      m_boundary_values[index + 3] = -1.;
      index += 4;
    }
  }
}
