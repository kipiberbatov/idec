#include <errno.h>

#include "int.h"
#include "mesh_file_scan_tess_private.h"

int mesh_file_scan_tess_get_number_of_edges(FILE * in, int * error)
{
  int cn_1;
  
  cn_1 = int_file_scan(in);
  *error = errno;
  if (*error)
  {
    fputs("Cannot scan number of edges\n", stderr);
    return -1;
  }
  if (cn_1 <= 0)
  {
    *error = 1;
    fprintf(stderr, "Number of edges is %d which is not positive", cn_1);
    return -1;
  }
  return cn_1;
}
