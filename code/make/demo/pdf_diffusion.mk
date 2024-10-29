build/$(MODE)/demo/pdf/diffusion: | build/$(MODE)/demo/pdf
	mkdir -p $@

_demo_pdf_diffusion_steady_state_continuous_2d_d00_p03 :=\
  build/$(MODE)/demo/pdf/diffusion/steady_state_continuous_2d_d00_p03_primal_strong_cochain_brick_2d_2_forman_potential.pdf\
  build/$(MODE)/demo/pdf/diffusion/steady_state_continuous_2d_d00_p03_primal_strong_cochain_brick_2d_2_forman_flow.pdf\
  build/$(MODE)/demo/pdf/diffusion/steady_state_continuous_2d_d00_p03_primal_weak_cochain_brick_2d_2_forman_potential.pdf\
  build/$(MODE)/demo/pdf/diffusion/steady_state_continuous_2d_d00_p03_primal_weak_cochain_brick_2d_2_forman_flow.pdf\
  build/$(MODE)/demo/pdf/diffusion/steady_state_continuous_2d_d00_p03_mixed_weak_cochain_brick_2d_2_forman_potential.pdf\
  build/$(MODE)/demo/pdf/diffusion/steady_state_continuous_2d_d00_p03_mixed_weak_cochain_brick_2d_2_forman_flow.pdf\

build/$(MODE)/demo/pdf/diffusion/steady_state_continuous_2d_d00_p03_primal_strong_cochain_brick_2d_2_forman_potential.pdf:\
  build/$(MODE)/bin/pdf_mesh_2d_colored_zero_cochain_sequence$(.EXE)\
  build/$(MODE)/demo/mesh/brick_2d_2_forman.txt\
  build/$(MODE)/demo/diffusion/steady_state_continuous_2d_d00_p03_primal_strong_cochain_brick_2d_2_forman_potential.txt\
  | build/$(MODE)/demo/pdf/diffusion
	$<\
  --raw $(word 2, $^)\
  0\
  --raw $(word 3, $^)\
  $@

build/$(MODE)/demo/pdf/diffusion/steady_state_continuous_2d_d00_p03_primal_strong_cochain_brick_2d_2_forman_flow.pdf:\
  build/$(MODE)/bin/pdf_mesh_2d_colored_one_cochain_sequence$(.EXE)\
  build/$(MODE)/demo/mesh/brick_2d_2_forman.txt\
  build/$(MODE)/demo/diffusion/steady_state_continuous_2d_d00_p03_primal_strong_cochain_brick_2d_2_forman_flow.txt\
  | build/$(MODE)/demo/pdf/diffusion
	$<\
  --raw $(word 2, $^)\
  0\
  --raw $(word 3, $^)\
  $@

build/$(MODE)/demo/pdf/diffusion/steady_state_continuous_2d_d00_p03_primal_weak_cochain_brick_2d_2_forman_potential.pdf:\
  build/$(MODE)/bin/pdf_mesh_2d_colored_zero_cochain_sequence$(.EXE)\
  build/$(MODE)/demo/mesh/brick_2d_2_forman.txt\
  build/$(MODE)/demo/diffusion/steady_state_continuous_2d_d00_p03_primal_weak_cochain_brick_2d_2_forman_potential.txt\
  | build/$(MODE)/demo/pdf/diffusion
	$<\
  --raw $(word 2, $^)\
  0\
  --raw $(word 3, $^)\
  $@

build/$(MODE)/demo/pdf/diffusion/steady_state_continuous_2d_d00_p03_primal_weak_cochain_brick_2d_2_forman_flow.pdf:\
  build/$(MODE)/bin/pdf_mesh_2d_colored_one_cochain_sequence$(.EXE)\
  build/$(MODE)/demo/mesh/brick_2d_2_forman.txt\
  build/$(MODE)/demo/diffusion/steady_state_continuous_2d_d00_p03_primal_weak_cochain_brick_2d_2_forman_flow.txt\
  | build/$(MODE)/demo/pdf/diffusion
	$<\
  --raw $(word 2, $^)\
  0\
  --raw $(word 3, $^)\
  $@

build/$(MODE)/demo/pdf/diffusion/steady_state_continuous_2d_d00_p03_mixed_weak_cochain_brick_2d_2_forman_potential.pdf:\
  build/$(MODE)/bin/pdf_mesh_2d_colored_zero_cochain_sequence$(.EXE)\
  build/$(MODE)/demo/mesh/brick_2d_2_forman.txt\
  build/$(MODE)/demo/diffusion/steady_state_continuous_2d_d00_p03_mixed_weak_cochain_brick_2d_2_forman_potential.txt\
  | build/$(MODE)/demo/pdf/diffusion
	$<\
  --raw $(word 2, $^)\
  0\
  --raw $(word 3, $^)\
  $@

build/$(MODE)/demo/pdf/diffusion/steady_state_continuous_2d_d00_p03_mixed_weak_cochain_brick_2d_2_forman_flow.pdf:\
  build/$(MODE)/bin/pdf_mesh_2d_colored_one_cochain_sequence$(.EXE)\
  build/$(MODE)/demo/mesh/brick_2d_2_forman.txt\
  build/$(MODE)/demo/diffusion/steady_state_continuous_2d_d00_p03_mixed_weak_cochain_brick_2d_2_forman_solution.txt\
  | build/$(MODE)/demo/pdf/diffusion
	$<\
  --raw $(word 2, $^)\
  0\
  --steady-state-mixed-weak-solution-flow-raw $(word 3, $^)\
  $@

_demo_pdf_diffusion_rest :=\
  build/$(MODE)/demo/pdf/diffusion/transient_continuous_2d_d00_p02_primal_strong_cochain_brick_2d_2_forman_temperature.pdf\
  build/$(MODE)/demo/pdf/diffusion/transient_continuous_2d_d00_p02_primal_strong_cochain_brick_2d_2_forman_flux.pdf\
  build/$(MODE)/demo/pdf/diffusion/steady_state_continuous_2d_d00_p02_primal_weak_cochain_brick_2d_2_forman_temperature.pdf\
  build/$(MODE)/demo/pdf/diffusion/transient_continuous_2d_d00_p00_primal_strong_cochain_brick_2d_5_forman_temperature.pdf\
  build/$(MODE)/demo/pdf/diffusion/transient_continuous_2d_d00_p01_primal_strong_cochain_brick_2d_5_forman_temperature.pdf\
  build/$(MODE)/demo/pdf/diffusion/steady_state_continuous_2d_d00_p01_primal_strong_cochain_brick_2d_5_forman_temperature.pdf\
  build/$(MODE)/demo/pdf/diffusion/transient_continuous_2d_d00_p01_primal_strong_cochain_brick_2d_10_forman_temperature.pdf\
  build/$(MODE)/demo/pdf/diffusion/transient_continuous_2d_d00_p01_primal_strong_cochain_brick_2d_10_forman_flux.pdf\
  build/$(MODE)/demo/pdf/diffusion/steady_state_continuous_2d_d02_p00_primal_strong_cochain_2d_10_grains_forman_temperature.pdf\
  build/$(MODE)/demo/pdf/diffusion/steady_state_continuous_2d_d02_p00_primal_weak_cochain_2d_10_grains_forman_temperature.pdf\
  build/$(MODE)/demo/pdf/diffusion/transient_continuous_2d_d01_p00_primal_strong_cochain_square_8_temperature.pdf\
  build/$(MODE)/demo/pdf/diffusion/steady_state_discrete_2d_d00_p01_primal_weak_brick_2d_2_forman_temperature.pdf\
  build/$(MODE)/demo/pdf/diffusion/steady_state_discrete_2d_d00_p01_primal_weak_brick_2d_2_forman_flow.pdf\
  build/$(MODE)/demo/pdf/diffusion/steady_state_discrete_2d_d00_p01_mixed_weak_brick_2d_2_forman_temperature.pdf\
  build/$(MODE)/demo/pdf/diffusion/steady_state_discrete_2d_d03_p00_primal_weak_circular_4_3_forman_temperature.pdf\
  build/$(MODE)/demo/pdf/diffusion/steady_state_discrete_2d_d03_p00_mixed_weak_circular_4_3_forman_temperature.pdf\
  build/$(MODE)/demo/pdf/diffusion/steady_state_discrete_2d_d03_p00_primal_weak_circular_17_10_forman_temperature.pdf\
  build/$(MODE)/demo/pdf/diffusion/steady_state_discrete_2d_d03_p00_mixed_weak_circular_17_10_forman_temperature.pdf\
  build/$(MODE)/demo/pdf/diffusion/steady_state_continuous_2d_d00_p03_brick_2d_2_forman_primal_weak_cochain_potential.pdf\
  build/$(MODE)/demo/pdf/diffusion/steady_state_continuous_2d_d00_p03_brick_2d_2_forman_mixed_weak_cochain_potential.pdf\
  build/$(MODE)/demo/pdf/diffusion/steady_state_continuous_2d_d00_p04_brick_2d_2_forman_primal_weak_cochain_potential.pdf\
  build/$(MODE)/demo/pdf/diffusion/steady_state_continuous_2d_d00_p04_brick_2d_2_forman_mixed_weak_cochain_potential.pdf\

build/$(MODE)/demo/pdf/diffusion/transient_continuous_2d_d00_p02_primal_strong_cochain_brick_2d_2_forman_temperature.pdf:\
  build/$(MODE)/bin/pdf_mesh_2d_colored_zero_cochain_sequence$(.EXE)\
  build/$(MODE)/demo/mesh/brick_2d_2_forman.txt\
  build/$(MODE)/demo/diffusion/transient_continuous_2d_d00_p02_primal_strong_cochain_brick_2d_2_forman_temperature.txt\
  | build/$(MODE)/demo/pdf/diffusion
	$< --raw $(word 2, $^) 20 --raw $(word 3, $^) $@

build/$(MODE)/demo/pdf/diffusion/transient_continuous_2d_d00_p02_primal_strong_cochain_brick_2d_2_forman_flux.pdf:\
  build/$(MODE)/bin/pdf_mesh_2d_colored_one_cochain_sequence$(.EXE)\
  build/$(MODE)/demo/mesh/brick_2d_2_forman.txt\
  build/$(MODE)/demo/diffusion/transient_continuous_2d_d00_p02_primal_strong_cochain_brick_2d_2_forman_flux.txt\
  | build/$(MODE)/demo/pdf/diffusion
	$< --raw $(word 2, $^) 20 --raw $(word 3, $^) $@

build/$(MODE)/demo/pdf/diffusion/steady_state_continuous_2d_d00_p02_primal_weak_cochain_brick_2d_2_forman_temperature.pdf:\
  build/$(MODE)/bin/pdf_mesh_2d_colored_zero_cochain_sequence$(.EXE)\
  build/$(MODE)/demo/mesh/brick_2d_2_forman.txt\
  build/$(MODE)/demo/diffusion/steady_state_continuous_2d_d00_p02_primal_weak_cochain_brick_2d_2_forman_temperature.txt\
  | build/$(MODE)/demo/pdf/diffusion
	$< --raw $(word 2, $^) 0 --raw $(word 3, $^) $@

build/$(MODE)/demo/pdf/diffusion/transient_continuous_2d_d00_p00_primal_strong_cochain_brick_2d_5_forman_temperature.pdf:\
  build/$(MODE)/bin/pdf_mesh_2d_colored_zero_cochain_sequence$(.EXE)\
  build/$(MODE)/demo/mesh/brick_2d_5_forman.txt\
  build/$(MODE)/demo/diffusion/transient_continuous_2d_d00_p00_primal_strong_cochain_brick_2d_5_forman_temperature.txt\
  | build/$(MODE)/demo/pdf/diffusion
	$< --raw $(word 2, $^) 1000 --raw $(word 3, $^) $@

build/$(MODE)/demo/pdf/diffusion/transient_continuous_2d_d00_p01_primal_strong_cochain_brick_2d_5_forman_temperature.pdf:\
  build/$(MODE)/bin/pdf_mesh_2d_colored_zero_cochain_sequence$(.EXE)\
  build/$(MODE)/demo/mesh/brick_2d_5_forman.txt\
  build/$(MODE)/demo/diffusion/transient_continuous_2d_d00_p01_primal_strong_cochain_brick_2d_5_forman_temperature.txt\
  | build/$(MODE)/demo/pdf/diffusion
	$< --raw $(word 2, $^) 10000 --raw $(word 3, $^) $@

build/$(MODE)/demo/pdf/diffusion/steady_state_continuous_2d_d00_p01_primal_strong_cochain_brick_2d_5_forman_temperature.pdf:\
  build/$(MODE)/bin/pdf_mesh_2d_colored_zero_cochain_sequence$(.EXE)\
  build/$(MODE)/demo/mesh/brick_2d_5_forman.txt\
  build/$(MODE)/demo/diffusion/steady_state_continuous_2d_d00_p01_primal_strong_cochain_brick_2d_5_forman_temperature.txt\
  | build/$(MODE)/demo/pdf/diffusion
	$< --raw $(word 2, $^) 0 --raw $(word 3, $^) $@

build/$(MODE)/demo/pdf/diffusion/transient_continuous_2d_d00_p01_primal_strong_cochain_brick_2d_10_forman_temperature.pdf:\
  build/$(MODE)/bin/pdf_mesh_2d_colored_zero_cochain_sequence$(.EXE)\
  build/$(MODE)/demo/mesh/brick_2d_10_forman.txt\
  build/$(MODE)/demo/diffusion/transient_continuous_2d_d00_p01_primal_strong_cochain_brick_2d_10_forman_temperature.txt\
  | build/$(MODE)/demo/pdf/diffusion
	$< --raw $(word 2, $^) 4000 --raw $(word 3, $^) $@

build/$(MODE)/demo/pdf/diffusion/transient_continuous_2d_d00_p01_primal_strong_cochain_brick_2d_10_forman_flux.pdf:\
  build/$(MODE)/bin/pdf_mesh_2d_colored_one_cochain_sequence$(.EXE)\
  build/$(MODE)/demo/mesh/brick_2d_10_forman.txt\
  build/$(MODE)/demo/diffusion/transient_continuous_2d_d00_p01_primal_strong_cochain_brick_2d_10_forman_flux.txt\
  | build/$(MODE)/demo/pdf/diffusion
	$< --raw $(word 2, $^) 4000 --raw $(word 3, $^) $@

build/$(MODE)/demo/pdf/diffusion/steady_state_continuous_2d_d02_p00_primal_strong_cochain_2d_10_grains_forman_temperature.pdf:\
  build/$(MODE)/bin/pdf_mesh_2d_colored_zero_cochain_sequence$(.EXE)\
  build/$(MODE)/demo/mesh/2d_10_grains_forman.txt\
  build/$(MODE)/demo/diffusion/steady_state_continuous_2d_d02_p00_primal_strong_cochain_2d_10_grains_forman_temperature.txt\
  | build/$(MODE)/demo/pdf/diffusion
	$< --raw $(word 2, $^) 0 --raw $(word 3, $^) $@

build/$(MODE)/demo/pdf/diffusion/steady_state_continuous_2d_d02_p00_primal_weak_cochain_2d_10_grains_forman_temperature.pdf:\
  build/$(MODE)/bin/pdf_mesh_2d_colored_zero_cochain_sequence$(.EXE)\
  build/$(MODE)/demo/mesh/2d_10_grains_forman.txt\
  build/$(MODE)/demo/diffusion/steady_state_continuous_2d_d02_p00_primal_weak_cochain_2d_10_grains_forman_temperature.txt\
  | build/$(MODE)/demo/pdf/diffusion
	$< --raw $(word 2, $^) 0 --raw $(word 3, $^) $@

build/$(MODE)/demo/pdf/diffusion/transient_continuous_2d_d01_p00_primal_strong_cochain_square_8_temperature.pdf:\
  build/$(MODE)/bin/pdf_mesh_2d_colored_zero_cochain_sequence$(.EXE)\
  build/$(MODE)/demo/mesh/square_8.txt\
  build/$(MODE)/demo/diffusion/transient_continuous_2d_d01_p00_primal_strong_cochain_square_8_temperature.txt\
  | build/$(MODE)/demo/pdf/diffusion
	$< --raw $(word 2, $^) 4000 --raw $(word 3, $^) $@

build/$(MODE)/demo/pdf/diffusion/steady_state_discrete_2d_d00_p01_primal_weak_brick_2d_2_forman_temperature.pdf:\
  build/$(MODE)/bin/pdf_mesh_2d_colored_zero_cochain_sequence$(.EXE)\
  build/$(MODE)/demo/mesh/brick_2d_2_forman.txt\
  build/$(MODE)/demo/diffusion/steady_state_discrete_2d_d00_p01_primal_weak_brick_2d_2_forman_temperature.txt\
  | build/$(MODE)/demo/pdf/diffusion
	$< --raw $(word 2, $^) 0 --raw $(word 3, $^) $@

build/$(MODE)/demo/pdf/diffusion/steady_state_discrete_2d_d00_p01_primal_weak_brick_2d_2_forman_flow.pdf:\
  build/$(MODE)/bin/pdf_mesh_2d_colored_one_cochain_sequence$(.EXE)\
  build/$(MODE)/demo/mesh/brick_2d_2_forman.txt\
  build/$(MODE)/demo/diffusion/steady_state_discrete_2d_d00_p01_primal_weak_brick_2d_2_forman_flow.txt\
  | build/$(MODE)/demo/pdf/diffusion
	$<\
  --raw $(word 2, $^)\
  0\
  --raw $(word 3, $^)\
  $@

build/$(MODE)/demo/pdf/diffusion/steady_state_discrete_2d_d00_p01_mixed_weak_brick_2d_2_forman_temperature.pdf:\
  build/$(MODE)/bin/pdf_mesh_2d_colored_zero_cochain_sequence$(.EXE)\
  build/$(MODE)/demo/mesh/brick_2d_2_forman.txt\
  build/$(MODE)/demo/diffusion/steady_state_discrete_2d_d00_p01_mixed_weak_brick_2d_2_forman_temperature.txt\
  | build/$(MODE)/demo/pdf/diffusion
	$< --raw $(word 2, $^) 0 --raw $(word 3, $^) $@

build/$(MODE)/demo/pdf/diffusion/steady_state_discrete_2d_d03_p00_primal_weak_circular_4_3_forman_temperature.pdf:\
  build/$(MODE)/bin/pdf_mesh_2d_colored_zero_cochain_sequence$(.EXE)\
  build/$(MODE)/demo/mesh/circular_4_3_forman.txt\
  build/$(MODE)/demo/diffusion/steady_state_discrete_2d_d03_p00_primal_weak_circular_4_3_forman_temperature.txt\
  | build/$(MODE)/demo/pdf/diffusion
	$< --raw $(word 2, $^) 0 --raw $(word 3, $^) $@

build/$(MODE)/demo/pdf/diffusion/steady_state_discrete_2d_d03_p00_mixed_weak_circular_4_3_forman_temperature.pdf:\
  build/$(MODE)/bin/pdf_mesh_2d_colored_zero_cochain_sequence$(.EXE)\
  build/$(MODE)/demo/mesh/circular_4_3_forman.txt\
  build/$(MODE)/demo/diffusion/steady_state_discrete_2d_d03_p00_mixed_weak_circular_4_3_forman_temperature.txt\
  | build/$(MODE)/demo/pdf/diffusion
	$< --raw $(word 2, $^) 0 --raw $(word 3, $^) $@

build/$(MODE)/demo/pdf/diffusion/steady_state_discrete_2d_d03_p00_primal_weak_circular_17_10_forman_temperature.pdf:\
  build/$(MODE)/bin/pdf_mesh_2d_colored_zero_cochain_sequence$(.EXE)\
  build/$(MODE)/demo/mesh/circular_17_10_forman.txt\
  build/$(MODE)/demo/diffusion/steady_state_discrete_2d_d03_p00_primal_weak_circular_17_10_forman_temperature.txt\
  | build/$(MODE)/demo/pdf/diffusion
	$< --raw $(word 2, $^) 0 --raw $(word 3, $^) $@

build/$(MODE)/demo/pdf/diffusion/steady_state_discrete_2d_d03_p00_mixed_weak_circular_17_10_forman_temperature.pdf:\
  build/$(MODE)/bin/pdf_mesh_2d_colored_zero_cochain_sequence$(.EXE)\
  build/$(MODE)/demo/mesh/circular_17_10_forman.txt\
  build/$(MODE)/demo/diffusion/steady_state_discrete_2d_d03_p00_mixed_weak_circular_17_10_forman_temperature.txt\
  | build/$(MODE)/demo/pdf/diffusion
	$< --raw $(word 2, $^) 0 --raw $(word 3, $^) $@

build/$(MODE)/demo/pdf/diffusion/steady_state_continuous_2d_d00_p03_brick_2d_2_forman_primal_weak_cochain_potential.pdf:\
  build/$(MODE)/bin/pdf_mesh_2d_colored_zero_cochain_sequence$(.EXE)\
  build/$(MODE)/demo/mesh/brick_2d_2_forman.txt\
  build/$(MODE)/demo/diffusion/steady_state_continuous_2d_d00_p03_primal_weak_cochain_brick_2d_2_forman_potential.txt\
  | build/$(MODE)/demo/pdf/diffusion
	$< --raw $(word 2, $^) 0 --raw $(word 3, $^) $@

build/$(MODE)/demo/pdf/diffusion/steady_state_continuous_2d_d00_p03_brick_2d_2_forman_mixed_weak_cochain_potential.pdf:\
  build/$(MODE)/bin/pdf_mesh_2d_colored_zero_cochain_sequence$(.EXE)\
  build/$(MODE)/demo/mesh/brick_2d_2_forman.txt\
  build/$(MODE)/demo/diffusion/steady_state_continuous_2d_d00_p03_mixed_weak_cochain_brick_2d_2_forman_potential.txt\
  | build/$(MODE)/demo/pdf/diffusion
	$< --raw $(word 2, $^) 0 --raw $(word 3, $^) $@

build/$(MODE)/demo/pdf/diffusion/steady_state_continuous_2d_d00_p04_brick_2d_2_forman_primal_weak_cochain_potential.pdf:\
  build/$(MODE)/bin/pdf_mesh_2d_colored_zero_cochain_sequence$(.EXE)\
  build/$(MODE)/demo/mesh/brick_2d_2_forman.txt\
  build/$(MODE)/demo/diffusion/steady_state_continuous_2d_d00_p04_brick_2d_2_forman_primal_weak_cochain_potential.txt\
  | build/$(MODE)/demo/pdf/diffusion
	$< --raw $(word 2, $^) 0 --raw $(word 3, $^) $@

build/$(MODE)/demo/pdf/diffusion/steady_state_continuous_2d_d00_p04_brick_2d_2_forman_mixed_weak_cochain_potential.pdf:\
  build/$(MODE)/bin/pdf_mesh_2d_colored_zero_cochain_sequence$(.EXE)\
  build/$(MODE)/demo/mesh/brick_2d_2_forman.txt\
  build/$(MODE)/demo/diffusion/steady_state_continuous_2d_d00_p04_brick_2d_2_forman_mixed_weak_cochain_potential.txt\
  | build/$(MODE)/demo/pdf/diffusion
	$< --raw $(word 2, $^) 0 --raw $(word 3, $^) $@

.PHONY: demo_pdf_diffusion demo_pdf_diffusion_clean demo_pdf_diffusion_distclean

_demo_pdf_diffusion :=\
  $(_demo_pdf_diffusion_steady_state_continuous_2d_d00_p03)\
  $(_demo_pdf_diffusion_rest)

demo_pdf_diffusion: $(_demo_pdf_diffusion)

demo_pdf_diffusion_clean:
	-$(RM) $(_demo_pdf_diffusion)

demo_pdf_diffusion_distclean:
	-$(RM) -r build/$(MODE)/demo/pdf/diffusion
