build/$(MODE)/demo/pdf/diffusion: | build/$(MODE)/demo/pdf
	mkdir -p $@

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
  build/$(MODE)/demo/pdf/diffusion/2d_steady_state_discrete_mixed_weak_p9_circular_4_3_forman_temperature.pdf\
  build/$(MODE)/demo/pdf/diffusion/2d_steady_state_discrete_primal_weak_p9_circular_17_10_forman_temperature.pdf\
  build/$(MODE)/demo/pdf/diffusion/2d_steady_state_discrete_mixed_weak_p9_circular_17_10_forman_temperature.pdf\
  build/$(MODE)/demo/pdf/diffusion/steady_state_continuous_2d_p00_brick_2d_2_forman_primal_weak_cochain_potential.pdf\
  build/$(MODE)/demo/pdf/diffusion/steady_state_continuous_2d_p00_brick_2d_2_forman_mixed_weak_cochain_potential.pdf\
  build/$(MODE)/demo/pdf/diffusion/steady_state_continuous_2d_p01_brick_2d_2_forman_primal_weak_cochain_potential.pdf\
  build/$(MODE)/demo/pdf/diffusion/steady_state_continuous_2d_p01_brick_2d_2_forman_mixed_weak_cochain_potential.pdf\

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

build/$(MODE)/demo/pdf/diffusion/2d_steady_state_discrete_mixed_weak_p9_circular_4_3_forman_temperature.pdf:\
  build/$(MODE)/bin/pdf_mesh_2d_colored_zero_cochain_sequence$(.EXE)\
  build/$(MODE)/demo/mesh/mesh_circular_4_3_forman.txt\
  build/$(MODE)/demo/diffusion/2d_steady_state_discrete_mixed_weak_p9_circular_4_3_forman_temperature.txt\
  | build/$(MODE)/demo/pdf/diffusion
	$< --raw $(word 2, $^) 0 --raw $(word 3, $^) $@

build/$(MODE)/demo/pdf/diffusion/2d_steady_state_discrete_primal_weak_p9_circular_17_10_forman_temperature.pdf:\
  build/$(MODE)/bin/pdf_mesh_2d_colored_zero_cochain_sequence$(.EXE)\
  build/$(MODE)/demo/mesh/mesh_circular_17_10_forman.txt\
  build/$(MODE)/demo/diffusion/2d_steady_state_discrete_primal_weak_p9_circular_17_10_forman_temperature.txt\
  | build/$(MODE)/demo/pdf/diffusion
	$< --raw $(word 2, $^) 0 --raw $(word 3, $^) $@

build/$(MODE)/demo/pdf/diffusion/2d_steady_state_discrete_mixed_weak_p9_circular_17_10_forman_temperature.pdf:\
  build/$(MODE)/bin/pdf_mesh_2d_colored_zero_cochain_sequence$(.EXE)\
  build/$(MODE)/demo/mesh/mesh_circular_17_10_forman.txt\
  build/$(MODE)/demo/diffusion/2d_steady_state_discrete_mixed_weak_p9_circular_17_10_forman_temperature.txt\
  | build/$(MODE)/demo/pdf/diffusion
	$< --raw $(word 2, $^) 0 --raw $(word 3, $^) $@

build/$(MODE)/demo/pdf/diffusion/steady_state_continuous_2d_p00_brick_2d_2_forman_primal_weak_cochain_potential.pdf:\
  build/$(MODE)/bin/pdf_mesh_2d_colored_zero_cochain_sequence$(.EXE)\
  build/$(MODE)/demo/mesh/mesh_brick_2d_2_forman.txt\
  build/$(MODE)/demo/diffusion/steady_state_continuous_2d_p00_brick_2d_2_forman_primal_weak_cochain_potential.txt\
  | build/$(MODE)/demo/pdf/diffusion
	$< --raw $(word 2, $^) 0 --raw $(word 3, $^) $@

build/$(MODE)/demo/pdf/diffusion/steady_state_continuous_2d_p00_brick_2d_2_forman_mixed_weak_cochain_potential.pdf:\
  build/$(MODE)/bin/pdf_mesh_2d_colored_zero_cochain_sequence$(.EXE)\
  build/$(MODE)/demo/mesh/mesh_brick_2d_2_forman.txt\
  build/$(MODE)/demo/diffusion/steady_state_continuous_2d_p00_brick_2d_2_forman_mixed_weak_cochain_potential.txt\
  | build/$(MODE)/demo/pdf/diffusion
	$< --raw $(word 2, $^) 0 --raw $(word 3, $^) $@

build/$(MODE)/demo/pdf/diffusion/steady_state_continuous_2d_p01_brick_2d_2_forman_primal_weak_cochain_potential.pdf:\
  build/$(MODE)/bin/pdf_mesh_2d_colored_zero_cochain_sequence$(.EXE)\
  build/$(MODE)/demo/mesh/mesh_brick_2d_2_forman.txt\
  build/$(MODE)/demo/diffusion/steady_state_continuous_2d_p01_brick_2d_2_forman_primal_weak_cochain_potential.txt\
  | build/$(MODE)/demo/pdf/diffusion
	$< --raw $(word 2, $^) 0 --raw $(word 3, $^) $@

build/$(MODE)/demo/pdf/diffusion/steady_state_continuous_2d_p01_brick_2d_2_forman_mixed_weak_cochain_potential.pdf:\
  build/$(MODE)/bin/pdf_mesh_2d_colored_zero_cochain_sequence$(.EXE)\
  build/$(MODE)/demo/mesh/mesh_brick_2d_2_forman.txt\
  build/$(MODE)/demo/diffusion/steady_state_continuous_2d_p01_brick_2d_2_forman_mixed_weak_cochain_potential.txt\
  | build/$(MODE)/demo/pdf/diffusion
	$< --raw $(word 2, $^) 0 --raw $(word 3, $^) $@

.PHONY: demo_pdf_diffusion demo_pdf_diffusion_clean demo_pdf_diffusion_distclean

demo_pdf_diffusion: $(_demo_pdf_diffusion)

demo_pdf_diffusion_clean:
	-$(RM) $(_demo_pdf_diffusion)

demo_pdf_diffusion_distclean:
	-$(RM) -r build/$(MODE)/demo/pdf/diffusion
