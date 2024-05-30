#include <errno.h>

#include "double.h"
#include "int.h"
#include "mesh_file_scan_tess_private.h"

void mesh_file_scan_tess_get_faces_number_of_sides(
  int * faces_number_of_sides, FILE * in, int * error, int cn_2)
{
  int c_i, i, j, tmp, x;

  for (i = 0; i < cn_2; ++i)
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

    faces_number_of_sides[i] = int_file_scan(in);
    *error = errno;
    if (*error)
    {
      fprintf(stderr, "Cannot scan %d-th 2-cell number of sides\n", i);
      return;
    }
    if (faces_number_of_sides[i] <= 3)
    {
      *error = 1;
      fprintf(stderr, "Invalid number of sides\n");
      return;
    }

    for (j = 0; j < faces_number_of_sides[i]; ++j)
    {
      x = int_file_scan(in);
      *error = errno;
      if (*error)
      {
        fprintf(stderr, "Unable to scan subface (%d, %d)\n", i, j);
        return;
      }
      if (x <= 0)
      {
        *error = 1;
        fprintf(stderr, "Invalid index of a vertex, must be positive\n");
        return;
      }
    }

    tmp = int_file_scan(i);
    *error = errno;
    if (*error)
    {
      fprintf(stderr, "Cannot scan %d-th 2-cell number of sides\n", i);
      return;
    }
    if (faces_number_of_sides[i] != tmp)
    {
      *error = 1;
      fprintf(stderr, "Invalid number of sides\n");
      return;
    }

    for (j = 0; j < faces_number_of_sides[i]; ++j)
    {
      x = int_file_scan(in);
      *error = errno;
      if (*error)
      {
        fprintf(stderr, "Unable to scan subface (%d, %d)\n", i, j);
        return;
      }
    }
    
    for (j = 0; j < 9; ++j)
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
