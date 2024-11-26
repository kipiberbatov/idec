#include <errno.h>

#include "color.h"
#include "int.h"
#include "mesh_file_scan_tess_private.h"

int mesh_file_scan_tess_get_number_of_edges(FILE * in, int * error)
{
  int cn_1;

  cn_1 = int_file_scan(in);
  if (errno)
  {
    color_error_position(__FILE__, __LINE__);
    fputs("cannot scan number of edges\n", stderr);
    *error = errno;
    return -1;
  }
  if (cn_1 <= 0)
  {
    color_error_position(__FILE__, __LINE__);
    fprintf(stderr, "number of edges is %d which is not positive", cn_1);
    *error = 1;
    return -1;
  }
  return cn_1;
}
