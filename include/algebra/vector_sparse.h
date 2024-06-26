#ifndef _vector_sparse_h
#define _vector_sparse_h

#include <stdio.h>

typedef struct vector_sparse
{
  int length;
  int nonzero_max;
  int * positions;
  double * values;
} vector_sparse;

double vector_sparse_part(const vector_sparse * a, int i);

/* can be added */
/*
vector_sparse * vector_sparse_linear_combination(
  const vector_sparse * a, const vector_sparse * b, double alpha, double beta);
vector_sparse * vector_sparse_add(
  const vector_sparse * a, const vector_sparse * b);
double vector_sparse_dot_product(
  const vector_sparse * a, const vector_sparse * b);
*/

/******************************** vector_sparse *******************************/
void vector_sparse_free(vector_sparse * a);

vector_sparse * vector_sparse_file_scan(FILE * in, const char * format);

vector_sparse * vector_sparse_file_scan_by_name(
  const char * name, const char * format);

void vector_sparse_file_print(
  FILE * out, const vector_sparse * a, const char * format);

void vector_sparse_rearrange(vector_sparse * b);

/**************************** vector_sparse_array *****************************/
void vector_sparse_array_free(vector_sparse ** arr, int a0);

vector_sparse ** vector_sparse_array_file_scan(
  FILE * in, int a0, const char * format);

vector_sparse ** vector_sparse_array_file_scan_by_name(
  const char * name, int a0, const char * format);

void vector_sparse_array_file_print(
  FILE * out, int a0, vector_sparse ** arr, const char * format);

/**************************** vector_sparse_array2 ****************************/
void vector_sparse_array2_free(vector_sparse *** arr, int a0, const int * a1);

vector_sparse *** vector_sparse_array2_file_scan(
  FILE * in, int a0, const int * a1, const char * format);

vector_sparse *** vector_sparse_array2_file_scan_by_name(
  const char * name, int a0, const int * a1, const char * format);

void vector_sparse_array2_file_print(
  FILE * out, int a0, const int * a1,
  vector_sparse *** arr, const char * format);

/*************************** vector_sparse_algebra ****************************/
// vector_sparse * vector_sparse_add(const vector_sparse * a, const vector_sparse * b);
//
// /* a := -a */
// void vector_sparse_negate(vector_sparse * a);
//
// vector_sparse * vector_sparse_subtract(const vector_sparse * a, const vector_sparse * b);
//
// vector_sparse * vector_sparse_scalar_multiply(const vector_sparse * a, double alpha);
//
// /* a *= alpha */
// void vector_sparse_scalar_multiply_with(vector_sparse * a, int alpha);
//
// double vector_sparse_dot_product(const vector_sparse * a, const vector_sparse * b);
//
// vector_sparse * vector_sparse_matrix_times_vector(const cs * a, const vector_sparse * b);

#endif /* _vector_sparse_h */
