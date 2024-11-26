#include <errno.h>
#include <string.h>

#include "color.h"
#include "mesh.h"

mesh * mesh_file_scan_by_name(const char * name, const char * format)
{
  FILE * in;
  mesh * m = NULL;

  in = fopen(name, "r");
  if (in == NULL)
  {
    color_error_position(__FILE__, __LINE__);
    fprintf(stderr,
      "cannot open file %s for reading: %s\n",
      name, strerror(errno));
    goto end;
  }

  m = mesh_file_scan(in, format);
  if (m == NULL)
  {
    color_error_position(__FILE__, __LINE__);
    fprintf(stderr,
      "cannot scan mesh m from file %s in format %s\n",
      name, format);
    goto in_close;
  }

in_close:
  fclose(in);
end:
  return m;
}
