#include <errno.h>
#include <stdlib.h>

#include "jagged.h"

static int int_compare(const void * a, const void * b)
{
  int res;
  int * a_int, * b_int;

  a_int = (int *) a;
  b_int = (int *) b;
  res = *a_int - *b_int;
  return res;
}

jagged1 * jagged1_delete_duplicates(jagged1 * arr)
{
  int arr_a0, i, ind, result_a0;
  int * arr_a1, * result_a1;
  jagged1 * result;

  arr_a0 = arr->a0;
  arr_a1 = arr->a1;
  result = (jagged1 *) malloc(sizeof(jagged1));
  /* NULL pointer check */
  result_a0 = 1;
  qsort(arr_a1, arr_a0, sizeof(int), int_compare);
  for (i = 0; i < arr_a0 - 1; ++i)
    if (arr_a1[i] < arr_a1[i + 1])
      ++result_a0;
  result->a0 = result_a0;
  
  result_a1 = (int *) malloc(result_a0 * sizeof(int));
  /* NULL pointer check */
  result_a1[0] = arr_a1[0];
  ind = 1;
  for (i = 0; i < arr_a0 - 1; ++i)
  {
    if (arr_a1[i] < arr_a1[i + 1])
    {
      result_a1[ind] = arr_a1[i + 1];
      ++ind;
    }
  }
  result->a1 = result_a1;
  
  return result;
}
