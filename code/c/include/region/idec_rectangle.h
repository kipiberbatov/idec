#ifndef _idec_rectangle_h
#define _idec_rectangle_h

/* the rectangle [x0, x1] * [y0, y1] */
struct idec_rectangle
{
  double x0;
  double x1;
  double y0;
  double y1;
};

double idec_rectangle_numerical_integration_average_value_gauss_1(
  const struct idec_rectangle * rectangle, double (*f)(const double *));

double idec_rectangle_numerical_integration_average_value_gauss_2(
  const struct idec_rectangle * rectangle, double (*f)(const double *));

#endif /* _idec_rectangle_h */
