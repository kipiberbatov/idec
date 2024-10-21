_demo_gtk_diffusion :=\
  build/$(MODE)/demo/gtk/diffusion/2d_transient_continuous_primal_strong_cochain_p2_brick_2d_2_forman_temperature.log\
  build/$(MODE)/demo/gtk/diffusion/2d_transient_continuous_primal_strong_cochain_p4_brick_2d_2_forman_temperature.log\
  build/$(MODE)/demo/gtk/diffusion/2d_transient_continuous_primal_strong_cochain_p2_brick_2d_5_forman_temperature.log\
  build/$(MODE)/demo/gtk/diffusion/2d_transient_continuous_primal_strong_cochain_p4_brick_2d_5_forman_temperature.log\
  build/$(MODE)/demo/gtk/diffusion/2d_transient_continuous_primal_strong_cochain_p4_brick_2d_10_forman_temperature.log\
  build/$(MODE)/demo/gtk/diffusion/2d_transient_continuous_primal_strong_cochain_p4_brick_2d_10_forman_flux.log\
  build/$(MODE)/demo/gtk/diffusion/2d_transient_continuous_primal_strong_cochain_p7_2d_10_grains_forman_temperature.log\
  build/$(MODE)/demo/gtk/diffusion/2d_transient_continuous_primal_strong_cochain_p7_2d_10_grains_forman_flux.log\
  build/$(MODE)/demo/gtk/diffusion/2d_transient_continuous_primal_weak_cochain_p7_2d_10_grains_forman_temperature.log\
  build/$(MODE)/demo/gtk/diffusion/2d_transient_continuous_primal_weak_cochain_p7_2d_10_grains_forman_flux.log\
  build/$(MODE)/demo/gtk/diffusion/2d_transient_to_steady_state_continuous_primal_weak_cochain_p7_2d_10_grains_forman_temperature.log\
  build/$(MODE)/demo/gtk/diffusion/2d_transient_continuous_primal_weak_cochain_p8_2d_10_grains_forman_temperature.log\
  build/$(MODE)/demo/gtk/diffusion/2d_transient_continuous_primal_strong_cochain_p5_square_8_temperature.log\
  build/$(MODE)/demo/gtk/diffusion/2d_transient_continuous_primal_weak_cochain_p4_brick_2d_2_forman_temperature.log

_demo_gtk := build/$(MODE)/demo/gtk/fill.log $(_demo_gtk_diffusion)

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

build/$(MODE)/demo/gtk/diffusion/2d_transient_continuous_primal_strong_cochain_p2_brick_2d_2_forman_temperature.log:\
  build/$(MODE)/bin/gtk_mesh_2d_colored_zero_cochain_sequence$(.EXE)\
  build/$(MODE)/demo/mesh/mesh_brick_2d_2_forman.txt\
  build/$(MODE)/demo/diffusion/2d_transient_continuous_primal_strong_cochain_p2_brick_2d_2_forman_temperature.txt\
  | build/$(MODE)/demo/gtk/diffusion
	$< --raw $(word 2, $^) 100 --raw $(word 3, $^) > $@


build/$(MODE)/demo/gtk/diffusion/2d_transient_continuous_primal_strong_cochain_p2_brick_2d_5_forman_temperature.log:\
  build/$(MODE)/bin/gtk_mesh_2d_colored_zero_cochain_sequence$(.EXE)\
  build/$(MODE)/demo/mesh/mesh_brick_2d_5_forman.txt\
  build/$(MODE)/demo/diffusion/2d_transient_continuous_primal_strong_cochain_p2_brick_2d_5_forman_temperature.txt\
  | build/$(MODE)/demo/gtk/diffusion
	$< --raw $(word 2, $^) 1000 --raw $(word 3, $^) > $@

build/$(MODE)/demo/gtk/diffusion/2d_transient_continuous_primal_strong_cochain_p4_brick_2d_5_forman_temperature.log:\
  build/$(MODE)/bin/gtk_mesh_2d_colored_zero_cochain_sequence$(.EXE)\
  build/$(MODE)/demo/mesh/mesh_brick_2d_5_forman.txt\
  build/$(MODE)/demo/diffusion/2d_transient_continuous_primal_strong_cochain_p4_brick_2d_5_forman_temperature.txt\
  | build/$(MODE)/demo/gtk/diffusion
	$< --raw $(word 2, $^) 10000 --raw $(word 3, $^) > $@

build/$(MODE)/demo/gtk/diffusion/2d_transient_continuous_primal_strong_cochain_p4_brick_2d_2_forman_temperature.log:\
  build/$(MODE)/bin/gtk_diffusion$(.EXE)\
  build/$(MODE)/demo/mesh/mesh_brick_2d_2_forman.txt\
  build/$(MODE)/demo/diffusion/2d_transient_continuous_primal_strong_cochain_p4_brick_2d_2_forman_temperature.txt\
  | build/$(MODE)/demo/gtk/diffusion
	$< --raw $(word 2, $^) $(word 3, $^) > $@

build/$(MODE)/demo/gtk/diffusion/2d_transient_continuous_primal_strong_cochain_p4_brick_2d_10_forman_temperature.log:\
  build/$(MODE)/bin/gtk_mesh_2d_colored_zero_cochain_sequence$(.EXE)\
  build/$(MODE)/demo/mesh/mesh_brick_2d_10_forman.txt\
  build/$(MODE)/demo/diffusion/2d_transient_continuous_primal_strong_cochain_p4_brick_2d_10_forman_temperature.txt\
  | build/$(MODE)/demo/gtk/diffusion
	$< --raw $(word 2, $^) 4000 --raw $(word 3, $^) > $@

build/$(MODE)/demo/gtk/diffusion/2d_transient_continuous_primal_strong_cochain_p4_brick_2d_10_forman_flux.log:\
  build/$(MODE)/bin/gtk_mesh_2d_colored_one_cochain_sequence$(.EXE)\
  build/$(MODE)/demo/mesh/mesh_brick_2d_10_forman.txt\
  build/$(MODE)/demo/diffusion/2d_transient_continuous_primal_strong_cochain_p4_brick_2d_10_forman_flux.txt\
  | build/$(MODE)/demo/gtk/diffusion
	$< --raw $(word 2, $^) 4000 --raw $(word 3, $^) > $@

build/$(MODE)/demo/gtk/diffusion/2d_transient_continuous_primal_strong_cochain_p7_2d_10_grains_forman_temperature.log:\
  build/$(MODE)/bin/gtk_mesh_2d_colored_zero_cochain_sequence$(.EXE)\
  build/$(MODE)/demo/mesh/mesh_2d_10_grains_forman.txt\
  build/$(MODE)/demo/diffusion/2d_transient_continuous_primal_strong_cochain_p7_2d_10_grains_forman_temperature.txt\
  | build/$(MODE)/demo/gtk/diffusion
	$< --raw $(word 2, $^) 1000 --raw $(word 3, $^) > $@

build/$(MODE)/demo/gtk/diffusion/2d_transient_continuous_primal_strong_cochain_p7_2d_10_grains_forman_flux.log:\
  build/$(MODE)/bin/gtk_mesh_2d_colored_one_cochain_sequence$(.EXE)\
  build/$(MODE)/demo/mesh/mesh_2d_10_grains_forman.txt\
  build/$(MODE)/demo/diffusion/2d_transient_continuous_primal_strong_cochain_p7_2d_10_grains_forman_flux.txt\
  | build/$(MODE)/demo/gtk/diffusion
	$< --raw $(word 2, $^) 1000 --raw $(word 3, $^) > $@

build/$(MODE)/demo/gtk/diffusion/2d_transient_continuous_primal_weak_cochain_p7_2d_10_grains_forman_temperature.log:\
  build/$(MODE)/bin/gtk_mesh_2d_colored_zero_cochain_sequence$(.EXE)\
  build/$(MODE)/demo/mesh/mesh_2d_10_grains_forman.txt\
  build/$(MODE)/demo/diffusion/2d_transient_continuous_primal_weak_cochain_p7_2d_10_grains_forman_temperature.txt\
  | build/$(MODE)/demo/gtk/diffusion
	$< --raw $(word 2, $^) 2000 --raw $(word 3, $^) > $@

build/$(MODE)/demo/gtk/diffusion/2d_transient_continuous_primal_weak_cochain_p7_2d_10_grains_forman_flux.log:\
  build/$(MODE)/bin/gtk_mesh_2d_colored_one_cochain_sequence$(.EXE)\
  build/$(MODE)/demo/mesh/mesh_2d_10_grains_forman.txt\
  build/$(MODE)/demo/diffusion/2d_transient_continuous_primal_weak_cochain_p7_2d_10_grains_forman_flux.txt\
  | build/$(MODE)/demo/gtk/diffusion
	$< --raw $(word 2, $^) 2000 --raw $(word 3, $^) > $@

build/$(MODE)/demo/gtk/diffusion/2d_transient_to_steady_state_continuous_primal_weak_cochain_p7_2d_10_grains_forman_temperature.log:\
  build/$(MODE)/bin/gtk_diffusion$(.EXE)\
  build/$(MODE)/demo/mesh/mesh_2d_10_grains_forman.txt\
  build/$(MODE)/demo/diffusion/2d_transient_to_steady_state_continuous_primal_weak_cochain_p7_2d_10_grains_forman_temperature.txt\
  | build/$(MODE)/demo/gtk/diffusion
	$< --raw $(word 2, $^) $(word 3, $^) > $@

build/$(MODE)/demo/gtk/diffusion/2d_transient_continuous_primal_weak_cochain_p8_2d_10_grains_forman_temperature.log:\
  build/$(MODE)/bin/gtk_mesh_2d_colored_zero_cochain_sequence$(.EXE)\
  build/$(MODE)/demo/mesh/mesh_2d_10_grains_forman.txt\
  build/$(MODE)/demo/diffusion/2d_transient_continuous_primal_weak_cochain_p8_2d_10_grains_forman_temperature.txt\
  | build/$(MODE)/demo/gtk/diffusion
	$< --raw $(word 2, $^) 2000 --raw $(word 3, $^) > $@

build/$(MODE)/demo/gtk/diffusion/2d_transient_continuous_primal_strong_cochain_p5_square_8_temperature.log:\
  build/$(MODE)/bin/gtk_mesh_2d_colored_zero_cochain_sequence$(.EXE)\
  build/$(MODE)/demo/mesh/mesh_square_8.txt\
  build/$(MODE)/demo/diffusion/2d_transient_continuous_primal_strong_cochain_p5_square_8_temperature.txt\
  | build/$(MODE)/demo/gtk/diffusion
	$< --raw $(word 2, $^) 4000 --raw $(word 3, $^) > $@

build/$(MODE)/demo/gtk/diffusion/2d_transient_continuous_primal_weak_cochain_p4_brick_2d_2_forman_temperature.log:\
  build/$(MODE)/bin/gtk_mesh_2d_colored_zero_cochain_sequence$(.EXE)\
  build/$(MODE)/demo/mesh/mesh_brick_2d_2_forman.txt\
  build/$(MODE)/demo/diffusion/2d_transient_continuous_primal_weak_cochain_p4_brick_2d_2_forman_temperature.txt\
  | build/$(MODE)/demo/gtk/diffusion
	$< --raw $(word 2, $^) 1000 --raw $(word 3, $^) > $@

.PHONY: demo_gtk_clean
demo_gtk_clean:
	-$(RM) $(_demo_gtk)
	-$(RM) -r build/$(MODE)/demo/gtk
