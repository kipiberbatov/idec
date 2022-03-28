#include <errno.h>
#include <stdlib.h>
#include "int.h"
#include "mesh_brick.h"

static void mesh_brick_fprint_raw(
  FILE * out, int d, const double * brick_lengths, const int * n)
{
  int p;
  int m_bd_sizes[MAX_DIM];
  mesh * m;
  int ** m_bd;
  
  m = mesh_brick(d, brick_lengths, n);
  if (errno)
  {
    fputs("mesh_brick_fprint - cannot calculate m\n", stderr);
    goto end;
  }
  mesh_fprint(out, m, "--raw");
  
  for (p = 1; p <= d; ++p)
    m_bd_sizes[p - 1] = mesh_bd_nzmax(m, p);
  
  m_bd = mesh_brick_bd(m->dim, n, m_bd_sizes);
  if (errno)
  {
    fputs("mesh_brick_fprint - cannot calculate m->bd\n", stderr);
    goto m_free;
  }
  
  for (p = 0; p < d; ++p)
    int_array_fprint(out, m_bd_sizes[p], m_bd[p], "--raw");
  
  int_array2_free(m_bd, d);
m_free:
  mesh_free(m);
end:
  return;
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
  
  mesh_brick_fprint_raw(stdout, d, brick_lengths, n);
  
  if (errno)
  {
    fputs("mesh_brick_fprint - find and print m->bd\n", stderr);
    return errno;
  }

  return 0;
}
