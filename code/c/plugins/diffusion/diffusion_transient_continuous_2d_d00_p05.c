#include <math.h>

#include "diffusion_transient_continuous.h"

/*
Solve the following problem:
Given a mesh M for the unit square, and the discrete Laplacian, solve:
  . du/dt = -Laplacian(u) + f    in the interior nodes of M
  . u = g_d                      at the boundary nodes of M
  . u(0) = initial               at all nodes of M
For this example it is assumed that f and g_d are time independent.
An artificial example with
  u(t, x, y) = exp(-2 * pi^2) sin(pi x) sin(pi y)
is taken.
This corresponds to f = 0, g_d = 0, initial = sin(pi x) sin(pi y).
*/

static double pi_0(const double * x)
{
  return 1.;
}

static double kappa_1(const double * x)
{
  return 1.;
}

static double initial(const double * x)
{
  return sin(M_PI * x[0]) * sin(M_PI * x[1]);
}

static double source(const double * x)
{
  return 0.;
}

static int boundary_dirichlet(const double * x)
{
  return x[0] == 0. || x[0] == 1. || x[1] == 0. || x[1] == 1.;
}

static double g_dirichlet(const double * x)
{
  return 0.;
}

static int boundary_neumann(const double * x)
{
  return 0;
}

static double g_neumann(const double * x)
{
  return 0.;
}

const struct diffusion_transient_continuous
diffusion_transient_continuous_2d_d00_p05 =
{
  pi_0,
  kappa_1,
  initial,
  source,
  boundary_dirichlet,
  g_dirichlet,
  boundary_neumann,
  g_neumann
};
