#include <errno.h>

#include "double.h"
#include "int.h"
#include "mesh_file_scan_tess_private.h"

#define EPSILON .0000000001

void mesh_file_scan_tess_get_coordinates(double * coordinates, FILE * in,
  int * error, int d, int cn_0)
{
  int c_i, i, j;
  double x;

  for (i = 0; i < cn_0; ++i)
  {
    c_i = int_file_scan(in);
    *error = errno;
    if (*error)
    {
      fprintf(stderr, "Cannot scan %d-th 0-cell id\n", i);
      return;
    }
    if (c_i != (i + 1))
    {
      *error = 1;
      fprintf(stderr, "Invalid vertex index\n");
      return;
    }
    for (j = 0; j < d; ++j)
    {
      x = double_file_scan(in);
      *error = errno;
      if (*error)
      {
        fprintf(stderr, "Unable to scan a coordinate (%d, %d)\n", i, j);
        return;
      }
      if (x < EPSILON && -x < EPSILON)
        coordinates[d * i + j] = 0;
      else
        coordinates[d * i + j] = x;
    }
    for (j = d; j < 4; ++j)
    {
      x = double_file_scan(in);
      *error = errno;
      if (*error)
      {
        fprintf(stderr, "Missing value\n");
        return;
      }
      if (x != 0)
      {
        *error = 1;
        fprintf(stderr, "mesh_file_scan_tess_get_edges_to_nodes: "
        "i = %d, last values must be zeroes\n", i);
        fprintf(stderr, "Instead, we have %g\n", x);
        return;
      }
    }
  }
}
