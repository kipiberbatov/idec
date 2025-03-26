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

#endif /* _arc_2d_h */
