_demo_graphics_pdf :=\
  demo/graphics/pdf/fill.pdf\
  demo/graphics/pdf/mesh_pentagon_edge_skeleton.pdf\
  demo/graphics/pdf/mesh_pentagon_forman_edge_skeleton.pdf\
  demo/graphics/pdf/mesh_brick_2d_1_forman_edge_skeleton.pdf\
  demo/graphics/pdf/mesh_brick_2d_10_forman_edge_skeleton.pdf\
  demo/graphics/pdf/mesh_2d_10_grains_edge_skeleton.pdf\
  demo/graphics/pdf/mesh_2d_10_grains_forman_edge_skeleton.pdf\
  demo/graphics/pdf/mesh_brick_2d_2_forman_diffusion_continuous_p0_temperature.pdf\
  demo/graphics/pdf/mesh_brick_2d_2_forman_diffusion_continuous_p0_flux.pdf\
  demo/graphics/pdf/mesh_brick_2d_5_forman_diffusion_continuous_p2_temperature.pdf\
  demo/graphics/pdf/mesh_brick_2d_5_forman_diffusion_continuous_p4_temperature.pdf\
  demo/graphics/pdf/mesh_brick_2d_5_forman_diffusion_steady_state_continuous_p4_temperature.pdf\
  demo/graphics/pdf/mesh_brick_2d_10_forman_diffusion_continuous_p4_temperature.pdf\
  demo/graphics/pdf/mesh_brick_2d_10_forman_diffusion_continuous_p4_flux.pdf\
  demo/graphics/pdf/mesh_2d_10_grains_forman_diffusion_steady_state_continuous_p7_temperature.pdf\
  demo/graphics/pdf/mesh_square_8_diffusion_continuous_p5_temperature.pdf\

.PHONY: demo_graphics_pdf
demo_graphics_pdf: bin_all $(_demo_graphics_pdf) | demo/graphics/pdf

demo/graphics/pdf: | demo/graphics
	mkdir -p $@

demo/graphics/pdf/fill.pdf: bin/pdf_fill | demo/graphics/pdf
	$< 100 $@

demo/graphics/pdf/mesh_pentagon_edge_skeleton.pdf:\
	  bin/pdf_mesh_2d_colored_edge_skeleton$(.EXE)\
	  data/mesh/mesh_pentagon.txt\
	  | demo/graphics/pdf
	$< --raw $(word 2, $^) $@

demo/graphics/pdf/mesh_pentagon_forman_edge_skeleton.pdf:\
	  bin/pdf_mesh_2d_colored_edge_skeleton$(.EXE)\
	  demo/mesh/mesh_pentagon_forman.txt\
	  | demo/graphics/pdf
	$< --raw $(word 2, $^) $@

demo/graphics/pdf/mesh_brick_2d_1_forman_edge_skeleton.pdf:\
	  bin/pdf_mesh_2d_colored_edge_skeleton$(.EXE)\
	  demo/mesh/mesh_brick_2d_1_forman.txt\
	  | demo/graphics/pdf
	$< --raw $(word 2, $^) $@

demo/graphics/pdf/mesh_brick_2d_10_forman_edge_skeleton.pdf:\
	  bin/pdf_mesh_2d_colored_edge_skeleton$(.EXE)\
	  demo/mesh/mesh_brick_2d_10_forman.txt\
	  | demo/graphics/pdf
	$< --raw $(word 2, $^) $@

demo/graphics/pdf/mesh_2d_10_grains_edge_skeleton.pdf:\
	  bin/pdf_mesh_2d_colored_edge_skeleton$(.EXE)\
	  data/mesh/mesh_2d_10_grains.tess\
	  | demo/graphics/pdf
	$< --tess $(word 2, $^) $@

demo/graphics/pdf/mesh_2d_10_grains_forman_edge_skeleton.pdf:\
	  bin/pdf_mesh_2d_colored_edge_skeleton$(.EXE)\
	  demo/mesh/mesh_2d_10_grains_forman.txt\
	  | demo/graphics/pdf
	$< --raw $(word 2, $^) $@

demo/graphics/pdf/mesh_brick_2d_2_forman_diffusion_continuous_p0_temperature.pdf:\
	  bin/pdf_mesh_2d_colored_zero_cochain_sequence$(.EXE)\
	  demo/mesh/mesh_brick_2d_2_forman.txt\
	  demo/mesh/mesh_brick_2d_2_forman_diffusion_continuous_p0_temperature.txt\
	  | demo/graphics/pdf
	$< --raw $(word 2, $^) 20 --raw $(word 3, $^) $@

demo/graphics/pdf/mesh_brick_2d_2_forman_diffusion_continuous_p0_flux.pdf:\
	  bin/pdf_mesh_2d_colored_one_cochain_sequence$(.EXE)\
	  demo/mesh/mesh_brick_2d_2_forman.txt\
	  demo/mesh/mesh_brick_2d_2_forman_diffusion_continuous_p0_flux.txt\
	  | demo/graphics/pdf
	$< --raw $(word 2, $^) 20 --raw $(word 3, $^) $@

demo/graphics/pdf/mesh_brick_2d_5_forman_diffusion_continuous_p2_temperature.pdf:\
	  bin/pdf_mesh_2d_colored_zero_cochain_sequence$(.EXE)\
	  demo/mesh/mesh_brick_2d_5_forman.txt\
	  demo/mesh/mesh_brick_2d_5_forman_diffusion_continuous_p2_temperature.txt\
	  | demo/graphics/pdf
	$< --raw $(word 2, $^) 1000 --raw $(word 3, $^) $@

demo/graphics/pdf/mesh_brick_2d_5_forman_diffusion_continuous_p4_temperature.pdf:\
	  bin/pdf_mesh_2d_colored_zero_cochain_sequence$(.EXE)\
	  demo/mesh/mesh_brick_2d_5_forman.txt\
	  demo/mesh/mesh_brick_2d_5_forman_diffusion_continuous_p4_temperature.txt\
	  | demo/graphics/pdf
	$< --raw $(word 2, $^) 10000 --raw $(word 3, $^) $@

demo/graphics/pdf/mesh_brick_2d_5_forman_diffusion_steady_state_continuous_p4_temperature.pdf:\
	  bin/pdf_mesh_2d_colored_zero_cochain_sequence$(.EXE)\
	  demo/mesh/mesh_brick_2d_5_forman.txt\
	  demo/mesh/mesh_brick_2d_5_forman_diffusion_steady_state_continuous_p4_temperature.txt\
	  | demo/graphics/pdf
	$< --raw $(word 2, $^) 0 --raw $(word 3, $^) $@

demo/graphics/pdf/mesh_brick_2d_10_forman_diffusion_continuous_p4_temperature.pdf:\
	  bin/pdf_mesh_2d_colored_zero_cochain_sequence$(.EXE)\
	  demo/mesh/mesh_brick_2d_10_forman.txt\
	  demo/mesh/mesh_brick_2d_10_forman_diffusion_continuous_p4_temperature.txt\
	  | demo/graphics/pdf
	$< --raw $(word 2, $^) 4000 --raw $(word 3, $^) $@

demo/graphics/pdf/mesh_brick_2d_10_forman_diffusion_continuous_p4_flux.pdf:\
	  bin/pdf_mesh_2d_colored_one_cochain_sequence$(.EXE)\
	  demo/mesh/mesh_brick_2d_10_forman.txt\
	  demo/mesh/mesh_brick_2d_10_forman_diffusion_continuous_p4_flux.txt\
	  | demo/graphics/pdf
	$< --raw $(word 2, $^) 4000 --raw $(word 3, $^) $@

demo/graphics/pdf/mesh_2d_10_grains_forman_diffusion_steady_state_continuous_p7_temperature.pdf:\
	  bin/pdf_mesh_2d_colored_zero_cochain_sequence$(.EXE)\
	  demo/mesh/mesh_2d_10_grains_forman.txt\
	  demo/mesh/mesh_2d_10_grains_forman_diffusion_steady_state_continuous_p7_temperature.txt\
	  | demo/graphics/pdf
	$< --raw $(word 2, $^) 0 --raw $(word 3, $^) $@

demo/graphics/pdf/mesh_square_8_diffusion_continuous_p5_temperature.pdf:\
	  bin/pdf_mesh_2d_colored_zero_cochain_sequence$(.EXE)\
	  demo/mesh/mesh_square_8.txt\
	  demo/mesh/mesh_square_8_diffusion_continuous_p5_temperature.txt\
	  | demo/graphics/pdf
	$< --raw $(word 2, $^) 4000 --raw $(word 3, $^) $@

.PHONY: demo_graphics_pdf_clean
demo_graphics_pdf_clean:
	-$(RM) $(_demo_graphics_pdf)
	-$(RM) -r demo/graphics/pdf
