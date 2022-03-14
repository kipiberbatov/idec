#include <errno.h>
#include "cs.h"
#include "double.h"

static void cs_constrained_cholsol_fprint(
  FILE * out, const cs * a, const double * b, const jagged1 * rows)
{
  double * x;
  
  x = cs_constrained_cholsol(a, b, rows);
  if (errno)
  {
    perror("Cannot apply cs_constrained cholsol");
    goto x_free;
  }
  fprintf(out, "%d\n", a->m);
  double_fprint_array_raw(out, a->m, x);
x_free:
  free(x);
}

int main()
{
  int b_m;
  double * b;
  jagged1 * rows;
  cs * a;
  FILE * in, * out;
  
  out = stdout;
  in = stdin;
  fscanf(in, "%d", &b_m);
  b = double_fscan_array(in, b_m);
  if (errno)
  {
    perror("Cannot scan right-hand side");
    goto b_free;
  }
  rows = jagged1_fscan_raw(in);
  if (errno)
  {
    perror("Cannot scan rows for deletion");
    goto rows_free;
  }
  a = cs_fscan(in);
  if (errno)
  {
    perror("Cannot scan left-hand side");
    goto a_free;
  }
  cs_constrained_cholsol_fprint(out, a, b, rows);
  if (errno)
  {
    perror("During calculation of cs_constrained_cholsol_fprint");
    goto a_free;
  }
a_free:
  cs_free(a);
rows_free:
  jagged1_free(rows);
b_free:
  free(b);
  return errno;
}
