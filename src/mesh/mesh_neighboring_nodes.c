#include <errno.h>
#include <stdlib.h>

#include "mesh.h"

jagged1 * mesh_neighboring_nodes(const mesh * m, int i)
{
  int j, j_local;
  int * values;
  jagged1 * result;
  jagged1 m_cf_1_0_j, m_fc_0_1_i;
  jagged2 m_cf_1_0, m_fc_0_1;
  
  result = (jagged1 *) malloc(sizeof(jagged1));
  if (errno)
  {
    fprintf(stderr, "Error: cannot allocate memory for result\n");
    return NULL;
  }
  
  mesh_cf_part2(&m_cf_1_0, m, 1, 0);
  mesh_fc_part2(&m_fc_0_1, m, 0, 1);
  jagged2_part1(&m_fc_0_1_i, &m_fc_0_1, i);
  values = (int *) malloc(sizeof(int) * m_fc_0_1_i.a0);
  if (errno)
  {
    fprintf(stderr, "Error: cannot allocate memory for values\n");
    free(result);
    return NULL;
  }
  
  for (j_local = 0; j_local <= m_fc_0_1_i.a0; ++ j_local)
  {
    j = m_fc_0_1_i.a1[j_local];
    jagged2_part1(&m_cf_1_0_j, &m_cf_1_0, j);
    values[j_local] = jagged1_couple_other_object(&m_cf_1_0_j, i);
  }
  
  result->a0 = m_fc_0_1_i.a0;
  result->a1 = values;
  return result;
}
