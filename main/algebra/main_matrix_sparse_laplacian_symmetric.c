#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include "double.h"
#include "int.h"
#include "matrix_sparse.h"

int main(int argc, char * argv[])
{
  char * m_inner_format, * m_inner_name, * m_laplacian_format,
       * m_laplacian_name, * out_format;
  int d, p;
  int * m_cn;
  double ** m_inner;
  matrix_sparse ** m_laplacian;
  FILE * m_laplacian_file, * m_inner_file;
  
  if (argc != 7)
  {
    fputs("main - the number of command-line arguments must be 7\n", stderr);
    goto end;
  }
  
  d = int_sscan(argv[1]);
  if (errno)
  {
    fputs("main - cannot scan d\n", stderr);
    goto end;
  }
  
  m_laplacian_name = argv[2];
  m_laplacian_format = argv[3];
  // m_laplacian = matrix_sparse_array_fscan_by_name(m_laplacian_name, d + 1,
  //                                                 m_laplacian_format);
  m_laplacian_file = fopen(m_laplacian_name, "r");
  if (errno)
  {
    fputs("main - cannot open file containing m_laplacian\n", stderr);
    goto end;
  }
  m_laplacian = matrix_sparse_array_fscan(
    m_laplacian_file,
    d + 1,
    m_laplacian_format
  );
  // matrix_sparse_array_fprint(stderr, d + 1, m_laplacian, "--raw");
  if (errno)
  {
    fputs("main - cannot scan for m_laplacian\n", stderr);
    goto m_laplacian_file_close;
  }
  
  m_cn = (int *) malloc(sizeof(int) * (d + 1));
  if (errno)
  {
    fputs("main - cannot allocate memmory for m_cn\n", stderr);
    goto m_laplacian_free;
  }
  for (p = 0; p <= d; ++p)
    m_cn[p] = m_laplacian[p]->cols;
  
  m_inner_name = argv[4];
  m_inner_format = argv[5];
  m_inner_file = fopen(m_inner_name, "r");
  if (errno)
  {
    fputs("main - cannot open file containing m_inner\n", stderr);
    goto m_cn_free;
  }
  m_inner = double_array2_fscan(
    m_inner_file,
    d + 1,
    m_cn,
    m_inner_format
  );
  // m_inner = 
  //   double_array2_fscan_by_name(m_inner_name, d + 1, m_cn, m_inner_format);
  if (errno)
  {
    fputs("main - cannot  scan m_inner\n", stderr);
    goto m_inner_file_close;
  }
  
  matrix_sparse_laplacian_symmetric(m_laplacian, d, m_inner);
  
  out_format = argv[6];
  matrix_sparse_array_fprint(stdout, d + 1, m_laplacian, out_format);

  double_array2_free(m_inner, d + 1);
m_inner_file_close:
  fclose(m_inner_file);
m_cn_free:
  free(m_cn);
m_laplacian_free:
  matrix_sparse_array_free(m_laplacian, d + 1);
m_laplacian_file_close:
  fclose(m_laplacian_file);
end:
  return errno;
}
