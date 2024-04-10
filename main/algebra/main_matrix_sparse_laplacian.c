#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include "matrix_sparse.h"

int main(int argc, char * argv[])
{
  int d;
  char * format;
  /* char * list; */
  matrix_sparse ** a, ** b;
  FILE * in, * out;
  
  out = stdout;
  in = stdin;
  format = argv[1];
  /* list = argv[2]; */
  d = atoi(argv[3]);
  
  a = matrix_sparse_array_fscan(in, d, "--raw");
  if (errno)
  {
    perror("Unsuccessful scanning of first operator");
    goto end;
  }
  
  b = matrix_sparse_array_fscan(in, d, "--raw");
  if (errno)
  {
    perror("Unsuccessful scanning of second operator");
    goto a_free;
  }
  
  matrix_sparse_laplacian_fprint(out, d, a, b, format);
  if (errno)
  {
    perror("Unsuccessful calculation or printing of Lalplacian");
    goto b_free;
  }

b_free:
  matrix_sparse_array_free(b, d);
a_free:
  matrix_sparse_array_free(a, d);
end:
  return errno;
}
