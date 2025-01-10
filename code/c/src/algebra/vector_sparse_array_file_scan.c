#include <stdlib.h>

#include "color.h"
#include "idec_error_message.h"
#include "vector_sparse.h"

vector_sparse ** vector_sparse_array_file_scan(
  FILE * in, int a0, const char * format)
{
  int i;
  vector_sparse ** arr;

  arr = (vector_sparse **) malloc(sizeof(vector_sparse *) * a0);
  if (arr == NULL)
  {
    color_error_position(__FILE__, __LINE__);
    idec_error_message_malloc(sizeof(vector_sparse *) * a0, "arr");
    return NULL;
  }
  for (i = 0; i < a0; ++i)
  {
    arr[i] = vector_sparse_file_scan(in, format);
    if (arr[i] == NULL)
    {
      color_error_position(__FILE__, __LINE__);
      fprintf(stderr, "cannot scan arr[%d] in format %s\n", i, format);
      vector_sparse_array_free(arr, i);
      return NULL;
    }
  }
  return arr;
}
