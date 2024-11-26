#include <errno.h>

#include "color.h"
#include "jagged.h"

int main(void)
{
  jagged4 * arr;

  arr = jagged4_file_scan(stdin, "--raw");
  if (errno)
  {
    color_error_position(__FILE__, __LINE__);
    fputs("cannot scan arr in format --raw\n", stderr);
    return errno;
  }
  jagged4_file_print(stdout, arr, "--curly");

  jagged4_free(arr);
  return 0;
}
