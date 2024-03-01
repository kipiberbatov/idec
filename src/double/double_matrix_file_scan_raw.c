#include <errno.h>

#include "double_array_file_scan.h"
#include "double_matrix_file_scan_raw.h"

/*
Scan a matrix of doubles stored as blank space separated values.
Return NULL if the scan is unsuccessful.
*/
double * double_matrix_file_scan_raw(FILE * in, int m, int n)
{
  double * a;
  
  a = double_array_file_scan(in, m * n, "--raw");
  if (errno)
    fprintf(stderr, "Error in %s: unsuccessful scanning\n", __func__);
  return a;
}
