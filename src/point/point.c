#include <stdlib.h>
#include <string.h>
#include "point.h"

point * point_new(double * p_x)
{
  point * p;
  
  p = (point *) malloc(sizeof(point));
  /* NULL pointer check */
  memcpy(p->x, p_x, sizeof(double) * 2);
  return p;
}

void point_free(point * p)
{
  free(p->x);
  free(p);
}

double point_measure(point * p)
{
  return 1;
}
