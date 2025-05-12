#include <limits.h>

#include "cmc_command_line.h"
#include "cmc_string.h"

static void
cmc_command_line_initialize_option_string_array(cmc_command_line * option)
{
  option->index = 0;
  option->number_of_arguments = 0;
  option->minimal_number_of_arguments = 0;
  option->maximal_number_of_arguments = INT_MAX;
  option->string_scan = cmc_string_string_scan_void;
  option->file_print = cmc_string_file_print_void;
  option->set_default = NULL;
  option->destroy = NULL;
  option->default_argument = NULL;
  option->arguments = NULL;
  option->type_size = sizeof(char *);
}

void cmc_command_line_set_option_string_array(
  cmc_command_line * option, const char * name)
{
  cmc_command_line_initialize_option_string_array(option);
  option->name = name;
}
