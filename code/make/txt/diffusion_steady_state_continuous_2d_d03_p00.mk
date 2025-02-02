_txt_diffusion_steady_state_continuous_2d_d03_p00 :=\
  build/$(MODE)/txt/diffusion/steady_state_continuous_2d_d03_p00_exact_circular_4_3_forman_potential.txt\
  build/$(MODE)/txt/diffusion/steady_state_continuous_2d_d03_p00_exact_circular_4_3_forman_flow.txt\
  build/$(MODE)/txt/diffusion/steady_state_continuous_2d_d03_p00_primal_weak_cochain_circular_4_3_forman_input.txt\
  build/$(MODE)/txt/diffusion/steady_state_continuous_2d_d03_p00_primal_weak_cochain_circular_4_3_forman_potential.txt\
  build/$(MODE)/txt/diffusion/steady_state_continuous_2d_d03_p00_primal_weak_cochain_circular_4_3_forman_flow.txt\
  build/$(MODE)/txt/diffusion/steady_state_continuous_2d_d03_p00_mixed_weak_cochain_circular_4_3_forman_input.txt\
  build/$(MODE)/txt/diffusion/steady_state_continuous_2d_d03_p00_mixed_weak_cochain_circular_4_3_forman_solution.txt\
  build/$(MODE)/txt/diffusion/steady_state_continuous_2d_d03_p00_mixed_weak_cochain_circular_4_3_forman_potential.txt\
  build/$(MODE)/txt/diffusion/steady_state_continuous_2d_d03_p00_exact_circular_18_10_forman_potential.txt\
  build/$(MODE)/txt/diffusion/steady_state_continuous_2d_d03_p00_exact_circular_18_10_forman_flow.txt\
  build/$(MODE)/txt/diffusion/steady_state_continuous_2d_d03_p00_primal_weak_cochain_circular_18_10_forman_input.txt\
  build/$(MODE)/txt/diffusion/steady_state_continuous_2d_d03_p00_primal_weak_cochain_circular_18_10_forman_potential.txt\
  build/$(MODE)/txt/diffusion/steady_state_continuous_2d_d03_p00_primal_weak_cochain_circular_18_10_forman_flow.txt\
  build/$(MODE)/txt/diffusion/steady_state_continuous_2d_d03_p00_mixed_weak_cochain_circular_18_10_forman_input.txt\
  build/$(MODE)/txt/diffusion/steady_state_continuous_2d_d03_p00_mixed_weak_cochain_circular_18_10_forman_solution.txt\
  build/$(MODE)/txt/diffusion/steady_state_continuous_2d_d03_p00_mixed_weak_cochain_circular_18_10_forman_potential.txt\

build/$(MODE)/txt/diffusion/steady_state_continuous_2d_d03_p00_exact_circular_4_3_forman_potential.txt:\
  build/$(MODE)/bin/diffusion_steady_state_continuous_exact_potential$(.EXE)\
  build/$(MODE)/txt/mesh/circular_4_3_forman.txt\
  build/$(MODE)/obj/src/diffusion_steady_state_continuous_2d_d03_p00$(.OBJ)\
  | build/$(MODE)/txt/diffusion build/$(MODE)/lib/libshared$(.DLL)
	$<\
  --raw $(word 2, $^)\
  $(word 2, $|)\
  diffusion_steady_state_continuous_2d_d03_p00_exact_potential_circular\
  --raw > $@

build/$(MODE)/txt/diffusion/steady_state_continuous_2d_d03_p00_exact_circular_4_3_forman_flow.txt:\
  build/$(MODE)/bin/diffusion_steady_state_continuous_exact_flow$(.EXE)\
  build/$(MODE)/txt/mesh/circular_4_3_forman.txt\
  build/$(MODE)/obj/src/diffusion_steady_state_continuous_2d_d03_p00$(.OBJ)\
  | build/$(MODE)/txt/diffusion build/$(MODE)/lib/libshared$(.DLL)
	$<\
  --raw $(word 2, $^)\
  $(word 2, $|)\
  diffusion_steady_state_continuous_2d_d03_p00_exact_flow_circular\
  --raw > $@

build/$(MODE)/txt/diffusion/steady_state_continuous_2d_d03_p00_primal_weak_cochain_circular_4_3_forman_input.txt:\
  build/$(MODE)/bin/diffusion_steady_state_discrete_primal_weak_from_continuous$(.EXE)\
  build/$(MODE)/txt/mesh/circular_4_3_forman.txt\
  build/$(MODE)/txt/mesh/circular_4_3_forman_vol.txt\
  build/$(MODE)/obj/src/diffusion_steady_state_continuous_2d_d03_p00$(.OBJ)\
  | build/$(MODE)/txt/diffusion build/$(MODE)/lib/libshared$(.DLL)
	$<\
  --raw $(word 2, $^)\
  --raw $(word 3, $^)\
  $(word 2, $|)\
  diffusion_steady_state_continuous_2d_d03_p00\
  > $@

build/$(MODE)/txt/diffusion/steady_state_continuous_2d_d03_p00_primal_weak_cochain_circular_4_3_forman_potential.txt:\
  build/$(MODE)/bin/diffusion_steady_state_discrete_primal_weak_solve$(.EXE)\
  build/$(MODE)/txt/mesh/circular_4_3_forman.txt\
  build/$(MODE)/txt/mesh/circular_4_3_forman_inner.txt\
  build/$(MODE)/txt/diffusion/steady_state_continuous_2d_d03_p00_primal_weak_cochain_circular_4_3_forman_input.txt\
  | build/$(MODE)/txt/diffusion
	$<\
  --raw $(word 2, $^)\
  --raw $(word 3, $^)\
  $(word 4, $^)\
  > $@

build/$(MODE)/txt/diffusion/steady_state_continuous_2d_d03_p00_primal_weak_cochain_circular_4_3_forman_flow.txt:\
  build/$(MODE)/bin/diffusion_steady_state_discrete_flow_from_potential$(.EXE)\
  build/$(MODE)/txt/mesh/circular_4_3_forman.txt\
  build/$(MODE)/txt/mesh/circular_4_3_forman_hodge.txt\
  build/$(MODE)/txt/diffusion/steady_state_continuous_2d_d03_p00_primal_weak_cochain_circular_4_3_forman_input.txt\
  build/$(MODE)/txt/diffusion/steady_state_continuous_2d_d03_p00_primal_weak_cochain_circular_4_3_forman_potential.txt\
  | build/$(MODE)/txt/diffusion
	$<\
  --raw $(word 2, $^)\
  --raw $(word 3, $^)\
  --steady-state-primal-weak-raw $(word 4, $^)\
  --raw $(word 5, $^)\
  --raw > $@

build/$(MODE)/txt/diffusion/steady_state_continuous_2d_d03_p00_mixed_weak_cochain_circular_4_3_forman_input.txt:\
  build/$(MODE)/bin/diffusion_steady_state_discrete_mixed_weak_from_continuous$(.EXE)\
  build/$(MODE)/txt/mesh/circular_4_3_forman.txt\
  build/$(MODE)/txt/mesh/circular_4_3_forman_vol.txt\
  build/$(MODE)/obj/src/diffusion_steady_state_continuous_2d_d03_p00$(.OBJ)\
  | build/$(MODE)/txt/diffusion build/$(MODE)/lib/libshared$(.DLL)
	$<\
  --raw $(word 2, $^)\
  --raw $(word 3, $^)\
  $(word 2, $|)\
  diffusion_steady_state_continuous_2d_d03_p00\
  > $@

build/$(MODE)/txt/diffusion/steady_state_continuous_2d_d03_p00_mixed_weak_cochain_circular_4_3_forman_solution.txt:\
  build/$(MODE)/bin/diffusion_steady_state_discrete_mixed_weak_solve$(.EXE)\
  build/$(MODE)/txt/mesh/circular_4_3_forman.txt\
  build/$(MODE)/txt/mesh/circular_4_3_forman_inner.txt\
  build/$(MODE)/txt/diffusion/steady_state_continuous_2d_d03_p00_mixed_weak_cochain_circular_4_3_forman_input.txt\
  | build/$(MODE)/txt/diffusion
	$<\
  --raw $(word 2, $^)\
  --raw $(word 3, $^)\
  $(word 4, $^)\
  > $@

build/$(MODE)/txt/diffusion/steady_state_continuous_2d_d03_p00_mixed_weak_cochain_circular_4_3_forman_potential.txt:\
  build/$(MODE)/bin/diffusion_steady_state_discrete_mixed_weak_potential$(.EXE)\
  build/$(MODE)/txt/mesh/circular_4_3_forman.txt\
  build/$(MODE)/txt/mesh/circular_4_3_forman_vol.txt\
  build/$(MODE)/txt/diffusion/steady_state_continuous_2d_d03_p00_mixed_weak_cochain_circular_4_3_forman_input.txt\
  build/$(MODE)/txt/diffusion/steady_state_continuous_2d_d03_p00_mixed_weak_cochain_circular_4_3_forman_solution.txt\
  | build/$(MODE)/txt/diffusion
	$<\
  --raw $(word 2, $^)\
  --raw $(word 3, $^)\
  $(word 4, $^)\
  $(word 5, $^)\
  > $@

build/$(MODE)/txt/diffusion/steady_state_continuous_2d_d03_p00_exact_circular_18_10_forman_potential.txt:\
  build/$(MODE)/bin/diffusion_steady_state_continuous_exact_potential$(.EXE)\
  build/$(MODE)/txt/mesh/circular_18_10_forman.txt\
  build/$(MODE)/obj/src/diffusion_steady_state_continuous_2d_d03_p00$(.OBJ)\
  | build/$(MODE)/txt/diffusion build/$(MODE)/lib/libshared$(.DLL)
	$<\
  --raw $(word 2, $^)\
  $(word 2, $|)\
  diffusion_steady_state_continuous_2d_d03_p00_exact_potential_circular\
  --raw > $@

build/$(MODE)/txt/diffusion/steady_state_continuous_2d_d03_p00_exact_circular_18_10_forman_flow.txt:\
  build/$(MODE)/bin/diffusion_steady_state_continuous_exact_flow$(.EXE)\
  build/$(MODE)/txt/mesh/circular_18_10_forman.txt\
  build/$(MODE)/obj/src/diffusion_steady_state_continuous_2d_d03_p00$(.OBJ)\
  | build/$(MODE)/txt/diffusion build/$(MODE)/lib/libshared$(.DLL)
	$<\
  --raw $(word 2, $^)\
  $(word 2, $|)\
  diffusion_steady_state_continuous_2d_d03_p00_exact_flow_circular\
  --raw > $@

build/$(MODE)/txt/diffusion/steady_state_continuous_2d_d03_p00_primal_weak_cochain_circular_18_10_forman_input.txt:\
  build/$(MODE)/bin/diffusion_steady_state_discrete_primal_weak_from_continuous$(.EXE)\
  build/$(MODE)/txt/mesh/circular_18_10_forman.txt\
  build/$(MODE)/txt/mesh/circular_18_10_forman_vol.txt\
  build/$(MODE)/obj/src/diffusion_steady_state_continuous_2d_d03_p00$(.OBJ)\
  | build/$(MODE)/txt/diffusion build/$(MODE)/lib/libshared$(.DLL)
	$<\
  --raw $(word 2, $^)\
  --raw $(word 3, $^)\
  $(word 2, $|)\
  diffusion_steady_state_continuous_2d_d03_p00\
  > $@

build/$(MODE)/txt/diffusion/steady_state_continuous_2d_d03_p00_primal_weak_cochain_circular_18_10_forman_potential.txt:\
  build/$(MODE)/bin/diffusion_steady_state_discrete_primal_weak_solve$(.EXE)\
  build/$(MODE)/txt/mesh/circular_18_10_forman.txt\
  build/$(MODE)/txt/mesh/circular_18_10_forman_inner.txt\
  build/$(MODE)/txt/diffusion/steady_state_continuous_2d_d03_p00_primal_weak_cochain_circular_18_10_forman_input.txt\
  | build/$(MODE)/txt/diffusion
	$<\
  --raw $(word 2, $^)\
  --raw $(word 3, $^)\
  $(word 4, $^)\
  > $@

build/$(MODE)/txt/diffusion/steady_state_continuous_2d_d03_p00_primal_weak_cochain_circular_18_10_forman_flow.txt:\
  build/$(MODE)/bin/diffusion_steady_state_discrete_flow_from_potential$(.EXE)\
  build/$(MODE)/txt/mesh/circular_18_10_forman.txt\
  build/$(MODE)/txt/mesh/circular_18_10_forman_hodge.txt\
  build/$(MODE)/txt/diffusion/steady_state_continuous_2d_d03_p00_primal_weak_cochain_circular_18_10_forman_input.txt\
  build/$(MODE)/txt/diffusion/steady_state_continuous_2d_d03_p00_primal_weak_cochain_circular_18_10_forman_potential.txt\
  | build/$(MODE)/txt/diffusion
	$<\
  --raw $(word 2, $^)\
  --raw $(word 3, $^)\
  --steady-state-primal-weak-raw $(word 4, $^)\
  --raw $(word 5, $^)\
  --raw > $@

build/$(MODE)/txt/diffusion/steady_state_continuous_2d_d03_p00_mixed_weak_cochain_circular_18_10_forman_input.txt:\
  build/$(MODE)/bin/diffusion_steady_state_discrete_mixed_weak_from_continuous$(.EXE)\
  build/$(MODE)/txt/mesh/circular_18_10_forman.txt\
  build/$(MODE)/txt/mesh/circular_18_10_forman_vol.txt\
  build/$(MODE)/obj/src/diffusion_steady_state_continuous_2d_d03_p00$(.OBJ)\
  | build/$(MODE)/txt/diffusion build/$(MODE)/lib/libshared$(.DLL)
	$<\
  --raw $(word 2, $^)\
  --raw $(word 3, $^)\
  $(word 2, $|)\
  diffusion_steady_state_continuous_2d_d03_p00\
  > $@

build/$(MODE)/txt/diffusion/steady_state_continuous_2d_d03_p00_mixed_weak_cochain_circular_18_10_forman_solution.txt:\
  build/$(MODE)/bin/diffusion_steady_state_discrete_mixed_weak_solve$(.EXE)\
  build/$(MODE)/txt/mesh/circular_18_10_forman.txt\
  build/$(MODE)/txt/mesh/circular_18_10_forman_inner.txt\
  build/$(MODE)/txt/diffusion/steady_state_continuous_2d_d03_p00_mixed_weak_cochain_circular_18_10_forman_input.txt\
  | build/$(MODE)/txt/diffusion
	$<\
  --raw $(word 2, $^)\
  --raw $(word 3, $^)\
  $(word 4, $^)\
  > $@

build/$(MODE)/txt/diffusion/steady_state_continuous_2d_d03_p00_mixed_weak_cochain_circular_18_10_forman_potential.txt:\
  build/$(MODE)/bin/diffusion_steady_state_discrete_mixed_weak_potential$(.EXE)\
  build/$(MODE)/txt/mesh/circular_18_10_forman.txt\
  build/$(MODE)/txt/mesh/circular_18_10_forman_vol.txt\
  build/$(MODE)/txt/diffusion/steady_state_continuous_2d_d03_p00_mixed_weak_cochain_circular_18_10_forman_input.txt\
  build/$(MODE)/txt/diffusion/steady_state_continuous_2d_d03_p00_mixed_weak_cochain_circular_18_10_forman_solution.txt\
  | build/$(MODE)/txt/diffusion
	$<\
  --raw $(word 2, $^)\
  --raw $(word 3, $^)\
  $(word 4, $^)\
  $(word 5, $^)\
  > $@
