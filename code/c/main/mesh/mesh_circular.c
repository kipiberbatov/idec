#include <errno.h>
#include <stdlib.h>

#include "color.h"
#include "double.h"
#include "int.h"
#include "mesh_circular.h"

int main(int argc, char ** argv)
{
  int i, index, j;
  int m_bd_values_size, m_cn_1, na, nd;
  double * m_bd_values;
  mesh * m;

  if (argc != 3)
  {
    color_error_position(__FILE__, __LINE__);
    fprintf(stderr,
      "number of command-line arguments should be 3;"
      "instead it is %d\n", argc);
    goto end;
  }

  na = int_string_scan(argv[1]);
  if (errno)
  {
    color_error_position(__FILE__, __LINE__);
    fputs("cannot scan number of angles na\n", stderr);
    goto end;
  }

  nd = int_string_scan(argv[2]);
  if (errno)
  {
    color_error_position(__FILE__, __LINE__);
    fputs("cannot scan number of disks nd\n", stderr);
    goto end;
  }

  m = mesh_circular(na, nd, 1, 0, 0);
  if (m == NULL)
  {
    color_error_position(__FILE__, __LINE__);
    fputs("cannot scan number of disks nd\n", stderr);
    goto end;
  }

  m_cn_1 = m->cn[1];
  m_bd_values_size = 2 * m_cn_1 + na * (3 + 4 * (nd - 1));
  m_bd_values = (double *) malloc(sizeof(double) * m_bd_values_size);
  if (m_bd_values == NULL)
  {
    color_error_position(__FILE__, __LINE__);
    fprintf(stderr,
      "cannot allocate %ld bytes of memory for _bd_values\n",
      sizeof(double) * m_bd_values_size);
    goto m_free;
  }
  index = 0;
  for (i = 0; i < m_cn_1; ++i)
  {
    m_bd_values[index + 0] = - 1;
    m_bd_values[index + 1] = 1;
    index += 2;
  }
  for (j = 0; j < na; ++j)
  {
    m_bd_values[index + 0] = 1;
    m_bd_values[index + 1] = 1;
    m_bd_values[index + 2] = -1;
    index += 3;
  }
  for (i = 1; i < nd; ++i)
  {
    for (j = 0; j < na; ++j)
    {
      m_bd_values[index + 0] = -1;
      m_bd_values[index + 1] = 1;
      m_bd_values[index + 2] = 1;
      m_bd_values[index + 3] = -1;
      index += 4;
    }
  }

  mesh_file_print(stdout, m, "--raw");
  double_array_file_print(stdout, m_bd_values_size, m_bd_values, "--raw");

  free(m_bd_values);
m_free:
  mesh_free(m);
end:
  return errno;
}
