TIMELAPSE = 100
CLOSE_AUTOMATICALLY = 0

# _gtk_diffusion :=\
#   build/$(MODE)/gtk/diffusion/transient_continuous_2d_d00_p00_primal_strong_cochain_brick_2d_2_forman_potential.log\
#   build/$(MODE)/gtk/diffusion/transient_continuous_2d_d00_p01_primal_strong_cochain_brick_2d_2_forman_potential.log\
#   build/$(MODE)/gtk/diffusion/transient_continuous_2d_d00_p00_primal_strong_cochain_brick_2d_5_forman_potential.log\
#   build/$(MODE)/gtk/diffusion/transient_continuous_2d_d00_p01_primal_strong_cochain_brick_2d_5_forman_potential.log\
#   build/$(MODE)/gtk/diffusion/transient_continuous_2d_d00_p01_primal_strong_cochain_brick_2d_10_forman_potential.log\
#   build/$(MODE)/gtk/diffusion/transient_continuous_2d_d00_p01_primal_strong_cochain_brick_2d_10_forman_dual_flow.log\
#   build/$(MODE)/gtk/diffusion/transient_continuous_2d_d02_p00_primal_strong_cochain_2d_10_grains_forman_potential.log\
#   build/$(MODE)/gtk/diffusion/transient_continuous_2d_d02_p00_primal_strong_cochain_2d_10_grains_forman_dual_flow.log\
#   build/$(MODE)/gtk/diffusion/transient_continuous_2d_d02_p00_primal_weak_cochain_2d_10_grains_forman_potential.log\
#   build/$(MODE)/gtk/diffusion/transient_continuous_2d_d02_p00_primal_weak_cochain_2d_10_grains_forman_dual_flow.log\
#   build/$(MODE)/gtk/diffusion/transient_continuous_2d_d02_p00_primal_weak_to_steady_state_cochain_2d_10_grains_forman_potential.log\
#   build/$(MODE)/gtk/diffusion/transient_continuous_2d_d02_p01_primal_weak_cochain_2d_10_grains_forman_potential.log\
#   build/$(MODE)/gtk/diffusion/transient_continuous_2d_d01_p00_primal_strong_cochain_square_8_potential.log\
#   build/$(MODE)/gtk/diffusion/transient_continuous_2d_d00_p01_primal_weak_cochain_brick_2d_2_forman_potential.log

include code/make/gtk/diffusion_transient_continuous_2d_d00_p00.mk
include code/make/gtk/diffusion_transient_continuous_2d_d00_p01.mk
include code/make/gtk/diffusion_transient_continuous_2d_d00_p04.mk

_gtk :=\
  build/$(MODE)/gtk/filled_window_rainbow_100.log\
  $(_gtk_diffusion_transient_continuous_2d_d00_p00)\
  $(_gtk_diffusion_transient_continuous_2d_d00_p01)\
  $(_gtk_diffusion_transient_continuous_2d_d00_p04)\
#   $(_gtk_diffusion)

.PHONY: gtk
gtk: bin $(_gtk)\
  | build/$(MODE)/gtk

build/$(MODE)/gtk: | build/$(MODE)
	mkdir -p $@

build/$(MODE)/gtk/filled_window_rainbow_100.log:\
  build/$(MODE)/bin/idec_graphics_filled_window$(.EXE)\
  build/$(MODE)/obj/src/idec_cairo_graphics_draw_functions_filled_window$(.OBJ)\
  build/$(MODE)/obj/src/idec_cairo_gtk_animation$(.OBJ)\
  | build/$(MODE)/gtk\
    build/$(MODE)/lib/libcanvas$(.DLL)\
    build/$(MODE)/lib/libanimation$(.DLL)
	$<\
  --canvas-library=$(word 2, $|)\
  --canvas-backend=idec_cairo_graphics_draw_functions_filled_window\
  --animation-library=$(word 3, $|)\
  --animation-backend=idec_cairo_gtk_animation\
  --title=filled_window\
  --close-automatically=$(CLOSE_AUTOMATICALLY)\
  --timelapse=$(TIMELAPSE)\
  --output=$@

build/$(MODE)/gtk/diffusion: | build/$(MODE)/gtk
	mkdir -p $@

# build/$(MODE)/gtk/diffusion/transient_continuous_2d_d00_p00_primal_strong_cochain_brick_2d_2_forman_potential.log:\
#   build/$(MODE)/bin/gtk_mesh_2d_colored_zero_cochain_sequence$(.EXE)\
#   build/$(MODE)/txt/mesh/brick_2d_2_forman.txt\
#   build/$(MODE)/txt/diffusion/transient_continuous_2d_d00_p00_primal_strong_cochain_brick_2d_2_forman_potential.txt\
#   | build/$(MODE)/gtk/diffusion
# 	$< --raw $(word 2, $^) 100 --raw $(word 3, $^) > $@


# build/$(MODE)/gtk/diffusion/transient_continuous_2d_d00_p00_primal_strong_cochain_brick_2d_5_forman_potential.log:\
#   build/$(MODE)/bin/gtk_mesh_2d_colored_zero_cochain_sequence$(.EXE)\
#   build/$(MODE)/txt/mesh/brick_2d_5_forman.txt\
#   build/$(MODE)/txt/diffusion/transient_continuous_2d_d00_p00_primal_strong_cochain_brick_2d_5_forman_potential.txt\
#   | build/$(MODE)/gtk/diffusion
# 	$< --raw $(word 2, $^) 1000 --raw $(word 3, $^) > $@

# build/$(MODE)/gtk/diffusion/transient_continuous_2d_d00_p01_primal_strong_cochain_brick_2d_5_forman_potential.log:\
#   build/$(MODE)/bin/gtk_mesh_2d_colored_zero_cochain_sequence$(.EXE)\
#   build/$(MODE)/txt/mesh/brick_2d_5_forman.txt\
#   build/$(MODE)/txt/diffusion/transient_continuous_2d_d00_p01_primal_strong_cochain_brick_2d_5_forman_potential.txt\
#   | build/$(MODE)/gtk/diffusion
# 	$< --raw $(word 2, $^) 10000 --raw $(word 3, $^) > $@

# build/$(MODE)/gtk/diffusion/transient_continuous_2d_d00_p01_primal_strong_cochain_brick_2d_2_forman_potential.log:\
#   build/$(MODE)/bin/gtk_diffusion$(.EXE)\
#   build/$(MODE)/txt/mesh/brick_2d_2_forman.txt\
#   build/$(MODE)/txt/diffusion/transient_continuous_2d_d00_p01_primal_strong_cochain_brick_2d_2_forman_potential.txt\
#   | build/$(MODE)/gtk/diffusion
# 	$< --raw $(word 2, $^) $(word 3, $^) > $@

# build/$(MODE)/gtk/diffusion/transient_continuous_2d_d00_p01_primal_strong_cochain_brick_2d_10_forman_potential.log:\
#   build/$(MODE)/bin/gtk_mesh_2d_colored_zero_cochain_sequence$(.EXE)\
#   build/$(MODE)/txt/mesh/brick_2d_10_forman.txt\
#   build/$(MODE)/txt/diffusion/transient_continuous_2d_d00_p01_primal_strong_cochain_brick_2d_10_forman_potential.txt\
#   | build/$(MODE)/gtk/diffusion
# 	$< --raw $(word 2, $^) 4000 --raw $(word 3, $^) > $@

# build/$(MODE)/gtk/diffusion/transient_continuous_2d_d00_p01_primal_strong_cochain_brick_2d_10_forman_dual_flow.log:\
#   build/$(MODE)/bin/gtk_mesh_2d_colored_one_cochain_sequence$(.EXE)\
#   build/$(MODE)/txt/mesh/brick_2d_10_forman.txt\
#   build/$(MODE)/txt/diffusion/transient_continuous_2d_d00_p01_primal_strong_cochain_brick_2d_10_forman_dual_flow.txt\
#   | build/$(MODE)/gtk/diffusion
# 	$< --raw $(word 2, $^) 4000 --raw $(word 3, $^) > $@

# build/$(MODE)/gtk/diffusion/transient_continuous_2d_d02_p00_primal_strong_cochain_2d_10_grains_forman_potential.log:\
#   build/$(MODE)/bin/gtk_mesh_2d_colored_zero_cochain_sequence$(.EXE)\
#   build/$(MODE)/txt/mesh/2d_10_grains_forman.txt\
#   build/$(MODE)/txt/diffusion/transient_continuous_2d_d02_p00_primal_strong_cochain_2d_10_grains_forman_potential.txt\
#   | build/$(MODE)/gtk/diffusion
# 	$< --raw $(word 2, $^) 1000 --raw $(word 3, $^) > $@

# build/$(MODE)/gtk/diffusion/transient_continuous_2d_d02_p00_primal_strong_cochain_2d_10_grains_forman_dual_flow.log:\
#   build/$(MODE)/bin/gtk_mesh_2d_colored_one_cochain_sequence$(.EXE)\
#   build/$(MODE)/txt/mesh/2d_10_grains_forman.txt\
#   build/$(MODE)/txt/diffusion/transient_continuous_2d_d02_p00_primal_strong_cochain_2d_10_grains_forman_dual_flow.txt\
#   | build/$(MODE)/gtk/diffusion
# 	$< --raw $(word 2, $^) 1000 --raw $(word 3, $^) > $@

# build/$(MODE)/gtk/diffusion/transient_continuous_2d_d02_p00_primal_weak_cochain_2d_10_grains_forman_potential.log:\
#   build/$(MODE)/bin/gtk_mesh_2d_colored_zero_cochain_sequence$(.EXE)\
#   build/$(MODE)/txt/mesh/2d_10_grains_forman.txt\
#   build/$(MODE)/txt/diffusion/transient_continuous_2d_d02_p00_primal_weak_cochain_2d_10_grains_forman_potential.txt\
#   | build/$(MODE)/gtk/diffusion
# 	$< --raw $(word 2, $^) 2000 --raw $(word 3, $^) > $@

# build/$(MODE)/gtk/diffusion/transient_continuous_2d_d02_p00_primal_weak_cochain_2d_10_grains_forman_dual_flow.log:\
#   build/$(MODE)/bin/gtk_mesh_2d_colored_one_cochain_sequence$(.EXE)\
#   build/$(MODE)/txt/mesh/2d_10_grains_forman.txt\
#   build/$(MODE)/txt/diffusion/transient_continuous_2d_d02_p00_primal_weak_cochain_2d_10_grains_forman_dual_flow.txt\
#   | build/$(MODE)/gtk/diffusion
# 	$< --raw $(word 2, $^) 2000 --raw $(word 3, $^) > $@

# build/$(MODE)/gtk/diffusion/transient_continuous_2d_d02_p00_primal_weak_to_steady_state_cochain_2d_10_grains_forman_potential.log:\
#   build/$(MODE)/bin/gtk_diffusion$(.EXE)\
#   build/$(MODE)/txt/mesh/2d_10_grains_forman.txt\
#   build/$(MODE)/txt/diffusion/transient_continuous_2d_d02_p00_primal_weak_to_steady_state_cochain_2d_10_grains_forman_potential.txt\
#   | build/$(MODE)/gtk/diffusion
# 	$< --raw $(word 2, $^) $(word 3, $^) > $@

# build/$(MODE)/gtk/diffusion/transient_continuous_2d_d02_p01_primal_weak_cochain_2d_10_grains_forman_potential.log:\
#   build/$(MODE)/bin/gtk_mesh_2d_colored_zero_cochain_sequence$(.EXE)\
#   build/$(MODE)/txt/mesh/2d_10_grains_forman.txt\
#   build/$(MODE)/txt/diffusion/transient_continuous_2d_d02_p01_primal_weak_cochain_2d_10_grains_forman_potential.txt\
#   | build/$(MODE)/gtk/diffusion
# 	$< --raw $(word 2, $^) 2000 --raw $(word 3, $^) > $@

# build/$(MODE)/gtk/diffusion/transient_continuous_2d_d01_p00_primal_strong_cochain_square_8_potential.log:\
#   build/$(MODE)/bin/gtk_mesh_2d_colored_zero_cochain_sequence$(.EXE)\
#   build/$(MODE)/txt/mesh/square_8.txt\
#   build/$(MODE)/txt/diffusion/transient_continuous_2d_d01_p00_primal_strong_cochain_square_8_potential.txt\
#   | build/$(MODE)/gtk/diffusion
# 	$< --raw $(word 2, $^) 4000 --raw $(word 3, $^) > $@

# build/$(MODE)/gtk/diffusion/transient_continuous_2d_d00_p01_primal_weak_cochain_brick_2d_2_forman_potential.log:\
#   build/$(MODE)/bin/gtk_mesh_2d_colored_zero_cochain_sequence$(.EXE)\
#   build/$(MODE)/txt/mesh/brick_2d_2_forman.txt\
#   build/$(MODE)/txt/diffusion/transient_continuous_2d_d00_p01_primal_weak_cochain_brick_2d_2_forman_potential.txt\
#   | build/$(MODE)/gtk/diffusion
# 	$< --raw $(word 2, $^) 1000 --raw $(word 3, $^) > $@

.PHONY: gtk_clean
gtk_clean:
	-$(RM) $(_gtk)
	-$(RM) -r build/$(MODE)/gtk
