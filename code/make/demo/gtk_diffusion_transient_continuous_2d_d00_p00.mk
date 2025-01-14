_demo_gtk_diffusion_transient_continuous_2d_d00_p00 :=\
  build/$(MODE)/demo/gtk/diffusion/transient_continuous_2d_d00_p00_primal_strong_cochain_brick_2d_2_forman_trapezoidal_0p001_1000_potential.log\
  build/$(MODE)/demo/gtk/diffusion/transient_continuous_2d_d00_p00_primal_strong_cochain_brick_2d_2_forman_trapezoidal_0p001_1000_flow.log\
  build/$(MODE)/demo/gtk/diffusion/transient_continuous_2d_d00_p00_primal_weak_cochain_brick_2d_2_forman_trapezoidal_0p001_1000_potential.log\
  build/$(MODE)/demo/gtk/diffusion/transient_continuous_2d_d00_p00_primal_weak_cochain_brick_2d_2_forman_trapezoidal_0p001_1000_flow.log\
  build/$(MODE)/demo/gtk/diffusion/transient_continuous_2d_d00_p00_mixed_weak_cochain_brick_2d_2_forman_trapezoidal_0p001_1000_potential.log\
  build/$(MODE)/demo/gtk/diffusion/transient_continuous_2d_d00_p00_mixed_weak_cochain_brick_2d_2_forman_trapezoidal_0p001_1000_flow.log\

.PHONY: demo_gtk_diffusion_transient_continuous_2d_d00_p00
demo_gtk_diffusion_transient_continuous_2d_d00_p00:\
  $(_demo_gtk_diffusion_transient_continuous_2d_d00_p00)

build/$(MODE)/demo/gtk/diffusion/transient_continuous_2d_d00_p00_primal_strong_cochain_brick_2d_2_forman_trapezoidal_0p001_1000_potential.log:\
  build/$(MODE)/bin/gtk_mesh_2d_colored_zero_cochain_sequence$(.EXE)\
  build/$(MODE)/demo/mesh/brick_2d_2_forman.txt\
  build/$(MODE)/demo/diffusion/transient_continuous_2d_d00_p00_primal_strong_cochain_brick_2d_2_forman_trapezoidal_0p001_1000_potential.txt\
  | build/$(MODE)/demo/gtk/diffusion
	$<\
  --mesh=$(word 2, $^)\
  --number-of-steps=100\
  --cochain-0=$(word 3, $^)\
  --title="2d_d00_p00 primal strong potential"\
  > $@

build/$(MODE)/demo/gtk/diffusion/transient_continuous_2d_d00_p00_primal_strong_cochain_brick_2d_2_forman_trapezoidal_0p001_1000_flow.log:\
  build/$(MODE)/bin/gtk_mesh_2d_colored_one_cochain_sequence$(.EXE)\
  build/$(MODE)/demo/mesh/brick_2d_2_forman.txt\
  build/$(MODE)/demo/diffusion/transient_continuous_2d_d00_p00_primal_strong_cochain_brick_2d_2_forman_trapezoidal_0p001_1000_flow.txt\
  | build/$(MODE)/demo/gtk/diffusion
	$<\
  --mesh=$(word 2, $^)\
  --number-of-steps=100\
  --cochain-1=$(word 3, $^)\
  --title="2d_d00_p00 primal strong flow"\
  > $@

build/$(MODE)/demo/gtk/diffusion/transient_continuous_2d_d00_p00_primal_weak_cochain_brick_2d_2_forman_trapezoidal_0p001_1000_potential.log:\
  build/$(MODE)/bin/gtk_mesh_2d_colored_zero_cochain_sequence$(.EXE)\
  build/$(MODE)/demo/mesh/brick_2d_2_forman.txt\
  build/$(MODE)/demo/diffusion/transient_continuous_2d_d00_p00_primal_weak_cochain_brick_2d_2_forman_trapezoidal_0p001_1000_potential.txt\
  | build/$(MODE)/demo/gtk/diffusion
	$<\
  --mesh=$(word 2, $^)\
  --number-of-steps=100\
  --cochain-0=$(word 3, $^)\
  --title="2d_d00_p00 primal weak potential"\
  > $@

build/$(MODE)/demo/gtk/diffusion/transient_continuous_2d_d00_p00_primal_weak_cochain_brick_2d_2_forman_trapezoidal_0p001_1000_flow.log:\
  build/$(MODE)/bin/gtk_mesh_2d_colored_one_cochain_sequence$(.EXE)\
  build/$(MODE)/demo/mesh/brick_2d_2_forman.txt\
  build/$(MODE)/demo/diffusion/transient_continuous_2d_d00_p00_primal_weak_cochain_brick_2d_2_forman_trapezoidal_0p001_1000_flow.txt\
  | build/$(MODE)/demo/gtk/diffusion
	$<\
  --mesh=$(word 2, $^)\
  --number-of-steps=100\
  --cochain-1=$(word 3, $^)\
  --title="2d_d00_p00 primal weak flow"\
  > $@

build/$(MODE)/demo/gtk/diffusion/transient_continuous_2d_d00_p00_mixed_weak_cochain_brick_2d_2_forman_trapezoidal_0p001_1000_potential.log:\
  build/$(MODE)/bin/gtk_mesh_2d_colored_zero_cochain_sequence$(.EXE)\
  build/$(MODE)/demo/mesh/brick_2d_2_forman.txt\
  build/$(MODE)/demo/diffusion/transient_continuous_2d_d00_p00_mixed_weak_cochain_brick_2d_2_forman_trapezoidal_0p001_1000_potential.txt\
  | build/$(MODE)/demo/gtk/diffusion
	$<\
  --mesh=$(word 2, $^)\
  --number-of-steps=1000\
  --cochain-0=$(word 3, $^)\
  --title="2d_d00_p00 mixed weak potential"\
  > $@

build/$(MODE)/demo/gtk/diffusion/transient_continuous_2d_d00_p00_mixed_weak_cochain_brick_2d_2_forman_trapezoidal_0p001_1000_flow.log:\
  build/$(MODE)/bin/gtk_mesh_2d_colored_one_cochain_sequence$(.EXE)\
  build/$(MODE)/demo/mesh/brick_2d_2_forman.txt\
  build/$(MODE)/demo/diffusion/transient_continuous_2d_d00_p00_mixed_weak_cochain_brick_2d_2_forman_trapezoidal_0p001_1000_solution.txt\
  | build/$(MODE)/demo/gtk/diffusion
	$<\
  --mesh=$(word 2, $^)\
  --number-of-steps=1000\
  --cochain-1=$(word 3, $^)\
  --title="2d_d00_p00 mixed weak flow"\
  > $@

.PHONY: demo_gtk_diffusion_transient_continuous_2d_d00_p00
demo_gtk_diffusion_transient_continuous_2d_d00_p00:\
  $(_demo_gtk_diffusion_transient_continuous_2d_d00_p00)

.PHONY: demo_gtk_diffusion_transient_continuous_2d_d00_p00_clean
demo_gtk_diffusion_transient_continuous_2d_d00_p00_clean:
	-$(RM) $(_demo_gtk_diffusion_transient_continuous_2d_d00_p00)
