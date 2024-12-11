#include <errno.h>
#include <stdlib.h>
#include <string.h>

#include <dlfcn.h>

#include "color.h"
#include "double.h"
#include "idec_error_message.h"
#include "mesh.h"

typedef void de_rham_dm1_t(double *, const mesh *, const matrix_sparse *);

int main(int argc, char ** argv)
{
  char * error, * function_name, * lib_name, * m_format, * m_name,
       * output_format;
  int d;
  double * flow;
  void * lib_handle;
  FILE * m_file;
  mesh * m;
  matrix_sparse * m_bd_1;
  de_rham_dm1_t * function;

#define ARGC 6
  if (argc != ARGC)
  {
    color_error_position(__FILE__, __LINE__);
    idec_error_message_number_of_command_line_arguments_mismatch(ARGC, argc);
    errno = EINVAL;
    goto end;
  }

  m_format = argv[1];
  m_name = argv[2];
  lib_name = argv[3];
  function_name = argv[4];
  output_format = argv[5];

  m_file = fopen(m_name, "r");
  if (m_file == NULL)
  {
    color_error_position(__FILE__, __LINE__);
    fprintf(stderr, "cannot open mesh file %s: %s\n", m_name, strerror(errno));
    goto end;
  }

  m = mesh_file_scan(m_file, m_format);
  if (m == NULL)
  {
    color_error_position(__FILE__, __LINE__);
    fprintf(stderr, "cannot scan mesh m from file %s in format %s\n",
      m_name, m_format);
    fclose(m_file);
    goto end;
  }

  m_bd_1 = mesh_file_scan_boundary_p(m_file, m, 1);
  if (m_bd_1 == NULL)
  {
    color_error_position(__FILE__, __LINE__);
    fprintf(stderr, "cannot scan m_bd_1 m from file %s\n", m_name);
    fclose(m_file);
    goto m_free;
  }
  fclose(m_file);
  d = m->dim;

  lib_handle = dlopen(lib_name, RTLD_LAZY);
  if (lib_handle == NULL)
  {
    color_error_position(__FILE__, __LINE__);
    fprintf(stderr, "cannot open dynamic library %s\n", lib_name);
    goto m_bd_1_free;
  }
  /* clear any existing errors */
  dlerror();

  function = (de_rham_dm1_t *) dlsym(lib_handle, function_name);
  error = dlerror();
  if (error)
  {
    color_error_position(__FILE__, __LINE__);
    fprintf(stderr, "%s\n", error);
    goto lib_close;
  }

  flow = (double *) malloc(sizeof(double) * m->cn[d - 1]);
  if (flow == NULL)
  {
    color_error_position(__FILE__, __LINE__);
    idec_error_message_malloc(sizeof(double) * m->cn[d - 1], "flow");
    goto lib_close;
  }

  function(flow, m, m_bd_1);
  double_array_file_print(stdout, m->cn[d - 1], flow, output_format);

  free(flow);
lib_close:
  dlclose(lib_name);
m_bd_1_free:
  matrix_sparse_free(m_bd_1);
m_free:
  mesh_free(m);
end:
  return errno;
}
