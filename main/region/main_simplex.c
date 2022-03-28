#include <errno.h>
#include "double.h"
#include "simplex.h"

static void simplex_measure_fprint(FILE * out, const simplex * r)
{
  double r_area;

  r_area = simplex_measure(r);
  fprintf(out, "area : %g\n", r_area);
}

static void simplex_centroid_fprint(FILE * out, const simplex * r)
{
  double r_centroid[3];

  simplex_centroid(r_centroid, r);
  fputs("centroid : ", out);
  double_array_fprint(out, r->dim_embedded, r_centroid, "--raw");
  fputc('\n', out);
}

int main()
{
  simplex * r;
  FILE * in, * out;
  
  out = stdout;
  in = stdin;
  r = simplex_fscan(in);
  if (errno)
  {
    perror("Problem in simplex scanning");
    simplex_free(r);
    return errno;
  }
  simplex_measure_fprint(out, r);
  simplex_centroid_fprint(out, r);
  simplex_free(r);
  return 0;
}
