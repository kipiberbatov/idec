#include "matrix.h"

static void matrix_inverse_2(double * b, const double * a)
{
  double det = matrix_determinant(2, a);
  const double * a_0 = a;
  const double * a_1 = a + 2;
  double * b_0 = b;
  double * b_1 = b + 2;

  b_0[0] = a_1[1] / det;
  b_0[1] = -a_0[1] / det;
  b_1[0] = -a_1[0] / det;
  b_1[1] = a_0[0] / det;
}

static void matrix_inverse_3(double * b, const double * a)
{
  double det = matrix_determinant(3, a);
  const double * a_0 = a;
  const double * a_1 = a + 3;
  const double * a_2 = a + 6;
  double * b_0 = b;
  double * b_1 = b + 3;
  double * b_2 = b + 6;

  b_0[0] = (a_1[1] * a_2[2] - a_2[1] * a_1[2]) / det;
  b_0[1] = (a_1[2] * a_2[0] - a_2[2] * a_1[0]) / det;
  b_0[2] = (a_1[0] * a_2[1] - a_2[0] * a_1[1]) / det;

  b_1[0] = (a_2[1] * a_0[2] - a_0[1] * a_2[2]) / det;
  b_1[1] = (a_2[2] * a_0[0] - a_0[2] * a_2[0]) / det;
  b_1[2] = (a_2[0] * a_0[1] - a_0[0] * a_2[1]) / det;

  b_2[0] = (a_0[1] * a_1[2] - a_1[1] * a_0[2]) / det;
  b_2[1] = (a_0[2] * a_1[0] - a_1[2] * a_0[0]) / det;
  b_2[2] = (a_0[0] * a_1[1] - a_1[0] * a_0[1]) / det;
}

void matrix_inverse(double * b, int d, const double * a)
{
  switch(d)
  {
  case 1:
    b[0] = 1 / a[0];
    return;
  case 2:
    matrix_inverse_2(b, a);
    return;
  case 3:
    matrix_inverse_3(b, a);
    return;
  }
}
