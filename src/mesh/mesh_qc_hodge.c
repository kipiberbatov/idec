#include "mesh_qc.h"

/* r = p + q,
 * cc[r, k] = sign * 2^r * (polytope_sum(cc[p, i], cc[q, j])).
 * cup_product(cc[p, i], cc[q, j]) = (sign / 2^r) * cc[r, k].
 */
static int mesh_qc_cup_product_sign(
  cs ** m_bd, int node, int p, int i, int q, int j, int r, int k)
{
  if (p == 0)
    return 1;
  if (q == 0)
    return 1;
  if (p == 1)
    return cs_part(m_bd[0], node, i) * cs_part(m_bd[r - 1], j, k);
  if (q == 1)
    return cs_part(m_bd[0], node, j) * cs_part(m_bd[r - 1], i, k);
  return 1;
}

static int list_intersection_count(const jagged1 * arr1, const jagged1 * arr2)
{
  int i, i_loc, j, j_loc, n;
  
  n = 0;
  for (i_loc = 0; i_loc < arr1->a0; ++i_loc)
  {
    i = arr1->a1[i_loc];
    for (j_loc = 0; j_loc < arr2->a0; ++j_loc)
    {
      j = arr2->a1[j_loc];
      if (i == j)
        ++n;
    }
  }
  return n;
}

static int list_intersection_unique(const jagged1 * arr1, const jagged1 * arr2)
{
  int i, i_loc, j, j_loc;
  
  for (i_loc = 0; i_loc < arr1->a0; ++i_loc)
  {
    i = arr1->a1[i_loc];
    for (j_loc = 0; j_loc < arr2->a0; ++j_loc)
    {
      j = arr2->a1[j_loc];
      if (i == j)
        return i;
    }
  }
  return -1;
}

/* Let c[d, k] be a volume around c[p, i].
 * Finds the combinatorially perpendicular cells of c[p, i] with respect to
 * c[d, k] and the nodes they intersect at.
 */
static void mesh_qc_perpendicular(
  int * nodes, int * perp, const mesh_qc * m, int p, int i, int k)
{
  int count, ind, j, j_loc, m_dim, q;
  jagged1 cell_candidates, p_cell_nodes, q_cell_nodes;
  
  m_dim = m->dim;
  q = m_dim - p;
  mesh_cf_part3(&cell_candidates, m, m_dim, q, k);
  mesh_cf_part3(&p_cell_nodes, m, p, 0, i);
  ind = 0;
  for (j_loc = 0; j_loc < cell_candidates.a0; ++j_loc)
  {
    j = jagged1_part1(&cell_candidates, j_loc);
    mesh_cf_part3(&q_cell_nodes, m, q, 0, j);
    count = list_intersection_count(&p_cell_nodes, &q_cell_nodes);
    if (count == 1)
    {
      nodes[ind] = list_intersection_unique(&p_cell_nodes, &q_cell_nodes);
      perp[ind] = j;
      ++ind;
    }
  }
}

cs * mesh_qc_hodge_p(const mesh_qc * m, cs ** m_bd, int p,
                     const double * m_inner_q, const double * m_coeff_q)
{
  int alpha, i, j, ind, k, k_loc, m_cn_p, m_dim, multiple, node, q;
  int * m_cn, * nodes, * perp;
  double sign;
  cs * m_hodge_p;
  jagged1 volume;
  
  m_dim = m->dim;
  q = m_dim - p;
  m_cn = m->cn;
  m_cn_p = m_cn[p];
  multiple = 1 << p;
  
  m_hodge_p = (cs *) malloc(sizeof(cs));
  /* NULL pointer check */
  
  m_hodge_p->m = m_cn[q];
  m_hodge_p->n = m_cn_p;
  
  m_hodge_p->p = (int *) malloc((m_cn_p + 1) * sizeof(int));
  /* NULL pointer check */
  m_hodge_p->p[0] = 0;
  for (i = 0; i < m_cn_p; ++i)
  {
    mesh_fc_part3(&volume, m, p, m_dim, i);
    m_hodge_p->p[i + 1] = m_hodge_p->p[i] + volume.a0 * multiple;
  }
  m_hodge_p->nzmax = m_hodge_p->p[m_cn_p];
  
  perp = (int *) malloc(multiple * sizeof(int));
  /* NULL pointer check */
  nodes = (int *) malloc(multiple * sizeof(int));
  /* NULL pointer check */
  m_hodge_p->i = (int *) malloc(m_hodge_p->nzmax * sizeof(int));
  /* NULL pointer check */
  ind = 0;
  for (i = 0; i < m_cn_p; ++i)
  {
    mesh_fc_part3(&volume, m, p, m_dim, i);
    for (k_loc = 0; k_loc < volume.a0; ++k_loc)
    {
      k = volume.a1[k_loc];
      mesh_qc_perpendicular(nodes, perp, m, p, i, k);
      for (alpha = 0; alpha < multiple; ++alpha)
      {
        m_hodge_p->i[ind] = perp[alpha];
        ++ind;
      }
    }
  }
  
  m_hodge_p->x = (double *) malloc(m_hodge_p->nzmax * sizeof(double));
  /* NULL pointer check */
  ind = 0;
  for (i = 0; i < m_cn_p; ++i)
  {
    mesh_fc_part3(&volume, m, p, m_dim, i);
    for (k_loc = 0; k_loc < volume.a0; ++k_loc)
    {
      k = volume.a1[k_loc];
      mesh_qc_perpendicular(nodes, perp, m, p, i, k);
      for (alpha = 0; alpha < multiple; ++alpha)
      {
        j = perp[alpha];
        node = nodes[alpha];
        sign = 
          (double) mesh_qc_cup_product_sign(m_bd, node, p, i, q, j, m_dim, k);
        m_hodge_p->x[ind] = m_coeff_q[j] * sign / ((1 << m_dim) * m_inner_q[j]);
        ++ind;
      }
    }
  }
  free(nodes);
  free(perp);
  
  m_hodge_p->nz = -1;
  
  return m_hodge_p;
}

cs ** mesh_qc_hodge(const mesh_qc * m, cs ** m_bd, const double ** m_inner,
                    const double ** m_coeff)
{
  int m_dim, p, q;
  cs ** m_hodge;
  
  m_dim = m->dim;
  m_hodge = (cs **) malloc((m_dim + 1) * sizeof(cs *));
  /* NULL pointer check */
  for (p = 0; p <= m_dim; ++p)
  {
    q = m_dim - p;
    m_hodge[p] = mesh_qc_hodge_p(m, m_bd, p, m_inner[q], m_coeff[q]);
    /* NULL pointer check */
  }
  return m_hodge;
}
