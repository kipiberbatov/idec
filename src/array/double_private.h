#ifndef DOUBLE_PRIVATE_H
#define DOUBLE_PRIVATE_H

#include "double.h"

/***************************** double_array_file_scan *****************************/
double * double_array_file_scan_raw(FILE * in, int n);

#define DOUBLE_ARRAY_file_scan_format_total 1

static const char * double_array_file_scan_format[DOUBLE_ARRAY_file_scan_format_total] =
  {
    "--raw"
  };

typedef double * (*double_array_file_scan_function_type)(FILE *, int);

static const double_array_file_scan_function_type
double_array_file_scan_function[DOUBLE_ARRAY_file_scan_format_total] =
  {
    double_array_file_scan_raw
  };

/**************************** double_array_file_print *****************************/
void double_array_file_print_raw(FILE * out, int n, const double * a);
void double_array_file_print_curly(FILE * out, int n, const double * a);

#define DOUBLE_ARRAY_file_print_format_total 2

static const char * double_array_file_print_format[DOUBLE_ARRAY_file_print_format_total] =
  {
    "--raw",
    "--curly"
  };

typedef void (*double_array_file_print_function_type)(FILE *, int, const double *);

static const double_array_file_print_function_type
double_array_file_print_function[DOUBLE_ARRAY_file_print_format_total] =
  {
    double_array_file_print_raw,
    double_array_file_print_curly
  };

/**************************** double_array2_file_scan *****************************/
double ** double_array2_file_scan_raw(FILE * in, int a0, const int * a1);

#define DOUBLE_ARRAY2_file_scan_format_total 1

static const char *
double_array2_file_scan_format[DOUBLE_ARRAY2_file_scan_format_total] =
  {
    "--raw"
  };

typedef double ** (*double_array2_file_scan_function_type)(
  FILE *, int, const int *);

static const double_array2_file_scan_function_type
double_array2_file_scan_function[DOUBLE_ARRAY2_file_scan_format_total] =
  {
    double_array2_file_scan_raw
  };

/**************************** double_matrix_file_scan *****************************/
double * double_matrix_file_scan_raw(FILE * in, int m, int n);

#define DOUBLE_MATRIX_file_scan_format_total 1

static const char *
double_matrix_file_scan_format[DOUBLE_MATRIX_file_scan_format_total] =
  {
    "--raw"
  };

typedef double * (*double_matrix_file_scan_function_type)(FILE *, int, int);

static const double_matrix_file_scan_function_type
double_matrix_file_scan_function[DOUBLE_ARRAY2_file_scan_format_total] =
  {
    double_matrix_file_scan_raw
  };

/**************************** double_matrix_file_print ****************************/
void double_matrix_file_print_raw(FILE * out, int m, int n, const double * a);
void double_matrix_file_print_curly(FILE * out, int m, int n, const double * a);

#define DOUBLE_MATRIX_file_print_format_total 2

static const char *
double_matrix_file_print_format[DOUBLE_MATRIX_file_print_format_total] =
  {
    "--raw",
    "--curly"
  };

typedef void (*double_matrix_file_print_function_type)(
  FILE *, int, int, const double *);

static const double_matrix_file_print_function_type
double_matrix_file_print_function[DOUBLE_MATRIX_file_print_format_total] =
  {
    double_matrix_file_print_raw,
    double_matrix_file_print_curly
  };

#endif /* DOUBLE_PRIVATE_H */
