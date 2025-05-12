#include "cmc_command_line.h"
#include "double.h"

static void
cmc_command_line_initialize_option_double(cmc_command_line * option)
{
  option->index = 0;
  option->number_of_arguments = 0;
  option->minimal_number_of_arguments = 0;
  option->maximal_number_of_arguments = 1;
  option->string_scan = double_string_scan_void;
  option->file_print = double_file_print_void;
  option->set_default = double_set_default_void;
  option->destroy = NULL;
  option->type_size = 0;
}

void cmc_command_line_set_option_double(
  cmc_command_line * option, double * value, const char * name,
  const double * default_argument)
{
  cmc_command_line_initialize_option_double(option);
  option->name = name;
  option->default_argument = (const void *) default_argument;
  if (default_argument == NULL)
    option->minimal_number_of_arguments = 1;
  option->arguments = (void *) value;
}
