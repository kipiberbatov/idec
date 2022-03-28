#include <errno.h>
#include <stdlib.h>
#include "int.h"
#include "mesh_private.h"

jagged4 * mesh_cf_fscan(FILE * in, int m_dim, const int * m_cn)
{
  int m_cf_a2_size, m_cf_a3_size, m_cf_a4_size;
  jagged4 * m_cf;
  
  m_cf = (jagged4 *) malloc(sizeof(jagged4));
  if (errno)
  {
    perror("mesh_fscan_cf - cannot allocate memory for m->cf");
    goto end;
  }
  
  m_cf->a1 = (int * ) malloc(sizeof(int) * m_dim);
  if (errno)
  {
    perror("mesh_fscan_cf - cannot allocate memory for m->cf->a1");
    goto m_cf_free;
  }
  mesh_cf_a1(m_cf->a1, m_dim);
  
  m_cf_a2_size = int_array_total_sum(m_dim, m_cf->a1);
  m_cf->a2 = (int * ) malloc(sizeof(int) * m_cf_a2_size);
  if (errno)
  {
    perror("mesh_fscan_cf - cannot allocate memory for m->cf->a2");
    goto m_cf_a1_free;
  }
  mesh_cf_a2(m_cf->a2, m_dim, m_cn);
  
  m_cf_a3_size = int_array_total_sum(m_cf_a2_size, m_cf->a2);
  m_cf->a3 = int_array_fscan(in, m_cf_a3_size, "--raw");
  if (errno)
  {
    perror("mesh_fscan_cf - cannot scan m->cf->a3");
    goto m_cf_a2_free;
  }
  
  m_cf_a4_size = int_array_total_sum(m_cf_a3_size, m_cf->a3);
  m_cf->a4 = int_array_fscan(in, m_cf_a4_size, "--raw");
  if (errno)
  {
    perror("mesh_fscan_cf - cannot scan m->cf->a4");
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
