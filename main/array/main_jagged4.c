#include <errno.h>
#include "jagged.h"

int main()
{
  jagged4 * arr;
  
  arr = jagged4_fscan(stdin, "--raw");
  if (errno)
  {
    fputs("main - cannot scan arr\n", stderr);
    return errno;
  }
  
  jagged4_fprint(stdout, arr, "--curly");
  fputc('\n', stdout);
  jagged4_free(arr);
  return 0;
}
