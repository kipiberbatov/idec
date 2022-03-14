#include <stdio.h>
#include <stdlib.h>
#include "double.h"
#include "int.h"
#include "vec_sparse.h"

// static int int_fscan(FILE * in)
// {
//   int a;
//
//   fscanf(in, "%d", &a);
//   return a;
// }
//
// static int * int_array_fscan(FILE * in, int n)
// {
//   int i;
//   int * a;
//
//   a = (int *) malloc(n * sizeof(int));
//   /* NULL pointer check */
//   for (i = 0; i < n; ++i)
//   {
//     fscanf(in, "%d", a + i);
//     /* successfull scanning check */
//   }
//   return a;
// }

// static double * double_array_fscan(FILE * in, int n)
// {
//   int i;
//   double * a;
//
//   a = (double *) malloc(n * sizeof(double));
//   /* NULL pointer check */
//   for (i = 0; i < n; ++i)
//   {
//     fscanf(in, "%lf", a + i);
//     /* successfull scanning check */
//   }
//   return a;
// }

vec_sparse * vec_sparse_fscan(FILE * in)
{
  int a_n, a_nzmax;
  int * a_p;
  double * a_x;
  vec_sparse * a;
  
  a = (vec_sparse *) malloc(sizeof(vec_sparse));
  /* NULL pointer check */
  a_nzmax = int_fscan(in);
  a_n = int_fscan(in);
  a_p = int_fscan_array(in, a_nzmax);
  /* NULL pointer check */
  a_x = double_fscan_array(in, a_nzmax);
  /* NULL pointer check */
  vec_sparse_set(a, a_nzmax, a_n, a_p, a_x);
  return a;
}

vec_sparse ** vec_sparse_fscan_array(FILE * in, int a0)
{
  int i;
  vec_sparse ** arr;
  
  arr = (vec_sparse **) malloc(a0 * sizeof(vec_sparse *));
  /* NULL pointer check */
  for (i = 0; i < a0; ++i)
  {
    arr[i] = vec_sparse_fscan(in);
    /* NULL pointer check */
  }
  return arr;
}

vec_sparse *** vec_sparse_fscan_array2(FILE * in, int a0, int * a1)
{
  int i;
  vec_sparse *** arr;
  
  arr = (vec_sparse ***) malloc(a0 * sizeof(vec_sparse **));
  /* NULL pointer check */
  for (i = 0; i < a0; ++i)
  {
    arr[i] = vec_sparse_fscan_array(in, a1[i]);
    /* NULL pointer check */
  }
  return arr;
}

#if 0
vec_sparse * vec_sparse_fscan_array(FILE * in, int a0)
{
  int i;
  vec_sparse * arr;
  
  arr = (vec_sparse *) malloc(a0 * sizeof(vec_sparse *));
  /* NULL pointer check */
  for (i = 0; i < a0; ++i)
  {
    arr + i = vec_sparse_fscan(in);
    /* NULL pointer check */
  }
  return arr;
}
#endif
