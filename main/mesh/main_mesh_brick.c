#include "int.h"
#include "mesh_brick.h"

static void mesh_brick_fprint(
  FILE * out, int d, const double * brick_lengths, const int * n)
{
  int p;
  int m_bd_sizes[MAX_DIM];
  mesh * m;
  int ** m_bd;
  
  m = mesh_brick(d, brick_lengths, n);
  /* NULL pointer check */
  mesh_fprint(out, m);
  for (p = 1; p <= d; ++p)
    m_bd_sizes[p - 1] = mesh_bd_nzmax(m, p);
  m_bd = mesh_brick_bd(m->dim, n, m_bd_sizes);
  /* NULL pointer check */
  for (p = 0; p < d; ++p)
    int_fprint_array_raw(out, m_bd_sizes[p], m_bd[p]);
  int_free_array2(m_bd, d);
  mesh_free(m);
}

int main(int argc, char * argv[])
{
  int d, p;
  int n[MAX_DIM];
  double brick_lengths[MAX_DIM];
  
  d = atoi(argv[1]);
  for (p = 0; p < d; ++p)
    brick_lengths[p] = atoi(argv[2 + p]);
  for (p = 0; p < d; ++p)
    n[p] = atoi(argv[2 + d + p]);
  mesh_brick_fprint(stdout, d, brick_lengths, n);
  return 0;
}
