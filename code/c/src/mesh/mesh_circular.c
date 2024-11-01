#include <math.h>
#include <stdlib.h>
#include <string.h>

#include "color.h"
#include "int.h"
#include "mesh_circular.h"
#include "mesh_private.h"

static void mesh_circular_cells_number(int * m_cn, int na, int nd)
{
  int product = na * nd;
  m_cn[0] = product + 1;
  m_cn[1] = 2 * product;
  m_cn[2] = product;
}

/*
(1, 0) -> 2 ($2 * na * nd$ times)
(2, 0) -> 3 ($na$ times), 4 ($na * (nd - 1)$ times)
(2, 1) -> 3 ($na$ times), 4 ($na * (nd - 1)$ times)
*/
static void mesh_circular_cells_to_faces_a3(int * m_cf_a3, int na, int nd)
{
  int index;

  int_array_assign_constant(m_cf_a3, 2 * na * nd, 2);
  index = 2 * na * nd;

  int_array_assign_constant(m_cf_a3 + index, na, 3);
  index += na;

  int_array_assign_constant(m_cf_a3 + index, na * (nd - 1), 4);
  index += na * (nd - 1);

  int_array_assign_constant(m_cf_a3 + index, na, 3);
  index += na;

  int_array_assign_constant(m_cf_a3 + index, na * (nd - 1), 4);
}

/*
(1, 0):
  j = 0 : na - 1
    j -> (0, j + 1)

  j = 0 : na - 2
    na + j -> (j + 1, j + 2)
  2 * na - 1 -> (na, 1)

  i = 1 : nd - 1
    j = 1 : na
      2 * i * na + j  -> (na * (i - 1) + j, na * i + j)

    j = 1 : na - 1
      (2 * i + 1) * na + j -> (na * i + j, na * i + j + 1)
    2 * (i + 1) * na - 1 -> (na * (i + 1), na * i + 1)

(2, 0):
  j = 0 : na - 2
    j -> (0, j + 1, j + 2)
  na - 1 -> (0, na, 1)

  i = 1 : nd - 1
    j = 0 : na - 2
      na * i + j -> (1, na + 1, na + 2, 2) + j + (i - 1) * na
    na * (i + 1) - 1 -> (2 * na, na + 1, 1, na) + (i - 1) * na

(2, 1):
  j = 0 : na - 2
    j -> (j, j + na, j + 1)
  na - 1 -> (na - 1, 2 * na - 1, 0)

  i = 1 : nd - 1
    j = 0 : na - 2
      na * i + j -> (na, 2 * na, 3 * na, 2 * na + 1) + j + 2 * (i - 1) * na
    na * (i + 1) - 1 -> (- 1, na - 1, 2 * na - 1, 0) + 2 * i * na
*/
static void mesh_circular_cells_to_faces_a4(int * m_cf_a4, int na, int nd)
{
  int i, index, j, offset;

  index = 0;

  /* (1, 0) -> inner, radial */
  for (j = 0; j < na; ++j)
  {
    m_cf_a4[index] = 0;
    m_cf_a4[index + 1] = j + 1;
    index += 2;
  }

  /* (1, 0) -> inner, arcs */
  for (j = 0; j < na - 1; ++j)
  {
    m_cf_a4[index] = j + 1;
    m_cf_a4[index + 1] = j + 2;
    index += 2;
  }
  m_cf_a4[index] = na;
  m_cf_a4[index + 1] = 1;
  index += 2;

  /* (1, 0) -> outer */
  for (i = 1; i < nd; ++i)
  {
    offset = na * i;
    /* radial */
    for (j = 1; j <= na; ++j)
    {
      m_cf_a4[index] = offset - na + j;
      m_cf_a4[index + 1] = offset + j;
      index += 2;
    }

    /* arcs */
    for (j = 1; j < na; ++j)
    {
      m_cf_a4[index] = offset + j;
      m_cf_a4[index + 1] = offset + j + 1;
      index += 2;
    }
    m_cf_a4[index] = offset + na;
    m_cf_a4[index + 1] = offset + 1;
    index += 2;
  }

  /* (2, 0) -> inner */
  for (j = 0; j < na - 1; ++j)
  {
    m_cf_a4[index] = 0;
    m_cf_a4[index + 1] = j + 1;
    m_cf_a4[index + 2] = j + 2;
    index += 3;
  }
  m_cf_a4[index] = 0;
  m_cf_a4[index + 1] = na;
  m_cf_a4[index + 2] = 1;
  index += 3;

  /* (2, 0) -> outer */
  for (i = 1; i < nd; ++i)
  {
    offset = (i - 1) * na;
    for (j = 0; j < na - 1; ++j)
    {
      m_cf_a4[index] = 1 + offset + j;
      m_cf_a4[index + 1] = na + 1 + offset + j;
      m_cf_a4[index + 2] = na + 2 + offset + j;
      m_cf_a4[index + 3] = 2 + offset + j;
      index += 4;
    }
    m_cf_a4[index] = 2 * na + offset;
    m_cf_a4[index + 1] = na + 1 + offset;
    m_cf_a4[index + 2] = 1 + offset;
    m_cf_a4[index + 3] = na + offset;
    index += 4;
  }

  /* (2, 1) -> inner */
  for (j = 0; j < na - 1; ++j)
  {
    m_cf_a4[index] = j;
    m_cf_a4[index + 1] = j + na;
    m_cf_a4[index + 2] = j + 1;
    index += 3;
  }
  m_cf_a4[index] = na - 1;
  m_cf_a4[index + 1] = 2 * na - 1;
  m_cf_a4[index + 2] = 0;
  index += 3;

  /* (2, 1) -> outer */
  for (i = 1; i < nd; ++i)
  {
    offset = 2 * (i - 1) * na;
    for (j = 0; j < na - 1; ++j)
    {
      m_cf_a4[index] = na + offset + j;
      m_cf_a4[index + 1] = 2 * na + offset + j;
      m_cf_a4[index + 2] = 3 * na + offset + j;
      m_cf_a4[index + 3] = 2 * na + 1 + offset + j;
      index += 4;
    }
    m_cf_a4[index] = 2 * na - 1 + offset;
    m_cf_a4[index + 1] = 3 * na - 1 + offset;
    m_cf_a4[index + 2] = 4 * na - 1 + offset;
    m_cf_a4[index + 3] = 2 * na + offset;
    index += 4;
  }
}

static jagged4 * mesh_circular_cells_to_faces(int na, int nd, const int * m_cn)
{
  int m_cf_a2_size, m_cf_a3_size, m_cf_a4_size;
  jagged4 * m_cf;

  m_cf = (jagged4 *) malloc(sizeof(jagged4));
  if (m_cf == NULL)
  {
    color_error_position(__FILE__, __LINE__);
    fprintf(stderr,
      "cannot allocate %ld bytes of memory for m_cf\n", sizeof(jagged4));
    goto end;
  }

  m_cf->a0 = 2;
  m_cf->a1 = (int *) malloc(sizeof(int) * 2);
  if (m_cf->a1 == NULL)
  {
    color_error_position(__FILE__, __LINE__);
    fprintf(stderr,
      "cannot allocate %ld bytes of memory for m_cf->a1\n", sizeof(int) * 2);
    goto m_cf_free;
  }
  mesh_cf_a1(m_cf->a1, 2);

  m_cf_a2_size = int_array_total_sum(2, m_cf->a1);
  m_cf->a2 = (int *) malloc(sizeof(int) * m_cf_a2_size);
  if (m_cf->a2 == NULL)
  {
    color_error_position(__FILE__, __LINE__);
    fprintf(stderr,
      "cannot allocate %ld bytes of memory for m_cf->a2\n",
      sizeof(int) * m_cf_a2_size);
    goto m_cf_a1_free;
  }
  mesh_cf_a2(m_cf->a2, 2, m_cn);

  m_cf_a3_size = int_array_total_sum(m_cf_a2_size, m_cf->a2);
  m_cf->a3 = (int *) malloc(sizeof(int) * m_cf_a3_size);
  if (m_cf->a3 == NULL)
  {
    color_error_position(__FILE__, __LINE__);
    fprintf(stderr,
      "cannot allocate %ld bytes of memory for m_cf->a3\n",
      sizeof(int) * m_cf_a3_size);
    goto m_cf_a2_free;
  }
  mesh_circular_cells_to_faces_a3(m_cf->a3, na, nd);

  m_cf_a4_size = int_array_total_sum(m_cf_a3_size, m_cf->a3);
  m_cf->a4 = (int *) malloc(sizeof(int) * m_cf_a4_size);
  if (m_cf->a4 == NULL)
  {
    color_error_position(__FILE__, __LINE__);
    fprintf(stderr,
      "cannot allocate %ld bytes of memory for m_cf->a4\n",
      sizeof(int) * m_cf_a4_size);
    goto m_cf_a3_free;
  }
  mesh_circular_cells_to_faces_a4(m_cf->a4, na, nd);

  return m_cf;

  /* cleaning if an error occurs */
m_cf_a3_free:
  free(m_cf->a3);
m_cf_a2_free:
  free(m_cf->a2);
m_cf_a1_free:
  free(m_cf->a1);
m_cf_free:
  free(m_cf);
end:
  return NULL;
}

static void mesh_circular_coordinates(
  double * m_coord, int na, int nd, double radius, double x0, double y0)
{
  int i, j, offset;
  double cost, length, sint, t;

  m_coord[0] = x0;
  m_coord[1] = y0;

  for (j = 0; j < na; ++j)
  {
    t = (2 * M_PI * (double) j) / (double) na;
    cost = cos(t);
    sint = sin(t);
    for (i = 0; i < nd; ++i)
    {
      offset = 2 * (1 + na * i + j);
      length = radius * (double) (i + 1) / (double) nd;
      m_coord[offset] = x0 + length * cost;
      m_coord[offset + 1] = y0 + length * sint;
    }
  }
}

mesh * mesh_circular(int na, int nd, double radius, double x0, double y0)
{
  int m_c_size;
  mesh * m;

  m = (mesh *) malloc(sizeof(mesh));
  if (m == NULL)
  {
    color_error_position(__FILE__, __LINE__);
    fprintf(stderr,
      "cannot allocate %ld bytes of memory for m\n", sizeof(mesh));
    goto end;
  }

  m->dim_embedded = 2;
  m->dim = 2;

  m->cn = (int *) malloc(sizeof(int) * 3);
  if (m->cn == NULL)
  {
    color_error_position(__FILE__, __LINE__);
    fprintf(stderr,
      "cannot allocate %ld bytes of memory for m->cn\n", sizeof(int) * 3);
    goto m_free;
  }
  mesh_circular_cells_number(m->cn, na, nd);

  m_c_size = int_array_total_sum(3, m->cn);
  m->c = (int *) malloc(sizeof(int) * m_c_size);
  if (m->c == NULL)
  {
    color_error_position(__FILE__, __LINE__);
    fprintf(stderr,
      "cannot allocate %ld bytes of memory for m->c\n", sizeof(int) * m_c_size);
    goto m_cn_free;
  }
  mesh_c(m->c, 2, m->cn);

  m->cf = mesh_circular_cells_to_faces(na, nd, m->cn);
  if (m->cf == NULL)
  {
    color_error_position(__FILE__, __LINE__);
    fputs("cannot calculate m->cf\n", stderr);
    goto m_c_free;
  }

  m->fc = NULL;

  m->coord = (double *) malloc(sizeof(double) * 2 * m->cn[0]);
  if (m->coord == NULL)
  {
    color_error_position(__FILE__, __LINE__);
    fprintf(stderr,
      "cannot allocate %ld bytes of memory for m->coord\n",
      sizeof(double) * 2 * m->cn[0]);
    goto m_cf_free;
  }
  mesh_circular_coordinates(m->coord, na, nd, radius, x0, y0);

  return m;

  /* cleaning if an error occurs */
m_cf_free:
  free(m->cf);
m_c_free:
  free(m->c);
m_cn_free:
  free(m->cn);
m_free:
  free(m);
end:
  return NULL;
}
