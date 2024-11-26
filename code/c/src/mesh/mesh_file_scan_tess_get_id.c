#include <errno.h>

#include "color.h"
#include "int.h"
#include "mesh_file_scan_tess_private.h"

void mesh_file_scan_tess_get_id(int * c, FILE * in, int * error, int cn_d)
{
  int i;

  for (i = 0; i < cn_d; ++i)
  {
    c[i] = int_file_scan(in) - 1;
    if (errno)
    {
      color_error_position(__FILE__, __LINE__);
      fprintf(stderr, "cannot scan %d-th cell's id\n", i + 1);
      *error = errno;
      return;
    }
  }
}
