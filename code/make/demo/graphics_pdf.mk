_demo_graphics_pdf :=\
  build/$(MODE)/demo/graphics/pdf/fill.pdf\
  build/$(MODE)/demo/graphics/pdf/mesh_pentagon_edge_skeleton.pdf\
  build/$(MODE)/demo/graphics/pdf/mesh_pentagon_forman_edge_skeleton.pdf\
  build/$(MODE)/demo/graphics/pdf/mesh_brick_2d_1_forman_edge_skeleton.pdf\
  build/$(MODE)/demo/graphics/pdf/mesh_brick_2d_10_forman_edge_skeleton.pdf\
  build/$(MODE)/demo/graphics/pdf/mesh_2d_10_grains_edge_skeleton.pdf\
  build/$(MODE)/demo/graphics/pdf/mesh_2d_10_grains_forman_edge_skeleton.pdf\
  build/$(MODE)/demo/graphics/pdf/mesh_brick_2d_2_forman_diffusion_transient_continuous_p0_temperature.pdf\
  build/$(MODE)/demo/graphics/pdf/mesh_brick_2d_2_forman_diffusion_transient_continuous_p0_flux.pdf\
  build/$(MODE)/demo/graphics/pdf/mesh_brick_2d_2_forman_diffusion_steady_state_continuous_p4_primal_weak_temperature.pdf\
  build/$(MODE)/demo/graphics/pdf/mesh_brick_2d_5_forman_diffusion_transient_continuous_p2_temperature.pdf\
  build/$(MODE)/demo/graphics/pdf/mesh_brick_2d_5_forman_diffusion_transient_continuous_p4_temperature.pdf\
  build/$(MODE)/demo/graphics/pdf/mesh_brick_2d_5_forman_diffusion_steady_state_continuous_p4_temperature.pdf\
  build/$(MODE)/demo/graphics/pdf/mesh_brick_2d_10_forman_diffusion_transient_continuous_p4_temperature.pdf\
  build/$(MODE)/demo/graphics/pdf/mesh_brick_2d_10_forman_diffusion_transient_continuous_p4_flux.pdf\
  build/$(MODE)/demo/graphics/pdf/mesh_2d_10_grains_forman_diffusion_steady_state_continuous_p7_temperature.pdf\
  build/$(MODE)/demo/graphics/pdf/mesh_2d_10_grains_forman_diffusion_steady_state_continuous_p7_primal_weak_temperature.pdf\
  build/$(MODE)/demo/graphics/pdf/mesh_square_8_diffusion_transient_continuous_p5_temperature.pdf\

.PHONY: demo_graphics_pdf
demo_graphics_pdf: bin $(_demo_graphics_pdf)\
  | build/$(MODE)/demo/graphics/pdf

build/$(MODE)/demo/graphics/pdf: | build/$(MODE)/demo/graphics
	mkdir -p $@

build/$(MODE)/demo/graphics/pdf/fill.pdf:\
  build/$(MODE)/bin/pdf_fill | build/$(MODE)/demo/graphics/pdf
	$< 100 $@

build/$(MODE)/demo/graphics/pdf/mesh_pentagon_edge_skeleton.pdf:\
  build/$(MODE)/bin/pdf_mesh_2d_colored_edge_skeleton$(.EXE)\
  data/mesh/mesh_pentagon.txt\
  | build/$(MODE)/demo/graphics/pdf
	$< --raw $(word 2, $^) $@

build/$(MODE)/demo/graphics/pdf/mesh_pentagon_forman_edge_skeleton.pdf:\
  build/$(MODE)/bin/pdf_mesh_2d_colored_edge_skeleton$(.EXE)\
  build/$(MODE)/demo/mesh/mesh_pentagon_forman.txt\
  | build/$(MODE)/demo/graphics/pdf
	$< --raw $(word 2, $^) $@

build/$(MODE)/demo/graphics/pdf/mesh_brick_2d_1_forman_edge_skeleton.pdf:\
  build/$(MODE)/bin/pdf_mesh_2d_colored_edge_skeleton$(.EXE)\
  build/$(MODE)/demo/mesh/mesh_brick_2d_1_forman.txt\
  | build/$(MODE)/demo/graphics/pdf
	$< --raw $(word 2, $^) $@

build/$(MODE)/demo/graphics/pdf/mesh_brick_2d_10_forman_edge_skeleton.pdf:\
  build/$(MODE)/bin/pdf_mesh_2d_colored_edge_skeleton$(.EXE)\
  build/$(MODE)/demo/mesh/mesh_brick_2d_10_forman.txt\
  | build/$(MODE)/demo/graphics/pdf
	$< --raw $(word 2, $^) $@

build/$(MODE)/demo/graphics/pdf/mesh_2d_10_grains_edge_skeleton.pdf:\
  build/$(MODE)/bin/pdf_mesh_2d_colored_edge_skeleton$(.EXE)\
  data/mesh/mesh_2d_10_grains.tess\
  | build/$(MODE)/demo/graphics/pdf
	$< --tess $(word 2, $^) $@

build/$(MODE)/demo/graphics/pdf/mesh_2d_10_grains_forman_edge_skeleton.pdf:\
  build/$(MODE)/bin/pdf_mesh_2d_colored_edge_skeleton$(.EXE)\
  build/$(MODE)/demo/mesh/mesh_2d_10_grains_forman.txt\
  | build/$(MODE)/demo/graphics/pdf
	$< --raw $(word 2, $^) $@

build/$(MODE)/demo/graphics/pdf/mesh_brick_2d_2_forman_diffusion_transient_continuous_p0_temperature.pdf:\
  build/$(MODE)/bin/pdf_mesh_2d_colored_zero_cochain_sequence$(.EXE)\
  build/$(MODE)/demo/mesh/mesh_brick_2d_2_forman.txt\
  build/$(MODE)/demo/diffusion/mesh_brick_2d_2_forman_diffusion_transient_continuous_p0_temperature.txt\
  | build/$(MODE)/demo/graphics/pdf
	$< --raw $(word 2, $^) 20 --raw $(word 3, $^) $@

build/$(MODE)/demo/graphics/pdf/mesh_brick_2d_2_forman_diffusion_transient_continuous_p0_flux.pdf:\
  build/$(MODE)/bin/pdf_mesh_2d_colored_one_cochain_sequence$(.EXE)\
  build/$(MODE)/demo/mesh/mesh_brick_2d_2_forman.txt\
  build/$(MODE)/demo/diffusion/mesh_brick_2d_2_forman_diffusion_transient_continuous_p0_flux.txt\
  | build/$(MODE)/demo/graphics/pdf
	$< --raw $(word 2, $^) 20 --raw $(word 3, $^) $@

build/$(MODE)/demo/graphics/pdf/mesh_brick_2d_2_forman_diffusion_steady_state_continuous_p4_primal_weak_temperature.pdf:\
  build/$(MODE)/bin/pdf_mesh_2d_colored_zero_cochain_sequence$(.EXE)\
  build/$(MODE)/demo/mesh/mesh_brick_2d_2_forman.txt\
  build/$(MODE)/demo/diffusion/mesh_brick_2d_2_forman_diffusion_steady_state_continuous_p4_primal_weak_temperature.txt\
  | build/$(MODE)/demo/graphics/pdf
	$< --raw $(word 2, $^) 0 --raw $(word 3, $^) $@

build/$(MODE)/demo/graphics/pdf/mesh_brick_2d_5_forman_diffusion_transient_continuous_p2_temperature.pdf:\
  build/$(MODE)/bin/pdf_mesh_2d_colored_zero_cochain_sequence$(.EXE)\
  build/$(MODE)/demo/mesh/mesh_brick_2d_5_forman.txt\
  build/$(MODE)/demo/diffusion/mesh_brick_2d_5_forman_diffusion_transient_continuous_p2_temperature.txt\
  | build/$(MODE)/demo/graphics/pdf
	$< --raw $(word 2, $^) 1000 --raw $(word 3, $^) $@

build/$(MODE)/demo/graphics/pdf/mesh_brick_2d_5_forman_diffusion_transient_continuous_p4_temperature.pdf:\
  build/$(MODE)/bin/pdf_mesh_2d_colored_zero_cochain_sequence$(.EXE)\
  build/$(MODE)/demo/mesh/mesh_brick_2d_5_forman.txt\
  build/$(MODE)/demo/diffusion/mesh_brick_2d_5_forman_diffusion_transient_continuous_p4_temperature.txt\
  | build/$(MODE)/demo/graphics/pdf
	$< --raw $(word 2, $^) 10000 --raw $(word 3, $^) $@

build/$(MODE)/demo/graphics/pdf/mesh_brick_2d_5_forman_diffusion_steady_state_continuous_p4_temperature.pdf:\
  build/$(MODE)/bin/pdf_mesh_2d_colored_zero_cochain_sequence$(.EXE)\
  build/$(MODE)/demo/mesh/mesh_brick_2d_5_forman.txt\
  build/$(MODE)/demo/diffusion/mesh_brick_2d_5_forman_diffusion_steady_state_continuous_p4_temperature.txt\
  | build/$(MODE)/demo/graphics/pdf
	$< --raw $(word 2, $^) 0 --raw $(word 3, $^) $@

build/$(MODE)/demo/graphics/pdf/mesh_brick_2d_10_forman_diffusion_transient_continuous_p4_temperature.pdf:\
  build/$(MODE)/bin/pdf_mesh_2d_colored_zero_cochain_sequence$(.EXE)\
  build/$(MODE)/demo/mesh/mesh_brick_2d_10_forman.txt\
  build/$(MODE)/demo/diffusion/mesh_brick_2d_10_forman_diffusion_transient_continuous_p4_temperature.txt\
  | build/$(MODE)/demo/graphics/pdf
	$< --raw $(word 2, $^) 4000 --raw $(word 3, $^) $@

build/$(MODE)/demo/graphics/pdf/mesh_brick_2d_10_forman_diffusion_transient_continuous_p4_flux.pdf:\
  build/$(MODE)/bin/pdf_mesh_2d_colored_one_cochain_sequence$(.EXE)\
  build/$(MODE)/demo/mesh/mesh_brick_2d_10_forman.txt\
  build/$(MODE)/demo/diffusion/mesh_brick_2d_10_forman_diffusion_transient_continuous_p4_flux.txt\
  | build/$(MODE)/demo/graphics/pdf
	$< --raw $(word 2, $^) 4000 --raw $(word 3, $^) $@

build/$(MODE)/demo/graphics/pdf/mesh_2d_10_grains_forman_diffusion_steady_state_continuous_p7_temperature.pdf:\
  build/$(MODE)/bin/pdf_mesh_2d_colored_zero_cochain_sequence$(.EXE)\
  build/$(MODE)/demo/mesh/mesh_2d_10_grains_forman.txt\
  build/$(MODE)/demo/diffusion/mesh_2d_10_grains_forman_diffusion_steady_state_continuous_p7_temperature.txt\
  | build/$(MODE)/demo/graphics/pdf
	$< --raw $(word 2, $^) 0 --raw $(word 3, $^) $@

build/$(MODE)/demo/graphics/pdf/mesh_2d_10_grains_forman_diffusion_steady_state_continuous_p7_primal_weak_temperature.pdf:\
  build/$(MODE)/bin/pdf_mesh_2d_colored_zero_cochain_sequence$(.EXE)\
  build/$(MODE)/demo/mesh/mesh_2d_10_grains_forman.txt\
  build/$(MODE)/demo/diffusion/mesh_2d_10_grains_forman_diffusion_steady_state_continuous_p7_primal_weak_temperature.txt\
  | build/$(MODE)/demo/graphics/pdf
	$< --raw $(word 2, $^) 0 --raw $(word 3, $^) $@

build/$(MODE)/demo/graphics/pdf/mesh_square_8_diffusion_transient_continuous_p5_temperature.pdf:\
  build/$(MODE)/bin/pdf_mesh_2d_colored_zero_cochain_sequence$(.EXE)\
  build/$(MODE)/demo/mesh/mesh_square_8.txt\
  build/$(MODE)/demo/diffusion/mesh_square_8_diffusion_transient_continuous_p5_temperature.txt\
  | build/$(MODE)/demo/graphics/pdf
	$< --raw $(word 2, $^) 4000 --raw $(word 3, $^) $@

.PHONY: demo_graphics_pdf_clean
demo_graphics_pdf_clean:
	-$(RM) $(_demo_graphics_pdf)
	-$(RM) -r build/$(MODE)/demo/graphics/pdf
