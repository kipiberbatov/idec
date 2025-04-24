#include <math.h>
#include <string.h>

#include "double_array.h"
#include "matrix.h"
#include "mesh.h"

/* finds the normal vector to a hyperface, but not its sign */
/* assumes that embedding dimension coincides with intrinsic dimension */

static void
hyperspace_normal_vector(double * normal, int d, const double * subspace_basis);

/*
Let:
  . $d$ be a psoitive integer;
  . $vector$ be an array of $d$ 64-bit floats;
  . $rank$ be a nonnegative integer, $rank < d$;
  . $basis$ be an array of $d * rank$ 64-bit floats representing $rank$
    linearly independent vectors in dimension $d$
    (and so forms a basis of the linear subspace it spans).
Then the integer
  $is_in_linear_span(d, rank, basis, vector)$
is 1 if $vector$ is in the span of $basis$ and 0 else.
*/
static int
in_linear_span(int d, int rank, const double * basis, const double * vector);

/*
Constants:
  . {$d$ : int} is the vector space dimension (at most 3);
  . {$m_cf_dm1_0$ : const jagged2 *} stores the hyperface-node connectivity;
  . {$i$ : int} is the index of a (boundary) hyperface;
  . {$m_coord$ : (const double *)} are the coordinates of the nodes;
  . {$size$ : int} is the number of nodes in a hyperface;
Mutable variables:
  . {$hyperface_normal$ : (double *)}.
Result:
  . $hyperface_normal$ stores a unit normal to the $i$-th face.
*/

void mesh_hyperface_normal_vector(
  double * hyperface_normal,
  int d, const jagged2 * m_cf_dm1_0, const double * m_coord, int i)
{
  int j, rank;
  const double * m_coord_i_0, * m_coord_i_j;
  double vector_j[3], subspace_basis[6];
  jagged1 m_cf_dm1_0_i;

  jagged2_part1(&m_cf_dm1_0_i, m_cf_dm1_0, i);
  m_coord_i_0 = m_coord + d * m_cf_dm1_0_i.a1[0];

  /* find maximal linearly independent set $subspace_basis$ */
  rank = 0;
  j = 1;
  while (rank < d - 1 && j < m_cf_dm1_0_i.a0)
  {
    m_coord_i_j = m_coord + d * m_cf_dm1_0_i.a1[j];
    double_array_difference(vector_j, d, m_coord_i_j, m_coord_i_0);
    if (in_linear_span(d, rank, subspace_basis, vector_j))
    {
      memcpy(subspace_basis + d * rank, vector_j, sizeof(double) * d);
      ++rank;
    }
    ++j;
  }

  /* find the unit basis of the orthogonal complement */
  hyperspace_normal_vector(hyperface_normal, d, subspace_basis);
}

static void hyperface_normal_vector_2d(
  double * normal, int d, const double * subspace_basis)
{
  double b00, b01, coefficient;

  b00 = subspace_basis[0];
  b01 = subspace_basis[1];
  coefficient = sqrt(b00 * b00 + b01 * b01);
  normal[0] = b01 / coefficient;
  normal[1] = -b00 / coefficient;
}

static void hyperface_normal_vector_3d(
  double * normal, int d, const double * subspace_basis)
{
  double b00, b01, b02, b10, b11, b12, coefficient, n0, n1, n2;

  b00 = subspace_basis[0];
  b01 = subspace_basis[1];
  b02 = subspace_basis[2];
  b10 = subspace_basis[3];
  b11 = subspace_basis[4];
  b12 = subspace_basis[5];
  n0 = b01 * b12 - b02 * b11;
  n1 = b02 * b10 - b00 * b12;
  n2 = b00 * b11 - b01 * b10;
  coefficient = sqrt(n0 * n0 + n1 * n1 + n2 * n2);
  normal[0] = n0 / coefficient;
  normal[1] = n1 / coefficient;
  normal[2] = n2 / coefficient;
}

static void
hyperspace_normal_vector(double * normal, int d, const double * subspace_basis)
{
  if (d == 2)
    hyperface_normal_vector_2d(normal, d, subspace_basis);
  else if (d == 3)
    hyperface_normal_vector_3d(normal, d, subspace_basis);
}

#define EPSILON .000001

static int vectors_proportional(int d, const double * v, const double * w)
{
  int i, ratio;

  for (i = 1; i < d; ++i)
  {
    ratio = (v[0] * w[i] - v[i] * w[0])
    / (sqrt(v[0] * v[0] + v[i] * v[i]) * sqrt(w[0] * w[0] + w[i] * w[i]));
    if (ratio >= EPSILON && -ratio >= EPSILON)
      return 0;
  }
  return 1;
}

static int in_linear_span_3d_2(
  const double * subspace_basis, const double * vector)
{
  int i;
  double det, norm, ratio;
  double a[9];

  for (i = 0; i < 6; ++i)
    a[i] = subspace_basis[i];
  for (i = 0; i < 3; ++i)
    a[6 + i] = vector[i];
  det = matrix_determinant(3, a);
  norm = double_array_norm(3, a) * double_array_norm(3, a + 3)
       * double_array_norm(3, a + 6);
  ratio = det / norm;
  if (ratio >= EPSILON && -ratio >= EPSILON)
    return 0;
  return 1;
}

static int in_linear_span(
  int d, int rank, const double * subspace_basis, const double * vector)
{
  if (rank == 0)
    return 1;
  if (rank == 1)
    return vectors_proportional(d, subspace_basis, vector);
  if (d == 3 && rank == 2)
    return in_linear_span_3d_2(subspace_basis, vector);
  return 0;
}
