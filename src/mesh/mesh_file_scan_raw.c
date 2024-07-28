#include <errno.h>
#include <stdlib.h>
#include "double.h"
#include "int.h"
#include "mesh_private.h"

mesh * mesh_file_scan_raw(FILE * in)
{
  int m_c_size;
  mesh * m;

  m = (mesh *) malloc(sizeof(mesh));
  if (errno)
  {
    perror("mesh_file_scan_raw - cannot allocate memory for m");
    goto end;
  }

  m->dim_embedded = int_file_scan(in);
  if (errno)
  {
    perror("mesh_file_scan_raw - cannot scan m->dim_embedded");
    goto m_free;
  }

  m->dim = int_file_scan(in);
  if (errno)
  {
    perror("mesh_file_scan_raw - cannot scan m->dim");
    goto m_free;
  }

  m->cn = int_array_file_scan(in, m->dim + 1, "--raw");
  if (errno)
  {
    perror("mesh_file_scan_raw - cannot scan m->cn");
    goto m_free;
  }

  m_c_size = int_array_total_sum(m->dim + 1, m->cn);
  m->c = (int * ) malloc(sizeof(int) * m_c_size);
  if (errno)
  {
    fputs("mesh_file_scan_raw - cannot allocate memory for m->c\n", stderr);
    goto m_cn_free;
  }
  mesh_c(m->c, m->dim, m->cn);
  // m->c = int_array_file_scan(in, m_c_size, "--raw");

  m->cf = mesh_cf_file_scan(in, m->dim, m->cn);
  if (errno)
  {
    perror("mesh_file_scan_raw - cannot scan m->cf");
    goto m_c_free;
  }

  m->fc = NULL;

  m->coord = double_matrix_file_scan(in, m->cn[0], m->dim_embedded, "--raw");
  if (errno)
  {
    perror("mesh_file_scan_raw - cannot scan m->coord");
    goto m_cf_free;
  }

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
