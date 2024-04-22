#include <errno.h>
#include <stdlib.h>
#include "double.h"
#include "matrix_sparse.h"

/* read a sparse matrix and vector from a file, multiply and print them */
int main(int argc, char * argv[])
{
  double * x, * y;
  matrix_sparse * a;
  FILE * a_in, * x_in;
  char * a_name, * x_name;
  int m, n;
  
  if (argc != 3)
  {
    fputs("There should be exactly 3 command line arguments!", stderr);
    return 1;
  }

  a_name = argv[1];
  a_in = fopen(a_name, "r");
  if (errno)
  {
    perror("Cannot open matrix file");
    goto end;
  }
  
  a = matrix_sparse_file_scan(a_in, "--raw");
  if (errno)
  {
    perror("Problem in matrix_sparse scanning");
    goto a_in_close;
  }

  m = a->rows;
  n = a->cols;
  
  x_name = argv[2];
  x_in = fopen(x_name, "r");
  if (errno)
  {
    perror("Problem in vector scanning");
    goto a_free;
  }
  
  x = double_array_file_scan(x_in, n, "--raw");
  if (errno)
  {
    perror("Problem in matrix_sparse scanning");
    goto x_in_close;
  }
  
  y = (double *) calloc(m, sizeof(double));
  if (errno)
  {
    perror("Problem in matrix_sparse scanning");
    goto x_free;
  }
  
  matrix_sparse_vector_multiply_add(y, a, x);
  double_array_file_print(stdout, m, y, "--raw");
  
  free(y);
x_free:
  free(x);
x_in_close:
  fclose(x_in);
a_free:
  free(a);
a_in_close:
  fclose(a_in);
end:
  return errno;
}
