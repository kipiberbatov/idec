#ifndef _arc_2d_h
#define _arc_2d_h

/* circular arc {(x0 + r cos(t), y0 + r sin(t)) | alpha <= t <= beta} */
struct arc_2d
{
  double x0;
  double y0;
  double r;
  double alpha;
  double beta;
};

struct line_2d;

void arc_2d_set_flow_rate_direction(
  struct line_2d * flow_rate_direction,
  const struct arc_2d * arc, double sign, double size);

#endif /* _arc_2d_h */
