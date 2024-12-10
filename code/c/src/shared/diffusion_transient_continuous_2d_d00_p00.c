#include <math.h>

#include "de_rham.h"
#include "diffusion_transient_continuous.h"

/*
[Example of transient diffusion in 2D via exterior calculus]

Let
  . M = [0, 1]^2
  . pi_0 = 1
  . kappa_1 = 1
  . u_0 = {(0.5, 0.5) |-> 100, (x, y) |-> 0 for (x, y) != (0.5, 0.5)}
  . f = 0
  . G be the boundary of M
  . G_D := G
  . G_N := {}
  . g_D = 0
  . g_N = 0

The potential 0-form u and flow 1-form q are solutions to the problem
  . q = - *_1 kappa_1 d_0 u
  . D_t Q = d q + f
  . D_t Q = *_0 (D_t (pi_0 u))
  . tr_{G_D, 0} u = g_D
  . tr_{G_N, 1} q = g_N
  . u(t, x, y) = u_0(x, y)

The steady-state version of this problem has exact solution
  . u(x, y) = 0
  . q(x, y) = 0
*/

static double pi_0(const double * x)
{
  return 1.;
}

static double kappa_1(const double * x)
{
  return 1.;
}

#define EPSILON 0.00001

static double initial(const double * x)
{
  if (fabs(x[0] - 0.5) < EPSILON && fabs(x[1] - 0.5) < EPSILON)
    return 100.;
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

const diffusion_transient_continuous
diffusion_transient_continuous_2d_d00_p00 =
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

static double u(double t, const double * point)
{
  return 0.;
}

void diffusion_transient_continuous_2d_d00_p00_potential(
  double * potential, const mesh * m, double step, int number_of_steps)
{
  de_rham_sequence_0(potential, m, 0., step, number_of_steps, u);
}

void diffusion_transient_continuous_2d_d00_p00_flow(
  double * flow, const mesh * m, double step, int number_of_steps,
  const matrix_sparse * m_bd_1)
{
  int i, m_cn_1;

  m_cn_1 = m->cn[1];
  for (i = 0; i < m_cn_1 * (number_of_steps + 1); ++i)
    flow[i] = 0.;
}
