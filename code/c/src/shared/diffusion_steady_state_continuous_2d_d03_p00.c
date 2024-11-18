#include <math.h>

#include "de_rham.h"
#include "diffusion_steady_state_continuous.h"

/*
[Example of steady-state diffusion in 2D via exterior calculus]

Let
  . M = {(x, y) in R | x^2 + y^2 = 1}
  . pi_1 = 1
  . f = -4 dx /\ dy
  . G be the boundary of M
  . G_D := G
  . G_N := {}
  . g_D = 1
  . g_N = 2 t dt (with respect to the (x, y) = (cos(t), sin(t)) coordinates)

The potential 0-form u and flow 1-form q are solutions to the problem
  . q = - *_1 pi_1 d_0 u
  . d q = -f
  . tr_{G_D, 0} u = g_D
  . tr_{G_N, 1} q = g_N

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

static int boundary_dirichlet(const double * x)
{
  return (on_unit_circle(x));
}

static double g_dirichlet(const double * x)
{
  return 1.;
}

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

static double norm_2d_squared(const double * point)
{
  double x, y;

  x = point[0];
  y = point[1];
  return x * x + y * y;
}

void diffusion_steady_state_continuous_2d_d03_p00_exact_potential_circular(
  double * potential, const mesh * m)
{
  de_rham_0(potential, m, norm_2d_squared);
}

/* Exact flow on the Forman subdivision */
void diffusion_steady_state_continuous_2d_d03_p00_exact_flow_circular(
  double * flow, const mesh * m, const matrix_sparse * m_bd_1)
{
  int i, index, j, na, nd;
  int * topology;
  double angle, coefficient, r0, value;
  double * m_bd_1_values;

  m_bd_1_values = m_bd_1->values;
  topology = m->cf->a4;
  i = 0;
  while (topology[i] == 0)
    i += 4;
  na = i / 2;
  nd = (m->cn[2] + na / 2) / na;
  r0 = 1. / (double) nd;
  angle = 2. * M_PI / (double) na;
  coefficient = 2 * r0 * r0 * angle;

  index = 0;
  /* edges to nodes */
  for (i = 1; i <= nd / 2; ++i)
  {
    /* rays */
    for (j = 0; j < na; ++j)
    {
      flow[index] = 0;
      ++index;
    }
    /* arcs */
    value = coefficient * (double) (4 * i * i);
    for (j = 0; j < na / 2; ++j)
    {
      flow[index + 0] = - value * m_bd_1_values[2 * index];
      flow[index + 1] =   value * m_bd_1_values[2 * index + 2];
      index += 2;
    }
  }
  /* inner faces to edges */
  value = coefficient;
  for (j = 0; j < na / 2; ++j)
  {
    flow[index + 0] = - value * m_bd_1_values[2 * index + 0]; /* arc */
    flow[index + 1] = 0;                                      /* ray */
    flow[index + 2] =   value * m_bd_1_values[2 * index + 4]; /* arc */
    index += 3;
  }
  /* outer faces to edges */
  for (i = 2; i <= nd / 2; ++i)
  {
    value = coefficient * (double) ((2 * i - 1) * (2 * i - 1));
    for (j = 0; j < na / 2; ++j)
    {
      flow[index + 0] = 0;                                      /* ray */
      flow[index + 1] = - value * m_bd_1_values[2 * index + 2]; /* arc */
      flow[index + 2] = 0;                                      /* ray */
      flow[index + 3] =   value * m_bd_1_values[2 * index + 6]; /* arc */
      index += 4;
    }
  }
}
