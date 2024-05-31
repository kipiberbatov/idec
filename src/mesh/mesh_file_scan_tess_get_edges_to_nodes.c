#include <errno.h>

#include "int.h"
#include "mesh_file_scan_tess_private.h"

void mesh_file_scan_tess_get_edges_to_nodes(int * edges_to_nodes, FILE * in,
  int * error, int cn_1)
{
  int c_i, i, j, x;

  for (i = 0; i < cn_1; ++i)
  {
    c_i = int_file_scan(in);
    *error = errno;
    if (*error)
    {
      fprintf(stderr, "Cannot scan %d-th 1-cell id\n", i);
      return;
    }
    if (c_i != (i + 1))
    {
      *error = 1;
      fprintf(stderr, "Invalid edge index\n");
      return;
    }
    for (j = 0; j <= 1; ++j)
    {
      edges_to_nodes[i * 2 + j] = int_file_scan(in);
      *error = errno;
      if (*error)
      {
        fprintf(stderr, "Unable to scan edge node (%d, %d)\n", i, j);
        return;
      }
      --edges_to_nodes[i * 2 + j];
    }
    x = int_file_scan(in);
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
      fprintf(stderr, "Instead, we have %d\n", x);
      return;
    }
  }
}
