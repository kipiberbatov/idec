#include <errno.h>
#include <string.h>

#include "color.h"
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
    {
      color_error_position(__FILE__, __LINE__);
      fprintf(stderr,
        "input is not a valid floating point number: %s\n",
        strerror(errno));
    }
    else
    {
      color_error_position(__FILE__, __LINE__);
      fprintf(stderr,
        "there is no number to scan: %s\n",
        strerror(errno));
    }
    return -1;
  }
  return a;
}
