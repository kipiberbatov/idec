#include <errno.h>
#include <string.h>

#include "double_matrix_file_scan.h"
#include "double_matrix_file_scan_raw.h"

/*
Read from a file in a specified format up to a specified length.
Return a pointer to a flattened matrix of type double.
If the reading is unsuccessful, return NULL and set errno to EINVAL.

Supported formats:
  --raw
*/
double * double_matrix_file_scan(FILE * in, int m, int n, const char * format)
{
  double * a;

  /* check format "--raw" */
  if (!strcmp(format, "--raw"))
  {
    a = double_matrix_file_scan_raw(in, m, n);
    if (errno)
      fprintf(stderr, "Error in %s: unsuccessful scanning\n", __func__);
    return a;
  }

  /* the program will get there only if the format is not supported */
  errno = EINVAL;
  fprintf(
    stderr,
    "Error in - %s: format %s is not supported\n",
    __func__,
    format
  );
  return NULL;
}
