#include "cmc_rgb.h"

void cmc_rgb_get_color_rgb(struct cmc_rgb * rgb_color, const void * color)
{
  *rgb_color = *((const struct cmc_rgb *) color);
}
