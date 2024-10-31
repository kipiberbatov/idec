#include <errno.h>
#include <stdlib.h>

#include <dlfcn.h>

#include "color.h"
#include "double.h"
#include "mesh.h"

typedef void de_rham_dm1_t(double *, const mesh *);

int main(int argc, char ** argv)
{
  char * error, * function_name, * lib_name, * m_format, * m_name,
       * output_format;
  int d;
  double * flow;
  void * lib_handle;
  mesh * m;
  de_rham_dm1_t * function;

#define ARGC 6
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
  lib_name = argv[3];
  function_name = argv[4];
  output_format = argv[5];

  m = mesh_file_scan_by_name(m_name, m_format);
  if (m == NULL)
  {
    color_error_position(__FILE__, __LINE__);
    fprintf(stderr,
      "cannot scan mesh m from file %s in format %s\n", m_name, m_format);
    goto end;
  }
  d = m->dim;

  lib_handle = dlopen(lib_name, RTLD_LAZY);
  if (lib_handle == NULL)
  {
    color_error_position(__FILE__, __LINE__);
    fprintf(stderr, "cannot open dynamic library %s\n", lib_name);
    goto m_free;
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
    fprintf(stderr,
      "cannot allocate %ld bytes of memory for flow\n",
      sizeof(double) * m->cn[d - 1]);
    goto lib_close;
  }

  function(flow, m);
  double_array_file_print(stdout, m->cn[d - 1], flow, output_format);

  free(flow);
lib_close:
  dlclose(lib_name);
m_free:
  mesh_free(m);
end:
  return errno;
}
