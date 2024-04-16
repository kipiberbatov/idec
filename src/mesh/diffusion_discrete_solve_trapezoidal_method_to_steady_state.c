#include <errno.h>
#include <stdlib.h>
#include <string.h>

#include "diffusion_discrete.h"

static void loop(
  double_array_sequence_dynamic * result,
  matrix_sparse * lhs,
  double * rhs_final,
  const matrix_sparse * rhs,
  const double * free_part,
  const jagged1 * boundary_dirichlet,
  const double * g_dirichlet,
  const jagged1 * boundary_neumann,
  const double * g_neumann)
{
  int i, j, n;
  double relative_norm;
  double ** tmp;

  n = rhs->rows;
  i = 0;
  do
  {
    // fprintf(stderr, "i = %d\n", i);
    
    memcpy(rhs_final, free_part, sizeof(double) * n);
    // fputs("  Copying rhs_final successful!\n", stderr);
    
    matrix_sparse_vector_multiply_add(rhs_final, rhs, result->values[i]);
    // fputs("  Mutating rhs_final successful!\n", stderr);
    
    /* update rhs_final with the boundary conditions */
    double_array_substitute_inverse(
      rhs_final, boundary_dirichlet->a0, g_dirichlet, boundary_dirichlet->a1);
    // fputs("  Applying Dirichlet condition successful!\n", stderr);
    
    double_array_substitute_inverse(
      rhs_final, boundary_neumann->a0, g_neumann, boundary_neumann->a1);
    // fputs("  Applying Neumann condition successful!\n", stderr);

    if (i == result->capacity - 1)
    {
      tmp = (double **) malloc(sizeof(double *) * 2 * result->capacity);
      /* NULL pointer checking */
      for (j = 0; j < result->capacity; ++j)
        tmp[j] = result->values[j];
      free(result->values);
      result->values = tmp;
      result->capacity *= 2;
    }
    // fputs("  Managing capacity successful!\n", stderr);
    
    result->values[i + 1] = malloc(sizeof(double) * n);
    // fputs("  Allocation successful!\n", stderr);
    memcpy(result->values[i + 1], rhs_final, sizeof(double) * n);
    // fputs("  Copying next iteration successful!\n", stderr);
    matrix_sparse_linear_solve(lhs, result->values[(i + 1)], "--lu");
    // fputs("  Linear solving successful!\n", stderr);
    ++result->length;
    // fputs("  Incrementing length successful!\n", stderr);
    // double_array_fprint(stderr, n, result->values[i], "--raw");
    // fprintf(stderr, "  %g\n", double_array_norm_uniform(n, result->values[i]));
    // fprintf(stderr, "  %g\n", double_array_norm_uniform(n, result->values[i + 1]));
    relative_norm = double_array_pair_norm_uniform_relative(
      n,
      result->values[i],
      result->values[i + 1]
    );
    // fputs("  Calculating condition successful!\n", stderr);
    ++i;
    // fprintf(stderr, "dimension = %d\n", result->dimension);
    // fprintf(stderr, "relative_norm = %g\n", relative_norm);
  }
  while (relative_norm >= 0.01);
  //--result->length;
}

double_array_sequence_dynamic *
diffusion_discrete_solve_trapezoidal_method_to_steady_state(
  const mesh * m,
  const matrix_sparse * m_cbd_0,
  const matrix_sparse * m_cbd_star_1,
  const diffusion_discrete * data,
  double time_step)
{ 
  int n;
  double * free_part, * rhs_final;
  double * a;
  matrix_sparse * b;
  matrix_sparse * m_cbd_star_1_material;
  matrix_sparse * lhs, * rhs;
  double_array_sequence_dynamic * result;
  
  n = m->cn[0];
  a = data->pi_0;
  
  m_cbd_star_1_material = matrix_sparse_copy(m_cbd_star_1);
  matrix_sparse_multiply_with_diagonal_matrix(
    m_cbd_star_1_material, data->pi_1);
  b = matrix_sparse_product(m_cbd_star_1_material, m_cbd_0);
  /* NULL pointer checking */
  
  /* lhs =  a + (time_step / 2) * b */
  lhs = matrix_sparse_copy(b);
  /* NULL pointer checking */
  matrix_sparse_scalar_multiply(lhs, time_step / 2);
  matrix_sparse_add_with_diagonal_matrix(lhs, a);
  
  /* lhs =  a - (time_step / 2) * b */
  rhs = matrix_sparse_copy(b);
  /* NULL pointer checking */
  matrix_sparse_scalar_multiply(rhs, - time_step / 2);
  matrix_sparse_add_with_diagonal_matrix(rhs, a);
  
  free_part = (double *) malloc(sizeof(double) * n);
  /* NULL pointer checking */
  
  memcpy(free_part, data->source, sizeof(double) * n);
  double_array_multiply_with(free_part, n, time_step);
  
  matrix_sparse_set_identity_rows(lhs, data->boundary_dirichlet);
  diffusion_discrete_set_neumann_rows(
    lhs, m, data->boundary_neumann, data->pi_1);
  /* NULL pointer checking */
  
  rhs_final = (double *) malloc(sizeof(double) * n);
  /* NULL pointer checking */
  
  // result = (double **) malloc(sizeof(double *));
  /* NULL pointer checking */
  //*result = (double *) malloc(sizeof(double) * n);

  result = (double_array_sequence_dynamic *) malloc(
    sizeof(double_array_sequence_dynamic *));
  result->capacity = 8;
  result->length = 1;
  result->dimension = n;
  result->values = malloc(sizeof(double *) * result->capacity);
  result->values[0] = (double *) malloc(sizeof(double) * n);
  // fputs("Allocation successful!\n", stderr);
  
  memcpy(result->values[0], data->initial, sizeof(double) * n);
  // fputs("Initialization successful!\n", stderr);
  // fprintf(stderr, "%d\n%d\n", n);
  // double_array_fprint(stderr, n, result->values[0], "--raw");
  // double_array_fprint(stderr, n, result->values[0], "--raw");
  
  loop(result, lhs, rhs_final, rhs, free_part,
    data->boundary_dirichlet, data->g_dirichlet,
    data->boundary_neumann, data->g_neumann);
  /* NULL pointer checking */
  
  /* World breaks if the next line is omitted. For no reason!
   * It becomes 0 in main for some reason (it is never modified).
   */
  result->dimension = n;
  
  free(rhs_final);
  free(free_part);
  matrix_sparse_free(rhs);
  matrix_sparse_free(lhs);
  matrix_sparse_free(b);
  matrix_sparse_free(m_cbd_star_1_material);
  return result;
}
