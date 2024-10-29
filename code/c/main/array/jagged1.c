#include <errno.h>
#include "jagged.h"

int main()
{
  jagged1 * arr;
  FILE * in, * out;

  out = stdout;
  in = stdin;

  arr = jagged1_file_scan(in, "--raw");
  if (errno)
  {
    fputs("main - cannot scan arr\n", stderr);
    return errno;
  }
  jagged1_file_print(out, arr, "--curly");

  jagged1_free(arr);
  return 0;
}
