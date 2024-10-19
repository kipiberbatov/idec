#ifndef _forman_private_h
#define _forman_private_h

#include "forman.h"

/********************************* forman_cn **********************************/
void forman_cn(int * m_forman_cn, const mesh * m);

/********************************* forman_cf **********************************/
void
forman_cf_a3(int * m_forman_cf_a3, const mesh * m, const int * m_forman_cn);

void forman_cf_a4(int * m_forman_cf_a4, const mesh * m);

jagged4 * forman_cf(const mesh * m, const int * m_forman_cn);

/******************************** forman_coord ********************************/
void forman_coordinates(
  double * m_forman_coord, const mesh * m, const char * format);

#endif /* _forman_private_h */
