#include <errno.h>

#include "color.h"
#include "double.h"

double * double_matrix_file_scan_by_name(
  const char * name, int m, int n, const char * format)
{
  double * a;

  a = double_array_file_scan_by_name(name, m * n, format);
  if (errno)
  {
    color_error_position(__FILE__, __LINE__);
    fprintf(stderr,
      "cannot scan matrix of size %d * %d from file %s in format %s\n",
      m, n, name, format);
  }
  return a;
}
