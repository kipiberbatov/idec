#include <stdio.h>

#include "color.h"
#include "idec_rgb.h"

void idec_rgb_set_from_scheme_rainbow_no_checks(
  struct idec_rgb * color, int i, int n)
{
  int k_n, k_i, k;
  
  k_n = n / idec_rgb_color_scheme_rainbow_regions_size;
  k_i = i % k_n;
  k = i / k_n;
  idec_rgb_color_scheme_rainbow_regions[k](color, k_i, k_n);
}

void idec_rgb_set_from_scheme_rainbow(
  struct idec_rgb * color, int * status, int i, int n)
{
  if (n % idec_rgb_color_scheme_rainbow_regions_size != 0)
  {
    color_error_position(__FILE__, __LINE__);
    fprintf(stderr,
      "the number of total colors (%s%d%s) "
      "is not divisible by the number of color regions (%s%d%s)\n",
      color_variable, n, color_none,
      color_variable, idec_rgb_color_scheme_rainbow_regions_size, color_none);
    *status = 1;
    return;
  }
  if (i < 0 || i >= n)
  {
    color_error_position(__FILE__, __LINE__);
    fprintf(stderr,
      "the color index i = %s%d%s "
      "is not in the interval [0, total_colors - 1] = [0, %s%d%s]\n",
      color_variable, i, color_none,
      color_variable, n - 1, color_none);
    *status = 1;
    return;
  }
  idec_rgb_set_from_scheme_rainbow_no_checks(color, i, n);
}
