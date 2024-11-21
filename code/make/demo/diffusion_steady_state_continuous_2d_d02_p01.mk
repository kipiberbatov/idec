_demo_diffusion_steady_state_continuous_2d_d02_p01 :=\
  build/$(MODE)/demo/diffusion/steady_state_continuous_2d_d02_p01_exact_2d_10_grains_forman_potential.txt\
  build/$(MODE)/demo/diffusion/steady_state_continuous_2d_d02_p01_exact_2d_10_grains_forman_flow.txt\
  build/$(MODE)/demo/diffusion/steady_state_continuous_2d_d02_p01_primal_strong_cochain_2d_10_grains_forman_input.txt\
  build/$(MODE)/demo/diffusion/steady_state_continuous_2d_d02_p01_primal_strong_cochain_2d_10_grains_forman_potential.txt\
  build/$(MODE)/demo/diffusion/steady_state_continuous_2d_d02_p01_primal_strong_cochain_2d_10_grains_forman_flow.txt\
  build/$(MODE)/demo/diffusion/steady_state_continuous_2d_d02_p01_primal_weak_cochain_2d_10_grains_forman_input.txt\
  build/$(MODE)/demo/diffusion/steady_state_continuous_2d_d02_p01_primal_weak_cochain_2d_10_grains_forman_potential.txt\
  build/$(MODE)/demo/diffusion/steady_state_continuous_2d_d02_p01_primal_weak_cochain_2d_10_grains_forman_flow.txt\
  build/$(MODE)/demo/diffusion/steady_state_continuous_2d_d02_p01_mixed_weak_cochain_2d_10_grains_forman_input.txt\
  build/$(MODE)/demo/diffusion/steady_state_continuous_2d_d02_p01_mixed_weak_cochain_2d_10_grains_forman_solution.txt\
  build/$(MODE)/demo/diffusion/steady_state_continuous_2d_d02_p01_mixed_weak_cochain_2d_10_grains_forman_potential.txt\

build/$(MODE)/demo/diffusion/steady_state_continuous_2d_d02_p01_exact_2d_10_grains_forman_potential.txt:\
  build/$(MODE)/bin/diffusion_steady_state_continuous_exact_potential$(.EXE)\
  build/$(MODE)/demo/mesh/2d_10_grains_forman.txt\
  build/$(MODE)/obj/src/diffusion_steady_state_continuous_2d_d02_p01$(.OBJ)\
  | build/$(MODE)/demo/diffusion build/$(MODE)/lib/libshared$(.DLL)
	$<\
  --raw $(word 2, $^)\
  $(word 2, $|)\
  diffusion_steady_state_continuous_2d_d02_p01_potential\
  --raw > $@

build/$(MODE)/demo/diffusion/steady_state_continuous_2d_d02_p01_exact_2d_10_grains_forman_flow.txt:\
  build/$(MODE)/bin/diffusion_steady_state_continuous_exact_flow$(.EXE)\
  build/$(MODE)/demo/mesh/2d_10_grains_forman.txt\
  build/$(MODE)/obj/src/diffusion_steady_state_continuous_2d_d02_p01$(.OBJ)\
  | build/$(MODE)/demo/diffusion build/$(MODE)/lib/libshared$(.DLL)
	$<\
  --raw $(word 2, $^)\
  $(word 2, $|)\
  diffusion_steady_state_continuous_2d_d02_p01_flow\
  --raw > $@

build/$(MODE)/demo/diffusion/steady_state_continuous_2d_d02_p01_primal_strong_cochain_2d_10_grains_forman_input.txt:\
  build/$(MODE)/bin/diffusion_steady_state_discrete_primal_strong_from_continuous$(.EXE)\
  build/$(MODE)/demo/mesh/2d_10_grains_forman.txt\
  build/$(MODE)/obj/src/diffusion_steady_state_continuous_2d_d02_p01$(.OBJ)\
  | build/$(MODE)/demo/diffusion build/$(MODE)/lib/libshared$(.DLL)
	$<\
  --raw $(word 2, $^)\
  $(word 2, $|)\
  diffusion_steady_state_continuous_2d_d02_p01\
  > $@

build/$(MODE)/demo/diffusion/steady_state_continuous_2d_d02_p01_primal_strong_cochain_2d_10_grains_forman_potential.txt:\
  build/$(MODE)/bin/diffusion_steady_state_discrete_primal_strong_solve$(.EXE)\
  build/$(MODE)/demo/mesh/2d_10_grains_forman.txt\
  build/$(MODE)/demo/mesh/2d_10_grains_forman_cbd.txt\
  build/$(MODE)/demo/mesh/2d_10_grains_forman_cbd_star.txt\
  build/$(MODE)/demo/diffusion/steady_state_continuous_2d_d02_p01_primal_strong_cochain_2d_10_grains_forman_input.txt\
  | build/$(MODE)/demo/diffusion
	$<\
  --raw $(word 2, $^)\
  $(word 3, $^)\
  $(word 4, $^)\
  $(word 5, $^)\
  > $@

build/$(MODE)/demo/diffusion/steady_state_continuous_2d_d02_p01_primal_strong_cochain_2d_10_grains_forman_flow.txt:\
  build/$(MODE)/bin/diffusion_steady_state_discrete_flow_from_potential$(.EXE)\
  build/$(MODE)/demo/mesh/2d_10_grains_forman.txt\
  build/$(MODE)/demo/mesh/2d_10_grains_forman_hodge.txt\
  build/$(MODE)/demo/diffusion/steady_state_continuous_2d_d02_p01_primal_strong_cochain_2d_10_grains_forman_input.txt\
  build/$(MODE)/demo/diffusion/steady_state_continuous_2d_d02_p01_primal_strong_cochain_2d_10_grains_forman_potential.txt\
  | build/$(MODE)/demo/diffusion
	$<\
  --raw $(word 2, $^)\
  --raw $(word 3, $^)\
  --steady-state-primal-strong-raw $(word 4, $^)\
  --raw $(word 5, $^)\
  --raw > $@

build/$(MODE)/demo/diffusion/steady_state_continuous_2d_d02_p01_primal_weak_cochain_2d_10_grains_forman_input.txt:\
  build/$(MODE)/bin/diffusion_steady_state_discrete_primal_weak_from_continuous$(.EXE)\
  build/$(MODE)/demo/mesh/2d_10_grains_forman.txt\
  build/$(MODE)/demo/mesh/2d_10_grains_forman_vol.txt\
  build/$(MODE)/obj/src/diffusion_steady_state_continuous_2d_d02_p01$(.OBJ)\
  | build/$(MODE)/demo/diffusion build/$(MODE)/lib/libshared$(.DLL)
	$<\
  --raw $(word 2, $^)\
  --raw $(word 3, $^)\
  $(word 2, $|)\
  diffusion_steady_state_continuous_2d_d02_p01\
  > $@

build/$(MODE)/demo/diffusion/steady_state_continuous_2d_d02_p01_primal_weak_cochain_2d_10_grains_forman_potential.txt:\
  build/$(MODE)/bin/diffusion_steady_state_discrete_primal_weak_solve$(.EXE)\
  build/$(MODE)/demo/mesh/2d_10_grains_forman.txt\
  build/$(MODE)/demo/mesh/2d_10_grains_forman_inner.txt\
  build/$(MODE)/demo/diffusion/steady_state_continuous_2d_d02_p01_primal_weak_cochain_2d_10_grains_forman_input.txt\
  | build/$(MODE)/demo/diffusion
	$<\
  --raw $(word 2, $^)\
  --raw $(word 3, $^)\
  $(word 4, $^)\
  > $@

build/$(MODE)/demo/diffusion/steady_state_continuous_2d_d02_p01_primal_weak_cochain_2d_10_grains_forman_flow.txt:\
  build/$(MODE)/bin/diffusion_steady_state_discrete_flow_from_potential$(.EXE)\
  build/$(MODE)/demo/mesh/2d_10_grains_forman.txt\
  build/$(MODE)/demo/mesh/2d_10_grains_forman_hodge.txt\
  build/$(MODE)/demo/diffusion/steady_state_continuous_2d_d02_p01_primal_weak_cochain_2d_10_grains_forman_input.txt\
  build/$(MODE)/demo/diffusion/steady_state_continuous_2d_d02_p01_primal_weak_cochain_2d_10_grains_forman_potential.txt\
  | build/$(MODE)/demo/diffusion
	$<\
  --raw $(word 2, $^)\
  --raw $(word 3, $^)\
  --steady-state-primal-weak-raw $(word 4, $^)\
  --raw $(word 5, $^)\
  --raw > $@

build/$(MODE)/demo/diffusion/steady_state_continuous_2d_d02_p01_mixed_weak_cochain_2d_10_grains_forman_input.txt:\
  build/$(MODE)/bin/diffusion_steady_state_discrete_mixed_weak_from_continuous$(.EXE)\
  build/$(MODE)/demo/mesh/2d_10_grains_forman.txt\
  build/$(MODE)/demo/mesh/2d_10_grains_forman_vol.txt\
  build/$(MODE)/obj/src/diffusion_steady_state_continuous_2d_d02_p01$(.OBJ)\
  | build/$(MODE)/demo/diffusion build/$(MODE)/lib/libshared$(.DLL)
	$<\
  --raw $(word 2, $^)\
  --raw $(word 3, $^)\
  $(word 2, $|)\
  diffusion_steady_state_continuous_2d_d02_p01\
  > $@

build/$(MODE)/demo/diffusion/steady_state_continuous_2d_d02_p01_mixed_weak_cochain_2d_10_grains_forman_solution.txt:\
  build/$(MODE)/bin/diffusion_steady_state_discrete_mixed_weak_solve$(.EXE)\
  build/$(MODE)/demo/mesh/2d_10_grains_forman.txt\
  build/$(MODE)/demo/mesh/2d_10_grains_forman_inner.txt\
  build/$(MODE)/demo/diffusion/steady_state_continuous_2d_d02_p01_mixed_weak_cochain_2d_10_grains_forman_input.txt\
  | build/$(MODE)/demo/diffusion
	$<\
  --raw $(word 2, $^)\
  --raw $(word 3, $^)\
  $(word 4, $^)\
  > $@

build/$(MODE)/demo/diffusion/steady_state_continuous_2d_d02_p01_mixed_weak_cochain_2d_10_grains_forman_potential.txt:\
  build/$(MODE)/bin/diffusion_steady_state_discrete_mixed_weak_potential$(.EXE)\
  build/$(MODE)/demo/mesh/2d_10_grains_forman.txt\
  build/$(MODE)/demo/mesh/2d_10_grains_forman_vol.txt\
  build/$(MODE)/demo/diffusion/steady_state_continuous_2d_d02_p01_mixed_weak_cochain_2d_10_grains_forman_input.txt\
  build/$(MODE)/demo/diffusion/steady_state_continuous_2d_d02_p01_mixed_weak_cochain_2d_10_grains_forman_solution.txt\
  | build/$(MODE)/demo/diffusion
	$<\
  --raw $(word 2, $^)\
  --raw $(word 3, $^)\
  $(word 4, $^)\
  $(word 5, $^)\
  > $@
