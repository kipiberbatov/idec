#include <stdlib.h>
#include <string.h>
#include "double.h"
#include "mesh_qc.h"

static void mesh_qc_elasticity_cbd_star_2_fprint_raw(
  FILE * out, const mesh_qc * m, const matrix_sparse * m_bd_2,
  const double * m_inner_2, const double * m_inner_1, double mu)
{
  int m_elasticity_cbd_star_2_nonzero_max;
  matrix_sparse * m_elasticity_cbd_star_2;
  
  m_elasticity_cbd_star_2 =
    mesh_qc_elasticity_cbd_star_2(m, m_bd_2, m_inner_2, m_inner_1, mu);
  /* NULL pointer check */
  
  m_elasticity_cbd_star_2_nonzero_max
    = m_elasticity_cbd_star_2->cols_total[m_elasticity_cbd_star_2->cols];
  
  double_array_fprint(out, m_elasticity_cbd_star_2_nonzero_max,
                      m_elasticity_cbd_star_2->values, "--raw");
  
  matrix_sparse_free_shared(m_elasticity_cbd_star_2);
}

int main(int argc, char * argv[])
{
  mesh_qc * m;
  matrix_sparse ** m_bd;
  double mu;
  double ** m_inner;
  
  mu = atof(argv[1]);
  m = mesh_fscan(stdin, "--raw");
  /* NULL pointer check */
  m_bd = mesh_fscan_bd(stdin, m);
  /* NULL pointer check */
  m_inner = double_array2_fscan(stdin, m->dim + 1, m->cn, "--raw");
  /* NULL pointer check */
  mesh_qc_elasticity_cbd_star_2_fprint_raw(
    stdout, m, m_bd[1], m_inner[2], m_inner[1], mu);
  /* NULL pointer check */
  double_array2_free(m_inner, m->dim + 1);
  matrix_sparse_array_free(m_bd, m->dim);
  mesh_free(m);
  return 0;
}
