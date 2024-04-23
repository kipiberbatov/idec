#include <stdlib.h>
// #include "array_indexed.h"
#include "int.h"
#include "mesh.h"

int mesh_boundary_nzmax(const mesh * m, int p)
{
  int i, m_cn_p;
  int * hyperfaces_a1;
  int m_bd_nzmax;
  jagged1 hyperfaces;
  jagged3 m_cfn;
  //jagged4 * m_cf;
  
  m_cn_p = m->cn[p];
  m_cfn.a0 = m->cf->a0;
  m_cfn.a1 = m->cf->a1;
  m_cfn.a2 = m->cf->a2;
  m_cfn.a3 = m->cf->a3;
  
  //jagged3_set(&m_cfn, m_cf->a0, m_cf->a1, m_cf->a2, m_cf->a3);
  jagged3_part2(&hyperfaces, &m_cfn, p - 1, p - 1);
  hyperfaces_a1 = hyperfaces.a1;
  
  m_bd_nzmax = 0;
  for (i = 0; i < m_cn_p; ++i)
    m_bd_nzmax += hyperfaces_a1[i];
  return m_bd_nzmax;
}

int * mesh_boundary_p(const mesh * m, int p)
{
  int i, m_cn_p;
  int * m_bd_p;
  jagged1 hyperfaces;
  jagged2 topology;
  jagged4 * m_cf;
  
  m_cn_p = m->cn[p];
  m_cf = m->cf;
  jagged4_part2(&topology, m_cf, p - 1, p - 1);
  
  m_bd_p = (int *) malloc((m_cn_p + 1) * sizeof(int));
  /* NULL pointer check */
  
  m_bd_p[0] = 0; 
  for (i = 0; i < m_cn_p; ++i)
  {
    jagged2_part1(&hyperfaces, &topology, i);
    m_bd_p[i + 1] = m_bd_p[i] + hyperfaces.a0;
  }
  return m_bd_p;
}

int * mesh_boundary_i(const mesh * m, int p)
{
  int i, ind, j_loc, m_bd_nzmax, m_cn_p;
  int * m_bd_i;
  jagged1 hyperfaces;
  jagged2 topology;
  jagged4 * m_cf;
  
  m_cn_p = m->cn[p];
  m_cf = m->cf;
  jagged4_part2(&topology, m_cf, p - 1, p - 1);
  m_bd_nzmax = mesh_boundary_nzmax(m, p);
  m_bd_i = (int *) malloc(m_bd_nzmax * sizeof(int));
  ind = 0;
  for (i = 0; i < m_cn_p; ++i)
  {
    jagged2_part1(&hyperfaces, &topology, i);
    for (j_loc = 0; j_loc < hyperfaces.a0; ++j_loc)
      m_bd_i[ind + j_loc] = hyperfaces.a1[j_loc];
    ind += hyperfaces.a0;
  }
  return m_bd_i;
}

// static void array_initialise(int * a, int n)
// {
//   int i;
//   for (i = 0; i < n; ++i)
//     a[i] = i;
// }

// static void array_double_permutate(double * a, int n, const int * perm)
// {
//   int i;
//   double * tmp;
//
//   tmp = (double *) malloc(n * sizeof(double));
//   /* NULL pointer check */
//   for (i = 0; i < n; ++i)
//     tmp[i] = a[perm[i]];
//   for (i = 0; i < n; ++i)
//      a[i] = tmp[i];
//   free(tmp);
// }

static void mesh_boundary_values(matrix_sparse * m_bd, const mesh * m, int p)
{
  int hyperfaces_a0, i, ind, j, j_loc, m_cn_p, pos0, pos1, sign;
  //int * a_positions;
  int * a_values, * hyperfaces_a1, * hyperface_nodes_a1, * m_bd_i;
  double * m_bd_x;
  jagged1 hyperfaces, cell_nodes, hyperface_nodes;
  jagged2 topology, cells_nodes;
  //jagged2 hyperfaces_nodes;
  jagged4 * m_cf;
  //array_indexed a;
  
  m_cn_p = m->cn[p];
  m_cf = m->cf;
  m_bd_x = m_bd->values;
  m_bd_i = m_bd->row_indices;
  jagged4_part2(&topology, m_cf, p - 1, p - 1);
  jagged4_part2(&cells_nodes, m_cf, p - 1, 0);
  /*jagged4_part2(&hyperfaces_nodes, m_cf, p - 2, 0);*/
  
  ind = 0;
  for (i = 0; i < m_cn_p; ++i)
  {
    jagged2_part1(&hyperfaces, &topology, i);
    hyperfaces_a0 = hyperfaces.a0;
    hyperfaces_a1 = hyperfaces.a1;
    jagged2_part1(&cell_nodes, &cells_nodes, i);
    // a_positions = (int *) malloc(hyperfaces_a0 * sizeof(int));
    // /* NULL pointer check */
    // array_initialise(a_positions, hyperfaces_a0);
    a_values = m_bd_i + ind;
    for (j_loc = 0; j_loc < hyperfaces_a0; ++j_loc)
    {
      j = hyperfaces_a1[j_loc];
      a_values[j_loc] = j;
      mesh_cf_part3(&hyperface_nodes, m, p - 1, 0, j);
      /* it is better to change to jagged<n>_part without j in the loop */
      if (cell_nodes.a0 == (p + 1)) /*. for simplices */
        sign = jagged1_relative_sign(&cell_nodes, &hyperface_nodes);
      else /* for polygons */
      {
        hyperface_nodes_a1 = hyperface_nodes.a1;
        pos0 = jagged1_position(&cell_nodes, hyperface_nodes_a1[0]);
        pos1 = jagged1_position(&cell_nodes, hyperface_nodes_a1[1]);
        sign = (((pos1 - pos0 + cell_nodes.a0) % cell_nodes.a0) == 1) ? 1 : -1;
      }
      m_bd_x[ind + j_loc] = (double) sign;
    }
    // a.positions = a_positions;
    // a.values = a_values;
    // array_indexed_merge_sort(&a, hyperfaces_a0);
    // /* NULL pointer check */
    // array_double_permutate(m_bd_x + ind, hyperfaces_a0, a_positions);
    // /* NULL pointer check */
    // free(a_positions);
    ind += hyperfaces_a0;
  }
}

matrix_sparse * mesh_boundary_single(const mesh * m, int p)
{
  int m_bd_nonzero_max;
  matrix_sparse * m_bd;
  
  m_bd_nonzero_max = mesh_boundary_nzmax(m, p);
  m_bd = (matrix_sparse *) malloc(sizeof(matrix_sparse));
  /* NULL pointer check */
  //m_bd->nzmax = mesh_boundary_nzmax(m, p);
  /* NULL pointer check */
  m_bd->rows = m->cn[p - 1];
  m_bd->cols = m->cn[p];
  m_bd->cols_total = mesh_boundary_p(m, p);
  /* NULL pointer check */
  m_bd->row_indices = (int *) malloc(sizeof(int) * m_bd_nonzero_max);
  /* NULL pointer check */
  m_bd->values = (double *) malloc(sizeof(double) * m_bd_nonzero_max);
  /* NULL pointer check */
  mesh_boundary_values(m_bd, m, p);
  /* NULL pointer check because of local dynamic memory */
  //m_bd->nz = -1;
  return m_bd;
}

// static void matrix_sparse * mesh_boundary_p(const mesh * m, int p, double * m_bd_x);
// {
//   int i, m_bd_n;
//   int * m_bd_p;
//   jagged1 cells;
//   jagged2 topology, m_bd_i;
//   matrix_sparse * m_bd;
//
//   mesh_cf_part2(&topology, m, p, p - 1);
//   m_bd = (matrix_sparse *) malloc(sizeof(matrix_sparse));
//   /* NULL pointer check */
//   m_bd->m = m->cn[p - 1];
//   m-bd->n = m->cn[p];
//   m_bd->p = (int *) malloc((m_bd_n + 1) * sizeof(int));
//   m_bd_p[0] = 0;
//   for (i = 0; i < m_bd_n; ++i)
//   {
//     jagged2_part1(&cells, topology, i);
//     m_bd_p[i + 1] = m_bd_p[i] + cells.a0;
//   }
//   m_bd->nzmax = m_bd_p[m_bd_n];
//   m_bd->i = (int *) malloc(m_bd->nzmax * sizeof(int));
//   /* NULL pointer check */
//   mesh_cfn_part2(&m_bd_i, m, p, p - 1);
//   memcpy(m_bd->i, m_bd_i.a2, m_bd->nzmax * sizeof(int));
//   m_bd->x = (double *) malloc(m_bd->nzmax * sizeof(double));
//   /* NULL pointer check */
//   memcpy(m_bd->x, m_bd_x, m_bd->nzmax * sizeof(double));
//   m-bd->nz = -1;
//
//   return m_bd;
// }

matrix_sparse ** mesh_boundary(const mesh * m)
{
  int m_dim, p;
  matrix_sparse ** m_bd;

  m_dim = m->dim;
  m_bd = (matrix_sparse **) malloc(sizeof(matrix_sparse *) * m_dim);
  /* NULL pointer check */

  for (p = 1; p <= m_dim; ++p)
  {
    m_bd[p - 1] = mesh_boundary_single(m, p);
    //m_bd[p - 1] = mesh_boundary_p(m, p);
    /* NULL pointer check */
  }
  return m_bd;
}

void mesh_boundary_check(
  FILE * out, int m_dim, matrix_sparse ** m_bd, const char * name)
{
  int p;
  matrix_sparse * m_bd_check;
  
  for (p = 0; p < m_dim - 1; ++p)
  {
    m_bd_check = matrix_sparse_product(m_bd[p], m_bd[p + 1]);
    /* NULL pointer check */
    fprintf(out, "%s_%d . %s_%d:\n\n", name, p + 1, name, p + 2);
    matrix_sparse_file_print(out, m_bd_check, "-annotated");
    fputs("\n", out);
    free(m_bd_check);
  }
}
