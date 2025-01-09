_demo_diffusion_transient_continuous_2d_d00_p00 :=\
  build/$(MODE)/demo/diffusion/transient_continuous_2d_d00_p00_primal_strong_cochain_brick_2d_2_forman_input.txt\
  build/$(MODE)/demo/diffusion/transient_continuous_2d_d00_p00_primal_strong_cochain_brick_2d_2_forman_trapezoidal_0p001_100_potential.txt\
  build/$(MODE)/demo/diffusion/transient_continuous_2d_d00_p00_primal_strong_cochain_brick_2d_2_forman_trapezoidal_0p001_100_flow.txt\
  build/$(MODE)/demo/diffusion/transient_continuous_2d_d00_p00_primal_weak_cochain_brick_2d_2_forman_input.txt\
  build/$(MODE)/demo/diffusion/transient_continuous_2d_d00_p00_primal_weak_cochain_brick_2d_2_forman_trapezoidal_0p001_100_potential.txt\
  build/$(MODE)/demo/diffusion/transient_continuous_2d_d00_p00_primal_weak_cochain_brick_2d_2_forman_trapezoidal_0p001_100_flow.txt\
  build/$(MODE)/demo/diffusion/transient_continuous_2d_d00_p00_mixed_weak_cochain_brick_2d_2_forman_input.txt\
  build/$(MODE)/demo/diffusion/transient_continuous_2d_d00_p00_mixed_weak_cochain_brick_2d_2_forman_trapezoidal_0p001_1000_solution.txt\
  build/$(MODE)/demo/diffusion/transient_continuous_2d_d00_p00_mixed_weak_cochain_brick_2d_2_forman_trapezoidal_0p001_1000_potential.txt

build/$(MODE)/demo/diffusion/transient_continuous_2d_d00_p00_primal_strong_cochain_brick_2d_2_forman_input.txt:\
  build/$(MODE)/bin/diffusion_transient_discrete_primal_strong_from_continuous$(.EXE)\
  build/$(MODE)/demo/mesh/brick_2d_2_forman.txt\
  build/$(MODE)/obj/src/diffusion_transient_continuous_2d_d00_p00$(.OBJ)\
  | build/$(MODE)/demo/diffusion build/$(MODE)/lib/libshared$(.DLL)
	$<\
  --raw $(word 2, $^)\
  $(word 2, $|)\
  diffusion_transient_continuous_2d_d00_p00\
  > $@

build/$(MODE)/demo/diffusion/transient_continuous_2d_d00_p00_primal_strong_cochain_brick_2d_2_forman_trapezoidal_0p001_100_potential.txt:\
  build/$(MODE)/bin/diffusion_transient_discrete_primal_strong_solve_trapezoidal$(.EXE)\
  build/$(MODE)/demo/mesh/brick_2d_2_forman.txt\
  build/$(MODE)/demo/mesh/brick_2d_2_forman_cbd.txt\
  build/$(MODE)/demo/mesh/brick_2d_2_forman_cbd_star.txt\
  build/$(MODE)/demo/diffusion/transient_continuous_2d_d00_p00_primal_strong_cochain_brick_2d_2_forman_input.txt\
  | build/$(MODE)/demo/diffusion
	$<\
  --raw $(word 2, $^)\
  $(word 3, $^)\
  $(word 4, $^)\
  $(word 5, $^)\
  0.001 100\
  > $@

build/$(MODE)/demo/diffusion/transient_continuous_2d_d00_p00_primal_strong_cochain_brick_2d_2_forman_trapezoidal_0p001_100_flow.txt:\
  build/$(MODE)/bin/diffusion_transient_discrete_flow_from_potential$(.EXE)\
  build/$(MODE)/demo/mesh/brick_2d_2_forman.txt\
  build/$(MODE)/demo/mesh/brick_2d_2_forman_hodge.txt\
  build/$(MODE)/demo/diffusion/transient_continuous_2d_d00_p00_primal_strong_cochain_brick_2d_2_forman_input.txt\
  build/$(MODE)/demo/diffusion/transient_continuous_2d_d00_p00_primal_strong_cochain_brick_2d_2_forman_trapezoidal_0p001_100_potential.txt\
  | build/$(MODE)/demo/diffusion
	$<\
  --raw $(word 2, $^)\
  --raw $(word 3, $^)\
  --transient-primal-strong-raw $(word 4, $^)\
  --raw $(word 5, $^)\
  100\
  --raw > $@

build/$(MODE)/demo/diffusion/transient_continuous_2d_d00_p00_primal_weak_cochain_brick_2d_2_forman_input.txt:\
  build/$(MODE)/bin/diffusion_transient_discrete_primal_weak_from_continuous$(.EXE)\
  build/$(MODE)/demo/mesh/brick_2d_2_forman.txt\
  build/$(MODE)/demo/mesh/brick_2d_2_forman_vol.txt\
  build/$(MODE)/obj/src/diffusion_transient_continuous_2d_d00_p00$(.OBJ)\
  | build/$(MODE)/demo/diffusion build/$(MODE)/lib/libshared$(.DLL)
	$<\
  --raw $(word 2, $^)\
  --raw $(word 3, $^)\
  $(word 2, $|)\
  diffusion_transient_continuous_2d_d00_p00\
  > $@

build/$(MODE)/demo/diffusion/transient_continuous_2d_d00_p00_primal_weak_cochain_brick_2d_2_forman_trapezoidal_0p001_100_potential.txt:\
  build/$(MODE)/bin/diffusion_transient_discrete_primal_weak_solve_trapezoidal$(.EXE)\
  build/$(MODE)/demo/mesh/brick_2d_2_forman.txt\
  build/$(MODE)/demo/mesh/brick_2d_2_forman_inner.txt\
  build/$(MODE)/demo/diffusion/transient_continuous_2d_d00_p00_primal_weak_cochain_brick_2d_2_forman_input.txt\
  | build/$(MODE)/demo/diffusion
	$<\
  --raw $(word 2, $^)\
  --raw $(word 3, $^)\
  $(word 4, $^)\
  0.001 100\
  > $@

build/$(MODE)/demo/diffusion/transient_continuous_2d_d00_p00_primal_weak_cochain_brick_2d_2_forman_trapezoidal_0p001_100_flow.txt:\
  build/$(MODE)/bin/diffusion_transient_discrete_flow_from_potential$(.EXE)\
  build/$(MODE)/demo/mesh/brick_2d_2_forman.txt\
  build/$(MODE)/demo/mesh/brick_2d_2_forman_hodge.txt\
  build/$(MODE)/demo/diffusion/transient_continuous_2d_d00_p00_primal_weak_cochain_brick_2d_2_forman_input.txt\
  build/$(MODE)/demo/diffusion/transient_continuous_2d_d00_p00_primal_weak_cochain_brick_2d_2_forman_trapezoidal_0p001_100_potential.txt\
  | build/$(MODE)/demo/diffusion
	$<\
  --raw $(word 2, $^)\
  --raw $(word 3, $^)\
  --transient-primal-weak-raw $(word 4, $^)\
  --raw $(word 5, $^)\
  100\
  --raw > $@

build/$(MODE)/demo/diffusion/transient_continuous_2d_d00_p00_mixed_weak_cochain_brick_2d_2_forman_input.txt:\
  build/$(MODE)/bin/diffusion_transient_discrete_mixed_weak_from_continuous$(.EXE)\
  build/$(MODE)/demo/mesh/brick_2d_2_forman.txt\
  build/$(MODE)/demo/mesh/brick_2d_2_forman_cbd_star.txt\
  build/$(MODE)/demo/mesh/brick_2d_2_forman_vol.txt\
  build/$(MODE)/obj/src/diffusion_transient_continuous_2d_d00_p00$(.OBJ)\
  | build/$(MODE)/demo/diffusion build/$(MODE)/lib/libshared$(.DLL)
	$<\
  --raw $(word 2, $^)\
  $(word 3, $^)\
  --raw $(word 4, $^)\
  $(word 2, $|)\
  diffusion_transient_continuous_2d_d00_p00\
  > $@

build/$(MODE)/demo/diffusion/transient_continuous_2d_d00_p00_mixed_weak_cochain_brick_2d_2_forman_trapezoidal_0p001_1000_solution.txt:\
  build/$(MODE)/bin/diffusion_transient_discrete_mixed_weak_solve_trapezoidal$(.EXE)\
  build/$(MODE)/demo/mesh/brick_2d_2_forman.txt\
  build/$(MODE)/demo/mesh/brick_2d_2_forman_inner.txt\
  build/$(MODE)/demo/diffusion/transient_continuous_2d_d00_p00_mixed_weak_cochain_brick_2d_2_forman_input.txt\
  | build/$(MODE)/demo/diffusion
	$<\
  --mesh-format=--raw\
  --mesh=$(word 2, $^)\
  --mesh-inner-format=--raw\
  --mesh-inner=$(word 3, $^)\
  --input-data=$(word 4, $^)\
  --number-of-steps=1000\
  --time-step=0.001\
  > $@

build/$(MODE)/demo/diffusion/transient_continuous_2d_d00_p00_mixed_weak_cochain_brick_2d_2_forman_trapezoidal_0p001_1000_potential.txt:\
  build/$(MODE)/bin/diffusion_transient_discrete_mixed_weak_potential$(.EXE)\
  build/$(MODE)/demo/mesh/brick_2d_2_forman.txt\
  build/$(MODE)/demo/mesh/brick_2d_2_forman_vol.txt\
  build/$(MODE)/demo/diffusion/transient_continuous_2d_d00_p00_mixed_weak_cochain_brick_2d_2_forman_input.txt\
  build/$(MODE)/demo/diffusion/transient_continuous_2d_d00_p00_mixed_weak_cochain_brick_2d_2_forman_trapezoidal_0p001_1000_solution.txt\
  | build/$(MODE)/demo/diffusion
	$<\
  --raw $(word 2, $^)\
  --raw $(word 3, $^)\
  $(word 4, $^)\
  1000 $(word 5, $^)\
  > $@
