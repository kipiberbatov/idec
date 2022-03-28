#include <errno.h>
#include <string.h>
#include "mesh_private.h"

mesh * mesh_fscan(FILE * in, const char * format)
{
  int i;
  mesh * m;
  
  for (i = 0; i < MESH_FSCAN_FORMAT_TOTAL; ++i)
    if (!strcmp(format, mesh_fscan_format[i]))
    {
      m = mesh_fscan_function[i](in);
      if (errno)
      {
        fputs("mesh_fscan - cannot scan input\n", stderr);
        return NULL;
      }
      return m;
    }
  errno = EINVAL;
  fprintf(stderr, "mesh_fscan - format %s is not supported\n", format);
  return NULL;
}
