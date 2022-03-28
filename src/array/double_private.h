#ifndef DOUBLE_PRIVATE_H
#define DOUBLE_PRIVATE_H

#include "double.h"

/***************************** double_array_fscan *****************************/
double * double_array_fscan_raw(FILE * in, int n);

#define DOUBLE_ARRAY_FSCAN_FORMAT_TOTAL 1

static const char * double_array_fscan_format[DOUBLE_ARRAY_FSCAN_FORMAT_TOTAL] =
  {
    "--raw"
  };

typedef double * (*double_array_fscan_function_type)(FILE *, int);

static const double_array_fscan_function_type
double_array_fscan_function[DOUBLE_ARRAY_FSCAN_FORMAT_TOTAL] =
  {
    double_array_fscan_raw
  };

/**************************** double_array_fprint *****************************/
void double_array_fprint_raw(FILE * out, int n, const double * a);
void double_array_fprint_curly(FILE * out, int n, const double * a);

#define DOUBLE_ARRAY_FPRINT_FORMAT_TOTAL 2

static const char * double_array_fprint_format[DOUBLE_ARRAY_FPRINT_FORMAT_TOTAL] =
  {
    "--raw",
    "--curly"
  };

typedef void (*double_array_fprint_function_type)(FILE *, int, const double *);

static const double_array_fprint_function_type
double_array_fprint_function[DOUBLE_ARRAY_FPRINT_FORMAT_TOTAL] =
  {
    double_array_fprint_raw,
    double_array_fprint_curly
  };

/**************************** double_array2_fscan *****************************/
double ** double_array2_fscan_raw(FILE * in, int a0, const int * a1);

#define DOUBLE_ARRAY2_FSCAN_FORMAT_TOTAL 1

static const char *
double_array2_fscan_format[DOUBLE_ARRAY2_FSCAN_FORMAT_TOTAL] =
  {
    "--raw"
  };

typedef double ** (*double_array2_fscan_function_type)(
  FILE *, int, const int *);

static const double_array2_fscan_function_type
double_array2_fscan_function[DOUBLE_ARRAY2_FSCAN_FORMAT_TOTAL] =
  {
    double_array2_fscan_raw
  };

/**************************** double_matrix_fscan *****************************/
double * double_matrix_fscan_raw(FILE * in, int m, int n);

#define DOUBLE_MATRIX_FSCAN_FORMAT_TOTAL 1

static const char *
double_matrix_fscan_format[DOUBLE_MATRIX_FSCAN_FORMAT_TOTAL] =
  {
    "--raw"
  };

typedef double * (*double_matrix_fscan_function_type)(FILE *, int, int);

static const double_matrix_fscan_function_type
double_matrix_fscan_function[DOUBLE_ARRAY2_FSCAN_FORMAT_TOTAL] =
  {
    double_matrix_fscan_raw
  };

/**************************** double_matrix_fprint ****************************/
void double_matrix_fprint_raw(FILE * out, int m, int n, const double * a);
void double_matrix_fprint_curly(FILE * out, int m, int n, const double * a);

#define DOUBLE_MATRIX_FPRINT_FORMAT_TOTAL 2

static const char *
double_matrix_fprint_format[DOUBLE_MATRIX_FPRINT_FORMAT_TOTAL] =
  {
    "--raw",
    "--curly"
  };

typedef void (*double_matrix_fprint_function_type)(
  FILE *, int, int, const double *);

static const double_matrix_fprint_function_type
double_matrix_fprint_function[DOUBLE_MATRIX_FPRINT_FORMAT_TOTAL] =
  {
    double_matrix_fprint_raw,
    double_matrix_fprint_curly
  };

#endif /* DOUBLE_PRIVATE_H */
