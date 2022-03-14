#include <errno.h>
#include "jagged.h"

int main()
{
  jagged4 * arr;
  FILE * in, * out;
  
  out = stdout;
  in = stdin;
  arr = jagged4_fscan_raw(in);
  if (errno)
  {
    perror("Problem in jagged4 scanning");
    goto arr_free;
  }
  jagged4_fprint(out, arr);
  fputc('\n', out);
arr_free:
  jagged4_free(arr);
  return errno;
}
