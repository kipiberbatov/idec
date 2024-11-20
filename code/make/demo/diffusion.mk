build/$(MODE)/demo/diffusion: | build/$(MODE)/demo
	mkdir -p $@

include code/make/demo/diffusion_steady_state_continuous_2d_d00_p00.mk
include code/make/demo/diffusion_steady_state_continuous_2d_d00_p01.mk
include code/make/demo/diffusion_steady_state_continuous_2d_d00_p02.mk
include code/make/demo/diffusion_steady_state_continuous_2d_d00_p03.mk
include code/make/demo/diffusion_steady_state_continuous_2d_d00_p04.mk
include code/make/demo/diffusion_steady_state_continuous_2d_d00_p05.mk
include code/make/demo/diffusion_steady_state_continuous_2d_d01_p00.mk
include code/make/demo/diffusion_steady_state_continuous_2d_d02_p00.mk
include code/make/demo/diffusion_steady_state_continuous_2d_d02_p01.mk
include code/make/demo/diffusion_steady_state_continuous_2d_d03_p00.mk
include code/make/demo/diffusion_steady_state_continuous_2d_d03_p01.mk
include code/make/demo/diffusion_steady_state_continuous_3d_d00_p00.mk

_demo_diffusion_steady_state :=\
  $(_demo_diffusion_steady_state_continuous_2d_d00_p00)\
  $(_demo_diffusion_steady_state_continuous_2d_d00_p01)\
  $(_demo_diffusion_steady_state_continuous_2d_d00_p02)\
  $(_demo_diffusion_steady_state_continuous_2d_d00_p03)\
  $(_demo_diffusion_steady_state_continuous_2d_d00_p04)\
  $(_demo_diffusion_steady_state_continuous_2d_d00_p05)\
  $(_demo_diffusion_steady_state_continuous_2d_d01_p00)\
  $(_demo_diffusion_steady_state_continuous_2d_d02_p00)\
  $(_demo_diffusion_steady_state_continuous_2d_d03_p00)\
  $(_demo_diffusion_steady_state_continuous_2d_d03_p01)\
  $(_demo_diffusion_steady_state_continuous_3d_d00_p00)\

include code/make/demo/diffusion_transient_continuous_2d_d00_p00.mk
include code/make/demo/diffusion_transient_continuous_2d_d00_p01.mk

_demo_diffusion_transient_continuous_2d :=\
  build/$(MODE)/demo/diffusion/transient_continuous_2d_d00_p02_primal_strong_cochain_brick_2d_2_forman_potential.txt\
  build/$(MODE)/demo/diffusion/transient_continuous_2d_d00_p02_primal_strong_cochain_brick_2d_2_forman_dual_flow.txt\
  build/$(MODE)/demo/diffusion/transient_continuous_2d_d00_p05_primal_strong_cochain_brick_2d_2_forman_potential.txt\
  build/$(MODE)/demo/diffusion/transient_continuous_2d_d00_p00_primal_strong_cochain_brick_2d_2_forman_potential.txt\
  build/$(MODE)/demo/diffusion/transient_continuous_2d_d00_p01_primal_strong_cochain_brick_2d_2_forman_potential.txt\
  build/$(MODE)/demo/diffusion/transient_continuous_2d_d00_p01_primal_weak_cochain_brick_2d_2_forman_potential.txt\
  build/$(MODE)/demo/diffusion/transient_continuous_2d_d00_p01_primal_weak_to_steady_state_cochain_brick_2d_2_forman_potential.txt\
  build/$(MODE)/demo/diffusion/transient_continuous_2d_d00_p00_primal_strong_cochain_brick_2d_5_forman_potential.txt\
  build/$(MODE)/demo/diffusion/transient_continuous_2d_d00_p01_primal_strong_cochain_brick_2d_5_forman_potential.txt\
  build/$(MODE)/demo/diffusion/transient_continuous_2d_d00_p01_primal_strong_cochain_brick_2d_10_forman_potential.txt\
  build/$(MODE)/demo/diffusion/transient_continuous_2d_d00_p01_primal_strong_cochain_brick_2d_10_forman_dual_flow.txt\
  build/$(MODE)/demo/diffusion/transient_continuous_2d_d02_p00_primal_strong_cochain_2d_10_grains_forman_potential.txt\
  build/$(MODE)/demo/diffusion/transient_continuous_2d_d02_p00_primal_strong_cochain_2d_10_grains_forman_dual_flow.txt\
  build/$(MODE)/demo/diffusion/transient_continuous_2d_d02_p00_primal_weak_cochain_2d_10_grains_forman_potential.txt\
  build/$(MODE)/demo/diffusion/transient_continuous_2d_d02_p00_primal_weak_cochain_2d_10_grains_forman_dual_flow.txt\
  build/$(MODE)/demo/diffusion/transient_continuous_2d_d02_p00_primal_weak_to_steady_state_cochain_2d_10_grains_forman_potential.txt\
  build/$(MODE)/demo/diffusion/transient_continuous_2d_d02_p01_primal_weak_cochain_2d_10_grains_forman_potential.txt\
  build/$(MODE)/demo/diffusion/transient_continuous_2d_d01_p00_primal_strong_cochain_square_8_potential.txt\

build/$(MODE)/demo/diffusion/transient_continuous_2d_d00_p02_primal_strong_cochain_brick_2d_2_forman_potential.txt:\
  build/$(MODE)/bin/diffusion_transient_continuous_primal_strong_cochain_solve_trapezoidal$(.EXE)\
  build/$(MODE)/demo/mesh/brick_2d_2_forman.txt\
  build/$(MODE)/demo/mesh/brick_2d_2_forman_cbd.txt\
  build/$(MODE)/demo/mesh/brick_2d_2_forman_cbd_star.txt\
  build/$(MODE)/obj/src/diffusion_transient_continuous_2d_d00_p02$(.OBJ)\
  | build/$(MODE)/demo/diffusion build/$(MODE)/lib/libshared$(.DLL)
	$< --raw $(word 2, $^) $(word 3, $^) $(word 4, $^) $(word 2, $|)\
	  diffusion_transient_continuous_2d_d00_p02 0.05 100 > $@

build/$(MODE)/demo/diffusion/transient_continuous_2d_d00_p02_primal_strong_cochain_brick_2d_2_forman_dual_flow.txt:\
  build/$(MODE)/bin/diffusion_transient_discrete_primal_dual_flow$(.EXE)\
  build/$(MODE)/demo/mesh/brick_2d_2_forman.txt\
  build/$(MODE)/demo/diffusion/transient_continuous_2d_d00_p02_primal_strong_cochain_brick_2d_2_forman_potential.txt\
  build/$(MODE)/obj/src/diffusion_transient_continuous_2d_d00_p02$(.OBJ)\
  | build/$(MODE)/demo/diffusion build/$(MODE)/lib/libshared$(.DLL)
	$< --raw $(word 2, $^) "-" $(word 2, $|)\
	  diffusion_transient_continuous_2d_d00_p02 100 --raw $(word 3, $^) --raw > $@

build/$(MODE)/demo/diffusion/transient_continuous_2d_d00_p01_primal_strong_cochain_brick_2d_2_forman_potential.txt:\
  build/$(MODE)/bin/diffusion_transient_continuous_primal_strong_cochain_solve_trapezoidal_to_steady_state$(.EXE)\
  build/$(MODE)/demo/mesh/brick_2d_2_forman.txt\
  build/$(MODE)/demo/mesh/brick_2d_2_forman_cbd.txt\
  build/$(MODE)/demo/mesh/brick_2d_2_forman_cbd_star.txt\
  build/$(MODE)/obj/src/diffusion_transient_continuous_2d_d00_p01$(.OBJ)\
  | build/$(MODE)/demo/diffusion build/$(MODE)/lib/libshared$(.DLL)
	$< --raw $(word 2, $^) $(word 3, $^) $(word 4, $^) $(word 2, $|)\
	  diffusion_transient_continuous_2d_d00_p01 0.001 > $@

build/$(MODE)/demo/diffusion/transient_continuous_2d_d00_p01_primal_weak_to_steady_state_cochain_brick_2d_2_forman_potential.txt:\
  build/$(MODE)/bin/diffusion_transient_continuous_primal_weak_cochain_solve_trapezoidal_to_steady_state$(.EXE)\
  build/$(MODE)/demo/mesh/brick_2d_2_forman.txt\
  build/$(MODE)/demo/mesh/brick_2d_2_forman_vol.txt\
  build/$(MODE)/demo/mesh/brick_2d_2_forman_inner.txt\
  build/$(MODE)/obj/src/diffusion_transient_continuous_2d_d00_p01$(.OBJ)\
  | build/$(MODE)/demo/diffusion build/$(MODE)/lib/libshared$(.DLL)
	$< --raw $(word 2, $^) --raw $(word 3, $^) --raw $(word 4, $^)\
	  $(word 2, $|) diffusion_transient_continuous_2d_d00_p01 0.001 0.01 > $@

build/$(MODE)/demo/diffusion/transient_continuous_2d_d00_p01_primal_weak_cochain_brick_2d_2_forman_potential.txt:\
  build/$(MODE)/bin/diffusion_transient_continuous_primal_weak_cochain_solve_trapezoidal$(.EXE)\
  build/$(MODE)/demo/mesh/brick_2d_2_forman.txt\
  build/$(MODE)/demo/mesh/brick_2d_2_forman_vol.txt\
  build/$(MODE)/demo/mesh/brick_2d_2_forman_inner.txt\
  build/$(MODE)/obj/src/diffusion_transient_continuous_2d_d00_p01$(.OBJ)\
  | build/$(MODE)/demo/diffusion build/$(MODE)/lib/libshared$(.DLL)
	$< --raw $(word 2, $^) --raw $(word 3, $^) --raw $(word 4, $^)\
	  $(word 2, $|) diffusion_transient_continuous_2d_d00_p01 0.001 1000 --raw > $@

build/$(MODE)/demo/diffusion/transient_continuous_2d_d00_p05_primal_strong_cochain_brick_2d_2_forman_potential.txt:\
  build/$(MODE)/bin/diffusion_transient_continuous_primal_strong_cochain_solve_trapezoidal$(.EXE)\
  build/$(MODE)/demo/mesh/brick_2d_2_forman.txt\
  build/$(MODE)/demo/mesh/brick_2d_2_forman_cbd.txt\
  build/$(MODE)/demo/mesh/brick_2d_2_forman_cbd_star.txt\
  build/$(MODE)/obj/src/diffusion_transient_continuous_2d_d00_p05$(.OBJ)\
  | build/$(MODE)/demo/diffusion build/$(MODE)/lib/libshared$(.DLL)
	$< --raw $(word 2, $^) $(word 3, $^) $(word 4, $^) $(word 2, $|)\
	  diffusion_transient_continuous_2d_d00_p05 0.05 20 > $@

build/$(MODE)/demo/diffusion/transient_continuous_2d_d00_p00_primal_strong_cochain_brick_2d_2_forman_potential.txt:\
  build/$(MODE)/bin/diffusion_transient_continuous_primal_strong_cochain_solve_trapezoidal$(.EXE)\
  build/$(MODE)/demo/mesh/brick_2d_2_forman.txt\
  build/$(MODE)/demo/mesh/brick_2d_2_forman_cbd.txt\
  build/$(MODE)/demo/mesh/brick_2d_2_forman_cbd_star.txt\
  build/$(MODE)/obj/src/diffusion_transient_continuous_2d_d00_p00$(.OBJ)\
  | build/$(MODE)/demo/diffusion build/$(MODE)/lib/libshared$(.DLL)
	$< --raw $(word 2, $^) $(word 3, $^) $(word 4, $^) $(word 2, $|)\
  	  diffusion_transient_continuous_2d_d00_p00 0.001 100 > $@

build/$(MODE)/demo/diffusion/transient_continuous_2d_d00_p00_primal_strong_cochain_brick_2d_5_forman_potential.txt:\
  build/$(MODE)/bin/diffusion_transient_continuous_primal_strong_cochain_solve_trapezoidal$(.EXE)\
  build/$(MODE)/demo/mesh/brick_2d_5_forman.txt\
  build/$(MODE)/demo/mesh/brick_2d_5_forman_cbd.txt\
  build/$(MODE)/demo/mesh/brick_2d_5_forman_cbd_star.txt\
  build/$(MODE)/obj/src/diffusion_transient_continuous_2d_d00_p00$(.OBJ)\
  | build/$(MODE)/demo/diffusion build/$(MODE)/lib/libshared$(.DLL)
	$< --raw $(word 2, $^) $(word 3, $^) $(word 4, $^) $(word 2, $|)\
	  diffusion_transient_continuous_2d_d00_p00 0.0001 10000 > $@

build/$(MODE)/demo/diffusion/transient_continuous_2d_d00_p01_primal_strong_cochain_brick_2d_5_forman_potential.txt:\
  build/$(MODE)/bin/diffusion_transient_continuous_primal_strong_cochain_solve_trapezoidal$(.EXE)\
  build/$(MODE)/demo/mesh/brick_2d_5_forman.txt\
  build/$(MODE)/demo/mesh/brick_2d_5_forman_cbd.txt\
  build/$(MODE)/demo/mesh/brick_2d_5_forman_cbd_star.txt\
  build/$(MODE)/obj/src/diffusion_transient_continuous_2d_d00_p01$(.OBJ)\
  | build/$(MODE)/demo/diffusion build/$(MODE)/lib/libshared$(.DLL)
	$< --raw $(word 2, $^) $(word 3, $^) $(word 4, $^) $(word 2, $|)\
	  diffusion_transient_continuous_2d_d00_p01 0.0001 10000 > $@

build/$(MODE)/demo/diffusion/transient_continuous_2d_d00_p01_primal_strong_cochain_brick_2d_10_forman_potential.txt:\
  build/$(MODE)/bin/diffusion_transient_continuous_primal_strong_cochain_solve_trapezoidal$(.EXE)\
  build/$(MODE)/demo/mesh/brick_2d_10_forman.txt\
  build/$(MODE)/demo/mesh/brick_2d_10_forman_cbd.txt\
  build/$(MODE)/demo/mesh/brick_2d_10_forman_cbd_star.txt\
  build/$(MODE)/obj/src/diffusion_transient_continuous_2d_d00_p01$(.OBJ)\
  | build/$(MODE)/demo/diffusion build/$(MODE)/lib/libshared$(.DLL)
	$< --raw $(word 2, $^) $(word 3, $^) $(word 4, $^) $(word 2, $|)\
	  diffusion_transient_continuous_2d_d00_p01 0.0001 4000 > $@

build/$(MODE)/demo/diffusion/transient_continuous_2d_d00_p01_primal_strong_cochain_brick_2d_10_forman_dual_flow.txt:\
  build/$(MODE)/bin/diffusion_transient_discrete_primal_dual_flow$(.EXE)\
  build/$(MODE)/demo/mesh/brick_2d_10_forman.txt\
  build/$(MODE)/demo/diffusion/transient_continuous_2d_d00_p01_primal_strong_cochain_brick_2d_10_forman_potential.txt\
  build/$(MODE)/obj/src/diffusion_steady_state_continuous_2d_d00_p01$(.OBJ)\
  | build/$(MODE)/demo/diffusion build/$(MODE)/lib/libshared$(.DLL)
	$< --raw $(word 2, $^) "-" $(word 2, $|)\
	  diffusion_transient_continuous_2d_d00_p01 4000 --raw $(word 3, $^) --raw > $@

build/$(MODE)/demo/diffusion/transient_continuous_2d_d02_p00_primal_strong_cochain_2d_10_grains_forman_potential.txt:\
  build/$(MODE)/bin/diffusion_transient_continuous_primal_strong_cochain_solve_trapezoidal$(.EXE)\
  build/$(MODE)/demo/mesh/2d_10_grains_forman.txt\
  build/$(MODE)/demo/mesh/2d_10_grains_forman_cbd.txt\
  build/$(MODE)/demo/mesh/2d_10_grains_forman_cbd_star.txt\
  build/$(MODE)/obj/src/diffusion_transient_continuous_2d_d02_p00$(.OBJ)\
  | build/$(MODE)/demo/diffusion build/$(MODE)/lib/libshared$(.DLL)
	$< --raw $(word 2, $^) $(word 3, $^) $(word 4, $^) $(word 2, $|)\
	  diffusion_transient_continuous_2d_d02_p00 0.0001 1000 > $@

build/$(MODE)/demo/diffusion/transient_continuous_2d_d02_p00_primal_strong_cochain_2d_10_grains_forman_dual_flow.txt:\
  build/$(MODE)/bin/diffusion_transient_discrete_primal_dual_flow$(.EXE)\
  build/$(MODE)/demo/mesh/2d_10_grains_forman.txt\
  build/$(MODE)/demo/diffusion/transient_continuous_2d_d02_p00_primal_strong_cochain_2d_10_grains_forman_potential.txt\
  build/$(MODE)/obj/src/diffusion_transient_continuous_2d_d02_p00$(.OBJ)\
  | build/$(MODE)/demo/diffusion build/$(MODE)/lib/libshared$(.DLL)
	$< --raw $(word 2, $^) "-" $(word 2, $|)\
	  diffusion_transient_continuous_2d_d02_p00 1000 --raw $(word 3, $^) --raw > $@

build/$(MODE)/demo/diffusion/transient_continuous_2d_d02_p00_primal_weak_cochain_2d_10_grains_forman_potential.txt:\
  build/$(MODE)/bin/diffusion_transient_continuous_primal_weak_cochain_solve_trapezoidal$(.EXE)\
  build/$(MODE)/demo/mesh/2d_10_grains_forman.txt\
  build/$(MODE)/demo/mesh/2d_10_grains_forman_vol.txt\
  build/$(MODE)/demo/mesh/2d_10_grains_forman_inner.txt\
  build/$(MODE)/obj/src/diffusion_transient_continuous_2d_d02_p00$(.OBJ)\
  | build/$(MODE)/demo/diffusion build/$(MODE)/lib/libshared$(.DLL)
	$< --raw $(word 2, $^) --raw $(word 3, $^) --raw $(word 4, $^)\
	  $(word 2, $|) diffusion_transient_continuous_2d_d02_p00 0.01 2000 --raw > $@

build/$(MODE)/demo/diffusion/transient_continuous_2d_d02_p00_primal_weak_cochain_2d_10_grains_forman_dual_flow.txt:\
  build/$(MODE)/bin/diffusion_transient_discrete_primal_dual_flow$(.EXE)\
  build/$(MODE)/demo/mesh/2d_10_grains_forman.txt\
  build/$(MODE)/demo/diffusion/transient_continuous_2d_d02_p00_primal_weak_cochain_2d_10_grains_forman_potential.txt\
  build/$(MODE)/obj/src/diffusion_transient_continuous_2d_d02_p00$(.OBJ)\
  | build/$(MODE)/demo/diffusion build/$(MODE)/lib/libshared$(.DLL)
	$< --raw $(word 2, $^) "-" $(word 2, $|)\
	  diffusion_transient_continuous_2d_d02_p00 2000 --raw $(word 3, $^) --raw > $@

build/$(MODE)/demo/diffusion/transient_continuous_2d_d02_p00_primal_weak_to_steady_state_cochain_2d_10_grains_forman_potential.txt:\
  build/$(MODE)/bin/diffusion_transient_continuous_primal_weak_cochain_solve_trapezoidal_to_steady_state$(.EXE)\
  build/$(MODE)/demo/mesh/2d_10_grains_forman.txt\
  build/$(MODE)/demo/mesh/2d_10_grains_forman_vol.txt\
  build/$(MODE)/demo/mesh/2d_10_grains_forman_inner.txt\
  build/$(MODE)/obj/src/diffusion_transient_continuous_2d_d02_p00$(.OBJ)\
  | build/$(MODE)/demo/diffusion build/$(MODE)/lib/libshared$(.DLL)
	$< --raw $(word 2, $^) --raw $(word 3, $^) --raw $(word 4, $^)\
	  $(word 2, $|) diffusion_transient_continuous_2d_d02_p00 0.001 0.0001 > $@

build/$(MODE)/demo/diffusion/transient_continuous_2d_d02_p01_primal_weak_cochain_2d_10_grains_forman_potential.txt:\
  build/$(MODE)/bin/diffusion_transient_continuous_primal_weak_cochain_solve_trapezoidal$(.EXE)\
  build/$(MODE)/demo/mesh/2d_10_grains_forman.txt\
  build/$(MODE)/demo/mesh/2d_10_grains_forman_vol.txt\
  build/$(MODE)/demo/mesh/2d_10_grains_forman_inner.txt\
  build/$(MODE)/obj/src/diffusion_transient_continuous_2d_d02_p01$(.OBJ)\
  | build/$(MODE)/demo/diffusion build/$(MODE)/lib/libshared$(.DLL)
	$< --raw $(word 2, $^) --raw $(word 3, $^) --raw $(word 4, $^)\
  	  $(word 2, $|) diffusion_transient_continuous_2d_d02_p01 0.01 2000 --raw > $@

build/$(MODE)/demo/diffusion/transient_continuous_2d_d01_p00_primal_strong_cochain_square_8_potential.txt:\
  build/$(MODE)/bin/diffusion_transient_continuous_primal_strong_cochain_solve_trapezoidal$(.EXE)\
  build/$(MODE)/demo/mesh/square_8.txt\
  build/$(MODE)/demo/mesh/square_8_cbd.txt\
  build/$(MODE)/demo/mesh/square_8_cbd_star.txt\
  build/$(MODE)/obj/src/diffusion_transient_continuous_2d_d01_p00$(.OBJ)\
  | build/$(MODE)/demo/diffusion build/$(MODE)/lib/libshared$(.DLL)
	$< --raw $(word 2, $^) $(word 3, $^) $(word 4, $^) $(word 2, $|)\
	  diffusion_transient_continuous_2d_d01_p00 0.001 4000 > $@

.PHONY: demo_diffusion_transient_continuous_2d
demo_diffusion_transient_continuous_2d: $(_demo_diffusion_transient_continuous_2d)

_demo_diffusion_transient_continuous_3d :=\
  build/$(MODE)/demo/diffusion/transient_continuous_3d_d00_p00_primal_strong_cochain_brick_3d_2_forman_potential.txt\

build/$(MODE)/demo/diffusion/transient_continuous_3d_d00_p00_primal_strong_cochain_brick_3d_2_forman_potential.txt:\
  build/$(MODE)/bin/diffusion_transient_continuous_primal_strong_cochain_solve_trapezoidal$(.EXE)\
  build/$(MODE)/demo/mesh/brick_3d_2_forman.txt\
  build/$(MODE)/demo/mesh/brick_3d_2_forman_cbd.txt\
  build/$(MODE)/demo/mesh/brick_3d_2_forman_cbd_star.txt\
  build/$(MODE)/obj/src/diffusion_transient_continuous_3d_d00_p00$(.OBJ)\
  | build/$(MODE)/demo/diffusion build/$(MODE)/lib/libshared$(.DLL)
	$< --raw $(word 2, $^) $(word 3, $^) $(word 4, $^) $(word 2, $|)\
	  diffusion_transient_continuous_3d_d00_p00 0.001 1000 > $@

.PHONY: demo_diffusion_transient_continuous_3d
demo_diffusion_transient_continuous_3d: $(_demo_diffusion_transient_continuous_3d)

_demo_diffusion_transient :=\
  $(_demo_diffusion_transient_continuous_2d_d00_p00)\
  $(_demo_diffusion_transient_continuous_2d_d00_p01)\
  $(_demo_diffusion_transient_continuous_2d)\
  $(_demo_diffusion_transient_continuous_3d)\

_demo_diffusion := $(_demo_diffusion_steady_state) $(_demo_diffusion_transient)

.PHONY: demo_diffusion demo_diffusion_clean demo_diffusion_distclean

demo_diffusion: $(_demo_diffusion)

demo_diffusion_clean:
	-$(RM) $(_demo_diffusion)

demo_diffusion_distclean:
	-$(RM) -r build/$(MODE)/demo/diffusion
