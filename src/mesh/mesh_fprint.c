#include <errno.h>
#include <string.h>
#include "mesh_private.h"

void mesh_fprint(FILE * out, const mesh * m, const char * format)
{
  int i;
  
  for (i = 0; i < MESH_FPRINT_FORMAT_TOTAL; ++i)
    if (!strcmp(format, mesh_fprint_format[i]))
    {
      mesh_fprint_function[i](out, m);
      if (errno)
      {
        fputs("mesh_fprint - cannot print m\n", stderr);
        return;
      }
      return;
    }
  errno = EINVAL;
  fprintf(stderr, "mesh_fprint - format %s is not supported\n", format);
  return;
}
