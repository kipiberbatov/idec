#include "mesh_qc.h"

// static double * mesh_qc_cbd_star_physical_single_x(
//   const mesh_qc * m, int p, const cs * m_bd_p,
//   const double * m_inner_p, const double * m_inner_p_minus_1,
//   const double * c_p_minus_1)
// {
//   int i, ind, j, j_loc, m_cn_p;
//   double sign, m_inner_p_i;
//   double * m_bd_p_x, * m_cbd_star_p_x;
//   jagged1 hyperfaces;
//   jagged2 topology;
//   jagged4 * m_cf;
//
//   m_cn_p = m->cn[p];
//   m_cf = m->cf;
//   m_bd_p_x = m_bd_p->x;
//   m_cbd_star_p_x = (double *) malloc(m_bd_p->nzmax * sizeof(double));
//   /* NULL pointer check */
//   jagged4_part2(&topology, m_cf, p - 1, p - 1);
//   ind = 0;
//   for (i = 0; i < m_cn_p; ++i)
//   {
//     jagged2_part1(&hyperfaces, &topology, i);
//     m_inner_p_i = m_inner_p[i];
//     for (j_loc = 0; j_loc < hyperfaces.a0; ++j_loc)
//     {
//       sign = m_bd_p_x[ind + j_loc];
//       j = hyperfaces.a1[j_loc];
//       m_cbd_star_p_x[ind + j_loc]
//         = sign * m_inner_p_i * c_p_minus_1[j] / m_inner_p_minus_1[j];
//     }
//     ind += hyperfaces.a0;
//   }
//   return m_cbd_star_p_x;
// }

static double * mesh_qc_cbd_star_physical_constant_single_x(
  const mesh_qc * m, int p, const cs * m_bd_p,
  const double * m_inner_p, const double * m_inner_p_minus_1,
  double c_p_minus_1)
{
  int i, ind, j, j_loc, m_cn_p;
  double sign, m_inner_p_i;
  double * m_bd_p_x, * m_cbd_star_p_x;
  jagged1 hyperfaces;
  jagged2 topology;
  jagged4 * m_cf;

  m_cn_p = m->cn[p];
  m_cf = m->cf;
  m_bd_p_x = m_bd_p->x;
  m_cbd_star_p_x = (double *) malloc(m_bd_p->nzmax * sizeof(double));
  /* NULL pointer check */
  jagged4_part2(&topology, m_cf, p - 1, p - 1);
  ind = 0;
  for (i = 0; i < m_cn_p; ++i)
  {
    jagged2_part1(&hyperfaces, &topology, i);
    m_inner_p_i = m_inner_p[i];
    for (j_loc = 0; j_loc < hyperfaces.a0; ++j_loc)
    {
      sign = m_bd_p_x[ind + j_loc];
      j = hyperfaces.a1[j_loc];
      m_cbd_star_p_x[ind + j_loc]
        = sign * m_inner_p_i * c_p_minus_1 / m_inner_p_minus_1[j];
    }
    ind += hyperfaces.a0;
  }
  return m_cbd_star_p_x;
}

static cs * mesh_qc_cbd_star_physical_constant_single(
  const mesh_qc * m, int p, const cs * m_bd_p,
  const double * m_inner_p, const double * m_inner_p_minus_1,
  double c_p_minus_1)
{
  cs * m_cbd_star_p;
  
  m_cbd_star_p = (cs *) malloc(sizeof(cs));
  /* NULL pointer check */
  m_cbd_star_p->nzmax = m_bd_p->nzmax;
  m_cbd_star_p->m = m_bd_p->m;
  m_cbd_star_p->n = m_bd_p->n;
  m_cbd_star_p->p = m_bd_p->p;
  m_cbd_star_p->i = m_bd_p->i;
  m_cbd_star_p->x =
    mesh_qc_cbd_star_physical_constant_single_x(m, p, m_bd_p, m_inner_p,
                                                m_inner_p_minus_1, c_p_minus_1);
  /* NULL pointer check */
  m_cbd_star_p->nz = m_bd_p->nz;
  return m_cbd_star_p;
}

cs * mesh_qc_elasticity_cbd_star_1(
  const mesh_qc * m, const cs * m_bd_1, const double * m_inner_1,
  const double * m_inner_0, double lambda, double mu)
{
  cs * res;
  
  res = mesh_qc_cbd_star_physical_constant_single(m, 1, m_bd_1, m_inner_1,
                                                  m_inner_0, lambda + 2 * mu);
  /* NULL pointer check */
  return res;
}

cs * mesh_qc_elasticity_cbd_star_2(
  const mesh_qc * m, const cs * m_bd_2,
  const double * m_inner_2, const double * m_inner_1, double mu)
{
  cs * res;

  res = mesh_qc_cbd_star_physical_constant_single(m, 2, m_bd_2, m_inner_2,
                                                  m_inner_1, -mu);
  /* NULL pointer check */
  return res;
}

// cs * mesh_qc_elasticity_laplacian_0(
//   const mesh_qc * m, const cs * m_bd_2, const cs * m_bd_1,
//   const double * m_inner_2, const double * m_inner_1, const double * m_inner_0,
//   double lambda, double mu)
// {
//   res = 3;
// }

// cs ** mesh_qc_cbd_star_physical(
//   const mesh_qc * m, cs ** m_bd, double ** m_inner)
// {
//   int m_dim, p;
//   cs ** m_cbd_star;
//
//   //m_dim = m->dim;
//   m_cbd_star = (cs **) malloc(2 * sizeof(cs *));
//   /* NULL pointer check */
//   for (p = 1; p <= 2; ++p)
//   {
//     m_cbd_star[p - 1] =
//       mesh_qc_cbd_star_physical_single(m, p, m_bd[p - 1], m_inner[p],
//                                        m_inner[p - 1], c[p - 1]);
//     /* NULL pointer check */
//   }
//   return m_cbd_star;
// }
//
// void mesh_qc_cbd_star_fprint(
//   FILE * out, const mesh_qc * m, cs ** m_bd, double ** m_inner)
// {
//   int m_dim, p;
//   int * m_cn;
//   cs * m_cbd_star_p;
//
//   m_dim = m->dim;
//   m_cn = m->cn;
//   for (p = 1; p <= m_dim; ++p)
//   {
//     m_cbd_star_p =
//       mesh_qc_cbd_star_single(m, p, m_bd[p - 1], m_inner[p], m_inner[p - 1]);
//     /* NULL pointer check */
//     double_fprint_array_raw(out, m_cbd_star_p->nzmax, m_cbd_star_p->x);
//     cs_free_shared(m_cbd_star_p);
//   }
// }
//
// void mesh_qc_cbd_star_fprint_fscan(FILE * out, FILE * in)
// {
//   mesh_qc * m;
//   cs ** m_bd;
//   double ** m_inner;
//
//   m = mesh_fscan(in);
//   /* NULL pointer check */
//   m_bd = mesh_fscan_bd(in, m);
//   /* NULL pointer check */
//   m_inner = double_fscan_array2(in, m->dim + 1, m->cn);
//   /* NULL pointer check */
//   mesh_qc_cbd_star_fprint(out, m, m_bd, m_inner);
//   /* NULL pointer check */
//   double_free_array2(m_inner, m->dim + 1);
//   cs_free_array(m_bd, m->dim);
//   mesh_free(m);
// }
