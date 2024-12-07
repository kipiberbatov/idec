#include <errno.h>
#include <stdlib.h>
#include <string.h>

#include "color.h"
#include "double.h"
#include "diffusion_steady_state_discrete_flow_from_potential.h"
#include "int.h"

int main(int argc, char ** argv)
{
  char * flow_format, * kappa_1_format, * kappa_1_name, * m_format, * m_name,
       * m_hodge_format, * m_hodge_name, * potential_format, * potential_name;
  double * flow, * kappa_1, * potential;
  mesh * m;
  matrix_sparse * m_bd_1;
  matrix_sparse ** m_hodge;
  FILE * m_file;

#define ARGC 10
  if (argc != ARGC)
  {
    color_error_position(__FILE__, __LINE__);
    fprintf(stderr,
      "number of command line arguments should be %d; instead it is %d\n",
      ARGC, argc);
    return EINVAL;
  }

  m_format = argv[1];
  m_name = argv[2];
  m_hodge_format = argv[3];
  m_hodge_name = argv[4];
  kappa_1_format = argv[5];
  kappa_1_name = argv[6];
  potential_format = argv[7];
  potential_name = argv[8];
  flow_format = argv[9];

  m_file = fopen(m_name, "r");
  if (m_file == NULL)
  {
    color_error_position(__FILE__, __LINE__);
    fprintf(stderr,
      "cannot open mesh file %s for reading: %s\n",
      m_name, strerror(errno));
    goto end;
  }
  m = mesh_file_scan(m_file, m_format);
  if (m == NULL)
  {
    color_error_position(__FILE__, __LINE__);
    fprintf(stderr,
      "cannot scan mesh m from file %s in format %s\n",
      m_name, m_format);
    fclose(m_file);
    goto end;
  }

  m_bd_1 = mesh_file_scan_boundary_p(m_file, m, 1);
  if (m_bd_1 == NULL)
  {
    color_error_position(__FILE__, __LINE__);
    fprintf(stderr, "cannot scan m_bd_1 from file %s\n", m_name);
    fclose(m_file);
    goto m_free;
  }
  fclose(m_file);

  m_hodge = matrix_sparse_array_file_scan_by_name(
    m_hodge_name, m->dim + 1, m_hodge_format);
  if (m_hodge == NULL)
  {
    color_error_position(__FILE__, __LINE__);
    fprintf(stderr,
      "cannot scan m_hodge form file %s in format %s\n",
      m_hodge_name, m_hodge_format);
    goto m_bd_1_free;
  }

  kappa_1 = double_array_file_scan_by_name(
    kappa_1_name, m->cn[1], kappa_1_format);
  if (kappa_1 == NULL)
  {
    color_error_position(__FILE__, __LINE__);
    fprintf(stderr,
      "cannot scan kappa_1 form file %s in format %s\n",
      kappa_1_name, kappa_1_format);
    goto m_hodge_free;
  }

  potential = double_array_file_scan_by_name(
    potential_name, m->cn[0], potential_format);
  if (potential == NULL)
  {
    color_error_position(__FILE__, __LINE__);
    fprintf(stderr,
      "cannot scan potential form file %s in format %s\n",
      potential_name, potential_format);
    goto kappa_1_free;
  }

  flow = (double *) calloc(m->cn[m->dim - 1], sizeof(double));
  if (flow == NULL)
  {
    color_error_position(__FILE__, __LINE__);
    fprintf(stderr,
      "cannot allocate allocate %ld bytes of memory for flow\n",
      sizeof(double) * m->cn[m->dim - 1]);
    goto potential_free;
  }

  diffusion_steady_state_discrete_flow_from_potential(
    flow, m, m_bd_1, kappa_1, potential, m_hodge[1]);
  if (errno)
  {
    color_error_position(__FILE__, __LINE__);
    fputs("cannot calculate flow %s\n", stderr);
    goto flow_free;
  }

  double_array_file_print(stdout, m->cn[m->dim - 1], flow, flow_format);

flow_free:
  free(flow);
potential_free:
  free(potential);
kappa_1_free:
  free(kappa_1);
m_hodge_free:
  matrix_sparse_array_free(m_hodge, m->dim + 1);
m_bd_1_free:
  matrix_sparse_free(m_bd_1);
m_free:
  mesh_free(m);
end:
  return errno;
}
