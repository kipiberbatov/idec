#ifndef _mesh_and_boundary_h
#define _mesh_and_boundary_h

#include "mesh.h"

typedef struct mesh_and_boundary
{
  mesh * _mesh;
  double ** boundary;
} mesh_and_boundary;

void mesh_and_boundary_free(mesh_and_boundary * m_bd);

mesh_and_boundary * mesh_and_boundary_file_scan(FILE * in, const char * format);

mesh_and_boundary * mesh_and_boundary_file_scan_tess(FILE * in);

#endif /* _mesh_and_boundary_h */
