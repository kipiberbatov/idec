#include "cmc_command_line.h"
#include "int.h"

static void cmc_command_line_initialize_option_int(cmc_command_line * option)
{
  option->index = 0;
  option->number_of_arguments = 0;
  option->minimal_number_of_arguments = 0;
  option->maximal_number_of_arguments = 1;
  option->string_scan = int_string_scan_void;
  option->file_print = int_file_print_void;
  option->set_default = int_set_default_void;
  option->destroy = NULL;
  option->type_size = 0;
}

void cmc_command_line_set_option_int(
  cmc_command_line * option, int * value, const char * name,
  const int * default_argument)
{
  cmc_command_line_initialize_option_int(option);
  option->name = name;
  option->default_argument = (const void *) default_argument;
  if (default_argument == NULL)
    option->minimal_number_of_arguments = 1;
  option->arguments = (void *) value;
}
