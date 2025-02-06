_gtk_diffusion_transient_continuous_2d_d00_p00 :=\
  build/$(MODE)/gtk/diffusion/transient/continuous_2d_d00_p00_primal_strong_cochain_brick_2d_2_forman_trapezoidal_0p001_1000_potential.log\
  build/$(MODE)/gtk/diffusion/transient/continuous_2d_d00_p00_primal_strong_cochain_brick_2d_2_forman_trapezoidal_0p001_1000_flow.log\
  build/$(MODE)/gtk/diffusion/transient/continuous_2d_d00_p00_primal_weak_cochain_brick_2d_2_forman_trapezoidal_0p001_1000_potential.log\
  build/$(MODE)/gtk/diffusion/transient/continuous_2d_d00_p00_primal_weak_cochain_brick_2d_2_forman_trapezoidal_0p001_1000_flow.log\
  build/$(MODE)/gtk/diffusion/transient/continuous_2d_d00_p00_mixed_weak_cochain_brick_2d_2_forman_trapezoidal_0p001_1000_potential.log\
  build/$(MODE)/gtk/diffusion/transient/continuous_2d_d00_p00_mixed_weak_cochain_brick_2d_2_forman_trapezoidal_0p001_1000_flow.log\

build/$(MODE)/gtk/diffusion/transient/continuous_2d_d00_p00_primal_strong_cochain_brick_2d_2_forman_trapezoidal_0p001_1000_potential.log:\
  build/$(MODE)/bin/idec_graphics_mesh_2d_0_cochain_sequence$(.EXE)\
  build/$(MODE)/txt/mesh/brick_2d_2_forman.txt\
  build/$(MODE)/txt/diffusion/transient/continuous_2d_d00_p00_primal_strong_cochain_brick_2d_2_forman_trapezoidal_0p001_1000_potential.txt\
  build/$(MODE)/obj/plugins/idec_cairo_graphics_draw_functions_mesh_2d_0_cochain_sequence$(.OBJ)\
  build/$(MODE)/obj/plugins/idec_cairo_gtk_animation$(.OBJ)\
  | build/$(MODE)/gtk/diffusion/transient\
    build/$(MODE)/lib/plugins/libcanvas$(.DLL)\
    build/$(MODE)/lib/plugins/libanimation$(.DLL)
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

build/$(MODE)/gtk/diffusion/transient/continuous_2d_d00_p00_primal_strong_cochain_brick_2d_2_forman_trapezoidal_0p001_1000_flow.log:\
  build/$(MODE)/bin/idec_graphics_mesh_2d_1_cochain_sequence$(.EXE)\
  build/$(MODE)/txt/mesh/brick_2d_2_forman.txt\
  build/$(MODE)/txt/diffusion/transient/continuous_2d_d00_p00_primal_strong_cochain_brick_2d_2_forman_trapezoidal_0p001_1000_flow.txt\
  build/$(MODE)/obj/plugins/idec_cairo_graphics_draw_functions_mesh_2d_1_cochain_sequence$(.OBJ)\
  build/$(MODE)/obj/plugins/idec_cairo_gtk_animation$(.OBJ)\
  | build/$(MODE)/gtk/diffusion/transient\
    build/$(MODE)/lib/plugins/libcanvas$(.DLL)\
    build/$(MODE)/lib/plugins/libanimation$(.DLL)
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

build/$(MODE)/gtk/diffusion/transient/continuous_2d_d00_p00_primal_weak_cochain_brick_2d_2_forman_trapezoidal_0p001_1000_potential.log:\
  build/$(MODE)/bin/idec_graphics_mesh_2d_0_cochain_sequence$(.EXE)\
  build/$(MODE)/txt/mesh/brick_2d_2_forman.txt\
  build/$(MODE)/txt/diffusion/transient/continuous_2d_d00_p00_primal_weak_cochain_brick_2d_2_forman_trapezoidal_0p001_1000_potential.txt\
  build/$(MODE)/obj/plugins/idec_cairo_graphics_draw_functions_mesh_2d_0_cochain_sequence$(.OBJ)\
  build/$(MODE)/obj/plugins/idec_cairo_gtk_animation$(.OBJ)\
  | build/$(MODE)/gtk/diffusion/transient\
    build/$(MODE)/lib/plugins/libcanvas$(.DLL)\
    build/$(MODE)/lib/plugins/libanimation$(.DLL)
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

build/$(MODE)/gtk/diffusion/transient/continuous_2d_d00_p00_primal_weak_cochain_brick_2d_2_forman_trapezoidal_0p001_1000_flow.log:\
  build/$(MODE)/bin/idec_graphics_mesh_2d_1_cochain_sequence$(.EXE)\
  build/$(MODE)/txt/mesh/brick_2d_2_forman.txt\
  build/$(MODE)/txt/diffusion/transient/continuous_2d_d00_p00_primal_weak_cochain_brick_2d_2_forman_trapezoidal_0p001_1000_flow.txt\
  build/$(MODE)/obj/plugins/idec_cairo_graphics_draw_functions_mesh_2d_1_cochain_sequence$(.OBJ)\
  build/$(MODE)/obj/plugins/idec_cairo_gtk_animation$(.OBJ)\
  | build/$(MODE)/gtk/diffusion/transient\
    build/$(MODE)/lib/plugins/libcanvas$(.DLL)\
    build/$(MODE)/lib/plugins/libanimation$(.DLL)
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

build/$(MODE)/gtk/diffusion/transient/continuous_2d_d00_p00_mixed_weak_cochain_brick_2d_2_forman_trapezoidal_0p001_1000_potential.log:\
  build/$(MODE)/bin/idec_graphics_mesh_2d_0_cochain_sequence$(.EXE)\
  build/$(MODE)/txt/mesh/brick_2d_2_forman.txt\
  build/$(MODE)/txt/diffusion/transient/continuous_2d_d00_p00_mixed_weak_cochain_brick_2d_2_forman_trapezoidal_0p001_1000_potential.txt\
  build/$(MODE)/obj/plugins/idec_cairo_graphics_draw_functions_mesh_2d_0_cochain_sequence$(.OBJ)\
  build/$(MODE)/obj/plugins/idec_cairo_gtk_animation$(.OBJ)\
  | build/$(MODE)/gtk/diffusion/transient\
    build/$(MODE)/lib/plugins/libcanvas$(.DLL)\
    build/$(MODE)/lib/plugins/libanimation$(.DLL)
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

build/$(MODE)/gtk/diffusion/transient/continuous_2d_d00_p00_mixed_weak_cochain_brick_2d_2_forman_trapezoidal_0p001_1000_flow.log:\
  build/$(MODE)/bin/idec_graphics_mesh_2d_1_cochain_sequence$(.EXE)\
  build/$(MODE)/txt/mesh/brick_2d_2_forman.txt\
  build/$(MODE)/txt/diffusion/transient/continuous_2d_d00_p00_mixed_weak_cochain_brick_2d_2_forman_trapezoidal_0p001_1000_solution.txt\
  build/$(MODE)/obj/plugins/idec_cairo_graphics_draw_functions_mesh_2d_1_cochain_sequence$(.OBJ)\
  build/$(MODE)/obj/plugins/idec_cairo_gtk_animation$(.OBJ)\
  | build/$(MODE)/gtk/diffusion/transient\
    build/$(MODE)/lib/plugins/libcanvas$(.DLL)\
    build/$(MODE)/lib/plugins/libanimation$(.DLL)
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

.PHONY: gtk_diffusion_transient_continuous_2d_d00_p00
gtk_diffusion_transient_continuous_2d_d00_p00:\
  $(_gtk_diffusion_transient_continuous_2d_d00_p00)

.PHONY: gtk_diffusion_transient_continuous_2d_d00_p00_clean
gtk_diffusion_transient_continuous_2d_d00_p00_clean:
	-$(RM) $(_gtk_diffusion_transient_continuous_2d_d00_p00)
