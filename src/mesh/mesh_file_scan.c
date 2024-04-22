#include <errno.h>
#include <string.h>
#include "mesh_private.h"

mesh * mesh_file_scan(FILE * in, const char * format)
{
  mesh * m;

  if (!strcmp(format, "--raw"))
    m = mesh_file_scan_raw(in);
  else
  {
    errno = EINVAL;
    fprintf(stderr, "mesh_file_scan - format %s is not supported\n", format);
    return NULL;
  }
  
  if (errno)
    fputs("mesh_file_scan - cannot scan input\n", stderr);
  return m;
}
