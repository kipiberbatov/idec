#ifndef _point_2d_h
#define _point_2d_h

typedef struct point_2d
{
  double x[2];
} point_2d;

/********************************* geometry ***********************************/
double point_2d_measure(const point_2d * p);

#endif /* _point_2d_h */
