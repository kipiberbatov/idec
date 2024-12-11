#ifndef _idec_error_message_h
#define _idec_error_message_h

#include <stddef.h>

void idec_error_message_malloc(size_t size, const char * name);
void idec_error_message_number_of_command_line_arguments_mismatch(
  int ARGC, int argc);

#endif /* _idec_error_message_h */
