#include "de_rham.h"
#include "diffusion_steady_state_continuous.h"

/*
[Example of steady-state diffusion in 3D via exterior calculus]

Let
  . M = [0, 1]^3
  . kappa_1 = 2
  . f = 12 dx /\ dy /\ dz
  . G be the boundary of M
  . G_D = {(x, y, z) in G | y in {0, 1} or z in {0, 1}}
  . G_N = {(x, y, z) in G | x in {0, 1}}
  . g_D(x, y, z) = x^2 + y^2 + z^2
  . g_N = {(0, y, z) |-> 0, (1, y, z) |-> 4 d y /\ dz}

The potential 0-form u and flow 1-form q are solutions to the problem
  . q = *_1 kappa_1 d_0 u
  . d q = -f
  . tr_{G_D, 0} u = g_D
  . tr_{G_N, 2} q = g_N

This problem has exact solution
  . u(x, y, z) = x^2 + y^2 + z^2
  . q(x, y, z) = 4 (x dy /\ dz + y dz /\ dx + z dx /\ dy)
*/

static double square(double x){return x * x;}

static double kappa_1(const double * x)
{
  return 2.;
}

static double source(const double * x)
{
  return -12;
}

static int boundary_dirichlet(const double * x)
{
  return
    ( ((x[1] == 0. || x[1] == 1.) && (0. <= x[2] && x[2] <= 1.)) ||
      ((x[2] == 0. || x[2] == 1.) && (0. <= x[1] && x[1] <= 1.))
    ) &&
    (0. <= x[0] && x[0] <= 1.);
}

static double g_dirichlet(const double * x)
{
  return square(x[0]) + square(x[1]) + square(x[2]);
}

static int boundary_neumann(const double * x)
{
  return
    (x[0] == 0. || x[0] == 1.) &&
    (0. <= x[1] && x[1] <= 1.) &&
    (0. <= x[2] && x[2] <= 1.);
}

static double g_neumann(const double * x)
{
  if (x[0] == 0.)
    return 0;
  else
    return 4;
}

const struct diffusion_steady_state_continuous
diffusion_steady_state_continuous_3d_d00_p01 =
{
  kappa_1,
  source,
  boundary_dirichlet,
  g_dirichlet,
  boundary_neumann,
  g_neumann
};

static double u(const double * point)
{
  return square(point[0]) + square(point[1]) + square(point[2]);
}

void diffusion_steady_state_continuous_3d_d00_p01_potential(
  double * potential, const struct mesh * m)
{
  de_rham_0(potential, m, u);
}
