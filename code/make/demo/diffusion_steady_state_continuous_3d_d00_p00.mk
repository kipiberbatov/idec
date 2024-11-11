_demo_diffusion_steady_state_continuous_3d_d00_p00 :=\
  build/$(MODE)/demo/diffusion/steady_state_continuous_3d_d00_p00_primal_strong_cochain_brick_3d_2_forman_input.txt\
  build/$(MODE)/demo/diffusion/steady_state_continuous_3d_d00_p00_primal_strong_cochain_brick_3d_2_forman_potential.txt\
  build/$(MODE)/demo/diffusion/steady_state_continuous_3d_d00_p00_primal_strong_cochain_brick_3d_2_forman_flow.txt\
  build/$(MODE)/demo/diffusion/steady_state_continuous_3d_d00_p00_primal_weak_cochain_brick_3d_2_forman_input.txt\
  build/$(MODE)/demo/diffusion/steady_state_continuous_3d_d00_p00_primal_weak_cochain_brick_3d_2_forman_potential.txt\
  build/$(MODE)/demo/diffusion/steady_state_continuous_3d_d00_p00_primal_weak_cochain_brick_3d_2_forman_flow.txt\
  build/$(MODE)/demo/diffusion/steady_state_continuous_3d_d00_p00_mixed_weak_cochain_brick_3d_2_forman_input.txt\
  build/$(MODE)/demo/diffusion/steady_state_continuous_3d_d00_p00_mixed_weak_cochain_brick_3d_2_forman_solution.txt\
  build/$(MODE)/demo/diffusion/steady_state_continuous_3d_d00_p00_mixed_weak_cochain_brick_3d_2_forman_potential.txt\

build/$(MODE)/demo/diffusion/steady_state_continuous_3d_d00_p00_primal_strong_cochain_brick_3d_2_forman_input.txt:\
  build/$(MODE)/bin/diffusion_steady_state_discrete_primal_strong_from_continuous$(.EXE)\
  build/$(MODE)/demo/mesh/brick_3d_2_forman.txt\
  build/$(MODE)/obj/src/diffusion_steady_state_continuous_3d_d00_p00$(.OBJ)\
  | build/$(MODE)/demo/diffusion build/$(MODE)/lib/libshared$(.DLL)
	$<\
  --raw $(word 2, $^)\
  $(word 2, $|)\
  diffusion_steady_state_continuous_3d_d00_p00\
  > $@

build/$(MODE)/demo/diffusion/steady_state_continuous_3d_d00_p00_primal_strong_cochain_brick_3d_2_forman_potential.txt:\
  build/$(MODE)/bin/diffusion_steady_state_discrete_primal_strong_solve$(.EXE)\
  build/$(MODE)/demo/mesh/brick_3d_2_forman.txt\
  build/$(MODE)/demo/mesh/brick_3d_2_forman_cbd.txt\
  build/$(MODE)/demo/mesh/brick_3d_2_forman_cbd_star.txt\
  build/$(MODE)/demo/diffusion/steady_state_continuous_3d_d00_p00_primal_strong_cochain_brick_3d_2_forman_input.txt\
  | build/$(MODE)/demo/diffusion
	$<\
  --raw $(word 2, $^)\
  $(word 3, $^)\
  $(word 4, $^)\
  $(word 5, $^)\
  > $@

build/$(MODE)/demo/diffusion/steady_state_continuous_3d_d00_p00_primal_strong_cochain_brick_3d_2_forman_flow.txt:\
  build/$(MODE)/bin/diffusion_steady_state_discrete_primal_flow_from_potential$(.EXE)\
  build/$(MODE)/demo/mesh/brick_3d_2_forman.txt\
  build/$(MODE)/demo/mesh/brick_3d_2_forman_hodge.txt\
  build/$(MODE)/demo/diffusion/steady_state_continuous_3d_d00_p00_primal_strong_cochain_brick_3d_2_forman_input.txt\
  build/$(MODE)/demo/diffusion/steady_state_continuous_3d_d00_p00_primal_strong_cochain_brick_3d_2_forman_potential.txt\
  | build/$(MODE)/demo/diffusion
	$<\
  --raw $(word 2, $^)\
  --raw $(word 3, $^)\
  --steady-state-primal-strong-raw $(word 4, $^)\
  --raw $(word 5, $^)\
  --raw > $@

build/$(MODE)/demo/diffusion/steady_state_continuous_3d_d00_p00_primal_weak_cochain_brick_3d_2_forman_input.txt:\
  build/$(MODE)/bin/diffusion_steady_state_discrete_primal_weak_from_continuous$(.EXE)\
  build/$(MODE)/demo/mesh/brick_3d_2_forman.txt\
  build/$(MODE)/demo/mesh/brick_3d_2_forman_vol.txt\
  build/$(MODE)/obj/src/diffusion_steady_state_continuous_3d_d00_p00$(.OBJ)\
  | build/$(MODE)/demo/diffusion build/$(MODE)/lib/libshared$(.DLL)
	$<\
  --raw $(word 2, $^)\
  --raw $(word 3, $^)\
  $(word 2, $|)\
  diffusion_steady_state_continuous_3d_d00_p00\
  > $@

build/$(MODE)/demo/diffusion/steady_state_continuous_3d_d00_p00_primal_weak_cochain_brick_3d_2_forman_potential.txt:\
  build/$(MODE)/bin/diffusion_steady_state_discrete_primal_weak_solve$(.EXE)\
  build/$(MODE)/demo/mesh/brick_3d_2_forman.txt\
  build/$(MODE)/demo/mesh/brick_3d_2_forman_inner.txt\
  build/$(MODE)/demo/diffusion/steady_state_continuous_3d_d00_p00_primal_weak_cochain_brick_3d_2_forman_input.txt\
  | build/$(MODE)/demo/diffusion
	$<\
  --raw $(word 2, $^)\
  --raw $(word 3, $^)\
  $(word 4, $^)\
  > $@

build/$(MODE)/demo/diffusion/steady_state_continuous_3d_d00_p00_primal_weak_cochain_brick_3d_2_forman_flow.txt:\
  build/$(MODE)/bin/diffusion_steady_state_discrete_primal_flow_from_potential$(.EXE)\
  build/$(MODE)/demo/mesh/brick_3d_2_forman.txt\
  build/$(MODE)/demo/mesh/brick_3d_2_forman_hodge.txt\
  build/$(MODE)/demo/diffusion/steady_state_continuous_3d_d00_p00_primal_weak_cochain_brick_3d_2_forman_input.txt\
  build/$(MODE)/demo/diffusion/steady_state_continuous_3d_d00_p00_primal_weak_cochain_brick_3d_2_forman_potential.txt\
  | build/$(MODE)/demo/diffusion
	$<\
  --raw $(word 2, $^)\
  --raw $(word 3, $^)\
  --steady-state-primal-weak-raw $(word 4, $^)\
  --raw $(word 5, $^)\
  --raw > $@

build/$(MODE)/demo/diffusion/steady_state_continuous_3d_d00_p00_mixed_weak_cochain_brick_3d_2_forman_input.txt:\
  build/$(MODE)/bin/diffusion_steady_state_discrete_mixed_weak_from_continuous$(.EXE)\
  build/$(MODE)/demo/mesh/brick_3d_2_forman.txt\
  build/$(MODE)/demo/mesh/brick_3d_2_forman_vol.txt\
  build/$(MODE)/obj/src/diffusion_steady_state_continuous_3d_d00_p00$(.OBJ)\
  | build/$(MODE)/demo/diffusion build/$(MODE)/lib/libshared$(.DLL)
	$<\
  --raw $(word 2, $^)\
  --raw $(word 3, $^)\
  $(word 2, $|)\
  diffusion_steady_state_continuous_3d_d00_p00\
  > $@

build/$(MODE)/demo/diffusion/steady_state_continuous_3d_d00_p00_mixed_weak_cochain_brick_3d_2_forman_solution.txt:\
  build/$(MODE)/bin/diffusion_steady_state_discrete_mixed_weak_solve$(.EXE)\
  build/$(MODE)/demo/mesh/brick_3d_2_forman.txt\
  build/$(MODE)/demo/mesh/brick_3d_2_forman_inner.txt\
  build/$(MODE)/demo/diffusion/steady_state_continuous_3d_d00_p00_mixed_weak_cochain_brick_3d_2_forman_input.txt\
  | build/$(MODE)/demo/diffusion
	$<\
  --raw $(word 2, $^)\
  --raw $(word 3, $^)\
  $(word 4, $^)\
  > $@

build/$(MODE)/demo/diffusion/steady_state_continuous_3d_d00_p00_mixed_weak_cochain_brick_3d_2_forman_potential.txt:\
  build/$(MODE)/bin/diffusion_steady_state_discrete_mixed_weak_temperature$(.EXE)\
  build/$(MODE)/demo/mesh/brick_3d_2_forman.txt\
  build/$(MODE)/demo/mesh/brick_3d_2_forman_vol.txt\
  build/$(MODE)/demo/diffusion/steady_state_continuous_3d_d00_p00_mixed_weak_cochain_brick_3d_2_forman_input.txt\
  build/$(MODE)/demo/diffusion/steady_state_continuous_3d_d00_p00_mixed_weak_cochain_brick_3d_2_forman_solution.txt\
  | build/$(MODE)/demo/diffusion
	$<\
  --raw $(word 2, $^)\
  --raw $(word 3, $^)\
  $(word 4, $^)\
  $(word 5, $^)\
  > $@
