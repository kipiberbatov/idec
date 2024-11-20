#include "diffusion_transient_continuous.h"

/*
Given a mesh M for the unit cube, and the discrete Laplacian, solve:
  . d(pi_0 u)/dt = -d_0^* pi_1 d_0 u + f   in the interior nodes of M
  . u = g_d                                at the Dirichlet boundary nodes of M
  . (L^* u). (hat (d u)) = g_n             at the Neumann boundary nodes of M
  . u(0) = initial                         at all nodes of M
In this example:
  . the initial potential at the left face (x[0] = 0) is 100 degrees
    the initial potential at the right face (x[0] = 1) is 0 degrees
  . we maintain constant potential at those two face
  . on the other 4 faces we maintain constant zero flux
After a finite amount of time the potential will be distributed linearly.
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
    (0. <= x[0] && x[0] <= 1.);
}

static double g_neumann(const double * x)
{
  return 0.;
}

const diffusion_transient_continuous
diffusion_transient_continuous_3d_d00_p00 =
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
