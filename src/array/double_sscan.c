#include <errno.h>
#include <stdlib.h>
#include "double.h"

double double_sscan(const char * s)
{
  int correct;
  double a;
  
  correct = sscanf(s, "%lf", &a);
  if (correct <= 0)
  {
    errno = EINVAL;
    if (correct == 0)
      fputs("double_sscan - not a valid floating point number\n", stderr);
    else
      fputs("double_sscan - empty string\n", stderr);
    return -1;
  }
  return a;
}
