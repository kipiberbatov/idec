#include "idec_command_line.h"

static void
idec_command_line_initialize_option_no_arguments(idec_command_line * option)
{
  option->index = 0;
  option->number_of_arguments = 0;
  option->minimal_number_of_arguments = 0;
  option->maximal_number_of_arguments = 0;
  option->string_scan = NULL;
  option->file_print = NULL;
  option->set_default = NULL;
  option->destroy = NULL;
  option->type_size = 0;
}

void idec_command_line_set_option_no_arguments(
  idec_command_line * option, void * value,
  const char * name, const void * default_argument)
{
  idec_command_line_initialize_option_no_arguments(option);
  option->name = name;
  option->default_argument = default_argument;
  option->arguments = value;
}
