_demo_pdf_diffusion_transient_continuous_2d_d00_p00 :=\
  build/$(MODE)/demo/pdf/diffusion/transient_continuous_2d_d00_p00_primal_strong_cochain_brick_2d_2_forman_trapezoidal_0p001_1000_potential.pdf\
  build/$(MODE)/demo/pdf/diffusion/transient_continuous_2d_d00_p00_primal_strong_cochain_brick_2d_2_forman_trapezoidal_0p001_1000_flow.pdf\
  build/$(MODE)/demo/pdf/diffusion/transient_continuous_2d_d00_p00_primal_weak_cochain_brick_2d_2_forman_trapezoidal_0p001_1000_potential.pdf\
  build/$(MODE)/demo/pdf/diffusion/transient_continuous_2d_d00_p00_primal_weak_cochain_brick_2d_2_forman_trapezoidal_0p001_1000_flow.pdf\

build/$(MODE)/demo/pdf/diffusion/transient_continuous_2d_d00_p00_primal_strong_cochain_brick_2d_2_forman_trapezoidal_0p001_1000_potential.pdf:\
  build/$(MODE)/bin/pdf_mesh_2d_colored_zero_cochain_sequence$(.EXE)\
  build/$(MODE)/demo/mesh/brick_2d_2_forman.txt\
  build/$(MODE)/demo/diffusion/transient_continuous_2d_d00_p00_primal_strong_cochain_brick_2d_2_forman_trapezoidal_0p001_1000_potential.txt\
  | build/$(MODE)/demo/pdf/diffusion
	$<\
  --raw $(word 2, $^)\
  1000\
  --raw $(word 3, $^)\
  $@

build/$(MODE)/demo/pdf/diffusion/transient_continuous_2d_d00_p00_primal_strong_cochain_brick_2d_2_forman_trapezoidal_0p001_1000_flow.pdf:\
  build/$(MODE)/bin/pdf_mesh_2d_colored_one_cochain_sequence$(.EXE)\
  build/$(MODE)/demo/mesh/brick_2d_2_forman.txt\
  build/$(MODE)/demo/diffusion/transient_continuous_2d_d00_p00_primal_strong_cochain_brick_2d_2_forman_trapezoidal_0p001_1000_flow.txt\
  | build/$(MODE)/demo/pdf/diffusion
	$<\
  --raw $(word 2, $^)\
  1000\
  --raw $(word 3, $^)\
  $@

build/$(MODE)/demo/pdf/diffusion/transient_continuous_2d_d00_p00_primal_weak_cochain_brick_2d_2_forman_trapezoidal_0p001_1000_potential.pdf:\
  build/$(MODE)/bin/pdf_mesh_2d_colored_zero_cochain_sequence$(.EXE)\
  build/$(MODE)/demo/mesh/brick_2d_2_forman.txt\
  build/$(MODE)/demo/diffusion/transient_continuous_2d_d00_p00_primal_weak_cochain_brick_2d_2_forman_trapezoidal_0p001_1000_potential.txt\
  | build/$(MODE)/demo/pdf/diffusion
	$<\
  --raw $(word 2, $^)\
  1000\
  --raw $(word 3, $^)\
  $@

build/$(MODE)/demo/pdf/diffusion/transient_continuous_2d_d00_p00_primal_weak_cochain_brick_2d_2_forman_trapezoidal_0p001_1000_flow.pdf:\
  build/$(MODE)/bin/pdf_mesh_2d_colored_one_cochain_sequence$(.EXE)\
  build/$(MODE)/demo/mesh/brick_2d_2_forman.txt\
  build/$(MODE)/demo/diffusion/transient_continuous_2d_d00_p00_primal_weak_cochain_brick_2d_2_forman_trapezoidal_0p001_1000_flow.txt\
  | build/$(MODE)/demo/pdf/diffusion
	$<\
  --raw $(word 2, $^)\
  1000\
  --raw $(word 3, $^)\
  $@
