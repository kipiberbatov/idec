#include <errno.h>
#include "double.h"

double * double_matrix_file_scan_by_name(
  const char * name, int m, int n, const char * format)
{
  double *a;
  
  a = double_array_file_scan_by_name(name, m * n, format);
  if (errno)
  {
    fprintf(stderr,
    "Error during execution of function %s in file %s on line %d: "
    "cannot allocate memory for result matrix\n",
    __func__, __FILE__, __LINE__);
  }
  return a;
}
