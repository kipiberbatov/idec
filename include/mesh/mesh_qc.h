#ifndef MESH_QC_H
#define MESH_QC_H

#include "mesh.h"
#include "quasi_cube.h"

typedef mesh mesh_qc;

/******************************** mesh_qc_vol *********************************/
double * mesh_qc_vol_p(const mesh_qc * m, int p);
double ** mesh_qc_vol(const mesh_qc * m);

/******************************* mesh_qc_metric *******************************/
vec_sparse ** mesh_qc_metric_p(
  const mesh_qc * m, int p, const double * m_vol_p);

vec_sparse *** mesh_qc_metric(const mesh_qc * m, double ** m_vol);

vec_sparse ** mesh_qc_metric_p_fscan(FILE * in, const mesh_qc * m, int p);
vec_sparse *** mesh_qc_metric_fscan(FILE * in, const mesh_qc * m);

/************************** mesh_qc_metric_corrected **************************/
vec_sparse ** mesh_qc_metric_corrected_p(
  const mesh_qc * m, int p, const double * m_vol_p, double * node_curvatures);

vec_sparse *** mesh_qc_metric_corrected(
  const mesh_qc * m, double ** m_vol, double * node_curvatures);

// vec_sparse ** mesh_qc_metric_corrected_p_fscan(
//   FILE * in, const mesh_qc * m, int p);
// vec_sparse *** mesh_qc_metric_corrected_fscan(FILE * in, const mesh_qc * m);

/***************************** mesh_qc_integrate ******************************/
double mesh_qc_integrate(const mesh_qc * m, const double * m_vol_m_dim,
                         const vec_sparse * a);

/******************************* mesh_qc_inner ********************************/
double * mesh_qc_inner_p(const mesh_qc * m, const double * m_vol_m_dim,
                         int p, vec_sparse ** m_metric_p);

double ** mesh_qc_inner(const mesh_qc * m, const double * m_vol_m_dim,
                        vec_sparse *** m_metric);

/***************************** mesh_qc_cbd_star *******************************/
cs * mesh_qc_cbd_star_p(
  const mesh_qc * m, int p, const cs * m_bd_p,
  const double * m_inner_p, const double * m_inner_p_minus_1);

cs ** mesh_qc_cbd_star(const mesh_qc * m, cs ** m_bd, double ** m_inner);

/******************************* mesh_qc_hodge ********************************/
cs * mesh_qc_hodge_p(const mesh_qc * m, cs ** m_bd, int p,
                     const double * m_inner_q, const double * m_coeff_q);

cs ** mesh_qc_hodge(const mesh_qc * m, cs ** m_bd, const double ** m_inner,
                    const double ** m_coeff);



/******************************************************************************/
/*                                 miscelaneous                               */
/******************************************************************************/

/************************ mesh_qc_hodge_codifferential ************************/
cs * mesh_qc_hodge_codifferential_p(
  int m_dim, int p, const cs * m_cbd_m_dim_minus_p, cs ** m_hodge);

cs ** mesh_qc_hodge_codifferential(int m_dim, cs ** m_cbd, cs ** m_hodge);

/***************************** mesh_qc_elasticity *****************************/
cs * mesh_qc_elasticity_cbd_star_1(
  const mesh_qc * m, const cs * m_bd_1, const double * m_inner_1,
  const double * m_inner_0, double lambda, double mu);

cs * mesh_qc_elasticity_cbd_star_2(
  const mesh_qc * m, const cs * m_bd_2,
  const double * m_inner_2, const double * m_inner_1, double mu);

/****************************** mesh_qc_bd_layer ******************************/
jagged1 * mesh_qc_bd_layer_0_hyperfaces(const mesh * m);

jagged1 * mesh_qc_bd_layer_0_cells(
  const mesh * m, const jagged1 * m_bd_layer_0_hyperfaces);

jagged1 * mesh_qc_bd_layer_0_1_nodes(
  const mesh * m, const jagged1 * m_bd_layer_0_cells);

/******************************** mesh_qc_cup *********************************/
#if 0
jagged4 * mesh_qc_cup(const mesh * m);
typedef struct cochain
{
  int p;
  int i;
  double coeff;
} cochain;

cochain * mesh_qc_cup_product(
  const mesh * m, const cochain * cc1, const cochain * cc2);
cochain *** mesh_cup_product_dimensions_fixed(const mesh * m, int p, int q);
cochain ***** mesh_cup_product_all(const mesh * m);
#endif
  
#endif /* MESH_QC_H */
