#include <errno.h>

#include "double.h"
#include "int.h"
#include "mesh_file_scan_tess_private.h"

void mesh_file_scan_tess_skip_seed(FILE * in, int * error, int cn_d,
  const int * c)
{
  int c_i, i, j;

  for (i = 0; i < cn_d; ++i)
  {
    c_i = int_file_scan(in);
    *error = errno;
    if (*error)
    {
      fprintf(stderr, "mesh_file_scan_tess_skip_seed: "
        "cannot scan %d-th cell id dimension\n", i);
      return;
    }
    if (c_i != c[i])
    {
      *error = 1;
      fprintf(stderr, "mesh_file_scan_tess_skip_seed: "
        "id of cell[%d] does not correspond with data from seed", c_i);
      return;
    }
    for (j = 0; j < 4; ++j)
    {
      double_file_scan(in);
      *error = errno;
      if (*error)
      {
        fprintf(stderr,
          "mesh_file_scan_tess_skip_seed: missing value (%d, %d)\n", i, j);
        return;
      }
    }
  }
}
