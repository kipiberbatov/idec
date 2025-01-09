#include "idec_command_line.h"
#include "idec_string.h"

void idec_command_line_initialize_option_string(idec_command_line * option)
{
  option->index = 0;
  option->number_of_arguments = 0;
  option->minimal_number_of_arguments = 0;
  option->maximal_number_of_arguments = 1;
  option->scan = idec_string_string_scan_void;
  option->file_print = idec_string_file_print_void;
  option->destroy = NULL;
  option->type_size = 0;
}
