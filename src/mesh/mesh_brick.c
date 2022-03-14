#include <errno.h>
#include <stdlib.h>
#include "mesh_brick.h"

mesh * mesh_brick(int d, const double * brick_lengths, const int * n)
{
  mesh * m;
  
  if (d > MAX_DIM)
  {
    errno = EINVAL;
    perror("Dimension too big");
    goto end;
  }
  if (d < 0)
  {
    errno = EINVAL;
    perror("Negative dimension");
    goto end;
  }
  m = (mesh *) malloc(sizeof(mesh));
  if (errno)
  {
    perror("Cannot allocate memory for m");
    goto end;
  }
  m->dim_embedded = d;
  m->dim = d;
  m->cn = mesh_brick_cn(m->dim, n);
  if (errno)
  {
    perror("Cannot calculate m->cn");
    goto m_free;
  }
  m->c = mesh_c(m->dim, m->cn);
  if (errno)
  {
    perror("Cannot calculate m->c");
    goto m_cn_free;
  }
  m->cf = mesh_brick_cf(m->dim, m->cn, n);
  if (errno)
  {
    perror("Cannot calculate m->cf");
    goto m_c_free;
  }
  m->fc = NULL;
  m->coord = mesh_brick_coord(m->dim, m->cn[0], brick_lengths, n);
  if (errno)
  {
    perror("Cannot calculate m->coord");
    goto m_cf_free;
  }
  return m;
  
  /* cleaning if an error occurs */
m_cf_free:
  free(m->cf);
m_c_free:
  free(m->c);
m_cn_free:
  free(m->cn);
m_free:
  free(m);
end:
  return NULL;
}
