#include <errno.h>
#include "cs.h"

static void cs_remove_symmetric_fprint(
  FILE * out, const cs * a, const jagged1 * rows)
{
  cs * b;
  
  b = cs_remove_symmetric(a, rows);
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
  jagged1 * rows;
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
  cs_remove_symmetric_fprint(out, a, rows);
  if (errno)
  {
    perror("Problem in printing reduced matrix");
    goto rows_free;
  }
rows_free:
  jagged1_free(rows);
a_free:
  cs_free(a);
  return errno;
}
