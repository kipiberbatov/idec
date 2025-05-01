#include <stdio.h>

#include "color.h"

void idec_error_message_position_in_code(const char * file, int line)
{
  color_error_position(file, line);
}
