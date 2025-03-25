.PHONY: pdf_diffusion_transient_continuous_2d_d03_p01\
        pdf_diffusion_transient_continuous_2d_d03_p01_clean\
        pdf_diffusion_transient_continuous_2d_d03_p01_distclean

build/$(MODE)/pdf/diffusion/transient/continuous_2d_d03_p01:\
  | build/$(MODE)/pdf/diffusion/transient
	mkdir -p $@

_pdf_diffusion_transient_continuous_2d_d03_p01 :=\
  build/$(MODE)/pdf/diffusion/transient/continuous_2d_d03_p01/primal_strong_cochain_circular_4_3_forman_trapezoidal_0p05_1000_potential.pdf\
  build/$(MODE)/pdf/diffusion/transient/continuous_2d_d03_p01/primal_strong_cochain_circular_4_3_forman_trapezoidal_0p05_1000_flow.pdf\
  build/$(MODE)/pdf/diffusion/transient/continuous_2d_d03_p01/primal_weak_cochain_circular_4_3_forman_trapezoidal_0p05_1000_potential.pdf\
  build/$(MODE)/pdf/diffusion/transient/continuous_2d_d03_p01/primal_weak_cochain_circular_4_3_forman_trapezoidal_0p05_1000_flow.pdf\
  build/$(MODE)/pdf/diffusion/transient/continuous_2d_d03_p01/mixed_weak_cochain_circular_4_3_forman_trapezoidal_0p05_1000_potential.pdf\
  build/$(MODE)/pdf/diffusion/transient/continuous_2d_d03_p01/mixed_weak_cochain_circular_4_3_forman_trapezoidal_0p05_1000_flow.pdf\

build/$(MODE)/pdf/diffusion/transient/continuous_2d_d03_p01/primal_strong_cochain_circular_4_3_forman_trapezoidal_0p05_1000_potential.pdf:\
  build/$(MODE)/bin/idec_graphics_mesh_2d_0_cochain_sequence$(.EXE)\
  build/$(MODE)/txt/mesh/circular_4_3_forman.txt\
  build/$(MODE)/txt/diffusion/transient/continuous_2d_d03_p01/primal_strong_cochain_circular_4_3_forman_trapezoidal_0p05_1000_potential.txt\
  build/$(MODE)/obj/plugins/idec_cairo_graphics_draw_functions_mesh_2d_0_cochain_sequence_circular_forman$(.OBJ)\
  build/$(MODE)/obj/plugins/idec_cairo_pdf_animation$(.OBJ)\
  | build/$(MODE)/pdf/diffusion/transient/continuous_2d_d03_p01\
    build/$(MODE)/lib/plugins/libcanvas$(.DLL)\
    build/$(MODE)/lib/plugins/libanimation$(.DLL)
	$<\
  --mesh=$(word 2, $^)\
  --number-of-time-steps=1000\
  --cochain-sequence=$(word 3, $^)\
  --canvas-library=$(word 2, $|)\
  --canvas-backend=idec_cairo_graphics_draw_functions_mesh_2d_0_cochain_sequence_circular_forman\
  --animation-library=$(word 3, $|)\
  --animation-backend=idec_cairo_pdf_animation\
  --output=$@

build/$(MODE)/pdf/diffusion/transient/continuous_2d_d03_p01/primal_strong_cochain_circular_4_3_forman_trapezoidal_0p05_1000_flow.pdf:\
  build/$(MODE)/bin/idec_graphics_mesh_2d_1_cochain_sequence$(.EXE)\
  build/$(MODE)/txt/mesh/circular_4_3_forman.txt\
  build/$(MODE)/txt/diffusion/transient/continuous_2d_d03_p01/primal_strong_cochain_circular_4_3_forman_trapezoidal_0p05_1000_flow.txt\
  build/$(MODE)/obj/plugins/idec_cairo_graphics_draw_functions_mesh_2d_1_cochain_sequence_circular_forman$(.OBJ)\
  build/$(MODE)/obj/plugins/idec_cairo_pdf_animation$(.OBJ)\
  | build/$(MODE)/pdf/diffusion/transient/continuous_2d_d03_p01\
    build/$(MODE)/lib/plugins/libcanvas$(.DLL)\
    build/$(MODE)/lib/plugins/libanimation$(.DLL)
	$<\
  --mesh=$(word 2, $^)\
  --number-of-time-steps=1000\
  --cochain-sequence=$(word 3, $^)\
  --canvas-library=$(word 2, $|)\
  --canvas-backend=idec_cairo_graphics_draw_functions_mesh_2d_1_cochain_sequence_circular_forman\
  --animation-library=$(word 3, $|)\
  --animation-backend=idec_cairo_pdf_animation\
  --output=$@

build/$(MODE)/pdf/diffusion/transient/continuous_2d_d03_p01/primal_weak_cochain_circular_4_3_forman_trapezoidal_0p05_1000_potential.pdf:\
  build/$(MODE)/bin/idec_graphics_mesh_2d_0_cochain_sequence$(.EXE)\
  build/$(MODE)/txt/mesh/circular_4_3_forman.txt\
  build/$(MODE)/txt/diffusion/transient/continuous_2d_d03_p01/primal_weak_cochain_circular_4_3_forman_trapezoidal_0p05_1000_potential.txt\
  build/$(MODE)/obj/plugins/idec_cairo_graphics_draw_functions_mesh_2d_0_cochain_sequence_circular_forman$(.OBJ)\
  build/$(MODE)/obj/plugins/idec_cairo_pdf_animation$(.OBJ)\
  | build/$(MODE)/pdf/diffusion/transient/continuous_2d_d03_p01\
    build/$(MODE)/lib/plugins/libcanvas$(.DLL)\
    build/$(MODE)/lib/plugins/libanimation$(.DLL)
	$<\
  --mesh=$(word 2, $^)\
  --number-of-time-steps=1000\
  --cochain-sequence=$(word 3, $^)\
  --canvas-library=$(word 2, $|)\
  --canvas-backend=idec_cairo_graphics_draw_functions_mesh_2d_0_cochain_sequence_circular_forman\
  --animation-library=$(word 3, $|)\
  --animation-backend=idec_cairo_pdf_animation\
  --output=$@

build/$(MODE)/pdf/diffusion/transient/continuous_2d_d03_p01/primal_weak_cochain_circular_4_3_forman_trapezoidal_0p05_1000_flow.pdf:\
  build/$(MODE)/bin/idec_graphics_mesh_2d_1_cochain_sequence$(.EXE)\
  build/$(MODE)/txt/mesh/circular_4_3_forman.txt\
  build/$(MODE)/txt/diffusion/transient/continuous_2d_d03_p01/primal_weak_cochain_circular_4_3_forman_trapezoidal_0p05_1000_flow.txt\
  build/$(MODE)/obj/plugins/idec_cairo_graphics_draw_functions_mesh_2d_1_cochain_sequence_circular_forman$(.OBJ)\
  build/$(MODE)/obj/plugins/idec_cairo_pdf_animation$(.OBJ)\
  | build/$(MODE)/pdf/diffusion/transient/continuous_2d_d03_p01\
    build/$(MODE)/lib/plugins/libcanvas$(.DLL)\
    build/$(MODE)/lib/plugins/libanimation$(.DLL)
	$<\
  --mesh=$(word 2, $^)\
  --number-of-time-steps=1000\
  --cochain-sequence=$(word 3, $^)\
  --canvas-library=$(word 2, $|)\
  --canvas-backend=idec_cairo_graphics_draw_functions_mesh_2d_1_cochain_sequence_circular_forman\
  --animation-library=$(word 3, $|)\
  --animation-backend=idec_cairo_pdf_animation\
  --output=$@

build/$(MODE)/pdf/diffusion/transient/continuous_2d_d03_p01/mixed_weak_cochain_circular_4_3_forman_trapezoidal_0p05_1000_potential.pdf:\
  build/$(MODE)/bin/idec_graphics_mesh_2d_0_cochain_sequence$(.EXE)\
  build/$(MODE)/txt/mesh/circular_4_3_forman.txt\
  build/$(MODE)/txt/diffusion/transient/continuous_2d_d03_p01/mixed_weak_cochain_circular_4_3_forman_trapezoidal_0p05_1000_potential.txt\
  build/$(MODE)/obj/plugins/idec_cairo_graphics_draw_functions_mesh_2d_0_cochain_sequence_circular_forman$(.OBJ)\
  build/$(MODE)/obj/plugins/idec_cairo_pdf_animation$(.OBJ)\
  | build/$(MODE)/pdf/diffusion/transient/continuous_2d_d03_p01\
    build/$(MODE)/lib/plugins/libcanvas$(.DLL)\
    build/$(MODE)/lib/plugins/libanimation$(.DLL)
	$<\
  --mesh=$(word 2, $^)\
  --number-of-time-steps=1000\
  --cochain-sequence=$(word 3, $^)\
  --canvas-library=$(word 2, $|)\
  --canvas-backend=idec_cairo_graphics_draw_functions_mesh_2d_0_cochain_sequence_circular_forman\
  --animation-library=$(word 3, $|)\
  --animation-backend=idec_cairo_pdf_animation\
  --output=$@

build/$(MODE)/pdf/diffusion/transient/continuous_2d_d03_p01/mixed_weak_cochain_circular_4_3_forman_trapezoidal_0p05_1000_flow.pdf:\
  build/$(MODE)/bin/idec_graphics_mesh_2d_1_cochain_sequence$(.EXE)\
  build/$(MODE)/txt/mesh/circular_4_3_forman.txt\
  build/$(MODE)/txt/diffusion/transient/continuous_2d_d03_p01/mixed_weak_cochain_circular_4_3_forman_trapezoidal_0p05_1000_solution.txt\
  build/$(MODE)/obj/plugins/idec_cairo_graphics_draw_functions_mesh_2d_1_cochain_sequence_circular_forman$(.OBJ)\
  build/$(MODE)/obj/plugins/idec_cairo_pdf_animation$(.OBJ)\
  | build/$(MODE)/pdf/diffusion/transient/continuous_2d_d03_p01\
    build/$(MODE)/lib/plugins/libcanvas$(.DLL)\
    build/$(MODE)/lib/plugins/libanimation$(.DLL)
	$<\
  --mesh=$(word 2, $^)\
  --number-of-time-steps=1000\
  --cochain-sequence=$(word 3, $^)\
  --canvas-library=$(word 2, $|)\
  --canvas-backend=idec_cairo_graphics_draw_functions_mesh_2d_1_cochain_sequence_circular_forman\
  --animation-library=$(word 3, $|)\
  --animation-backend=idec_cairo_pdf_animation\
  --output=$@

pdf_diffusion_transient_continuous_2d_d03_p01:\
  $(_pdf_diffusion_transient_continuous_2d_d03_p01)

pdf_diffusion_transient_continuous_2d_d03_p01_clean:
	-$(RM) $(_pdf_diffusion_transient_continuous_2d_d03_p01)

pdf_diffusion_transient_continuous_2d_d03_p01_distclean:
	-$(RM) -r build/$(MODE)/pdf/diffusion/transient/continuous_2d_d03_p01
