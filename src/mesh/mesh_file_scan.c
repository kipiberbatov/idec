#include <errno.h>
#include <string.h>
#include "mesh_private.h"

mesh * mesh_file_scan(FILE * in, const char * format)
{
  int i;
  mesh * m;
  
  for (i = 0; i < mesh_file_scan_format_total; ++i)
    if (!strcmp(format, mesh_file_scan_format[i]))
    {
      m = mesh_file_scan_function[i](in);
      if (errno)
      {
        fputs("mesh_file_scan - cannot scan input\n", stderr);
        return NULL;
      }
      return m;
    }
  errno = EINVAL;
  fprintf(stderr, "mesh_file_scan - format %s is not supported\n", format);
  return NULL;
}
