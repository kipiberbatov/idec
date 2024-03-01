#include <errno.h>
#include <stdlib.h>
#include <string.h>

#include "double_file_scan.h"
#include "double_array_file_scan_raw.h"

/*
Scan an array of doubles stored as blank space separated values.
Return NULL if the scan is unsuccessful.
*/
double * double_array_file_scan_raw(FILE * in, int n)
{
  int i;
  double * a;
  
  /* allocate memory for the final result */
  a = (double *) malloc(sizeof(double) * n);
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
  for (i = 0; i < n; ++i)
  {
    a[i] = double_file_scan(in);
    if (errno)
    {
      fprintf(
        stderr,
        "Error in %s: cannot scan element with index %d: %s\n",
        __func_,
        i
      );
      free(a);
      return NULL;
    }
  }
  
  return a;
}
