#include <string.h>
#include "double.h"
#include "mesh_qc.h"

static void mesh_qc_elasticity_cbd_star_1_fprint(
  FILE * out, const mesh_qc * m, const cs * m_bd_1,
  const double * m_inner_1, const double * m_inner_0, double lambda, double mu)
{
  cs * m_elasticity_cbd_star_1;
  
  m_elasticity_cbd_star_1 =
    mesh_qc_elasticity_cbd_star_1(m, m_bd_1, m_inner_1, m_inner_0, lambda, mu);
  /* NULL pointer check */
  double_fprint_array_raw(out, m_elasticity_cbd_star_1->nzmax,
                          m_elasticity_cbd_star_1->x);
  cs_free_shared(m_elasticity_cbd_star_1);
}

static void mesh_qc_elasticity_cbd_star_1_fprint_fscan(
  FILE * out, FILE * in, double lambda, double mu)
{
  int m_dim;
  int * m_cn;
  mesh_qc * m;
  cs ** m_bd;
  double ** m_inner;
  
  m = mesh_fscan(in);
  /* NULL pointer check */
  m_dim = m->dim;
  m_cn = m->cn;
  m_bd = mesh_fscan_bd(in, m);
  /* NULL pointer check */
  m_inner = double_fscan_array2(in, m_dim + 1, m_cn);
  /* NULL pointer check */
  mesh_qc_elasticity_cbd_star_1_fprint(
    out, m, m_bd[0], m_inner[1], m_inner[0], lambda, mu);
  /* NULL pointer check */
  double_free_array2(m_inner, m_dim + 1);
  cs_free_array(m_bd, m_dim);
  mesh_free(m);
}

int main(int argc, char * argv[])
{
  double lambda, mu;
  
  lambda = atof(argv[1]);
  mu = atof(argv[2]);
  mesh_qc_elasticity_cbd_star_1_fprint_fscan(stdout, stdin, lambda, mu);
  return 0;
}
