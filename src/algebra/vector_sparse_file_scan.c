#include <errno.h>
#include <string.h>
#include "vector_sparse_private.h"

vector_sparse * vector_sparse_file_scan(FILE * in, const char * format)
{
  vector_sparse * a;

  if (!strcmp(format, "--raw"))
    a = vector_sparse_file_scan_raw(in);
  else
  {
    errno = EINVAL;
    fprintf(stderr,
      "vector_sparse_file_scan - format %s is not supported\n", format);
    return NULL;
  }
  
  if (errno)
    fputs("vector_sparse_file_scan - cannot scan input\n", stderr);
  return a;
}
