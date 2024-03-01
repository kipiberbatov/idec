#ifndef LINE_H
#define LINE_H

typedef struct line
{
  double x0[2];
  double x1[2];
} line;

/***************************** memory_management ******************************/
line * line_new(double * p_x0, double * p_x1);

void line_free(line * p);

/********************************* geometry ***********************************/
double line_measure(line * p);

#endif /* LINE_H */
