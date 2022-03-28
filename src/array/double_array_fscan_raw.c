#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include "double_private.h"

double * double_array_fscan_raw(FILE * in, int n)
{
  int i;
  double * a;
  
  a = (double *) malloc(sizeof(double) * n);
  if (errno)
  {
    perror("double_array_fscan_raw - cannot allocate memory for array");
    return NULL;
  }
  for (i = 0; i < n; ++i)
  {
    a[i] = double_fscan(in);
    if (errno)
    {
      fprintf(stderr,
              "double_array_fscan_raw - cannot scan a[%d]: %s\n",
              i, strerror(errno));
      free(a);
      return NULL;
    }
  }
  return a;
}
