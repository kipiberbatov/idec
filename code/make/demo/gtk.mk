TIMELAPSE = 100
CLOSE_AUTOMATICALLY = 0

# _demo_gtk_diffusion :=\
#   build/$(MODE)/demo/gtk/diffusion/transient_continuous_2d_d00_p00_primal_strong_cochain_brick_2d_2_forman_potential.log\
#   build/$(MODE)/demo/gtk/diffusion/transient_continuous_2d_d00_p01_primal_strong_cochain_brick_2d_2_forman_potential.log\
#   build/$(MODE)/demo/gtk/diffusion/transient_continuous_2d_d00_p00_primal_strong_cochain_brick_2d_5_forman_potential.log\
#   build/$(MODE)/demo/gtk/diffusion/transient_continuous_2d_d00_p01_primal_strong_cochain_brick_2d_5_forman_potential.log\
#   build/$(MODE)/demo/gtk/diffusion/transient_continuous_2d_d00_p01_primal_strong_cochain_brick_2d_10_forman_potential.log\
#   build/$(MODE)/demo/gtk/diffusion/transient_continuous_2d_d00_p01_primal_strong_cochain_brick_2d_10_forman_dual_flow.log\
#   build/$(MODE)/demo/gtk/diffusion/transient_continuous_2d_d02_p00_primal_strong_cochain_2d_10_grains_forman_potential.log\
#   build/$(MODE)/demo/gtk/diffusion/transient_continuous_2d_d02_p00_primal_strong_cochain_2d_10_grains_forman_dual_flow.log\
#   build/$(MODE)/demo/gtk/diffusion/transient_continuous_2d_d02_p00_primal_weak_cochain_2d_10_grains_forman_potential.log\
#   build/$(MODE)/demo/gtk/diffusion/transient_continuous_2d_d02_p00_primal_weak_cochain_2d_10_grains_forman_dual_flow.log\
#   build/$(MODE)/demo/gtk/diffusion/transient_continuous_2d_d02_p00_primal_weak_to_steady_state_cochain_2d_10_grains_forman_potential.log\
#   build/$(MODE)/demo/gtk/diffusion/transient_continuous_2d_d02_p01_primal_weak_cochain_2d_10_grains_forman_potential.log\
#   build/$(MODE)/demo/gtk/diffusion/transient_continuous_2d_d01_p00_primal_strong_cochain_square_8_potential.log\
#   build/$(MODE)/demo/gtk/diffusion/transient_continuous_2d_d00_p01_primal_weak_cochain_brick_2d_2_forman_potential.log

include code/make/demo/gtk_diffusion_transient_continuous_2d_d00_p00.mk
include code/make/demo/gtk_diffusion_transient_continuous_2d_d00_p01.mk
include code/make/demo/gtk_diffusion_transient_continuous_2d_d00_p04.mk

_demo_gtk :=\
  build/$(MODE)/demo/gtk/filled_window_default.log\
  $(_demo_gtk_diffusion_transient_continuous_2d_d00_p00)\
  $(_demo_gtk_diffusion_transient_continuous_2d_d00_p01)\
  $(_demo_gtk_diffusion_transient_continuous_2d_d00_p04)\
#   $(_demo_gtk_diffusion)

.PHONY: demo_gtk
demo_gtk: bin $(_demo_gtk)\
  | build/$(MODE)/demo/gtk

build/$(MODE)/demo/gtk: | build/$(MODE)/demo
	mkdir -p $@

build/$(MODE)/demo/gtk/filled_window_default.log:\
  build/$(MODE)/bin/idec_filled_window$(.EXE)\
  build/$(MODE)/obj/src/idec_cairo_canvas_functions_filled_window$(.OBJ)\
  build/$(MODE)/obj/src/idec_cairo_gtk_animation$(.OBJ)\
  | build/$(MODE)/demo/gtk\
    build/$(MODE)/lib/libcanvas$(.DLL)\
    build/$(MODE)/lib/libanimation$(.DLL)
	$<\
  --canvas-library=$(word 2, $|)\
  --canvas-backend=idec_cairo_canvas_functions_filled_window\
  --animation-library=$(word 3, $|)\
  --animation-backend=idec_cairo_gtk_animation\
  --title=filled_window\
  --close-automatically=$(CLOSE_AUTOMATICALLY)\
  --timelapse=$(TIMELAPSE)\
  --output=$@

build/$(MODE)/demo/gtk/diffusion: | build/$(MODE)/demo/gtk
	mkdir -p $@

# build/$(MODE)/demo/gtk/diffusion/transient_continuous_2d_d00_p00_primal_strong_cochain_brick_2d_2_forman_potential.log:\
#   build/$(MODE)/bin/gtk_mesh_2d_colored_zero_cochain_sequence$(.EXE)\
#   build/$(MODE)/demo/mesh/brick_2d_2_forman.txt\
#   build/$(MODE)/demo/diffusion/transient_continuous_2d_d00_p00_primal_strong_cochain_brick_2d_2_forman_potential.txt\
#   | build/$(MODE)/demo/gtk/diffusion
# 	$< --raw $(word 2, $^) 100 --raw $(word 3, $^) > $@


# build/$(MODE)/demo/gtk/diffusion/transient_continuous_2d_d00_p00_primal_strong_cochain_brick_2d_5_forman_potential.log:\
#   build/$(MODE)/bin/gtk_mesh_2d_colored_zero_cochain_sequence$(.EXE)\
#   build/$(MODE)/demo/mesh/brick_2d_5_forman.txt\
#   build/$(MODE)/demo/diffusion/transient_continuous_2d_d00_p00_primal_strong_cochain_brick_2d_5_forman_potential.txt\
#   | build/$(MODE)/demo/gtk/diffusion
# 	$< --raw $(word 2, $^) 1000 --raw $(word 3, $^) > $@

# build/$(MODE)/demo/gtk/diffusion/transient_continuous_2d_d00_p01_primal_strong_cochain_brick_2d_5_forman_potential.log:\
#   build/$(MODE)/bin/gtk_mesh_2d_colored_zero_cochain_sequence$(.EXE)\
#   build/$(MODE)/demo/mesh/brick_2d_5_forman.txt\
#   build/$(MODE)/demo/diffusion/transient_continuous_2d_d00_p01_primal_strong_cochain_brick_2d_5_forman_potential.txt\
#   | build/$(MODE)/demo/gtk/diffusion
# 	$< --raw $(word 2, $^) 10000 --raw $(word 3, $^) > $@

# build/$(MODE)/demo/gtk/diffusion/transient_continuous_2d_d00_p01_primal_strong_cochain_brick_2d_2_forman_potential.log:\
#   build/$(MODE)/bin/gtk_diffusion$(.EXE)\
#   build/$(MODE)/demo/mesh/brick_2d_2_forman.txt\
#   build/$(MODE)/demo/diffusion/transient_continuous_2d_d00_p01_primal_strong_cochain_brick_2d_2_forman_potential.txt\
#   | build/$(MODE)/demo/gtk/diffusion
# 	$< --raw $(word 2, $^) $(word 3, $^) > $@

# build/$(MODE)/demo/gtk/diffusion/transient_continuous_2d_d00_p01_primal_strong_cochain_brick_2d_10_forman_potential.log:\
#   build/$(MODE)/bin/gtk_mesh_2d_colored_zero_cochain_sequence$(.EXE)\
#   build/$(MODE)/demo/mesh/brick_2d_10_forman.txt\
#   build/$(MODE)/demo/diffusion/transient_continuous_2d_d00_p01_primal_strong_cochain_brick_2d_10_forman_potential.txt\
#   | build/$(MODE)/demo/gtk/diffusion
# 	$< --raw $(word 2, $^) 4000 --raw $(word 3, $^) > $@

# build/$(MODE)/demo/gtk/diffusion/transient_continuous_2d_d00_p01_primal_strong_cochain_brick_2d_10_forman_dual_flow.log:\
#   build/$(MODE)/bin/gtk_mesh_2d_colored_one_cochain_sequence$(.EXE)\
#   build/$(MODE)/demo/mesh/brick_2d_10_forman.txt\
#   build/$(MODE)/demo/diffusion/transient_continuous_2d_d00_p01_primal_strong_cochain_brick_2d_10_forman_dual_flow.txt\
#   | build/$(MODE)/demo/gtk/diffusion
# 	$< --raw $(word 2, $^) 4000 --raw $(word 3, $^) > $@

# build/$(MODE)/demo/gtk/diffusion/transient_continuous_2d_d02_p00_primal_strong_cochain_2d_10_grains_forman_potential.log:\
#   build/$(MODE)/bin/gtk_mesh_2d_colored_zero_cochain_sequence$(.EXE)\
#   build/$(MODE)/demo/mesh/2d_10_grains_forman.txt\
#   build/$(MODE)/demo/diffusion/transient_continuous_2d_d02_p00_primal_strong_cochain_2d_10_grains_forman_potential.txt\
#   | build/$(MODE)/demo/gtk/diffusion
# 	$< --raw $(word 2, $^) 1000 --raw $(word 3, $^) > $@

# build/$(MODE)/demo/gtk/diffusion/transient_continuous_2d_d02_p00_primal_strong_cochain_2d_10_grains_forman_dual_flow.log:\
#   build/$(MODE)/bin/gtk_mesh_2d_colored_one_cochain_sequence$(.EXE)\
#   build/$(MODE)/demo/mesh/2d_10_grains_forman.txt\
#   build/$(MODE)/demo/diffusion/transient_continuous_2d_d02_p00_primal_strong_cochain_2d_10_grains_forman_dual_flow.txt\
#   | build/$(MODE)/demo/gtk/diffusion
# 	$< --raw $(word 2, $^) 1000 --raw $(word 3, $^) > $@

# build/$(MODE)/demo/gtk/diffusion/transient_continuous_2d_d02_p00_primal_weak_cochain_2d_10_grains_forman_potential.log:\
#   build/$(MODE)/bin/gtk_mesh_2d_colored_zero_cochain_sequence$(.EXE)\
#   build/$(MODE)/demo/mesh/2d_10_grains_forman.txt\
#   build/$(MODE)/demo/diffusion/transient_continuous_2d_d02_p00_primal_weak_cochain_2d_10_grains_forman_potential.txt\
#   | build/$(MODE)/demo/gtk/diffusion
# 	$< --raw $(word 2, $^) 2000 --raw $(word 3, $^) > $@

# build/$(MODE)/demo/gtk/diffusion/transient_continuous_2d_d02_p00_primal_weak_cochain_2d_10_grains_forman_dual_flow.log:\
#   build/$(MODE)/bin/gtk_mesh_2d_colored_one_cochain_sequence$(.EXE)\
#   build/$(MODE)/demo/mesh/2d_10_grains_forman.txt\
#   build/$(MODE)/demo/diffusion/transient_continuous_2d_d02_p00_primal_weak_cochain_2d_10_grains_forman_dual_flow.txt\
#   | build/$(MODE)/demo/gtk/diffusion
# 	$< --raw $(word 2, $^) 2000 --raw $(word 3, $^) > $@

# build/$(MODE)/demo/gtk/diffusion/transient_continuous_2d_d02_p00_primal_weak_to_steady_state_cochain_2d_10_grains_forman_potential.log:\
#   build/$(MODE)/bin/gtk_diffusion$(.EXE)\
#   build/$(MODE)/demo/mesh/2d_10_grains_forman.txt\
#   build/$(MODE)/demo/diffusion/transient_continuous_2d_d02_p00_primal_weak_to_steady_state_cochain_2d_10_grains_forman_potential.txt\
#   | build/$(MODE)/demo/gtk/diffusion
# 	$< --raw $(word 2, $^) $(word 3, $^) > $@

# build/$(MODE)/demo/gtk/diffusion/transient_continuous_2d_d02_p01_primal_weak_cochain_2d_10_grains_forman_potential.log:\
#   build/$(MODE)/bin/gtk_mesh_2d_colored_zero_cochain_sequence$(.EXE)\
#   build/$(MODE)/demo/mesh/2d_10_grains_forman.txt\
#   build/$(MODE)/demo/diffusion/transient_continuous_2d_d02_p01_primal_weak_cochain_2d_10_grains_forman_potential.txt\
#   | build/$(MODE)/demo/gtk/diffusion
# 	$< --raw $(word 2, $^) 2000 --raw $(word 3, $^) > $@

# build/$(MODE)/demo/gtk/diffusion/transient_continuous_2d_d01_p00_primal_strong_cochain_square_8_potential.log:\
#   build/$(MODE)/bin/gtk_mesh_2d_colored_zero_cochain_sequence$(.EXE)\
#   build/$(MODE)/demo/mesh/square_8.txt\
#   build/$(MODE)/demo/diffusion/transient_continuous_2d_d01_p00_primal_strong_cochain_square_8_potential.txt\
#   | build/$(MODE)/demo/gtk/diffusion
# 	$< --raw $(word 2, $^) 4000 --raw $(word 3, $^) > $@

# build/$(MODE)/demo/gtk/diffusion/transient_continuous_2d_d00_p01_primal_weak_cochain_brick_2d_2_forman_potential.log:\
#   build/$(MODE)/bin/gtk_mesh_2d_colored_zero_cochain_sequence$(.EXE)\
#   build/$(MODE)/demo/mesh/brick_2d_2_forman.txt\
#   build/$(MODE)/demo/diffusion/transient_continuous_2d_d00_p01_primal_weak_cochain_brick_2d_2_forman_potential.txt\
#   | build/$(MODE)/demo/gtk/diffusion
# 	$< --raw $(word 2, $^) 1000 --raw $(word 3, $^) > $@

.PHONY: demo_gtk_clean
demo_gtk_clean:
	-$(RM) $(_demo_gtk)
	-$(RM) -r build/$(MODE)/demo/gtk
