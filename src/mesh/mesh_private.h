#ifndef MESH_PRIVATE_H
#define MESH_PRIVATE_H

#include "mesh.h"

/*********************************** mesh_c ***********************************/
void mesh_c(int * m_c, int m_dim, const int * m_cn);

/********************************** mesh_cf ***********************************/
void mesh_cf_a1(int * m_cf_a1, int m_dim);
void mesh_cf_a2(int * m_cf_a2, int m_dim, const int * m_cn);

jagged4 * mesh_cf_fscan(FILE * in, int m_dim, const int * m_cn);

/********************************* mesh_cell **********************************/
void mesh_cell_coord(
  double * s_coord, const jagged1 * m_cf_p_0_i,
  int m_dim_embedded, const double * m_coord);

/********************************* mesh_fscan *********************************/
mesh * mesh_fscan_raw(FILE * in);

#define MESH_FSCAN_FORMAT_TOTAL 1

static const char * mesh_fscan_format[MESH_FSCAN_FORMAT_TOTAL] =
  {
    "--raw"
  };

typedef mesh * (*mesh_fscan_function_type)(FILE *);

static const mesh_fscan_function_type 
mesh_fscan_function[MESH_FSCAN_FORMAT_TOTAL] =
  {
    mesh_fscan_raw
  };

/******************************** mesh_fprint *********************************/
void mesh_fprint_raw(FILE * out, const mesh * a);

#define MESH_FPRINT_FORMAT_TOTAL 1

static const char * mesh_fprint_format[MESH_FPRINT_FORMAT_TOTAL] =
  {
    "--raw"
  };

typedef void (*mesh_fprint_function_type)(FILE *, const mesh *);

static const mesh_fprint_function_type
mesh_fprint_function[MESH_FPRINT_FORMAT_TOTAL] =
  {
    mesh_fprint_raw
  };

#endif /* MESH_PRIVATE_H */
