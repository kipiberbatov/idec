#include <errno.h>

#include "double.h"
#include "int.h"
#include "mesh_file_scan_tess_private.h"

void mesh_file_scan_tess_skip_seed(FILE * in, int * error, int cn_d,
  const int * c)
{
  int c_i, i;
  double x;

  for (i = 0; i < cn_d; ++i)
  {
    c_i = int_file_scan(in);
    if (errno)
    {
      fprintf(stderr, "Cannot scan %d-th cell id dimension\n", i);
      return;
    }
    if (c_i != c[i])
    {
      fprintf(stderr,
        "Id of cell[%d] doe not correspond with data from seed", c_i);
      return;
    }
    for (i = 0; i < 4; ++i)
    {
      x = double_file_scan(in);
      if (errno)
      {
        fprintf(stderr, "Missing value\n");
        return;
      }
    }
  }
}
