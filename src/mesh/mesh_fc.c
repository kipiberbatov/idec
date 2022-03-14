#include <stdlib.h>
#include "mesh.h"
#include "list.h"

static int * mesh_fc_a1(int m_dim)
{
  int q;
  int * m_fc_a1;
  
  m_fc_a1 = (int *) malloc(m_dim * sizeof(int));
  /* NULL pointer check */
  for (q = 0; q <= m_dim; ++q)
    m_fc_a1[q] = m_dim - q;
  return m_fc_a1;
}

static int * mesh_fc_a2(int m_fc_a2_size, int m_dim, const int * m_cn)
{
  int ind, m_cn_q, p, q;
  int * m_fc_a2;
  
  m_fc_a2 = (int *) malloc(m_fc_a2_size * sizeof(int));
  /* NULL pointer check */
  ind = 0;
  for (q = 0; q < m_dim; ++q)
  {
    m_cn_q = m_cn[q];
    for (p = q + 1; p <= m_dim; ++p)
    {
      m_fc_a2[ind] = m_cn_q;
      ++ind;
    }
  }
  return m_fc_a2;
}

static int * mesh_fc_a3(int m_fc_a3_size, const mesh * m)
{
  int i, ind, j, j_loc, m_cn_q, m_dim, p, q;
  int * m_cn, * m_fc_a3;
  jagged1 face;
  jagged2 faces;
  
  m_dim = m->dim;
  m_cn = m->cn;
  m_fc_a3 = (int *) calloc(m_fc_a3_size, sizeof(int));
  /* NULL pointer check */
  ind = 0;
  for (q = 0; q < m_dim; ++q)
  {
    m_cn_q = m_cn[q];
    for (p = q + 1; p <= m_dim; ++p)
    {
      mesh_cf_part2(&faces, m, p, q);
      for (i = 0; i < m_cn[p]; ++i)
      {
        jagged2_part1(&face, &faces, i);
        for (j_loc = 0; j_loc < face.a0; ++j_loc)
        {
          j = (face.a1)[j_loc];
          ++(m_fc_a3[ind + j]);
        }
      }
      ind += m_cn_q;
    }
  }
  return m_fc_a3;
}

static int * mesh_fc_a4(int m_fc_a4_size, const mesh * m, int * m_fc_a3)
{
  int i, ind, ind_loc, j, j_loc, m_cn_q, m_dim, p, q, tmp, tmp_list_sum;
  int * ind_current, * m_cn, * m_fc_a4;
  jagged1 face;
  jagged2 faces;
  
  m_dim = m->dim;
  m_cn = m->cn;
  m_fc_a4 = (int *) malloc(m_fc_a4_size * sizeof(int));
  /* NULL pointer check */
  ind_loc = 0;
  ind = 0;
  for (q = 0; q < m_dim; ++q)
  {
    m_cn_q = m_cn[q];
    for (p = q + 1; p <= m_dim; ++p)
    {
      ind_current = (int *) calloc(m_cn_q, sizeof(int));
      /* NULL pointer check */
      mesh_cf_part2(&faces, m, p, q);
      for (i = 0; i < m_cn[p]; ++i)
      {
        jagged2_part1(&face, &faces, i);
        for (j_loc = 0; j_loc < face.a0; ++j_loc)
        {
          j = (face.a1)[j_loc];
          tmp_list_sum = list_sum(m_fc_a3, ind_loc, ind_loc + j);
          tmp = ind + tmp_list_sum + ind_current[j];
          m_fc_a4[tmp] = i;
          ++ind_current[j];
        }
      }
      free(ind_current);
      ind += list_sum(m_fc_a3, ind_loc, ind_loc + m_cn[q]);
      ind_loc += m_cn_q;
    }
  }
  return m_fc_a4;
}

/* the next function constructs fc if only cf is given */
jagged4 * mesh_fc(const mesh * m)
{
  int m_dim, m_fc_a2_size, m_fc_a3_size, m_fc_a4_size;
  int * m_fc_a1, * m_fc_a2, * m_fc_a3, * m_fc_a4, * m_cn;
  jagged4 * m_fc;
  
  m_dim = m->dim;
  m_cn = m->cn;
  m_fc = (jagged4 *) malloc(sizeof(jagged4));
  /* NULL pointer check */
  m_fc_a1 = mesh_fc_a1(m_dim);
  /* NULL pointer check */
  m_fc_a2_size = list_sum(m_fc_a1, 0, m_dim);
  m_fc_a2 = mesh_fc_a2(m_fc_a2_size, m_dim, m_cn);
  /* NULL pointer check */
  m_fc_a3_size = list_sum(m_fc_a2, 0, m_fc_a2_size);
  m_fc_a3 = mesh_fc_a3(m_fc_a3_size, m);
  /* NULL pointer check */
  m_fc_a4_size = list_sum(m_fc_a3, 0, m_fc_a3_size);
  m_fc_a4 = mesh_fc_a4(m_fc_a4_size, m, m_fc_a3);
  /* NULL pointer check */
  jagged4_set(m_fc, m_dim, m_fc_a1, m_fc_a2, m_fc_a3, m_fc_a4);
  return m_fc;
}
