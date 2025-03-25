#ifndef _idec_graphics_2d_arc_h
#define _idec_graphics_2d_arc_h

/* circular arc {(x0 + r cos(t), y0 + r sin(t)) | alpha <= t <= beta} */
struct idec_graphics_2d_arc
{
  double x0;
  double y0;
  double r;
  double alpha;
  double beta;
};

#endif /* _idec_graphics_2d_arc_h */
