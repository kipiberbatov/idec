#include <errno.h>
#include <stdlib.h>

#include <dlfcn.h>

#include "double.h"
#include "diffusion_transient_continuous.h"
#include "diffusion_transient_discrete_dual_flow_from_potential.h"
#include "int.h"
#include "unsigned_approximation.h"

int main(int argc, char ** argv)
{
  char * data_name, * error, * dual_flow_format, * lib_name, * m_format, * m_name,
       * m_bd_1_name, * number_of_steps_name, * potential_format,
       * potential_name;
  int i, number_of_steps;
  double * dual_flow, * pi_1, * potential;
  void * lib_handle;
  const diffusion_transient_continuous * data;
  mesh * m;
  matrix_sparse * m_bd_1;
  FILE * m_file, * m_bd_1_file;

#define ARGC 10
  if (argc != ARGC)
  {
    fprintf(stderr,
      "%s:%d: number of command line arguments should be %d, not %d\n",
      __FILE__, __LINE__, ARGC, argc);
    for (i = 0; i < argc; ++i)
      fprintf(stderr, "%d: %s\n", i, argv[i]);
    return EINVAL;
  }

  m_format = argv[1];
  m_name = argv[2];
  m_file = fopen(m_name, "r");
  if (errno)
  {
    fprintf(stderr,
      "%s:%d: cannot open file %s\n", __FILE__, __LINE__, m_name);
    goto end;
  }
  m = mesh_file_scan(m_file, m_format);
  if (errno)
  {
    fprintf(stderr, "%s:%d: cannot scan mesh m\n", __FILE__, __LINE__);
    fclose(m_file);
    goto end;
  }


  m_bd_1_name = argv[3];
  if (m_bd_1_name[1] == 0 && m_bd_1_name[0] == '-')
  {
    m_bd_1 = mesh_file_scan_boundary_p(m_file, m, 1);
    if (errno)
    {
      fprintf(stderr,
        "%s:%d: cannot scan m_bd_1 from file %s\n",__FILE__, __LINE__, m_name);
      goto m_free;
    }
    fclose(m_file);
  }
  else
  {
    fclose(m_file);
    m_bd_1_file = fopen(m_bd_1_name, "r");
    if (errno)
    {
      fprintf(stderr,
        "%s:%d: cannot open file %s\n", __FILE__, __LINE__, m_bd_1_name);
      goto m_free;
    }
    m_bd_1 = mesh_file_scan_boundary_p(m_bd_1_file, m, 1);
    if (errno)
    {
      fprintf(stderr,
        "%s:%d: cannot scan sparse matrix m_bd_1\n", __FILE__, __LINE__);
      fclose(m_bd_1_file);
      goto m_free;
    }
    fclose(m_bd_1_file);
  }

  lib_name = argv[4];
  lib_handle = dlopen(lib_name, RTLD_LAZY);
  if (!lib_handle)
  {
    fprintf(stderr,
      "%s:%d: cannot open library %s\n", __FILE__, __LINE__, lib_name);
    goto m_bd_1_free;
  }
  /* clear any existing errors */
  dlerror();

  data_name = argv[5];
  data = (const diffusion_transient_continuous *) dlsym(lib_handle, data_name);
  error = dlerror();
  if (error)
  {
    fprintf(stderr,
      "%s:%d: cannot read %s: %s\n", __FILE__, __LINE__, data_name, error);
    goto lib_close;
  }

  number_of_steps_name = argv[6];
  number_of_steps = int_string_scan(number_of_steps_name);
  if (errno)
  {
    fprintf(stderr, "%s:%d: cannot scan number_of_steps\n", __FILE__, __LINE__);
    goto m_free;
  }

  potential_format = argv[7];
  potential_name = argv[8];
  potential = double_array_file_scan_by_name(
    potential_name, m->cn[0] * (number_of_steps + 1), potential_format);
  if (errno)
  {
    fprintf(stderr, "%s:%d: cannot scan potential\n", __FILE__, __LINE__);
    goto lib_close;
  }

  pi_1 = (double *) malloc(sizeof(double) * m->cn[1]);
  if (errno)
    goto potential_free;
  unsigned_approximation_of_scalar_field_on_1_cells(pi_1, m, data->pi_1);

  dual_flow = (double *) malloc(sizeof(double) * m->cn[1] * (number_of_steps + 1));
  if (errno)
  {
    fprintf(stderr,
      "%s:%d: cannot allocate memory for dual_flow\n", __FILE__, __LINE__);
    goto pi_1_free;
  }

  diffusion_transient_discrete_dual_flow_from_potential(
    dual_flow, m, m_bd_1, pi_1, number_of_steps, potential);

  dual_flow_format = argv[9];
  double_matrix_file_print(
    stdout, number_of_steps + 1, m->cn[1], dual_flow, dual_flow_format);

  free(dual_flow);
pi_1_free:
  free(pi_1);
potential_free:
  free(potential);
lib_close:
  dlclose(lib_handle);
m_bd_1_free:
  matrix_sparse_free(m_bd_1);
m_free:
  mesh_free(m);
end:
  return errno;
}
