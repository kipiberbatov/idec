#include <errno.h>
#include <stdlib.h>

#include "color.h"
#include "int.h"
#include "mesh_brick.h"

static void mesh_brick_regular_file_print_raw(FILE * out, int d, int n)
{
  int p;
  int m_bd_sizes[MAX_DIM], n_list[MAX_DIM];
  mesh * m;
  int ** m_bd;

  m = mesh_brick_regular(d, n);
  if (errno)
  {
    color_error_position(__FILE__, __LINE__);
    fputs("cannot calculate m\n", stderr);
    goto end;
  }
  mesh_file_print(out, m, "--raw");

  int_array_assign_constant(n_list, d, n);
  for (p = 1; p <= d; ++p)
    m_bd_sizes[p - 1] = mesh_boundary_nonzero_max(m, p);

  m_bd = mesh_brick_boundary(m->dim, n_list, m_bd_sizes);
  if (errno)
  {
    color_error_position(__FILE__, __LINE__);
    fputs("cannot calculate m->bd\n", stderr);
    goto m_free;
  }
  for (p = 0; p < d; ++p)
    int_array_file_print(out, m_bd_sizes[p], m_bd[p], "--raw");

  int_array2_free(m_bd, d);
m_free:
  mesh_free(m);
end:
  return;
}

int main(int argc, char ** argv)
{
  int d, n;

  if (argc != 3)
  {
    errno = EIO;
    color_error_position(__FILE__, __LINE__);
    fputs("the number of command-line arguments must be 3.\n", stderr);
    goto end;
  }

  sscanf(argv[1], "%d", &d);
  if (errno)
  {
    color_error_position(__FILE__, __LINE__);
    fputs("cannot scan dimension d\n", stderr);
    goto end;
  }

  sscanf(argv[2], "%d", &n);
  if (errno)
  {
    color_error_position(__FILE__, __LINE__);
    fputs("cannot scan number of divisions n\n", stderr);
    goto end;
  }

  mesh_brick_regular_file_print_raw(stdout, d, n);
  if (errno)
  {
    color_error_position(__FILE__, __LINE__);
    fputs("cannot calculate and print the mesh m\n", stderr);
    goto end;
  }

end:
  return errno;
}
