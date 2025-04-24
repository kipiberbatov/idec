#ifndef _double_array_h
#define _double_array_h

#include <stdio.h>

struct jagged1;

double * double_array_file_scan(FILE * in, int n, const char * format);

double * double_array_file_scan_by_name(
  const char * name, int n, const char * format);

void double_array_file_print(
  FILE * out, int n, const double * a, const char * format);

void double_array_assign_identity(double * a, int n);

void double_array_assign_constant(double * a, int n, double c);

void double_array_add_to(double * a, int d, const double * b);

void double_array_add_sparse_to(
  double * f, const struct jagged1 * indices, const double * g);

void double_array_negate(double * b, int n, const double * a);

void double_array_subtract(double * a, int n, const double * b);

void double_array_multiply_with(double * a, int d, double lambda);

void double_array_pointwise_multiply(double * b, int n, const double * a);

void double_array_pointwise_divide(double * b, int n, const double * a);

void double_array_compress_to_sparse_array(
  double * b, const struct jagged1 * positions, const double * a);

void double_array_assemble_from_sparse_array(
  double * b, const struct jagged1 * positions, const double * a);

double double_array_dot_product(int d, const double * a, const double * b);

double double_array_norm(int d, const double * a);

void double_array_normalize(double * res, int d, const double * a);

double double_array_lebesgue_norm(double p, int d, const double * a);

void double_array_difference(
  double * res, int d, const double * a, const double * b);

double double_array_min(int n, const double * a);

double double_array_max(int n, const double * a);

double double_array_absolute_min(int n, const double * a);

double double_array_absolute_max(int n, const double * a);

double double_array_total_sum(int n, const double * a);

double double_array_norm_uniform(int n, const double * a);

double double_array_pair_norm_uniform_relative(
  int n, const double * a, const double * b);

#endif /* _double_array_h */
