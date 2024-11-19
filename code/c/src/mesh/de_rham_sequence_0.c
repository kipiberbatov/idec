#include "de_rham.h"

void de_rham_sequence_0(
  double * w,
  const mesh * m,
  double start,
  double step,
  int number_of_steps,
  double (*f)(double, const double *))
{
  int i, j, m_cn_0, m_dim_embedded;
  double t;
  double * m_coord, * w_j;

  m_cn_0 = m->cn[0];
  m_dim_embedded = m->dim_embedded;
  m_coord = m->coord;

  for (j = 0; j <= number_of_steps; ++j)
  {
    w_j = w + m_cn_0 * j;
    t = start + j * step;
    for (i = 0; i < m_cn_0; ++i)
      w_j[i] = f(t, m_coord + m_dim_embedded * i);
  }
}
