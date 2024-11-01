build/$(MODE)/demo/pdf/diffusion: | build/$(MODE)/demo/pdf
	mkdir -p $@

# include code/make/demo/pdf_diffusion_steady_state_continuous_2d_d00_p00.mk
include code/make/demo/pdf_diffusion_steady_state_continuous_2d_d00_p01.mk
include code/make/demo/pdf_diffusion_steady_state_continuous_2d_d00_p02.mk
include code/make/demo/pdf_diffusion_steady_state_continuous_2d_d00_p03.mk
include code/make/demo/pdf_diffusion_steady_state_continuous_2d_d00_p04.mk
include code/make/demo/pdf_diffusion_steady_state_continuous_2d_d01_p00.mk
include code/make/demo/pdf_diffusion_steady_state_continuous_2d_d02_p00.mk
include code/make/demo/pdf_diffusion_steady_state_continuous_2d_d02_p01.mk
include code/make/demo/pdf_diffusion_steady_state_continuous_2d_d03_p00.mk
include code/make/demo/pdf_diffusion_steady_state_continuous_2d_d03_p01.mk

_demo_pdf_diffusion_transient :=\
  build/$(MODE)/demo/pdf/diffusion/transient_continuous_2d_d00_p02_primal_strong_cochain_brick_2d_2_forman_temperature.pdf\
  build/$(MODE)/demo/pdf/diffusion/transient_continuous_2d_d00_p02_primal_strong_cochain_brick_2d_2_forman_flux.pdf\
  build/$(MODE)/demo/pdf/diffusion/transient_continuous_2d_d00_p00_primal_strong_cochain_brick_2d_5_forman_temperature.pdf\
  build/$(MODE)/demo/pdf/diffusion/transient_continuous_2d_d00_p01_primal_strong_cochain_brick_2d_5_forman_temperature.pdf\
  build/$(MODE)/demo/pdf/diffusion/transient_continuous_2d_d00_p01_primal_strong_cochain_brick_2d_10_forman_temperature.pdf\
  build/$(MODE)/demo/pdf/diffusion/transient_continuous_2d_d00_p01_primal_strong_cochain_brick_2d_10_forman_flux.pdf\
  build/$(MODE)/demo/pdf/diffusion/transient_continuous_2d_d01_p00_primal_strong_cochain_square_8_temperature.pdf\

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

build/$(MODE)/demo/pdf/diffusion/transient_continuous_2d_d01_p00_primal_strong_cochain_square_8_temperature.pdf:\
  build/$(MODE)/bin/pdf_mesh_2d_colored_zero_cochain_sequence$(.EXE)\
  build/$(MODE)/demo/mesh/square_8.txt\
  build/$(MODE)/demo/diffusion/transient_continuous_2d_d01_p00_primal_strong_cochain_square_8_temperature.txt\
  | build/$(MODE)/demo/pdf/diffusion
	$< --raw $(word 2, $^) 4000 --raw $(word 3, $^) $@

.PHONY: demo_pdf_diffusion demo_pdf_diffusion_clean demo_pdf_diffusion_distclean

_demo_pdf_diffusion :=\
  $(_demo_pdf_diffusion_steady_state_continuous_2d_d00_p00)\
  $(_demo_pdf_diffusion_steady_state_continuous_2d_d00_p01)\
  $(_demo_pdf_diffusion_steady_state_continuous_2d_d00_p02)\
  $(_demo_pdf_diffusion_steady_state_continuous_2d_d00_p03)\
  $(_demo_pdf_diffusion_steady_state_continuous_2d_d00_p04)\
  $(_demo_pdf_diffusion_steady_state_continuous_2d_d01_p00)\
  $(_demo_pdf_diffusion_steady_state_continuous_2d_d02_p00)\
  $(_demo_pdf_diffusion_steady_state_continuous_2d_d02_p01)\
  $(_demo_pdf_diffusion_steady_state_continuous_2d_d03_p00)\
  $(_demo_pdf_diffusion_steady_state_continuous_2d_d03_p01)\
  $(_demo_pdf_diffusion_transient)

demo_pdf_diffusion: $(_demo_pdf_diffusion)

demo_pdf_diffusion_clean:
	-$(RM) $(_demo_pdf_diffusion)

demo_pdf_diffusion_distclean:
	-$(RM) -r build/$(MODE)/demo/pdf/diffusion
