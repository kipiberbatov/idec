#include <errno.h>
#include <stdlib.h>

#include "double.h"
#include "int.h"
#include "mesh_file_scan_tess_private.h"

/* error is impossible there, as data is checked on the previous call */
void mesh_file_scan_tess_get_faces_to_subfaces(int * faces_to_subfaces,
  FILE * in, int cn_2, int faces_total_edges)
{
  int faces_number_of_sides_i, i, index, j;

  index = 0;
  for (i = 0; i < cn_2; ++i)
  {
    int_file_scan(in); /* c_i; */

    faces_number_of_sides_i = int_file_scan(in);
    for (j = 0; j < faces_number_of_sides_i; ++j)
    {
      faces_to_subfaces[index] = int_file_scan(in) - 1;
      ++index;
    }

    faces_number_of_sides_i = int_file_scan(in);
    for (j = 0; j < faces_number_of_sides_i; ++j)
    {
      faces_to_subfaces[index] = abs(int_file_scan(in)) - 1;
      ++index;
    }

    for (j = 0; j < 9; ++j)
      double_file_scan(in); /* garbage values */
  }
}
