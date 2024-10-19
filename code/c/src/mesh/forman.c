#include <errno.h>
#include <stdlib.h>
#include "forman_private.h"
#include "int.h"
#include "mesh_private.h"

mesh * forman(const mesh * m, const char * new_coordinates_format)
{
  int m_forman_c_size, m_forman_coord_size;
  mesh * m_forman;

  m_forman = (mesh *) malloc(sizeof(mesh));
  if (errno)
  {
    fputs("forman - cannot allocate memory for m_forman\n", stderr);
    goto end;
  }

  m_forman->dim_embedded = m->dim_embedded;
  m_forman->dim = m->dim;

  m_forman->cn = (int *) calloc((m->dim + 1), sizeof(int));
  if (errno)
  {
    fputs("forman - cannot allocate memory for m_forman->cn\n", stderr);
    goto m_forman_free;
  }
  forman_cn(m_forman->cn, m);

  m_forman_c_size = int_array_total_sum(m->dim + 1, m_forman->cn);
  m_forman->c = (int *) malloc(sizeof(int) * m_forman_c_size);
  if (errno)
  {
    fputs("forman - cannot allocate memory for m_forman->c\n", stderr);
    goto m_forman_cn_free;
  }
  mesh_c(m_forman->c, m->dim, m_forman->cn);

  m_forman->cf = forman_cf(m, m_forman->cn);
  if (errno)
  {
    fputs("forman - cannot calculate m_forman->cf", stderr);
    goto m_forman_c_free;
  }

  m_forman->fc = NULL;

  m_forman_coord_size = m->dim_embedded * m_forman->cn[0];
  m_forman->coord = (double *) calloc(m_forman_coord_size, sizeof(double));
  if (errno)
  {
    fputs("forman - cannot allocate memory for m_forman_coord", stderr);
    goto m_forman_cf_free;
  }
  forman_coordinates(m_forman->coord, m, new_coordinates_format);

  return m_forman;

  /* cleaning if an error occurs */
m_forman_cf_free:
  free(m_forman->cf);
m_forman_c_free:
  free(m_forman->c);
m_forman_cn_free:
  free(m_forman->cn);
m_forman_free:
  free(m_forman);
end:
  return NULL;
}
