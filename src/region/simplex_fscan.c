#include <errno.h>
#include <stdlib.h>
#include "double.h"
#include "int.h"
#include "simplex.h"

simplex * simplex_fscan(FILE * in)
{
  simplex * s;
  
  s = (simplex *) malloc(sizeof(simplex));
  if (errno)
  {
    fputs("simplex_fscan - cannot allocate memory for s\n", stderr);
    goto end;
  }
  
  s->dim_embedded = int_fscan(in);
  if (errno)
  {
    fputs("simplex_fscan - cannot scan s->dim_embedded\n", stderr);
    goto end;
  }
  
  s->dim = int_fscan(in);
  if (errno)
  {
    fputs("simplex_fscan - cannot scan s->dim\n", stderr);
    goto end;
  }
  
  s->coord = double_array_fscan(in, s->dim_embedded * (1 + s->dim), "--raw");
  if (errno)
  {
    fputs("simplex_fscan - cannot scan s->coord\n", stderr);
    goto s_free;
  }
  return s;
  
  /* cleaning if an error occurs */
s_free:
  free(s);
end:
  return NULL;
}
