#include <errno.h>
#include <string.h>

#include "color.h"
#include "mesh_private.h"

mesh * mesh_file_scan(FILE * in, const char * format)
{
  mesh * m;
  mesh * (*scanner)(FILE *);

  if (!strcmp(format, "--raw"))
    scanner = mesh_file_scan_raw;
  else if (!strcmp(format, "tess"))
    scanner = mesh_file_scan_tess;
  else
  {
    color_error_position(__FILE__, __LINE__);
    fprintf(stderr,
      "format %s%s%s is not supported\n",
      color_variable, format, color_none);
    errno = EINVAL;
    return NULL;
  }

  m = scanner(in);
  if (errno)
  {
    color_error_position(__FILE__, __LINE__);
    fprintf(stderr,
      "cannot scan mesh input in format %s%s%s\n",
      color_variable, format, color_none);
    return NULL;
  }

  return m;
}
