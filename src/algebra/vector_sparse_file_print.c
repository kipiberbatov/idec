#include <errno.h>
#include <string.h>
#include "vector_sparse_private.h"

void vector_sparse_file_print(
  FILE * out, const vector_sparse * a, const char * format)
{
  if (!strcmp(format, "--only-values"))
    vector_sparse_file_print_only_values(out, a);
  else if (!strcmp(format, "--raw"))
    vector_sparse_file_print_raw(out, a);
  else if (!strcmp(format, "--annotated"))
    vector_sparse_file_print_annotated(out, a);
  else if (!strcmp(format, "--curly"))
    vector_sparse_file_print_curly(out, a);
  else if (!strcmp(format, "--mathematica-sparse"))
    vector_sparse_file_print_mathematica_sparse(out, a);
  else
  {
    errno = EINVAL;
    fprintf(stderr,
      "vector_sparse_file_print - format %s is not supported\n", format);
  }
}
