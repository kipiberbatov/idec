#include <stdio.h>

#include "color.h"
#include "idec_rgb.h"

void idec_rgb_check_color_scheme_rainbow(int * status, int n)
{
  if (n % idec_rgb_color_scheme_rainbow_regions_size)
  {
    color_error_position(__FILE__, __LINE__);
    fprintf(stderr,
      "the number of total colors (%s%d%s) "
      "is not divisible by the number of color regions (%s%d%s)\n",
      color_variable, n, color_none,
      color_variable, idec_rgb_color_scheme_rainbow_regions_size, color_none);
    *status = 1;
  }
}
