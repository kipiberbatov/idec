#ifndef _idec_error_message_h
#define _idec_error_message_h

#include <stddef.h>

void idec_error_message_position_in_code(const char * file, int line);
void idec_error_message_memory_allocate(const char * name);
void idec_error_message_cannot_calculate(const char * name);
void idec_error_message_malloc(size_t size, const char * name);
void idec_error_message_number_of_command_line_arguments_mismatch(
  int ARGC, int argc);

#endif /* _idec_error_message_h */
