#include <errno.h>
#include <stdlib.h>
#include "list.h"
#include "mesh_brick_private.h"

jagged4 * mesh_brick_cf(int m_dim, const int * m_cn, const int * n)
{
  int m_cf_a2_size, m_cf_a3_size, m_cf_a4_size;
  jagged4 * m_cf;
  
  m_cf = (jagged4 *) malloc(sizeof(jagged4));
  if (errno)
  {
    perror("Cannot allocate memory for m->cf");
    goto end;
  }
  m_cf->a1 = mesh_cf_a1(m_dim);
  if (errno)
  {
    perror("Cannot calculate m->cf->a1");
    goto m_cf_free;
  }
  m_cf_a2_size = list_sum(m_cf->a1, 0, m_dim);
  m_cf->a2 = mesh_cf_a2(m_cf_a2_size, m_dim, m_cn);
  if (errno)
  {
    perror("Cannot calculate m->cf->a2");
    goto m_cf_a1_free;
  }
  m_cf_a3_size = list_sum(m_cf->a2, 0, m_cf_a2_size);
  m_cf->a3 = mesh_brick_cf_a3(m_cf_a3_size, m_dim, m_cn);
  if (errno)
  {
    perror("Cannot calculate m->cf->a3");
    goto m_cf_a2_free;
  }
  m_cf_a4_size = list_sum(m_cf->a3, 0, m_cf_a3_size);
  m_cf->a4 = mesh_brick_cf_a4(m_cf_a4_size, m_dim, n);
  if (errno)
  {
    perror("Cannot calculate m->cf->a4");
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
