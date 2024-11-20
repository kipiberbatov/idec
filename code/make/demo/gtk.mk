_demo_gtk_diffusion :=\
  build/$(MODE)/demo/gtk/diffusion/transient_continuous_2d_d00_p00_primal_strong_cochain_brick_2d_2_forman_temperature.log\
  build/$(MODE)/demo/gtk/diffusion/transient_continuous_2d_d00_p01_primal_strong_cochain_brick_2d_2_forman_temperature.log\
  build/$(MODE)/demo/gtk/diffusion/transient_continuous_2d_d00_p00_primal_strong_cochain_brick_2d_5_forman_temperature.log\
  build/$(MODE)/demo/gtk/diffusion/transient_continuous_2d_d00_p01_primal_strong_cochain_brick_2d_5_forman_temperature.log\
  build/$(MODE)/demo/gtk/diffusion/transient_continuous_2d_d00_p01_primal_strong_cochain_brick_2d_10_forman_temperature.log\
  build/$(MODE)/demo/gtk/diffusion/transient_continuous_2d_d00_p01_primal_strong_cochain_brick_2d_10_forman_flux.log\
  build/$(MODE)/demo/gtk/diffusion/transient_continuous_2d_d02_p00_primal_strong_cochain_2d_10_grains_forman_temperature.log\
  build/$(MODE)/demo/gtk/diffusion/transient_continuous_2d_d02_p00_primal_strong_cochain_2d_10_grains_forman_flux.log\
  build/$(MODE)/demo/gtk/diffusion/transient_continuous_2d_d02_p00_primal_weak_cochain_2d_10_grains_forman_temperature.log\
  build/$(MODE)/demo/gtk/diffusion/transient_continuous_2d_d02_p00_primal_weak_cochain_2d_10_grains_forman_flux.log\
  build/$(MODE)/demo/gtk/diffusion/transient_continuous_2d_d02_p00_primal_weak_to_steady_state_cochain_2d_10_grains_forman_temperature.log\
  build/$(MODE)/demo/gtk/diffusion/transient_continuous_2d_d02_p01_primal_weak_cochain_2d_10_grains_forman_temperature.log\
  build/$(MODE)/demo/gtk/diffusion/transient_continuous_2d_d01_p00_primal_strong_cochain_square_8_temperature.log\
  build/$(MODE)/demo/gtk/diffusion/transient_continuous_2d_d00_p01_primal_weak_cochain_brick_2d_2_forman_temperature.log

include code/make/demo/gtk_diffusion_transient_continuous_2d_d00_p00.mk
include code/make/demo/gtk_diffusion_transient_continuous_2d_d00_p01.mk

_demo_gtk :=\
  build/$(MODE)/demo/gtk/fill.log\
  $(_demo_gtk_diffusion_transient_continuous_2d_d00_p00)\
  $(_demo_gtk_diffusion_transient_continuous_2d_d00_p01)\
#   $(_demo_gtk_diffusion)

.PHONY: demo_gtk
demo_gtk: bin $(_demo_gtk)\
  | build/$(MODE)/demo/gtk

build/$(MODE)/demo/gtk: | build/$(MODE)/demo
	mkdir -p $@

build/$(MODE)/demo/gtk/fill.log:\
  build/$(MODE)/bin/gtk_fill | build/$(MODE)/demo/gtk
	$< 100 > $@

build/$(MODE)/demo/gtk/diffusion: | build/$(MODE)/demo/gtk
	mkdir -p $@

build/$(MODE)/demo/gtk/diffusion/transient_continuous_2d_d00_p00_primal_strong_cochain_brick_2d_2_forman_temperature.log:\
  build/$(MODE)/bin/gtk_mesh_2d_colored_zero_cochain_sequence$(.EXE)\
  build/$(MODE)/demo/mesh/brick_2d_2_forman.txt\
  build/$(MODE)/demo/diffusion/transient_continuous_2d_d00_p00_primal_strong_cochain_brick_2d_2_forman_temperature.txt\
  | build/$(MODE)/demo/gtk/diffusion
	$< --raw $(word 2, $^) 100 --raw $(word 3, $^) > $@


build/$(MODE)/demo/gtk/diffusion/transient_continuous_2d_d00_p00_primal_strong_cochain_brick_2d_5_forman_temperature.log:\
  build/$(MODE)/bin/gtk_mesh_2d_colored_zero_cochain_sequence$(.EXE)\
  build/$(MODE)/demo/mesh/brick_2d_5_forman.txt\
  build/$(MODE)/demo/diffusion/transient_continuous_2d_d00_p00_primal_strong_cochain_brick_2d_5_forman_temperature.txt\
  | build/$(MODE)/demo/gtk/diffusion
	$< --raw $(word 2, $^) 1000 --raw $(word 3, $^) > $@

build/$(MODE)/demo/gtk/diffusion/transient_continuous_2d_d00_p01_primal_strong_cochain_brick_2d_5_forman_temperature.log:\
  build/$(MODE)/bin/gtk_mesh_2d_colored_zero_cochain_sequence$(.EXE)\
  build/$(MODE)/demo/mesh/brick_2d_5_forman.txt\
  build/$(MODE)/demo/diffusion/transient_continuous_2d_d00_p01_primal_strong_cochain_brick_2d_5_forman_temperature.txt\
  | build/$(MODE)/demo/gtk/diffusion
	$< --raw $(word 2, $^) 10000 --raw $(word 3, $^) > $@

build/$(MODE)/demo/gtk/diffusion/transient_continuous_2d_d00_p01_primal_strong_cochain_brick_2d_2_forman_temperature.log:\
  build/$(MODE)/bin/gtk_diffusion$(.EXE)\
  build/$(MODE)/demo/mesh/brick_2d_2_forman.txt\
  build/$(MODE)/demo/diffusion/transient_continuous_2d_d00_p01_primal_strong_cochain_brick_2d_2_forman_temperature.txt\
  | build/$(MODE)/demo/gtk/diffusion
	$< --raw $(word 2, $^) $(word 3, $^) > $@

build/$(MODE)/demo/gtk/diffusion/transient_continuous_2d_d00_p01_primal_strong_cochain_brick_2d_10_forman_temperature.log:\
  build/$(MODE)/bin/gtk_mesh_2d_colored_zero_cochain_sequence$(.EXE)\
  build/$(MODE)/demo/mesh/brick_2d_10_forman.txt\
  build/$(MODE)/demo/diffusion/transient_continuous_2d_d00_p01_primal_strong_cochain_brick_2d_10_forman_temperature.txt\
  | build/$(MODE)/demo/gtk/diffusion
	$< --raw $(word 2, $^) 4000 --raw $(word 3, $^) > $@

build/$(MODE)/demo/gtk/diffusion/transient_continuous_2d_d00_p01_primal_strong_cochain_brick_2d_10_forman_flux.log:\
  build/$(MODE)/bin/gtk_mesh_2d_colored_one_cochain_sequence$(.EXE)\
  build/$(MODE)/demo/mesh/brick_2d_10_forman.txt\
  build/$(MODE)/demo/diffusion/transient_continuous_2d_d00_p01_primal_strong_cochain_brick_2d_10_forman_flux.txt\
  | build/$(MODE)/demo/gtk/diffusion
	$< --raw $(word 2, $^) 4000 --raw $(word 3, $^) > $@

build/$(MODE)/demo/gtk/diffusion/transient_continuous_2d_d02_p00_primal_strong_cochain_2d_10_grains_forman_temperature.log:\
  build/$(MODE)/bin/gtk_mesh_2d_colored_zero_cochain_sequence$(.EXE)\
  build/$(MODE)/demo/mesh/2d_10_grains_forman.txt\
  build/$(MODE)/demo/diffusion/transient_continuous_2d_d02_p00_primal_strong_cochain_2d_10_grains_forman_temperature.txt\
  | build/$(MODE)/demo/gtk/diffusion
	$< --raw $(word 2, $^) 1000 --raw $(word 3, $^) > $@

build/$(MODE)/demo/gtk/diffusion/transient_continuous_2d_d02_p00_primal_strong_cochain_2d_10_grains_forman_flux.log:\
  build/$(MODE)/bin/gtk_mesh_2d_colored_one_cochain_sequence$(.EXE)\
  build/$(MODE)/demo/mesh/2d_10_grains_forman.txt\
  build/$(MODE)/demo/diffusion/transient_continuous_2d_d02_p00_primal_strong_cochain_2d_10_grains_forman_flux.txt\
  | build/$(MODE)/demo/gtk/diffusion
	$< --raw $(word 2, $^) 1000 --raw $(word 3, $^) > $@

build/$(MODE)/demo/gtk/diffusion/transient_continuous_2d_d02_p00_primal_weak_cochain_2d_10_grains_forman_temperature.log:\
  build/$(MODE)/bin/gtk_mesh_2d_colored_zero_cochain_sequence$(.EXE)\
  build/$(MODE)/demo/mesh/2d_10_grains_forman.txt\
  build/$(MODE)/demo/diffusion/transient_continuous_2d_d02_p00_primal_weak_cochain_2d_10_grains_forman_temperature.txt\
  | build/$(MODE)/demo/gtk/diffusion
	$< --raw $(word 2, $^) 2000 --raw $(word 3, $^) > $@

build/$(MODE)/demo/gtk/diffusion/transient_continuous_2d_d02_p00_primal_weak_cochain_2d_10_grains_forman_flux.log:\
  build/$(MODE)/bin/gtk_mesh_2d_colored_one_cochain_sequence$(.EXE)\
  build/$(MODE)/demo/mesh/2d_10_grains_forman.txt\
  build/$(MODE)/demo/diffusion/transient_continuous_2d_d02_p00_primal_weak_cochain_2d_10_grains_forman_flux.txt\
  | build/$(MODE)/demo/gtk/diffusion
	$< --raw $(word 2, $^) 2000 --raw $(word 3, $^) > $@

build/$(MODE)/demo/gtk/diffusion/transient_continuous_2d_d02_p00_primal_weak_to_steady_state_cochain_2d_10_grains_forman_temperature.log:\
  build/$(MODE)/bin/gtk_diffusion$(.EXE)\
  build/$(MODE)/demo/mesh/2d_10_grains_forman.txt\
  build/$(MODE)/demo/diffusion/transient_continuous_2d_d02_p00_primal_weak_to_steady_state_cochain_2d_10_grains_forman_temperature.txt\
  | build/$(MODE)/demo/gtk/diffusion
	$< --raw $(word 2, $^) $(word 3, $^) > $@

build/$(MODE)/demo/gtk/diffusion/transient_continuous_2d_d02_p01_primal_weak_cochain_2d_10_grains_forman_temperature.log:\
  build/$(MODE)/bin/gtk_mesh_2d_colored_zero_cochain_sequence$(.EXE)\
  build/$(MODE)/demo/mesh/2d_10_grains_forman.txt\
  build/$(MODE)/demo/diffusion/transient_continuous_2d_d02_p01_primal_weak_cochain_2d_10_grains_forman_temperature.txt\
  | build/$(MODE)/demo/gtk/diffusion
	$< --raw $(word 2, $^) 2000 --raw $(word 3, $^) > $@

build/$(MODE)/demo/gtk/diffusion/transient_continuous_2d_d01_p00_primal_strong_cochain_square_8_temperature.log:\
  build/$(MODE)/bin/gtk_mesh_2d_colored_zero_cochain_sequence$(.EXE)\
  build/$(MODE)/demo/mesh/square_8.txt\
  build/$(MODE)/demo/diffusion/transient_continuous_2d_d01_p00_primal_strong_cochain_square_8_temperature.txt\
  | build/$(MODE)/demo/gtk/diffusion
	$< --raw $(word 2, $^) 4000 --raw $(word 3, $^) > $@

build/$(MODE)/demo/gtk/diffusion/transient_continuous_2d_d00_p01_primal_weak_cochain_brick_2d_2_forman_temperature.log:\
  build/$(MODE)/bin/gtk_mesh_2d_colored_zero_cochain_sequence$(.EXE)\
  build/$(MODE)/demo/mesh/brick_2d_2_forman.txt\
  build/$(MODE)/demo/diffusion/transient_continuous_2d_d00_p01_primal_weak_cochain_brick_2d_2_forman_temperature.txt\
  | build/$(MODE)/demo/gtk/diffusion
	$< --raw $(word 2, $^) 1000 --raw $(word 3, $^) > $@

.PHONY: demo_gtk_clean
demo_gtk_clean:
	-$(RM) $(_demo_gtk)
	-$(RM) -r build/$(MODE)/demo/gtk
