#include <math.h>

#include "diffusion_transient_continuous.h"

/*
Solve the following problem:
Given a mesh M for the unit square, and the discrete Laplacian, solve:
  . du/dt = -Laplacian(u) + f    in the interior nodes of M
  . u = g_d                      at the boundary nodes of M
  . u(0) = initial               at all nodes of M
In this example:
  . we have zero degrees everywhere except at the central node where it is 100
  . we maintain zero degrees at the boundary
After a finite amount of time the temperature will be zero degrees everywhere.
*/

static double pi_0(const double * x)
{
  return 1.;
}

static double pi_1(const double * x)
{
  return 1.;
}

static double initial(const double * x)
{
  if (fabs(x[0] - 0.5) < 0.00001 && fabs(x[1] - 0.5) < 0.00001)
    return 100;
  return 0;
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

const diffusion_transient_continuous diffusion_transient_continuous_p2 =
{
  pi_0,
  pi_1,
  initial,
  source,
  boundary_dirichlet,
  g_dirichlet,
  boundary_neumann,
  g_neumann
};
