#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "line.h"

line * line_new(double * p_x0, double * p_x1)
{
  line * p;
  
  p = (line *) malloc(sizeof(line));
  /* NULL pointer check */
  memcpy(p->x0, p_x0, sizeof(double) * 2);
  memcpy(p->x1, p_x1, sizeof(double) * 2);
  return p;
}

void line_free(line * p)
{
  free(p->x1);
  free(p->x0);
  free(p);
}

double line_measure(line * p)
{
  double y0, y1;
  double p_x0[2], p_x1[2];
  
  memcpy(p_x0, p->x0, sizeof(double) * 2);
  memcpy(p_x1, p->x1, sizeof(double) * 2);
  y0 = p_x1[0] - p_x0[0];
  y1 = p_x1[1] - p_x0[1];
  return sqrt(y0 * y0 + y1 * y1);
}
