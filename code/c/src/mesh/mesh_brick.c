#include <errno.h>
#include <stdlib.h>
#include "int.h"
#include "mesh_brick_private.h"
#include "mesh_private.h"

mesh * mesh_brick(int d, const double * brick_lengths, const int * n)
{
  int m_c_size;
  mesh * m;

  if (d > MAX_DIM)
  {
    errno = EINVAL;
    fputs("mesh_brick - dimension is too big\n", stderr);
    goto end;
  }

  if (d < 0)
  {
    errno = EINVAL;
    fputs("mesh_brick - dimension is negative\n", stderr);
    goto end;
  }

  m = (mesh *) malloc(sizeof(mesh));
  if (errno)
  {
    fputs("mesh_brick - cannot allocate memory for m\n", stderr);
    goto end;
  }

  m->dim_embedded = d;
  m->dim = d;

  m->cn = (int *) calloc((m->dim + 1), sizeof(int));
  if (errno)
  {
    fputs("mesh_brick - cannot allocate memory for m->cn\n", stderr);
    goto m_free;
  }
  mesh_brick_cn(m->cn, m->dim, n);

  m_c_size = int_array_total_sum(m->dim + 1, m->cn);
  m->c = (int *) malloc(sizeof(int) * m_c_size);
  if (errno)
  {
    fputs("mesh_brick - cannot allocate memory for m->c\n", stderr);
    goto m_cn_free;
  }
  mesh_c(m->c, m->dim, m->cn);

  m->cf = mesh_brick_cf(m->dim, m->cn, n);
  if (errno)
  {
    fputs("mesh_brick - cannot calculate m->cf\n", stderr);
    goto m_c_free;
  }

  m->fc = NULL;

  m->coord = (double *) malloc(sizeof(double) * m->dim * m->cn[0]);
  if (errno)
  {
    fputs("mesh_brick - cannot allocate memory for m->coord\n", stderr);
    goto m_cf_free;
  }
  mesh_brick_coord(m->coord, m->dim, brick_lengths, n);

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
