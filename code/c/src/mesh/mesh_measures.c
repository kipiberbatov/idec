#include <math.h>
#include <stdlib.h>
#include <string.h>

#include "color.h"
#include "double.h"
#include "idec_error_message.h"
#include "mesh_qc.h"

typedef void
mesh_measures_function(double *** m_measures, int * status, const mesh * m);

static void
mesh_measures_default(double *** m_measures, int * status, const mesh * m)
{
  *m_measures = mesh_qc_vol(m);
  if (*m_measures == NULL)
  {
    color_error_position(__FILE__, __LINE__);
    fputs("cannot calculate m_measures\n", stderr);
    *status = 1;
  }
}

static void mesh_measures_simplicial_or_quasi_cubical(
  double *** m_measures, int * status, const mesh * m)
{
  int d, p;
  int * m_cn;
  double ** vol;

  d = m->dim;
  m_cn = m->cn;
  *m_measures = (double **) malloc(sizeof(double *) * (d + 1));
  if (*m_measures == NULL)
  {
    color_error_position(__FILE__, __LINE__);
    idec_error_message_malloc(sizeof(double *) * (d + 1), "*m_measures");
    *status = 1;
    return;
  }
  vol = *m_measures;

  for (p = 0; p <= d; ++p)
  {
    vol[p] = (double *) malloc(sizeof(double) * m_cn[p]);
    if (vol[p] == NULL)
    {
      color_error_position(__FILE__, __LINE__);
      fprintf(stderr,
        "cannot allocate %s%ld%s bytes of memory for %s%s[%d]%s\n",
         color_variable, sizeof(double) * m_cn[p], color_none,
         color_variable, "vol", p, color_none);
      *status = 1;
      return;
    }
  }

  for (p = 0; p <= d; ++p)
    mesh_measure_single(vol[p], m, p);
}

/* m is the Forman mesh of a circular mesh */
static void mesh_measures_circular_forman(
  double *** m_measures, int * status, const mesh * m)
{
  int i, index, j, na, nd, p;
  int * m_cn;
  double a, a0, r, r0, s_0, s_i0, s_i1, theta;
  double * vol_1, * vol_2;
  double ** vol;

  *m_measures = (double **) malloc(sizeof(double *) * 3);
  if (*m_measures == NULL)
  {
    color_error_position(__FILE__, __LINE__);
    idec_error_message_malloc(sizeof(double *) * 3, "*m_measures");
    *status = 1;
    return;
  }

  m_cn = m->cn;
  vol = *m_measures;
  for (p = 0; p <= 2; ++p)
  {
    vol[p] = (double *) malloc(sizeof(double) * m_cn[p]);
    if (vol[p] == NULL)
    {
      color_error_position(__FILE__, __LINE__);
      fprintf(stderr,
        "cannot allocate %s%ld%s bytes of memory for %s%s[%d]%s\n",
         color_variable, sizeof(double) * m_cn[p], color_none,
         color_variable, "vol", p, color_none);
      *status = 1;
      return;
    }
  }

  double_array_assign_constant(vol[0], m_cn[0], 1.);

  na = 2 * (2 * m_cn[0] - m_cn[1] - 2);
  nd = (m_cn[0] - 1) / na;
  {
    int end_index = na * nd / 4;
    double rx = m->coord[2 * end_index];
    double ry = m->coord[2 * end_index + 1];
    r = sqrt(rx * rx + ry * ry);
  }
  r0 = r / nd;
  theta = M_PI * 2 / na;
  a0 = r0 * theta;

  /* edges */
  vol_1 = vol[1];
  index = 0;

  /* original edges to nodes */
  for (i = 1; i <= nd / 2; ++i)
  {
    /* rays */
    double_array_assign_constant(vol_1 + index, na, r0);
    index += na;
    /* arcs */
    a = a0 * 2 * i;
    double_array_assign_constant(vol_1 + index, na, a);
    index += na;
  }

  /* original faces to edges */
  /* inner circle */
  for (j = 0; j < na / 2; ++j)
  {
    vol_1[index + 0] = a0; /* arc */
    vol_1[index + 1] = r0; /* ray */
    vol_1[index + 2] = a0; /* arc */
    index += 3;
  }
  /* outer circles */
  for (i = 1; i < nd / 2; ++i)
  {
    a = a0 * (2 * i + 1);
    for (j = 0; j < na / 2; ++j)
    {
      vol_1[index + 0] = r0; /* ray */
      vol_1[index + 1] = a;  /* arc */
      vol_1[index + 2] = r0; /* ray */
      vol_1[index + 3] = a;  /* arc */
      index += 4;
    }
  }

  /* faces */
  vol_2 = vol[2];
  index = 0;
  s_0 = r0 * r0 * theta / 2;

  /* inner circle */
  s_i0 = 2 * s_0;
  s_i1 = 3 * s_0;
  for (j = 0; j < na / 2; ++j)
  {
    vol_2[index + 0] = s_i0;  /* (0, r0) */
    vol_2[index + 1] = s_i1;  /* (r0, r1) */
    vol_2[index + 2] = s_i1;  /* (r0, r1) */
    index += 3;
  }
  /* outer circles */
  for (i = 1; i < nd / 2; ++i)
  {
    s_i0 = (4 * i + 1) * s_0;
    s_i1 = (4 * i + 3) * s_0;
    for (j = 0; j < na / 2; ++j)
    {
      vol_2[index + 0] = s_i0; /* (r[2 i + 0], r[2 i + 1]) */
      vol_2[index + 1] = s_i1; /* (r[2 i + 1], r[2 i + 2]) */
      vol_2[index + 2] = s_i1; /* (r[2 i + 0], r[2 i + 1]) */
      vol_2[index + 3] = s_i0; /* (r[2 i + 1], r[2 i + 2]) */
      index += 4;
    }
  }
}

void mesh_measures(double *** m_measures, int * status,
  const mesh * m, const char * method)
{
  mesh_measures_function * measurer;

  if (!strcmp(method, "default"))
    measurer = mesh_measures_default;
  else if (!strcmp(method, "simplicial-or-quasi-cubical"))
    measurer = mesh_measures_simplicial_or_quasi_cubical;
  else if (!strcmp(method, "circular-forman"))
    measurer = mesh_measures_circular_forman;
  else
    measurer = NULL;

  if (measurer == NULL)
  {
    color_error_position(__FILE__, __LINE__);
    fprintf(stderr, "method %s is not supported\n", method);
    *status = 1;
    return;
  }

  measurer(m_measures, status, m);
  if (*status)
  {
    color_error_position(__FILE__, __LINE__);
    fprintf(stderr, "cannot calculate m_measures using method %s\n", method);
  }
}
