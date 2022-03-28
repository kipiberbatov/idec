#include <errno.h>
#include <stdlib.h>
#include "double.h"

double double_fscan(FILE * in)
{
  int correct;
  double a;
  
  correct = fscanf(in, "%lf", &a);
  if (correct <= 0)
  {
    errno = EINVAL;
    if (correct == 0)
      perror("double_fscan - not a valid floating point number");
    else
      perror("double_fscan - there is no number to scan");
    return -1;
  }
  return a;
}
