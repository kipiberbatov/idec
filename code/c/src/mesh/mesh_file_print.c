#include <errno.h>
#include <string.h>
#include "mesh_private.h"

void mesh_file_print(FILE * out, const mesh * m, const char * format)
{
  if (!strcmp(format, "--raw"))
    mesh_file_print_raw(out, m);
  else
  {
    errno = EINVAL;
    fprintf(stderr, "mesh_file_print - format %s is not supported\n", format);
  }
}
