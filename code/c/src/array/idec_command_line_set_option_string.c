#include "idec_command_line.h"
#include "idec_string.h"

static void
idec_command_line_initialize_option_string(idec_command_line * option)
{
  option->index = 0;
  option->number_of_arguments = 0;
  option->minimal_number_of_arguments = 0;
  option->maximal_number_of_arguments = 1;
  option->string_scan = idec_string_string_scan_void;
  option->file_print = idec_string_file_print_void;
  option->set_default = idec_string_set_default_void;
  option->destroy = NULL;
  option->type_size = 0;
}

void idec_command_line_set_option_string(
  idec_command_line * option, char ** value, const char * name,
  const char * default_argument)
{
  idec_command_line_initialize_option_string(option);
  option->name = name;
  option->default_argument = (const void *) default_argument;
  if (default_argument == NULL)
    option->minimal_number_of_arguments = 1;
  option->arguments = (void *) value;
}
