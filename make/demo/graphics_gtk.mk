_demo_graphics_gtk :=\
  demo/graphics/log/fill_gtk.log\
  demo/graphics/log/mesh_brick_2d_2_forman_diffusion_continuous_p2_temperature_gtk.log\
  demo/graphics/log/mesh_brick_2d_2_forman_diffusion_continuous_p4_temperature_gtk.log\
  demo/graphics/log/mesh_brick_2d_5_forman_diffusion_continuous_p2_temperature_gtk.log\
  demo/graphics/log/mesh_brick_2d_5_forman_diffusion_continuous_p4_temperature_gtk.log\
  demo/graphics/log/mesh_brick_2d_10_forman_diffusion_continuous_p4_temperature_gtk.log\
  demo/graphics/log/mesh_brick_2d_10_forman_diffusion_continuous_p4_flux_gtk.log\
  demo/graphics/log/mesh_2d_10_grains_forman_diffusion_continuous_p7_temperature_gtk.log\
  demo/graphics/log/mesh_2d_10_grains_forman_diffusion_continuous_p7_flux_gtk.log\
  demo/graphics/log/mesh_square_8_diffusion_continuous_p5_temperature_gtk.log\

.PHONY: demo_graphics_gtk
demo_graphics_gtk: bin_all $(_demo_graphics_gtk) | demo/graphics/log

demo/graphics/log: | demo/graphics
	mkdir -p $@

demo/graphics/log/fill_gtk.log: bin/gtk_fill | demo/graphics/log
	$< 100 > $@

demo/graphics/log/mesh_brick_2d_2_forman_diffusion_continuous_p2_temperature_gtk.log:\
	  bin/gtk_mesh_2d_colored_zero_cochain_sequence$(.EXE)\
	  demo/mesh/mesh_brick_2d_2_forman.txt\
	  demo/mesh/mesh_brick_2d_2_forman_diffusion_continuous_p2_temperature.txt\
	  | demo/graphics/log
	$< --raw $(word 2, $^) 100 --raw $(word 3, $^) > $@


demo/graphics/log/mesh_brick_2d_5_forman_diffusion_continuous_p2_temperature_gtk.log:\
	  bin/gtk_mesh_2d_colored_zero_cochain_sequence$(.EXE)\
	  demo/mesh/mesh_brick_2d_5_forman.txt\
	  demo/mesh/mesh_brick_2d_5_forman_diffusion_continuous_p2_temperature.txt\
	  | demo/graphics/log
	$< --raw $(word 2, $^) 1000 --raw $(word 3, $^) > $@

demo/graphics/log/mesh_brick_2d_5_forman_diffusion_continuous_p4_temperature_gtk.log:\
	  bin/gtk_mesh_2d_colored_zero_cochain_sequence$(.EXE)\
	  demo/mesh/mesh_brick_2d_5_forman.txt\
	  demo/mesh/mesh_brick_2d_5_forman_diffusion_continuous_p4_temperature.txt\
	  | demo/graphics/log
	$< --raw $(word 2, $^) 10000 --raw $(word 3, $^) > $@

demo/graphics/log/mesh_brick_2d_2_forman_diffusion_continuous_p4_temperature_gtk.log:\
	  bin/gtk_diffusion$(.EXE)\
	  demo/mesh/mesh_brick_2d_2_forman.txt\
	  demo/mesh/mesh_brick_2d_2_forman_diffusion_continuous_p4_temperature.txt\
	  | demo/graphics/log
	$< --raw $(word 2, $^) $(word 3, $^) > $@

demo/graphics/log/mesh_brick_2d_10_forman_diffusion_continuous_p4_temperature_gtk.log:\
	  bin/gtk_mesh_2d_colored_zero_cochain_sequence$(.EXE)\
	  demo/mesh/mesh_brick_2d_10_forman.txt\
	  demo/mesh/mesh_brick_2d_10_forman_diffusion_continuous_p4_temperature.txt\
	  | demo/graphics/log
	$< --raw $(word 2, $^) 4000 --raw $(word 3, $^) > $@

demo/graphics/log/mesh_brick_2d_10_forman_diffusion_continuous_p4_flux_gtk.log:\
	  bin/gtk_mesh_2d_colored_one_cochain_sequence$(.EXE)\
	  demo/mesh/mesh_brick_2d_10_forman.txt\
	  demo/mesh/mesh_brick_2d_10_forman_diffusion_continuous_p4_flux.txt\
	  | demo/graphics/log
	$< --raw $(word 2, $^) 4000 --raw $(word 3, $^) > $@

demo/graphics/log/mesh_2d_10_grains_forman_diffusion_continuous_p7_temperature_gtk.log:\
	  bin/gtk_mesh_2d_colored_zero_cochain_sequence$(.EXE)\
	  demo/mesh/mesh_2d_10_grains_forman.txt\
	  demo/mesh/mesh_2d_10_grains_forman_diffusion_continuous_p7_temperature.txt\
	  | demo/graphics/log
	$< --raw $(word 2, $^) 1000 --raw $(word 3, $^) > $@

demo/graphics/log/mesh_2d_10_grains_forman_diffusion_continuous_p7_flux_gtk.log:\
	  bin/gtk_mesh_2d_colored_one_cochain_sequence$(.EXE)\
	  demo/mesh/mesh_2d_10_grains_forman.txt\
	  demo/mesh/mesh_2d_10_grains_forman_diffusion_continuous_p7_flux.txt\
	  | demo/graphics/log
	$< --raw $(word 2, $^) 1000 --raw $(word 3, $^) > $@

demo/graphics/log/mesh_square_8_diffusion_continuous_p5_temperature_gtk.log:\
	  bin/gtk_mesh_2d_colored_zero_cochain_sequence$(.EXE)\
	  demo/mesh/mesh_square_8.txt\
	  demo/mesh/mesh_square_8_diffusion_continuous_p5_temperature.txt\
	  | demo/graphics/log
	$< --raw $(word 2, $^) 4000 --raw $(word 3, $^) > $@

# demo/graphics/log/mesh_square_8_diffusion_continuous_p5_temperature_gtk.log:\
# 	  bin/gtk_diffusion\
# 	  demo/mesh/mesh_square_8.txt\
# 	  demo/mesh/mesh_square_8_diffusion_continuous_p5_temperature.txt\
# 	  | demo/graphics/log
# 	$< --raw $(word 2, $^) $(word 3, $^) > $@

.PHONY: demo_graphics_gtk_clean
demo_graphics_gtk_clean:
	-$(RM) $(_demo_graphics_gtk)
	-$(RM) -r demo/graphics/log
