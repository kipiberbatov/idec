#ifndef FORMAN_PRIVATE_H
#define FORMAN_PRIVATE_H

#include "forman.h"

/********************************* forman_cn **********************************/
void forman_cn(int * m_forman_cn, const mesh * m);

/********************************* forman_cf **********************************/
/* Boring work with indices to construct forman_cf. */
/* Use the code as it is. I do not remember the exact implementation details. */

/* cbi = cells by indices
 * fi = first indices 
 * si = second indces
 */

jagged3 * forman_cbi(const mesh * m, const int * m_forman_cn);
jagged2 * forman_fi(const mesh * m);
jagged3 * forman_si(const mesh * m);

jagged2 * forman_u(
  const mesh * m, int p_f, int q_f, int p, int i, int q, int j);

jagged3 * forman_v(
  const mesh * m, const jagged2 * m_forman_u, int p_f, int q_f, int q, int j);

void forman_polytope_vertices(
  int * m_forman_cell_to_faces, const mesh * m, const jagged2 * m_forman_u,
  const jagged3 * m_forman_v, const jagged2 * m_forman_fi,
  const jagged3 * m_forman_si, int p_f, int q_f, int q);
  
void forman_cell_to_faces(
  int * m_forman_cell_to_faces, const mesh * m, const jagged3 * m_forman_cbi,
  const jagged2 * m_forman_fi, const jagged3 * m_forman_si,
  int p_f, int q_f, int i_f);

void forman_cf_a3(int * m_forman_cf_a3, int m_dim, const int * m_forman_cn);

void forman_cf_a4(
  int * m_forman_cf_a4, const mesh * m, const int * m_forman_cn);

jagged4 * forman_cf(const mesh * m, const int * m_forman_cn);

/********************************** forman_boundary *********************************/
matrix_sparse * forman_boundary_p_f(
  const mesh * m_forman, matrix_sparse ** bd,
  const jagged3 * m_forman_cbi, int p_f);

/******************************** forman_coord ********************************/
void forman_coord(double * m_forman_coord, const mesh * m);

#endif /* FORMAN_PRIVATE_H */
