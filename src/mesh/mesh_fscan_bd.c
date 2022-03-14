#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "double.h"
#include "mesh.h"

// cs * mesh_fscan_bd_single(FILE * in, const mesh * m, int p)
// {
//   int * m_cn;
//   cs * m_bd;
//
//   m_cn = m->cn;
//   m_bd = (cs *) malloc(sizeof(cs));
//   /* NULL pointer check */
//   m_bd->nzmax = mesh_bd_nzmax(m, p); /* using m_cfn */
//   m_bd->m = m_cn[p - 1];
//   m_bd->n = m_cn[p]; /* using m_cfn */
//   m_bd->p = mesh_bd_p(m, p);
//   /* NULL pointer check */
//   m_bd->i = mesh_bd_i(m, p);
//   /* NULL pointer check */
//   m_bd->x = double_fscan_array(in, m_bd->nzmax);
//   /* NULL pointer check */
//   m_bd->nz = -1;
//   return m_bd;
// }
//
// cs ** mesh_fscan_bd(FILE * in, const mesh * m)
// {
//   int m_dim, p;
//   cs ** m_bd;
//
//   m_dim = m->dim;
//   m_bd = (cs **) malloc(m_dim * sizeof(cs *));
//   /* NULL pointer check */
//   for (p = 1; p <= m_dim; ++p)
//   {
//     m_bd[p - 1] = mesh_fscan_bd_single(in, m, p);
//     /* NULL pointer check */
//   }
//   return m_bd;
// }

cs * mesh_fscan_bd_p(FILE * in, const mesh * m, int p)
{
  int i, m_bd_n;
  int * m_bd_p;
  jagged1 cells;
  jagged2 topology;
  cs * m_bd;

  m_bd = (cs *) malloc(sizeof(cs));
  /* NULL pointer check */
  m_bd->m = m->cn[p - 1];
  m_bd->n = m->cn[p];
  m_bd_n = m_bd->n;
  m_bd->p = (int *) malloc((m_bd_n + 1) * sizeof(int));
  mesh_cfn_part2(&cells, m, p, p - 1);
  m_bd_p = m_bd->p;
  m_bd_p[0] = 0;
  for (i = 0; i < m_bd->n; ++i)
    m_bd_p[i + 1] = m_bd_p[i] + cells.a1[i];
  m_bd->nzmax = m_bd_p[m_bd_n];
  m_bd->i = (int *) malloc(m_bd->nzmax * sizeof(int));
  /* NULL pointer check */
  mesh_cf_part2(&topology, m, p, p - 1);
  memcpy(m_bd->i, topology.a2, m_bd->nzmax * sizeof(int));
  m_bd->x = double_fscan_array(in, m_bd->nzmax);
  /* NULL pointer check */
  m_bd->nz = -1;
  return m_bd;
}

cs ** mesh_fscan_bd(FILE * in, const mesh * m)
{
  int m_dim, p;
  cs ** m_bd;
  
  m_dim = m->dim;
  m_bd = (cs **) malloc(m_dim * sizeof(cs *));
  /* NULL pointer check */
  for (p = 1; p <= m_dim; ++p)
  {
    m_bd[p - 1] = mesh_fscan_bd_p(in, m, p);
    /* NULL pointer check */
  }
  return m_bd;
}
