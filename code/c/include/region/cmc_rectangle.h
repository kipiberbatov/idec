#ifndef _cmc_rectangle_h
#define _cmc_rectangle_h

/* the rectangle [x0, x1] * [y0, y1] */
struct cmc_rectangle
{
  double x0;
  double x1;
  double y0;
  double y1;
};

double cmc_rectangle_numerical_integration_average_value_gauss_1(
  const struct cmc_rectangle * rectangle, double (*f)(const double *));

double cmc_rectangle_numerical_integration_average_value_gauss_2(
  const struct cmc_rectangle * rectangle, double (*f)(const double *));

#endif /* _cmc_rectangle_h */
