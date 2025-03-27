#include "idec_rgb.h"

void idec_rgb_get_color_rgb(struct idec_rgb * rgb_color, const void * color)
{
  *rgb_color = *((const struct idec_rgb *) color);
}
