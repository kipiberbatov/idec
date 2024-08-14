#include <math.h>

#include "mesh.h"

static double double_square(double x) {return x * x;}

double mesh_size(const mesh * m)
{
  int d, i, j, m_cn_0, p;
  double result_squared, tmp_squared;
  double * m_coord, * m_coord_i, * m_coord_j;

  d = m->dim_embedded;
  m_coord = m->coord;
  m_cn_0 = m->cn[0];

  result_squared = 0;
  for (p = 0; p < d; ++p)
    result_squared += double_square(m_coord[p] - m_coord[d + p]);

  for (i = 0; i < m_cn_0; ++i)
  {
    m_coord_i = m_coord + d * i;
    for (j = i + 1; j < m_cn_0; ++j)
    {
      m_coord_j = m_coord + d * j;
      tmp_squared = 0;
      for (p = 0; p < d; ++p)
        tmp_squared += double_square(m_coord_i[p] - m_coord_j[p]);
      if (tmp_squared < result_squared)
        result_squared = tmp_squared;
    }
  }
  return sqrt(result_squared);
}
