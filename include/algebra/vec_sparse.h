#ifndef VEC_SPARSE_H
#define VEC_SPARSE_H

#include <stdio.h>
#include "cs.h"

typedef struct vec_sparse
{
  int nzmax;
  int n;
  int * p;
  double * x;
} vec_sparse;

/***************************** vec_sparse_algebra *****************************/
vec_sparse * vec_sparse_add(const vec_sparse * a, const vec_sparse * b);

/* a := -a */
void vec_sparse_negate(vec_sparse * a);

vec_sparse * vec_sparse_subtract(const vec_sparse * a, const vec_sparse * b);

vec_sparse * vec_sparse_scalar_multiply(const vec_sparse * a, double alpha);

/* a *= alpha */
void vec_sparse_scalar_multiply_with(vec_sparse * a, int alpha);

double vec_sparse_dot_product(const vec_sparse * a, const vec_sparse * b);

vec_sparse * vec_sparse_matrix_times_vector(const cs * a, const vec_sparse * b);

/****************************** vec_sparse_set *******************************/
void vec_sparse_set(
  vec_sparse * a, int a_nzmax, int a_n, int * a_p, double * a_x);

/****************************** vec_sparse_new *******************************/
vec_sparse * vec_sparse_new(int a_nzmax, int a_n, int * a_p, double * a_x);

vec_sparse ** vec_sparse_new_array(
  int n, int * a_nzmax, int * a_n, int ** a_p, double ** a_x);

/****************************** vec_sparse_free *******************************/
void vec_sparse_free(vec_sparse * a);
void vec_sparse_free_array(vec_sparse ** arr, int a0);
void vec_sparse_free_array2(vec_sparse *** arr, int a0, const int * a1);

/***************************** vec_sparse_fprint ******************************/
void vec_sparse_fprint(FILE * out, const vec_sparse * a);
void vec_sparse_fprint_array(FILE * out, int a0, vec_sparse ** arr);
void vec_sparse_fprint_array2(FILE * out, int a0, const int * a1,
                              vec_sparse *** arr);

/****************************** vec_sparse_fscan ******************************/
vec_sparse * vec_sparse_fscan(FILE * in);
vec_sparse ** vec_sparse_fscan_array(FILE * in, int a0);
vec_sparse *** vec_sparse_fscan_array2(FILE * in, int a0, int * a1);

#endif /* VEC_SPARSE_H */
