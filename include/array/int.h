#ifndef INT_H
#define INT_H

#include <stdio.h>

/************************************ int *************************************/
int int_fscan(FILE * in);

int int_sscan(const char * s);

int int_power(int a, int n);

int int_factorial(int n);

int int_binomial(int n, int k);

void int_swap(int * a, int * b);

/********************************* int_array **********************************/
int * int_array_fscan(FILE * in, int n, const char * format);

void int_array_fprint(FILE * out, int n, const int * a, const char * format);

void int_array_assign_identity(int * a, int n);

void int_array_assign_constant(int * a, int n, int c);

void int_array_substitute(int * b, int n, const int * a, const int * k);

void int_array_substitute_inverse(
  int * b, int n, const int * a, const int * position);

void int_array_sum(int * c, int n, const int * a, const int * b);

void int_array_set_difference(
  int * b_bar, int p, const int * a, int q, const int * b);

int int_array_total_sum(int n, const int * a);

int int_array_total_product(int n, const int * a);

int int_array_member(int n, const int * a, int element);

int int_array_flatten_index(int d, const int * dimensions, const int * indices);

int int_array_positive(int n, const int * a);

void int_array_cartesian_product_next(int * a, int d, const int * n);

void int_array_combination_next(int * a, int m, int n);

int int_array_combination_index(int * comb, int m, int n);

void int_array_4_values_get(
  const int * a, int * x0, int * x1, int * x2, int * x3);

void int_array_4_values_set(int * a, int x0, int x1, int x2, int x3);

/********************************* int_array2 *********************************/
void int_array2_free(int ** arr, int a0);

#endif /* INT_H */
