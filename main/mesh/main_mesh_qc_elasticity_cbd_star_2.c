#include <string.h>
#include "double.h"
#include "mesh_qc.h"

static void mesh_qc_elasticity_cbd_star_2_fprint(
  FILE * out, const mesh_qc * m, const cs * m_bd_2,
  const double * m_inner_2, const double * m_inner_1, double mu)
{
  cs * m_elasticity_cbd_star_2;
  
  m_elasticity_cbd_star_2 =
    mesh_qc_elasticity_cbd_star_2(m, m_bd_2, m_inner_2, m_inner_1, mu);
  /* NULL pointer check */
  double_fprint_array_raw(out, m_elasticity_cbd_star_2->nzmax,
                          m_elasticity_cbd_star_2->x);
  cs_free_shared(m_elasticity_cbd_star_2);
}

static void mesh_qc_elasticity_cbd_star_2_fprint_fscan(
  FILE * out, FILE * in, double mu)
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
  mesh_qc_elasticity_cbd_star_2_fprint(
    out, m, m_bd[1], m_inner[2], m_inner[1], mu);
  /* NULL pointer check */
  double_free_array2(m_inner, m_dim + 1);
  cs_free_array(m_bd, m_dim);
  mesh_free(m);
}

int main(int argc, char * argv[])
{
  double mu;
  
  mu = atof(argv[1]);
  mesh_qc_elasticity_cbd_star_2_fprint_fscan(stdout, stdin, mu);
  return 0;
}
