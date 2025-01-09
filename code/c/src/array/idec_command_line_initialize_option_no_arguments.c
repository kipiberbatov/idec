#include "idec_command_line.h"

void
idec_command_line_initialize_option_no_arguments(idec_command_line * option)
{
  option->index = 0;
  option->number_of_arguments = 0;
  option->minimal_number_of_arguments = 0;
  option->maximal_number_of_arguments = 0;
  option->scan = NULL;
  option->file_print = NULL;
  option->destroy = NULL;
  option->type_size = 0;
}
