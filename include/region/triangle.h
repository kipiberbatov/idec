#ifndef TRIANGLE_H
#define TRIANGLE_H

typedef struct triangle
{
  double x0[2];
  double x1[2];
  double x2[2];
} triangle;

/***************************** memory_management ******************************/
triangle * triangle_new(double * p_x0, double * p_x1, double * p_x2);

void triangle_free(triangle * p);

/********************************* geometry ***********************************/
double triangle_measure(triangle * p);

#endif /* TRIANGLE_H */
