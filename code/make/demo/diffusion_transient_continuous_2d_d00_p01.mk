_demo_diffusion_transient_continuous_2d_d00_p01 :=\
  build/$(MODE)/demo/diffusion/transient_continuous_2d_d00_p01_primal_strong_cochain_brick_2d_5_forman_input.txt\
  build/$(MODE)/demo/diffusion/transient_continuous_2d_d00_p01_primal_strong_cochain_brick_2d_5_forman_trapezoidal_0p001_2500_potential.txt\
  build/$(MODE)/demo/diffusion/transient_continuous_2d_d00_p01_primal_strong_cochain_brick_2d_5_forman_trapezoidal_0p001_2500_flow.txt\
  build/$(MODE)/demo/diffusion/transient_continuous_2d_d00_p01_primal_weak_cochain_brick_2d_5_forman_input.txt\
  build/$(MODE)/demo/diffusion/transient_continuous_2d_d00_p01_primal_weak_cochain_brick_2d_5_forman_trapezoidal_0p001_2500_potential.txt\
  build/$(MODE)/demo/diffusion/transient_continuous_2d_d00_p01_primal_weak_cochain_brick_2d_5_forman_trapezoidal_0p001_2500_flow.txt\
  build/$(MODE)/demo/diffusion/transient_continuous_2d_d00_p01_mixed_weak_cochain_brick_2d_5_forman_input.txt\
  build/$(MODE)/demo/diffusion/transient_continuous_2d_d00_p01_mixed_weak_cochain_brick_2d_5_forman_trapezoidal_0p001_2500_solution.txt\
  build/$(MODE)/demo/diffusion/transient_continuous_2d_d00_p01_mixed_weak_cochain_brick_2d_5_forman_trapezoidal_0p001_2500_potential.txt

build/$(MODE)/demo/diffusion/transient_continuous_2d_d00_p01_primal_strong_cochain_brick_2d_5_forman_input.txt:\
  build/$(MODE)/bin/diffusion_transient_discrete_primal_strong_from_continuous$(.EXE)\
  build/$(MODE)/demo/mesh/brick_2d_5_forman.txt\
  build/$(MODE)/obj/src/diffusion_transient_continuous_2d_d00_p01$(.OBJ)\
  | build/$(MODE)/demo/diffusion build/$(MODE)/lib/libshared$(.DLL)
	$<\
  --mesh=$(word 2, $^)\
  --dynamic-library=$(word 2, $|)\
  --input-data=diffusion_transient_continuous_2d_d00_p00\
  > $@

build/$(MODE)/demo/diffusion/transient_continuous_2d_d00_p01_primal_strong_cochain_brick_2d_5_forman_trapezoidal_0p001_2500_potential.txt:\
  build/$(MODE)/bin/diffusion_transient_discrete_primal_strong_solve_trapezoidal$(.EXE)\
  build/$(MODE)/demo/mesh/brick_2d_5_forman.txt\
  build/$(MODE)/demo/mesh/brick_2d_5_forman_cbd.txt\
  build/$(MODE)/demo/mesh/brick_2d_5_forman_cbd_star.txt\
  build/$(MODE)/demo/diffusion/transient_continuous_2d_d00_p01_primal_strong_cochain_brick_2d_5_forman_input.txt\
  | build/$(MODE)/demo/diffusion
	$<\
  --mesh=$(word 2, $^)\
  --mesh-coboundary-0=$(word 3, $^)\
  --mesh-coboundary-star-1=$(word 4, $^)\
  --input-data=$(word 5, $^)\
  --time-step=0.001\
  --number-of-steps=2500\
  > $@

build/$(MODE)/demo/diffusion/transient_continuous_2d_d00_p01_primal_strong_cochain_brick_2d_5_forman_trapezoidal_0p001_2500_flow.txt:\
  build/$(MODE)/bin/diffusion_transient_discrete_flow_from_potential$(.EXE)\
  build/$(MODE)/demo/mesh/brick_2d_5_forman.txt\
  build/$(MODE)/demo/mesh/brick_2d_5_forman_hodge.txt\
  build/$(MODE)/demo/diffusion/transient_continuous_2d_d00_p01_primal_strong_cochain_brick_2d_5_forman_input.txt\
  build/$(MODE)/demo/diffusion/transient_continuous_2d_d00_p01_primal_strong_cochain_brick_2d_5_forman_trapezoidal_0p001_2500_potential.txt\
  | build/$(MODE)/demo/diffusion
	$<\
  --mesh=$(word 2, $^)\
  --mesh-hodge=$(word 3, $^)\
  --kappa-1-format=transient-primal-strong-raw\
  --kappa-1=$(word 4, $^)\
  --potential=$(word 5, $^)\
  --number-of-steps=2500\
  > $@

build/$(MODE)/demo/diffusion/transient_continuous_2d_d00_p01_primal_weak_cochain_brick_2d_5_forman_input.txt:\
  build/$(MODE)/bin/diffusion_transient_discrete_primal_weak_from_continuous$(.EXE)\
  build/$(MODE)/demo/mesh/brick_2d_5_forman.txt\
  build/$(MODE)/demo/mesh/brick_2d_5_forman_vol.txt\
  build/$(MODE)/obj/src/diffusion_transient_continuous_2d_d00_p01$(.OBJ)\
  | build/$(MODE)/demo/diffusion build/$(MODE)/lib/libshared$(.DLL)
	$<\
  --mesh=$(word 2, $^)\
  --mesh-volumes=$(word 3, $^)\
  --dynamic-library=$(word 2, $|)\
  --input-data=diffusion_transient_continuous_2d_d00_p01\
  > $@

build/$(MODE)/demo/diffusion/transient_continuous_2d_d00_p01_primal_weak_cochain_brick_2d_5_forman_trapezoidal_0p001_2500_potential.txt:\
  build/$(MODE)/bin/diffusion_transient_discrete_primal_weak_solve_trapezoidal$(.EXE)\
  build/$(MODE)/demo/mesh/brick_2d_5_forman.txt\
  build/$(MODE)/demo/mesh/brick_2d_5_forman_inner.txt\
  build/$(MODE)/demo/diffusion/transient_continuous_2d_d00_p01_primal_weak_cochain_brick_2d_5_forman_input.txt\
  | build/$(MODE)/demo/diffusion
	$<\
  --mesh=$(word 2, $^)\
  --mesh-inner=$(word 3, $^)\
  --input-data=$(word 4, $^)\
  --time-step=0.001\
  --number-of-steps=2500\
  > $@

build/$(MODE)/demo/diffusion/transient_continuous_2d_d00_p01_primal_weak_cochain_brick_2d_5_forman_trapezoidal_0p001_2500_flow.txt:\
  build/$(MODE)/bin/diffusion_transient_discrete_flow_from_potential$(.EXE)\
  build/$(MODE)/demo/mesh/brick_2d_5_forman.txt\
  build/$(MODE)/demo/mesh/brick_2d_5_forman_hodge.txt\
  build/$(MODE)/demo/diffusion/transient_continuous_2d_d00_p01_primal_weak_cochain_brick_2d_5_forman_input.txt\
  build/$(MODE)/demo/diffusion/transient_continuous_2d_d00_p01_primal_weak_cochain_brick_2d_5_forman_trapezoidal_0p001_2500_potential.txt\
  | build/$(MODE)/demo/diffusion
	$<\
  --mesh=$(word 2, $^)\
  --mesh-hodge=$(word 3, $^)\
  --kappa-1=$(word 4, $^)\
  --kappa-1-format=transient-primal-weak-raw\
  --potential=$(word 5, $^)\
  --number-of-steps=2500\
  > $@

build/$(MODE)/demo/diffusion/transient_continuous_2d_d00_p01_mixed_weak_cochain_brick_2d_5_forman_input.txt:\
  build/$(MODE)/bin/diffusion_transient_discrete_mixed_weak_from_continuous$(.EXE)\
  build/$(MODE)/demo/mesh/brick_2d_5_forman.txt\
  build/$(MODE)/demo/mesh/brick_2d_5_forman_cbd_star.txt\
  build/$(MODE)/demo/mesh/brick_2d_5_forman_vol.txt\
  build/$(MODE)/obj/src/diffusion_transient_continuous_2d_d00_p01$(.OBJ)\
  | build/$(MODE)/demo/diffusion build/$(MODE)/lib/libshared$(.DLL)
	$<\
  --mesh=$(word 2, $^)\
  --mesh-coboundary-star=$(word 3, $^)\
  --mesh-volumes=$(word 4, $^)\
  --dynamic-library=$(word 2, $|)\
  --input-data=diffusion_transient_continuous_2d_d00_p01\
  > $@

build/$(MODE)/demo/diffusion/transient_continuous_2d_d00_p01_mixed_weak_cochain_brick_2d_5_forman_trapezoidal_0p001_2500_solution.txt:\
  build/$(MODE)/bin/diffusion_transient_discrete_mixed_weak_solve_trapezoidal$(.EXE)\
  build/$(MODE)/demo/mesh/brick_2d_5_forman.txt\
  build/$(MODE)/demo/mesh/brick_2d_5_forman_inner_corrected.txt\
  build/$(MODE)/demo/diffusion/transient_continuous_2d_d00_p01_mixed_weak_cochain_brick_2d_5_forman_input.txt\
  | build/$(MODE)/demo/diffusion
	$<\
  --mesh=$(word 2, $^)\
  --mesh-inner=$(word 3, $^)\
  --input-data=$(word 4, $^)\
  --time-step=0.001\
  --number-of-steps=2500\
  > $@

build/$(MODE)/demo/diffusion/transient_continuous_2d_d00_p01_mixed_weak_cochain_brick_2d_5_forman_trapezoidal_0p001_2500_potential.txt:\
  build/$(MODE)/bin/diffusion_transient_discrete_mixed_weak_potential$(.EXE)\
  build/$(MODE)/demo/mesh/brick_2d_5_forman.txt\
  build/$(MODE)/demo/mesh/brick_2d_5_forman_vol.txt\
  build/$(MODE)/demo/diffusion/transient_continuous_2d_d00_p01_mixed_weak_cochain_brick_2d_5_forman_input.txt\
  build/$(MODE)/demo/diffusion/transient_continuous_2d_d00_p01_mixed_weak_cochain_brick_2d_5_forman_trapezoidal_0p001_2500_solution.txt\
  | build/$(MODE)/demo/diffusion
	$<\
  --mesh=$(word 2, $^)\
  --mesh-volumes=$(word 3, $^)\
  --input-data=$(word 4, $^)\
  --number-of-steps=2500\
  --solution=$(word 5, $^)\
  > $@
