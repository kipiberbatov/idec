#include <errno.h>

#include "color.h"
#include "jagged.h"

int main(void)
{
  jagged1 * arr;
  FILE * in, * out;

  out = stdout;
  in = stdin;

  arr = jagged1_file_scan(in, "--raw");
  if (arr == NULL)
  {
    color_error_position(__FILE__, __LINE__);
    fputs("cannot scan arr in format --raw\n", stderr);
    return errno;
  }
  jagged1_file_print(out, arr, "--curly");

  jagged1_free(arr);
  return errno;
}
