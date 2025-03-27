#ifndef _line_2d_h
#define _line_2d_h

typedef struct line_2d
{
  double x0[2];
  double x1[2];
} line_2d;

double line_2d_measure(const struct line_2d * p);
void line_2d_midpoint(double c[2], const struct line_2d * line);
void line_2d_direction_90_degrees(double v[2], const struct line_2d * l);

void line_2d_oriented_set_from_center_and_direction(
  struct line_2d * flow_rate_direction, const double c[2], const double v[2]);

void line_2d_set_flow_rate_direction(
  struct line_2d * flow_rate_direction,
  const struct line_2d * line, double sign, double size);

#endif /* _line_2d_h */
