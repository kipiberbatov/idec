#include <stdlib.h>
#include "double.h"

double double_fscan(FILE * in)
{
  double a;
  
  fscanf(in, "%lf", &a);
  return a;
}

double * double_fscan_array(FILE * in, int n)
{
  int i;
  double * a;
  
  a = (double *) malloc(n * sizeof(double));
  /* NULL pointer check */
  for (i = 0; i < n; ++i)
  {
    fscanf(in, "%lf", a + i);
    /* successfull scanning check */
  }
  return a;
}

double ** double_fscan_array2(FILE * in, int a0, int * a1)
{
  int i;
  double ** arr;
  
  arr = (double **) malloc(a0 * sizeof(double *)); 
  /* NULL pointer check */
  for (i = 0; i < a0; ++i)
  {
    arr[i] = double_fscan_array(in, a1[i]);
    /* NULL pointer and successfull scanning check */
  }
  return arr;
}

double * double_fscan_matrix(FILE * in, int rows, int cols)
{
  return double_fscan_array(in, rows * cols);
}
