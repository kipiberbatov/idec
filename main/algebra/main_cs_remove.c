#include <errno.h>
#include "cs.h"

static void cs_remove_fprint(
  FILE * out, const cs * a, const jagged1 * rows, const jagged1 * cols)
{
  cs * b;
  
  b = cs_remove(a, rows, cols);
  if (errno)
  {
    perror("Problem in cs scanning");
    goto b_free;
  }
  cs_fprint(out, b, "--raw");
b_free:
  cs_free(b);
}

int main()
{
  cs * a;
  jagged1 * rows, * cols;
  FILE * in, * out;
  
  out = stdout;
  in = stdin;
  a = cs_fscan(in);
  if (errno)
  {
    perror("Problem in original matrix scanning");
    goto a_free;
  }
  rows = jagged1_fscan_raw(in);
  if (errno)
  {
    perror("Problem in rows scanning");
    goto rows_free;
  }
  cols = jagged1_fscan_raw(in);
  if (errno)
  {
    perror("Problem in columns scanning");
    goto cols_free;
  }
  cs_remove_fprint(out, a, rows, cols);
  if (errno)
  {
    perror("Problem in printing reduced matrix");
    goto cols_free;
  }
cols_free:
  jagged1_free(cols);
rows_free:
  jagged1_free(rows);
a_free:
  cs_free(a);
  return errno;
}
