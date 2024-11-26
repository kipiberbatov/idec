#include <errno.h>
#include <stdlib.h>
#include <string.h>

#include "color.h"
#include "double.h"
#include "int.h"
#include "matrix_sparse.h"

int main(int argc, char ** argv)
{
  char * m_inner_format, * m_inner_name, * m_laplacian_format,
       * m_laplacian_name, * out_format;
  int d, p;
  int * m_cn;
  double ** m_inner;
  matrix_sparse ** m_laplacian;
  FILE * m_laplacian_file, * m_inner_file;

#define ARGC 7
  if (argc != ARGC)
  {
    color_error_position(__FILE__, __LINE__);
    fprintf(stderr,
      "the number of command-line arguments must be %d; instead it is %d\n",
      ARGC, argc);
    errno = EIO;
    goto end;
  }

  d = int_string_scan(argv[1]);
  if (errno)
  {
    color_error_position(__FILE__, __LINE__);
    fprintf(stderr, "cannot scan dimension d from string %s\n", argv[1]);
    goto end;
  }

  m_laplacian_name = argv[2];
  m_laplacian_format = argv[3];
  m_laplacian_file = fopen(m_laplacian_name, "r");
  if (m_laplacian_file == NULL)
  {
    color_error_position(__FILE__, __LINE__);
    fprintf(stderr,
      "cannot open file %s for reading: %s\n",
      m_laplacian_name, strerror(errno));
    goto end;
  }
  m_laplacian = matrix_sparse_array_file_scan(
    m_laplacian_file, d + 1, m_laplacian_format);
  if (m_laplacian == NULL)
  {
    color_error_position(__FILE__, __LINE__);
    fprintf(stderr,
      "cannot scan m_laplacian from file %s in format %s\n",
      m_laplacian_name, m_laplacian_format);
    goto m_laplacian_file_close;
  }

  m_cn = (int *) malloc(sizeof(int) * (d + 1));
  if (m_cn == NULL)
  {
    color_error_position(__FILE__, __LINE__);
    fprintf(stderr,
      "cannot allocate %ld bytes of memmory for m_cn\n",
      sizeof(int) * (d + 1));
    goto m_laplacian_free;
  }
  for (p = 0; p <= d; ++p)
    m_cn[p] = m_laplacian[p]->cols;

  m_inner_name = argv[4];
  m_inner_format = argv[5];
  m_inner_file = fopen(m_inner_name, "r");
  if (m_inner_file == NULL)
  {
    color_error_position(__FILE__, __LINE__);
    fprintf(stderr,
      "cannot open file %s for reading: %s\n",
      m_inner_name, strerror(errno));
    goto m_cn_free;
  }
  m_inner = double_array2_file_scan(m_inner_file, d + 1, m_cn, m_inner_format);
  if (m_inner == NULL)
  {
    color_error_position(__FILE__, __LINE__);
    fprintf(stderr,
      "cannot scan m_inner from file %s in format %s\n",
      m_inner_name, m_inner_format);
    goto m_inner_file_close;
  }

  matrix_sparse_laplacian_symmetric(m_laplacian, d, m_inner);

  out_format = argv[6];
  matrix_sparse_array_file_print(stdout, d + 1, m_laplacian, out_format);

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
