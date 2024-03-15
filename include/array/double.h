#ifndef DOUBLE_H
#define DOUBLE_H

#include <stdio.h>

/*********************************** double ***********************************/
double double_fscan(FILE * in);

double double_sscan(const char * s);

/******************************** double_array ********************************/
double * double_array_fscan(FILE * in, int n, const char * format);

double * double_array_fscan_by_name(
  const char * name, int n, const char * format);

void double_array_fprint(
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

/******************************* double_matrix ********************************/
double * double_matrix_fscan(FILE * in, int m, int n, const char * format);

double * double_matrix_fscan_by_name(
  const char * name, int m, int n, const char * format);

void double_matrix_fprint(
  FILE * out, int m, int n, const double * a, const char * format);

/******************************* double_array2 ********************************/
void double_array2_free(double ** arr, int n);

double ** double_array2_fscan(
  FILE * in, int a0, const int * a1, const char * format);

double ** double_array2_fscan_by_name(
  const char * name, int a0, const int * a1, const char * format);

#endif /* DOUBLE_H */
