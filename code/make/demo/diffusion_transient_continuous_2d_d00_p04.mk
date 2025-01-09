_demo_diffusion_transient_continuous_2d_d00_p04 :=\
  build/$(MODE)/demo/diffusion/transient_continuous_2d_d00_p04_primal_strong_cochain_brick_2d_5_forman_input.txt\
  build/$(MODE)/demo/diffusion/transient_continuous_2d_d00_p04_primal_strong_cochain_brick_2d_5_forman_trapezoidal_0p001_2500_potential.txt\
  build/$(MODE)/demo/diffusion/transient_continuous_2d_d00_p04_primal_strong_cochain_brick_2d_5_forman_trapezoidal_0p001_2500_flow.txt\
  build/$(MODE)/demo/diffusion/transient_continuous_2d_d00_p04_primal_weak_cochain_brick_2d_5_forman_input.txt\
  build/$(MODE)/demo/diffusion/transient_continuous_2d_d00_p04_primal_weak_cochain_brick_2d_5_forman_trapezoidal_0p001_2500_potential.txt\
  build/$(MODE)/demo/diffusion/transient_continuous_2d_d00_p04_primal_weak_cochain_brick_2d_5_forman_trapezoidal_0p001_2500_flow.txt\
  build/$(MODE)/demo/diffusion/transient_continuous_2d_d00_p04_mixed_weak_cochain_brick_2d_5_forman_input.txt\
  build/$(MODE)/demo/diffusion/transient_continuous_2d_d00_p04_mixed_weak_cochain_brick_2d_5_forman_trapezoidal_0p001_2500_solution.txt\
  build/$(MODE)/demo/diffusion/transient_continuous_2d_d00_p04_mixed_weak_cochain_brick_2d_5_forman_trapezoidal_0p001_2500_potential.txt

build/$(MODE)/demo/diffusion/transient_continuous_2d_d00_p04_primal_strong_cochain_brick_2d_5_forman_input.txt:\
  build/$(MODE)/bin/diffusion_transient_discrete_primal_strong_from_continuous$(.EXE)\
  build/$(MODE)/demo/mesh/brick_2d_5_forman.txt\
  build/$(MODE)/obj/src/diffusion_transient_continuous_2d_d00_p04$(.OBJ)\
  | build/$(MODE)/demo/diffusion build/$(MODE)/lib/libshared$(.DLL)
	$<\
  --raw $(word 2, $^)\
  $(word 2, $|)\
  diffusion_transient_continuous_2d_d00_p04\
  > $@

build/$(MODE)/demo/diffusion/transient_continuous_2d_d00_p04_primal_strong_cochain_brick_2d_5_forman_trapezoidal_0p001_2500_potential.txt:\
  build/$(MODE)/bin/diffusion_transient_discrete_primal_strong_solve_trapezoidal$(.EXE)\
  build/$(MODE)/demo/mesh/brick_2d_5_forman.txt\
  build/$(MODE)/demo/mesh/brick_2d_5_forman_cbd.txt\
  build/$(MODE)/demo/mesh/brick_2d_5_forman_cbd_star.txt\
  build/$(MODE)/demo/diffusion/transient_continuous_2d_d00_p04_primal_strong_cochain_brick_2d_5_forman_input.txt\
  | build/$(MODE)/demo/diffusion
	$<\
  --raw $(word 2, $^)\
  $(word 3, $^)\
  $(word 4, $^)\
  $(word 5, $^)\
  0.001 2500\
  > $@

build/$(MODE)/demo/diffusion/transient_continuous_2d_d00_p04_primal_strong_cochain_brick_2d_5_forman_trapezoidal_0p001_2500_flow.txt:\
  build/$(MODE)/bin/diffusion_transient_discrete_flow_from_potential$(.EXE)\
  build/$(MODE)/demo/mesh/brick_2d_5_forman.txt\
  build/$(MODE)/demo/mesh/brick_2d_5_forman_hodge.txt\
  build/$(MODE)/demo/diffusion/transient_continuous_2d_d00_p04_primal_strong_cochain_brick_2d_5_forman_input.txt\
  build/$(MODE)/demo/diffusion/transient_continuous_2d_d00_p04_primal_strong_cochain_brick_2d_5_forman_trapezoidal_0p001_2500_potential.txt\
  | build/$(MODE)/demo/diffusion
	$<\
  --raw $(word 2, $^)\
  --raw $(word 3, $^)\
  --transient-primal-strong-raw $(word 4, $^)\
  --raw $(word 5, $^)\
  2500\
  --raw > $@

build/$(MODE)/demo/diffusion/transient_continuous_2d_d00_p04_primal_weak_cochain_brick_2d_5_forman_input.txt:\
  build/$(MODE)/bin/diffusion_transient_discrete_primal_weak_from_continuous$(.EXE)\
  build/$(MODE)/demo/mesh/brick_2d_5_forman.txt\
  build/$(MODE)/demo/mesh/brick_2d_5_forman_vol.txt\
  build/$(MODE)/obj/src/diffusion_transient_continuous_2d_d00_p04$(.OBJ)\
  | build/$(MODE)/demo/diffusion build/$(MODE)/lib/libshared$(.DLL)
	$<\
  --raw $(word 2, $^)\
  --raw $(word 3, $^)\
  $(word 2, $|)\
  diffusion_transient_continuous_2d_d00_p04\
  > $@

build/$(MODE)/demo/diffusion/transient_continuous_2d_d00_p04_primal_weak_cochain_brick_2d_5_forman_trapezoidal_0p001_2500_potential.txt:\
  build/$(MODE)/bin/diffusion_transient_discrete_primal_weak_solve_trapezoidal$(.EXE)\
  build/$(MODE)/demo/mesh/brick_2d_5_forman.txt\
  build/$(MODE)/demo/mesh/brick_2d_5_forman_inner.txt\
  build/$(MODE)/demo/diffusion/transient_continuous_2d_d00_p04_primal_weak_cochain_brick_2d_5_forman_input.txt\
  | build/$(MODE)/demo/diffusion
	$<\
  --raw $(word 2, $^)\
  --raw $(word 3, $^)\
  $(word 4, $^)\
  0.001 2500\
  > $@

build/$(MODE)/demo/diffusion/transient_continuous_2d_d00_p04_primal_weak_cochain_brick_2d_5_forman_trapezoidal_0p001_2500_flow.txt:\
  build/$(MODE)/bin/diffusion_transient_discrete_flow_from_potential$(.EXE)\
  build/$(MODE)/demo/mesh/brick_2d_5_forman.txt\
  build/$(MODE)/demo/mesh/brick_2d_5_forman_hodge.txt\
  build/$(MODE)/demo/diffusion/transient_continuous_2d_d00_p04_primal_weak_cochain_brick_2d_5_forman_input.txt\
  build/$(MODE)/demo/diffusion/transient_continuous_2d_d00_p04_primal_weak_cochain_brick_2d_5_forman_trapezoidal_0p001_2500_potential.txt\
  | build/$(MODE)/demo/diffusion
	$<\
  --raw $(word 2, $^)\
  --raw $(word 3, $^)\
  --transient-primal-weak-raw $(word 4, $^)\
  --raw $(word 5, $^)\
  2500\
  --raw > $@

build/$(MODE)/demo/diffusion/transient_continuous_2d_d00_p04_mixed_weak_cochain_brick_2d_5_forman_input.txt:\
  build/$(MODE)/bin/diffusion_transient_discrete_mixed_weak_from_continuous$(.EXE)\
  build/$(MODE)/demo/mesh/brick_2d_5_forman.txt\
  build/$(MODE)/demo/mesh/brick_2d_5_forman_cbd_star.txt\
  build/$(MODE)/demo/mesh/brick_2d_5_forman_vol.txt\
  build/$(MODE)/obj/src/diffusion_transient_continuous_2d_d00_p04$(.OBJ)\
  | build/$(MODE)/demo/diffusion build/$(MODE)/lib/libshared$(.DLL)
	$<\
  --raw $(word 2, $^)\
  $(word 3, $^)\
  --raw $(word 4, $^)\
  $(word 2, $|)\
  diffusion_transient_continuous_2d_d00_p04\
  > $@

build/$(MODE)/demo/diffusion/transient_continuous_2d_d00_p04_mixed_weak_cochain_brick_2d_5_forman_trapezoidal_0p001_2500_solution.txt:\
  build/$(MODE)/bin/diffusion_transient_discrete_mixed_weak_solve_trapezoidal$(.EXE)\
  build/$(MODE)/demo/mesh/brick_2d_5_forman.txt\
  build/$(MODE)/demo/mesh/brick_2d_5_forman_inner.txt\
  build/$(MODE)/demo/diffusion/transient_continuous_2d_d00_p04_mixed_weak_cochain_brick_2d_5_forman_input.txt\
  | build/$(MODE)/demo/diffusion
	$<\
  --mesh-format=--raw\
  --mesh=$(word 2, $^)\
  --mesh-inner-format=--raw\
  --mesh-inner=$(word 3, $^)\
  --input-data=$(word 4, $^)\
  --number-of-steps=2500\
  --time-step=0.001\
  > $@

build/$(MODE)/demo/diffusion/transient_continuous_2d_d00_p04_mixed_weak_cochain_brick_2d_5_forman_trapezoidal_0p001_2500_potential.txt:\
  build/$(MODE)/bin/diffusion_transient_discrete_mixed_weak_potential$(.EXE)\
  build/$(MODE)/demo/mesh/brick_2d_5_forman.txt\
  build/$(MODE)/demo/mesh/brick_2d_5_forman_vol.txt\
  build/$(MODE)/demo/diffusion/transient_continuous_2d_d00_p04_mixed_weak_cochain_brick_2d_5_forman_input.txt\
  build/$(MODE)/demo/diffusion/transient_continuous_2d_d00_p04_mixed_weak_cochain_brick_2d_5_forman_trapezoidal_0p001_2500_solution.txt\
  | build/$(MODE)/demo/diffusion
	$<\
  --raw $(word 2, $^)\
  --raw $(word 3, $^)\
  $(word 4, $^)\
  2500 $(word 5, $^)\
  > $@
