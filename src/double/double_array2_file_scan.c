#include <errno.h>
#include <string.h>

#include "double_array2_file_scan.h"
#include "double_array2_file_scan_raw.h"

/*
Read from a file in a specified format.
Return a pointer to an array of arrays of type double.
The result res is of size a0 and each of res[i] is of size a1[i].
If the reading is unsuccessful, return NULL and set errno to EINVAL.

Supported formats:
  --raw
*/
double * double_array2_file_scan(
  FILE * in,
  int a0,
  const int * a1,
  const char * format)
{
  double * a;

  /* check format "--raw" */
  if (!strcmp(format, "--raw"))
  {
    a = double_array2_file_scan_raw(in, a0, a1);
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
