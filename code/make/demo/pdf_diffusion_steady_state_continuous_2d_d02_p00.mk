_demo_pdf_diffusion_steady_state_continuous_2d_d02_p00 :=\
  build/$(MODE)/demo/pdf/diffusion/steady_state_continuous_2d_d02_p00_exact_2d_10_grains_forman_potential.pdf\
  build/$(MODE)/demo/pdf/diffusion/steady_state_continuous_2d_d02_p00_exact_2d_10_grains_forman_flow.pdf\
  build/$(MODE)/demo/pdf/diffusion/steady_state_continuous_2d_d02_p00_primal_strong_cochain_2d_10_grains_forman_potential.pdf\
  build/$(MODE)/demo/pdf/diffusion/steady_state_continuous_2d_d02_p00_primal_strong_cochain_2d_10_grains_forman_flow.pdf\
  build/$(MODE)/demo/pdf/diffusion/steady_state_continuous_2d_d02_p00_primal_weak_cochain_2d_10_grains_forman_potential.pdf\
  build/$(MODE)/demo/pdf/diffusion/steady_state_continuous_2d_d02_p00_primal_weak_cochain_2d_10_grains_forman_flow.pdf\
  build/$(MODE)/demo/pdf/diffusion/steady_state_continuous_2d_d02_p00_mixed_weak_cochain_2d_10_grains_forman_potential.pdf\
  build/$(MODE)/demo/pdf/diffusion/steady_state_continuous_2d_d02_p00_mixed_weak_cochain_2d_10_grains_forman_flow.pdf\

build/$(MODE)/demo/pdf/diffusion/steady_state_continuous_2d_d02_p00_exact_2d_10_grains_forman_potential.pdf:\
  build/$(MODE)/bin/pdf_mesh_2d_colored_zero_cochain_sequence$(.EXE)\
  build/$(MODE)/demo/mesh/2d_10_grains_forman.txt\
  build/$(MODE)/demo/diffusion/steady_state_continuous_2d_d02_p00_exact_2d_10_grains_forman_potential.txt\
  | build/$(MODE)/demo/pdf/diffusion
	$<\
  --raw $(word 2, $^)\
  0\
  --raw $(word 3, $^)\
  $@

build/$(MODE)/demo/pdf/diffusion/steady_state_continuous_2d_d02_p00_exact_2d_10_grains_forman_flow.pdf:\
  build/$(MODE)/bin/pdf_mesh_2d_colored_one_cochain_sequence$(.EXE)\
  build/$(MODE)/demo/mesh/2d_10_grains_forman.txt\
  build/$(MODE)/demo/diffusion/steady_state_continuous_2d_d02_p00_exact_2d_10_grains_forman_flow.txt\
  | build/$(MODE)/demo/pdf/diffusion
	$<\
  --raw $(word 2, $^)\
  0\
  --raw $(word 3, $^)\
  $@

build/$(MODE)/demo/pdf/diffusion/steady_state_continuous_2d_d02_p00_primal_strong_cochain_2d_10_grains_forman_potential.pdf:\
  build/$(MODE)/bin/pdf_mesh_2d_colored_zero_cochain_sequence$(.EXE)\
  build/$(MODE)/demo/mesh/2d_10_grains_forman.txt\
  build/$(MODE)/demo/diffusion/steady_state_continuous_2d_d02_p00_primal_strong_cochain_2d_10_grains_forman_potential.txt\
  | build/$(MODE)/demo/pdf/diffusion
	$<\
  --raw $(word 2, $^)\
  0\
  --raw $(word 3, $^)\
  $@

build/$(MODE)/demo/pdf/diffusion/steady_state_continuous_2d_d02_p00_primal_strong_cochain_2d_10_grains_forman_flow.pdf:\
  build/$(MODE)/bin/pdf_mesh_2d_colored_one_cochain_sequence$(.EXE)\
  build/$(MODE)/demo/mesh/2d_10_grains_forman.txt\
  build/$(MODE)/demo/diffusion/steady_state_continuous_2d_d02_p00_primal_strong_cochain_2d_10_grains_forman_flow.txt\
  | build/$(MODE)/demo/pdf/diffusion
	$<\
  --raw $(word 2, $^)\
  0\
  --raw $(word 3, $^)\
  $@

build/$(MODE)/demo/pdf/diffusion/steady_state_continuous_2d_d02_p00_primal_weak_cochain_2d_10_grains_forman_potential.pdf:\
  build/$(MODE)/bin/pdf_mesh_2d_colored_zero_cochain_sequence$(.EXE)\
  build/$(MODE)/demo/mesh/2d_10_grains_forman.txt\
  build/$(MODE)/demo/diffusion/steady_state_continuous_2d_d02_p00_primal_weak_cochain_2d_10_grains_forman_potential.txt\
  | build/$(MODE)/demo/pdf/diffusion
	$<\
  --raw $(word 2, $^)\
  0\
  --raw $(word 3, $^)\
  $@

build/$(MODE)/demo/pdf/diffusion/steady_state_continuous_2d_d02_p00_primal_weak_cochain_2d_10_grains_forman_flow.pdf:\
  build/$(MODE)/bin/pdf_mesh_2d_colored_one_cochain_sequence$(.EXE)\
  build/$(MODE)/demo/mesh/2d_10_grains_forman.txt\
  build/$(MODE)/demo/diffusion/steady_state_continuous_2d_d02_p00_primal_weak_cochain_2d_10_grains_forman_flow.txt\
  | build/$(MODE)/demo/pdf/diffusion
	$<\
  --raw $(word 2, $^)\
  0\
  --raw $(word 3, $^)\
  $@

build/$(MODE)/demo/pdf/diffusion/steady_state_continuous_2d_d02_p00_mixed_weak_cochain_2d_10_grains_forman_potential.pdf:\
  build/$(MODE)/bin/pdf_mesh_2d_colored_zero_cochain_sequence$(.EXE)\
  build/$(MODE)/demo/mesh/2d_10_grains_forman.txt\
  build/$(MODE)/demo/diffusion/steady_state_continuous_2d_d02_p00_mixed_weak_cochain_2d_10_grains_forman_potential.txt\
  | build/$(MODE)/demo/pdf/diffusion
	$<\
  --raw $(word 2, $^)\
  0\
  --raw $(word 3, $^)\
  $@

build/$(MODE)/demo/pdf/diffusion/steady_state_continuous_2d_d02_p00_mixed_weak_cochain_2d_10_grains_forman_flow.pdf:\
  build/$(MODE)/bin/pdf_mesh_2d_colored_one_cochain_sequence$(.EXE)\
  build/$(MODE)/demo/mesh/2d_10_grains_forman.txt\
  build/$(MODE)/demo/diffusion/steady_state_continuous_2d_d02_p00_mixed_weak_cochain_2d_10_grains_forman_solution.txt\
  | build/$(MODE)/demo/pdf/diffusion
	$<\
  --raw $(word 2, $^)\
  0\
  --steady-state-mixed-weak-solution-flow-raw $(word 3, $^)\
  $@
