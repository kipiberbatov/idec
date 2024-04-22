#include <errno.h>
#include "jagged.h"

int main()
{
  jagged4 * arr;
  
  arr = jagged4_file_scan(stdin, "--raw");
  if (errno)
  {
    fputs("main - cannot scan arr\n", stderr);
    return errno;
  }
  jagged4_file_print(stdout, arr, "--curly");
  
  jagged4_free(arr);
  return 0;
}
