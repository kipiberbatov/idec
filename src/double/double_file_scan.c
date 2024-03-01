#include <errno.h>

#include "double_file_scan.h"

/*
Read from a file and return a number of type double.
If the reading is unsuccessful, return -1 and set errno to EINVAL.
*/
double double_file_scan(FILE * in)
{
  int correct;
  double a;
  
  correct = fscanf(in, "%lf", &a);
  if (correct <= 0)
  {
    errno = EINVAL;
    if (correct == 0)
      fprintf(
        stderr,
        "Error in %s: input file does not store a floating point number\n",
        __func__
      );
    else
      fprintf(
        stderr,
        "Error in %s: nothing to read from current position of input file\n"
        "  (if you read an array, you may have set longer size)\n",
        __func__
      );
    return -1;
  }
  return a;
}
