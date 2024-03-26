#ifndef MESH_H
#define MESH_H

#include "matrix_sparse.h"
#include "jagged.h"
#include "vector_sparse.h"

#define MAX_DIM 10

typedef struct mesh
{
  int       dim_embedded; /* embedding dimension   */
  int       dim;          /* geometric dimension   */
  int *     cn;           /* cells numbers         */
  int *     c;            /* cells                 */
  jagged4 * cf;           /* cells to faces        */
  jagged4 * fc;           /* faces to cells        */
  double *  coord;        /* flattened coordinates */
} mesh;

/* Other abbreviations:
 * cfn - cells to faces number
 * fcn - faces to cells number
 * bd  - boundary
 * cbd - coboundary
 */

/********************************* mesh_free **********************************/
void mesh_free(mesh * m);

/********************************* mesh_fscan *********************************/
mesh * mesh_fscan(FILE * in, const char * format);

mesh * mesh_fscan_by_name(const char * name, const char * format);

matrix_sparse * mesh_fscan_bd_p(FILE * in, const mesh * m, int p);

matrix_sparse ** mesh_fscan_bd(FILE * in, const mesh * m);

/******************************** mesh_fprint *********************************/
void mesh_fprint(FILE * out, const mesh * m, const char * format);

/******************************* mesh_cf_part *********************************/
void mesh_cf_part2(jagged2 * m_cf_p_q, const mesh * m, int p, int q);
void mesh_cf_part3(jagged1 * m_cf_p_q_i, const mesh * m, int p, int q, int i);

/******************************* mesh_cfn_part ********************************/
void mesh_cfn_part2(jagged1 * m_cfn_p_q, const mesh * m, int p, int q);
int mesh_cfn_part3(const mesh * m, int p, int q, int i);

/********************************** mesh_fc ***********************************/
jagged4 * mesh_fc(const mesh * m);

/******************************* mesh_fc_part *********************************/
void mesh_fc_part2(jagged2 * m_fc_q_p, const mesh * m, int q, int p);
void mesh_fc_part3(jagged1 * m_fc_q_p_j, const mesh * m, int q, int p, int j);

/******************************* mesh_fcn_part ********************************/
void mesh_fcn_part2(jagged1 * m_fcn_q_p, const mesh * m, int q, int p);
int mesh_fcn_part3(const mesh * m, int q, int p, int j);

/**************************** mesh_bd_hyperfaces ******************************/
jagged1 * mesh_bd_hyperfaces(const mesh * m);
jagged1 * mesh_bd_cells(const mesh * m, const jagged1 * m_bd_hyperfaces);
jagged1 * mesh_almost_bd_cells(
  const mesh * m, const jagged1 * m_bd_cells, int p);

/********************************** mesh_bd ***********************************/
int mesh_bd_nzmax(const mesh * m, int p);
int * mesh_bd_p(const mesh * m, int p);
int * mesh_bd_i(const mesh * m, int p);
matrix_sparse * mesh_bd_single(const mesh * m, int p);
matrix_sparse ** mesh_bd(const mesh * m);

void mesh_bd_check(
  FILE * out, int m_dim, matrix_sparse ** m_bd, const char * name);

jagged1 * mesh_bd_nodes(const mesh * m);

/********************************* mesh_cbd ***********************************/
matrix_sparse * mesh_cbd_p(matrix_sparse * m_bd_p);
matrix_sparse ** mesh_cbd(int m_dim, matrix_sparse ** m_bd);

/******************************** mesh_measure ********************************/
double * mesh_measure(const mesh * m);
// double * mesh_measure_simplex(const mesh * m);
// double * mesh_measure_quasi_cube(const mesh * m);

/**************************** mesh_node_curvature *****************************/
// double mesh_node_curvature_i(const mesh * m, int i);
double * mesh_node_curvature(const mesh * m);

/***************************** mesh_displacement ******************************/
double ** mesh_displacement(
  const mesh * m, const matrix_sparse * m_bd_0, const double * u);

jagged1 * mesh_boundary_cells_of_hyperfaces(const mesh * m);

jagged1 * mesh_boundary_cells(
  const mesh * m,
  int p,
  const jagged1 * m_boundary_hyperfaces);

/*
Let $m be a mesh and $i is an index of a boundary node.
$normal holds coordinates of the exterior to that node.*/
// void mesh_point_normal(double * normal, const mesh * m, int i,
//   const jagged1 * m_nodes_bd);

#endif /* MESH_H */
