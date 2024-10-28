#include "diffusion_steady_state_continuous.h"

/*
We solve the heat equation for (u, q):
. q = - * pi_1 d u
. d q = -f 
. tr_{G_D} u = g_D
. tr_{G_N} q = g_N

with the following data
. M = "unit circle"
. pi_1 = 1
. f = -4 dx /\ dy
. G_D := {x in M | x[0] >= 0}
. G_N := {x in M | x[0] <= 0}
. g_D = 1
. g_N = 2 t dt (with respect to the (x[0], x[1]) = (cos(t), sin(t)) coordinates)

This problem has exact solution
. u(x, y) = x^2 + y^2
. q(x, y) = - 2 y dx + 2 x dy
*/

#define EPSILON 0.000001

static int on_unit_circle(const double * x)
{
  double error = x[0] * x[0] + x[1] * x[1] - 1;
  if (error < EPSILON && -error < EPSILON)
    return 1;
  return 0;
}

static double pi_1(const double * x)
{
  return 1.;
}

static double source(const double * x)
{
  return -4.;
}

// static int boundary_dirichlet(const double * x)
// {
//   return (on_unit_circle(x) && x[0] > -EPSILON );
// }

/* in pure Dirichlet problem */

static int boundary_dirichlet(const double * x)
{
  return (on_unit_circle(x));
}


static double g_dirichlet(const double * x)
{
  return 1.;
}

// static int boundary_neumann(const double * x)
// {
//   return (on_unit_circle(x) && x[0] < EPSILON);
// }

/* in pure Dirichlet problem */

static int boundary_neumann(const double * x)
{
  return 0;
}


static double g_neumann(const double * x)
{
  return 2.;
}

const diffusion_steady_state_continuous
diffusion_steady_state_continuous_2d_d03_p00 =
{
  pi_1,
  source,
  boundary_dirichlet,
  g_dirichlet,
  boundary_neumann,
  g_neumann
};
