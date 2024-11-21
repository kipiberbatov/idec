#include <errno.h>
#include <stdlib.h>

#include <dlfcn.h>

#include "color.h"
#include "double.h"
#include "diffusion_transient_continuous.h"
#include "diffusion_transient_discrete_flow_from_potential.h"
#include "int.h"
#include "unsigned_approximation.h"

int main(int argc, char ** argv)
{
  char * flow_format, * m_format, * m_name, * m_hodge_format, * m_hodge_name,
       * number_of_steps_name, * pi_1_format, * pi_1_name, * potential_format,
      * potential_name;
  int d, number_of_steps;
  double * flow, * pi_1, * potential;
  mesh * m;
  matrix_sparse * m_bd_1;
  matrix_sparse ** m_hodge;
  FILE * m_file;

#define ARGC 11
  if (argc != ARGC)
  {
    fprintf(stderr,
      "number of command line arguments should be %d; instead it is %d\n",
      ARGC, argc);
    return EINVAL;
  }

  m_format = argv[1];
  m_name = argv[2];
  m_hodge_format = argv[3];
  m_hodge_name = argv[4];
  pi_1_format = argv[5];
  pi_1_name = argv[6];
  potential_format = argv[7];
  potential_name = argv[8];
  number_of_steps_name = argv[9];
  flow_format = argv[10];

  m_file = fopen(m_name, "r");
  if (errno)
  {
    color_error_position(__FILE__, __LINE__);
    fprintf(stderr, "cannot open mesh file %s\n", m_name);
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
  d = m->dim;

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

  pi_1 = double_array_file_scan_by_name(pi_1_name, m->cn[1], pi_1_format);
  if (pi_1 == NULL)
  {
    color_error_position(__FILE__, __LINE__);
    fprintf(stderr,
      "cannot scan pi_1 form file %s in format %s\n",
      pi_1_name, pi_1_format);
    goto m_hodge_free;
  }

  number_of_steps = int_string_scan(number_of_steps_name);
  if (errno)
  {
    color_error_position(__FILE__, __LINE__);
    fprintf(stderr,
      "cannot scan number of steps from string %s\n", number_of_steps_name);
    goto pi_1_free;
  }
  if (number_of_steps < 0)
  {
    color_error_position(__FILE__, __LINE__);
    fprintf(stderr,
      "the number of steps is %d but it must be at least 0\n", number_of_steps);
    goto pi_1_free;
  }

  potential = double_matrix_file_scan_by_name(
    potential_name, number_of_steps + 1, m->cn[0], potential_format);
  if (potential == NULL)
  {
    color_error_position(__FILE__, __LINE__);
    fprintf(stderr,
      "cannot scan potential form file %s in format %s\n",
      potential_name, potential_format);
    goto pi_1_free;
  }

  flow = (double *) calloc(m->cn[d - 1] * (number_of_steps + 1),
                           sizeof(double));
  if (flow == NULL)
  {
    color_error_position(__FILE__, __LINE__);
    fprintf(stderr,
      "cannot allocate allocate %ld bytes of memory for flow\n",
      sizeof(double) * m->cn[d - 1] * (number_of_steps + 1));
    goto potential_free;
  }

  diffusion_transient_discrete_flow_from_potential(
    flow, m, m_bd_1, pi_1, potential, m_hodge[1], number_of_steps);
  if (errno)
  {
    color_error_position(__FILE__, __LINE__);
    fputs("cannot calculate flow %s\n", stderr);
    goto flow_free;
  }

  double_matrix_file_print(
    stdout, number_of_steps + 1, m->cn[d - 1], flow, flow_format);

flow_free:
  free(flow);
potential_free:
  free(potential);
pi_1_free:
  free(pi_1);
m_hodge_free:
  matrix_sparse_array_free(m_hodge, d + 1);
m_bd_1_free:
  matrix_sparse_free(m_bd_1);
m_free:
  mesh_free(m);
end:
  return errno;
}
