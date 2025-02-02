build/$(MODE)/pdf/diffusion: | build/$(MODE)/pdf
	mkdir -p $@

include code/make/pdf/diffusion_steady_state_continuous_2d_d00_p00.mk
include code/make/pdf/diffusion_steady_state_continuous_2d_d00_p01.mk
include code/make/pdf/diffusion_steady_state_continuous_2d_d00_p02.mk
include code/make/pdf/diffusion_steady_state_continuous_2d_d00_p03.mk
include code/make/pdf/diffusion_steady_state_continuous_2d_d00_p04.mk
include code/make/pdf/diffusion_steady_state_continuous_2d_d00_p05.mk
include code/make/pdf/diffusion_steady_state_continuous_2d_d01_p00.mk
include code/make/pdf/diffusion_steady_state_continuous_2d_d02_p00.mk
include code/make/pdf/diffusion_steady_state_continuous_2d_d02_p01.mk
include code/make/pdf/diffusion_steady_state_continuous_2d_d03_p00.mk
include code/make/pdf/diffusion_steady_state_continuous_2d_d03_p01.mk

_pdf_diffusion_steady_state :=\
  $(_pdf_diffusion_steady_state_continuous_2d_d00_p00)\
  $(_pdf_diffusion_steady_state_continuous_2d_d00_p01)\
  $(_pdf_diffusion_steady_state_continuous_2d_d00_p02)\
  $(_pdf_diffusion_steady_state_continuous_2d_d00_p03)\
  $(_pdf_diffusion_steady_state_continuous_2d_d00_p04)\
  $(_pdf_diffusion_steady_state_continuous_2d_d00_p05)\
  $(_pdf_diffusion_steady_state_continuous_2d_d01_p00)\
  $(_pdf_diffusion_steady_state_continuous_2d_d02_p00)\
  $(_pdf_diffusion_steady_state_continuous_2d_d02_p01)\
  $(_pdf_diffusion_steady_state_continuous_2d_d03_p00)\
  $(_pdf_diffusion_steady_state_continuous_2d_d03_p01)\

# _pdf_diffusion_transient :=\
#   build/$(MODE)/pdf/diffusion/transient_continuous_2d_d00_p02_primal_strong_cochain_brick_2d_2_forman_potential.pdf\
#   build/$(MODE)/pdf/diffusion/transient_continuous_2d_d00_p02_primal_strong_cochain_brick_2d_2_forman_dual_flow.pdf\
#   build/$(MODE)/pdf/diffusion/transient_continuous_2d_d00_p00_primal_strong_cochain_brick_2d_5_forman_potential.pdf\
#   build/$(MODE)/pdf/diffusion/transient_continuous_2d_d00_p01_primal_strong_cochain_brick_2d_5_forman_potential.pdf\
#   build/$(MODE)/pdf/diffusion/transient_continuous_2d_d00_p01_primal_strong_cochain_brick_2d_10_forman_potential.pdf\
#   build/$(MODE)/pdf/diffusion/transient_continuous_2d_d00_p01_primal_strong_cochain_brick_2d_10_forman_dual_flow.pdf\
#   build/$(MODE)/pdf/diffusion/transient_continuous_2d_d01_p00_primal_strong_cochain_square_8_potential.pdf\

# build/$(MODE)/pdf/diffusion/transient_continuous_2d_d00_p02_primal_strong_cochain_brick_2d_2_forman_potential.pdf:\
#   build/$(MODE)/bin/pdf_mesh_2d_colored_zero_cochain_sequence$(.EXE)\
#   build/$(MODE)/txt/mesh/brick_2d_2_forman.txt\
#   build/$(MODE)/txt/diffusion/transient_continuous_2d_d00_p02_primal_strong_cochain_brick_2d_2_forman_potential.txt\
#   | build/$(MODE)/pdf/diffusion
# 	$< --raw $(word 2, $^) 20 --raw $(word 3, $^) $@

# build/$(MODE)/pdf/diffusion/transient_continuous_2d_d00_p02_primal_strong_cochain_brick_2d_2_forman_dual_flow.pdf:\
#   build/$(MODE)/bin/pdf_mesh_2d_colored_one_cochain_sequence$(.EXE)\
#   build/$(MODE)/txt/mesh/brick_2d_2_forman.txt\
#   build/$(MODE)/txt/diffusion/transient_continuous_2d_d00_p02_primal_strong_cochain_brick_2d_2_forman_dual_flow.txt\
#   | build/$(MODE)/pdf/diffusion
# 	$< --raw $(word 2, $^) 20 --raw $(word 3, $^) $@

# build/$(MODE)/pdf/diffusion/transient_continuous_2d_d00_p00_primal_strong_cochain_brick_2d_5_forman_potential.pdf:\
#   build/$(MODE)/bin/pdf_mesh_2d_colored_zero_cochain_sequence$(.EXE)\
#   build/$(MODE)/txt/mesh/brick_2d_5_forman.txt\
#   build/$(MODE)/txt/diffusion/transient_continuous_2d_d00_p00_primal_strong_cochain_brick_2d_5_forman_potential.txt\
#   | build/$(MODE)/pdf/diffusion
# 	$< --raw $(word 2, $^) 1000 --raw $(word 3, $^) $@

# build/$(MODE)/pdf/diffusion/transient_continuous_2d_d00_p01_primal_strong_cochain_brick_2d_5_forman_potential.pdf:\
#   build/$(MODE)/bin/pdf_mesh_2d_colored_zero_cochain_sequence$(.EXE)\
#   build/$(MODE)/txt/mesh/brick_2d_5_forman.txt\
#   build/$(MODE)/txt/diffusion/transient_continuous_2d_d00_p01_primal_strong_cochain_brick_2d_5_forman_potential.txt\
#   | build/$(MODE)/pdf/diffusion
# 	$< --raw $(word 2, $^) 10000 --raw $(word 3, $^) $@

# build/$(MODE)/pdf/diffusion/transient_continuous_2d_d00_p01_primal_strong_cochain_brick_2d_10_forman_potential.pdf:\
#   build/$(MODE)/bin/pdf_mesh_2d_colored_zero_cochain_sequence$(.EXE)\
#   build/$(MODE)/txt/mesh/brick_2d_10_forman.txt\
#   build/$(MODE)/txt/diffusion/transient_continuous_2d_d00_p01_primal_strong_cochain_brick_2d_10_forman_potential.txt\
#   | build/$(MODE)/pdf/diffusion
# 	$< --raw $(word 2, $^) 4000 --raw $(word 3, $^) $@

# build/$(MODE)/pdf/diffusion/transient_continuous_2d_d00_p01_primal_strong_cochain_brick_2d_10_forman_dual_flow.pdf:\
#   build/$(MODE)/bin/pdf_mesh_2d_colored_one_cochain_sequence$(.EXE)\
#   build/$(MODE)/txt/mesh/brick_2d_10_forman.txt\
#   build/$(MODE)/txt/diffusion/transient_continuous_2d_d00_p01_primal_strong_cochain_brick_2d_10_forman_dual_flow.txt\
#   | build/$(MODE)/pdf/diffusion
# 	$< --raw $(word 2, $^) 4000 --raw $(word 3, $^) $@

# build/$(MODE)/pdf/diffusion/transient_continuous_2d_d01_p00_primal_strong_cochain_square_8_potential.pdf:\
#   build/$(MODE)/bin/pdf_mesh_2d_colored_zero_cochain_sequence$(.EXE)\
#   build/$(MODE)/txt/mesh/square_8.txt\
#   build/$(MODE)/txt/diffusion/transient_continuous_2d_d01_p00_primal_strong_cochain_square_8_potential.txt\
#   | build/$(MODE)/pdf/diffusion
# 	$< --raw $(word 2, $^) 4000 --raw $(word 3, $^) $@

include code/make/pdf/diffusion_transient_continuous_2d_d00_p00.mk
include code/make/pdf/diffusion_transient_continuous_2d_d00_p01.mk
include code/make/pdf/diffusion_transient_continuous_2d_d00_p04.mk

.PHONY: pdf_diffusion pdf_diffusion_clean pdf_diffusion_distclean

_pdf_diffusion :=\
  $(_pdf_diffusion_steady_state)\
  $(_pdf_diffusion_transient_continuous_2d_d00_p00)\
  $(_pdf_diffusion_transient_continuous_2d_d00_p01)\
  $(_pdf_diffusion_transient_continuous_2d_d00_p04)\
#   $(_pdf_diffusion_transient)\

pdf_diffusion: $(_pdf_diffusion)

pdf_diffusion_clean:
	-$(RM) $(_pdf_diffusion)

pdf_diffusion_distclean:
	-$(RM) -r build/$(MODE)/pdf/diffusion
