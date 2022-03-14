#include <math.h>
#include "mesh.h"

#define PI 3.14159265

static double angle_unit(int d)
{
  switch (d)
  {
    case 0: return 1.;
    case 1: return 1.;
    case 2: return (2 * PI);
    case 3: return (4 * PI);
    default: return 1.;
  }
  return 1.;
}

static double vector_dot(int d, const double * a, const double * b)
{
  int i;
  double res;
  
  res = 0;
  for (i = 0; i < d; ++i)
    res += a[i] * b[i];
  return res;
}

static double vector_length(int d, const double * a)
{
  double length_square;
  
  length_square = vector_dot(d, a, a);
  return sqrt(length_square);
}
  
static void vector_normalise(double * res, int d, const double * a)
{
  int i;
  double l;
  
  l = vector_length(d, a);
  for (i = 0; i < d; ++i)
    res[i] = a[i] / l;
}

// static double angle_2d(const double a[3][3])
// {
//   double dot, l0, l1;
//
//   dot = vector_dot(2, a[0], a[1]);
//   l0 = vector_length(2, a[0]);
//   l1 = vector_length(2, a[1]);
//   return acos(dot / (l0 * l1));
// }

static double angle_2d_general(int d, const double a0[3], const double a1[3])
{
  double dot;
  double v0[3], v1[3];
  
  vector_normalise(v0, d, a0);
  vector_normalise(v1, d, a1);
  dot = vector_dot(d, v0, v1);
  return acos(dot);
}

static double angle_2d(const double a[3][3])
{
  double dot;
  double v0[3], v1[3];

  vector_normalise(v0, 2, a[0]);
  vector_normalise(v1, 2, a[1]);
  dot = vector_dot(2, v0, v1);
  return acos(dot);
}

// static double determinant_3d(const double a[3][3])
// {
//   return a[0][0] * a[1][1] * a[2][2] - a[0][0] * a[1][2] * a[2][1]
//        + a[1][0] * a[2][1] * a[0][2] - a[1][0] * a[0][1] * a[2][2]
//        + a[2][0] * a[0][1] * a[1][2] - a[2][0] * a[1][1] * a[0][2];
// }
//
// static double angle_3d(const double a[3][3])
// {
//   double dot01, dot02, dot12, l0, l1, l2, triple;
//   double numerator, denominator;
//
//   dot01 = vector_dot(3, a[0], a[1]);
//   dot02 = vector_dot(3, a[0], a[2]);
//   dot12 = vector_dot(3, a[1], a[2]);
//   l0 = vector_length(3, a[0]);
//   l1 = vector_length(3, a[1]);
//   l2 = vector_length(3, a[2]);
//   triple = determinant_3d(a);
//   numerator = fabs(triple);
//   denominator = l0 * l1 * l2 + dot01 * l2 + dot02 * l1 + dot12 * l0;
//   return 2 * atan(numerator / denominator);
// }

static double angle_3d(const double a[3][3])
{
  double fourth_tan_square, theta_s, theta01, theta02, theta12;

  theta01 = angle_2d_general(3, a[0], a[1]);
  theta02 = angle_2d_general(3, a[0], a[2]);
  theta12 = angle_2d_general(3, a[1], a[2]);
  theta_s = (theta01 + theta02 + theta12) / 2;
  fourth_tan_square = 
      tan(theta_s / 2) 
    * tan((theta_s - theta01) / 2)
    * tan((theta_s - theta02) / 2)
    * tan((theta_s - theta12) / 2);
  return 4 * atan(sqrt(fourth_tan_square));
}

static void point_difference(
  double * res, int d, const double * a, const double * b)
{
  int i;
  
  for (i = 0; i < d; ++i)
    res[i] = b[i] - a[i];
}

static void edge_vector(int * ind, double a[3][3], int d, const double * coord,
                        const jagged1 * arr, int i)
{
  if (arr->a1[0] == i)
  {
    point_difference(a[*ind], d, coord + d * i, coord + d * arr->a1[1]);
    ++*ind;
  }
  else if (arr->a1[1] == i)
  {
    point_difference(a[*ind], d, coord + d * i, coord + d * arr->a1[0]);
    ++*ind;
  }
}

static double mesh_angle_nd(const mesh * m, int i, int d, int k)
{
  int ind, j, j_loc;
  double * m_coord;
  double edges_coord[3][3];
  jagged1 edges, edge_nodes;
  
  m_coord = m->coord;
  mesh_cf_part3(&edges, m, d, 1, k);
  ind = 0;
  for (j_loc = 0; j_loc < edges.a0; ++j_loc)
  {
    j = edges.a1[j_loc];
    mesh_cf_part3(&edge_nodes, m, 1, 0, j);
    edge_vector(&ind, edges_coord, d, m_coord, &edge_nodes, i);
  }
  return (d == 2) ? angle_2d(edges_coord) : angle_3d(edges_coord);
}

static double mesh_angle(const mesh * m, int i, int d, int k)
{
  switch (d)
  {
    case 0: return 1.;
    case 1: return 0.5;
    case 2: case 3: return mesh_angle_nd(m, i, d, k);
    default: return 1.;
  }
  return 1.;
}

double mesh_node_curvature_i(const mesh * m, int i)
{
  int k, k_loc, m_dim;
  double node_total_angle;
  jagged1 volumes;
  
  m_dim = m->dim;
  mesh_fc_part3(&volumes, m, 0, m_dim, i);
  node_total_angle = 0;
  for (k_loc = 0; k_loc < volumes.a0; ++k_loc)
  {
    k = volumes.a1[k_loc];
    node_total_angle += mesh_angle(m, i, m_dim, k);
  }
  return angle_unit(m_dim) / node_total_angle;
}

double * mesh_node_curvature(const mesh * m)
{
  int i, m_cn_0;
  double * res;
  
  m_cn_0 = m->cn[0];
  res = (double *) malloc(m_cn_0 * sizeof(double));
  /* NULL pointer check */
  for (i = 0; i < m_cn_0; ++i)
    res[i] = mesh_node_curvature_i(m, i);
  return res;
}
  