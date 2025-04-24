#include <stdlib.h>

#include "color.h"
#include "double.h"
#include "double_private.h"

double * double_matrix_file_scan_raw(FILE * in, int m, int n)
{
  double * a;

  a = double_array_file_scan(in, m * n, "--raw");
  if (a == NULL)
  {
    color_error_position(__FILE__, __LINE__);
    fprintf(stderr, "cannot scan matrix as an array of length %d\n", m * n);
    return NULL;
  }
  return a;
}
