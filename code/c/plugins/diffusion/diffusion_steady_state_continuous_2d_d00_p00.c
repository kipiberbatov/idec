#include "de_rham.h"
#include "diffusion_steady_state_continuous.h"

/*
[Example of steady-state diffusion in 2D via exterior calculus]

Let
  . M = [0, 1]^2
  . kappa_1 = 1
  . f = 0
  . G_D be the boundary of M
  . G_N = {}
  . g_D = 0

The potential 0-form u and flow rate 1-form q are solutions to the problem
  . q = - *_1 kappa_1 d_0 u
  . d q = -f
  . tr_{G_D, 0} u = g_D
  . tr_{G_N, 1} q = g_N

This problem has exact solution
  . u(x, y) = 0
  . q(x, y) = 0
*/

static double kappa_1(const double * x)
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

const struct diffusion_steady_state_continuous
diffusion_steady_state_continuous_2d_d00_p00 =
{
  kappa_1,
  source,
  boundary_dirichlet,
  g_dirichlet,
  boundary_neumann,
  NULL
};

static double u(const double * point)
{
  return 0.;
}

void diffusion_steady_state_continuous_2d_d00_p00_potential(
  double * potential, const struct mesh * m)
{
  de_rham_0(potential, m, u);
}

void diffusion_steady_state_continuous_2d_d00_p00_flow_rate(
  double * flow_rate,
  const struct mesh * m,
  const struct matrix_sparse * m_bd_1)
{
  int i, m_cn_1;

  m_cn_1 = m->cn[1];
  for (i = 0; i < m_cn_1; ++i)
    flow_rate[i] = 0.;
}
