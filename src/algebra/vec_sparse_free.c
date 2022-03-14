#include <stdlib.h>
#include "vec_sparse.h"

// static void vec_sparse_free_cells(vec_sparse * a)
// {
//   free(a->x);
//   free(a->p);
// }
//
// void vec_sparse_free(vec_sparse * a)
// {
//   vec_sparse_free_cells(a);
//   free(a);
// }
//
// static void vec_sparse_free_array_cells(vec_sparse * arr, int a0)
// {
//   int i;
//
//   for (i = 0; i < n; ++i)
//     vec_sparse_free_cells(arr + i);
// }
//
// void vec_sparse_free_array(vec_sparse * arr, int a0)
// {
//   vec_sparse_free_array_cells(arr, a0);
//   free(arr);
// }
//
// static void vec_sparse_free_array2_cells(vec_sparse * arr, int a0, int * a1)
// {
//   int i, ind;
//
//   ind = 0;
//   for (i = 0; i < n; ++i)
//   {
//     vec_sparse_free_array(arr + ind, a1[i]);
//     ind += a1[i];
//   }
// }
//
// void vec_sparse_free_array2(vec_sparse * arr, int a0, const int * a1)
// {
//   vec_sparse_free_array2_cells(arr, a0, a1);
//   free(arr);
// }

// void vec_sparse_free_array2(vec_sparse ** arr, int a0, const int * a1)
// {
//   int i;
//
//   for (i = a0 - 1; i >= 0; --i)
//     vec_sparse_free_array(arr[i], a1[i]);
//   free(arr);
// }

void vec_sparse_free(vec_sparse * a)
{
  free(a->x);
  free(a->p);
  free(a);
}

void vec_sparse_free_array(vec_sparse ** arr, int a0)
{
  int i;

  for (i = a0 - 1; i >= 0; --i)
    vec_sparse_free(arr[i]);
  free(arr);
}

void vec_sparse_free_array2(vec_sparse *** arr, int a0, const int * a1)
{
  int i;

  for (i = a0 - 1; i >= 0; --i)
    vec_sparse_free_array(arr[i], a1[i]);
  free(arr);
}
