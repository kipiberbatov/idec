#include <errno.h>
#include <stdlib.h>
#include "forman_private.h"

mesh * forman(const mesh * m)
{
  mesh * m_forman;

  m_forman = (mesh *) malloc(sizeof(mesh));
  if (errno)
  {
    perror("Cannot allocate memory for m_forman");
    return NULL;
  }
  m_forman->dim_embedded = m->dim_embedded;
  m_forman->dim = m->dim;
  m_forman->cn = forman_cn(m);
  if (errno)
  {
    perror("Cannot calculate m_forman->cn");
    goto m_forman_free;
  }
  m_forman->c = mesh_c(m_forman->dim, m_forman->cn);
  if (errno)
  {
    perror("Cannot calculate m_forman->c");
    goto m_forman_cn_free;
  }
  m_forman->cf = forman_cf(m, m_forman->cn);
  if (errno)
  {
    perror("Cannot calculate m_forman->cf");
    goto m_forman_c_free;
  }
  m_forman->fc = NULL;
  m_forman->coord = forman_coord(m, m_forman->cn);
  if (errno)
  {
    perror("Cannot calculate m_forman->coord");
    goto m_forman_cf_free;
  }
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
  return NULL;
}
