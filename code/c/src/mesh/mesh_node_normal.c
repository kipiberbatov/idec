#include <math.h>
#include <string.h>

#include "double.h"
#include "matrix.h"
#include "mesh.h"

#define EPSILON .000001

/* find normals to non-parallel hyperfaces */
static void mesh_node_hyperface_normals(
  double * hyperface_normals,
  int * number_of_non_prallell_hyperfaces,
  int d,
  const double * m_coord,
  const jagged1 * boundary_hyperfaces,
  const jagged2 * m_cf_dm1_0,
  const jagged1 * m_fc_0_dm1_i);

/* make all normals to point outwards */
static void mesh_node_normal_exterior(
  double * hyperface_normals,
  const mesh * m,
  int d,
  double m_size,
  int number_of_non_prallell_hyperfaces,
  double * m_coord_i);

/* in $normal$ store the average of hyperfaces exterior normals */
static void hyperface_normals_average(
  double * normal, int d, int size, const double * hyperface_normals);

/*
Constants:
  . $m$ is of type @mesh and let $d$ be its dimension (intrinsic == embedding);
  . $boundary_hyperfaces$ is a @jagged1 array with the indices of boundary
    hyperfaces of $m$;
  . $m_fc_0_dm1$ is the node-hyperface @jagged2 array;
  . $m_size$ of type @double is the minimal distance between points in $m$;
  . $i$ is an @int representing index of a boundary node in $m$.
Modified:
  . $normal$ is a pointer to a @double array of length $d$. It is overwritten
    with the external normal vector (in a generalized sense) to the $i$-th node
    of $m$;
  . {$hyperface_normals$ : (double *)} stores disjoint (up to sign) normal
    vectors to the hyperfaces adjacent to $N_i$.
Algorithm:
  . start with an empty list of normal vectors at a point;
  . find all hyperfaces that are adjacent to $N_i$;
  . loop through them:
      . skip interior ones;
      . for any adjacent boundary hyperface, find a unit normal vector and add
        it to the list if it is not presented (or its opposute) yet;
      . check if it points outwards -- if not, change sign
        (that is not a trivial task in general);
  . find an average of those normals -> here normalized arithmetic mean is used
    (note that in 3D solid angles some angle trisector may be better);
  . the result is stored in $normal$.
*/
void mesh_node_normal(
  double * normal,
  double * hyperface_normals,
  const mesh * m,
  const jagged1 * boundary_hyperfaces,
  const jagged2 * m_cf_dm1_0,
  const jagged2 * m_fc_0_dm1,
  double m_size,
  int i)
{
  int d, number_of_non_prallell_hyperfaces;
  double * m_coord, * m_coord_i;
  jagged1 m_fc_0_dm1_i;

  d = m->dim;
  m_coord = m->coord;

  /* find all hyperfaces that are adjacent to $N_i$ */
  jagged2_part1(&m_fc_0_dm1_i, m_fc_0_dm1, i);

  number_of_non_prallell_hyperfaces = 0;
  /* find nonparallel hyperfaces and their normals */
  mesh_node_hyperface_normals(
    hyperface_normals, &number_of_non_prallell_hyperfaces,
    d, m_coord, boundary_hyperfaces, m_cf_dm1_0, &m_fc_0_dm1_i);

  /* make all found normals to be outwards pointing */
  m_coord_i = m_coord + d * i;
  mesh_node_normal_exterior(
    hyperface_normals,
    m, d, m_size, number_of_non_prallell_hyperfaces, m_coord_i);

  /* in $normal$ store the average of hyperfaces exterior normals */
  hyperface_normals_average(
    normal, d, number_of_non_prallell_hyperfaces, hyperface_normals);
}

/******************** implementation of helping functions *********************/
static double double_square(double x) {return x * x;}

static int normal_in_list(
  int d, int size, const double * normals, const double * hyperface_normal)
{
  int i, p;
  double difference_i, sum_i;
  const double * normal_i;

  for (i = 0; i < size; ++i)
  {
    sum_i = 0;
    difference_i = 0;
    normal_i = normals + d * i;
    for (p = 0; p < d; ++p)
    {
      sum_i += double_square(hyperface_normal[p] + normal_i[p]);
      difference_i += double_square(hyperface_normal[p] - normal_i[p]);
    }
    if (sum_i < EPSILON * EPSILON || difference_i < EPSILON * EPSILON)
      return 1;
  }
  return 0;
}

static void mesh_node_hyperface_normals(
  double * hyperface_normals,
  int * number_of_non_prallell_hyperfaces,
  int d,
  const double * m_coord,
  const jagged1 * boundary_hyperfaces,
  const jagged2 * m_cf_dm1_0,
  const jagged1 * m_fc_0_dm1_i)
{
  int j, j_local, m_fc_0_dm1_i_a0, p, t;
  int * m_fc_0_dm1_i_a1;
  double hyperface_normal[3];
  double * hyperface_normal_t;

  m_fc_0_dm1_i_a0 = m_fc_0_dm1_i->a0;
  m_fc_0_dm1_i_a1 = m_fc_0_dm1_i->a1;
  t = 0;
  for (j_local = 0; j_local < m_fc_0_dm1_i_a0; ++j_local)
  {
    j = m_fc_0_dm1_i_a1[j_local];
    /* skip interior hyperfaces */
    if (!jagged1_member(boundary_hyperfaces, j))
      continue;

    /* loop through hyperface nodes */
    mesh_hyperface_normal_vector(hyperface_normal, d, m_cf_dm1_0, m_coord, j);
    if (!normal_in_list(d, t, hyperface_normals, hyperface_normal))
    {
      hyperface_normal_t = hyperface_normals + d * t;
      for (p = 0; p < d; ++p)
        hyperface_normal_t[p] = hyperface_normal[p];
      ++t;
    }
    *number_of_non_prallell_hyperfaces = t;
  }
}

/*
Works only for meshes enclosing convex polytope
If a half-space is detemined by the equation
  $l(x) := n_0 x_0 + ... + n_{d - 1} x_{d - 1} - c = 0$,
then two points $x$ and $y$ not lying on l are on the same side iff
  $l(x) * l(y) > 0$
(and on the opposite when $l(x) * l(y) < 0$).
*/
static void mesh_node_normal_exterior(
  double * hyperface_normals,
  const mesh * m,
  int d,
  double m_size,
  int number_of_non_prallell_hyperfaces,
  double * m_coord_i)
{
  int j, m_cn_0, p, t;
  double free_coefficient, normal_point_value, other_point_value;
  double nearby_point[3];
  double * m_coord, * m_coord_j, * hyperface_normal_t;

  m_coord = m->coord;
  m_cn_0 = m->cn[0];
  for (t = 0; t < number_of_non_prallell_hyperfaces; ++t)
  {
    hyperface_normal_t = hyperface_normals + d * t;
    for (p = 0; p < d; ++p)
      nearby_point[p] = m_coord_i[p] + (m_size / 2) * hyperface_normal_t[p];
    free_coefficient = 0;
    for (p = 0; p < d; ++p)
      free_coefficient += m_coord_i[p] * hyperface_normal_t[p];

    normal_point_value = -free_coefficient;
    for (p = 0; p < d; ++p)
      normal_point_value += nearby_point[p] * hyperface_normal_t[p];

    for (j = 0; j < m_cn_0; ++j)
    {
      m_coord_j = m_coord + d * j;
      other_point_value = -free_coefficient;
      for (p = 0; p < d; ++p)
        other_point_value += m_coord_j[p] * hyperface_normal_t[p];
      if (other_point_value >= EPSILON || other_point_value <= -EPSILON)
        break;
    }
    // fprintf(stderr,
      // "  t = %d, normal_point_value = %g, other_point_value = %g\n",
      // t, normal_point_value, other_point_value);
    if (normal_point_value * other_point_value > 0)
    {
      double_array_multiply_with(hyperface_normal_t, d, -1.);
    }
  }
}

static void hyperface_normals_average(
  double * normal, int d, int size, const double * hyperface_normals)
{
  int p, t;
  double norm;

  memset(normal, 0, sizeof(double) * d);
  for (t = 0; t < size; ++t)
  {
    for (p = 0; p < d; ++p)
      normal[p] += hyperface_normals[d * t + p];
  }
  norm = double_array_norm(d, normal);
  for (p = 0; p < d; ++p)
    normal[p] /= norm;
}
