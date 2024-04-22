#include "matrix.h"

static double matrix_determinant_2(const double * a)
{
  const double * a_0 = a;
  const double * a_1 = a + 2;
  return a_0[0] * a_1[1] - a_0[1] * a_1[0];
}

static double matrix_determinant_3(const double * a)
{
  const double * a_0 = a;
  const double * a_1 = a + 3;
  const double * a_2 = a + 6;
  return a_0[0] * a_1[1] * a_2[2] - a_0[0] * a_1[2] * a_2[1]
       + a_1[0] * a_2[1] * a_0[2] - a_1[0] * a_0[1] * a_2[2]
       + a_2[0] * a_0[1] * a_1[2] - a_2[0] * a_1[1] * a_0[2];
}

double matrix_determinant(int d, const double * a)
{
  switch (d)
  {
  case 0:
    return 1;
  case 1:
    return a[0];
  case 2:
    return matrix_determinant_2(a);
  case 3:
    return matrix_determinant_3(a);
  default:
    return 0.;
  }
  return 0.;
}
