#ifndef _line_2d_h
#define _line_2d_h

typedef struct line_2d
{
  double x0[2];
  double x1[2];
} line_2d;

double line_2d_measure(const line_2d * p);

#endif /* _line_2d_h */
