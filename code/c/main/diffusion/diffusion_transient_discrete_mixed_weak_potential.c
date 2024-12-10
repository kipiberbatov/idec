#include <errno.h>
#include <stdlib.h>
#include <string.h>

#include "color.h"
#include "diffusion_transient_discrete_mixed_weak.h"
#include "double.h"
#include "int.h"
#include "mesh_qc.h"

int main(int argc, char ** argv)
{
  char * data_name, * m_vol_format, * m_vol_name, * m_format, * m_name,
       * number_of_steps_name, * solution_name;
  int d, m_cn_dm1, m_cn_0, m_cn_d, number_of_steps, s;
  int * m_cn;
  double * flow, * potential, * dual_potential;
  double ** m_vol;
  FILE * data_file, * m_file, * solution_file;
  mesh * m;
  diffusion_transient_discrete_mixed_weak * data;

#define ARGC 8
  if (argc != ARGC)
  {
    color_error_position(__FILE__, __LINE__);
    fprintf(stderr,
      "the number of command-line arguments must be %d; instead it is %d\n",
      ARGC, argc);
    errno = EINVAL;
    goto end;
  }

  m_format = argv[1];
  m_name = argv[2];
  m_vol_format = argv[3];
  m_vol_name = argv[4];
  data_name = argv[5];
  number_of_steps_name = argv[6];
  solution_name = argv[7];

  m_file = fopen(m_name, "r");
  if (m_file == NULL)
  {
    color_error_position(__FILE__, __LINE__);
    fprintf(stderr, "cannot open mesh file %s: %s\n", m_name, strerror(errno));
    goto end;
  }

  m = mesh_file_scan_by_name(m_name, m_format);
  if (m == NULL)
  {
    color_error_position(__FILE__, __LINE__);
    fprintf(stderr,
      "cannot scan mesh m from file %s in format %s\n", m_name, m_format);
    goto end;
  }

  d = m->dim;
  m_cn = m->cn;
  m_cn_0 = m_cn[0];
  m_cn_dm1 = m_cn[d - 1];
  m_cn_d = m_cn[d];

  m->fc = mesh_fc(m);
  if (m->fc == NULL)
  {
    color_error_position(__FILE__, __LINE__);
    fputs("cannot calculate m->fc\n", stderr);
    goto m_free;
  }

  m_vol = double_array2_file_scan_by_name(
    m_vol_name, d + 1, m_cn, m_vol_format);
  if (m_vol == NULL)
  {
    color_error_position(__FILE__, __LINE__);
    fprintf(stderr,
      "cannot scan cells' measures from file %s in format %s\n",
      m_vol_name, m_vol_format);
    goto m_free;
  }

  data_file = fopen(data_name, "r");
  if (data_file == NULL)
  {
    color_error_position(__FILE__, __LINE__);
    fprintf(stderr,
      "cannot open problem data file %s: %s\n", data_name, strerror(errno));
    goto m_vol_free;
  }
  data = diffusion_transient_discrete_mixed_weak_file_scan_raw(data_file);
  if (data == NULL)
  {
    color_error_position(__FILE__, __LINE__);
    fprintf(stderr, "cannot scan problem data from file %s\n", data_name);
    fclose(data_file);
    goto m_vol_free;
  }
  fclose(data_file);

  number_of_steps = int_string_scan(number_of_steps_name);
  if (errno)
  {
    color_error_position(__FILE__, __LINE__);
    fprintf(stderr,
      "cannot scan number of steps from string %s\n", number_of_steps_name);
    goto data_free;
  }
  if (number_of_steps < 0)
  {
    color_error_position(__FILE__, __LINE__);
    fprintf(stderr,
      "the number of steps is %d but it must be at least 0\n", number_of_steps);
    goto data_free;
  }

  solution_file = fopen(solution_name, "r");
  if (solution_file == NULL)
  {
    color_error_position(__FILE__, __LINE__);
    fprintf(stderr,
      "cannot open problem solution file %s: %s\n",
      solution_name, strerror(errno));
    goto data_free;
  }

  flow = double_matrix_file_scan(solution_file,
    number_of_steps + 1, m_cn_dm1, "--raw");
  if (flow == NULL)
  {
    color_error_position(__FILE__, __LINE__);
    fprintf(stderr,
      "cannot scan flow from file in format 'raw' %s\n", solution_name);
    fclose(solution_file);
    goto data_free;
  }
  free(flow);

  dual_potential = double_matrix_file_scan(solution_file,
    number_of_steps + 1, m_cn_d, "--raw");
  if (dual_potential == NULL)
  {
    color_error_position(__FILE__, __LINE__);
    fprintf(stderr,
      "cannot scan dual_potential from file in format 'raw' %s\n",
      solution_name);
    fclose(solution_file);
    goto data_free;
  }
  fclose(solution_file);

  potential = (double *) malloc(
    sizeof(double) * (number_of_steps + 1) * m_cn_0);
  if (potential == NULL)
  {
    color_error_position(__FILE__, __LINE__);
    fprintf(stderr, "cannot allocate %ld bytes of memory for potential",
      sizeof(double) * (number_of_steps + 1) * m_cn_0);
    goto dual_potential_free;
  }

  for (s = 0; s <= number_of_steps; ++s)
  {
    mesh_qc_hodge_star_d(potential + m_cn_0 * s,
      m, m_vol[d], dual_potential + m_cn_d * s);
    double_array_assemble_from_sparse_array(
      potential + m_cn_0 * s, data->boundary_dirichlet_0, data->g_dirichlet_0);
  }

  double_matrix_file_print(stdout,
    number_of_steps + 1, m_cn_0, potential, "--raw");

  free(potential);
dual_potential_free:
  free(dual_potential);
data_free:
  diffusion_transient_discrete_mixed_weak_free(data);
m_vol_free:
  double_array2_free(m_vol, d + 1);
m_free:
  mesh_free(m);
end:
  return errno;
}
