#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include "double.h"
#include "int.h"
#include "list.h"
#include "mesh.h"

static jagged4 * mesh_fscan_cf(FILE * in, int m_dim, const int * m_cn)
{
  int m_cf_a2_size, m_cf_a3_size, m_cf_a4_size;
  jagged4 * m_cf;
  
  m_cf = (jagged4 *) malloc(sizeof(jagged4));
  if (errno)
  {
    perror("Cannot allocate memory for m_cf");
    goto end;
  }
  m_cf->a1 = mesh_cf_a1(m_dim);
  if (errno)
  {
    perror("Cannot scan m->cf->a1");
    goto m_cf_free;
  }
  m_cf_a2_size = list_sum(m_cf->a1, 0, m_dim);
  m_cf->a2 = mesh_cf_a2(m_cf_a2_size, m_dim, m_cn);
  if (errno)
  {
    perror("Cannot scan m->cf->a2");
    goto m_cf_a1_free;
  }
  m_cf_a3_size = list_sum(m_cf->a2, 0, m_cf_a2_size);
  m_cf->a3 = int_fscan_array(in, m_cf_a3_size);
  if (errno)
  {
    perror("Cannot scan m->cf->a3");
    goto m_cf_a2_free;
  }
  m_cf_a4_size = list_sum(m_cf->a3, 0, m_cf_a3_size);
  m_cf->a4 = int_fscan_array(in, m_cf_a4_size);
  if (errno)
  {
    perror("Cannot scan m->cf->a4");
    goto m_cf_a3_free;
  }
  return m_cf;
  
  /* cleaning if an error occurs */
m_cf_a3_free:
  free(m_cf->a3);
m_cf_a2_free:
  free(m_cf->a2);
m_cf_a1_free:
  free(m_cf->a1);
m_cf_free:
  free(m_cf);
end:
  return NULL;
}

mesh * mesh_fscan(FILE * in)
{
  int m_c_size;
  mesh * m;
  
  m = (mesh *) malloc(sizeof(mesh));
  if (errno)
  {
    perror("Cannot allocate memory for m");
    goto end;
  }
  m->dim_embedded = int_fscan(in);
  if (errno)
  {
    perror("Cannot scan m->dim_embedded");
    goto m_free;
  }
  m->dim = int_fscan(in);
  if (errno)
  {
    perror("Cannot scan m->dim");
    goto m_free;
  }
  m->cn = int_fscan_array(in, m->dim + 1);
  if (errno)
  {
    perror("Cannot scan m->cn");
    goto m_free;
  }
  m_c_size = list_sum(m->cn, 0, m->dim + 1);
  m->c = int_fscan_array(in, m_c_size);
  if (errno)
  {
    perror("Cannot scan m->c");
    goto m_cn_free;
  }
  m->cf = mesh_fscan_cf(in, m->dim, m->cn);
  if (errno)
  {
    perror("Cannot scan m->cf");
    goto m_c_free;
  }
  m->fc = NULL;
  m->coord = double_fscan_matrix(in, m->cn[0], m->dim_embedded);
  if (errno)
  {
    perror("Cannot scan m->coord");
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
