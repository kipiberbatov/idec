#ifndef _diffusion_steady_state_discrete_h
#define _diffusion_steady_state_discrete_h

struct jagged1;

struct diffusion_steady_state_discrete
{
  int number_of_cells_1;
  int number_of_cells_dm1;
  int number_of_cells_d;
  double * conductivity;
  double * dual_conductivity;
  double * production_rate;
  struct jagged1 * boundary_dirichlet_dm1;
  struct jagged1 * boundary_dirichlet_0;
  double * g_dirichlet;
  struct jagged1 * boundary_neumann_dm1;
  double * g_neumann;
};

#endif /* _diffusion_steady_state_discrete_h */
