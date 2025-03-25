#ifndef _mesh_measures_h
#define _mesh_measures_h

struct mesh;

void mesh_measures_default(
  double *** m_measures, int * status, const struct mesh * m);

void mesh_measures_simplicial_or_quasi_cubical(
  double *** m_measures, int * status, const struct mesh * m);

/* m is the Forman mesh of a circular mesh */
void mesh_measures_circular_forman(
  double *** m_measures, int * status, const struct mesh * m);

#endif /* _mesh_measures_h */
