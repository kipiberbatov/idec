_demo_pdf_mesh :=\
  build/$(MODE)/demo/pdf/mesh/circular_4_3_edge_skeleton.pdf\
  build/$(MODE)/demo/pdf/mesh/circular_4_3_forman_edge_skeleton.pdf\
  build/$(MODE)/demo/pdf/mesh/circular_17_10_edge_skeleton.pdf\
  build/$(MODE)/demo/pdf/mesh/circular_17_10_forman_edge_skeleton.pdf\
  build/$(MODE)/demo/pdf/mesh/pentagon_edge_skeleton.pdf\
  build/$(MODE)/demo/pdf/mesh/pentagon_forman_edge_skeleton.pdf\
  build/$(MODE)/demo/pdf/mesh/brick_2d_1_forman_edge_skeleton.pdf\
  build/$(MODE)/demo/pdf/mesh/brick_2d_10_forman_edge_skeleton.pdf\
  build/$(MODE)/demo/pdf/mesh/2d_10_grains_edge_skeleton.pdf\
  build/$(MODE)/demo/pdf/mesh/2d_10_grains_forman_edge_skeleton.pdf\

_demo_pdf_diffusion :=\
  build/$(MODE)/demo/pdf/diffusion/2d_transient_continuous_primal_strong_cochain_p0_brick_2d_2_forman_temperature.pdf\
  build/$(MODE)/demo/pdf/diffusion/2d_transient_continuous_primal_strong_cochain_p0_brick_2d_2_forman_flux.pdf\
  build/$(MODE)/demo/pdf/diffusion/2d_steady_state_continuous_primal_weak_cochain_p4_brick_2d_2_forman_temperature.pdf\
  build/$(MODE)/demo/pdf/diffusion/2d_transient_continuous_primal_strong_cochain_p2_brick_2d_5_forman_temperature.pdf\
  build/$(MODE)/demo/pdf/diffusion/2d_transient_continuous_primal_strong_cochain_p4_brick_2d_5_forman_temperature.pdf\
  build/$(MODE)/demo/pdf/diffusion/2d_steady_state_continuous_primal_strong_cochain_p4_brick_2d_5_forman_temperature.pdf\
  build/$(MODE)/demo/pdf/diffusion/2d_transient_continuous_primal_strong_cochain_p4_brick_2d_10_forman_temperature.pdf\
  build/$(MODE)/demo/pdf/diffusion/2d_transient_continuous_primal_strong_cochain_p4_brick_2d_10_forman_flux.pdf\
  build/$(MODE)/demo/pdf/diffusion/2d_steady_state_continuous_primal_strong_cochain_p7_2d_10_grains_forman_temperature.pdf\
  build/$(MODE)/demo/pdf/diffusion/2d_steady_state_continuous_primal_weak_cochain_p7_2d_10_grains_forman_temperature.pdf\
  build/$(MODE)/demo/pdf/diffusion/2d_transient_continuous_primal_strong_cochain_p5_square_8_temperature.pdf\
  build/$(MODE)/demo/pdf/diffusion/2d_steady_state_discrete_primal_weak_p4_brick_2d_2_forman_temperature.pdf\
  build/$(MODE)/demo/pdf/diffusion/2d_steady_state_discrete_mixed_weak_p4_brick_2d_2_forman_temperature.pdf\
  build/$(MODE)/demo/pdf/diffusion/2d_steady_state_discrete_primal_weak_p9_circular_4_3_forman_temperature.pdf\
  build/$(MODE)/demo/pdf/diffusion/2d_steady_state_discrete_primal_weak_p9_circular_17_10_forman_temperature.pdf\

_demo_pdf :=\
  build/$(MODE)/demo/pdf/fill.pdf $(_demo_pdf_mesh) $(_demo_pdf_diffusion)\

.PHONY: demo_pdf
demo_pdf: bin $(_demo_pdf)\
  | build/$(MODE)/demo/pdf

build/$(MODE)/demo/pdf: | build/$(MODE)/demo
	mkdir -p $@

build/$(MODE)/demo/pdf/fill.pdf:\
  build/$(MODE)/bin/pdf_fill | build/$(MODE)/demo/pdf
	$< 100 $@

build/$(MODE)/demo/pdf/mesh: | build/$(MODE)/demo/pdf
	mkdir -p $@

build/$(MODE)/demo/pdf/mesh/circular_4_3_edge_skeleton.pdf:\
  build/$(MODE)/bin/pdf_mesh_2d_colored_edge_skeleton$(.EXE)\
  build/$(MODE)/demo/mesh/mesh_circular_4_3.txt\
  | build/$(MODE)/demo/pdf/mesh
	$< --raw $(word 2, $^) $@

build/$(MODE)/demo/pdf/mesh/circular_4_3_forman_edge_skeleton.pdf:\
  build/$(MODE)/bin/pdf_mesh_2d_colored_edge_skeleton$(.EXE)\
  build/$(MODE)/demo/mesh/mesh_circular_4_3_forman.txt\
  | build/$(MODE)/demo/pdf/mesh
	$< --raw $(word 2, $^) $@

build/$(MODE)/demo/pdf/mesh/circular_17_10_edge_skeleton.pdf:\
  build/$(MODE)/bin/pdf_mesh_2d_colored_edge_skeleton$(.EXE)\
  build/$(MODE)/demo/mesh/mesh_circular_17_10.txt\
  | build/$(MODE)/demo/pdf/mesh
	$< --raw $(word 2, $^) $@

build/$(MODE)/demo/pdf/mesh/circular_17_10_forman_edge_skeleton.pdf:\
  build/$(MODE)/bin/pdf_mesh_2d_colored_edge_skeleton$(.EXE)\
  build/$(MODE)/demo/mesh/mesh_circular_17_10_forman.txt\
  | build/$(MODE)/demo/pdf/mesh
	$< --raw $(word 2, $^) $@

build/$(MODE)/demo/pdf/mesh/pentagon_edge_skeleton.pdf:\
  build/$(MODE)/bin/pdf_mesh_2d_colored_edge_skeleton$(.EXE)\
  data/mesh/mesh_pentagon.txt\
  | build/$(MODE)/demo/pdf/mesh
	$< --raw $(word 2, $^) $@

build/$(MODE)/demo/pdf/mesh/pentagon_forman_edge_skeleton.pdf:\
  build/$(MODE)/bin/pdf_mesh_2d_colored_edge_skeleton$(.EXE)\
  build/$(MODE)/demo/mesh/mesh_pentagon_forman.txt\
  | build/$(MODE)/demo/pdf/mesh
	$< --raw $(word 2, $^) $@

build/$(MODE)/demo/pdf/mesh/brick_2d_1_forman_edge_skeleton.pdf:\
  build/$(MODE)/bin/pdf_mesh_2d_colored_edge_skeleton$(.EXE)\
  build/$(MODE)/demo/mesh/mesh_brick_2d_1_forman.txt\
  | build/$(MODE)/demo/pdf/mesh
	$< --raw $(word 2, $^) $@

build/$(MODE)/demo/pdf/mesh/brick_2d_10_forman_edge_skeleton.pdf:\
  build/$(MODE)/bin/pdf_mesh_2d_colored_edge_skeleton$(.EXE)\
  build/$(MODE)/demo/mesh/mesh_brick_2d_10_forman.txt\
  | build/$(MODE)/demo/pdf/mesh
	$< --raw $(word 2, $^) $@

build/$(MODE)/demo/pdf/mesh/2d_10_grains_edge_skeleton.pdf:\
  build/$(MODE)/bin/pdf_mesh_2d_colored_edge_skeleton$(.EXE)\
  data/mesh/mesh_2d_10_grains.tess\
  | build/$(MODE)/demo/pdf/mesh
	$< --tess $(word 2, $^) $@

build/$(MODE)/demo/pdf/mesh/2d_10_grains_forman_edge_skeleton.pdf:\
  build/$(MODE)/bin/pdf_mesh_2d_colored_edge_skeleton$(.EXE)\
  build/$(MODE)/demo/mesh/mesh_2d_10_grains_forman.txt\
  | build/$(MODE)/demo/pdf/mesh
	$< --raw $(word 2, $^) $@

build/$(MODE)/demo/pdf/diffusion: | build/$(MODE)/demo/pdf
	mkdir -p $@

build/$(MODE)/demo/pdf/diffusion/2d_transient_continuous_primal_strong_cochain_p0_brick_2d_2_forman_temperature.pdf:\
  build/$(MODE)/bin/pdf_mesh_2d_colored_zero_cochain_sequence$(.EXE)\
  build/$(MODE)/demo/mesh/mesh_brick_2d_2_forman.txt\
  build/$(MODE)/demo/diffusion/2d_transient_continuous_primal_strong_cochain_p0_brick_2d_2_forman_temperature.txt\
  | build/$(MODE)/demo/pdf/diffusion
	$< --raw $(word 2, $^) 20 --raw $(word 3, $^) $@

build/$(MODE)/demo/pdf/diffusion/2d_transient_continuous_primal_strong_cochain_p0_brick_2d_2_forman_flux.pdf:\
  build/$(MODE)/bin/pdf_mesh_2d_colored_one_cochain_sequence$(.EXE)\
  build/$(MODE)/demo/mesh/mesh_brick_2d_2_forman.txt\
  build/$(MODE)/demo/diffusion/2d_transient_continuous_primal_strong_cochain_p0_brick_2d_2_forman_flux.txt\
  | build/$(MODE)/demo/pdf/diffusion
	$< --raw $(word 2, $^) 20 --raw $(word 3, $^) $@

build/$(MODE)/demo/pdf/diffusion/2d_steady_state_continuous_primal_weak_cochain_p4_brick_2d_2_forman_temperature.pdf:\
  build/$(MODE)/bin/pdf_mesh_2d_colored_zero_cochain_sequence$(.EXE)\
  build/$(MODE)/demo/mesh/mesh_brick_2d_2_forman.txt\
  build/$(MODE)/demo/diffusion/2d_steady_state_continuous_primal_weak_cochain_p4_brick_2d_2_forman_temperature.txt\
  | build/$(MODE)/demo/pdf/diffusion
	$< --raw $(word 2, $^) 0 --raw $(word 3, $^) $@

build/$(MODE)/demo/pdf/diffusion/2d_transient_continuous_primal_strong_cochain_p2_brick_2d_5_forman_temperature.pdf:\
  build/$(MODE)/bin/pdf_mesh_2d_colored_zero_cochain_sequence$(.EXE)\
  build/$(MODE)/demo/mesh/mesh_brick_2d_5_forman.txt\
  build/$(MODE)/demo/diffusion/2d_transient_continuous_primal_strong_cochain_p2_brick_2d_5_forman_temperature.txt\
  | build/$(MODE)/demo/pdf/diffusion
	$< --raw $(word 2, $^) 1000 --raw $(word 3, $^) $@

build/$(MODE)/demo/pdf/diffusion/2d_transient_continuous_primal_strong_cochain_p4_brick_2d_5_forman_temperature.pdf:\
  build/$(MODE)/bin/pdf_mesh_2d_colored_zero_cochain_sequence$(.EXE)\
  build/$(MODE)/demo/mesh/mesh_brick_2d_5_forman.txt\
  build/$(MODE)/demo/diffusion/2d_transient_continuous_primal_strong_cochain_p4_brick_2d_5_forman_temperature.txt\
  | build/$(MODE)/demo/pdf/diffusion
	$< --raw $(word 2, $^) 10000 --raw $(word 3, $^) $@

build/$(MODE)/demo/pdf/diffusion/2d_steady_state_continuous_primal_strong_cochain_p4_brick_2d_5_forman_temperature.pdf:\
  build/$(MODE)/bin/pdf_mesh_2d_colored_zero_cochain_sequence$(.EXE)\
  build/$(MODE)/demo/mesh/mesh_brick_2d_5_forman.txt\
  build/$(MODE)/demo/diffusion/2d_steady_state_continuous_primal_strong_cochain_p4_brick_2d_5_forman_temperature.txt\
  | build/$(MODE)/demo/pdf/diffusion
	$< --raw $(word 2, $^) 0 --raw $(word 3, $^) $@

build/$(MODE)/demo/pdf/diffusion/2d_transient_continuous_primal_strong_cochain_p4_brick_2d_10_forman_temperature.pdf:\
  build/$(MODE)/bin/pdf_mesh_2d_colored_zero_cochain_sequence$(.EXE)\
  build/$(MODE)/demo/mesh/mesh_brick_2d_10_forman.txt\
  build/$(MODE)/demo/diffusion/2d_transient_continuous_primal_strong_cochain_p4_brick_2d_10_forman_temperature.txt\
  | build/$(MODE)/demo/pdf/diffusion
	$< --raw $(word 2, $^) 4000 --raw $(word 3, $^) $@

build/$(MODE)/demo/pdf/diffusion/2d_transient_continuous_primal_strong_cochain_p4_brick_2d_10_forman_flux.pdf:\
  build/$(MODE)/bin/pdf_mesh_2d_colored_one_cochain_sequence$(.EXE)\
  build/$(MODE)/demo/mesh/mesh_brick_2d_10_forman.txt\
  build/$(MODE)/demo/diffusion/2d_transient_continuous_primal_strong_cochain_p4_brick_2d_10_forman_flux.txt\
  | build/$(MODE)/demo/pdf/diffusion
	$< --raw $(word 2, $^) 4000 --raw $(word 3, $^) $@

build/$(MODE)/demo/pdf/diffusion/2d_steady_state_continuous_primal_strong_cochain_p7_2d_10_grains_forman_temperature.pdf:\
  build/$(MODE)/bin/pdf_mesh_2d_colored_zero_cochain_sequence$(.EXE)\
  build/$(MODE)/demo/mesh/mesh_2d_10_grains_forman.txt\
  build/$(MODE)/demo/diffusion/2d_steady_state_continuous_primal_strong_cochain_p7_2d_10_grains_forman_temperature.txt\
  | build/$(MODE)/demo/pdf/diffusion
	$< --raw $(word 2, $^) 0 --raw $(word 3, $^) $@

build/$(MODE)/demo/pdf/diffusion/2d_steady_state_continuous_primal_weak_cochain_p7_2d_10_grains_forman_temperature.pdf:\
  build/$(MODE)/bin/pdf_mesh_2d_colored_zero_cochain_sequence$(.EXE)\
  build/$(MODE)/demo/mesh/mesh_2d_10_grains_forman.txt\
  build/$(MODE)/demo/diffusion/2d_steady_state_continuous_primal_weak_cochain_p7_2d_10_grains_forman_temperature.txt\
  | build/$(MODE)/demo/pdf/diffusion
	$< --raw $(word 2, $^) 0 --raw $(word 3, $^) $@

build/$(MODE)/demo/pdf/diffusion/2d_transient_continuous_primal_strong_cochain_p5_square_8_temperature.pdf:\
  build/$(MODE)/bin/pdf_mesh_2d_colored_zero_cochain_sequence$(.EXE)\
  build/$(MODE)/demo/mesh/mesh_square_8.txt\
  build/$(MODE)/demo/diffusion/2d_transient_continuous_primal_strong_cochain_p5_square_8_temperature.txt\
  | build/$(MODE)/demo/pdf/diffusion
	$< --raw $(word 2, $^) 4000 --raw $(word 3, $^) $@

build/$(MODE)/demo/pdf/diffusion/2d_steady_state_discrete_primal_weak_p4_brick_2d_2_forman_temperature.pdf:\
  build/$(MODE)/bin/pdf_mesh_2d_colored_zero_cochain_sequence$(.EXE)\
  build/$(MODE)/demo/mesh/mesh_brick_2d_2_forman.txt\
  build/$(MODE)/demo/diffusion/2d_steady_state_discrete_primal_weak_p4_brick_2d_2_forman_temperature.txt\
  | build/$(MODE)/demo/pdf/diffusion
	$< --raw $(word 2, $^) 0 --raw $(word 3, $^) $@

build/$(MODE)/demo/pdf/diffusion/2d_steady_state_discrete_mixed_weak_p4_brick_2d_2_forman_temperature.pdf:\
  build/$(MODE)/bin/pdf_mesh_2d_colored_zero_cochain_sequence$(.EXE)\
  build/$(MODE)/demo/mesh/mesh_brick_2d_2_forman.txt\
  build/$(MODE)/demo/diffusion/2d_steady_state_discrete_mixed_weak_p4_brick_2d_2_forman_temperature.txt\
  | build/$(MODE)/demo/pdf/diffusion
	$< --raw $(word 2, $^) 0 --raw $(word 3, $^) $@

build/$(MODE)/demo/pdf/diffusion/2d_steady_state_discrete_primal_weak_p9_circular_4_3_forman_temperature.pdf:\
  build/$(MODE)/bin/pdf_mesh_2d_colored_zero_cochain_sequence$(.EXE)\
  build/$(MODE)/demo/mesh/mesh_circular_4_3_forman.txt\
  build/$(MODE)/demo/diffusion/2d_steady_state_discrete_primal_weak_p9_circular_4_3_forman_temperature.txt\
  | build/$(MODE)/demo/pdf/diffusion
	$< --raw $(word 2, $^) 0 --raw $(word 3, $^) $@

build/$(MODE)/demo/pdf/diffusion/2d_steady_state_discrete_primal_weak_p9_circular_17_10_forman_temperature.pdf:\
  build/$(MODE)/bin/pdf_mesh_2d_colored_zero_cochain_sequence$(.EXE)\
  build/$(MODE)/demo/mesh/mesh_circular_17_10_forman.txt\
  build/$(MODE)/demo/diffusion/2d_steady_state_discrete_primal_weak_p9_circular_17_10_forman_temperature.txt\
  | build/$(MODE)/demo/pdf/diffusion
	$< --raw $(word 2, $^) 0 --raw $(word 3, $^) $@

.PHONY: demo_pdf_clean
demo_pdf_clean:
	-$(RM) $(_demo_pdf)
	-$(RM) -r build/$(MODE)/demo/pdf
