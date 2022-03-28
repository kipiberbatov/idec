#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include "mesh.h"

mesh * mesh_fscan_by_name(const char * name, const char * format)
{
  FILE * in;
  mesh * a = NULL;

  in = fopen(name, "r");
  if (errno)
  {
    fprintf(stderr, "mesh_fscan_by_name - cannot open file %s: %s\n",
            name, strerror(errno));
    goto end;
  }
  a = mesh_fscan(in, format);
  if (errno)
  {
    fprintf(stderr, "mesh_fscan_by_name - cannot scan a ");
    fprintf(stderr, "in format %s: %s\n", format, strerror(errno));
    goto in_close;
  }
in_close:
  fclose(in);
end:
  return a;
}
