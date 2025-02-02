_pdf_diffusion_steady_state_continuous_2d_d03_p01 :=\
  build/$(MODE)/pdf/diffusion/steady_state_continuous_2d_d03_p01_exact_circular_4_3_forman_potential.pdf\
  build/$(MODE)/pdf/diffusion/steady_state_continuous_2d_d03_p01_exact_circular_4_3_forman_flow.pdf\
  build/$(MODE)/pdf/diffusion/steady_state_continuous_2d_d03_p01_primal_weak_cochain_circular_4_3_forman_potential.pdf\
  build/$(MODE)/pdf/diffusion/steady_state_continuous_2d_d03_p01_primal_weak_cochain_circular_4_3_forman_flow.pdf\
  build/$(MODE)/pdf/diffusion/steady_state_continuous_2d_d03_p01_mixed_weak_cochain_circular_4_3_forman_potential.pdf\
  build/$(MODE)/pdf/diffusion/steady_state_continuous_2d_d03_p01_mixed_weak_cochain_circular_4_3_forman_flow.pdf\
  build/$(MODE)/pdf/diffusion/steady_state_continuous_2d_d03_p01_exact_circular_18_10_forman_potential.pdf\
  build/$(MODE)/pdf/diffusion/steady_state_continuous_2d_d03_p01_exact_circular_18_10_forman_flow.pdf\
  build/$(MODE)/pdf/diffusion/steady_state_continuous_2d_d03_p01_primal_weak_cochain_circular_18_10_forman_potential.pdf\
  build/$(MODE)/pdf/diffusion/steady_state_continuous_2d_d03_p01_primal_weak_cochain_circular_18_10_forman_flow.pdf\
  build/$(MODE)/pdf/diffusion/steady_state_continuous_2d_d03_p01_mixed_weak_cochain_circular_18_10_forman_potential.pdf\
  build/$(MODE)/pdf/diffusion/steady_state_continuous_2d_d03_p01_mixed_weak_cochain_circular_18_10_forman_flow.pdf\

build/$(MODE)/pdf/diffusion/steady_state_continuous_2d_d03_p01_exact_circular_4_3_forman_potential.pdf:\
  build/$(MODE)/bin/idec_graphics_mesh_2d_0_cochain_sequence$(.EXE)\
  build/$(MODE)/txt/mesh/circular_4_3_forman.txt\
  build/$(MODE)/txt/diffusion/steady_state_continuous_2d_d03_p01_exact_circular_4_3_forman_potential.txt\
  build/$(MODE)/obj/plugins/idec_cairo_graphics_draw_functions_mesh_2d_0_cochain_sequence$(.OBJ)\
  build/$(MODE)/obj/plugins/idec_cairo_pdf_animation$(.OBJ)\
  | build/$(MODE)/pdf/diffusion\
    build/$(MODE)/lib/plugins/libcanvas$(.DLL)\
    build/$(MODE)/lib/plugins/libanimation$(.DLL)
	$<\
  --mesh=$(word 2, $^)\
  --number-of-time-steps=0\
  --cochain-sequence=$(word 3, $^)\
  --canvas-library=$(word 2, $|)\
  --canvas-backend=idec_cairo_graphics_draw_functions_mesh_2d_0_cochain_sequence\
  --animation-library=$(word 3, $|)\
  --animation-backend=idec_cairo_pdf_animation\
  --output=$@

build/$(MODE)/pdf/diffusion/steady_state_continuous_2d_d03_p01_exact_circular_4_3_forman_flow.pdf:\
  build/$(MODE)/bin/idec_graphics_mesh_2d_1_cochain_sequence$(.EXE)\
  build/$(MODE)/txt/mesh/circular_4_3_forman.txt\
  build/$(MODE)/txt/diffusion/steady_state_continuous_2d_d03_p01_exact_circular_4_3_forman_flow.txt\
  build/$(MODE)/obj/plugins/idec_cairo_graphics_draw_functions_mesh_2d_1_cochain_sequence$(.OBJ)\
  build/$(MODE)/obj/plugins/idec_cairo_pdf_animation$(.OBJ)\
  | build/$(MODE)/pdf/diffusion\
    build/$(MODE)/lib/plugins/libcanvas$(.DLL)\
    build/$(MODE)/lib/plugins/libanimation$(.DLL)
	$<\
  --mesh=$(word 2, $^)\
  --number-of-time-steps=0\
  --cochain-sequence=$(word 3, $^)\
  --canvas-library=$(word 2, $|)\
  --canvas-backend=idec_cairo_graphics_draw_functions_mesh_2d_1_cochain_sequence\
  --animation-library=$(word 3, $|)\
  --animation-backend=idec_cairo_pdf_animation\
  --output=$@

build/$(MODE)/pdf/diffusion/steady_state_continuous_2d_d03_p01_primal_weak_cochain_circular_4_3_forman_potential.pdf:\
  build/$(MODE)/bin/idec_graphics_mesh_2d_0_cochain_sequence$(.EXE)\
  build/$(MODE)/txt/mesh/circular_4_3_forman.txt\
  build/$(MODE)/txt/diffusion/steady_state_continuous_2d_d03_p01_primal_weak_cochain_circular_4_3_forman_potential.txt\
  build/$(MODE)/obj/plugins/idec_cairo_graphics_draw_functions_mesh_2d_0_cochain_sequence$(.OBJ)\
  build/$(MODE)/obj/plugins/idec_cairo_pdf_animation$(.OBJ)\
  | build/$(MODE)/pdf/diffusion\
    build/$(MODE)/lib/plugins/libcanvas$(.DLL)\
    build/$(MODE)/lib/plugins/libanimation$(.DLL)
	$<\
  --mesh=$(word 2, $^)\
  --number-of-time-steps=0\
  --cochain-sequence=$(word 3, $^)\
  --canvas-library=$(word 2, $|)\
  --canvas-backend=idec_cairo_graphics_draw_functions_mesh_2d_0_cochain_sequence\
  --animation-library=$(word 3, $|)\
  --animation-backend=idec_cairo_pdf_animation\
  --output=$@

build/$(MODE)/pdf/diffusion/steady_state_continuous_2d_d03_p01_primal_weak_cochain_circular_4_3_forman_flow.pdf:\
  build/$(MODE)/bin/idec_graphics_mesh_2d_1_cochain_sequence$(.EXE)\
  build/$(MODE)/txt/mesh/circular_4_3_forman.txt\
  build/$(MODE)/txt/diffusion/steady_state_continuous_2d_d03_p01_primal_weak_cochain_circular_4_3_forman_flow.txt\
  build/$(MODE)/obj/plugins/idec_cairo_graphics_draw_functions_mesh_2d_1_cochain_sequence$(.OBJ)\
  build/$(MODE)/obj/plugins/idec_cairo_pdf_animation$(.OBJ)\
  | build/$(MODE)/pdf/diffusion\
    build/$(MODE)/lib/plugins/libcanvas$(.DLL)\
    build/$(MODE)/lib/plugins/libanimation$(.DLL)
	$<\
  --mesh=$(word 2, $^)\
  --number-of-time-steps=0\
  --cochain-sequence=$(word 3, $^)\
  --canvas-library=$(word 2, $|)\
  --canvas-backend=idec_cairo_graphics_draw_functions_mesh_2d_1_cochain_sequence\
  --animation-library=$(word 3, $|)\
  --animation-backend=idec_cairo_pdf_animation\
  --output=$@

build/$(MODE)/pdf/diffusion/steady_state_continuous_2d_d03_p01_mixed_weak_cochain_circular_4_3_forman_potential.pdf:\
  build/$(MODE)/bin/idec_graphics_mesh_2d_0_cochain_sequence$(.EXE)\
  build/$(MODE)/txt/mesh/circular_4_3_forman.txt\
  build/$(MODE)/txt/diffusion/steady_state_continuous_2d_d03_p01_mixed_weak_cochain_circular_4_3_forman_potential.txt\
  build/$(MODE)/obj/plugins/idec_cairo_graphics_draw_functions_mesh_2d_0_cochain_sequence$(.OBJ)\
  build/$(MODE)/obj/plugins/idec_cairo_pdf_animation$(.OBJ)\
  | build/$(MODE)/pdf/diffusion\
    build/$(MODE)/lib/plugins/libcanvas$(.DLL)\
    build/$(MODE)/lib/plugins/libanimation$(.DLL)
	$<\
  --mesh=$(word 2, $^)\
  --number-of-time-steps=0\
  --cochain-sequence=$(word 3, $^)\
  --canvas-library=$(word 2, $|)\
  --canvas-backend=idec_cairo_graphics_draw_functions_mesh_2d_0_cochain_sequence\
  --animation-library=$(word 3, $|)\
  --animation-backend=idec_cairo_pdf_animation\
  --output=$@

build/$(MODE)/pdf/diffusion/steady_state_continuous_2d_d03_p01_mixed_weak_cochain_circular_4_3_forman_flow.pdf:\
  build/$(MODE)/bin/idec_graphics_mesh_2d_1_cochain_sequence$(.EXE)\
  build/$(MODE)/txt/mesh/circular_4_3_forman.txt\
  build/$(MODE)/txt/diffusion/steady_state_continuous_2d_d03_p01_mixed_weak_cochain_circular_4_3_forman_solution.txt\
  build/$(MODE)/obj/plugins/idec_cairo_graphics_draw_functions_mesh_2d_1_cochain_sequence$(.OBJ)\
  build/$(MODE)/obj/plugins/idec_cairo_pdf_animation$(.OBJ)\
  | build/$(MODE)/pdf/diffusion\
    build/$(MODE)/lib/plugins/libcanvas$(.DLL)\
    build/$(MODE)/lib/plugins/libanimation$(.DLL)
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

build/$(MODE)/pdf/diffusion/steady_state_continuous_2d_d03_p01_exact_circular_18_10_forman_potential.pdf:\
  build/$(MODE)/bin/idec_graphics_mesh_2d_0_cochain_sequence$(.EXE)\
  build/$(MODE)/txt/mesh/circular_18_10_forman.txt\
  build/$(MODE)/txt/diffusion/steady_state_continuous_2d_d03_p01_exact_circular_18_10_forman_potential.txt\
  build/$(MODE)/obj/plugins/idec_cairo_graphics_draw_functions_mesh_2d_0_cochain_sequence$(.OBJ)\
  build/$(MODE)/obj/plugins/idec_cairo_pdf_animation$(.OBJ)\
  | build/$(MODE)/pdf/diffusion\
    build/$(MODE)/lib/plugins/libcanvas$(.DLL)\
    build/$(MODE)/lib/plugins/libanimation$(.DLL)
	$<\
  --mesh=$(word 2, $^)\
  --number-of-time-steps=0\
  --cochain-sequence=$(word 3, $^)\
  --canvas-library=$(word 2, $|)\
  --canvas-backend=idec_cairo_graphics_draw_functions_mesh_2d_0_cochain_sequence\
  --animation-library=$(word 3, $|)\
  --animation-backend=idec_cairo_pdf_animation\
  --output=$@

build/$(MODE)/pdf/diffusion/steady_state_continuous_2d_d03_p01_exact_circular_18_10_forman_flow.pdf:\
  build/$(MODE)/bin/idec_graphics_mesh_2d_1_cochain_sequence$(.EXE)\
  build/$(MODE)/txt/mesh/circular_18_10_forman.txt\
  build/$(MODE)/txt/diffusion/steady_state_continuous_2d_d03_p01_exact_circular_18_10_forman_flow.txt\
  build/$(MODE)/obj/plugins/idec_cairo_graphics_draw_functions_mesh_2d_1_cochain_sequence$(.OBJ)\
  build/$(MODE)/obj/plugins/idec_cairo_pdf_animation$(.OBJ)\
  | build/$(MODE)/pdf/diffusion\
    build/$(MODE)/lib/plugins/libcanvas$(.DLL)\
    build/$(MODE)/lib/plugins/libanimation$(.DLL)
	$<\
  --mesh=$(word 2, $^)\
  --number-of-time-steps=0\
  --cochain-sequence=$(word 3, $^)\
  --canvas-library=$(word 2, $|)\
  --canvas-backend=idec_cairo_graphics_draw_functions_mesh_2d_1_cochain_sequence\
  --animation-library=$(word 3, $|)\
  --animation-backend=idec_cairo_pdf_animation\
  --output=$@

build/$(MODE)/pdf/diffusion/steady_state_continuous_2d_d03_p01_primal_weak_cochain_circular_18_10_forman_potential.pdf:\
  build/$(MODE)/bin/idec_graphics_mesh_2d_0_cochain_sequence$(.EXE)\
  build/$(MODE)/txt/mesh/circular_18_10_forman.txt\
  build/$(MODE)/txt/diffusion/steady_state_continuous_2d_d03_p01_primal_weak_cochain_circular_18_10_forman_potential.txt\
  build/$(MODE)/obj/plugins/idec_cairo_graphics_draw_functions_mesh_2d_0_cochain_sequence$(.OBJ)\
  build/$(MODE)/obj/plugins/idec_cairo_pdf_animation$(.OBJ)\
  | build/$(MODE)/pdf/diffusion\
    build/$(MODE)/lib/plugins/libcanvas$(.DLL)\
    build/$(MODE)/lib/plugins/libanimation$(.DLL)
	$<\
  --mesh=$(word 2, $^)\
  --number-of-time-steps=0\
  --cochain-sequence=$(word 3, $^)\
  --canvas-library=$(word 2, $|)\
  --canvas-backend=idec_cairo_graphics_draw_functions_mesh_2d_0_cochain_sequence\
  --animation-library=$(word 3, $|)\
  --animation-backend=idec_cairo_pdf_animation\
  --output=$@

build/$(MODE)/pdf/diffusion/steady_state_continuous_2d_d03_p01_primal_weak_cochain_circular_18_10_forman_flow.pdf:\
  build/$(MODE)/bin/idec_graphics_mesh_2d_1_cochain_sequence$(.EXE)\
  build/$(MODE)/txt/mesh/circular_18_10_forman.txt\
  build/$(MODE)/txt/diffusion/steady_state_continuous_2d_d03_p01_primal_weak_cochain_circular_18_10_forman_flow.txt\
  build/$(MODE)/obj/plugins/idec_cairo_graphics_draw_functions_mesh_2d_1_cochain_sequence$(.OBJ)\
  build/$(MODE)/obj/plugins/idec_cairo_pdf_animation$(.OBJ)\
  | build/$(MODE)/pdf/diffusion\
    build/$(MODE)/lib/plugins/libcanvas$(.DLL)\
    build/$(MODE)/lib/plugins/libanimation$(.DLL)
	$<\
  --mesh=$(word 2, $^)\
  --number-of-time-steps=0\
  --cochain-sequence=$(word 3, $^)\
  --canvas-library=$(word 2, $|)\
  --canvas-backend=idec_cairo_graphics_draw_functions_mesh_2d_1_cochain_sequence\
  --animation-library=$(word 3, $|)\
  --animation-backend=idec_cairo_pdf_animation\
  --output=$@

build/$(MODE)/pdf/diffusion/steady_state_continuous_2d_d03_p01_mixed_weak_cochain_circular_18_10_forman_potential.pdf:\
  build/$(MODE)/bin/idec_graphics_mesh_2d_0_cochain_sequence$(.EXE)\
  build/$(MODE)/txt/mesh/circular_18_10_forman.txt\
  build/$(MODE)/txt/diffusion/steady_state_continuous_2d_d03_p01_mixed_weak_cochain_circular_18_10_forman_potential.txt\
  build/$(MODE)/obj/plugins/idec_cairo_graphics_draw_functions_mesh_2d_0_cochain_sequence$(.OBJ)\
  build/$(MODE)/obj/plugins/idec_cairo_pdf_animation$(.OBJ)\
  | build/$(MODE)/pdf/diffusion\
    build/$(MODE)/lib/plugins/libcanvas$(.DLL)\
    build/$(MODE)/lib/plugins/libanimation$(.DLL)
	$<\
  --mesh=$(word 2, $^)\
  --number-of-time-steps=0\
  --cochain-sequence=$(word 3, $^)\
  --canvas-library=$(word 2, $|)\
  --canvas-backend=idec_cairo_graphics_draw_functions_mesh_2d_0_cochain_sequence\
  --animation-library=$(word 3, $|)\
  --animation-backend=idec_cairo_pdf_animation\
  --output=$@

build/$(MODE)/pdf/diffusion/steady_state_continuous_2d_d03_p01_mixed_weak_cochain_circular_18_10_forman_flow.pdf:\
  build/$(MODE)/bin/idec_graphics_mesh_2d_1_cochain_sequence$(.EXE)\
  build/$(MODE)/txt/mesh/circular_18_10_forman.txt\
  build/$(MODE)/txt/diffusion/steady_state_continuous_2d_d03_p01_mixed_weak_cochain_circular_18_10_forman_solution.txt\
  build/$(MODE)/obj/plugins/idec_cairo_graphics_draw_functions_mesh_2d_1_cochain_sequence$(.OBJ)\
  build/$(MODE)/obj/plugins/idec_cairo_pdf_animation$(.OBJ)\
  | build/$(MODE)/pdf/diffusion\
    build/$(MODE)/lib/plugins/libcanvas$(.DLL)\
    build/$(MODE)/lib/plugins/libanimation$(.DLL)
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
