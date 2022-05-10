#include <errno.h>
#include "jagged.h"

int main()
{
  jagged1 * arr;
  FILE * in, * out;
  
  out = stdout;
  in = stdin;
  
  arr = jagged1_fscan(in, "--raw");
  if (errno)
  {
    fputs("main - cannot scan arr\n", stderr);
    return errno;
  }
  jagged1_fprint(out, arr, "--curly");
  
  jagged1_free(arr);
  return 0;
}
