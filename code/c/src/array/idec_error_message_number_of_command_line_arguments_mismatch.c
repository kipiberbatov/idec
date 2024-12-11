#include <stdio.h>

#include "idec_error_message.h"

void idec_error_message_number_of_command_line_arguments_mismatch(
  int ARGC, int argc)
{
  fprintf(stderr,
    "the number of command-line arguments must be %d; instead it is %d\n",
    ARGC, argc);
}
