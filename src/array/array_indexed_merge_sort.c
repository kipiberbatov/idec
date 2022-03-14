#include <stdlib.h>
#include <stdio.h>
#include "array_indexed.h"

static void update(int * b_positions, int * b_values, int * i, int * k,
                   const int * a_positions, const int * a_values)
{
  b_positions[*k] = a_positions[*i];
  b_values[*k] = a_values[*i];
  ++*i;
  ++*k;
}

static void array_indexed_merge_sort_ordered(
  array_indexed * a, array_indexed * b, int begin, int middle, int end)
{
  int i = begin, j = middle + 1, k = begin;
  int * a_positions, * a_values, * b_positions, * b_values;
  a_positions = a->positions, a_values = a->values;
  b_positions = b->positions, b_values = b->values;
  while (i <= middle && j <= end)
  {
    if (a_values[i] <= a_values[j])
      update(b_positions, b_values, &i, &k, a_positions, a_values);
    else
      update(b_positions, b_values, &j, &k, a_positions, a_values);
  }
  if (i == middle + 1)
    while (j <= end)
      update(b_positions, b_values, &j, &k, a_positions, a_values);
  else
    while (i <= middle)
      update(b_positions, b_values, &i, &k, a_positions, a_values);
  for (k = begin; k <= end; ++k)
  {
    a_positions[k] = b_positions[k];
    a_values[k] = b_values[k];
  }
}

static void array_indexed_merge_sort_loc(
  array_indexed * a, array_indexed * b, int begin, int end)
{
  int middle = (begin + end) / 2;
  if (begin == end)
    return;
  array_indexed_merge_sort_loc(a, b, begin, middle);
  array_indexed_merge_sort_loc(a, b, middle + 1, end);
  array_indexed_merge_sort_ordered(a, b, begin, middle, end);
}

void array_indexed_merge_sort(array_indexed * a, int n)
{
  int * b_positions, * b_values;
  array_indexed b;
  
  b_positions = (int *) malloc(n * sizeof(int));
  if (b_positions == NULL)
  {
    fputs("Allocation error\n", stderr);
    goto end;
  }
  b.positions = b_positions;
  
  b_values = (int *) malloc(n * sizeof(int));
  if (b_values == NULL)
  {
    fputs("Allocation error\n", stderr);
    goto clean_b_positions;
  }
  b.values = b_values;
  
  array_indexed_merge_sort_loc(a, &b, 0, n - 1);
  
// clean_b_values:
  free(b_values);
clean_b_positions:
  free(b_positions);
end:
  return;
}
