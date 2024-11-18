#include "de_rham.h"
#include "diffusion_steady_state_continuous.h"

/*
[Example of steady-state diffusion in 2D via exterior calculus]

Let
  . M = [0, 1]^2
  . pi_1 = 1
  . f = 0
  . G be the boundary of M
  . G_D := G
  . G_N := {}
  . g_D = 0
  . g_N = 0

The potential 0-form u and flow 1-form q are solutions to the problem
  . q = - *_1 pi_1 d_0 u
  . d q = -f
  . tr_{G_D, 0} u = g_D
  . tr_{G_N, 1} q = g_N

This problem has exact solution
  . u(x, y) = 0
  . q(x, y) = 0
*/

static double pi_1(const double * x)
{
  return 1.;
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

const diffusion_steady_state_continuous
diffusion_steady_state_continuous_2d_d00_p00 =
{
  pi_1,
  source,
  boundary_dirichlet,
  g_dirichlet,
  boundary_neumann,
  g_neumann
};

static double u(const double * point)
{
  return 0.;
}

void diffusion_steady_state_continuous_2d_d00_p00_potential(
  double * potential, const mesh * m)
{
  de_rham_0(potential, m, u);
}

void diffusion_steady_state_continuous_2d_d00_p00_flow(
  double * flow, const mesh * m, const matrix_sparse * m_bd_1)
{
  int i, m_cn_1;

  m_cn_1 = m->cn[1];
  for (i = 0; i < m_cn_1; ++i)
    flow[i] = 0.;
}
