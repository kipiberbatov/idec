#include <errno.h>
#include <string.h>

#include "color.h"
#include "mesh_private.h"

mesh * mesh_file_scan(FILE * in, const char * format)
{
  mesh * m;

  if (!strcmp(format, "--raw"))
    m = mesh_file_scan_raw(in);
  else if (!strcmp(format, "--tess"))
    m = mesh_file_scan_tess(in);
  else
  {
    color_error_position(__FILE__, __LINE__);
    fprintf(stderr, "format %s is not supported\n", format);
    errno = EINVAL;
    return NULL;
  }

  if (errno)
  {
    color_error_position(__FILE__, __LINE__);
    fprintf(stderr, "cannot scan mesh input in format %s\n", format);
  }

  return m;
}
