/*
Solves dynamic partial differential eqation, first order with respect to time.
At any moment the participating operators are linear.
The next iteration is find using the trapezoidal rule
*/

#include <errno.h>
#include <stdlib.h>
#include <string.h>

#include "double.h"
#include "int.h"
#include "mesh.h"
#include "spacetime_pde.h"

/* update rhs_final with the boundary conditions */
static void double_array_partial_update(
  double * rhs_final,
  const jagged1 * boundary_positions,
  const double * g)
{
  int j, j_local, size;
  int * values;

  size = boundary_positions->a0;
  values = boundary_positions->a1;

  for (j_local = 0; j_local < size; ++j_local)
  {
    j = values[j_local];
    rhs_final[j] = g[j_local];
  }
}

double * spacetime_pde_dirichlet_boundary_vector(
  int m_dim_embedded,
  const double * m_coord,
  const jagged1 * m_nodes_bd,
  scalar_field g_d)
{
  int j, j_loc, m_nodes_bd_a0;
  int * m_nodes_bd_a1;
  double * result;
  
  m_nodes_bd_a0 = m_nodes_bd->a0;
  m_nodes_bd_a1 = m_nodes_bd->a1;
  result = (double *) malloc(sizeof(double) * m_nodes_bd_a0);
  if (errno)
    return NULL;
  
  for (j_loc = 0; j_loc < m_nodes_bd_a0; ++j_loc)
  {
    j = m_nodes_bd_a1[j_loc];
    result[j_loc] = g_d(m_coord + m_dim_embedded * j);
  }
  return result;
}

static void matrix_sparse_set_identity_rows(
  matrix_sparse * lhs,
  const jagged1 * boundary_positions)
{
  int column_j_nonzero_total, i, i_local, j;
  int * column_j_row_indices;
  double * column_j_values;
  
  for (j = 0; j < lhs->cols; ++j)
  {
    column_j_nonzero_total = lhs->cols_total[j + 1] - lhs->cols_total[j];
    column_j_row_indices = lhs->row_indices + lhs->cols_total[j];
    column_j_values = lhs->values + lhs->cols_total[j];
    for (i_local = 0; i_local < column_j_nonzero_total; ++i_local)
    {
      i = column_j_row_indices[i_local];
      if (jagged1_member(boundary_positions, i))
      {
        if (i == j)
          column_j_values[i_local] = 1.;
        else
          column_j_values[i_local] = 0.;
      }
    }
  }
}

double ** spacetime_pde_time_order_1_linear_trapezoid_method(
  const double * u0,
  const matrix_sparse * a,
  const matrix_sparse * b,
  const double * c,
  const double * g,
  const jagged1 * boundary_positions,
  double time_step,
  int number_of_steps)
{
  int i, n;
  double * free_part, * rhs_final;
  double ** result;
  matrix_sparse * lhs, * rhs;
  
  n = a->rows;
  
  lhs = matrix_sparse_linear_combination(a, b, 1, - time_step / 2);
  /* NULL pointer checking */
  
  rhs = matrix_sparse_linear_combination(a, b, 1, time_step / 2);
  /* NULL pointer checking */
  
  free_part = (double *) malloc(sizeof(double) * n);
  /* NULL pointer checking */
  
  memcpy(free_part, c, sizeof(double) * n);
  double_array_multiply_with(free_part, n, time_step);
  
  matrix_sparse_set_identity_rows(lhs, boundary_positions);
  
  rhs_final = (double *) malloc(sizeof(double) * n);
  
  result = (double **) malloc(sizeof(double *) * (number_of_steps + 1));
  /* NULL pointer checking */
  
  for (i = 0; i <= number_of_steps; ++i)
  {
    result[i] = (double *) malloc(sizeof(double) * n);
    /* NULL pointer checking */
  }
  
  memcpy(result[0], u0, sizeof(double) * n);
  
  for (i = 0; i < number_of_steps; ++ i)
  {
    memcpy(rhs_final, free_part, sizeof(double) * n);
    
    matrix_sparse_vector_multiply_add(rhs_final, rhs, result[i]);

    double_array_partial_update(rhs_final, boundary_positions, g);

    memcpy(result[i + 1], rhs_final, sizeof(double) * n);

    matrix_sparse_linear_solve(lhs, result[i + 1], "--lu");
  }
  
  free(rhs_final);
  free(free_part);
  matrix_sparse_free(rhs);
  matrix_sparse_free(lhs);
  return result;
}

double ** spacetime_pde_heat_equation_solve_trapezoidal_method(
  const matrix_sparse * m_laplacian,
  int m_dim_embedded,
  const double * m_coord,
  const jagged1 * m_nodes_bd,
  scalar_field initial,
  scalar_field f,
  scalar_field g_d,
  double time_step,
  int number_of_steps)
{
  int i, n;
  double * u0;
  matrix_sparse * a;
  double * c;
  double * g;
  double ** result;

  n = m_laplacian->cols;
  
  u0 = (double *) malloc(sizeof(double) * n);
  /* NULL pointer checking */

  for (i = 0; i < n; ++i)
    u0[i] = initial(m_coord + m_dim_embedded * i);

  c = (double *) malloc(sizeof(double) * n);
  /* NULL pointer checking */

  for (i = 0; i < n; ++i)
    c[i] = f(m_coord + m_dim_embedded * i);

  g = spacetime_pde_dirichlet_boundary_vector(
    m_dim_embedded,
    m_coord,
    m_nodes_bd,
    g_d);
  /* NULL pointer checking */

  a = matrix_sparse_identity(n);
  /* NULL pointer checking */

  result = spacetime_pde_time_order_1_linear_trapezoid_method(
    u0,
    a,
    m_laplacian,
    c,
    g,
    m_nodes_bd,
    time_step,
    number_of_steps);
  /* NULL pointer checking */

  free(a);
  free(g);
  free(c);
  free(u0);
  return result;
}

/*
Solves heat equation with Dirichlet boundary conditions.
Command-line arguments give necessary matrices.
Scalar fields are given in main file.
*/
int spacetime_pde_heat_equation_runner(
  int argc,
  char * argv[],
  scalar_field f,
  scalar_field g_d,
  scalar_field initial)
{
  char * m_format, * m_laplacian_0_format, * m_laplacian_0_name, * m_name;
  double ** result;
  mesh * m;
  jagged1 * m_nodes_bd;
  matrix_sparse * m_laplacian_0;
  int i, number_of_steps;
  double time_step;
  
  if (argc != 7)
  {
    errno = EINVAL;
    fputs("main - the number of command-line arguments must be 6\n", stderr);
    goto end;
  }
  
  m_format = argv[1];
  m_name = argv[2];
  m = mesh_fscan_by_name(m_name, m_format);
  if (errno)
  {
    fputs("main - cannot scan m\n", stderr);
    goto end;
  }
  
  m->fc = mesh_fc(m);
  if (errno)
  {
    fputs("main - cannot calculate m->fc\n", stderr);
    goto m_free;
  }
  
  m_nodes_bd = mesh_bd_nodes(m);
  if (errno)
  {
    fputs("main - cannot calculate m_nodes_bd\n", stderr);
    goto m_free;
  }
  
  m_laplacian_0_format = argv[3];
  m_laplacian_0_name = argv[4];
  
  m_laplacian_0 = 
    matrix_sparse_fscan_by_name(m_laplacian_0_name, m_laplacian_0_format);
  if (errno)
  {
    fputs("main - cannot calculate m_laplacian[0]\n", stderr);
    goto m_nodes_bd_free;
  }
  matrix_sparse_scalar_multiply(m_laplacian_0, -1);

  time_step = double_sscan(argv[5]);
  if (errno)
  {
    fprintf(stderr, "Error in %s: cannot scan time_step\n", __func__);
    goto m_laplacian_0_free;
  }

  number_of_steps = int_sscan(argv[6]);
  if (errno)
  {
    fprintf(stderr, "Error in %s: cannot scan number_of_steps\n", __func__);
    goto m_laplacian_0_free;
  }
  
  result = spacetime_pde_heat_equation_solve_trapezoidal_method(
    m_laplacian_0,
    m->dim_embedded,
    m->coord,
    m_nodes_bd,
    initial,
    f,
    g_d,
    time_step,
    number_of_steps);
  
  if (errno)
  {
    fputs("main - cannot calculate x\n", stderr);
    goto m_laplacian_0_free;
  }
  
  for (i = 0; i <= number_of_steps; ++i)
  {
    double_array_fprint(stdout, m_laplacian_0->cols, result[i], "--raw");
    fputs("\n", stdout);
  }

  free(result);
m_laplacian_0_free:
  matrix_sparse_free(m_laplacian_0);
m_nodes_bd_free:
  jagged1_free(m_nodes_bd);
m_free:
  mesh_free(m);
end:
  return errno;
}






// static double * matrix_sparse_part_ptr(const matrix_sparse * a, int i, int j)
// {
//   int i_loc;
//   int * a_cols_total, * a_row_indices;
//   double * a_values;
//
//   a_cols_total = a->cols_total;
//   a_row_indices = a->row_indices;
//   a_values = a->values;
//   for (i_loc = a_cols_total[j]; i_loc < a_cols_total[j + 1]; ++i_loc)
//     if (a_row_indices[i_loc] == i)
//       return a_values + i_loc;
//   return NULL;
// }
//
// static void matrix_sparse_set_neumann_rows(
//   matrix_sparse * lhs,
//   const mesh * m,
//   const jagged1 * m_boundary_nodes)
// {
//   int i, i_local, j, j_local, size;
//   double * coefficients, * position;
//   jagged1 * neighbors;
//
//   for (i_local = 0; i_local < m_boundary_nodes->a0; ++i_local)
//   {
//     i = m_boundary_nodes->a1[i_local];
//     // jagged2_part1(&m_fc_0_1_i, &m_fc_0_1, i);
//     // size = m_fc_0_1_i.a0;
//     neighbors = mesh_neighboring_nodes(m, i);
//     // NULL
//     size = neighbors->a1;
//
//     coefficients = mesh_boundary_neumann_coefficients(m, i);
//     // NULL
//
//     for (j_local = 0; j_local < size; ++j_local)
//     {
//       j = neighbors.a1[i];
//       position = matrix_sparse_part_ptr(lhs, i, j);
//       if (i != j)
//         *position = coefficients[j_local];
//       else
//       {
//         *position = 0;
//         for (s = 0; s < size; ++s)
//           *position -= coefficients[s];
//       }
//     }
//   }
// }
//
// double ** spacetime_pde_full_time_order_1_linear_trapezoid_method(
//   const mesh * m,
//   const double * u0,
//   const matrix_sparse * a,
//   const matrix_sparse * b,
//   const double * c,
//   const double * g_d,
//   const double * g_n,
//   const jagged1 * boundary_dirichlet,
//   const jagged1 * boundary_neumann,
//   double time_step,
//   int number_of_steps)
// {
//   int i, n;
//   double * free_part, * rhs_final;
//   double ** result;
//   matrix_sparse * lhs, * rhs;
//
//   n = a->rows;
//
//   lhs = matrix_sparse_linear_combination(a, b, 1, - time_step / 2);
//   /* NULL pointer checking */
//
//   rhs = matrix_sparse_linear_combination(a, b, 1, time_step / 2);
//   /* NULL pointer checking */
//
//   free_part = (double *) malloc(sizeof(double) * n);
//   /* NULL pointer checking */
//
//   memcpy(free_part, c, sizeof(double) * n);
//   double_array_multiply_with(free_part, n, time_step);
//
//   matrix_sparse_set_identity_rows(lhs, boundary_dirichlet);
//
//   matrix_sparse_set_neumann_rows(lhs, m, boundary_neumann);
//
//   rhs_final = (double *) malloc(sizeof(double) * n);
//
//   result = (double **) malloc(sizeof(double *) * (number_of_steps + 1));
//   /* NULL pointer checking */
//
//   for (i = 0; i <= number_of_steps; ++i)
//   {
//     result[i] = (double *) malloc(sizeof(double) * n);
//     /* NULL pointer checking */
//   }
//
//   memcpy(result[0], u0, sizeof(double) * n);
//
//   for (i = 0; i < number_of_steps; ++ i)
//   {
//     memcpy(rhs_final, free_part, sizeof(double) * n);
//
//     matrix_sparse_vector_multiply_add(rhs_final, rhs, result[i]);
//
//     double_array_partial_update(rhs_final, boundary_dirichlet, g_d);
//     double_array_partial_update(rhs_final, boundary_neumann, g_n);
//
//     memcpy(result[i + 1], rhs_final, sizeof(double) * n);
//
//     matrix_sparse_linear_solve(lhs, result[i + 1], "--lu");
//   }
//
//   free(rhs_final);
//   free(free_part);
//   matrix_sparse_free(rhs);
//   matrix_sparse_free(lhs);
//   return result;
// }
//
// double ** spacetime_pde_full_heat_equation_solve_trapezoidal_method(
//   const mesh * m,
//   const matrix_sparse * m_laplacian,
//   int m_dim_embedded,
//   const double * m_coord,
//   scalar_field initial,
//   scalar_field f,
//   const jagged1 * boundary_dirichlet,
//   scalar_field g_d,
//   const jagged1 * boundary_neumann,
//   scalar_field g_n,
//   double time_step,
//   int number_of_steps)
// {
//   int i, n;
//   double * u0;
//   matrix_sparse * a;
//   double * c;
//   double * gv_d;
//   double * gv_n;
//   double ** result;
//
//   n = m_laplacian->cols;
//
//   u0 = (double *) malloc(sizeof(double) * n);
//   /* NULL pointer checking */
//
//   for (i = 0; i < n; ++i)
//     u0[i] = initial(m_coord + m_dim_embedded * i);
//
//   c = (double *) malloc(sizeof(double) * n);
//   /* NULL pointer checking */
//
//   for (i = 0; i < n; ++i)
//     c[i] = f(m_coord + m_dim_embedded * i);
//
//   gv_d = spacetime_pde_dirichlet_boundary_vector(
//     m_dim_embedded,
//     m_coord,
//     m_boundary_dirichlet,
//     g_d);
//   /* NULL pointer checking */
//
//   gv_n = spacetime_pde_dirichlet_boundary_vector(
//     m_dim_embedded,
//     m_coord,
//     m_boundary_neumann,
//     g_n);
//   /* NULL pointer checking */
//
//   a = matrix_sparse_identity(n);
//   /* NULL pointer checking */
//   // double ** spacetime_pde_full_time_order_1_linear_trapezoid_method(
//   //   const mesh * m,
//   //   const double * u0,
//   //   const matrix_sparse * a,
//   //   const matrix_sparse * b,
//   //   const double * c,
//   //   const double * g_d,
//   //   const double * g_n,
//   //   const jagged1 * boundary_dirichlet,
//   //   const jagged1 * boundary_neumann,
//   //   double time_step,
//   //   int number_of_steps)
//   result = spacetime_pde_fulltime_order_1_linear_trapezoid_method(
//     m,
//     u0,
//     a,
//     m_laplacian,
//     c,
//     gv_d,
//     gv_n
//     boundary_dirichlet,
//     boundary_neumann,
//     time_step,
//     number_of_steps);
//   /* NULL pointer checking */
//
//   free(a);
//   free(g);
//   free(c);
//   free(u0);
//   return result;
// }
//
// /*
// Solves heat equation with Dirichlet boundary conditions.
// Command-line arguments give necessary matrices.
// Scalar fields are given in main file.
// */
// int spacetime_pde_heat_equation_runner(
//   int argc,
//   char * argv[],
//   scalar_field f,
//   scalar_field initial
//   scalar_field g_d,
//   scalar_field g_n,
//   int (*dirichlet)(const double *),
//   int (*neumann)(const double *))
// {
//   char * m_format, * m_laplacian_0_format, * m_laplacian_0_name, * m_name;
//   double ** result;
//   mesh * m;
//   jagged1 * m_nodes_bd;
//   matrix_sparse * m_laplacian_0;
//   int i, number_of_steps;
//   double time_step;
//
//   if (argc != 7)
//   {
//     errno = EINVAL;
//     fputs("main - the number of command-line arguments must be 6\n", stderr);
//     goto end;
//   }
//
//   m_format = argv[1];
//   m_name = argv[2];
//   m = mesh_fscan_by_name(m_name, m_format);
//   if (errno)
//   {
//     fputs("main - cannot scan m\n", stderr);
//     goto end;
//   }
//
//   m->fc = mesh_fc(m);
//   if (errno)
//   {
//     fputs("main - cannot calculate m->fc\n", stderr);
//     goto m_free;
//   }
//
//   m_nodes_bd = mesh_bd_nodes(m);
//   if (errno)
//   {
//     fputs("main - cannot calculate m_nodes_bd\n", stderr);
//     goto m_free;
//   }
//
//   m_laplacian_0_format = argv[3];
//   m_laplacian_0_name = argv[4];
//
//   m_laplacian_0 =
//     matrix_sparse_fscan_by_name(m_laplacian_0_name, m_laplacian_0_format);
//   if (errno)
//   {
//     fputs("main - cannot calculate m_laplacian[0]\n", stderr);
//     goto m_nodes_bd_free;
//   }
//   matrix_sparse_scalar_multiply(m_laplacian_0, -1);
//
//   time_step = double_sscan(argv[5]);
//   if (errno)
//   {
//     fprintf(stderr, "Error in %s: cannot scan time_step\n", __func__);
//     goto m_laplacian_0_free;
//   }
//
//   number_of_steps = int_sscan(argv[6]);
//   if (errno)
//   {
//     fprintf(stderr, "Error in %s: cannot scan number_of_steps\n", __func__);
//     goto m_laplacian_0_free;
//   }
//   // spacetime_pde_full_heat_equation_solve_trapezoidal_method(
//   //   const mesh * m,
//   //   const matrix_sparse * m_laplacian,
//   //   int m_dim_embedded,
//   //   const double * m_coord,
//   //   scalar_field initial,
//   //   scalar_field f,
//   //   const jagged1 * boundary_dirichlet,
//   //   scalar_field g_d,
//   //   const jagged1 * boundary_neumann,
//   //   scalar_field g_n,
//   //   double time_step,
//   //   int number_of_steps)
//   result = spacetime_pde_full_heat_equation_solve_trapezoidal_method(
//     m,
//     m_laplacian_0,
//     m->dim_embedded,
//     m->coord,
//     initial,
//     f,
//     boundary_dirichlet,
//     g_d,
//     boundary_neumann,
//     g_d,
//     time_step,
//     number_of_steps);
//
//   if (errno)
//   {
//     fputs("main - cannot calculate x\n", stderr);
//     goto m_laplacian_0_free;
//   }
//
//   for (i = 0; i <= number_of_steps; ++i)
//   {
//     double_array_fprint(stdout, m_laplacian_0->cols, result[i], "--raw");
//     fputs("\n", stdout);
//   }
//
//   free(result);
// m_laplacian_0_free:
//   matrix_sparse_free(m_laplacian_0);
// m_nodes_bd_free:
//   jagged1_free(m_nodes_bd);
// m_free:
//   mesh_free(m);
// end:
//   return errno;
// }
