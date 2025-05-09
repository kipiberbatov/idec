#include "de_rham.h"
#include "idec_rectangle.h"

void de_rham_2_hemisphere_polar_forman_gauss_2(
  double * x,
  const mesh * m,
  const double * m_vol_d,
  double (*f)(const double *))
{
  de_rham_2_hemisphere_polar_forman_generic(x, m, f,
    (double (*)(const void *, double (*)(const double *)))
    idec_rectangle_numerical_integration_average_value_gauss_2);
}
