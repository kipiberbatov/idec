#include <errno.h>
#include <stdlib.h>
#include "double.h"
#include "int.h"
#include "quasi_cube.h"

quasi_cube * quasi_cube_file_scan(FILE * in)
{
  quasi_cube * s;
  
  s = (quasi_cube *) malloc(sizeof(quasi_cube));
  if (errno)
  {
    fputs("quasi_cube_file_scan - cannot allocate memory for s\n", stderr);
    goto end;
  }
  
  s->dim_embedded = int_file_scan(in);
  if (errno)
  {
    fputs("quasi_cube_file_scan - cannot scan s->dim_embedded\n", stderr);
    goto end;
  }
  
  s->dim = int_file_scan(in);
  if (errno)
  {
    fputs("quasi_cube_file_scan - cannot scan s->dim\n", stderr);
    goto end;
  }
  
  s->coord = double_array_file_scan(in, s->dim_embedded * (1 << s->dim), "--raw");
  if (errno)
  {
    fputs("quasi_cube_file_scan - cannot scan s->coord\n", stderr);
    goto s_free;
  }
  return s;
  
  /* cleaning if an error occurs */
s_free:
  free(s);
end:
  return NULL;
}
