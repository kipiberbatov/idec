#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include "double_private.h"

double ** double_array2_fscan_raw(FILE * in, int a0, const int * a1)
{
  int i;
  double ** a;
  
  a = (double **) malloc(sizeof(double *) * a0); 
  if (errno)
  {
    perror("double_array2_fscan_raw - cannot allocate memory for a");
    return NULL;
  }
  for (i = 0; i < a0; ++i)
  {
    a[i] = double_array_fscan(in, a1[i], "--raw");
    if (errno)
    {
      fprintf(stderr,
              "double_array2_fscan_raw - cannot scan a[%d]: %s\n",
              i, strerror(errno));
      double_array2_free(a, i);
      return NULL;
    }
  }
  return a;
}
