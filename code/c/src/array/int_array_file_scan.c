#include <errno.h>
#include <stdlib.h>
#include <string.h>

#include "color.h"
#include "int_private.h"

int * int_array_file_scan(FILE * in, int n, const char * format)
{
  int * a;

  if (n == 0)
    return (int *) malloc(sizeof(int));

  if (!strcmp(format, "--raw"))
    a = int_array_file_scan_raw(in, n);
  else
  {
    errno = EINVAL;
    color_error_position(__FILE__, __LINE__);
    fprintf(stderr, "format %s is not supported\n", format);
    return NULL;
  }

  if (a == NULL)
  {
    color_error_position(__FILE__, __LINE__);
    fputs("cannot scan input\n", stderr);
  }
  return a;
}
