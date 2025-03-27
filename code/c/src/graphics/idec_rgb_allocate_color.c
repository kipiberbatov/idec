#include <stdio.h>
#include <stdlib.h>

#include "color.h"
#include "idec_error_message.h"
#include "idec_rgb.h"

void idec_rgb_allocate_color(struct idec_rgb ** color, int * status)
{
  *color = (struct idec_rgb *) malloc(sizeof(struct idec_rgb));
  if (*color == NULL)
  {
    color_error_position(__FILE__, __LINE__);
    idec_error_message_malloc(sizeof(struct idec_rgb), "color");
    *status = 1;
    return;
  }
}
