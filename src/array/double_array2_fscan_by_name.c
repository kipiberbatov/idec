#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include "double.h"

double ** double_array2_fscan_by_name(
  const char * name, int a0, const int * a1, const char * format)
{
  int i;
  double ** a;
  
  a = (double **) malloc(sizeof(double *) * a0);
  if (errno)
  {
    fputs("double_array2_fscan_by_name - cannot allocate memory for a\n",
          stderr);
    return NULL;
  }
  for (i = 0; i < a0; ++i)
  {
    a[i] = double_array_fscan_by_name(name, a1[i], format);
    if (errno)
    {
      fprintf(stderr, "double_array2_fscan_by_name - cannot scan ");
      fprintf(stderr, "a[%d]: %s\n", i, strerror(errno));
      double_array2_free(a, i);
      return NULL;
    }
  }
  return a;
}
