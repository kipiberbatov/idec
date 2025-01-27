_demo_pdf_diffusion_transient_continuous_2d_d00_p00 :=\
  build/$(MODE)/demo/pdf/diffusion/transient_continuous_2d_d00_p00_primal_strong_cochain_brick_2d_2_forman_trapezoidal_0p001_1000_potential.pdf\
  build/$(MODE)/demo/pdf/diffusion/transient_continuous_2d_d00_p00_primal_strong_cochain_brick_2d_2_forman_trapezoidal_0p001_1000_flow.pdf\
  build/$(MODE)/demo/pdf/diffusion/transient_continuous_2d_d00_p00_primal_weak_cochain_brick_2d_2_forman_trapezoidal_0p001_1000_potential.pdf\
  build/$(MODE)/demo/pdf/diffusion/transient_continuous_2d_d00_p00_primal_weak_cochain_brick_2d_2_forman_trapezoidal_0p001_1000_flow.pdf\

build/$(MODE)/demo/pdf/diffusion/transient_continuous_2d_d00_p00_primal_strong_cochain_brick_2d_2_forman_trapezoidal_0p001_1000_potential.pdf:\
  build/$(MODE)/bin/idec_graphics_mesh_2d_0_cochain_sequence$(.EXE)\
  build/$(MODE)/demo/mesh/brick_2d_2_forman.txt\
  build/$(MODE)/demo/diffusion/transient_continuous_2d_d00_p00_primal_strong_cochain_brick_2d_2_forman_trapezoidal_0p001_1000_potential.txt\
  build/$(MODE)/obj/src/idec_cairo_canvas_functions_graphics_mesh_2d_0_cochain_sequence$(.OBJ)\
  build/$(MODE)/obj/src/idec_cairo_pdf_animation$(.OBJ)\
  | build/$(MODE)/demo/pdf/diffusion\
    build/$(MODE)/lib/libcanvas$(.DLL)\
    build/$(MODE)/lib/libanimation$(.DLL)
	$<\
  --mesh=$(word 2, $^)\
  --number-of-time-steps=1000\
  --cochain-sequence=$(word 3, $^)\
  --canvas-library=$(word 2, $|)\
  --canvas-backend=idec_cairo_canvas_functions_graphics_mesh_2d_0_cochain_sequence\
  --animation-library=$(word 3, $|)\
  --animation-backend=idec_cairo_pdf_animation\
  --output=$@

build/$(MODE)/demo/pdf/diffusion/transient_continuous_2d_d00_p00_primal_strong_cochain_brick_2d_2_forman_trapezoidal_0p001_1000_flow.pdf:\
  build/$(MODE)/bin/idec_graphics_mesh_2d_1_cochain_sequence$(.EXE)\
  build/$(MODE)/demo/mesh/brick_2d_2_forman.txt\
  build/$(MODE)/demo/diffusion/transient_continuous_2d_d00_p00_primal_strong_cochain_brick_2d_2_forman_trapezoidal_0p001_1000_flow.txt\
  build/$(MODE)/obj/src/idec_cairo_canvas_functions_graphics_mesh_2d_1_cochain_sequence$(.OBJ)\
  build/$(MODE)/obj/src/idec_cairo_pdf_animation$(.OBJ)\
  | build/$(MODE)/demo/pdf/diffusion\
    build/$(MODE)/lib/libcanvas$(.DLL)\
    build/$(MODE)/lib/libanimation$(.DLL)
	$<\
  --mesh=$(word 2, $^)\
  --number-of-time-steps=1000\
  --cochain-sequence=$(word 3, $^)\
  --canvas-library=$(word 2, $|)\
  --canvas-backend=idec_cairo_canvas_functions_graphics_mesh_2d_1_cochain_sequence\
  --animation-library=$(word 3, $|)\
  --animation-backend=idec_cairo_pdf_animation\
  --output=$@

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
