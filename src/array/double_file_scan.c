#include <errno.h>
#include <stdlib.h>
#include "double.h"

double double_file_scan(FILE * in)
{
  int correct;
  double a;
  
  correct = fscanf(in, "%lf", &a);
  if (correct <= 0)
  {
    errno = EINVAL;
    if (correct == 0)
      perror("double_file_scan - not a valid floating point number");
    else
      perror("double_file_scan - there is no number to scan");
    return -1;
  }
  return a;
}
