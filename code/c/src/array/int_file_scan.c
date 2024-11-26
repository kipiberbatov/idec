#include <errno.h>

#include "color.h"
#include "int.h"

int int_file_scan(FILE * in)
{
  int a, correct;

  correct = fscanf(in, "%d", &a);
  if (correct <= 0)
  {
    color_error_position(__FILE__, __LINE__);
    if (correct == 0)
      fputs("input is not a valid integer\n", stderr);
    else
      fputs("there is no number to scan\n", stderr);
    errno = EINVAL;
    return -1;
  }
  return a;
}
