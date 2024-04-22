#include <stdlib.h>
#include <string.h>
#include "double.h"
#include "mesh_qc.h"

static void mesh_qc_elasticity_cbd_star_1_file_print_raw(
  FILE * out, const mesh_qc * m, const matrix_sparse * m_bd_1,
  const double * m_inner_1, const double * m_inner_0, double lambda, double mu)
{
  int m_elasticity_cbd_star_1_nonzero_max;
  matrix_sparse * m_elasticity_cbd_star_1;
  
  m_elasticity_cbd_star_1 =
    mesh_qc_elasticity_cbd_star_1(m, m_bd_1, m_inner_1, m_inner_0, lambda, mu);
  /* NULL pointer check */
  
  m_elasticity_cbd_star_1_nonzero_max
    = m_elasticity_cbd_star_1->cols_total[m_elasticity_cbd_star_1->cols];
  
  double_array_file_print(out, m_elasticity_cbd_star_1_nonzero_max,
                      m_elasticity_cbd_star_1->values, "--raw");
  
  matrix_sparse_free_shared(m_elasticity_cbd_star_1);
}

int main(int argc, char * argv[])
{
  int m_dim;
  int * m_cn;
  mesh_qc * m;
  matrix_sparse ** m_bd;
  double lambda, mu;
  double ** m_inner;
  
  lambda = atof(argv[1]);
  mu = atof(argv[2]);
  m = mesh_file_scan(stdin, "--raw");
  /* NULL pointer check */
  m_dim = m->dim;
  m_cn = m->cn;
  m_bd = mesh_file_scan_bd(stdin, m);
  /* NULL pointer check */
  m_inner = double_array2_file_scan(stdin, m_dim + 1, m_cn, "--raw");
  /* NULL pointer check */
  mesh_qc_elasticity_cbd_star_1_file_print_raw(
    stdout, m, m_bd[0], m_inner[1], m_inner[0], lambda, mu);
  /* NULL pointer check */
  double_array2_free(m_inner, m_dim + 1);
  matrix_sparse_array_free(m_bd, m_dim);
  mesh_free(m);
  return 0;
}
