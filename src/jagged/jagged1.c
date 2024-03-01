#include <errno.h>
#include <stdlib.h>
#include "int.h"
#include "jagged.h"

int jagged1_total_sum(const jagged1 * arr)
{
  return int_array_total_sum(arr->a0, arr->a1);
}

/* finds the complement of arr with respect to {0, ..., n - 1} */
// jagged1 * jagged1_complement(int n, const jagged1 * arr)
// {
//   int i, j, ind;
//   jagged1 * res;
//
//   res = (jagged1 *) malloc(sizeof(jagged1));
//   if (errno)
//   {
//     perror("jagged1_complement : cannot allocate memory for res");
//     goto end;
//   }
//   res->a0 = n - arr->a0;
//   res->a1 = (int *) malloc(sizeof(int) * res->a0);
//   if (errno)
//   {
//     perror("jagged1_complement : cannot allocate memory for res->a1");
//     goto res_free;
//   }
//   ind = 0;
//   i = 0;
//   j = 0;
//   while (j < arr->a0)
//   {
//     if (i == arr->a1[j])
//     {
//       ++i;
//       ++j;
//     }
//     else
//     {
//       res->a1[ind] = i;
//       ++i;
//       ++ind;
//     }
//   }
//   while (i < n)
//   {
//     res->a1[ind] = i;
//     ++i;
//     ++ind;
//   }
//   return res;
//
//   /* cleaning if an error occurs */
// res_free:
//   free(res);
// end:
//   return NULL;
// }

jagged1 * jagged1_complement(int n, const jagged1 * arr)
{
  int i, ind;
  jagged1 * res;
  
  res = (jagged1 *) malloc(sizeof(jagged1));
  if (errno)
  {
    perror("jagged1_complement : cannot allocate memory for res");
    goto end;
  }
  
  res->a0 = n - arr->a0;
  
  res->a1 = (int *) malloc(sizeof(int) * res->a0);
  if (errno)
  {
    perror("jagged1_complement : cannot allocate memory for res->a1");
    goto res_free;
  }
  
  ind = 0;
  for (i = 0; i < n; ++i)
  {
    if (!jagged1_member(arr, i))
    {
      res->a1[ind] = i;
      ++ind;
    }
  }
  
  return res;
  
  /* cleaning if an error occurs */
res_free:
  free(res);
end:
  return NULL;
}

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
    if (arr_a1[i] < arr_a1[i + 1])
    {
      result_a1[ind] = arr_a1[i + 1];
      ++ind;
    }
  result->a1 = result_a1;
  
  return result;
}

int jagged1_position(const jagged1 * arr, int element)
{
  int arr_a0, i;
  int * arr_a1;
  
  arr_a0 = arr->a0;
  arr_a1 = arr->a1;
  for (i = 0; i < arr_a0; ++i)
    if (element == arr_a1[i])
      return i;
  return -1;
}

int jagged1_signature(const jagged1 * arr)
{
  int arr_a0, i, inversions, j;
  int * arr_a1;

  arr_a0 = arr->a0;
  arr_a1 = arr->a1;

  inversions = 0;
  for (i = 0; i < arr_a0 - 1; ++i)
    for (j = i + 1; j < arr_a0; ++j)
      if (arr_a1[i] > arr_a1[j])
        ++inversions;
  return ((inversions % 2 == 0) ? 1 : -1);
}

void jagged1_delete(jagged1 * result, const jagged1 * arr, int position)
{
  int i, result_a0;
  int * arr_a1, * result_a1;

  result_a0 = result->a0;
  result_a1 = result->a1;
  arr_a1 = arr->a1;
  for (i = 0; i < position; ++i)
    result_a1[i] = arr_a1[i];
  for (i = position; i < result_a0; ++i)
    result_a1[i] = arr_a1[i + 1];
}

int jagged1_member(const jagged1 * arr, int element)
{
  int arr_a0, i;
  int * arr_a1;

  arr_a0 = arr->a0;
  arr_a1 = arr->a1;

  for (i = 0; i < arr_a0; ++i)
    if (element == arr_a1[i])
      return 1;
  return 0;
}

int jagged1_intersection_count(const jagged1 * arr1, const jagged1 * arr2)
{
  int arr1_a0, i, res;
  int * arr1_a1;
  
  arr1_a0 = arr1->a0;
  arr1_a1 = arr1->a1;
  res = 0;
  for (i = 0; i < arr1_a0; ++i)
    res += jagged1_member(arr2, arr1_a1[i]);
  return res;
}

/* it is required that jagged1_intersection_count(arr1, arr2) == 1 */
/* otherwise, the function finds the first intersection */
int jagged1_intersection_unique(const jagged1 * arr1, const jagged1 * arr2)
{
  int arr1_a0, i;
  int * arr1_a1;

  arr1_a0 = arr1->a0;
  arr1_a1 = arr1->a1;

  for (i = 0; i < arr1_a0; ++i)
    if (jagged1_member(arr2, arr1_a1[i]))
      return arr1_a1[i];
  return -1;
}

void jagged1_intersection(
  jagged1 * res, const jagged1 * arr1, const jagged1 * arr2)
{
  int arr1_a0, i, ind;
  int * arr1_a1, * res_a1;
  
  arr1_a0 = arr1->a0;
  arr1_a1 = arr1->a1;
  res_a1 = res->a1;
  ind = 0;
  for (i = 0; i < arr1_a0; ++i)
  {
    if (jagged1_member(arr2, arr1_a1[i]))
    {
      res_a1[ind] = arr1_a1[i];
      ++ind;
    }
  }
  res->a0 = ind;
}

int jagged1_complement_simplicial(const jagged1 * cell_nodes,
                                  const jagged1 * hyperface_nodes)
{
  int cell_nodes_a0, i;
  int * cell_nodes_a1;

  cell_nodes_a0 = cell_nodes->a0;
  cell_nodes_a1 = cell_nodes->a1;
  for (i = 0; i < cell_nodes_a0; ++i)
    if(!jagged1_member(hyperface_nodes, cell_nodes_a1[i]))
      return cell_nodes_a1[i];
  return -1;
}

int jagged1_relative_sign(const jagged1 * cell_nodes,
                          const jagged1 * hyperface_nodes)
{
  int rest_node, rest_node_position, sign0, sign1, sign2;
  int hyperface_nodes_messed_a1[4];
  jagged1 hyperface_nodes_messed;

  rest_node = jagged1_complement_simplicial(cell_nodes, hyperface_nodes);
  rest_node_position = jagged1_position(cell_nodes, rest_node);
  hyperface_nodes_messed.a0 = hyperface_nodes->a0;
  hyperface_nodes_messed.a1 = hyperface_nodes_messed_a1;
  jagged1_delete(&hyperface_nodes_messed, cell_nodes, rest_node_position);
  sign0 = (rest_node_position % 2 == 0) ? 1 : -1;
  sign1 = jagged1_signature(&hyperface_nodes_messed);
  sign2 = jagged1_signature(hyperface_nodes);
  return sign0 * sign1 * sign2;
}
