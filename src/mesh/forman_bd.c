#include <errno.h>
#include <stdlib.h>
#include <stdio.h>
#include "forman_private.h"
#include "int.h"

static double * forman_bd_x(
  const mesh * m_forman, matrix_sparse ** m_bd,
  int m_forman_bd_p_f_nzmax, const jagged3 * m_forman_cbi, int p_f)
{
  int i, i_f, ind, j, j_f, j_f_loc, k, l, p, q, r, s;
  int * m_forman_cn;
  double sign, sign_loc;
  double * m_forman_bd_p_f_x;
  jagged1 m_forman_cbi_p_f_i_f, m_forman_cbi_p_f_minus_1_j_f,
          m_forman_hyperface;
  jagged2 m_forman_cbi_p_f, m_forman_cbi_p_f_minus_1, m_forman_hyperfaces;
  jagged4 * m_forman_cf;
  
  m_forman_cn = m_forman->cn;
  m_forman_cf = m_forman->cf;
  jagged3_part1(&m_forman_cbi_p_f, m_forman_cbi, p_f);
  jagged3_part1(&m_forman_cbi_p_f_minus_1, m_forman_cbi, p_f - 1);
  jagged4_part2(&m_forman_hyperfaces, m_forman_cf, p_f - 1, p_f - 1);
  
  m_forman_bd_p_f_x = (double *) malloc(sizeof(double) * m_forman_bd_p_f_nzmax);
  if (errno)
  {
    perror("forman_bd_x - cannot allocate memory for m_forman_bd_p_f_x");
    return NULL;
  }
  ind = 0;
  for (i_f = 0; i_f < m_forman_cn[p_f]; ++i_f)
  {
    jagged2_part1(&m_forman_cbi_p_f_i_f, &m_forman_cbi_p_f, i_f);
    int_array_4_values_get(m_forman_cbi_p_f_i_f.a1, &r, &k, &s, &l);
    jagged2_part1(&m_forman_hyperface, &m_forman_hyperfaces, i_f);
    for (j_f_loc = 0; j_f_loc < m_forman_hyperface.a0; ++j_f_loc)
    {
      j_f = jagged1_part1(&m_forman_hyperface, j_f_loc);
      jagged2_part1(&m_forman_cbi_p_f_minus_1_j_f,
                    &m_forman_cbi_p_f_minus_1, j_f);
      int_array_4_values_get(m_forman_cbi_p_f_minus_1_j_f.a1, &p, &i, &q, &j);
      if (r == p)
      {
        sign_loc = p_f % 2 == 0 ? 1. : -1.;
        sign = sign_loc * matrix_sparse_part(m_bd[q - 1], l, j);
      }
      else
        sign = matrix_sparse_part(m_bd[p], i, k);
      m_forman_bd_p_f_x[ind + j_f_loc] = sign;
    }
    ind += m_forman_hyperface.a0;
  }
  return m_forman_bd_p_f_x;
}

matrix_sparse * forman_bd_p_f(
  const mesh * m_forman, matrix_sparse ** m_bd,
  const jagged3 * m_forman_cbi, int p_f)
{
  int m_forman_bd_p_f_nonzero_max;
  int * m_forman_cn;
  matrix_sparse * m_forman_bd_p_f;
  
  m_forman_cn = m_forman->cn;
  m_forman_bd_p_f = (matrix_sparse *) malloc(sizeof(matrix_sparse));
  if (errno)
  {
    perror("forman_bd_p_f - cannot allocate memory for m_forman_bd_p_f");
    goto end;
  }
  m_forman_bd_p_f_nonzero_max = mesh_bd_nzmax(m_forman, p_f);
  m_forman_bd_p_f->rows = m_forman_cn[p_f - 1];
  m_forman_bd_p_f->cols = m_forman_cn[p_f];
  m_forman_bd_p_f->cols_total = mesh_bd_p(m_forman, p_f);
  if (errno)
  {
    perror("forman_bd_p_f - cannot calculate m_forman_bd_p_f->p");
    goto m_forman_bd_p_f_free;
  }
  m_forman_bd_p_f->row_indices = mesh_bd_i(m_forman, p_f);
  if (errno)
  {
    perror("forman_bd_p_f - cannot calculate m_forman_bd_p_f->i");
    goto m_forman_bd_p_f_p_free;
  }
  m_forman_bd_p_f->values = 
       forman_bd_x(m_forman, m_bd, m_forman_bd_p_f_nonzero_max, 
                   m_forman_cbi, p_f);
  if (errno)
  {
    perror("forman_bd_p_f - cannot calculate m_forman_bd_p_f->x");
    goto m_forman_bd_p_f_i_free;
  }
  //m_forman_bd_p_f->nz = -1;
  return m_forman_bd_p_f;
  
  /* cleaning if an error occurs */
m_forman_bd_p_f_i_free:
  free(m_forman_bd_p_f->row_indices);
m_forman_bd_p_f_p_free:
  free(m_forman_bd_p_f->cols_total);
m_forman_bd_p_f_free:
  free(m_forman_bd_p_f);
end:
  return NULL;
}

matrix_sparse ** forman_bd(
  const mesh * m, const mesh * m_forman, matrix_sparse ** m_bd)
{
  int m_dim, p_f;
  int * m_forman_cn;
  matrix_sparse ** m_forman_bd;
  jagged3 * m_forman_cbi;

  m_dim = m->dim;
  m_forman_cn = m_forman->cn;
  m_forman_bd = (matrix_sparse **) malloc(sizeof(matrix_sparse *) * m_dim);
  if (errno)
  {
    perror("forman_bd - cannot allocate memory for m_forman_bd");
    goto end;
  }
  m_forman_cbi = forman_cbi(m, m_forman_cn);
  if (errno)
  {
    perror("forman_bd - cannot calculate m_forman_cbi");
    goto m_forman_bd_free;
  }
  for (p_f = 1; p_f <= m_dim; ++p_f)
  {
    m_forman_bd[p_f - 1] = forman_bd_p_f(m_forman, m_bd, m_forman_cbi, p_f);
    if (errno)
    {
      fprintf(stderr, "forman_bd - cannot calculate m_forman_bd[%d]", p_f - 1);
      perror("");
      goto m_forman_bd_p_f_free;
    }
  }
  jagged3_free(m_forman_cbi);
  return m_forman_bd;
  
  /* cleaning if an error occurs */
m_forman_bd_p_f_free:
  matrix_sparse_array_free(m_forman_bd, p_f - 1);
m_forman_bd_free:
  free(m_forman_bd);
end:
  return NULL;
}
