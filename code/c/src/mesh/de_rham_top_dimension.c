#include "de_rham.h"

void de_rham_top_dimension(
  double * x,
  const mesh * m,
  const double * m_vol_d,
  double (*f)(const double *))
{
  de_rham_nonzero(x, m, m->dim, m_vol_d, f);
}
