#include "double.h"
#include "int.h"
#include "quasi_cube.h"

quasi_cube * quasi_cube_fscan(FILE * in)
{
  int s_dim_embedded, s_dim;
  double * s_coord;
  quasi_cube * s;
  
  s = (quasi_cube *) malloc(sizeof(quasi_cube));
  /* NULL pointer check */
  s_dim_embedded = int_fscan(in);
  s_dim = int_fscan(in);
  s_coord = double_fscan_array(in, s_dim_embedded * (1 << s_dim));
  /* NULL pointer check */
  quasi_cube_set(s, s_dim_embedded, s_dim, s_coord);
  return s;
}
