#include <errno.h>
#include "array_fprint.h"
#include "jagged.h"

int main()
{
  jagged1 * arr;
  FILE * in, * out;
  
  out = stdout;
  in = stdin;
  arr = jagged1_fscan_raw(in);
  if (errno)
  {
    perror("Problem in array scanning");
    goto arr_free;
  }
  array_fprint1(out, arr->a0, arr->a1);
  fputc('\n', out);
arr_free:
  jagged1_free(arr);
  return errno;
}
