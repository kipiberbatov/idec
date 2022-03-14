#include <errno.h>
#include "mesh.h"

cs * mesh_qc_hodge_codifferential_p(
  int m_dim, int p, const cs * m_cbd_m_dim_minus_p, cs ** m_hodge)
{
  cs * tmp, * m_hodge_codifferential_p;
  
  tmp = cs_multiply(m_cbd_m_dim_minus_p, m_hodge[p]);
  if (errno)
  {
    perror("During the calculation of d*");
    cs_free(tmp);
    return NULL;
  }
  //cs_fprint_matrix_form_curly(stderr, tmp);
  m_hodge_codifferential_p = cs_multiply(m_hodge[m_dim - p + 1], tmp);
  if (errno)
  {
    perror("During the calculation of *d*");
    cs_free(m_hodge_codifferential_p);
    cs_free(tmp);
    return NULL;
  }
  cs_free(tmp);
  return m_hodge_codifferential_p;
}

cs ** mesh_qc_hodge_codifferential(int m_dim, cs ** m_cbd, cs ** m_hodge)
{
  int p;
  cs ** m_hodge_codifferential;
  
  m_hodge_codifferential = (cs **) malloc(m_dim * sizeof(cs *));
  if (errno)
  {
    perror("During memory allocation for m_hodge_codifferential");
    return NULL;
  }
  for (p = 1; p <= m_dim; ++p)
  {
    m_hodge_codifferential[p - 1] = 
      mesh_qc_hodge_codifferential_p(m_dim, p, m_cbd[m_dim - p], m_hodge);
    if (errno)
    {
      fprintf(stderr, "During the calculation of *d*_%d", p);
      perror("");
      cs_free_array(m_hodge_codifferential, m_dim);
      return NULL;
    }
  }
  return m_hodge_codifferential;
}
