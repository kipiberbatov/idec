#include <errno.h>
#include "jagged.h"
#include "matrix_sparse.h"

int main(int argc, char * argv[])
{
  char * a_format, * a_name, * rows_format, * rows_name, * out_format;
  FILE * rows_file;
  matrix_sparse * a, * b;
  jagged1 * rows;
  
  if (argc != 6)
  {
    errno = EINVAL;
    fputs("main - the number of command-line arguments must be 6\n", stderr);
    goto end;
  }
  
  /* a = m_laplacian_0 */
  a_name = argv[1];
  a_format = argv[2];
  a = matrix_sparse_fscan_by_name(a_name, a_format);
  if (errno)
  {
    fputs("main - cannot scan matrix a\n", stderr);
    goto end;
  }
  
  /* rows = m_bd_nodes */
  rows_name = argv[3];
  rows_format = argv[4];
  
  rows_file = fopen(rows_name, "r");
  rows = jagged1_fscan(rows_file, rows_format);
  if (errno)
  {
    fputs("main - cannot scan rows\n", stderr);
    fclose(rows_file);
    goto a_free;
  }
  fclose(rows_file);
  
  b = matrix_sparse_remove_symmetric(a, rows);
  if (errno)
  {
    fputs("main - cannot calculate restricted matrix b\n", stderr);
    goto rows_free;
  }
  
  out_format = argv[5];
  matrix_sparse_fprint(stdout, b, out_format);

  matrix_sparse_free(b);
rows_free:
  jagged1_free(rows);
a_free:
  matrix_sparse_free(a);
end:
  return errno;
}
