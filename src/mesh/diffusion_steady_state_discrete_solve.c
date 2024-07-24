#include <errno.h>
#include <stdlib.h>
#include <string.h>

#include "double.h"
#include "diffusion_discrete.h"
#include "diffusion_steady_state_discrete.h"

#define FUNCTION "diffusion_steady_state_discrete_solve"
#define START_ERROR_MESSAGE fprintf(stderr,"  %s: ", FUNCTION)

static matrix_sparse * lhs_calculate(
  const matrix_sparse * m_cbd_0,
  const double * pi_1,
  const matrix_sparse * m_cbd_star_1)
{
  matrix_sparse * lhs, * m_cbd_star_1_material;

  m_cbd_star_1_material = matrix_sparse_copy(m_cbd_star_1);
  if (errno)
  {
    fputs("  lhs_calculate: cannot initialize m_cbd_star_1_material\n", stderr);
    return NULL;
  }
  matrix_sparse_multiply_with_diagonal_matrix(m_cbd_star_1_material, pi_1);

  lhs = matrix_sparse_product(m_cbd_star_1_material, m_cbd_0);
  if (errno)
  {
    fputs("  lhs_calculate: cannot calculate matrix lhs\n", stderr);
    matrix_sparse_free(m_cbd_star_1_material);
    return NULL;
  }
  matrix_sparse_free(m_cbd_star_1_material);

  return lhs;
}

double * diffusion_steady_state_discrete_solve(
  const mesh * m,
  const matrix_sparse * m_cbd_0,
  const matrix_sparse * m_cbd_star_1,
  const diffusion_steady_state_discrete * data)
{ 
  int n;
  double * result = NULL;
  matrix_sparse * lhs;

  lhs = lhs_calculate(m_cbd_0, data->pi_1, m_cbd_star_1);
  if (errno)
  {
    START_ERROR_MESSAGE;
    fputs("cannot allocate memory for free_part\n", stderr);
    goto end;
  }

  n = m->cn[0];
  result = (double *) malloc(sizeof(double) * n);
  if (errno)
  {
    fputs("Runtime error stack trace:\n", stderr);
    START_ERROR_MESSAGE;
    fputs("cannot allocate memory for result\n", stderr);
    goto lhs_free;
  }
  memcpy(result, data->source, sizeof(double) * n);
  double_array_multiply_with(result, n, -1);

  /* apply Dirichlet boundary conditions */
  matrix_sparse_set_identity_rows(lhs, data->boundary_dirichlet);
  double_array_substitute_inverse(
    result,
    data->boundary_dirichlet->a0,
    data->g_dirichlet,
    data->boundary_dirichlet->a1);

  /* apply Neumann boundary conditions */
  diffusion_discrete_set_neumann_rows(
    lhs, m, data->boundary_neumann, data->pi_1);
  if (errno)
  {
    START_ERROR_MESSAGE;
    fputs("cannot apply Neumann boundary condition\n", stderr);
    goto lhs_free;
  }
  double_array_substitute_inverse(
    result,
    data->boundary_neumann->a0,
    data->g_neumann,
    data->boundary_neumann->a1);

  matrix_sparse_linear_solve(lhs, result, "--lu");
  if (errno)
  {
    START_ERROR_MESSAGE;
    fputs("  cannot solve linear system\n", stderr);
    goto lhs_free;
  }

lhs_free:
  matrix_sparse_free(lhs);
end:
  return result;
}
