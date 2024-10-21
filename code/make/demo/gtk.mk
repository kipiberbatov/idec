_demo_gtk :=\
  build/$(MODE)/demo/gtk/fill.log\
  build/$(MODE)/demo/gtk/mesh_brick_2d_2_forman_diffusion_transient_continuous_p2_temperature.log\
  build/$(MODE)/demo/gtk/diffusion_2d_transient_continuous_p4_temperature_primal_strong_cochain_trapezoidal_brick_2d_2_forman.log\
  build/$(MODE)/demo/gtk/mesh_brick_2d_5_forman_diffusion_transient_continuous_p2_temperature.log\
  build/$(MODE)/demo/gtk/mesh_brick_2d_5_forman_diffusion_transient_continuous_p4_temperature.log\
  build/$(MODE)/demo/gtk/mesh_brick_2d_10_forman_diffusion_transient_continuous_p4_temperature.log\
  build/$(MODE)/demo/gtk/mesh_brick_2d_10_forman_diffusion_transient_continuous_p4_flux.log\
  build/$(MODE)/demo/gtk/mesh_2d_10_grains_forman_diffusion_transient_continuous_p7_temperature.log\
  build/$(MODE)/demo/gtk/mesh_2d_10_grains_forman_diffusion_transient_continuous_p7_flux.log\
  build/$(MODE)/demo/gtk/diffusion_2d_transient_continuous_p7_temperature_primal_weak_cochain_trapezoidal_neper_2d_10_grains_forman.log\
  build/$(MODE)/demo/gtk/diffusion_2d_transient_continuous_p8_temperature_primal_weak_cochain_trapezoidal_neper_2d_10_grains_forman.log\
  build/$(MODE)/demo/gtk/diffusion_2d_transient_continuous_p7_flux_primal_weak_cochain_trapezoidal_neper_2d_10_grains_forman.log\
  build/$(MODE)/demo/gtk/diffusion_2d_transient_continuous_p7_temperature_primal_weak_cochain_trapezoidal_to_steady_state_neper_2d_10_grains_forman.log\
  build/$(MODE)/demo/gtk/mesh_square_8_diffusion_transient_continuous_p5_temperature.log\
  build/$(MODE)/demo/gtk/diffusion-2d-transient-continuous-temperature-primal_weak-cochain-trapezoidal-p4-brick_2d_2_forman.log

.PHONY: demo_gtk
demo_gtk: bin $(_demo_gtk)\
  | build/$(MODE)/demo/gtk

build/$(MODE)/demo/gtk: | build/$(MODE)/demo
	mkdir -p $@

build/$(MODE)/demo/gtk/fill.log:\
  build/$(MODE)/bin/gtk_fill | build/$(MODE)/demo/gtk
	$< 100 > $@

build/$(MODE)/demo/gtk/mesh_brick_2d_2_forman_diffusion_transient_continuous_p2_temperature.log:\
  build/$(MODE)/bin/gtk_mesh_2d_colored_zero_cochain_sequence$(.EXE)\
  build/$(MODE)/demo/mesh/mesh_brick_2d_2_forman.txt\
  build/$(MODE)/demo/diffusion/mesh_brick_2d_2_forman_diffusion_transient_continuous_p2_temperature.txt\
  | build/$(MODE)/demo/gtk
	$< --raw $(word 2, $^) 100 --raw $(word 3, $^) > $@


build/$(MODE)/demo/gtk/mesh_brick_2d_5_forman_diffusion_transient_continuous_p2_temperature.log:\
  build/$(MODE)/bin/gtk_mesh_2d_colored_zero_cochain_sequence$(.EXE)\
  build/$(MODE)/demo/mesh/mesh_brick_2d_5_forman.txt\
  build/$(MODE)/demo/diffusion/mesh_brick_2d_5_forman_diffusion_transient_continuous_p2_temperature.txt\
  | build/$(MODE)/demo/gtk
	$< --raw $(word 2, $^) 1000 --raw $(word 3, $^) > $@

build/$(MODE)/demo/gtk/mesh_brick_2d_5_forman_diffusion_transient_continuous_p4_temperature.log:\
  build/$(MODE)/bin/gtk_mesh_2d_colored_zero_cochain_sequence$(.EXE)\
  build/$(MODE)/demo/mesh/mesh_brick_2d_5_forman.txt\
  build/$(MODE)/demo/diffusion/mesh_brick_2d_5_forman_diffusion_transient_continuous_p4_temperature.txt\
  | build/$(MODE)/demo/gtk
	$< --raw $(word 2, $^) 10000 --raw $(word 3, $^) > $@

build/$(MODE)/demo/gtk/diffusion_2d_transient_continuous_p4_temperature_primal_strong_cochain_trapezoidal_brick_2d_2_forman.log:\
  build/$(MODE)/bin/gtk_diffusion$(.EXE)\
  build/$(MODE)/demo/mesh/mesh_brick_2d_2_forman.txt\
  build/$(MODE)/demo/diffusion/2d_transient_continuous_p4_temperature_primal_strong_cochain_trapezoidal_brick_2d_2_forman.txt\
  | build/$(MODE)/demo/gtk
	$< --raw $(word 2, $^) $(word 3, $^) > $@

build/$(MODE)/demo/gtk/mesh_brick_2d_10_forman_diffusion_transient_continuous_p4_temperature.log:\
  build/$(MODE)/bin/gtk_mesh_2d_colored_zero_cochain_sequence$(.EXE)\
  build/$(MODE)/demo/mesh/mesh_brick_2d_10_forman.txt\
  build/$(MODE)/demo/diffusion/mesh_brick_2d_10_forman_diffusion_transient_continuous_p4_temperature.txt\
  | build/$(MODE)/demo/gtk
	$< --raw $(word 2, $^) 4000 --raw $(word 3, $^) > $@

build/$(MODE)/demo/gtk/mesh_brick_2d_10_forman_diffusion_transient_continuous_p4_flux.log:\
  build/$(MODE)/bin/gtk_mesh_2d_colored_one_cochain_sequence$(.EXE)\
  build/$(MODE)/demo/mesh/mesh_brick_2d_10_forman.txt\
  build/$(MODE)/demo/diffusion/mesh_brick_2d_10_forman_diffusion_transient_continuous_p4_flux.txt\
  | build/$(MODE)/demo/gtk
	$< --raw $(word 2, $^) 4000 --raw $(word 3, $^) > $@

build/$(MODE)/demo/gtk/mesh_2d_10_grains_forman_diffusion_transient_continuous_p7_temperature.log:\
  build/$(MODE)/bin/gtk_mesh_2d_colored_zero_cochain_sequence$(.EXE)\
  build/$(MODE)/demo/mesh/mesh_2d_10_grains_forman.txt\
  build/$(MODE)/demo/diffusion/mesh_2d_10_grains_forman_diffusion_transient_continuous_p7_temperature.txt\
  | build/$(MODE)/demo/gtk
	$< --raw $(word 2, $^) 1000 --raw $(word 3, $^) > $@

build/$(MODE)/demo/gtk/mesh_2d_10_grains_forman_diffusion_transient_continuous_p7_flux.log:\
  build/$(MODE)/bin/gtk_mesh_2d_colored_one_cochain_sequence$(.EXE)\
  build/$(MODE)/demo/mesh/mesh_2d_10_grains_forman.txt\
  build/$(MODE)/demo/diffusion/mesh_2d_10_grains_forman_diffusion_transient_continuous_p7_flux.txt\
  | build/$(MODE)/demo/gtk
	$< --raw $(word 2, $^) 1000 --raw $(word 3, $^) > $@

build/$(MODE)/demo/gtk/diffusion_2d_transient_continuous_p7_temperature_primal_weak_cochain_trapezoidal_neper_2d_10_grains_forman.log:\
  build/$(MODE)/bin/gtk_mesh_2d_colored_zero_cochain_sequence$(.EXE)\
  build/$(MODE)/demo/mesh/mesh_2d_10_grains_forman.txt\
  build/$(MODE)/demo/diffusion/2d_transient_continuous_p7_temperature_primal_weak_cochain_trapezoidal_neper_2d_10_grains_forman.txt\
  | build/$(MODE)/demo/gtk
	$< --raw $(word 2, $^) 2000 --raw $(word 3, $^) > $@

build/$(MODE)/demo/gtk/diffusion_2d_transient_continuous_p8_temperature_primal_weak_cochain_trapezoidal_neper_2d_10_grains_forman.log:\
  build/$(MODE)/bin/gtk_mesh_2d_colored_zero_cochain_sequence$(.EXE)\
  build/$(MODE)/demo/mesh/mesh_2d_10_grains_forman.txt\
  build/$(MODE)/demo/diffusion/2d_transient_continuous_p8_temperature_primal_weak_cochain_trapezoidal_neper_2d_10_grains_forman.txt\
  | build/$(MODE)/demo/gtk
	$< --raw $(word 2, $^) 2000 --raw $(word 3, $^) > $@

build/$(MODE)/demo/gtk/diffusion_2d_transient_continuous_p7_flux_primal_weak_cochain_trapezoidal_neper_2d_10_grains_forman.log:\
  build/$(MODE)/bin/gtk_mesh_2d_colored_one_cochain_sequence$(.EXE)\
  build/$(MODE)/demo/mesh/mesh_2d_10_grains_forman.txt\
  build/$(MODE)/demo/diffusion/2d_transient_continuous_p7_flux_primal_weak_cochain_trapezoidal_neper_2d_10_grains_forman.txt\
  | build/$(MODE)/demo/gtk
	$< --raw $(word 2, $^) 2000 --raw $(word 3, $^) > $@

build/$(MODE)/demo/gtk/diffusion_2d_transient_continuous_p7_temperature_primal_weak_cochain_trapezoidal_to_steady_state_neper_2d_10_grains_forman.log:\
  build/$(MODE)/bin/gtk_diffusion$(.EXE)\
  build/$(MODE)/demo/mesh/mesh_2d_10_grains_forman.txt\
  build/$(MODE)/demo/diffusion/2d_transient_continuous_p7_temperature_primal_weak_cochain_trapezoidal_to_steady_state_neper_2d_10_grains_forman.txt\
  | build/$(MODE)/demo/gtk
	$< --raw $(word 2, $^) $(word 3, $^) > $@

build/$(MODE)/demo/gtk/mesh_square_8_diffusion_transient_continuous_p5_temperature.log:\
  build/$(MODE)/bin/gtk_mesh_2d_colored_zero_cochain_sequence$(.EXE)\
  build/$(MODE)/demo/mesh/mesh_square_8.txt\
  build/$(MODE)/demo/diffusion/mesh_square_8_diffusion_transient_continuous_p5_temperature.txt\
  | build/$(MODE)/demo/gtk
	$< --raw $(word 2, $^) 4000 --raw $(word 3, $^) > $@

build/$(MODE)/demo/gtk/diffusion-2d-transient-continuous-temperature-primal_weak-cochain-trapezoidal-p4-brick_2d_2_forman.log:\
  build/$(MODE)/bin/gtk_mesh_2d_colored_zero_cochain_sequence$(.EXE)\
  build/$(MODE)/demo/mesh/mesh_brick_2d_2_forman.txt\
  build/$(MODE)/demo/diffusion/2d_transient_continuous_p4_temperature_primal_weak_cochain_trapezoidal_brick_2d_2_forman.txt\
  | build/$(MODE)/demo/gtk
	$< --raw $(word 2, $^) 1000 --raw $(word 3, $^) > $@

.PHONY: demo_gtk_clean
demo_gtk_clean:
	-$(RM) $(_demo_gtk)
	-$(RM) -r build/$(MODE)/demo/gtk
