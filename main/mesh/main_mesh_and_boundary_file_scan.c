#include <errno.h>

#include "double.h"
#include "mesh_and_boundary.h"

int main(int argc, char ** argv)
{
  int d, p, size;
  char * format;
  double ** bd;
  mesh * m;
  mesh_and_boundary * m_and_bd;
  jagged1 m_cfn_pp1_p;

  if (argc != 2)
  {
    fputs("main: number of command line arguments should be 1\n", stderr);
    return errno;
  }

  format = argv[1];
  m_and_bd = mesh_and_boundary_file_scan(stdin, format);
  if (errno)
  {
    fprintf(stderr, "%s:%d: unable to scan mesh and boundary in format %s\n",
      __FILE__, __LINE__, format);
    return errno;
  }
  
  m = m_and_bd->_mesh;
  bd = m_and_bd->boundary;
  d = m->dim;
  mesh_file_print(stdout, m, "--raw");
  for (p = 0; p < d; ++p)
  {
    mesh_cfn_part2(&m_cfn_pp1_p, m, p + 1, p);
    size = jagged1_total_sum(&m_cfn_pp1_p);
    double_array_file_print(stdout, size, bd[p], "--raw");
  }
  mesh_and_boundary_free(m_and_bd);
  return 0;
}
