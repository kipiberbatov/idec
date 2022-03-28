#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include "matrix_sparse.h"

static void matrix_sparse_fprint_fscan(FILE * out, FILE * in, char * format)
{
  matrix_sparse * a;
  
  a = matrix_sparse_fscan(in, "--raw");
  if (errno)
  {
    perror("Unsuccessful matrix scanning during matrix printing calculation");
    goto a_free;
  }
  matrix_sparse_fprint(out, a, format);
  if (errno)
  {
    perror("Unsuccessful matrix printing");
    goto a_free;
  }
a_free:
  free(a);
}

static void matrix_sparse_array_fprint_fscan(
  FILE * out, FILE * in, char * format, int d)
{
  int p;
  
  for (p = 0; p < d; ++p)
  {
    matrix_sparse_fprint_fscan(out, in, format);
    if (errno)
    {
      fprintf(stderr, "During the printing of the %d-th matrix", p);
      perror("");
    }
    if (p < d - 1)
      fputc('\n', out);
  }
}

int main(int argc, char * argv[])
{
  char * format, * list;
  int d;
  
  format = argv[1];
  if (argc == 4)
  {
    list = argv[2];
    if (!strcmp(list, "list"))
    {
      errno = EINVAL;
      perror(list);
      return errno;
    }
    d = atoi(argv[3]);
    matrix_sparse_array_fprint_fscan(stdout, stdin, format, d);
    return 0;
  }
  matrix_sparse_fprint_fscan(stdout, stdin, format);
  return 0;
}
