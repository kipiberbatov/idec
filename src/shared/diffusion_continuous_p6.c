#include "diffusion_continuous.h"

/*
Given a mesh M for the unit cube, and the discrete Laplacian, solve:
  . du/dt = -Laplacian(u) + f    in the interior nodes of M
  . u = g_d                      at the boundary nodes of M
  . u(0) = initial               at all nodes of M
In this example:
  . the initial temperature at the left side (x[0] = 0) is 100 degrees
  . the initialelsewhere (x[0] = 1) is 0 degrees
  . we maintain constant temperature at those two sides
  . on the other 4 sides we maintain constant zero flux
After a finite amount of time the temperature will be distributed linearly.
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
  if (x[0] == 0.)
    return 100.;
  else
    return 0.;
}

static double source(const double * x)
{
  return 0.;
}

static int boundary_dirichlet(const double * x)
{
  return
    (x[0] == 0. || x[0] == 1.) &&
    (0. <= x[1] && x[1] <= 1.) &&
    (0. <= x[2] && x[2] <= 1.);
}

static double g_dirichlet(const double * x)
{
  if (x[0] == 0.)
    return 100.;
  else
    return 0.;
}

static int boundary_neumann(const double * x)
{
  return
    ( ((x[1] == 0. || x[1] == 1.) && (0. <= x[2] && x[2] <= 1.)) ||
      ((x[2] == 0. || x[2] == 1.) && (0. <= x[1] && x[1] <= 1.))
    ) &&
    (0. < x[0] && x[0] < 1.);
}

static double g_neumann(const double * x)
{
  return 0.;
}

const diffusion_continuous diffusion_continuous_p6 =
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
