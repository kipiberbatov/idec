#include <errno.h>

#include "int.h"
#include "mesh_file_scan_tess_private.h"

int mesh_file_scan_tess_get_number_of_nodes(FILE * in, int * error)
{
  int cn_0;

  cn_0 = int_file_scan(in);
  *error = errno;
  if (*error)
  {
    fputs("Cannot scan number of nodes\n", stderr);
    return -1;
  }
  if (cn_0 <= 0)
  {
    *error = 1;
    fprintf(stderr, "Number of vertices is %d which is not positive", cn_0);
    return -1;
  }
  return cn_0;
}
