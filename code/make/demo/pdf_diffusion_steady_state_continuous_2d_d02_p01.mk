_demo_pdf_diffusion_steady_state_continuous_2d_d02_p01 :=\
  build/$(MODE)/demo/pdf/diffusion/steady_state_continuous_2d_d02_p01_exact_2d_10_grains_forman_potential.pdf\
  build/$(MODE)/demo/pdf/diffusion/steady_state_continuous_2d_d02_p01_exact_2d_10_grains_forman_flow.pdf\
  build/$(MODE)/demo/pdf/diffusion/steady_state_continuous_2d_d02_p01_primal_strong_cochain_2d_10_grains_forman_potential.pdf\
  build/$(MODE)/demo/pdf/diffusion/steady_state_continuous_2d_d02_p01_primal_strong_cochain_2d_10_grains_forman_flow.pdf\
  build/$(MODE)/demo/pdf/diffusion/steady_state_continuous_2d_d02_p01_primal_weak_cochain_2d_10_grains_forman_potential.pdf\
  build/$(MODE)/demo/pdf/diffusion/steady_state_continuous_2d_d02_p01_primal_weak_cochain_2d_10_grains_forman_flow.pdf\
  build/$(MODE)/demo/pdf/diffusion/steady_state_continuous_2d_d02_p01_mixed_weak_cochain_2d_10_grains_forman_potential.pdf\
  build/$(MODE)/demo/pdf/diffusion/steady_state_continuous_2d_d02_p01_mixed_weak_cochain_2d_10_grains_forman_flow.pdf\

build/$(MODE)/demo/pdf/diffusion/steady_state_continuous_2d_d02_p01_exact_2d_10_grains_forman_potential.pdf:\
  build/$(MODE)/bin/idec_graphics_mesh_2d_0_cochain_sequence$(.EXE)\
  build/$(MODE)/demo/mesh/2d_10_grains_forman.txt\
  build/$(MODE)/demo/diffusion/steady_state_continuous_2d_d02_p01_exact_2d_10_grains_forman_potential.txt\
  build/$(MODE)/obj/src/idec_cairo_graphics_draw_functions_mesh_2d_0_cochain_sequence$(.OBJ)\
  build/$(MODE)/obj/src/idec_cairo_pdf_animation$(.OBJ)\
  | build/$(MODE)/demo/pdf/diffusion\
    build/$(MODE)/lib/libcanvas$(.DLL)\
    build/$(MODE)/lib/libanimation$(.DLL)
	$<\
  --mesh=$(word 2, $^)\
  --number-of-time-steps=0\
  --cochain-sequence=$(word 3, $^)\
  --canvas-library=$(word 2, $|)\
  --canvas-backend=idec_cairo_graphics_draw_functions_mesh_2d_0_cochain_sequence\
  --animation-library=$(word 3, $|)\
  --animation-backend=idec_cairo_pdf_animation\
  --output=$@

build/$(MODE)/demo/pdf/diffusion/steady_state_continuous_2d_d02_p01_exact_2d_10_grains_forman_flow.pdf:\
  build/$(MODE)/bin/idec_graphics_mesh_2d_1_cochain_sequence$(.EXE)\
  build/$(MODE)/demo/mesh/2d_10_grains_forman.txt\
  build/$(MODE)/demo/diffusion/steady_state_continuous_2d_d02_p01_exact_2d_10_grains_forman_flow.txt\
  build/$(MODE)/obj/src/idec_cairo_graphics_draw_functions_mesh_2d_1_cochain_sequence$(.OBJ)\
  build/$(MODE)/obj/src/idec_cairo_pdf_animation$(.OBJ)\
  | build/$(MODE)/demo/pdf/diffusion\
    build/$(MODE)/lib/libcanvas$(.DLL)\
    build/$(MODE)/lib/libanimation$(.DLL)
	$<\
  --mesh=$(word 2, $^)\
  --number-of-time-steps=0\
  --cochain-sequence=$(word 3, $^)\
  --canvas-library=$(word 2, $|)\
  --canvas-backend=idec_cairo_graphics_draw_functions_mesh_2d_1_cochain_sequence\
  --animation-library=$(word 3, $|)\
  --animation-backend=idec_cairo_pdf_animation\
  --output=$@

build/$(MODE)/demo/pdf/diffusion/steady_state_continuous_2d_d02_p01_primal_strong_cochain_2d_10_grains_forman_potential.pdf:\
  build/$(MODE)/bin/idec_graphics_mesh_2d_0_cochain_sequence$(.EXE)\
  build/$(MODE)/demo/mesh/2d_10_grains_forman.txt\
  build/$(MODE)/demo/diffusion/steady_state_continuous_2d_d02_p01_primal_strong_cochain_2d_10_grains_forman_potential.txt\
  build/$(MODE)/obj/src/idec_cairo_graphics_draw_functions_mesh_2d_0_cochain_sequence$(.OBJ)\
  build/$(MODE)/obj/src/idec_cairo_pdf_animation$(.OBJ)\
  | build/$(MODE)/demo/pdf/diffusion\
    build/$(MODE)/lib/libcanvas$(.DLL)\
    build/$(MODE)/lib/libanimation$(.DLL)
	$<\
  --mesh=$(word 2, $^)\
  --number-of-time-steps=0\
  --cochain-sequence=$(word 3, $^)\
  --canvas-library=$(word 2, $|)\
  --canvas-backend=idec_cairo_graphics_draw_functions_mesh_2d_0_cochain_sequence\
  --animation-library=$(word 3, $|)\
  --animation-backend=idec_cairo_pdf_animation\
  --output=$@

build/$(MODE)/demo/pdf/diffusion/steady_state_continuous_2d_d02_p01_primal_strong_cochain_2d_10_grains_forman_flow.pdf:\
  build/$(MODE)/bin/idec_graphics_mesh_2d_1_cochain_sequence$(.EXE)\
  build/$(MODE)/demo/mesh/2d_10_grains_forman.txt\
  build/$(MODE)/demo/diffusion/steady_state_continuous_2d_d02_p01_primal_strong_cochain_2d_10_grains_forman_flow.txt\
  build/$(MODE)/obj/src/idec_cairo_graphics_draw_functions_mesh_2d_1_cochain_sequence$(.OBJ)\
  build/$(MODE)/obj/src/idec_cairo_pdf_animation$(.OBJ)\
  | build/$(MODE)/demo/pdf/diffusion\
    build/$(MODE)/lib/libcanvas$(.DLL)\
    build/$(MODE)/lib/libanimation$(.DLL)
	$<\
  --mesh=$(word 2, $^)\
  --number-of-time-steps=0\
  --cochain-sequence=$(word 3, $^)\
  --canvas-library=$(word 2, $|)\
  --canvas-backend=idec_cairo_graphics_draw_functions_mesh_2d_1_cochain_sequence\
  --animation-library=$(word 3, $|)\
  --animation-backend=idec_cairo_pdf_animation\
  --output=$@

build/$(MODE)/demo/pdf/diffusion/steady_state_continuous_2d_d02_p01_primal_weak_cochain_2d_10_grains_forman_potential.pdf:\
  build/$(MODE)/bin/idec_graphics_mesh_2d_0_cochain_sequence$(.EXE)\
  build/$(MODE)/demo/mesh/2d_10_grains_forman.txt\
  build/$(MODE)/demo/diffusion/steady_state_continuous_2d_d02_p01_primal_weak_cochain_2d_10_grains_forman_potential.txt\
  build/$(MODE)/obj/src/idec_cairo_graphics_draw_functions_mesh_2d_0_cochain_sequence$(.OBJ)\
  build/$(MODE)/obj/src/idec_cairo_pdf_animation$(.OBJ)\
  | build/$(MODE)/demo/pdf/diffusion\
    build/$(MODE)/lib/libcanvas$(.DLL)\
    build/$(MODE)/lib/libanimation$(.DLL)
	$<\
  --mesh=$(word 2, $^)\
  --number-of-time-steps=0\
  --cochain-sequence=$(word 3, $^)\
  --canvas-library=$(word 2, $|)\
  --canvas-backend=idec_cairo_graphics_draw_functions_mesh_2d_0_cochain_sequence\
  --animation-library=$(word 3, $|)\
  --animation-backend=idec_cairo_pdf_animation\
  --output=$@

build/$(MODE)/demo/pdf/diffusion/steady_state_continuous_2d_d02_p01_primal_weak_cochain_2d_10_grains_forman_flow.pdf:\
  build/$(MODE)/bin/idec_graphics_mesh_2d_1_cochain_sequence$(.EXE)\
  build/$(MODE)/demo/mesh/2d_10_grains_forman.txt\
  build/$(MODE)/demo/diffusion/steady_state_continuous_2d_d02_p01_primal_weak_cochain_2d_10_grains_forman_flow.txt\
  build/$(MODE)/obj/src/idec_cairo_graphics_draw_functions_mesh_2d_1_cochain_sequence$(.OBJ)\
  build/$(MODE)/obj/src/idec_cairo_pdf_animation$(.OBJ)\
  | build/$(MODE)/demo/pdf/diffusion\
    build/$(MODE)/lib/libcanvas$(.DLL)\
    build/$(MODE)/lib/libanimation$(.DLL)
	$<\
  --mesh=$(word 2, $^)\
  --number-of-time-steps=0\
  --cochain-sequence=$(word 3, $^)\
  --canvas-library=$(word 2, $|)\
  --canvas-backend=idec_cairo_graphics_draw_functions_mesh_2d_1_cochain_sequence\
  --animation-library=$(word 3, $|)\
  --animation-backend=idec_cairo_pdf_animation\
  --output=$@

build/$(MODE)/demo/pdf/diffusion/steady_state_continuous_2d_d02_p01_mixed_weak_cochain_2d_10_grains_forman_potential.pdf:\
  build/$(MODE)/bin/idec_graphics_mesh_2d_0_cochain_sequence$(.EXE)\
  build/$(MODE)/demo/mesh/2d_10_grains_forman.txt\
  build/$(MODE)/demo/diffusion/steady_state_continuous_2d_d02_p01_mixed_weak_cochain_2d_10_grains_forman_potential.txt\
  build/$(MODE)/obj/src/idec_cairo_graphics_draw_functions_mesh_2d_0_cochain_sequence$(.OBJ)\
  build/$(MODE)/obj/src/idec_cairo_pdf_animation$(.OBJ)\
  | build/$(MODE)/demo/pdf/diffusion\
    build/$(MODE)/lib/libcanvas$(.DLL)\
    build/$(MODE)/lib/libanimation$(.DLL)
	$<\
  --mesh=$(word 2, $^)\
  --number-of-time-steps=0\
  --cochain-sequence=$(word 3, $^)\
  --canvas-library=$(word 2, $|)\
  --canvas-backend=idec_cairo_graphics_draw_functions_mesh_2d_0_cochain_sequence\
  --animation-library=$(word 3, $|)\
  --animation-backend=idec_cairo_pdf_animation\
  --output=$@

build/$(MODE)/demo/pdf/diffusion/steady_state_continuous_2d_d02_p01_mixed_weak_cochain_2d_10_grains_forman_flow.pdf:\
  build/$(MODE)/bin/idec_graphics_mesh_2d_1_cochain_sequence$(.EXE)\
  build/$(MODE)/demo/mesh/2d_10_grains_forman.txt\
  build/$(MODE)/demo/diffusion/steady_state_continuous_2d_d02_p01_mixed_weak_cochain_2d_10_grains_forman_solution.txt\
  build/$(MODE)/obj/src/idec_cairo_graphics_draw_functions_mesh_2d_1_cochain_sequence$(.OBJ)\
  build/$(MODE)/obj/src/idec_cairo_pdf_animation$(.OBJ)\
  | build/$(MODE)/demo/pdf/diffusion\
    build/$(MODE)/lib/libcanvas$(.DLL)\
    build/$(MODE)/lib/libanimation$(.DLL)
	$<\
  --mesh=$(word 2, $^)\
  --number-of-time-steps=0\
  --cochain-sequence-format=--steady-state-mixed-weak-solution-flow-raw\
  --cochain-sequence=$(word 3, $^)\
  --canvas-library=$(word 2, $|)\
  --canvas-backend=idec_cairo_graphics_draw_functions_mesh_2d_1_cochain_sequence\
  --animation-library=$(word 3, $|)\
  --animation-backend=idec_cairo_pdf_animation\
  --output=$@
