#include <errno.h>
#include <stdlib.h>
#include "int.h"
#include "jagged_private.h"

jagged2 * jagged2_fscan_raw(FILE * in)
{
  int arr_a2_size;
  jagged2 * arr;
  
  arr = (jagged2 *) malloc(sizeof(jagged2));
  if (errno)
  {
    perror("jagged2_fscan_raw - cannot allocate memory for arr");
    goto end;
  }
  arr->a0 = int_fscan(in);
  if (errno)
  {
    perror("jagged2_fscan_raw - cannot scan arr->a0 from input");
    goto arr_free;
  }
  if (arr->a0 <= 0)
  {
    errno = EINVAL;
    perror("jagged2_fscan_raw - arr->a0 is nonpositive");
    goto arr_free;
  }
  arr->a1 = int_array_fscan(in, arr->a0, "--raw");
  if (errno)
  {
    perror("jagged2_fscan_raw - cannot scan arr->a1 from input");
    goto arr_free;
  }
  if (!int_array_positive(arr->a0, arr->a1))
  {
    errno = EINVAL;
    perror("jagged2_fscan_raw - arr->a1 is nonpositive");
    goto arr_a1_free;
  }
  arr_a2_size = int_array_total_sum(arr->a0, arr->a1);
  arr->a2 = int_array_fscan(in, arr_a2_size, "--raw");
  if (errno)
  {
    perror("jagged2_fscan_raw - cannot scan arr->a2 from input");
    goto arr_a1_free;
  }
  return arr;
  
  /* cleaning if an error occurs */
arr_a1_free:
  free(arr->a1);
arr_free:
  free(arr);
end:
  return NULL;
}
