#include <errno.h>
#include "vector_sparse_private.h"

void vector_sparse_file_print_curly(FILE * out, const vector_sparse * a)
{
  int a_length, i;

  a_length = a->length;
  fputc('{', out);
  for (i = 0; i < a_length - 1; ++i)
  {
    fprintf(out, "%g,", vector_sparse_part(a, i));
  }
  fprintf(out, "%g}\n", vector_sparse_part(a, i));
}
