#include <string.h>
#include "double.h"
#include "mesh_qc.h"

static void mesh_qc_elasticity_laplacian_fprint(
  FILE * out, cs * m_cbd_0, cs * m_cbd_1, cs * m_cbd_star_elasticity_1,
  cs * m_cbd_star_elasticity_2)
{
  cs * m_laplacian_elasticity_1;
  
  m_laplacian_elasticity_1 = cs_laplacian_p(
    m_cbd_0, m_cbd_1, m_cbd_star_elasticity_1, m_cbd_star_elasticity_2);
  /* NULL pointer check */
  cs_fprint(out, m_laplacian_elasticity_1, "--raw");
  cs_free(m_laplacian_elasticity_1);
}

static void mesh_qc_elasticity_laplacian_fprint_fscan(FILE * out, FILE * in)
{
  int m_dim;
  mesh * m;
  cs * m_cbd_0, * m_cbd_1, * m_cbd_star_elasticity_1, *m_cbd_star_elasticity_2;
  cs ** m_bd;
  
  m = mesh_fscan(in);
  /* NULL pointer check */
  m_dim = m->dim;
  m_bd = mesh_fscan_bd(in, m);
  /* NULL pointer check */
  m_cbd_0 = cs_transpose(m_bd[0], 1);
  /* NULL pointer check */
  m_cbd_1 = cs_transpose(m_bd[1], 1);
  /* NULL pointer check */
  m_cbd_star_elasticity_1 = mesh_fscan_bd_p(in, m, 1);
  /* NULL pointer check */
  m_cbd_star_elasticity_2 = mesh_fscan_bd_p(in, m, 2);
  /* NULL pointer check */
  mesh_qc_elasticity_laplacian_fprint(
    out, m_cbd_0, m_cbd_1, m_cbd_star_elasticity_1, m_cbd_star_elasticity_2);
  /* NULL pointer check */
  cs_free(m_cbd_star_elasticity_2);
  cs_free(m_cbd_star_elasticity_1);
  cs_free(m_cbd_1);
  cs_free(m_cbd_0);
  cs_free_array(m_bd, m_dim);
  mesh_free(m);
}

int main()
{
  mesh_qc_elasticity_laplacian_fprint_fscan(stdout, stdin);
  return 0;
}
