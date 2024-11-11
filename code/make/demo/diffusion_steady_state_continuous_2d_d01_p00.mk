_demo_diffusion_steady_state_continuous_2d_d01_p00 :=\
  build/$(MODE)/demo/diffusion/steady_state_continuous_2d_d01_p00_exact_square_8_potential.txt\
  build/$(MODE)/demo/diffusion/steady_state_continuous_2d_d01_p00_exact_square_8_flow.txt\
  build/$(MODE)/demo/diffusion/steady_state_continuous_2d_d01_p00_primal_strong_cochain_square_8_input.txt\
  build/$(MODE)/demo/diffusion/steady_state_continuous_2d_d01_p00_primal_strong_cochain_square_8_potential.txt\
  build/$(MODE)/demo/diffusion/steady_state_continuous_2d_d01_p00_primal_strong_cochain_square_8_flow.txt\
  build/$(MODE)/demo/diffusion/steady_state_continuous_2d_d01_p00_primal_weak_cochain_square_8_input.txt\
  build/$(MODE)/demo/diffusion/steady_state_continuous_2d_d01_p00_primal_weak_cochain_square_8_potential.txt\
  build/$(MODE)/demo/diffusion/steady_state_continuous_2d_d01_p00_primal_weak_cochain_square_8_flow.txt\
  build/$(MODE)/demo/diffusion/steady_state_continuous_2d_d01_p00_mixed_weak_cochain_square_8_input.txt\
  build/$(MODE)/demo/diffusion/steady_state_continuous_2d_d01_p00_mixed_weak_cochain_square_8_solution.txt\
  build/$(MODE)/demo/diffusion/steady_state_continuous_2d_d01_p00_mixed_weak_cochain_square_8_potential.txt\

build/$(MODE)/demo/diffusion/steady_state_continuous_2d_d01_p00_exact_square_8_potential.txt:\
  build/$(MODE)/bin/diffusion_steady_state_continuous_exact_potential$(.EXE)\
  build/$(MODE)/demo/mesh/square_8.txt\
  build/$(MODE)/obj/src/diffusion_steady_state_continuous_2d_d01_p00$(.OBJ)\
  | build/$(MODE)/demo/diffusion build/$(MODE)/lib/libshared$(.DLL)
	$<\
  --raw $(word 2, $^)\
  $(word 2, $|)\
  diffusion_steady_state_continuous_2d_d01_p00_potential\
  --raw > $@

build/$(MODE)/demo/diffusion/steady_state_continuous_2d_d01_p00_exact_square_8_flow.txt:\
  build/$(MODE)/bin/diffusion_steady_state_continuous_exact_flow$(.EXE)\
  build/$(MODE)/demo/mesh/square_8.txt\
  build/$(MODE)/obj/src/diffusion_steady_state_continuous_2d_d01_p00$(.OBJ)\
  | build/$(MODE)/demo/diffusion build/$(MODE)/lib/libshared$(.DLL)
	$<\
  --raw $(word 2, $^)\
  $(word 2, $|)\
  diffusion_steady_state_continuous_2d_d01_p00_flow\
  --raw > $@

build/$(MODE)/demo/diffusion/steady_state_continuous_2d_d01_p00_primal_strong_cochain_square_8_input.txt:\
  build/$(MODE)/bin/diffusion_steady_state_discrete_primal_strong_from_continuous$(.EXE)\
  build/$(MODE)/demo/mesh/square_8.txt\
  build/$(MODE)/obj/src/diffusion_steady_state_continuous_2d_d01_p00$(.OBJ)\
  | build/$(MODE)/demo/diffusion build/$(MODE)/lib/libshared$(.DLL)
	$<\
  --raw $(word 2, $^)\
  $(word 2, $|)\
  diffusion_steady_state_continuous_2d_d01_p00\
  > $@

build/$(MODE)/demo/diffusion/steady_state_continuous_2d_d01_p00_primal_strong_cochain_square_8_potential.txt:\
  build/$(MODE)/bin/diffusion_steady_state_discrete_primal_strong_solve$(.EXE)\
  build/$(MODE)/demo/mesh/square_8.txt\
  build/$(MODE)/demo/mesh/square_8_cbd.txt\
  build/$(MODE)/demo/mesh/square_8_cbd_star.txt\
  build/$(MODE)/demo/diffusion/steady_state_continuous_2d_d01_p00_primal_strong_cochain_square_8_input.txt\
  | build/$(MODE)/demo/diffusion
	$<\
  --raw $(word 2, $^)\
  $(word 3, $^)\
  $(word 4, $^)\
  $(word 5, $^)\
  > $@

build/$(MODE)/demo/diffusion/steady_state_continuous_2d_d01_p00_primal_strong_cochain_square_8_flow.txt:\
  build/$(MODE)/bin/diffusion_steady_state_discrete_primal_flow_from_potential$(.EXE)\
  build/$(MODE)/demo/mesh/square_8.txt\
  build/$(MODE)/demo/mesh/square_8_hodge.txt\
  build/$(MODE)/demo/diffusion/steady_state_continuous_2d_d01_p00_primal_strong_cochain_square_8_input.txt\
  build/$(MODE)/demo/diffusion/steady_state_continuous_2d_d01_p00_primal_strong_cochain_square_8_potential.txt\
  | build/$(MODE)/demo/diffusion
	$<\
  --raw $(word 2, $^)\
  --raw $(word 3, $^)\
  --steady-state-primal-strong-raw $(word 4, $^)\
  --raw $(word 5, $^)\
  --raw > $@

build/$(MODE)/demo/diffusion/steady_state_continuous_2d_d01_p00_primal_weak_cochain_square_8_input.txt:\
  build/$(MODE)/bin/diffusion_steady_state_discrete_primal_weak_from_continuous$(.EXE)\
  build/$(MODE)/demo/mesh/square_8.txt\
  build/$(MODE)/demo/mesh/square_8_vol.txt\
  build/$(MODE)/obj/src/diffusion_steady_state_continuous_2d_d01_p00$(.OBJ)\
  | build/$(MODE)/demo/diffusion build/$(MODE)/lib/libshared$(.DLL)
	$<\
  --raw $(word 2, $^)\
  --raw $(word 3, $^)\
  $(word 2, $|)\
  diffusion_steady_state_continuous_2d_d01_p00\
  > $@

build/$(MODE)/demo/diffusion/steady_state_continuous_2d_d01_p00_primal_weak_cochain_square_8_potential.txt:\
  build/$(MODE)/bin/diffusion_steady_state_discrete_primal_weak_solve$(.EXE)\
  build/$(MODE)/demo/mesh/square_8.txt\
  build/$(MODE)/demo/mesh/square_8_inner.txt\
  build/$(MODE)/demo/diffusion/steady_state_continuous_2d_d01_p00_primal_weak_cochain_square_8_input.txt\
  | build/$(MODE)/demo/diffusion
	$<\
  --raw $(word 2, $^)\
  --raw $(word 3, $^)\
  $(word 4, $^)\
  > $@

build/$(MODE)/demo/diffusion/steady_state_continuous_2d_d01_p00_primal_weak_cochain_square_8_flow.txt:\
  build/$(MODE)/bin/diffusion_steady_state_discrete_primal_flow_from_potential$(.EXE)\
  build/$(MODE)/demo/mesh/square_8.txt\
  build/$(MODE)/demo/mesh/square_8_hodge.txt\
  build/$(MODE)/demo/diffusion/steady_state_continuous_2d_d01_p00_primal_weak_cochain_square_8_input.txt\
  build/$(MODE)/demo/diffusion/steady_state_continuous_2d_d01_p00_primal_weak_cochain_square_8_potential.txt\
  | build/$(MODE)/demo/diffusion
	$<\
  --raw $(word 2, $^)\
  --raw $(word 3, $^)\
  --steady-state-primal-weak-raw $(word 4, $^)\
  --raw $(word 5, $^)\
  --raw > $@

build/$(MODE)/demo/diffusion/steady_state_continuous_2d_d01_p00_mixed_weak_cochain_square_8_input.txt:\
  build/$(MODE)/bin/diffusion_steady_state_discrete_mixed_weak_from_continuous$(.EXE)\
  build/$(MODE)/demo/mesh/square_8.txt\
  build/$(MODE)/demo/mesh/square_8_vol.txt\
  build/$(MODE)/obj/src/diffusion_steady_state_continuous_2d_d01_p00$(.OBJ)\
  | build/$(MODE)/demo/diffusion build/$(MODE)/lib/libshared$(.DLL)
	$<\
  --raw $(word 2, $^)\
  --raw $(word 3, $^)\
  $(word 2, $|)\
  diffusion_steady_state_continuous_2d_d01_p00\
  > $@

build/$(MODE)/demo/diffusion/steady_state_continuous_2d_d01_p00_mixed_weak_cochain_square_8_solution.txt:\
  build/$(MODE)/bin/diffusion_steady_state_discrete_mixed_weak_solve$(.EXE)\
  build/$(MODE)/demo/mesh/square_8.txt\
  build/$(MODE)/demo/mesh/square_8_inner.txt\
  build/$(MODE)/demo/diffusion/steady_state_continuous_2d_d01_p00_mixed_weak_cochain_square_8_input.txt\
  | build/$(MODE)/demo/diffusion
	$<\
  --raw $(word 2, $^)\
  --raw $(word 3, $^)\
  $(word 4, $^)\
  > $@

build/$(MODE)/demo/diffusion/steady_state_continuous_2d_d01_p00_mixed_weak_cochain_square_8_potential.txt:\
  build/$(MODE)/bin/diffusion_steady_state_discrete_mixed_weak_temperature$(.EXE)\
  build/$(MODE)/demo/mesh/square_8.txt\
  build/$(MODE)/demo/mesh/square_8_vol.txt\
  build/$(MODE)/demo/diffusion/steady_state_continuous_2d_d01_p00_mixed_weak_cochain_square_8_input.txt\
  build/$(MODE)/demo/diffusion/steady_state_continuous_2d_d01_p00_mixed_weak_cochain_square_8_solution.txt\
  | build/$(MODE)/demo/diffusion
	$<\
  --raw $(word 2, $^)\
  --raw $(word 3, $^)\
  $(word 4, $^)\
  $(word 5, $^)\
  > $@
