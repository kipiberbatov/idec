#include <stdio.h>
#include <stdlib.h>
#include "array_fprint.h"
#include "forman_private.h"
#include "imath.h"
// #include "int_fprint.h"
#include "list.h"

static int * forman_cf_a3(
  int m_forman_cf_a3_size, int m_dim, const int * m_forman_cn)
{
  int ind, i_f, m_forman_cn_p_f, p_f, q_f, r_f, vertices_number;
  int * m_forman_cf_a3;
  
  m_forman_cf_a3 = (int *) malloc(m_forman_cf_a3_size * sizeof(int));
  /* NULL pointer check */
  ind = 0;
  for (p_f = 1; p_f <= m_dim; ++p_f)
  {
    m_forman_cn_p_f = m_forman_cn[p_f];
    for (q_f = 0; q_f < p_f; ++q_f)
    {
      r_f = p_f - q_f;
      vertices_number = (1 << r_f) * imath_binom(p_f, r_f);
      for (i_f = 0; i_f < m_forman_cn_p_f; ++i_f)
      {
        m_forman_cf_a3[ind] = vertices_number;
        ++ind;
      }
    }
  }
  return m_forman_cf_a3;
}

// static int * forman_cf_a4_long(
//   int m_dim, int m_forman_cf_a4_size, const int * m_forman_cn, const mesh * m,
//   const jagged3 * m_forman_cbi, const jagged2 * m_forman_fi,
//   const jagged3 * m_forman_si)
// {
//   int ind, i_f, j_f_loc, m_forman_cn_p_f, p_f, q_f, r_f, vertices_number;
//   int * m_forman_cf_a4;
//   int m_forman_cell_to_faces[12];
//
//   m_forman_cf_a4 = (int *) malloc(m_forman_cf_a4_size * sizeof(int));
//   /* NULL pointer check */
//   ind = 0;
//   for (p_f = 1; p_f <= m_dim; ++p_f)
//   {
//     m_forman_cn_p_f = m_forman_cn[p_f];
//     for (q_f = 0; q_f < p_f; ++q_f)
//     {
//       r_f = p_f - q_f;
//       vertices_number = (1 << r_f) * imath_binom(p_f, r_f);
//       for (i_f = 0; i_f < m_forman_cn_p_f; ++i_f)
//       {
//         forman_cell_to_faces(m_forman_cell_to_faces, m, m_forman_cbi,
//                              m_forman_fi, m_forman_si, p_f, q_f, i_f);
//         /* NULL pointer check */
//         for (j_f_loc = 0; j_f_loc < vertices_number; ++j_f_loc)
//           m_forman_cf_a4[ind + j_f_loc] = m_forman_cell_to_faces[j_f_loc];
//         ind += vertices_number;
//       }
//     }
//   }
//   return m_forman_cf_a4;
// }
//
// jagged4 * forman_cf_long(
//   const mesh * m, const int * m_forman_cn,
//   const jagged3 * m_forman_cbi,
//   const jagged2 * m_forman_fi,
//   const jagged3 * m_forman_si)
// {
//   int m_dim, m_forman_cf_a2_size, m_forman_cf_a3_size, m_forman_cf_a4_size;
//   int * m_cn, * m_forman_cf_a1, * m_forman_cf_a2, * m_forman_cf_a3,
//       * m_forman_cf_a4;
//   jagged4 * m_forman_cf;
//
//   m_dim = m->dim;
//   m_cn = m->cn;
//   m_forman_cf = (jagged4 *) malloc(sizeof(jagged4));
// /* NULL pointer check */
// m_forman_cf_a1 = mesh_cf_a1(m_dim);
// /* NULL pointer check */
// m_forman_cf_a2_size = list_sum(m_forman_cf_a1, 0, m_dim);
// m_forman_cf_a2 = mesh_cf_a2(m_forman_cf_a2_size, m_dim, m_forman_cn);
// /* NULL pointer check */
//   m_forman_cf_a3_size = list_sum(m_forman_cf_a2, 0, m_forman_cf_a2_size);
//   m_forman_cf_a3 =
//     forman_cf_a3(m_dim, m_forman_cf_a3_size, m_forman_cn);
//   /* NULL pointer check */
//   m_forman_cf_a4_size = list_sum(m_forman_cf_a3, 0, m_forman_cf_a3_size);
//   m_forman_cf_a4 =
//     forman_cf_a4_long(
//       m_dim, m_forman_cf_a4_size, m_forman_cn, m,
//       m_forman_cbi, m_forman_fi, m_forman_si);
//   /* NULL pointer check */
//   jagged4_set(m_forman_cf, m_dim, m_forman_cf_a1, m_forman_cf_a2,
//               m_forman_cf_a3, m_forman_cf_a4);
//   return m_forman_cf;
// }

// jagged4 * forman_cf_direct(const mesh * m, const int * m_forman_cn)
// {
//   jagged2 * m_forman_fi;
//   jagged3 * m_forman_cbi, * m_forman_si;
//   jagged4 * m_forman_cf;
//
//   m_forman_cbi = forman_cbi(m, m_forman_cn);
//   /* NULL pointer check */
//   m_forman_fi = forman_fi(m);
//   /* NULL pointer check */
//   m_forman_si = forman_si(m);
//   /* NULL pointer check */
//   m_forman_cf = forman_cf(m, m_forman_cn, m_forman_cbi,
//                                       m_forman_fi, m_forman_si);
//   /* NULL pointer check */
//   jagged3_free(m_forman_si);
//   jagged2_free(m_forman_fi);
//   jagged3_free(m_forman_cbi);
//   return m_forman_cf;
// }

static int * forman_cf_a4(
  int m_forman_cf_a4_size, const mesh * m, const int * m_forman_cn)
{
  int ind, i_f, j_f_loc, m_dim, m_forman_cn_p_f, p_f, q_f, r_f, vertices_number;
  int m_forman_cell_to_faces[100]; /* 100 -> 12 */
  int * m_forman_cf_a4;
  jagged2 * m_forman_fi;
  jagged3 * m_forman_cbi, * m_forman_si;

  m_dim = m->dim;
  m_forman_cf_a4 = (int *) malloc(m_forman_cf_a4_size * sizeof(int));
  /* NULL pointer check */
  m_forman_cbi = forman_cbi(m, m_forman_cn);
  /* NULL pointer check */
  m_forman_fi = forman_fi(m);
  /* NULL pointer check */
  m_forman_si = forman_si(m);
  /* NULL pointer check */
  ind = 0;
  for (p_f = 1; p_f <= m_dim; ++p_f)
  {
    m_forman_cn_p_f = m_forman_cn[p_f];
    for (q_f = 0; q_f < p_f; ++q_f)
    {
      r_f = p_f - q_f;
      vertices_number = (1 << r_f) * imath_binom(p_f, r_f);
      for (i_f = 0; i_f < m_forman_cn_p_f; ++i_f)
      {
        forman_cell_to_faces(m_forman_cell_to_faces, m, m_forman_cbi,
                             m_forman_fi, m_forman_si, p_f, q_f, i_f);
        /* NULL pointer check */
        for (j_f_loc = 0; j_f_loc < vertices_number; ++j_f_loc)
          m_forman_cf_a4[ind + j_f_loc] = m_forman_cell_to_faces[j_f_loc];
        ind += vertices_number;
      }
    }
  }
  jagged3_free(m_forman_si);
  jagged2_free(m_forman_fi);
  jagged3_free(m_forman_cbi);
  return m_forman_cf_a4;
}

jagged4 * forman_cf(const mesh * m, const int * m_forman_cn)
{
  int m_dim, m_forman_cf_a2_size, m_forman_cf_a3_size, m_forman_cf_a4_size;
  int * m_forman_cf_a1, * m_forman_cf_a2, * m_forman_cf_a3, * m_forman_cf_a4;
  jagged4 * m_forman_cf;
  
  m_dim = m->dim;
  m_forman_cf = (jagged4 *) malloc(sizeof(jagged4));
  /* NULL pointer check */
  m_forman_cf_a1 = mesh_cf_a1(m_dim);
  /* NULL pointer check */
  m_forman_cf_a2_size = list_sum(m_forman_cf_a1, 0, m_dim);
  m_forman_cf_a2 = mesh_cf_a2(m_forman_cf_a2_size, m_dim, m_forman_cn);
  /* NULL pointer check */
  m_forman_cf_a3_size = list_sum(m_forman_cf_a2, 0, m_forman_cf_a2_size);
  m_forman_cf_a3 = forman_cf_a3(m_forman_cf_a3_size, m_dim, m_forman_cn);
  /* NULL pointer check */
  m_forman_cf_a4_size = list_sum(m_forman_cf_a3, 0, m_forman_cf_a3_size);
  m_forman_cf_a4 = forman_cf_a4(m_forman_cf_a4_size, m, m_forman_cn);
  jagged4_set(m_forman_cf, m_dim, m_forman_cf_a1, m_forman_cf_a2,
              m_forman_cf_a3, m_forman_cf_a4);
  return m_forman_cf;
}
