#ifndef _triangle_2d_h
#define _triangle_2d_h

typedef struct triangle_2d
{
  double x0[2];
  double x1[2];
  double x2[2];
} triangle_2d;

double triangle_2d_measure(const triangle_2d * p);

#endif /* _triangle_2d_h */
