_demo_gtk_diffusion_transient_continuous_2d_d00_p04 :=\
  build/$(MODE)/demo/gtk/diffusion/transient_continuous_2d_d00_p04_primal_strong_cochain_brick_2d_5_forman_trapezoidal_0p001_2500_potential.log\
  build/$(MODE)/demo/gtk/diffusion/transient_continuous_2d_d00_p04_primal_strong_cochain_brick_2d_5_forman_trapezoidal_0p001_2500_flow.log\
  build/$(MODE)/demo/gtk/diffusion/transient_continuous_2d_d00_p04_primal_weak_cochain_brick_2d_5_forman_trapezoidal_0p001_2500_potential.log\
  build/$(MODE)/demo/gtk/diffusion/transient_continuous_2d_d00_p04_primal_weak_cochain_brick_2d_5_forman_trapezoidal_0p001_2500_flow.log\
  build/$(MODE)/demo/gtk/diffusion/transient_continuous_2d_d00_p04_mixed_weak_cochain_brick_2d_5_forman_trapezoidal_0p001_2500_potential.log\
  build/$(MODE)/demo/gtk/diffusion/transient_continuous_2d_d00_p04_mixed_weak_cochain_brick_2d_5_forman_trapezoidal_0p001_2500_flow.log\

.PHONY: demo_gtk_diffusion_transient_continuous_2d_d00_p04
demo_gtk_diffusion_transient_continuous_2d_d00_p04:\
  $(_demo_gtk_diffusion_transient_continuous_2d_d00_p04)

build/$(MODE)/demo/gtk/diffusion/transient_continuous_2d_d00_p04_primal_strong_cochain_brick_2d_5_forman_trapezoidal_0p001_2500_potential.log:\
  build/$(MODE)/bin/gtk_mesh_2d_colored_zero_cochain_sequence$(.EXE)\
  build/$(MODE)/demo/mesh/brick_2d_5_forman.txt\
  build/$(MODE)/demo/diffusion/transient_continuous_2d_d00_p04_primal_strong_cochain_brick_2d_5_forman_trapezoidal_0p001_2500_potential.txt\
  | build/$(MODE)/demo/gtk/diffusion
	$<\
  --raw $(word 2, $^)\
  2500\
  --raw $(word 3, $^)\
  > $@

build/$(MODE)/demo/gtk/diffusion/transient_continuous_2d_d00_p04_primal_strong_cochain_brick_2d_5_forman_trapezoidal_0p001_2500_flow.log:\
  build/$(MODE)/bin/gtk_mesh_2d_colored_one_cochain_sequence$(.EXE)\
  build/$(MODE)/demo/mesh/brick_2d_5_forman.txt\
  build/$(MODE)/demo/diffusion/transient_continuous_2d_d00_p04_primal_strong_cochain_brick_2d_5_forman_trapezoidal_0p001_2500_flow.txt\
  | build/$(MODE)/demo/gtk/diffusion
	$<\
  --raw $(word 2, $^)\
  2500\
  --raw $(word 3, $^)\
  > $@

build/$(MODE)/demo/gtk/diffusion/transient_continuous_2d_d00_p04_primal_weak_cochain_brick_2d_5_forman_trapezoidal_0p001_2500_potential.log:\
  build/$(MODE)/bin/gtk_mesh_2d_colored_zero_cochain_sequence$(.EXE)\
  build/$(MODE)/demo/mesh/brick_2d_5_forman.txt\
  build/$(MODE)/demo/diffusion/transient_continuous_2d_d00_p04_primal_weak_cochain_brick_2d_5_forman_trapezoidal_0p001_2500_potential.txt\
  | build/$(MODE)/demo/gtk/diffusion
	$<\
  --raw $(word 2, $^)\
  2500\
  --raw $(word 3, $^)\
  > $@

build/$(MODE)/demo/gtk/diffusion/transient_continuous_2d_d00_p04_primal_weak_cochain_brick_2d_5_forman_trapezoidal_0p001_2500_flow.log:\
  build/$(MODE)/bin/gtk_mesh_2d_colored_one_cochain_sequence$(.EXE)\
  build/$(MODE)/demo/mesh/brick_2d_5_forman.txt\
  build/$(MODE)/demo/diffusion/transient_continuous_2d_d00_p04_primal_weak_cochain_brick_2d_5_forman_trapezoidal_0p001_2500_flow.txt\
  | build/$(MODE)/demo/gtk/diffusion
	$<\
  --raw $(word 2, $^)\
  2500\
  --raw $(word 3, $^)\
  > $@

build/$(MODE)/demo/gtk/diffusion/transient_continuous_2d_d00_p04_mixed_weak_cochain_brick_2d_5_forman_trapezoidal_0p001_2500_potential.log:\
  build/$(MODE)/bin/gtk_mesh_2d_colored_zero_cochain_sequence$(.EXE)\
  build/$(MODE)/demo/mesh/brick_2d_5_forman.txt\
  build/$(MODE)/demo/diffusion/transient_continuous_2d_d00_p04_mixed_weak_cochain_brick_2d_5_forman_trapezoidal_0p001_2500_potential.txt\
  | build/$(MODE)/demo/gtk/diffusion
	$<\
  --raw $(word 2, $^)\
  2500\
  --raw $(word 3, $^)\
  > $@

build/$(MODE)/demo/gtk/diffusion/transient_continuous_2d_d00_p04_mixed_weak_cochain_brick_2d_5_forman_trapezoidal_0p001_2500_flow.log:\
  build/$(MODE)/bin/gtk_mesh_2d_colored_one_cochain_sequence$(.EXE)\
  build/$(MODE)/demo/mesh/brick_2d_5_forman.txt\
  build/$(MODE)/demo/diffusion/transient_continuous_2d_d00_p04_mixed_weak_cochain_brick_2d_5_forman_trapezoidal_0p001_2500_solution.txt\
  | build/$(MODE)/demo/gtk/diffusion
	$<\
  --raw $(word 2, $^)\
  2500\
  --raw $(word 3, $^)\
  > $@
