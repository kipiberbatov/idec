#include <errno.h>
#include "double.h"
#include "mesh_qc.h"

/* if only one hodge star is needed */

// static void mesh_qc_hodge_codifferential_p_fprint(
//   FILE * out, int m_dim, int p, const cs * m_cbd_m_dim_minus_p, cs ** m_hodge)
// {
//   cs * m_hodge_codifferential_p;
//
//   m_hodge_codifferential_p =
//     mesh_qc_hodge_codifferential_p(m_dim, p, m_cbd_m_dim_minus_p, m_hodge);
//   if (errno)
//   {
//     fprintf(stderr, "During the calculation of *d*_%d", p);
//     perror("");
//     cs_free(m_hodge_codifferential_p);
//     return;
//   }
//   cs_fprint_raw(out, m_hodge_codifferential_p);
//   if (errno)
//   {
//     fprintf(stderr, "Unsuccessful printing of *d*_%d", p);
//     perror("");
//     cs_free(m_hodge_codifferential_p);
//     return;
//   }
//   cs_free(m_hodge_codifferential_p);
// }

static void mesh_qc_hodge_codifferential_fprint(
  FILE * out, int m_dim, cs ** m_cbd, cs ** m_hodge)
{
  int p;
  cs * m_hodge_codifferential_p;
  
  for (p = 1; p <= m_dim; ++p)
  {
    m_hodge_codifferential_p = 
      mesh_qc_hodge_codifferential_p(m_dim, p, m_cbd[m_dim - p], m_hodge);
    if (errno)
    {
      fprintf(stderr, "During the calculation of *d*_%d", p);
      perror("");
      return;
    }
    cs_fprint(out, m_hodge_codifferential_p, "--raw");
    if (errno)
    {
      fprintf(stderr, "Unsuccessful printing of *d*_%d", p);
      perror("");
      cs_free(m_hodge_codifferential_p);
      return;
    }
    if (p < m_dim)
      fputc('\n', out);
    cs_free(m_hodge_codifferential_p);
  }
}

int main()
{
  int m_dim;
  mesh_qc * m;
  cs ** m_bd, ** m_cbd, ** m_hodge;
  FILE * in, * out;
  
  out = stdout;
  in = stdin;
  m = mesh_fscan(in);
  if (errno)
  {
    perror("During mesh scanning");
    return errno;
  }
  m->fc = mesh_fc(m);
  if (errno)
  {
    perror("During calculation of mesh faces to cells");
    mesh_free(m);
    return errno;
  }
  m_dim = m->dim;
  m_bd = mesh_fscan_bd(in, m);
  if (errno)
  {
    perror("During calculation of mesh boundary operator");
    mesh_free(m);
    return errno;
  }
  mesh_free(m);
  m_cbd = mesh_cbd(m_dim, m_bd);
  if (errno)
  {
    perror("During calculation of mesh coboundary operator");
    cs_free_array(m_bd, m_dim);
    return errno;
  }
  cs_free_array(m_bd, m_dim);
  m_hodge = cs_fscan_array(in, m_dim + 1);
  if (!m_hodge)
  {
    perror("During calculation of mesh hodge star operator");
    goto m_cbd_free;
  }
  mesh_qc_hodge_codifferential_fprint(out, m_dim, m_cbd, m_hodge);
  if (errno)
    perror("During purinting of mesh hodge codifferential operator");
  cs_free_array(m_hodge, m_dim + 1);
m_cbd_free:
  cs_free_array(m_cbd, m_dim);
  return 0;
}
