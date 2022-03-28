#ifndef INT_PRIVATE_H
#define INT_PRIVATE_H

#include "int.h"

/****************************** int_array_fscan *******************************/
int * int_array_fscan_raw(FILE * in, int n);

#define INT_ARRAY_FSCAN_FORMAT_TOTAL 1

static const char * int_array_fscan_format[INT_ARRAY_FSCAN_FORMAT_TOTAL] =
  {
    "--raw"
  };

typedef int * (*int_array_fscan_function_type)(FILE *, int);

static const int_array_fscan_function_type
int_array_fscan_function[INT_ARRAY_FSCAN_FORMAT_TOTAL] =
  {
    int_array_fscan_raw
  };

/****************************** int_array_fprint ******************************/
void int_array_fprint_raw(FILE * out, int n, const int * a);
void int_array_fprint_curly(FILE * out, int n, const int * a);

#define INT_ARRAY_FPRINT_FORMAT_TOTAL 2

static const char * int_array_fprint_format[INT_ARRAY_FPRINT_FORMAT_TOTAL] =
  {
    "--raw",
    "--curly"
  };

typedef void (*int_array_fprint_function_type)(FILE *, int, const int *);

static const int_array_fprint_function_type
int_array_fprint_function[INT_ARRAY_FPRINT_FORMAT_TOTAL] =
  {
    int_array_fprint_raw,
    int_array_fprint_curly
  };

#endif /* INT_PRIVATE_H */
