#include "rgb.h"

static void rgb_red_to_yellow(rgb * color, int i, int n)
{
  color->red = 1.;
  color->green = (double) i / (double) n;
  color->blue = 0.;
}

static void rgb_yellow_to_green(rgb * color, int i, int n)
{
  color->red = 1. - (double) i / (double) n;
  color->green = 1.;
  color->blue = 0.;
}

static void rgb_green_to_cyan(rgb * color, int i, int n)
{
  color->red = 0.;
  color->green = 1.;
  color->blue = (double) i / (double) n;
}

static void rgb_cyan_to_blue(rgb * color, int i, int n)
{
  color->red = 0.;
  color->green = 1. - (double) i / (double) n;
  color->blue = 1.;
}

static void rgb_blue_to_magenta(rgb * color, int i, int n)
{
  color->red = (double) i / (double) n;
  color->green = 0.;
  color->blue = 1.;
}

typedef void (*rgb_nuance_t)(rgb *, int, int);

rgb_nuance_t rgb_nuances[] =
{
  rgb_red_to_yellow,
  rgb_yellow_to_green,
  rgb_green_to_cyan,
  rgb_cyan_to_blue,
  rgb_blue_to_magenta
};

void rgb_color(rgb * color, int i, int n)
{
  int k_n = n / (sizeof(rgb_nuances) / sizeof(rgb_nuance_t));
  int k_i = i % k_n;
  int k = i / k_n;
  rgb_nuances[k](color, k_i, k_n);
}
