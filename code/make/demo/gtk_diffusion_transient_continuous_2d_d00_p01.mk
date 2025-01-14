_demo_gtk_diffusion_transient_continuous_2d_d00_p01 :=\
  build/$(MODE)/demo/gtk/diffusion/transient_continuous_2d_d00_p01_primal_strong_cochain_brick_2d_5_forman_trapezoidal_0p001_2500_potential.log\
  build/$(MODE)/demo/gtk/diffusion/transient_continuous_2d_d00_p01_primal_strong_cochain_brick_2d_5_forman_trapezoidal_0p001_2500_flow.log\
  build/$(MODE)/demo/gtk/diffusion/transient_continuous_2d_d00_p01_primal_weak_cochain_brick_2d_5_forman_trapezoidal_0p001_2500_potential.log\
  build/$(MODE)/demo/gtk/diffusion/transient_continuous_2d_d00_p01_primal_weak_cochain_brick_2d_5_forman_trapezoidal_0p001_2500_flow.log\
  build/$(MODE)/demo/gtk/diffusion/transient_continuous_2d_d00_p01_mixed_weak_cochain_brick_2d_5_forman_trapezoidal_0p001_2500_potential.log\
  build/$(MODE)/demo/gtk/diffusion/transient_continuous_2d_d00_p01_mixed_weak_cochain_brick_2d_5_forman_trapezoidal_0p001_2500_flow.log\

.PHONY: demo_gtk_diffusion_transient_continuous_2d_d00_p01
demo_gtk_diffusion_transient_continuous_2d_d00_p01:\
  $(_demo_gtk_diffusion_transient_continuous_2d_d00_p01)

build/$(MODE)/demo/gtk/diffusion/transient_continuous_2d_d00_p01_primal_strong_cochain_brick_2d_5_forman_trapezoidal_0p001_2500_potential.log:\
  build/$(MODE)/bin/gtk_mesh_2d_colored_zero_cochain_sequence$(.EXE)\
  build/$(MODE)/demo/mesh/brick_2d_5_forman.txt\
  build/$(MODE)/demo/diffusion/transient_continuous_2d_d00_p01_primal_strong_cochain_brick_2d_5_forman_trapezoidal_0p001_2500_potential.txt\
  | build/$(MODE)/demo/gtk/diffusion
	$<\
  --mesh=$(word 2, $^)\
  --number-of-steps=2500\
  --cochain-0=$(word 3, $^)\
  --title="2d_d00_p01 primal strong potential"\
  > $@

build/$(MODE)/demo/gtk/diffusion/transient_continuous_2d_d00_p01_primal_strong_cochain_brick_2d_5_forman_trapezoidal_0p001_2500_flow.log:\
  build/$(MODE)/bin/gtk_mesh_2d_colored_one_cochain_sequence$(.EXE)\
  build/$(MODE)/demo/mesh/brick_2d_5_forman.txt\
  build/$(MODE)/demo/diffusion/transient_continuous_2d_d00_p01_primal_strong_cochain_brick_2d_5_forman_trapezoidal_0p001_2500_flow.txt\
  | build/$(MODE)/demo/gtk/diffusion
	$<\
  --mesh=$(word 2, $^)\
  --number-of-steps=2500\
  --cochain-1=$(word 3, $^)\
  --title="2d_d00_p01 primal strong flow"\
  > $@

build/$(MODE)/demo/gtk/diffusion/transient_continuous_2d_d00_p01_primal_weak_cochain_brick_2d_5_forman_trapezoidal_0p001_2500_potential.log:\
  build/$(MODE)/bin/gtk_mesh_2d_colored_zero_cochain_sequence$(.EXE)\
  build/$(MODE)/demo/mesh/brick_2d_5_forman.txt\
  build/$(MODE)/demo/diffusion/transient_continuous_2d_d00_p01_primal_weak_cochain_brick_2d_5_forman_trapezoidal_0p001_2500_potential.txt\
  | build/$(MODE)/demo/gtk/diffusion
	$<\
  --mesh=$(word 2, $^)\
  --number-of-steps=2500\
  --cochain-0=$(word 3, $^)\
  --title="2d_d00_p01 primal weak potential"\
  > $@

build/$(MODE)/demo/gtk/diffusion/transient_continuous_2d_d00_p01_primal_weak_cochain_brick_2d_5_forman_trapezoidal_0p001_2500_flow.log:\
  build/$(MODE)/bin/gtk_mesh_2d_colored_one_cochain_sequence$(.EXE)\
  build/$(MODE)/demo/mesh/brick_2d_5_forman.txt\
  build/$(MODE)/demo/diffusion/transient_continuous_2d_d00_p01_primal_weak_cochain_brick_2d_5_forman_trapezoidal_0p001_2500_flow.txt\
  | build/$(MODE)/demo/gtk/diffusion
	$<\
  --mesh=$(word 2, $^)\
  --number-of-steps=2500\
  --cochain-1=$(word 3, $^)\
  --title="2d_d00_p01 primal weak flow"\
  > $@

build/$(MODE)/demo/gtk/diffusion/transient_continuous_2d_d00_p01_mixed_weak_cochain_brick_2d_5_forman_trapezoidal_0p001_2500_potential.log:\
  build/$(MODE)/bin/gtk_mesh_2d_colored_zero_cochain_sequence$(.EXE)\
  build/$(MODE)/demo/mesh/brick_2d_5_forman.txt\
  build/$(MODE)/demo/diffusion/transient_continuous_2d_d00_p01_mixed_weak_cochain_brick_2d_5_forman_trapezoidal_0p001_2500_potential.txt\
  | build/$(MODE)/demo/gtk/diffusion
	$<\
  --mesh=$(word 2, $^)\
  --number-of-steps=2500\
  --cochain-0=$(word 3, $^)\
  --title="2d_d00_p01 mixed_weak potential"\
  > $@

build/$(MODE)/demo/gtk/diffusion/transient_continuous_2d_d00_p01_mixed_weak_cochain_brick_2d_5_forman_trapezoidal_0p001_2500_flow.log:\
  build/$(MODE)/bin/gtk_mesh_2d_colored_one_cochain_sequence$(.EXE)\
  build/$(MODE)/demo/mesh/brick_2d_5_forman.txt\
  build/$(MODE)/demo/diffusion/transient_continuous_2d_d00_p01_mixed_weak_cochain_brick_2d_5_forman_trapezoidal_0p001_2500_solution.txt\
  | build/$(MODE)/demo/gtk/diffusion
	$<\
  --mesh=$(word 2, $^)\
  --number-of-steps=2500\
  --cochain-1=$(word 3, $^)\
  --title="2d_d00_p01 mixed weak flow"\
  > $@
