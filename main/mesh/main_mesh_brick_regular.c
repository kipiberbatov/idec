#include "int.h"
#include "mesh_brick.h"

static void mesh_brick_regular_fprint(FILE * out, int d, int n)
{
  int p;
  int m_bd_sizes[MAX_DIM], n_list[MAX_DIM];
  mesh * m;
  int ** m_bd;
  
  m = mesh_brick_regular(d, n);
  /* NULL pointer check */
  mesh_fprint(out, m);
  for (p = 0; p < d; ++p)
    n_list[p] = n;
  for (p = 1; p <= d; ++p)
    m_bd_sizes[p - 1] = mesh_bd_nzmax(m, p);
  m_bd = mesh_brick_bd(m->dim, n_list, m_bd_sizes);
  /* NULL pointer check */
  for (p = 0; p < d; ++p)
    int_fprint_array_raw(out, m_bd_sizes[p], m_bd[p]);
  int_free_array2(m_bd, d);
  mesh_free(m);
}

int main(int argc, char * argv[])
{
  int d, n;
  
  d = atoi(argv[1]);
  n = atoi(argv[2]);
  mesh_brick_regular_fprint(stdout, d, n);
  return 0;
}
