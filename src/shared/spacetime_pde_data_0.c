#include "diffusion_continuous.h"

/*
Solve the following problem:
Given a mesh M for the unit square, and the discrete Laplacian, solve:
  . du/dt = -Laplacian(u) + f    in the interior nodes of M
  . u = g_d                      at the boundary nodes of M
  . u(0) = initial               at all nodes of M
For this example it is assumed that f and g_d are time independent.
An artificial example with u(t, x_0, x_1) = x_0^2 + x_1^2 is taken.
This corresponds to f(x_0, x_1) = -4.
*/

static double pi_0(const double * x)
{
  return 1.;
}

static double initial(const double * x)
{
  return x[0] * x[0] + x[1] * x[1];
}

static double source(const double * x)
{
  return -4.;
}

static int boundary_dirichlet(const double * x)
{
  return x[0] == 0. || x[0] == 1. || x[1] == 0. || x[1] == 1.;
}

static double g_dirichlet(const double * x)
{
  return x[0] * x[0] + x[1] * x[1];
}

static int boundary_neumann(const double * x)
{
  return 0;
}

static double g_neumann(const double * x)
{
  return 0.;
}

const diffusion_continuous spacetime_pde_data_0 =
{
  .pi_0 = pi_0,
  .initial = initial,
  .source = source,
  .boundary_dirichlet = boundary_dirichlet,
  .g_dirichlet = g_dirichlet,
  .boundary_neumann = boundary_neumann,
  .g_neumann = g_neumann
};
