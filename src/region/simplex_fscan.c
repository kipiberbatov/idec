#include "double.h"
#include "int.h"
#include "simplex.h"

simplex * simplex_fscan(FILE * in)
{
  int s_dim_embedded, s_dim;
  double * s_coord;
  simplex * s;
  
  s = (simplex *) malloc(sizeof(simplex));
  /* NULL pointer check */
  s_dim_embedded = int_fscan(in);
  s_dim = int_fscan(in);
  s_coord = double_fscan_array(in, s_dim_embedded * (s_dim + 1));
  /* NULL pointer check */
  simplex_set(s, s_dim_embedded, s_dim, s_coord);
  return s;
}
