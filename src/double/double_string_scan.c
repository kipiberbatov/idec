#include <errno.h>

#include "double_string_scan.h"

/*
Read from a constant string and return a number of type double.
If the reading is unsuccessful, return -1 and set errno to EINVAL.
*/
double double_string_scan(const char * s)
{
  int correct;
  double a;
  
  correct = sscanf(s, "%lf", &a);
  if (correct <= 0)
  {
    errno = EINVAL;
    if (correct == 0)
      fprintf(
        stderr,
        "Error in %s: input string does not store a floating point number\n",
        __func__
      );
    else
      fprintf(stderr, "Error in %s: empty input string\n", __func__);
    return -1;
  }
  return a;
}
