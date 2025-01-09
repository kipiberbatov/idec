#include "double.h"
#include "idec_command_line.h"

void idec_command_line_initialize_option_double(idec_command_line * option)
{
  option->index = 0;
  option->number_of_arguments = 0;
  option->minimal_number_of_arguments = 0;
  option->maximal_number_of_arguments = 1;
  option->scan = double_string_scan_void;
  option->file_print = double_file_print_void;
  option->destroy = NULL;
  option->type_size = 0;
}
