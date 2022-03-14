#ifndef POINT_H
#define POINT_H

typedef struct point
{
  double x[2];
} point;

/***************************** memory_management ******************************/
point * point_new(double * p_x);

void point_free(point * p);

/********************************* geometry ***********************************/
double point_measure(point * p);

#endif /* POINT_H */