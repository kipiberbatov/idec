#include "idec_rgb.h"

static void red_to_yellow(struct idec_rgb * color, int i, int n)
{
  color->red = 1.;
  color->green = (double) i / (double) n;
  color->blue = 0.;
}

static void yellow_to_green(struct idec_rgb * color, int i, int n)
{
  color->red = 1. - (double) i / (double) n;
  color->green = 1.;
  color->blue = 0.;
}

static void green_to_cyan(struct idec_rgb * color, int i, int n)
{
  color->red = 0.;
  color->green = 1.;
  color->blue = (double) i / (double) n;
}

static void cyan_to_blue(struct idec_rgb * color, int i, int n)
{
  color->red = 0.;
  color->green = 1. - (double) i / (double) n;
  color->blue = 1.;
}

static void blue_to_magenta(struct idec_rgb * color, int i, int n)
{
  color->red = (double) i / (double) n;
  color->green = 0.;
  color->blue = 1.;
}

static void (* const subregions[])(struct idec_rgb *, int, int) =
{
  red_to_yellow,
  yellow_to_green,
  green_to_cyan,
  cyan_to_blue,
  blue_to_magenta
};

void (* const * idec_rgb_color_scheme_rainbow_regions)(
  struct idec_rgb *, int, int) = subregions;

const int idec_rgb_color_scheme_rainbow_regions_size =
sizeof(subregions) / sizeof(*subregions);
