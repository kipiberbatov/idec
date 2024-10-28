#include "diffusion_steady_state_continuous.h"

/*
We solve the following continuous steady state diffusion problem for (u^0, q^1):
. q^1 = *_1 pi_1 d_0 u^0
. d_1 q^1 = -f^0 
. tr_{G_D, 0} u^0 = g_D^0
. tr_{G_N, 1} q^1 = g_N^1

with the following data
. M = [0, 1]^2 with boundary G
. pi_1 = 1
. f^2 = -2 dx /\ dy
. G_D := {(x, y) in G | x = 0 or x = 1}
. G_N := {(x, y) in G | y = 0 or y = 1}
. g_D^0 = 0
. g_N^1 = 0

This problem has exact solution
. u^0(x, y) = x (x - 1)
. q^1(x, y) = (2 x - 1) dy
*/

static double pi_1(const double * x)
{
  return 1.;
}

static double source(const double * x)
{
  return -2.;
}

static int boundary_dirichlet(const double * x)
{
  return ((x[0] == 0 || x[0] == 1) && 0 <= x[1] && x[1] <= 1);
}

static double g_dirichlet(const double * x)
{
  return 0.;
}

static int boundary_neumann(const double * x)
{
  return ((x[1] == 0 || x[1] == 1) && 0 <= x[0] && x[0] <= 1);
}

static double g_neumann(const double * x)
{
  return 0.;
}

const diffusion_steady_state_continuous
diffusion_steady_state_continuous_2d_p00 =
{
  pi_1,
  source,
  boundary_dirichlet,
  g_dirichlet,
  boundary_neumann,
  g_neumann
};
