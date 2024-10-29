_demo_pdf_diffusion_steady_state_continuous_2d_d03_p00 :=\
  build/$(MODE)/demo/pdf/diffusion/steady_state_continuous_2d_d03_p00_primal_weak_cochain_circular_4_3_forman_potential.pdf\
  build/$(MODE)/demo/pdf/diffusion/steady_state_continuous_2d_d03_p00_primal_weak_cochain_circular_4_3_forman_flow.pdf\
  build/$(MODE)/demo/pdf/diffusion/steady_state_continuous_2d_d03_p00_mixed_weak_cochain_circular_4_3_forman_potential.pdf\
  build/$(MODE)/demo/pdf/diffusion/steady_state_continuous_2d_d03_p00_mixed_weak_cochain_circular_4_3_forman_flow.pdf\
  build/$(MODE)/demo/pdf/diffusion/steady_state_continuous_2d_d03_p00_primal_weak_cochain_circular_17_10_forman_potential.pdf\
  build/$(MODE)/demo/pdf/diffusion/steady_state_continuous_2d_d03_p00_primal_weak_cochain_circular_17_10_forman_flow.pdf\
  build/$(MODE)/demo/pdf/diffusion/steady_state_continuous_2d_d03_p00_mixed_weak_cochain_circular_17_10_forman_potential.pdf\
  build/$(MODE)/demo/pdf/diffusion/steady_state_continuous_2d_d03_p00_mixed_weak_cochain_circular_17_10_forman_flow.pdf\

build/$(MODE)/demo/pdf/diffusion/steady_state_continuous_2d_d03_p00_primal_weak_cochain_circular_4_3_forman_potential.pdf:\
  build/$(MODE)/bin/pdf_mesh_2d_colored_zero_cochain_sequence$(.EXE)\
  build/$(MODE)/demo/mesh/circular_4_3_forman.txt\
  build/$(MODE)/demo/diffusion/steady_state_continuous_2d_d03_p00_primal_weak_cochain_circular_4_3_forman_potential.txt\
  | build/$(MODE)/demo/pdf/diffusion
	$<\
  --raw $(word 2, $^)\
  0\
  --raw $(word 3, $^)\
  $@

build/$(MODE)/demo/pdf/diffusion/steady_state_continuous_2d_d03_p00_primal_weak_cochain_circular_4_3_forman_flow.pdf:\
  build/$(MODE)/bin/pdf_mesh_2d_colored_one_cochain_sequence$(.EXE)\
  build/$(MODE)/demo/mesh/circular_4_3_forman.txt\
  build/$(MODE)/demo/diffusion/steady_state_continuous_2d_d03_p00_primal_weak_cochain_circular_4_3_forman_flow.txt\
  | build/$(MODE)/demo/pdf/diffusion
	$<\
  --raw $(word 2, $^)\
  0\
  --raw $(word 3, $^)\
  $@

build/$(MODE)/demo/pdf/diffusion/steady_state_continuous_2d_d03_p00_mixed_weak_cochain_circular_4_3_forman_potential.pdf:\
  build/$(MODE)/bin/pdf_mesh_2d_colored_zero_cochain_sequence$(.EXE)\
  build/$(MODE)/demo/mesh/circular_4_3_forman.txt\
  build/$(MODE)/demo/diffusion/steady_state_continuous_2d_d03_p00_mixed_weak_cochain_circular_4_3_forman_potential.txt\
  | build/$(MODE)/demo/pdf/diffusion
	$<\
  --raw $(word 2, $^)\
  0\
  --raw $(word 3, $^)\
  $@

build/$(MODE)/demo/pdf/diffusion/steady_state_continuous_2d_d03_p00_mixed_weak_cochain_circular_4_3_forman_flow.pdf:\
  build/$(MODE)/bin/pdf_mesh_2d_colored_one_cochain_sequence$(.EXE)\
  build/$(MODE)/demo/mesh/circular_4_3_forman.txt\
  build/$(MODE)/demo/diffusion/steady_state_continuous_2d_d03_p00_mixed_weak_cochain_circular_4_3_forman_solution.txt\
  | build/$(MODE)/demo/pdf/diffusion
	$<\
  --raw $(word 2, $^)\
  0\
  --steady-state-mixed-weak-solution-flow-raw $(word 3, $^)\
  $@

build/$(MODE)/demo/pdf/diffusion/steady_state_continuous_2d_d03_p00_primal_weak_cochain_circular_17_10_forman_potential.pdf:\
  build/$(MODE)/bin/pdf_mesh_2d_colored_zero_cochain_sequence$(.EXE)\
  build/$(MODE)/demo/mesh/circular_17_10_forman.txt\
  build/$(MODE)/demo/diffusion/steady_state_continuous_2d_d03_p00_primal_weak_cochain_circular_17_10_forman_potential.txt\
  | build/$(MODE)/demo/pdf/diffusion
	$<\
  --raw $(word 2, $^)\
  0\
  --raw $(word 3, $^)\
  $@

build/$(MODE)/demo/pdf/diffusion/steady_state_continuous_2d_d03_p00_primal_weak_cochain_circular_17_10_forman_flow.pdf:\
  build/$(MODE)/bin/pdf_mesh_2d_colored_one_cochain_sequence$(.EXE)\
  build/$(MODE)/demo/mesh/circular_17_10_forman.txt\
  build/$(MODE)/demo/diffusion/steady_state_continuous_2d_d03_p00_primal_weak_cochain_circular_17_10_forman_flow.txt\
  | build/$(MODE)/demo/pdf/diffusion
	$<\
  --raw $(word 2, $^)\
  0\
  --raw $(word 3, $^)\
  $@

build/$(MODE)/demo/pdf/diffusion/steady_state_continuous_2d_d03_p00_mixed_weak_cochain_circular_17_10_forman_potential.pdf:\
  build/$(MODE)/bin/pdf_mesh_2d_colored_zero_cochain_sequence$(.EXE)\
  build/$(MODE)/demo/mesh/circular_17_10_forman.txt\
  build/$(MODE)/demo/diffusion/steady_state_continuous_2d_d03_p00_mixed_weak_cochain_circular_17_10_forman_potential.txt\
  | build/$(MODE)/demo/pdf/diffusion
	$<\
  --raw $(word 2, $^)\
  0\
  --raw $(word 3, $^)\
  $@

build/$(MODE)/demo/pdf/diffusion/steady_state_continuous_2d_d03_p00_mixed_weak_cochain_circular_17_10_forman_flow.pdf:\
  build/$(MODE)/bin/pdf_mesh_2d_colored_one_cochain_sequence$(.EXE)\
  build/$(MODE)/demo/mesh/circular_17_10_forman.txt\
  build/$(MODE)/demo/diffusion/steady_state_continuous_2d_d03_p00_mixed_weak_cochain_circular_17_10_forman_solution.txt\
  | build/$(MODE)/demo/pdf/diffusion
	$<\
  --raw $(word 2, $^)\
  0\
  --steady-state-mixed-weak-solution-flow-raw $(word 3, $^)\
  $@
