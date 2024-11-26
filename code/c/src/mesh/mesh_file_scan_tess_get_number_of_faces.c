#include <errno.h>

#include "color.h"
#include "int.h"
#include "mesh_file_scan_tess_private.h"

int mesh_file_scan_tess_get_number_of_faces(FILE * in, int * error)
{
  int cn_2;

  cn_2 = int_file_scan(in);
  if (errno)
  {
    color_error_position(__FILE__, __LINE__);
    fputs("cannot scan number of faces\n", stderr);
    *error = errno;
    return -1;
  }
  if (cn_2 <= 0)
  {
    color_error_position(__FILE__, __LINE__);
    fprintf(stderr, "number of faces is %d which is not positive", cn_2);
    *error = 1;
    return -1;
  }
  return cn_2;
}
