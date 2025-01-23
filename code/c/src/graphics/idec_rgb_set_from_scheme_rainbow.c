#include <stdio.h>

#include "color.h"
#include "idec_rgb.h"

static void red_to_yellow(idec_rgb * color, int i, int n)
{
  color->red = 1.;
  color->green = (double) i / (double) n;
  color->blue = 0.;
}

static void yellow_to_green(idec_rgb * color, int i, int n)
{
  color->red = 1. - (double) i / (double) n;
  color->green = 1.;
  color->blue = 0.;
}

static void green_to_cyan(idec_rgb * color, int i, int n)
{
  color->red = 0.;
  color->green = 1.;
  color->blue = (double) i / (double) n;
}

static void cyan_to_blue(idec_rgb * color, int i, int n)
{
  color->red = 0.;
  color->green = 1. - (double) i / (double) n;
  color->blue = 1.;
}

static void blue_to_magenta(idec_rgb * color, int i, int n)
{
  color->red = (double) i / (double) n;
  color->green = 0.;
  color->blue = 1.;
}

void
idec_rgb_set_from_scheme_rainbow(idec_rgb * color, int * status, int i, int n)
{
  int k_n, k_i, k, size;
  void (*(color_subschemes[]))(idec_rgb *, int, int) =
  {
    red_to_yellow,
    yellow_to_green,
    green_to_cyan,
    cyan_to_blue,
    blue_to_magenta
  };

  size = sizeof(color_subschemes) / sizeof(*color_subschemes);
  if (n % size != 0)
  {
    color_error_position(__FILE__, __LINE__);
    fprintf(stderr,
      "the number of total colors (%s%d%s) "
      "is not divisible by the number of color regions (%s%d%s)\n",
      color_variable, n, color_none,
      color_variable, size, color_none);
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
  k_n = n / size;
  k_i = i % k_n;
  k = i / k_n;
  color_subschemes[k](color, k_i, k_n);
}
