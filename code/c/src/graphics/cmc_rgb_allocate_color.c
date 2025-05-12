#include <stdio.h>
#include <stdlib.h>

#include "color.h"
#include "cmc_error_message.h"
#include "cmc_rgb.h"

void cmc_rgb_allocate_color(struct cmc_rgb ** color, int * status)
{
  *color = (struct cmc_rgb *) malloc(sizeof(struct cmc_rgb));
  if (*color == NULL)
  {
    color_error_position(__FILE__, __LINE__);
    cmc_error_message_malloc(sizeof(struct cmc_rgb), "color");
    *status = 1;
    return;
  }
}
