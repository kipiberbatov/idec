#include <string.h>
#include "double.h"
#include "mesh_qc.h"

static void mesh_qc_elasticity_laplacian_fprint_raw(
  FILE * out, matrix_sparse * m_cbd_0, matrix_sparse * m_cbd_1, matrix_sparse * m_cbd_star_elasticity_1,
  matrix_sparse * m_cbd_star_elasticity_2)
{
  matrix_sparse * m_laplacian_elasticity_1;
  
  m_laplacian_elasticity_1 = matrix_sparse_laplacian_p(
    m_cbd_0, m_cbd_1, m_cbd_star_elasticity_1, m_cbd_star_elasticity_2);
  /* NULL pointer check */
  matrix_sparse_fprint(out, m_laplacian_elasticity_1, "--raw");
  matrix_sparse_free(m_laplacian_elasticity_1);
}

int main()
{
  mesh * m;
  matrix_sparse * m_cbd_0, * m_cbd_1, * m_cbd_star_elasticity_1, 
                * m_cbd_star_elasticity_2;
  matrix_sparse ** m_bd;
  
  m = mesh_fscan(stdin, "--raw");
  /* NULL pointer check */
  m_bd = mesh_fscan_bd(stdin, m);
  /* NULL pointer check */
  m_cbd_0 = matrix_sparse_transpose(m_bd[0]);
  /* NULL pointer check */
  m_cbd_1 = matrix_sparse_transpose(m_bd[1]);
  /* NULL pointer check */
  m_cbd_star_elasticity_1 = mesh_fscan_bd_p(stdin, m, 1);
  /* NULL pointer check */
  m_cbd_star_elasticity_2 = mesh_fscan_bd_p(stdin, m, 2);
  /* NULL pointer check */
  mesh_qc_elasticity_laplacian_fprint_raw(
    stdout, m_cbd_0, m_cbd_1, m_cbd_star_elasticity_1, m_cbd_star_elasticity_2);
  /* NULL pointer check */
  matrix_sparse_free(m_cbd_star_elasticity_2);
  matrix_sparse_free(m_cbd_star_elasticity_1);
  matrix_sparse_free(m_cbd_1);
  matrix_sparse_free(m_cbd_0);
  matrix_sparse_array_free(m_bd, m->dim);
  mesh_free(m);
  return 0;
}
