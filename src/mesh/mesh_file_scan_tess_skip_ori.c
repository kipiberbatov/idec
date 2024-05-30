#include <errno.h>

#include "double.h"
#include "mesh_file_scan_tess_private.h"

void mesh_file_scan_tess_skip_ori(FILE * in, int * error, int cn_d)
{
  int i, j;

  for (i = 0; i < cn_d; ++i)
  {
    for (j = 0; j < 4; ++j)
    {
      double_file_scan(in);
      *error = errno;
      if (*error)
      {
        fprintf(stderr, "Missing value\n");
        return;
      }
    }
  }
}
