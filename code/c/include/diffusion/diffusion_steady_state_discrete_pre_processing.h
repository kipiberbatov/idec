#ifndef _diffusion_steady_state_discrete_pre_processing_h
#define _diffusion_steady_state_discrete_pre_processing_h

struct jagged1;
struct mesh;

struct diffusion_steady_state_discrete_pre_processing
{
  void (*get_conductivity)(
    double *,                    /* conductivity_discrete   */
    const struct mesh *,         /* m                       */
    double (*)(const double *)); /* conductivity_continuous */

  void (*get_dual_conductivity)(
    double *,                    /* dual_conductivity_discrete   */
    const struct mesh *,         /* m                            */
    double (*)(const double *)); /* dual_conductivity_continuous */

  void (*get_production_rate)(
    double *,                    /* production_rate_discrete   */
    const struct mesh *,         /* m                          */
    const double *,              /* m_vol_d                    */
    double (*)(const double *)); /* production_rate_continuous */

  void (*get_boundary_dirichlet_dm1)(
    struct jagged1 **,         /* boundary_dirichlet_dm1_discrete */
    int *,                     /* status                          */
    const struct mesh *,       /* m                               */
    const struct jagged1 *,    /* m_boundary_dm1                  */
    int (*)(const double *));  /* boundary_dirichlet_continuous   */

  void (*get_g_dirichlet)(
    double *,                    /* g_dirichlet_discrete          */
    const struct mesh *,         /* m                             */
    const struct jagged1 *,      /* boundary_dirichlet_0_discrete */
    double (*)(const double *)); /* g_dirichlet_continuous        */

  void (*get_g_neumann)(
    double *,                     /* g_neumann_discrete            */
    const struct mesh *,          /* m                             */
    const double *,               /* m_vol_dm1                     */
    const struct jagged1 *,      /* boundary_neumann_dm1_discrete */
    double (*)(const double *)); /* g_neumann_continuous          */
};

#endif /* _diffusion_steady_state_discrete_pre_processing_h */
