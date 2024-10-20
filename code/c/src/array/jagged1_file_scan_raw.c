#include <errno.h>
#include <stdlib.h>
#include "int.h"
#include "jagged_private.h"

jagged1 * jagged1_file_scan_raw(FILE * in)
{
  jagged1 * arr;

  arr = (jagged1 *) malloc(sizeof(jagged1));
  if (errno)
  {
    perror("jagged1_file_scan_raw: cannot allocate memory for arr");
    goto end;
  }
  arr->a0 = int_file_scan(in);
  if (errno)
  {
    perror("jagged1_file_scan_raw: cannot scan arr->a0 from input");
    goto arr_free;
  }
  if (arr->a0 < 0)
  {
    errno = EINVAL;
    perror("jagged1_file_scan_raw: arr->a0 is negative");
    goto arr_free;
  }
  arr->a1 = int_array_file_scan(in, arr->a0, "--raw");
  if (errno)
  {
    perror("jagged1_file_scan_raw: cannot scan arr->a1 from input");
    goto arr_free;
  }
  return arr;

  /* cleaning if an error occurs */
arr_free:
  free(arr);
end:
  return NULL;
}
