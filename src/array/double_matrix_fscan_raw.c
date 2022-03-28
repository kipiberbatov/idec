#include <errno.h>
#include <stdlib.h>
#include "double_private.h"

double * double_matrix_fscan_raw(FILE * in, int m, int n)
{
  double * a;
  
  a =  double_array_fscan(in, m * n, "--raw");
  if (errno)
  {
    perror("double_matrix_fscan_raw - cannot scan a");
    return NULL;
  }
  return a;
}
