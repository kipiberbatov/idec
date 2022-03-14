#include <errno.h>
#include "cs.h"

static void cs_part_fprint(FILE * out, const cs * a)
{
  int i, j;
  double k;
  
  for (i = 0; i < a->m; ++i)
  {
    for (j = 0; j < a->n - 1; ++j)
    {
      k = cs_part(a, i, j);
      fprintf(out, "%g ", k);
    }
    k = cs_part(a, i, j);
    fprintf(out, "%g\n", k);
  }
}

int main()
{
  cs * a;
  FILE * in, * out;
  
  out = stdout;
  in = stdin;
  a = cs_fscan(in);
  if (errno)
  {
    perror("Problem in cs scanning");
    goto a_free;
  }
  cs_part_fprint(out, a);
a_free:
  cs_free(a);
  return errno;
}
