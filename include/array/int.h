#ifndef INT_H
#define INT_H

#include <stdio.h>

/********************************** int_free **********************************/
void int_free_array2(int ** arr, int a0);

/********************************** int_fscan *********************************/
int int_fscan(FILE * in);
int * int_fscan_array(FILE * in, int n);

/********************************* int_fprint *********************************/
void int_fprint_array(FILE * out, int n, const int * a);
void int_fprint_array_annotated(
  FILE * out, int n, const int * a, const char * name);
void int_fprint_array_raw(FILE * out, int n, const int * a);

/********************************* int_array **********************************/
void int_array_assign_identity(int * a, int n);
void int_array_assign_integer(int * a, int n, int c);
void int_array_substitute(int * b, int n, const int * a, const int * k);
void int_array_substitute_inverse(
  int * z, int p_minus_q, const int * b_bar, const int * w);
void int_array_sum(int * c, int n, const int * a, const int * b);
void int_array_set_difference(
  int * b_bar, int p, const int * a, int q, const int * b);
int int_array_total_product(const int * a, int begin, int end);
int int_array_member(int n, const int * a, int element);
int int_array_flatten_index(int d, const int * dimensions, const int * indices);

/******************************* combinatorics ********************************/
// void int_swap(int * a, int * b);
//
// int int_power(int a, int b);
//
// void int_array_cartesian_product_next(int * a, int d, const int * n);
//
// int int_binomial(int a, int b);
// void int_array_combination_next(int * a, int m, int n);
// int int_array_combination_index(int * comb, int m, int n);
//
// int int_factorial(int n);

#endif /* INT_H */
