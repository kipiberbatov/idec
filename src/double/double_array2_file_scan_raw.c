#include <errno.h>
#include <stdlib.h>
#include <string.h>

#include "double_array_file_scan.h"
#include "double_array2_free.h"
#include "double_array2_file_scan_raw.h"

/*
Scan an array of arrays of doubles stored as blank space separated values.
Return NULL if the scan is unsuccessful and set errno to EINVAL.
*/
double ** double_array2_file_scan_raw(FILE * in, int a0, const int * a1)
{
  int i;
  double ** a;
  
  /* allocate memory for the final result */
  a = (double **) malloc(sizeof(double *) * a0); 
  if (errno)
  {
    fprintf(
      stderr,
      "Error in %s: cannot allocate memory for the array being scanned\n",
      __func__
    );
    return NULL;
  }
  
  /* scan individual elements */
  for (i = 0; i < a0; ++i)
  {
    a[i] = double_array_file_scan(in, a1[i], "--raw");
    if (errno)
    {
      fprintf(
        stderr,
        "Error in %s: cannot scan element with index %d: %s\n",
        __func_,
        i
      );
      double_array2_free(a, i);
      return NULL;
    }
  }
  
  return a;
}
