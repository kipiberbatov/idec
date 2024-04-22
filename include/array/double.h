#ifndef _double_h
#define _double_h

#include <stdio.h>

/*********************************** double ***********************************/
double double_file_scan(FILE * in);

double double_string_scan(const char * s);

int double_equal(double x, double y, double tolerance);

/******************************** double_array ********************************/
double * double_array_file_scan(FILE * in, int n, const char * format);

double * double_array_file_scan_by_name(
  const char * name, int n, const char * format);

void double_array_file_print(
  FILE * out, int n, const double * a, const char * format);

void double_array_assign_identity(double * a, int n);

void double_array_assign_constant(double * a, int n, double c);

void double_array_add_to(double * a, int d, const double * b);

void double_array_multiply_with(double * a, int d, double lambda);

void double_array_substitute(
  double * b, int n, const double * a, const int * position);

void double_array_substitute_inverse(
  double * b, int n, const double * a, const int * position);

double double_array_dot_product(int d, const double * a, const double * b);

double double_array_norm(int d, const double * a);

void double_array_normalise(double * res, int d, const double * a);

void double_array_difference(
  double * res, int d, const double * a, const double * b);

double double_array_min(int n, const double * a);

double double_array_max(int n, const double * a);

double double_array_norm_uniform(int n, const double * a);

double double_array_pair_norm_uniform_relative(
  int n, const double * a, const double * b);

typedef struct double_array_sequence_dynamic
{
  int capacity;
  int length;
  int dimension;
  double ** values;
} double_array_sequence_dynamic;

void double_array_sequence_dynamic_free(double_array_sequence_dynamic * a);

void double_array_sequence_dynamic_file_print(
  FILE * out,
  const double_array_sequence_dynamic * a);

double_array_sequence_dynamic *
double_array_sequence_dynamic_file_scan(FILE * in);

double_array_sequence_dynamic *
double_array_sequence_dynamic_file_scan_by_name(const char * name);

void double_array_sequence_dynamic_resize(double_array_sequence_dynamic * a);

double_array_sequence_dynamic * double_array_sequence_dynamic_initialize(int n);

/******************************* double_matrix ********************************/
double * double_matrix_file_scan(FILE * in, int m, int n, const char * format);

double * double_matrix_file_scan_by_name(
  const char * name, int m, int n, const char * format);

void double_matrix_file_print(
  FILE * out, int m, int n, const double * a, const char * format);

/******************************* double_array2 ********************************/
void double_array2_free(double ** arr, int n);

double ** double_array2_file_scan(
  FILE * in, int a0, const int * a1, const char * format);

double ** double_array2_file_scan_by_name(
  const char * name, int a0, const int * a1, const char * format);

#endif /* _double_h */
