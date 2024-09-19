_demo_graphics_gtk :=\
  build/$(MODE)/demo/graphics/log/fill_gtk.log\
  build/$(MODE)/demo/graphics/log/mesh_brick_2d_2_forman_diffusion_transient_continuous_p2_temperature_gtk.log\
  build/$(MODE)/demo/graphics/log/mesh_brick_2d_2_forman_diffusion_transient_continuous_p4_temperature_gtk.log\
  build/$(MODE)/demo/graphics/log/mesh_brick_2d_5_forman_diffusion_transient_continuous_p2_temperature_gtk.log\
  build/$(MODE)/demo/graphics/log/mesh_brick_2d_5_forman_diffusion_transient_continuous_p4_temperature_gtk.log\
  build/$(MODE)/demo/graphics/log/mesh_brick_2d_10_forman_diffusion_transient_continuous_p4_temperature_gtk.log\
  build/$(MODE)/demo/graphics/log/mesh_brick_2d_10_forman_diffusion_transient_continuous_p4_flux_gtk.log\
  build/$(MODE)/demo/graphics/log/mesh_2d_10_grains_forman_diffusion_transient_continuous_p7_temperature_gtk.log\
  build/$(MODE)/demo/graphics/log/mesh_2d_10_grains_forman_diffusion_transient_continuous_p7_flux_gtk.log\
  build/$(MODE)/demo/graphics/log/diffusion_2d_transient_continuous_p7_temperature_primal_weak_cochain_trapezoidal_neper_2d_10_grains_forman_gtk.log\
  build/$(MODE)/demo/graphics/log/diffusion_2d_transient_continuous_p7_flux_primal_weak_cochain_trapezoidal_neper_2d_10_grains_forman_gtk.log\
  build/$(MODE)/demo/graphics/log/mesh_square_8_diffusion_transient_continuous_p5_temperature_gtk.log\
  build/$(MODE)/demo/graphics/log/diffusion-2d-transient-continuous-temperature-primal_weak-cochain-trapezoidal-p4-brick_2d_2_forman_gtk.log

.PHONY: demo_graphics_gtk
demo_graphics_gtk: bin $(_demo_graphics_gtk)\
  | build/$(MODE)/demo/graphics/log

build/$(MODE)/demo/graphics/log: | build/$(MODE)/demo/graphics
	mkdir -p $@

build/$(MODE)/demo/graphics/log/fill_gtk.log:\
  build/$(MODE)/bin/gtk_fill | build/$(MODE)/demo/graphics/log
	$< 100 > $@

build/$(MODE)/demo/graphics/log/mesh_brick_2d_2_forman_diffusion_transient_continuous_p2_temperature_gtk.log:\
  build/$(MODE)/bin/gtk_mesh_2d_colored_zero_cochain_sequence$(.EXE)\
  build/$(MODE)/demo/mesh/mesh_brick_2d_2_forman.txt\
  build/$(MODE)/demo/diffusion/mesh_brick_2d_2_forman_diffusion_transient_continuous_p2_temperature.txt\
  | build/$(MODE)/demo/graphics/log
	$< --raw $(word 2, $^) 100 --raw $(word 3, $^) > $@


build/$(MODE)/demo/graphics/log/mesh_brick_2d_5_forman_diffusion_transient_continuous_p2_temperature_gtk.log:\
  build/$(MODE)/bin/gtk_mesh_2d_colored_zero_cochain_sequence$(.EXE)\
  build/$(MODE)/demo/mesh/mesh_brick_2d_5_forman.txt\
  build/$(MODE)/demo/diffusion/mesh_brick_2d_5_forman_diffusion_transient_continuous_p2_temperature.txt\
  | build/$(MODE)/demo/graphics/log
	$< --raw $(word 2, $^) 1000 --raw $(word 3, $^) > $@

build/$(MODE)/demo/graphics/log/mesh_brick_2d_5_forman_diffusion_transient_continuous_p4_temperature_gtk.log:\
  build/$(MODE)/bin/gtk_mesh_2d_colored_zero_cochain_sequence$(.EXE)\
  build/$(MODE)/demo/mesh/mesh_brick_2d_5_forman.txt\
  build/$(MODE)/demo/diffusion/mesh_brick_2d_5_forman_diffusion_transient_continuous_p4_temperature.txt\
  | build/$(MODE)/demo/graphics/log
	$< --raw $(word 2, $^) 10000 --raw $(word 3, $^) > $@

build/$(MODE)/demo/graphics/log/mesh_brick_2d_2_forman_diffusion_transient_continuous_p4_temperature_gtk.log:\
  build/$(MODE)/bin/gtk_diffusion$(.EXE)\
  build/$(MODE)/demo/mesh/mesh_brick_2d_2_forman.txt\
  build/$(MODE)/demo/diffusion/mesh_brick_2d_2_forman_diffusion_transient_continuous_p4_temperature.txt\
  | build/$(MODE)/demo/graphics/log
	$< --raw $(word 2, $^) $(word 3, $^) > $@

build/$(MODE)/demo/graphics/log/mesh_brick_2d_10_forman_diffusion_transient_continuous_p4_temperature_gtk.log:\
  build/$(MODE)/bin/gtk_mesh_2d_colored_zero_cochain_sequence$(.EXE)\
  build/$(MODE)/demo/mesh/mesh_brick_2d_10_forman.txt\
  build/$(MODE)/demo/diffusion/mesh_brick_2d_10_forman_diffusion_transient_continuous_p4_temperature.txt\
  | build/$(MODE)/demo/graphics/log
	$< --raw $(word 2, $^) 4000 --raw $(word 3, $^) > $@

build/$(MODE)/demo/graphics/log/mesh_brick_2d_10_forman_diffusion_transient_continuous_p4_flux_gtk.log:\
  build/$(MODE)/bin/gtk_mesh_2d_colored_one_cochain_sequence$(.EXE)\
  build/$(MODE)/demo/mesh/mesh_brick_2d_10_forman.txt\
  build/$(MODE)/demo/diffusion/mesh_brick_2d_10_forman_diffusion_transient_continuous_p4_flux.txt\
  | build/$(MODE)/demo/graphics/log
	$< --raw $(word 2, $^) 4000 --raw $(word 3, $^) > $@

build/$(MODE)/demo/graphics/log/mesh_2d_10_grains_forman_diffusion_transient_continuous_p7_temperature_gtk.log:\
  build/$(MODE)/bin/gtk_mesh_2d_colored_zero_cochain_sequence$(.EXE)\
  build/$(MODE)/demo/mesh/mesh_2d_10_grains_forman.txt\
  build/$(MODE)/demo/diffusion/mesh_2d_10_grains_forman_diffusion_transient_continuous_p7_temperature.txt\
  | build/$(MODE)/demo/graphics/log
	$< --raw $(word 2, $^) 1000 --raw $(word 3, $^) > $@

build/$(MODE)/demo/graphics/log/mesh_2d_10_grains_forman_diffusion_transient_continuous_p7_flux_gtk.log:\
  build/$(MODE)/bin/gtk_mesh_2d_colored_one_cochain_sequence$(.EXE)\
  build/$(MODE)/demo/mesh/mesh_2d_10_grains_forman.txt\
  build/$(MODE)/demo/diffusion/mesh_2d_10_grains_forman_diffusion_transient_continuous_p7_flux.txt\
  | build/$(MODE)/demo/graphics/log
	$< --raw $(word 2, $^) 1000 --raw $(word 3, $^) > $@

build/$(MODE)/demo/graphics/log/diffusion_2d_transient_continuous_p7_temperature_primal_weak_cochain_trapezoidal_neper_2d_10_grains_forman_gtk.log:\
  build/$(MODE)/bin/gtk_mesh_2d_colored_zero_cochain_sequence$(.EXE)\
  build/$(MODE)/demo/mesh/mesh_2d_10_grains_forman.txt\
  build/$(MODE)/demo/diffusion/2d_transient_continuous_p7_temperature_primal_weak_cochain_trapezoidal_neper_2d_10_grains_forman.txt\
  | build/$(MODE)/demo/graphics/log
	$< --raw $(word 2, $^) 2000 --raw $(word 3, $^) > $@

build/$(MODE)/demo/graphics/log/diffusion_2d_transient_continuous_p7_flux_primal_weak_cochain_trapezoidal_neper_2d_10_grains_forman_gtk.log:\
  build/$(MODE)/bin/gtk_mesh_2d_colored_one_cochain_sequence$(.EXE)\
  build/$(MODE)/demo/mesh/mesh_2d_10_grains_forman.txt\
  build/$(MODE)/demo/diffusion/2d_transient_continuous_p7_flux_primal_weak_cochain_trapezoidal_neper_2d_10_grains_forman.txt\
  | build/$(MODE)/demo/graphics/log
	$< --raw $(word 2, $^) 2000 --raw $(word 3, $^) > $@

build/$(MODE)/demo/graphics/log/mesh_square_8_diffusion_transient_continuous_p5_temperature_gtk.log:\
  build/$(MODE)/bin/gtk_mesh_2d_colored_zero_cochain_sequence$(.EXE)\
  build/$(MODE)/demo/mesh/mesh_square_8.txt\
  build/$(MODE)/demo/diffusion/mesh_square_8_diffusion_transient_continuous_p5_temperature.txt\
  | build/$(MODE)/demo/graphics/log
	$< --raw $(word 2, $^) 4000 --raw $(word 3, $^) > $@

build/$(MODE)/demo/graphics/log/diffusion-2d-transient-continuous-temperature-primal_weak-cochain-trapezoidal-p4-brick_2d_2_forman_gtk.log:\
  build/$(MODE)/bin/gtk_mesh_2d_colored_zero_cochain_sequence$(.EXE)\
  build/$(MODE)/demo/mesh/mesh_brick_2d_2_forman.txt\
  build/$(MODE)/demo/diffusion/2d-transient-continuous-temperature-primal_weak-cochain-trapezoidal-p4-brick_2d_2_forman.txt\
  | build/$(MODE)/demo/graphics/log
	$< --raw $(word 2, $^) 1000 --raw $(word 3, $^) > $@

.PHONY: demo_graphics_gtk_clean
demo_graphics_gtk_clean:
	-$(RM) $(_demo_graphics_gtk)
	-$(RM) -r build/$(MODE)/demo/graphics/log
