_demo_gtk_diffusion_transient_continuous_2d_d00_p00 :=\
  build/$(MODE)/demo/gtk/diffusion/transient_continuous_2d_d00_p00_primal_strong_cochain_brick_2d_2_forman_trapezoidal_0p001_1000_potential.log\
  build/$(MODE)/demo/gtk/diffusion/transient_continuous_2d_d00_p00_primal_strong_cochain_brick_2d_2_forman_trapezoidal_0p001_1000_flow.log\
  build/$(MODE)/demo/gtk/diffusion/transient_continuous_2d_d00_p00_primal_weak_cochain_brick_2d_2_forman_trapezoidal_0p001_1000_potential.log\
  build/$(MODE)/demo/gtk/diffusion/transient_continuous_2d_d00_p00_primal_weak_cochain_brick_2d_2_forman_trapezoidal_0p001_1000_flow.log\
  build/$(MODE)/demo/gtk/diffusion/transient_continuous_2d_d00_p00_mixed_weak_cochain_brick_2d_2_forman_trapezoidal_0p001_1000_potential.log\
  build/$(MODE)/demo/gtk/diffusion/transient_continuous_2d_d00_p00_mixed_weak_cochain_brick_2d_2_forman_trapezoidal_0p001_1000_flow.log\

build/$(MODE)/demo/gtk/diffusion/transient_continuous_2d_d00_p00_primal_strong_cochain_brick_2d_2_forman_trapezoidal_0p001_1000_potential.log:\
  build/$(MODE)/bin/idec_graphics_mesh_2d_0_cochain_sequence$(.EXE)\
  build/$(MODE)/demo/mesh/brick_2d_2_forman.txt\
  build/$(MODE)/demo/diffusion/transient_continuous_2d_d00_p00_primal_strong_cochain_brick_2d_2_forman_trapezoidal_0p001_1000_potential.txt\
  build/$(MODE)/obj/src/idec_cairo_graphics_draw_functions_mesh_2d_0_cochain_sequence$(.OBJ)\
  build/$(MODE)/obj/src/idec_cairo_gtk_animation$(.OBJ)\
  | build/$(MODE)/demo/gtk/diffusion\
    build/$(MODE)/lib/libcanvas$(.DLL)\
    build/$(MODE)/lib/libanimation$(.DLL)
	$<\
  --mesh=$(word 2, $^)\
  --number-of-time-steps=1000\
  --cochain-sequence=$(word 3, $^)\
  --canvas-library=$(word 2, $|)\
  --canvas-backend=idec_cairo_graphics_draw_functions_mesh_2d_0_cochain_sequence\
  --animation-library=$(word 3, $|)\
  --animation-backend=idec_cairo_gtk_animation\
  --title=2d_d00_p00_primal_strong_brick_2d_2_forman_potential\
  --close-automatically=$(CLOSE_AUTOMATICALLY)\
  --timelapse=$(TIMELAPSE)\
  --output=$@

build/$(MODE)/demo/gtk/diffusion/transient_continuous_2d_d00_p00_primal_strong_cochain_brick_2d_2_forman_trapezoidal_0p001_1000_flow.log:\
  build/$(MODE)/bin/idec_graphics_mesh_2d_1_cochain_sequence$(.EXE)\
  build/$(MODE)/demo/mesh/brick_2d_2_forman.txt\
  build/$(MODE)/demo/diffusion/transient_continuous_2d_d00_p00_primal_strong_cochain_brick_2d_2_forman_trapezoidal_0p001_1000_flow.txt\
  build/$(MODE)/obj/src/idec_cairo_graphics_draw_functions_mesh_2d_1_cochain_sequence$(.OBJ)\
  build/$(MODE)/obj/src/idec_cairo_gtk_animation$(.OBJ)\
  | build/$(MODE)/demo/gtk/diffusion\
    build/$(MODE)/lib/libcanvas$(.DLL)\
    build/$(MODE)/lib/libanimation$(.DLL)
	$<\
  --mesh=$(word 2, $^)\
  --number-of-time-steps=1000\
  --cochain-sequence=$(word 3, $^)\
  --canvas-library=$(word 2, $|)\
  --canvas-backend=idec_cairo_graphics_draw_functions_mesh_2d_1_cochain_sequence\
  --animation-library=$(word 3, $|)\
  --animation-backend=idec_cairo_gtk_animation\
  --title=2d_d00_p00_primal_strong_brick_2d_2_forman_flow\
  --close-automatically=$(CLOSE_AUTOMATICALLY)\
  --timelapse=$(TIMELAPSE)\
  --output=$@

build/$(MODE)/demo/gtk/diffusion/transient_continuous_2d_d00_p00_primal_weak_cochain_brick_2d_2_forman_trapezoidal_0p001_1000_potential.log:\
  build/$(MODE)/bin/idec_graphics_mesh_2d_0_cochain_sequence$(.EXE)\
  build/$(MODE)/demo/mesh/brick_2d_2_forman.txt\
  build/$(MODE)/demo/diffusion/transient_continuous_2d_d00_p00_primal_weak_cochain_brick_2d_2_forman_trapezoidal_0p001_1000_potential.txt\
  build/$(MODE)/obj/src/idec_cairo_graphics_draw_functions_mesh_2d_0_cochain_sequence$(.OBJ)\
  build/$(MODE)/obj/src/idec_cairo_gtk_animation$(.OBJ)\
  | build/$(MODE)/demo/gtk/diffusion\
    build/$(MODE)/lib/libcanvas$(.DLL)\
    build/$(MODE)/lib/libanimation$(.DLL)
	$<\
  --mesh=$(word 2, $^)\
  --number-of-time-steps=1000\
  --cochain-sequence=$(word 3, $^)\
  --canvas-library=$(word 2, $|)\
  --canvas-backend=idec_cairo_graphics_draw_functions_mesh_2d_0_cochain_sequence\
  --animation-library=$(word 3, $|)\
  --animation-backend=idec_cairo_gtk_animation\
  --title=2d_d00_p00_primal_weak_brick_2d_2_forman_potential\
  --close-automatically=$(CLOSE_AUTOMATICALLY)\
  --timelapse=$(TIMELAPSE)\
  --output=$@

build/$(MODE)/demo/gtk/diffusion/transient_continuous_2d_d00_p00_primal_weak_cochain_brick_2d_2_forman_trapezoidal_0p001_1000_flow.log:\
  build/$(MODE)/bin/idec_graphics_mesh_2d_1_cochain_sequence$(.EXE)\
  build/$(MODE)/demo/mesh/brick_2d_2_forman.txt\
  build/$(MODE)/demo/diffusion/transient_continuous_2d_d00_p00_primal_weak_cochain_brick_2d_2_forman_trapezoidal_0p001_1000_flow.txt\
  build/$(MODE)/obj/src/idec_cairo_graphics_draw_functions_mesh_2d_1_cochain_sequence$(.OBJ)\
  build/$(MODE)/obj/src/idec_cairo_gtk_animation$(.OBJ)\
  | build/$(MODE)/demo/gtk/diffusion\
    build/$(MODE)/lib/libcanvas$(.DLL)\
    build/$(MODE)/lib/libanimation$(.DLL)
	$<\
  --mesh=$(word 2, $^)\
  --number-of-time-steps=1000\
  --cochain-sequence=$(word 3, $^)\
  --canvas-library=$(word 2, $|)\
  --canvas-backend=idec_cairo_graphics_draw_functions_mesh_2d_1_cochain_sequence\
  --animation-library=$(word 3, $|)\
  --animation-backend=idec_cairo_gtk_animation\
  --title=2d_d00_p00_primal_weak_brick_2d_2_forman_flow\
  --close-automatically=$(CLOSE_AUTOMATICALLY)\
  --timelapse=$(TIMELAPSE)\
  --output=$@

build/$(MODE)/demo/gtk/diffusion/transient_continuous_2d_d00_p00_mixed_weak_cochain_brick_2d_2_forman_trapezoidal_0p001_1000_potential.log:\
  build/$(MODE)/bin/idec_graphics_mesh_2d_0_cochain_sequence$(.EXE)\
  build/$(MODE)/demo/mesh/brick_2d_2_forman.txt\
  build/$(MODE)/demo/diffusion/transient_continuous_2d_d00_p00_mixed_weak_cochain_brick_2d_2_forman_trapezoidal_0p001_1000_potential.txt\
  build/$(MODE)/obj/src/idec_cairo_graphics_draw_functions_mesh_2d_0_cochain_sequence$(.OBJ)\
  build/$(MODE)/obj/src/idec_cairo_gtk_animation$(.OBJ)\
  | build/$(MODE)/demo/gtk/diffusion\
    build/$(MODE)/lib/libcanvas$(.DLL)\
    build/$(MODE)/lib/libanimation$(.DLL)
	$<\
  --mesh=$(word 2, $^)\
  --number-of-time-steps=1000\
  --cochain-sequence=$(word 3, $^)\
  --canvas-library=$(word 2, $|)\
  --canvas-backend=idec_cairo_graphics_draw_functions_mesh_2d_0_cochain_sequence\
  --animation-library=$(word 3, $|)\
  --animation-backend=idec_cairo_gtk_animation\
  --title=2d_d00_p00_mixed_weak_brick_2d_2_forman_potential\
  --close-automatically=$(CLOSE_AUTOMATICALLY)\
  --timelapse=$(TIMELAPSE)\
  --output=$@

build/$(MODE)/demo/gtk/diffusion/transient_continuous_2d_d00_p00_mixed_weak_cochain_brick_2d_2_forman_trapezoidal_0p001_1000_flow.log:\
  build/$(MODE)/bin/idec_graphics_mesh_2d_1_cochain_sequence$(.EXE)\
  build/$(MODE)/demo/mesh/brick_2d_2_forman.txt\
  build/$(MODE)/demo/diffusion/transient_continuous_2d_d00_p00_mixed_weak_cochain_brick_2d_2_forman_trapezoidal_0p001_1000_solution.txt\
  build/$(MODE)/obj/src/idec_cairo_graphics_draw_functions_mesh_2d_1_cochain_sequence$(.OBJ)\
  build/$(MODE)/obj/src/idec_cairo_gtk_animation$(.OBJ)\
  | build/$(MODE)/demo/gtk/diffusion\
    build/$(MODE)/lib/libcanvas$(.DLL)\
    build/$(MODE)/lib/libanimation$(.DLL)
	$<\
  --mesh=$(word 2, $^)\
  --number-of-time-steps=1000\
  --cochain-sequence=$(word 3, $^)\
  --canvas-library=$(word 2, $|)\
  --canvas-backend=idec_cairo_graphics_draw_functions_mesh_2d_1_cochain_sequence\
  --animation-library=$(word 3, $|)\
  --animation-backend=idec_cairo_gtk_animation\
  --title=2d_d00_p00_mixed_weak_brick_2d_2_forman_flow\
  --close-automatically=$(CLOSE_AUTOMATICALLY)\
  --timelapse=$(TIMELAPSE)\
  --output=$@

.PHONY: demo_gtk_diffusion_transient_continuous_2d_d00_p00
demo_gtk_diffusion_transient_continuous_2d_d00_p00:\
  $(_demo_gtk_diffusion_transient_continuous_2d_d00_p00)

.PHONY: demo_gtk_diffusion_transient_continuous_2d_d00_p00_clean
demo_gtk_diffusion_transient_continuous_2d_d00_p00_clean:
	-$(RM) $(_demo_gtk_diffusion_transient_continuous_2d_d00_p00)
