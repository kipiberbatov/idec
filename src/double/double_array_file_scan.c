#include <errno.h>
#include <string.h>

#include "double_array_file_scan.h"
#include "double_array_file_scan_raw.h"

/*
Read from a file in a specified format up to a specified length.
Return a pointer to an array of type double.
If the writing is unsuccessful, return NULL and set errno to EINVAL.

Supported formats:
  --raw
*/
double * double_array_file_scan(FILE * in, int n, const char * format)
{
  double * a;

  /* check format "--raw" */
  if (!strcmp(format, "--raw"))
  {
    a = double_array_file_scan_raw(in, n);
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
