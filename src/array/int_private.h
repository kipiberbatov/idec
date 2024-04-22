#ifndef INT_PRIVATE_H
#define INT_PRIVATE_H

#include "int.h"

/****************************** int_array_file_scan *******************************/
int * int_array_file_scan_raw(FILE * in, int n);

#define INT_ARRAY_file_scan_format_total 1

static const char * int_array_file_scan_format[INT_ARRAY_file_scan_format_total] =
  {
    "--raw"
  };

typedef int * (*int_array_file_scan_function_type)(FILE *, int);

static const int_array_file_scan_function_type
int_array_file_scan_function[INT_ARRAY_file_scan_format_total] =
  {
    int_array_file_scan_raw
  };

/****************************** int_array_file_print ******************************/
void int_array_file_print_raw(FILE * out, int n, const int * a);
void int_array_file_print_curly(FILE * out, int n, const int * a);

#define INT_ARRAY_file_print_format_total 2

static const char * int_array_file_print_format[INT_ARRAY_file_print_format_total] =
  {
    "--raw",
    "--curly"
  };

typedef void (*int_array_file_print_function_type)(FILE *, int, const int *);

static const int_array_file_print_function_type
int_array_file_print_function[INT_ARRAY_file_print_format_total] =
  {
    int_array_file_print_raw,
    int_array_file_print_curly
  };

#endif /* INT_PRIVATE_H */
