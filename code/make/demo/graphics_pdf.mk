_demo_graphics_pdf :=\
  build/$(BUILD_TYPE)/demo/graphics/pdf/fill.pdf\
  build/$(BUILD_TYPE)/demo/graphics/pdf/mesh_pentagon_edge_skeleton.pdf\
  build/$(BUILD_TYPE)/demo/graphics/pdf/mesh_pentagon_forman_edge_skeleton.pdf\
  build/$(BUILD_TYPE)/demo/graphics/pdf/mesh_brick_2d_1_forman_edge_skeleton.pdf\
  build/$(BUILD_TYPE)/demo/graphics/pdf/mesh_brick_2d_10_forman_edge_skeleton.pdf\
  build/$(BUILD_TYPE)/demo/graphics/pdf/mesh_2d_10_grains_edge_skeleton.pdf\
  build/$(BUILD_TYPE)/demo/graphics/pdf/mesh_2d_10_grains_forman_edge_skeleton.pdf\
  build/$(BUILD_TYPE)/demo/graphics/pdf/mesh_brick_2d_2_forman_diffusion_continuous_p0_temperature.pdf\
  build/$(BUILD_TYPE)/demo/graphics/pdf/mesh_brick_2d_2_forman_diffusion_continuous_p0_flux.pdf\
  build/$(BUILD_TYPE)/demo/graphics/pdf/mesh_brick_2d_5_forman_diffusion_continuous_p2_temperature.pdf\
  build/$(BUILD_TYPE)/demo/graphics/pdf/mesh_brick_2d_5_forman_diffusion_continuous_p4_temperature.pdf\
  build/$(BUILD_TYPE)/demo/graphics/pdf/mesh_brick_2d_5_forman_diffusion_steady_state_continuous_p4_temperature.pdf\
  build/$(BUILD_TYPE)/demo/graphics/pdf/mesh_brick_2d_10_forman_diffusion_continuous_p4_temperature.pdf\
  build/$(BUILD_TYPE)/demo/graphics/pdf/mesh_brick_2d_10_forman_diffusion_continuous_p4_flux.pdf\
  build/$(BUILD_TYPE)/demo/graphics/pdf/mesh_2d_10_grains_forman_diffusion_steady_state_continuous_p7_temperature.pdf\
  build/$(BUILD_TYPE)/demo/graphics/pdf/mesh_square_8_diffusion_continuous_p5_temperature.pdf\

.PHONY: demo_graphics_pdf
demo_graphics_pdf: bin $(_demo_graphics_pdf)\
  | build/$(BUILD_TYPE)/demo/graphics/pdf

build/$(BUILD_TYPE)/demo/graphics/pdf: | build/$(BUILD_TYPE)/demo/graphics
	mkdir -p $@

build/$(BUILD_TYPE)/demo/graphics/pdf/fill.pdf:\
  build/$(BUILD_TYPE)/bin/pdf_fill | build/$(BUILD_TYPE)/demo/graphics/pdf
	$< 100 $@

build/$(BUILD_TYPE)/demo/graphics/pdf/mesh_pentagon_edge_skeleton.pdf:\
  build/$(BUILD_TYPE)/bin/pdf_mesh_2d_colored_edge_skeleton$(.EXE)\
  data/mesh/mesh_pentagon.txt\
  | build/$(BUILD_TYPE)/demo/graphics/pdf
	$< --raw $(word 2, $^) $@

build/$(BUILD_TYPE)/demo/graphics/pdf/mesh_pentagon_forman_edge_skeleton.pdf:\
  build/$(BUILD_TYPE)/bin/pdf_mesh_2d_colored_edge_skeleton$(.EXE)\
  build/$(BUILD_TYPE)/demo/mesh/mesh_pentagon_forman.txt\
  | build/$(BUILD_TYPE)/demo/graphics/pdf
	$< --raw $(word 2, $^) $@

build/$(BUILD_TYPE)/demo/graphics/pdf/mesh_brick_2d_1_forman_edge_skeleton.pdf:\
  build/$(BUILD_TYPE)/bin/pdf_mesh_2d_colored_edge_skeleton$(.EXE)\
  build/$(BUILD_TYPE)/demo/mesh/mesh_brick_2d_1_forman.txt\
  | build/$(BUILD_TYPE)/demo/graphics/pdf
	$< --raw $(word 2, $^) $@

build/$(BUILD_TYPE)/demo/graphics/pdf/mesh_brick_2d_10_forman_edge_skeleton.pdf:\
  build/$(BUILD_TYPE)/bin/pdf_mesh_2d_colored_edge_skeleton$(.EXE)\
  build/$(BUILD_TYPE)/demo/mesh/mesh_brick_2d_10_forman.txt\
  | build/$(BUILD_TYPE)/demo/graphics/pdf
	$< --raw $(word 2, $^) $@

build/$(BUILD_TYPE)/demo/graphics/pdf/mesh_2d_10_grains_edge_skeleton.pdf:\
  build/$(BUILD_TYPE)/bin/pdf_mesh_2d_colored_edge_skeleton$(.EXE)\
  data/mesh/mesh_2d_10_grains.tess\
  | build/$(BUILD_TYPE)/demo/graphics/pdf
	$< --tess $(word 2, $^) $@

build/$(BUILD_TYPE)/demo/graphics/pdf/mesh_2d_10_grains_forman_edge_skeleton.pdf:\
  build/$(BUILD_TYPE)/bin/pdf_mesh_2d_colored_edge_skeleton$(.EXE)\
  build/$(BUILD_TYPE)/demo/mesh/mesh_2d_10_grains_forman.txt\
  | build/$(BUILD_TYPE)/demo/graphics/pdf
	$< --raw $(word 2, $^) $@

build/$(BUILD_TYPE)/demo/graphics/pdf/mesh_brick_2d_2_forman_diffusion_continuous_p0_temperature.pdf:\
  build/$(BUILD_TYPE)/bin/pdf_mesh_2d_colored_zero_cochain_sequence$(.EXE)\
  build/$(BUILD_TYPE)/demo/mesh/mesh_brick_2d_2_forman.txt\
  build/$(BUILD_TYPE)/demo/mesh/mesh_brick_2d_2_forman_diffusion_continuous_p0_temperature.txt\
  | build/$(BUILD_TYPE)/demo/graphics/pdf
	$< --raw $(word 2, $^) 20 --raw $(word 3, $^) $@

build/$(BUILD_TYPE)/demo/graphics/pdf/mesh_brick_2d_2_forman_diffusion_continuous_p0_flux.pdf:\
  build/$(BUILD_TYPE)/bin/pdf_mesh_2d_colored_one_cochain_sequence$(.EXE)\
  build/$(BUILD_TYPE)/demo/mesh/mesh_brick_2d_2_forman.txt\
  build/$(BUILD_TYPE)/demo/mesh/mesh_brick_2d_2_forman_diffusion_continuous_p0_flux.txt\
  | build/$(BUILD_TYPE)/demo/graphics/pdf
	$< --raw $(word 2, $^) 20 --raw $(word 3, $^) $@

build/$(BUILD_TYPE)/demo/graphics/pdf/mesh_brick_2d_5_forman_diffusion_continuous_p2_temperature.pdf:\
  build/$(BUILD_TYPE)/bin/pdf_mesh_2d_colored_zero_cochain_sequence$(.EXE)\
  build/$(BUILD_TYPE)/demo/mesh/mesh_brick_2d_5_forman.txt\
  build/$(BUILD_TYPE)/demo/mesh/mesh_brick_2d_5_forman_diffusion_continuous_p2_temperature.txt\
  | build/$(BUILD_TYPE)/demo/graphics/pdf
	$< --raw $(word 2, $^) 1000 --raw $(word 3, $^) $@

build/$(BUILD_TYPE)/demo/graphics/pdf/mesh_brick_2d_5_forman_diffusion_continuous_p4_temperature.pdf:\
  build/$(BUILD_TYPE)/bin/pdf_mesh_2d_colored_zero_cochain_sequence$(.EXE)\
  build/$(BUILD_TYPE)/demo/mesh/mesh_brick_2d_5_forman.txt\
  build/$(BUILD_TYPE)/demo/mesh/mesh_brick_2d_5_forman_diffusion_continuous_p4_temperature.txt\
  | build/$(BUILD_TYPE)/demo/graphics/pdf
	$< --raw $(word 2, $^) 10000 --raw $(word 3, $^) $@

build/$(BUILD_TYPE)/demo/graphics/pdf/mesh_brick_2d_5_forman_diffusion_steady_state_continuous_p4_temperature.pdf:\
  build/$(BUILD_TYPE)/bin/pdf_mesh_2d_colored_zero_cochain_sequence$(.EXE)\
  build/$(BUILD_TYPE)/demo/mesh/mesh_brick_2d_5_forman.txt\
  build/$(BUILD_TYPE)/demo/mesh/mesh_brick_2d_5_forman_diffusion_steady_state_continuous_p4_temperature.txt\
  | build/$(BUILD_TYPE)/demo/graphics/pdf
	$< --raw $(word 2, $^) 0 --raw $(word 3, $^) $@

build/$(BUILD_TYPE)/demo/graphics/pdf/mesh_brick_2d_10_forman_diffusion_continuous_p4_temperature.pdf:\
  build/$(BUILD_TYPE)/bin/pdf_mesh_2d_colored_zero_cochain_sequence$(.EXE)\
  build/$(BUILD_TYPE)/demo/mesh/mesh_brick_2d_10_forman.txt\
  build/$(BUILD_TYPE)/demo/mesh/mesh_brick_2d_10_forman_diffusion_continuous_p4_temperature.txt\
  | build/$(BUILD_TYPE)/demo/graphics/pdf
	$< --raw $(word 2, $^) 4000 --raw $(word 3, $^) $@

build/$(BUILD_TYPE)/demo/graphics/pdf/mesh_brick_2d_10_forman_diffusion_continuous_p4_flux.pdf:\
  build/$(BUILD_TYPE)/bin/pdf_mesh_2d_colored_one_cochain_sequence$(.EXE)\
  build/$(BUILD_TYPE)/demo/mesh/mesh_brick_2d_10_forman.txt\
  build/$(BUILD_TYPE)/demo/mesh/mesh_brick_2d_10_forman_diffusion_continuous_p4_flux.txt\
  | build/$(BUILD_TYPE)/demo/graphics/pdf
	$< --raw $(word 2, $^) 4000 --raw $(word 3, $^) $@

build/$(BUILD_TYPE)/demo/graphics/pdf/mesh_2d_10_grains_forman_diffusion_steady_state_continuous_p7_temperature.pdf:\
  build/$(BUILD_TYPE)/bin/pdf_mesh_2d_colored_zero_cochain_sequence$(.EXE)\
  build/$(BUILD_TYPE)/demo/mesh/mesh_2d_10_grains_forman.txt\
  build/$(BUILD_TYPE)/demo/mesh/mesh_2d_10_grains_forman_diffusion_steady_state_continuous_p7_temperature.txt\
  | build/$(BUILD_TYPE)/demo/graphics/pdf
	$< --raw $(word 2, $^) 0 --raw $(word 3, $^) $@

build/$(BUILD_TYPE)/demo/graphics/pdf/mesh_square_8_diffusion_continuous_p5_temperature.pdf:\
  build/$(BUILD_TYPE)/bin/pdf_mesh_2d_colored_zero_cochain_sequence$(.EXE)\
  build/$(BUILD_TYPE)/demo/mesh/mesh_square_8.txt\
  build/$(BUILD_TYPE)/demo/mesh/mesh_square_8_diffusion_continuous_p5_temperature.txt\
  | build/$(BUILD_TYPE)/demo/graphics/pdf
	$< --raw $(word 2, $^) 4000 --raw $(word 3, $^) $@

.PHONY: demo_graphics_pdf_clean
demo_graphics_pdf_clean:
	-$(RM) $(_demo_graphics_pdf)
	-$(RM) -r build/$(BUILD_TYPE)/demo/graphics/pdf
