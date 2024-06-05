#ifndef FORMAN_PRIVATE_H
#define FORMAN_PRIVATE_H

#include "forman.h"

/********************************* forman_cn **********************************/
void forman_cn(int * m_forman_cn, const mesh * m);

/********************************* forman_cf **********************************/

/*
cbi = cells by indices

The result is the list of all quadruples of the form (p, i, q, j), where
c(q, i) is a subface of c(p, i).

The list is in particularly defined as follows:
cbi.a0 = m->dim + 1
cbi.a1 = m_forman_cn
cbi.a2 = {4}^total(m_forman_cn)
cbi.a3[r, a, b] = (p, i, q, j), where
  . (p, i) corresponds to the deflattening of m_forman_cn
  . q = p - r
  . j comes from the delattening of b
*/
jagged3 * forman_cbi(const mesh * m, const int * m_forman_cn);

void forman_cf_a3(int * m_forman_cf_a3, const mesh * m);

void forman_cf_a4(int * m_forman_cf_a4, const mesh * m);

jagged4 * forman_cf(const mesh * m, const int * m_forman_cn);

/******************************* forman_boundary ******************************/
matrix_sparse * forman_boundary_p_f(
  const mesh * m_forman, matrix_sparse ** bd,
  const jagged3 * m_forman_cbi, int p_f);

/******************************** forman_coord ********************************/
void forman_coord(double * m_forman_coord, const mesh * m);

#endif /* FORMAN_PRIVATE_H */
