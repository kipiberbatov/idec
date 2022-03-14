#ifndef FORMAN_PRIVATE_H
#define FORMAN_PRIVATE_H

#include "forman.h"

/********************************* forman_cn **********************************/
int * forman_cn(const mesh * m);

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

void forman_u_array(jagged2 * m_forman_u_array, const mesh * m,
                    int p_f, int q_f, int p, int i, int q, int j);

void forman_v_array(
  jagged3 * m_forman_v_array, int * m_forman_v_array_a3_size, const mesh * m,
  const jagged2 * m_forman_u_array, int p_f, int q_f, int q, int j);

void forman_polytope_vertices(
  int * m_forman_pv, const mesh * m, const jagged2 * m_forman_u_array,
  const jagged3 * m_forman_v_array, int m_forman_v_array_a3_size,
  const jagged2 * m_forman_fi, const jagged3 * m_forman_si,
  int p_f, int q_f, int q);
  
void forman_cell_to_faces(
  int * m_forman_cell_to_faces, const mesh * m, const jagged3 * m_forman_cbi,
  const jagged2 * m_forman_fi, const jagged3 * m_forman_si,
  int p_f, int q_f, int i_f);

cs * forman_bd_p_f(const mesh * m_forman, cs ** bd,
                   const jagged3 * m_forman_cbi, int p_f);

jagged4 * forman_cf(const mesh * m, const int * m_forman_cn);

/******************************** forman_coord ********************************/
double * forman_coord(const mesh * m, const int * m_forman_cn);

#endif /* FORMAN_PRIVATE_H */
