#include <errno.h>
#include <string.h>

#include "mesh_and_boundary.h"

mesh_and_boundary * mesh_and_boundary_file_scan(FILE * in, const char * format)
{
  mesh_and_boundary * m;

  if (!strcmp(format, "--tess"))
    m = mesh_and_boundary_file_scan_tess(in);
  else
  {
    errno = EINVAL;
    fprintf(stderr, "%s:%d: format %s is not supported\n",
      __FILE__, __LINE__, format);
    return NULL;
  }
  if (errno)
    fprintf(stderr, "%s:%d: cannot scan input\n", __FILE__, __LINE__);
  return m;
}
