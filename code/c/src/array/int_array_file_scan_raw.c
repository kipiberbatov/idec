#include <errno.h>
#include <stdlib.h>
#include <string.h>

#include "color.h"
#include "int_private.h"

int * int_array_file_scan_raw(FILE * in, int n)
{
  int i;
  int * a;

  a = (int *) malloc(sizeof(int) * n);
  if (a == NULL)
  {
    color_error_position(__FILE__, __LINE__);
    fprintf(stderr,
      "cannot allocate %ld bytes of memory for a\n",
      sizeof(int) * n);
    return NULL;
  }
  for (i = 0; i < n; ++i)
  {
    a[i] = int_file_scan(in);
    if (errno)
    {
      color_error_position(__FILE__, __LINE__);
      fprintf(stderr, "cannot scan a[%d]: %s\n", i, strerror(errno));
      free(a);
      return NULL;
    }
  }
  return a;
}
