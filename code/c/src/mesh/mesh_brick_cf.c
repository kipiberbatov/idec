#include <errno.h>
#include <stdlib.h>
#include "int.h"
#include "mesh_private.h"
#include "mesh_brick_private.h"

jagged4 * mesh_brick_cf(int d, const int * m_cn, const int * partitions)
{
  int m_cf_a2_size, m_cf_a3_size, m_cf_a4_size;
  jagged4 * m_cf;

  m_cf = (jagged4 *) malloc(sizeof(jagged4));
  if (errno)
  {
    fputs("mesh_brick_cf - cannot allocate memory for m->cf\n", stderr);
    goto end;
  }

  m_cf->a0 = d;
  m_cf->a1 = (int *) malloc(sizeof(int) * d);
  if (errno)
  {
    fputs("mesh_brick_cf - cannot allocate memory for m->cf->a1\n", stderr);
    goto m_cf_free;
  }
  mesh_cf_a1(m_cf->a1, d);

  m_cf_a2_size = int_array_total_sum(d, m_cf->a1);
  m_cf->a2 = (int *) malloc(sizeof(int) * m_cf_a2_size);
  if (errno)
  {
    fputs("mesh_brick_cf - cannot allocate memory for m->cf->a2\n", stderr);
    goto m_cf_a1_free;
  }
  mesh_cf_a2(m_cf->a2, d, m_cn);

  m_cf_a3_size = int_array_total_sum(m_cf_a2_size, m_cf->a2);
  m_cf->a3 = (int *) malloc(sizeof(int) * m_cf_a3_size);
  if (errno)
  {
    fputs("mesh_brick_cf - cannot allocate memory for m->cf->a3\n", stderr);
    goto m_cf_a2_free;
  }
  mesh_brick_cf_a3(m_cf->a3, d, m_cn);

  m_cf_a4_size = int_array_total_sum(m_cf_a3_size, m_cf->a3);
  m_cf->a4 = (int *) malloc(sizeof(int) * m_cf_a4_size);
  if (errno)
  {
    fputs("mesh_brick_cf - cannot allocate memory for m->cf->a4\n", stderr);
    goto m_cf_a3_free;
  }
  mesh_brick_cf_a4(m_cf->a4, d, partitions);

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
