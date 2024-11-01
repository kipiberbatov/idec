_demo_diffusion_steady_state_continuous_2d_d03_p01 :=\
  build/$(MODE)/demo/diffusion/steady_state_continuous_2d_d03_p01_exact_circular_4_3_forman_potential.txt\
  build/$(MODE)/demo/diffusion/steady_state_continuous_2d_d03_p01_exact_circular_4_3_forman_flow.txt\
  build/$(MODE)/demo/diffusion/steady_state_continuous_2d_d03_p01_primal_weak_cochain_circular_4_3_forman_input.txt\
  build/$(MODE)/demo/diffusion/steady_state_continuous_2d_d03_p01_primal_weak_cochain_circular_4_3_forman_potential.txt\
  build/$(MODE)/demo/diffusion/steady_state_continuous_2d_d03_p01_primal_weak_cochain_circular_4_3_forman_flow.txt\
  build/$(MODE)/demo/diffusion/steady_state_continuous_2d_d03_p01_mixed_weak_cochain_circular_4_3_forman_input.txt\
  build/$(MODE)/demo/diffusion/steady_state_continuous_2d_d03_p01_mixed_weak_cochain_circular_4_3_forman_solution.txt\
  build/$(MODE)/demo/diffusion/steady_state_continuous_2d_d03_p01_mixed_weak_cochain_circular_4_3_forman_potential.txt\
  build/$(MODE)/demo/diffusion/steady_state_continuous_2d_d03_p01_exact_circular_17_10_forman_potential.txt\
  build/$(MODE)/demo/diffusion/steady_state_continuous_2d_d03_p01_exact_circular_17_10_forman_flow.txt\
  build/$(MODE)/demo/diffusion/steady_state_continuous_2d_d03_p01_primal_weak_cochain_circular_17_10_forman_input.txt\
  build/$(MODE)/demo/diffusion/steady_state_continuous_2d_d03_p01_primal_weak_cochain_circular_17_10_forman_potential.txt\
  build/$(MODE)/demo/diffusion/steady_state_continuous_2d_d03_p01_primal_weak_cochain_circular_17_10_forman_flow.txt\
  build/$(MODE)/demo/diffusion/steady_state_continuous_2d_d03_p01_mixed_weak_cochain_circular_17_10_forman_input.txt\
  build/$(MODE)/demo/diffusion/steady_state_continuous_2d_d03_p01_mixed_weak_cochain_circular_17_10_forman_solution.txt\
  build/$(MODE)/demo/diffusion/steady_state_continuous_2d_d03_p01_mixed_weak_cochain_circular_17_10_forman_potential.txt\

build/$(MODE)/demo/diffusion/steady_state_continuous_2d_d03_p01_exact_circular_4_3_forman_potential.txt:\
  build/$(MODE)/bin/diffusion_steady_state_continuous_exact_potential$(.EXE)\
  build/$(MODE)/demo/mesh/circular_4_3_forman.txt\
  build/$(MODE)/obj/src/diffusion_steady_state_continuous_2d_d03_p00$(.OBJ)\
  | build/$(MODE)/demo/diffusion build/$(MODE)/lib/libshared$(.DLL)
	$<\
  --raw $(word 2, $^)\
  $(word 2, $|)\
  diffusion_steady_state_continuous_2d_d03_p00_exact_potential_circular\
  --raw > $@

build/$(MODE)/demo/diffusion/steady_state_continuous_2d_d03_p01_exact_circular_4_3_forman_flow.txt:\
  build/$(MODE)/bin/diffusion_steady_state_continuous_exact_flow$(.EXE)\
  build/$(MODE)/demo/mesh/circular_4_3_forman.txt\
  build/$(MODE)/obj/src/diffusion_steady_state_continuous_2d_d03_p00$(.OBJ)\
  | build/$(MODE)/demo/diffusion build/$(MODE)/lib/libshared$(.DLL)
	$<\
  --raw $(word 2, $^)\
  $(word 2, $|)\
  diffusion_steady_state_continuous_2d_d03_p00_exact_flow_circular\
  --raw > $@

build/$(MODE)/demo/diffusion/steady_state_continuous_2d_d03_p01_primal_weak_cochain_circular_4_3_forman_input.txt:\
  build/$(MODE)/bin/diffusion_steady_state_discrete_primal_weak_from_continuous$(.EXE)\
  build/$(MODE)/demo/mesh/circular_4_3_forman.txt\
  build/$(MODE)/demo/mesh/circular_4_3_forman_vol.txt\
  build/$(MODE)/obj/src/diffusion_steady_state_continuous_2d_d03_p01$(.OBJ)\
  | build/$(MODE)/demo/diffusion build/$(MODE)/lib/libshared$(.DLL)
	$<\
  --raw $(word 2, $^)\
  --raw $(word 3, $^)\
  $(word 2, $|)\
  diffusion_steady_state_continuous_2d_d03_p01\
  > $@

build/$(MODE)/demo/diffusion/steady_state_continuous_2d_d03_p01_primal_weak_cochain_circular_4_3_forman_potential.txt:\
  build/$(MODE)/bin/diffusion_steady_state_discrete_primal_weak_solve$(.EXE)\
  build/$(MODE)/demo/mesh/circular_4_3_forman.txt\
  build/$(MODE)/demo/mesh/circular_4_3_forman_inner.txt\
  build/$(MODE)/demo/diffusion/steady_state_continuous_2d_d03_p01_primal_weak_cochain_circular_4_3_forman_input.txt\
  | build/$(MODE)/demo/diffusion
	$<\
  --raw $(word 2, $^)\
  --raw $(word 3, $^)\
  $(word 4, $^)\
  > $@

build/$(MODE)/demo/diffusion/steady_state_continuous_2d_d03_p01_primal_weak_cochain_circular_4_3_forman_flow.txt:\
  build/$(MODE)/bin/diffusion_steady_state_discrete_primal_flow_from_potential$(.EXE)\
  build/$(MODE)/demo/mesh/circular_4_3_forman.txt\
  build/$(MODE)/demo/mesh/circular_4_3_forman_hodge.txt\
  build/$(MODE)/demo/diffusion/steady_state_continuous_2d_d03_p01_primal_weak_cochain_circular_4_3_forman_input.txt\
  build/$(MODE)/demo/diffusion/steady_state_continuous_2d_d03_p01_primal_weak_cochain_circular_4_3_forman_potential.txt\
  | build/$(MODE)/demo/diffusion
	$<\
  --raw $(word 2, $^)\
  --raw $(word 3, $^)\
  --steady-state-primal-weak-raw $(word 4, $^)\
  --raw $(word 5, $^)\
  --raw > $@

build/$(MODE)/demo/diffusion/steady_state_continuous_2d_d03_p01_mixed_weak_cochain_circular_4_3_forman_input.txt:\
  build/$(MODE)/bin/diffusion_steady_state_discrete_mixed_weak_from_continuous$(.EXE)\
  build/$(MODE)/demo/mesh/circular_4_3_forman.txt\
  build/$(MODE)/demo/mesh/circular_4_3_forman_vol.txt\
  build/$(MODE)/obj/src/diffusion_steady_state_continuous_2d_d03_p01$(.OBJ)\
  | build/$(MODE)/demo/diffusion build/$(MODE)/lib/libshared$(.DLL)
	$<\
  --raw $(word 2, $^)\
  --raw $(word 3, $^)\
  $(word 2, $|)\
  diffusion_steady_state_continuous_2d_d03_p01\
  > $@

build/$(MODE)/demo/diffusion/steady_state_continuous_2d_d03_p01_mixed_weak_cochain_circular_4_3_forman_solution.txt:\
  build/$(MODE)/bin/diffusion_steady_state_discrete_mixed_weak_solve$(.EXE)\
  build/$(MODE)/demo/mesh/circular_4_3_forman.txt\
  build/$(MODE)/demo/mesh/circular_4_3_forman_inner.txt\
  build/$(MODE)/demo/diffusion/steady_state_continuous_2d_d03_p01_mixed_weak_cochain_circular_4_3_forman_input.txt\
  | build/$(MODE)/demo/diffusion
	$<\
  --raw $(word 2, $^)\
  --raw $(word 3, $^)\
  $(word 4, $^)\
  > $@ \
  2> /dev/null

build/$(MODE)/demo/diffusion/steady_state_continuous_2d_d03_p01_mixed_weak_cochain_circular_4_3_forman_potential.txt:\
  build/$(MODE)/bin/diffusion_steady_state_discrete_mixed_weak_temperature$(.EXE)\
  build/$(MODE)/demo/mesh/circular_4_3_forman.txt\
  build/$(MODE)/demo/mesh/circular_4_3_forman_vol.txt\
  build/$(MODE)/demo/diffusion/steady_state_continuous_2d_d03_p01_mixed_weak_cochain_circular_4_3_forman_input.txt\
  build/$(MODE)/demo/diffusion/steady_state_continuous_2d_d03_p01_mixed_weak_cochain_circular_4_3_forman_solution.txt\
  | build/$(MODE)/demo/diffusion
	$<\
  --raw $(word 2, $^)\
  --raw $(word 3, $^)\
  $(word 4, $^)\
  $(word 5, $^)\
  > $@

build/$(MODE)/demo/diffusion/steady_state_continuous_2d_d03_p01_exact_circular_17_10_forman_potential.txt:\
  build/$(MODE)/bin/diffusion_steady_state_continuous_exact_potential$(.EXE)\
  build/$(MODE)/demo/mesh/circular_17_10_forman.txt\
  build/$(MODE)/obj/src/diffusion_steady_state_continuous_2d_d03_p00$(.OBJ)\
  | build/$(MODE)/demo/diffusion build/$(MODE)/lib/libshared$(.DLL)
	$<\
  --raw $(word 2, $^)\
  $(word 2, $|)\
  diffusion_steady_state_continuous_2d_d03_p00_exact_potential_circular\
  --raw > $@

build/$(MODE)/demo/diffusion/steady_state_continuous_2d_d03_p01_exact_circular_17_10_forman_flow.txt:\
  build/$(MODE)/bin/diffusion_steady_state_continuous_exact_flow$(.EXE)\
  build/$(MODE)/demo/mesh/circular_17_10_forman.txt\
  build/$(MODE)/obj/src/diffusion_steady_state_continuous_2d_d03_p00$(.OBJ)\
  | build/$(MODE)/demo/diffusion build/$(MODE)/lib/libshared$(.DLL)
	$<\
  --raw $(word 2, $^)\
  $(word 2, $|)\
  diffusion_steady_state_continuous_2d_d03_p00_exact_flow_circular\
  --raw > $@

build/$(MODE)/demo/diffusion/steady_state_continuous_2d_d03_p01_primal_weak_cochain_circular_17_10_forman_input.txt:\
  build/$(MODE)/bin/diffusion_steady_state_discrete_primal_weak_from_continuous$(.EXE)\
  build/$(MODE)/demo/mesh/circular_17_10_forman.txt\
  build/$(MODE)/demo/mesh/circular_17_10_forman_vol.txt\
  build/$(MODE)/obj/src/diffusion_steady_state_continuous_2d_d03_p01$(.OBJ)\
  | build/$(MODE)/demo/diffusion build/$(MODE)/lib/libshared$(.DLL)
	$<\
  --raw $(word 2, $^)\
  --raw $(word 3, $^)\
  $(word 2, $|)\
  diffusion_steady_state_continuous_2d_d03_p01\
  > $@

build/$(MODE)/demo/diffusion/steady_state_continuous_2d_d03_p01_primal_weak_cochain_circular_17_10_forman_potential.txt:\
  build/$(MODE)/bin/diffusion_steady_state_discrete_primal_weak_solve$(.EXE)\
  build/$(MODE)/demo/mesh/circular_17_10_forman.txt\
  build/$(MODE)/demo/mesh/circular_17_10_forman_inner.txt\
  build/$(MODE)/demo/diffusion/steady_state_continuous_2d_d03_p01_primal_weak_cochain_circular_17_10_forman_input.txt\
  | build/$(MODE)/demo/diffusion
	$<\
  --raw $(word 2, $^)\
  --raw $(word 3, $^)\
  $(word 4, $^)\
  > $@

build/$(MODE)/demo/diffusion/steady_state_continuous_2d_d03_p01_primal_weak_cochain_circular_17_10_forman_flow.txt:\
  build/$(MODE)/bin/diffusion_steady_state_discrete_primal_flow_from_potential$(.EXE)\
  build/$(MODE)/demo/mesh/circular_17_10_forman.txt\
  build/$(MODE)/demo/mesh/circular_17_10_forman_hodge.txt\
  build/$(MODE)/demo/diffusion/steady_state_continuous_2d_d03_p01_primal_weak_cochain_circular_17_10_forman_input.txt\
  build/$(MODE)/demo/diffusion/steady_state_continuous_2d_d03_p01_primal_weak_cochain_circular_17_10_forman_potential.txt\
  | build/$(MODE)/demo/diffusion
	$<\
  --raw $(word 2, $^)\
  --raw $(word 3, $^)\
  --steady-state-primal-weak-raw $(word 4, $^)\
  --raw $(word 5, $^)\
  --raw > $@

build/$(MODE)/demo/diffusion/steady_state_continuous_2d_d03_p01_mixed_weak_cochain_circular_17_10_forman_input.txt:\
  build/$(MODE)/bin/diffusion_steady_state_discrete_mixed_weak_from_continuous$(.EXE)\
  build/$(MODE)/demo/mesh/circular_17_10_forman.txt\
  build/$(MODE)/demo/mesh/circular_17_10_forman_vol.txt\
  build/$(MODE)/obj/src/diffusion_steady_state_continuous_2d_d03_p01$(.OBJ)\
  | build/$(MODE)/demo/diffusion build/$(MODE)/lib/libshared$(.DLL)
	$<\
  --raw $(word 2, $^)\
  --raw $(word 3, $^)\
  $(word 2, $|)\
  diffusion_steady_state_continuous_2d_d03_p01\
  > $@

build/$(MODE)/demo/diffusion/steady_state_continuous_2d_d03_p01_mixed_weak_cochain_circular_17_10_forman_solution.txt:\
  build/$(MODE)/bin/diffusion_steady_state_discrete_mixed_weak_solve$(.EXE)\
  build/$(MODE)/demo/mesh/circular_17_10_forman.txt\
  build/$(MODE)/demo/mesh/circular_17_10_forman_inner.txt\
  build/$(MODE)/demo/diffusion/steady_state_continuous_2d_d03_p01_mixed_weak_cochain_circular_17_10_forman_input.txt\
  | build/$(MODE)/demo/diffusion
	$<\
  --raw $(word 2, $^)\
  --raw $(word 3, $^)\
  $(word 4, $^)\
  > $@ \
  2> /dev/null

build/$(MODE)/demo/diffusion/steady_state_continuous_2d_d03_p01_mixed_weak_cochain_circular_17_10_forman_potential.txt:\
  build/$(MODE)/bin/diffusion_steady_state_discrete_mixed_weak_temperature$(.EXE)\
  build/$(MODE)/demo/mesh/circular_17_10_forman.txt\
  build/$(MODE)/demo/mesh/circular_17_10_forman_vol.txt\
  build/$(MODE)/demo/diffusion/steady_state_continuous_2d_d03_p01_mixed_weak_cochain_circular_17_10_forman_input.txt\
  build/$(MODE)/demo/diffusion/steady_state_continuous_2d_d03_p01_mixed_weak_cochain_circular_17_10_forman_solution.txt\
  | build/$(MODE)/demo/diffusion
	$<\
  --raw $(word 2, $^)\
  --raw $(word 3, $^)\
  $(word 4, $^)\
  $(word 5, $^)\
  > $@
