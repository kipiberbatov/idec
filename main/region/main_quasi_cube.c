#include <errno.h>
#include "double.h"
#include "quasi_cube.h"

static void quasi_cube_measure_fprint(FILE * out, const quasi_cube * r)
{
  double r_area;

  r_area = quasi_cube_measure(r);
  fprintf(out, "area : %g\n", r_area);
}

static void quasi_cube_centroid_fprint(FILE * out, const quasi_cube * r)
{
  double r_centroid[3];

  quasi_cube_centroid(r_centroid, r);
  fputs("centroid : ", out);
  double_array_fprint(out, r->dim_embedded, r_centroid, "--raw");
  fputc('\n', out);
}

int main()
{
  quasi_cube * r;
  FILE * in, * out;
  
  out = stdout;
  in = stdin;
  r = quasi_cube_fscan(in);
  if (errno)
  {
    perror("Problem in quasi-cube scanning");
    quasi_cube_free(r);
    return errno;
  }
  quasi_cube_measure_fprint(out, r);
  quasi_cube_centroid_fprint(out, r);
  quasi_cube_free(r);
  return 0;
}
