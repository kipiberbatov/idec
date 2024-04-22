#ifndef MESH_PRIVATE_H
#define MESH_PRIVATE_H

#include "mesh.h"

/*********************************** mesh_c ***********************************/
void mesh_c(int * m_c, int m_dim, const int * m_cn);

/********************************** mesh_cf ***********************************/
void mesh_cf_a1(int * m_cf_a1, int m_dim);
void mesh_cf_a2(int * m_cf_a2, int m_dim, const int * m_cn);

jagged4 * mesh_cf_file_scan(FILE * in, int m_dim, const int * m_cn);

/********************************* mesh_cell **********************************/
void mesh_cell_coord(
  double * s_coord, const jagged1 * m_cf_p_0_i,
  int m_dim_embedded, const double * m_coord);

/********************************* mesh_file_scan *********************************/
mesh * mesh_file_scan_raw(FILE * in);

#define mesh_file_scan_format_total 1

static const char * mesh_file_scan_format[mesh_file_scan_format_total] =
  {
    "--raw"
  };

typedef mesh * (*mesh_file_scan_function_type)(FILE *);

static const mesh_file_scan_function_type 
mesh_file_scan_function[mesh_file_scan_format_total] =
  {
    mesh_file_scan_raw
  };

/******************************** mesh_file_print *********************************/
void mesh_file_print_raw(FILE * out, const mesh * a);

#define mesh_file_print_format_total 1

static const char * mesh_file_print_format[mesh_file_print_format_total] =
  {
    "--raw"
  };

typedef void (*mesh_file_print_function_type)(FILE *, const mesh *);

static const mesh_file_print_function_type
mesh_file_print_function[mesh_file_print_format_total] =
  {
    mesh_file_print_raw
  };

#endif /* MESH_PRIVATE_H */
