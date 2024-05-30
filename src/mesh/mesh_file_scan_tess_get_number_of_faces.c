#include <errno.h>

#include "int.h"
#include "mesh_file_scan_tess_private.h"

int mesh_file_scan_tess_get_number_of_faces(FILE * in, int * error)
{
  int cn_2;
  
  cn_2 = int_file_scan(in);
  *error = errno;
  if (*error)
  {
    fputs("Cannot scan number of faces\n", stderr);
    return -1;
  }
  if (cn_2 <= 0)
  {
    *error = 1;
    fprintf(stderr, "Number of faces is %d which is not positive", cn_2);
    return -1;
  }
  return cn_2;
}
