build/$(MODE)/txt/diffusion: | build/$(MODE)/txt
	mkdir -p $@

include code/make/txt/diffusion_steady_state_continuous_2d_d00_p00.mk
include code/make/txt/diffusion_steady_state_continuous_2d_d00_p01.mk
include code/make/txt/diffusion_steady_state_continuous_2d_d00_p02.mk
include code/make/txt/diffusion_steady_state_continuous_2d_d00_p03.mk
include code/make/txt/diffusion_steady_state_continuous_2d_d00_p04.mk
include code/make/txt/diffusion_steady_state_continuous_2d_d00_p05.mk
include code/make/txt/diffusion_steady_state_continuous_2d_d01_p00.mk
include code/make/txt/diffusion_steady_state_continuous_2d_d02_p00.mk
include code/make/txt/diffusion_steady_state_continuous_2d_d02_p01.mk
include code/make/txt/diffusion_steady_state_continuous_2d_d03_p00.mk
include code/make/txt/diffusion_steady_state_continuous_2d_d03_p01.mk
include code/make/txt/diffusion_steady_state_continuous_3d_d00_p00.mk

_txt_diffusion_steady_state :=\
  $(_txt_diffusion_steady_state_continuous_2d_d00_p00)\
  $(_txt_diffusion_steady_state_continuous_2d_d00_p01)\
  $(_txt_diffusion_steady_state_continuous_2d_d00_p02)\
  $(_txt_diffusion_steady_state_continuous_2d_d00_p03)\
  $(_txt_diffusion_steady_state_continuous_2d_d00_p04)\
  $(_txt_diffusion_steady_state_continuous_2d_d00_p05)\
  $(_txt_diffusion_steady_state_continuous_2d_d01_p00)\
  $(_txt_diffusion_steady_state_continuous_2d_d02_p00)\
  $(_txt_diffusion_steady_state_continuous_2d_d02_p01)\
  $(_txt_diffusion_steady_state_continuous_2d_d03_p00)\
  $(_txt_diffusion_steady_state_continuous_2d_d03_p01)\
  $(_txt_diffusion_steady_state_continuous_3d_d00_p00)\

.PHONY: txt_diffusion_steady_state
txt_diffusion_steady_state: $(_txt_diffusion_steady_state)

include code/make/txt/diffusion_transient_continuous_2d_d00_p00.mk
include code/make/txt/diffusion_transient_continuous_2d_d00_p01.mk
include code/make/txt/diffusion_transient_continuous_2d_d00_p04.mk

_txt_diffusion_transient_continuous_2d :=\
  build/$(MODE)/txt/diffusion/transient_continuous_2d_d00_p02_primal_strong_cochain_brick_2d_2_forman_potential.txt\
  build/$(MODE)/txt/diffusion/transient_continuous_2d_d00_p02_primal_strong_cochain_brick_2d_2_forman_dual_flow.txt\
  build/$(MODE)/txt/diffusion/transient_continuous_2d_d00_p05_primal_strong_cochain_brick_2d_2_forman_potential.txt\
  build/$(MODE)/txt/diffusion/transient_continuous_2d_d00_p00_primal_strong_cochain_brick_2d_2_forman_potential.txt\
  build/$(MODE)/txt/diffusion/transient_continuous_2d_d00_p01_primal_strong_cochain_brick_2d_2_forman_potential.txt\
  build/$(MODE)/txt/diffusion/transient_continuous_2d_d00_p01_primal_weak_cochain_brick_2d_2_forman_potential.txt\
  build/$(MODE)/txt/diffusion/transient_continuous_2d_d00_p01_primal_weak_to_steady_state_cochain_brick_2d_2_forman_potential.txt\
  build/$(MODE)/txt/diffusion/transient_continuous_2d_d00_p00_primal_strong_cochain_brick_2d_5_forman_potential.txt\
  build/$(MODE)/txt/diffusion/transient_continuous_2d_d00_p01_primal_strong_cochain_brick_2d_5_forman_potential.txt\
  build/$(MODE)/txt/diffusion/transient_continuous_2d_d00_p01_primal_strong_cochain_brick_2d_10_forman_potential.txt\
  build/$(MODE)/txt/diffusion/transient_continuous_2d_d00_p01_primal_strong_cochain_brick_2d_10_forman_dual_flow.txt\
  build/$(MODE)/txt/diffusion/transient_continuous_2d_d02_p00_primal_strong_cochain_2d_10_grains_forman_potential.txt\
  build/$(MODE)/txt/diffusion/transient_continuous_2d_d02_p00_primal_strong_cochain_2d_10_grains_forman_dual_flow.txt\
  build/$(MODE)/txt/diffusion/transient_continuous_2d_d02_p00_primal_weak_cochain_2d_10_grains_forman_potential.txt\
  build/$(MODE)/txt/diffusion/transient_continuous_2d_d02_p00_primal_weak_cochain_2d_10_grains_forman_dual_flow.txt\
  build/$(MODE)/txt/diffusion/transient_continuous_2d_d02_p00_primal_weak_to_steady_state_cochain_2d_10_grains_forman_potential.txt\
  build/$(MODE)/txt/diffusion/transient_continuous_2d_d02_p01_primal_weak_cochain_2d_10_grains_forman_potential.txt\
  build/$(MODE)/txt/diffusion/transient_continuous_2d_d01_p00_primal_strong_cochain_square_8_potential.txt\

build/$(MODE)/txt/diffusion/transient_continuous_2d_d00_p02_primal_strong_cochain_brick_2d_2_forman_potential.txt:\
  build/$(MODE)/bin/diffusion_transient_continuous_primal_strong_cochain_solve_trapezoidal$(.EXE)\
  build/$(MODE)/txt/mesh/brick_2d_2_forman.txt\
  build/$(MODE)/txt/mesh/brick_2d_2_forman_cbd.txt\
  build/$(MODE)/txt/mesh/brick_2d_2_forman_cbd_star.txt\
  build/$(MODE)/obj/src/diffusion_transient_continuous_2d_d00_p02$(.OBJ)\
  | build/$(MODE)/txt/diffusion build/$(MODE)/lib/libshared$(.DLL)
	$< --raw $(word 2, $^) $(word 3, $^) $(word 4, $^) $(word 2, $|)\
	  diffusion_transient_continuous_2d_d00_p02 0.05 100 > $@

build/$(MODE)/txt/diffusion/transient_continuous_2d_d00_p02_primal_strong_cochain_brick_2d_2_forman_dual_flow.txt:\
  build/$(MODE)/bin/diffusion_transient_discrete_dual_flow_from_potential$(.EXE)\
  build/$(MODE)/txt/mesh/brick_2d_2_forman.txt\
  build/$(MODE)/txt/diffusion/transient_continuous_2d_d00_p02_primal_strong_cochain_brick_2d_2_forman_potential.txt\
  build/$(MODE)/obj/src/diffusion_transient_continuous_2d_d00_p02$(.OBJ)\
  | build/$(MODE)/txt/diffusion build/$(MODE)/lib/libshared$(.DLL)
	$< --raw $(word 2, $^) "-" $(word 2, $|)\
	  diffusion_transient_continuous_2d_d00_p02 100 --raw $(word 3, $^) --raw > $@

build/$(MODE)/txt/diffusion/transient_continuous_2d_d00_p01_primal_strong_cochain_brick_2d_2_forman_potential.txt:\
  build/$(MODE)/bin/diffusion_transient_continuous_primal_strong_cochain_solve_trapezoidal_to_steady_state$(.EXE)\
  build/$(MODE)/txt/mesh/brick_2d_2_forman.txt\
  build/$(MODE)/txt/mesh/brick_2d_2_forman_cbd.txt\
  build/$(MODE)/txt/mesh/brick_2d_2_forman_cbd_star.txt\
  build/$(MODE)/obj/src/diffusion_transient_continuous_2d_d00_p01$(.OBJ)\
  | build/$(MODE)/txt/diffusion build/$(MODE)/lib/libshared$(.DLL)
	$< --raw $(word 2, $^) $(word 3, $^) $(word 4, $^) $(word 2, $|)\
	  diffusion_transient_continuous_2d_d00_p01 0.001 > $@

build/$(MODE)/txt/diffusion/transient_continuous_2d_d00_p01_primal_weak_to_steady_state_cochain_brick_2d_2_forman_potential.txt:\
  build/$(MODE)/bin/diffusion_transient_continuous_primal_weak_cochain_solve_trapezoidal_to_steady_state$(.EXE)\
  build/$(MODE)/txt/mesh/brick_2d_2_forman.txt\
  build/$(MODE)/txt/mesh/brick_2d_2_forman_vol.txt\
  build/$(MODE)/txt/mesh/brick_2d_2_forman_inner.txt\
  build/$(MODE)/obj/src/diffusion_transient_continuous_2d_d00_p01$(.OBJ)\
  | build/$(MODE)/txt/diffusion build/$(MODE)/lib/libshared$(.DLL)
	$< --raw $(word 2, $^) --raw $(word 3, $^) --raw $(word 4, $^)\
	  $(word 2, $|) diffusion_transient_continuous_2d_d00_p01 0.001 0.01 > $@

build/$(MODE)/txt/diffusion/transient_continuous_2d_d00_p01_primal_weak_cochain_brick_2d_2_forman_potential.txt:\
  build/$(MODE)/bin/diffusion_transient_continuous_primal_weak_cochain_solve_trapezoidal$(.EXE)\
  build/$(MODE)/txt/mesh/brick_2d_2_forman.txt\
  build/$(MODE)/txt/mesh/brick_2d_2_forman_vol.txt\
  build/$(MODE)/txt/mesh/brick_2d_2_forman_inner.txt\
  build/$(MODE)/obj/src/diffusion_transient_continuous_2d_d00_p01$(.OBJ)\
  | build/$(MODE)/txt/diffusion build/$(MODE)/lib/libshared$(.DLL)
	$< --raw $(word 2, $^) --raw $(word 3, $^) --raw $(word 4, $^)\
	  $(word 2, $|) diffusion_transient_continuous_2d_d00_p01 0.001 1000 --raw > $@

build/$(MODE)/txt/diffusion/transient_continuous_2d_d00_p05_primal_strong_cochain_brick_2d_2_forman_potential.txt:\
  build/$(MODE)/bin/diffusion_transient_continuous_primal_strong_cochain_solve_trapezoidal$(.EXE)\
  build/$(MODE)/txt/mesh/brick_2d_2_forman.txt\
  build/$(MODE)/txt/mesh/brick_2d_2_forman_cbd.txt\
  build/$(MODE)/txt/mesh/brick_2d_2_forman_cbd_star.txt\
  build/$(MODE)/obj/src/diffusion_transient_continuous_2d_d00_p05$(.OBJ)\
  | build/$(MODE)/txt/diffusion build/$(MODE)/lib/libshared$(.DLL)
	$< --raw $(word 2, $^) $(word 3, $^) $(word 4, $^) $(word 2, $|)\
	  diffusion_transient_continuous_2d_d00_p05 0.05 20 > $@

build/$(MODE)/txt/diffusion/transient_continuous_2d_d00_p00_primal_strong_cochain_brick_2d_2_forman_potential.txt:\
  build/$(MODE)/bin/diffusion_transient_continuous_primal_strong_cochain_solve_trapezoidal$(.EXE)\
  build/$(MODE)/txt/mesh/brick_2d_2_forman.txt\
  build/$(MODE)/txt/mesh/brick_2d_2_forman_cbd.txt\
  build/$(MODE)/txt/mesh/brick_2d_2_forman_cbd_star.txt\
  build/$(MODE)/obj/src/diffusion_transient_continuous_2d_d00_p00$(.OBJ)\
  | build/$(MODE)/txt/diffusion build/$(MODE)/lib/libshared$(.DLL)
	$< --raw $(word 2, $^) $(word 3, $^) $(word 4, $^) $(word 2, $|)\
  	  diffusion_transient_continuous_2d_d00_p00 0.001 100 > $@

build/$(MODE)/txt/diffusion/transient_continuous_2d_d00_p00_primal_strong_cochain_brick_2d_5_forman_potential.txt:\
  build/$(MODE)/bin/diffusion_transient_continuous_primal_strong_cochain_solve_trapezoidal$(.EXE)\
  build/$(MODE)/txt/mesh/brick_2d_5_forman.txt\
  build/$(MODE)/txt/mesh/brick_2d_5_forman_cbd.txt\
  build/$(MODE)/txt/mesh/brick_2d_5_forman_cbd_star.txt\
  build/$(MODE)/obj/src/diffusion_transient_continuous_2d_d00_p00$(.OBJ)\
  | build/$(MODE)/txt/diffusion build/$(MODE)/lib/libshared$(.DLL)
	$< --raw $(word 2, $^) $(word 3, $^) $(word 4, $^) $(word 2, $|)\
	  diffusion_transient_continuous_2d_d00_p00 0.0001 10000 > $@

build/$(MODE)/txt/diffusion/transient_continuous_2d_d00_p01_primal_strong_cochain_brick_2d_5_forman_potential.txt:\
  build/$(MODE)/bin/diffusion_transient_continuous_primal_strong_cochain_solve_trapezoidal$(.EXE)\
  build/$(MODE)/txt/mesh/brick_2d_5_forman.txt\
  build/$(MODE)/txt/mesh/brick_2d_5_forman_cbd.txt\
  build/$(MODE)/txt/mesh/brick_2d_5_forman_cbd_star.txt\
  build/$(MODE)/obj/src/diffusion_transient_continuous_2d_d00_p01$(.OBJ)\
  | build/$(MODE)/txt/diffusion build/$(MODE)/lib/libshared$(.DLL)
	$< --raw $(word 2, $^) $(word 3, $^) $(word 4, $^) $(word 2, $|)\
	  diffusion_transient_continuous_2d_d00_p01 0.0001 10000 > $@

build/$(MODE)/txt/diffusion/transient_continuous_2d_d00_p01_primal_strong_cochain_brick_2d_10_forman_potential.txt:\
  build/$(MODE)/bin/diffusion_transient_continuous_primal_strong_cochain_solve_trapezoidal$(.EXE)\
  build/$(MODE)/txt/mesh/brick_2d_10_forman.txt\
  build/$(MODE)/txt/mesh/brick_2d_10_forman_cbd.txt\
  build/$(MODE)/txt/mesh/brick_2d_10_forman_cbd_star.txt\
  build/$(MODE)/obj/src/diffusion_transient_continuous_2d_d00_p01$(.OBJ)\
  | build/$(MODE)/txt/diffusion build/$(MODE)/lib/libshared$(.DLL)
	$< --raw $(word 2, $^) $(word 3, $^) $(word 4, $^) $(word 2, $|)\
	  diffusion_transient_continuous_2d_d00_p01 0.0001 4000 > $@

build/$(MODE)/txt/diffusion/transient_continuous_2d_d00_p01_primal_strong_cochain_brick_2d_10_forman_dual_flow.txt:\
  build/$(MODE)/bin/diffusion_transient_discrete_dual_flow_from_potential$(.EXE)\
  build/$(MODE)/txt/mesh/brick_2d_10_forman.txt\
  build/$(MODE)/txt/diffusion/transient_continuous_2d_d00_p01_primal_strong_cochain_brick_2d_10_forman_potential.txt\
  build/$(MODE)/obj/src/diffusion_steady_state_continuous_2d_d00_p01$(.OBJ)\
  | build/$(MODE)/txt/diffusion build/$(MODE)/lib/libshared$(.DLL)
	$< --raw $(word 2, $^) "-" $(word 2, $|)\
	  diffusion_transient_continuous_2d_d00_p01 4000 --raw $(word 3, $^) --raw > $@

build/$(MODE)/txt/diffusion/transient_continuous_2d_d02_p00_primal_strong_cochain_2d_10_grains_forman_potential.txt:\
  build/$(MODE)/bin/diffusion_transient_continuous_primal_strong_cochain_solve_trapezoidal$(.EXE)\
  build/$(MODE)/txt/mesh/2d_10_grains_forman.txt\
  build/$(MODE)/txt/mesh/2d_10_grains_forman_cbd.txt\
  build/$(MODE)/txt/mesh/2d_10_grains_forman_cbd_star.txt\
  build/$(MODE)/obj/src/diffusion_transient_continuous_2d_d02_p00$(.OBJ)\
  | build/$(MODE)/txt/diffusion build/$(MODE)/lib/libshared$(.DLL)
	$< --raw $(word 2, $^) $(word 3, $^) $(word 4, $^) $(word 2, $|)\
	  diffusion_transient_continuous_2d_d02_p00 0.0001 1000 > $@

build/$(MODE)/txt/diffusion/transient_continuous_2d_d02_p00_primal_strong_cochain_2d_10_grains_forman_dual_flow.txt:\
  build/$(MODE)/bin/diffusion_transient_discrete_dual_flow_from_potential$(.EXE)\
  build/$(MODE)/txt/mesh/2d_10_grains_forman.txt\
  build/$(MODE)/txt/diffusion/transient_continuous_2d_d02_p00_primal_strong_cochain_2d_10_grains_forman_potential.txt\
  build/$(MODE)/obj/src/diffusion_transient_continuous_2d_d02_p00$(.OBJ)\
  | build/$(MODE)/txt/diffusion build/$(MODE)/lib/libshared$(.DLL)
	$< --raw $(word 2, $^) "-" $(word 2, $|)\
	  diffusion_transient_continuous_2d_d02_p00 1000 --raw $(word 3, $^) --raw > $@

build/$(MODE)/txt/diffusion/transient_continuous_2d_d02_p00_primal_weak_cochain_2d_10_grains_forman_potential.txt:\
  build/$(MODE)/bin/diffusion_transient_continuous_primal_weak_cochain_solve_trapezoidal$(.EXE)\
  build/$(MODE)/txt/mesh/2d_10_grains_forman.txt\
  build/$(MODE)/txt/mesh/2d_10_grains_forman_vol.txt\
  build/$(MODE)/txt/mesh/2d_10_grains_forman_inner.txt\
  build/$(MODE)/obj/src/diffusion_transient_continuous_2d_d02_p00$(.OBJ)\
  | build/$(MODE)/txt/diffusion build/$(MODE)/lib/libshared$(.DLL)
	$< --raw $(word 2, $^) --raw $(word 3, $^) --raw $(word 4, $^)\
	  $(word 2, $|) diffusion_transient_continuous_2d_d02_p00 0.01 2000 --raw > $@

build/$(MODE)/txt/diffusion/transient_continuous_2d_d02_p00_primal_weak_cochain_2d_10_grains_forman_dual_flow.txt:\
  build/$(MODE)/bin/diffusion_transient_discrete_dual_flow_from_potential$(.EXE)\
  build/$(MODE)/txt/mesh/2d_10_grains_forman.txt\
  build/$(MODE)/txt/diffusion/transient_continuous_2d_d02_p00_primal_weak_cochain_2d_10_grains_forman_potential.txt\
  build/$(MODE)/obj/src/diffusion_transient_continuous_2d_d02_p00$(.OBJ)\
  | build/$(MODE)/txt/diffusion build/$(MODE)/lib/libshared$(.DLL)
	$< --raw $(word 2, $^) "-" $(word 2, $|)\
	  diffusion_transient_continuous_2d_d02_p00 2000 --raw $(word 3, $^) --raw > $@

build/$(MODE)/txt/diffusion/transient_continuous_2d_d02_p00_primal_weak_to_steady_state_cochain_2d_10_grains_forman_potential.txt:\
  build/$(MODE)/bin/diffusion_transient_continuous_primal_weak_cochain_solve_trapezoidal_to_steady_state$(.EXE)\
  build/$(MODE)/txt/mesh/2d_10_grains_forman.txt\
  build/$(MODE)/txt/mesh/2d_10_grains_forman_vol.txt\
  build/$(MODE)/txt/mesh/2d_10_grains_forman_inner.txt\
  build/$(MODE)/obj/src/diffusion_transient_continuous_2d_d02_p00$(.OBJ)\
  | build/$(MODE)/txt/diffusion build/$(MODE)/lib/libshared$(.DLL)
	$< --raw $(word 2, $^) --raw $(word 3, $^) --raw $(word 4, $^)\
	  $(word 2, $|) diffusion_transient_continuous_2d_d02_p00 0.001 0.0001 > $@

build/$(MODE)/txt/diffusion/transient_continuous_2d_d02_p01_primal_weak_cochain_2d_10_grains_forman_potential.txt:\
  build/$(MODE)/bin/diffusion_transient_continuous_primal_weak_cochain_solve_trapezoidal$(.EXE)\
  build/$(MODE)/txt/mesh/2d_10_grains_forman.txt\
  build/$(MODE)/txt/mesh/2d_10_grains_forman_vol.txt\
  build/$(MODE)/txt/mesh/2d_10_grains_forman_inner.txt\
  build/$(MODE)/obj/src/diffusion_transient_continuous_2d_d02_p01$(.OBJ)\
  | build/$(MODE)/txt/diffusion build/$(MODE)/lib/libshared$(.DLL)
	$< --raw $(word 2, $^) --raw $(word 3, $^) --raw $(word 4, $^)\
  	  $(word 2, $|) diffusion_transient_continuous_2d_d02_p01 0.01 2000 --raw > $@

build/$(MODE)/txt/diffusion/transient_continuous_2d_d01_p00_primal_strong_cochain_square_8_potential.txt:\
  build/$(MODE)/bin/diffusion_transient_continuous_primal_strong_cochain_solve_trapezoidal$(.EXE)\
  build/$(MODE)/txt/mesh/square_8.txt\
  build/$(MODE)/txt/mesh/square_8_cbd.txt\
  build/$(MODE)/txt/mesh/square_8_cbd_star.txt\
  build/$(MODE)/obj/src/diffusion_transient_continuous_2d_d01_p00$(.OBJ)\
  | build/$(MODE)/txt/diffusion build/$(MODE)/lib/libshared$(.DLL)
	$< --raw $(word 2, $^) $(word 3, $^) $(word 4, $^) $(word 2, $|)\
	  diffusion_transient_continuous_2d_d01_p00 0.001 4000 > $@

.PHONY: txt_diffusion_transient_continuous_2d
txt_diffusion_transient_continuous_2d: $(_txt_diffusion_transient_continuous_2d)

_txt_diffusion_transient_continuous_3d :=\
  build/$(MODE)/txt/diffusion/transient_continuous_3d_d00_p00_primal_strong_cochain_brick_3d_2_forman_potential.txt\

build/$(MODE)/txt/diffusion/transient_continuous_3d_d00_p00_primal_strong_cochain_brick_3d_2_forman_potential.txt:\
  build/$(MODE)/bin/diffusion_transient_continuous_primal_strong_cochain_solve_trapezoidal$(.EXE)\
  build/$(MODE)/txt/mesh/brick_3d_2_forman.txt\
  build/$(MODE)/txt/mesh/brick_3d_2_forman_cbd.txt\
  build/$(MODE)/txt/mesh/brick_3d_2_forman_cbd_star.txt\
  build/$(MODE)/obj/src/diffusion_transient_continuous_3d_d00_p00$(.OBJ)\
  | build/$(MODE)/txt/diffusion build/$(MODE)/lib/libshared$(.DLL)
	$< --raw $(word 2, $^) $(word 3, $^) $(word 4, $^) $(word 2, $|)\
	  diffusion_transient_continuous_3d_d00_p00 0.001 1000 > $@

.PHONY: txt_diffusion_transient_continuous_3d
txt_diffusion_transient_continuous_3d: $(_txt_diffusion_transient_continuous_3d)

_txt_diffusion_transient :=\
  $(_txt_diffusion_transient_continuous_2d_d00_p00)\
  $(_txt_diffusion_transient_continuous_2d_d00_p01)\
  $(_txt_diffusion_transient_continuous_2d_d00_p04)\
  build/$(MODE)/txt/diffusion/transient_continuous_2d_d00_p01_primal_strong_cochain_brick_2d_2_forman_potential.txt\
#   $(_txt_diffusion_transient_continuous_2d)\
#   $(_txt_diffusion_transient_continuous_3d)\

.PHONY: txt_diffusion_transient
txt_diffusion_transient: $(_txt_diffusion_transient)

_txt_diffusion := $(_txt_diffusion_steady_state) $(_txt_diffusion_transient)

.PHONY: txt_diffusion txt_diffusion_clean txt_diffusion_distclean

txt_diffusion: txt_diffusion_steady_state txt_diffusion_transient

txt_diffusion_clean:
	-$(RM) $(_txt_diffusion)

txt_diffusion_distclean:
	-$(RM) -r build/$(MODE)/txt/diffusion
