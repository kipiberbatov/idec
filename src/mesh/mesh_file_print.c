#include <errno.h>
#include <string.h>
#include "mesh_private.h"

void mesh_file_print(FILE * out, const mesh * m, const char * format)
{
  int i;
  
  for (i = 0; i < mesh_file_print_format_total; ++i)
    if (!strcmp(format, mesh_file_print_format[i]))
    {
      mesh_file_print_function[i](out, m);
      if (errno)
      {
        fputs("mesh_file_print - cannot print m\n", stderr);
        return;
      }
      return;
    }
  errno = EINVAL;
  fprintf(stderr, "mesh_file_print - format %s is not supported\n", format);
  return;
}
