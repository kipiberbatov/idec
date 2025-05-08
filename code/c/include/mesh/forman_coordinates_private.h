#ifndef _forman_coordinates_private_h
#define _forman_coordinates_private_h

#include "mesh.h"

void forman_coordinates_standard(double * m_forman_coordinates, const mesh * m);

void
forman_coordinates_disk_polar(double * m_forman_coordinates, const mesh * m);

void forman_coordinates_centroid(double * m_forman_coordinates, const mesh * m);

#endif /* _forman_coordinates_private_h */
