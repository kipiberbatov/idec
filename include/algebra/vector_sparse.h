#ifndef VEC_SPARSE_H
#define VEC_SPARSE_H

#include <stdio.h>
//#include "cs.h"

// typedef struct vector_sparse
// {
//   int nzmax;
//   int n;
//   int * p;
//   double * x;
// } vector_sparse;

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

vector_sparse * vector_sparse_fscan(FILE * in, const char * format);

vector_sparse * vector_sparse_fscan_by_name(
  const char * name, const char * format);

void vector_sparse_fprint(
  FILE * out, const vector_sparse * a, const char * format);

void vector_sparse_rearange(vector_sparse * b);

/**************************** vector_sparse_array *****************************/
void vector_sparse_array_free(vector_sparse ** arr, int a0);

vector_sparse ** vector_sparse_array_fscan(
  FILE * in, int a0, const char * format);

vector_sparse ** vector_sparse_array_fscan_by_name(
  const char * name, int a0, const char * format);

void vector_sparse_array_fprint(
  FILE * out, int a0, vector_sparse ** arr, const char * format);

/**************************** vector_sparse_array2 ****************************/
void vector_sparse_array2_free(vector_sparse *** arr, int a0, const int * a1);

vector_sparse *** vector_sparse_array2_fscan(
  FILE * in, int a0, int * a1, const char * format);

vector_sparse *** vector_sparse_array2_fscan_by_name(
  const char * name, int a0, const int * a1, const char * format);

void vector_sparse_array2_fprint(
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

#endif /* VEC_SPARSE_H */
