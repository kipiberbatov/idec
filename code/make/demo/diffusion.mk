.PHONY: demo_diffusion
demo_diffusion:\
  bin_diffusion\
  demo_diffusion_2d\
  demo_diffusion_3d\
  | build/$(MODE)/demo/diffusion

build/$(MODE)/demo/diffusion: | build/$(MODE)/demo
	mkdir -p $@

_demo_diffusion_brick_2d_2 :=\
  build/$(MODE)/demo/diffusion/2d_transient_continuous_primal_strong_cochain_p0_brick_2d_2_forman_temperature.txt\
  build/$(MODE)/demo/diffusion/2d_steady_state_continuous_primal_weak_cochain_p4_brick_2d_2_forman_temperature.txt\
  build/$(MODE)/demo/diffusion/2d_transient_continuous_primal_strong_cochain_p0_brick_2d_2_forman_flux.txt\
  build/$(MODE)/demo/diffusion/2d_transient_continuous_primal_strong_cochain_p1_brick_2d_2_forman_temperature.txt\
  build/$(MODE)/demo/diffusion/2d_transient_continuous_primal_strong_cochain_p2_brick_2d_2_forman_temperature.txt\
  build/$(MODE)/demo/diffusion/2d_transient_continuous_primal_strong_cochain_p4_brick_2d_2_forman_temperature.txt\
  build/$(MODE)/demo/diffusion/2d_transient_continuous_primal_weak_cochain_p4_brick_2d_2_forman_temperature.txt\
  build/$(MODE)/demo/diffusion/2d_transient_to_steady_state_continuous_primal_weak_cochain_p4_brick_2d_2_forman_temperature.txt\
  build/$(MODE)/demo/diffusion/2d_steady_state_discrete_primal_weak_p4_brick_2d_2_forman.txt\
  build/$(MODE)/demo/diffusion/2d_steady_state_discrete_primal_weak_p4_brick_2d_2_forman_temperature.txt\
  build/$(MODE)/demo/diffusion/2d_steady_state_discrete_mixed_weak_p4_brick_2d_2_forman.txt\
  build/$(MODE)/demo/diffusion/2d_steady_state_discrete_mixed_weak_p4_brick_2d_2_forman_all.txt\
  build/$(MODE)/demo/diffusion/2d_steady_state_discrete_mixed_weak_p4_brick_2d_2_forman_temperature.txt\

build/$(MODE)/demo/diffusion/2d_transient_continuous_primal_strong_cochain_p0_brick_2d_2_forman_temperature.txt:\
  build/$(MODE)/bin/diffusion_transient_continuous_primal_strong_cochain_solve_trapezoidal$(.EXE)\
  build/$(MODE)/demo/mesh/mesh_brick_2d_2_forman.txt\
  build/$(MODE)/demo/mesh/mesh_brick_2d_2_forman_cbd.txt\
  build/$(MODE)/demo/mesh/mesh_brick_2d_2_forman_cbd_star.txt\
  build/$(MODE)/obj/src/diffusion_transient_continuous_p0$(.OBJ)\
  | build/$(MODE)/demo/diffusion build/$(MODE)/lib/libshared$(.DLL)
	$< --raw $(word 2, $^) $(word 3, $^) $(word 4, $^) $(word 2, $|)\
	  diffusion_transient_continuous_p0 0.05 100 > $@

build/$(MODE)/demo/diffusion/2d_steady_state_continuous_primal_weak_cochain_p4_brick_2d_2_forman_temperature.txt:\
  build/$(MODE)/bin/diffusion_steady_state_continuous_primal_weak_cochain_solve$(.EXE)\
  build/$(MODE)/demo/mesh/mesh_brick_2d_2_forman.txt\
  build/$(MODE)/demo/mesh/mesh_brick_2d_2_forman_vol.txt\
  build/$(MODE)/demo/mesh/mesh_brick_2d_2_forman_inner.txt\
  build/$(MODE)/obj/src/diffusion_steady_state_continuous_p4$(.OBJ)\
  | build/$(MODE)/demo/diffusion build/$(MODE)/lib/libshared$(.DLL)
	$< --raw $(word 2, $^) $(word 3, $^) $(word 4, $^) $(word 2, $|)\
	  diffusion_steady_state_continuous_p4 > $@

build/$(MODE)/demo/diffusion/2d_transient_continuous_primal_strong_cochain_p0_brick_2d_2_forman_flux.txt:\
  build/$(MODE)/bin/diffusion_transient_discrete_primal_edge_flux$(.EXE)\
  build/$(MODE)/demo/mesh/mesh_brick_2d_2_forman.txt\
  build/$(MODE)/demo/mesh/mesh_brick_2d_2_forman_boundary.txt\
  build/$(MODE)/demo/diffusion/2d_transient_continuous_primal_strong_cochain_p0_brick_2d_2_forman_temperature.txt\
  build/$(MODE)/obj/src/diffusion_transient_continuous_p0$(.OBJ)\
  | build/$(MODE)/demo/diffusion build/$(MODE)/lib/libshared$(.DLL)
	$< --raw $(word 2, $^) $(word 3, $^) $(word 2, $|)\
	  diffusion_transient_continuous_p0 100 --raw $(word 4, $^) --raw > $@

build/$(MODE)/demo/diffusion/2d_transient_continuous_primal_strong_cochain_p4_brick_2d_2_forman_temperature.txt:\
  build/$(MODE)/bin/diffusion_transient_continuous_primal_strong_cochain_solve_trapezoidal_to_steady_state$(.EXE)\
  build/$(MODE)/demo/mesh/mesh_brick_2d_2_forman.txt\
  build/$(MODE)/demo/mesh/mesh_brick_2d_2_forman_cbd.txt\
  build/$(MODE)/demo/mesh/mesh_brick_2d_2_forman_cbd_star.txt\
  build/$(MODE)/obj/src/diffusion_transient_continuous_p4$(.OBJ)\
  | build/$(MODE)/demo/diffusion build/$(MODE)/lib/libshared$(.DLL)
	$< --raw $(word 2, $^) $(word 3, $^) $(word 4, $^) $(word 2, $|)\
	  diffusion_transient_continuous_p4 0.001 > $@

build/$(MODE)/demo/diffusion/2d_transient_to_steady_state_continuous_primal_weak_cochain_p4_brick_2d_2_forman_temperature.txt:\
  build/$(MODE)/bin/diffusion_transient_continuous_primal_weak_cochain_solve_trapezoidal_to_steady_state$(.EXE)\
  build/$(MODE)/demo/mesh/mesh_brick_2d_2_forman.txt\
  build/$(MODE)/demo/mesh/mesh_brick_2d_2_forman_vol.txt\
  build/$(MODE)/demo/mesh/mesh_brick_2d_2_forman_inner.txt\
  build/$(MODE)/obj/src/diffusion_transient_continuous_p4$(.OBJ)\
  | build/$(MODE)/demo/diffusion build/$(MODE)/lib/libshared$(.DLL)
	$< --raw $(word 2, $^) --raw $(word 3, $^) --raw $(word 4, $^)\
	  $(word 2, $|) diffusion_transient_continuous_p4 0.001 0.01 > $@

build/$(MODE)/demo/diffusion/2d_transient_continuous_primal_weak_cochain_p4_brick_2d_2_forman_temperature.txt:\
  build/$(MODE)/bin/diffusion_transient_continuous_primal_weak_cochain_solve_trapezoidal$(.EXE)\
  build/$(MODE)/demo/mesh/mesh_brick_2d_2_forman.txt\
  build/$(MODE)/demo/mesh/mesh_brick_2d_2_forman_vol.txt\
  build/$(MODE)/demo/mesh/mesh_brick_2d_2_forman_inner.txt\
  build/$(MODE)/obj/src/diffusion_transient_continuous_p4$(.OBJ)\
  | build/$(MODE)/demo/diffusion build/$(MODE)/lib/libshared$(.DLL)
	$< --raw $(word 2, $^) --raw $(word 3, $^) --raw $(word 4, $^)\
	  $(word 2, $|) diffusion_transient_continuous_p4 0.001 1000 --raw > $@

build/$(MODE)/demo/diffusion/2d_transient_continuous_primal_strong_cochain_p1_brick_2d_2_forman_temperature.txt:\
  build/$(MODE)/bin/diffusion_transient_continuous_primal_strong_cochain_solve_trapezoidal$(.EXE)\
  build/$(MODE)/demo/mesh/mesh_brick_2d_2_forman.txt\
  build/$(MODE)/demo/mesh/mesh_brick_2d_2_forman_cbd.txt\
  build/$(MODE)/demo/mesh/mesh_brick_2d_2_forman_cbd_star.txt\
  build/$(MODE)/obj/src/diffusion_transient_continuous_p1$(.OBJ)\
  | build/$(MODE)/demo/diffusion build/$(MODE)/lib/libshared$(.DLL)
	$< --raw $(word 2, $^) $(word 3, $^) $(word 4, $^) $(word 2, $|)\
	  diffusion_transient_continuous_p1 0.05 20 > $@

build/$(MODE)/demo/diffusion/2d_transient_continuous_primal_strong_cochain_p2_brick_2d_2_forman_temperature.txt:\
  build/$(MODE)/bin/diffusion_transient_continuous_primal_strong_cochain_solve_trapezoidal$(.EXE)\
  build/$(MODE)/demo/mesh/mesh_brick_2d_2_forman.txt\
  build/$(MODE)/demo/mesh/mesh_brick_2d_2_forman_cbd.txt\
  build/$(MODE)/demo/mesh/mesh_brick_2d_2_forman_cbd_star.txt\
  build/$(MODE)/obj/src/diffusion_transient_continuous_p2$(.OBJ)\
  | build/$(MODE)/demo/diffusion build/$(MODE)/lib/libshared$(.DLL)
	$< --raw $(word 2, $^) $(word 3, $^) $(word 4, $^) $(word 2, $|)\
  	  diffusion_transient_continuous_p2 0.001 100 > $@

build/$(MODE)/demo/diffusion/2d_steady_state_discrete_primal_weak_p4_brick_2d_2_forman.txt:\
  build/$(MODE)/bin/diffusion_steady_state_discrete_primal_weak_from_continuous$(.EXE)\
  build/$(MODE)/demo/mesh/mesh_brick_2d_2_forman.txt\
  build/$(MODE)/demo/mesh/mesh_brick_2d_2_forman_vol.txt\
  build/$(MODE)/obj/src/diffusion_steady_state_continuous_p4$(.OBJ)\
  | build/$(MODE)/demo/diffusion build/$(MODE)/lib/libshared$(.DLL)
	$< --raw $(word 2, $^) --raw $(word 3, $^) $(word 2, $|)\
	  diffusion_steady_state_continuous_p4 > $@

build/$(MODE)/demo/diffusion/2d_steady_state_discrete_mixed_weak_p4_brick_2d_2_forman.txt:\
  build/$(MODE)/bin/diffusion_steady_state_discrete_mixed_weak_from_continuous$(.EXE)\
  build/$(MODE)/demo/mesh/mesh_brick_2d_2_forman.txt\
  build/$(MODE)/demo/mesh/mesh_brick_2d_2_forman_vol.txt\
  build/$(MODE)/obj/src/diffusion_steady_state_continuous_p4$(.OBJ)\
  | build/$(MODE)/demo/diffusion build/$(MODE)/lib/libshared$(.DLL)
	$< --raw $(word 2, $^) --raw $(word 3, $^) $(word 2, $|)\
	  diffusion_steady_state_continuous_p4 > $@

build/$(MODE)/demo/diffusion/2d_steady_state_discrete_primal_weak_p4_brick_2d_2_forman_temperature.txt:\
  build/$(MODE)/bin/diffusion_steady_state_discrete_primal_weak_solve$(.EXE)\
  build/$(MODE)/demo/mesh/mesh_brick_2d_2_forman.txt\
  build/$(MODE)/demo/mesh/mesh_brick_2d_2_forman_inner.txt\
  build/$(MODE)/demo/diffusion/2d_steady_state_discrete_primal_weak_p4_brick_2d_2_forman.txt\
  | build/$(MODE)/demo/diffusion
	$< --raw $(word 2, $^) --raw $(word 3, $^) $(word 4, $^) > $@

build/$(MODE)/demo/diffusion/2d_steady_state_discrete_mixed_weak_p4_brick_2d_2_forman_all.txt:\
  build/$(MODE)/bin/diffusion_steady_state_discrete_mixed_weak_solve$(.EXE)\
  build/$(MODE)/demo/mesh/mesh_brick_2d_2_forman.txt\
  build/$(MODE)/demo/mesh/mesh_brick_2d_2_forman_inner.txt\
  build/$(MODE)/demo/diffusion/2d_steady_state_discrete_mixed_weak_p4_brick_2d_2_forman.txt\
  | build/$(MODE)/demo/diffusion
	$< --raw $(word 2, $^) --raw $(word 3, $^) $(word 4, $^) > $@ 2> /dev/null

build/$(MODE)/demo/diffusion/2d_steady_state_discrete_mixed_weak_p4_brick_2d_2_forman_temperature.txt:\
  build/$(MODE)/bin/diffusion_steady_state_discrete_mixed_weak_temperature$(.EXE)\
  build/$(MODE)/demo/mesh/mesh_brick_2d_2_forman.txt\
  build/$(MODE)/demo/mesh/mesh_brick_2d_2_forman_vol.txt\
  build/$(MODE)/demo/diffusion/2d_steady_state_discrete_mixed_weak_p4_brick_2d_2_forman.txt\
  build/$(MODE)/demo/diffusion/2d_steady_state_discrete_mixed_weak_p4_brick_2d_2_forman_all.txt\
  | build/$(MODE)/demo/diffusion
	$< --raw $(word 2, $^) --raw $(word 3, $^) $(word 4, $^) $(word 5, $^) > $@

_demo_diffusion_brick_2d_5 :=\
  build/$(MODE)/demo/diffusion/2d_transient_continuous_primal_strong_cochain_p2_brick_2d_5_forman_temperature.txt\
  build/$(MODE)/demo/diffusion/2d_transient_continuous_primal_strong_cochain_p4_brick_2d_5_forman_temperature.txt\
  build/$(MODE)/demo/diffusion/2d_steady_state_continuous_primal_strong_cochain_p4_brick_2d_5_forman_temperature.txt\
  build/$(MODE)/demo/diffusion/2d_steady_state_continuous_mixed_weak_cochain_p4_brick_2d_5_forman_temperature.txt\

build/$(MODE)/demo/diffusion/2d_transient_continuous_primal_strong_cochain_p2_brick_2d_5_forman_temperature.txt:\
  build/$(MODE)/bin/diffusion_transient_continuous_primal_strong_cochain_solve_trapezoidal$(.EXE)\
  build/$(MODE)/demo/mesh/mesh_brick_2d_5_forman.txt\
  build/$(MODE)/demo/mesh/mesh_brick_2d_5_forman_cbd.txt\
  build/$(MODE)/demo/mesh/mesh_brick_2d_5_forman_cbd_star.txt\
  build/$(MODE)/obj/src/diffusion_transient_continuous_p2$(.OBJ)\
  | build/$(MODE)/demo/diffusion build/$(MODE)/lib/libshared$(.DLL)
	$< --raw $(word 2, $^) $(word 3, $^) $(word 4, $^) $(word 2, $|)\
	  diffusion_transient_continuous_p2 0.0001 10000 > $@

build/$(MODE)/demo/diffusion/2d_transient_continuous_primal_strong_cochain_p4_brick_2d_5_forman_temperature.txt:\
  build/$(MODE)/bin/diffusion_transient_continuous_primal_strong_cochain_solve_trapezoidal$(.EXE)\
  build/$(MODE)/demo/mesh/mesh_brick_2d_5_forman.txt\
  build/$(MODE)/demo/mesh/mesh_brick_2d_5_forman_cbd.txt\
  build/$(MODE)/demo/mesh/mesh_brick_2d_5_forman_cbd_star.txt\
  build/$(MODE)/obj/src/diffusion_transient_continuous_p4$(.OBJ)\
  | build/$(MODE)/demo/diffusion build/$(MODE)/lib/libshared$(.DLL)
	$< --raw $(word 2, $^) $(word 3, $^) $(word 4, $^) $(word 2, $|)\
	  diffusion_transient_continuous_p4 0.0001 10000 > $@

build/$(MODE)/demo/diffusion/2d_steady_state_continuous_primal_strong_cochain_p4_brick_2d_5_forman_temperature.txt:\
  build/$(MODE)/bin/diffusion_steady_state_continuous_primal_strong_cochain_solve$(.EXE)\
  build/$(MODE)/demo/mesh/mesh_brick_2d_5_forman.txt\
  build/$(MODE)/demo/mesh/mesh_brick_2d_5_forman_cbd.txt\
  build/$(MODE)/demo/mesh/mesh_brick_2d_5_forman_cbd_star.txt\
  build/$(MODE)/obj/src/diffusion_steady_state_continuous_p4$(.OBJ)\
  | build/$(MODE)/demo/diffusion build/$(MODE)/lib/libshared$(.DLL)
	$< --raw $(word 2, $^) $(word 3, $^) $(word 4, $^) $(word 2, $|)\
	  diffusion_steady_state_continuous_p4 > $@

build/$(MODE)/demo/diffusion/2d_steady_state_continuous_mixed_weak_cochain_p4_brick_2d_5_forman_temperature.txt:\
  build/$(MODE)/bin/diffusion_steady_state_continuous_mixed_weak_cochain_solve$(.EXE)\
  build/$(MODE)/demo/mesh/mesh_brick_2d_5_forman.txt\
  build/$(MODE)/demo/mesh/mesh_brick_2d_5_forman_vol.txt\
  build/$(MODE)/demo/mesh/mesh_brick_2d_5_forman_inner.txt\
  build/$(MODE)/obj/src/diffusion_steady_state_continuous_p4$(.OBJ)\
  | build/$(MODE)/demo/diffusion build/$(MODE)/lib/libshared$(.DLL)
	$< $(word 2, $^) $(word 3, $^) $(word 4, $^) $(word 2, $|)\
	  diffusion_steady_state_continuous_p4 &> $@

_demo_diffusion_brick_2d_10 :=\
  build/$(MODE)/demo/diffusion/2d_transient_continuous_primal_strong_cochain_p4_brick_2d_10_forman_temperature.txt\
  build/$(MODE)/demo/diffusion/2d_transient_continuous_primal_strong_cochain_p4_brick_2d_10_forman_flux.txt\


build/$(MODE)/demo/diffusion/2d_transient_continuous_primal_strong_cochain_p4_brick_2d_10_forman_temperature.txt:\
  build/$(MODE)/bin/diffusion_transient_continuous_primal_strong_cochain_solve_trapezoidal$(.EXE)\
  build/$(MODE)/demo/mesh/mesh_brick_2d_10_forman.txt\
  build/$(MODE)/demo/mesh/mesh_brick_2d_10_forman_cbd.txt\
  build/$(MODE)/demo/mesh/mesh_brick_2d_10_forman_cbd_star.txt\
  build/$(MODE)/obj/src/diffusion_transient_continuous_p4$(.OBJ)\
  | build/$(MODE)/demo/diffusion build/$(MODE)/lib/libshared$(.DLL)
	$< --raw $(word 2, $^) $(word 3, $^) $(word 4, $^) $(word 2, $|)\
	  diffusion_transient_continuous_p4 0.0001 4000 > $@

build/$(MODE)/demo/diffusion/2d_transient_continuous_primal_strong_cochain_p4_brick_2d_10_forman_flux.txt:\
  build/$(MODE)/bin/diffusion_transient_discrete_primal_edge_flux$(.EXE)\
  build/$(MODE)/demo/mesh/mesh_brick_2d_10_forman.txt\
  build/$(MODE)/demo/mesh/mesh_brick_2d_10_forman_boundary.txt\
  build/$(MODE)/demo/diffusion/2d_transient_continuous_primal_strong_cochain_p4_brick_2d_10_forman_temperature.txt\
  build/$(MODE)/obj/src/diffusion_steady_state_continuous_p4$(.OBJ)\
  | build/$(MODE)/demo/diffusion build/$(MODE)/lib/libshared$(.DLL)
	$< --raw $(word 2, $^) $(word 3, $^) $(word 2, $|)\
	  diffusion_transient_continuous_p4 4000 --raw $(word 4, $^) --raw > $@

_demo_diffusion_circular :=\
  build/$(MODE)/demo/diffusion/2d_steady_state_discrete_primal_weak_p9_circular_4_3_forman.txt\
  build/$(MODE)/demo/diffusion/2d_steady_state_discrete_primal_weak_p9_circular_4_3_forman_temperature.txt\
  build/$(MODE)/demo/diffusion/2d_steady_state_discrete_primal_weak_p9_circular_17_10_forman.txt\
  build/$(MODE)/demo/diffusion/2d_steady_state_discrete_primal_weak_p9_circular_17_10_forman_temperature.txt\

build/$(MODE)/demo/diffusion/2d_steady_state_discrete_primal_weak_p9_circular_4_3_forman.txt:\
  build/$(MODE)/bin/diffusion_steady_state_discrete_primal_weak_from_continuous$(.EXE)\
  build/$(MODE)/demo/mesh/mesh_circular_4_3_forman.txt\
  build/$(MODE)/demo/mesh/mesh_circular_4_3_forman_vol.txt\
  build/$(MODE)/obj/src/diffusion_steady_state_continuous_p9$(.OBJ)\
  | build/$(MODE)/demo/diffusion build/$(MODE)/lib/libshared$(.DLL)
	$< --raw $(word 2, $^) --raw $(word 3, $^) $(word 2, $|)\
	  diffusion_steady_state_continuous_p9 > $@

build/$(MODE)/demo/diffusion/2d_steady_state_discrete_primal_weak_p9_circular_4_3_forman_temperature.txt:\
  build/$(MODE)/bin/diffusion_steady_state_discrete_primal_weak_solve$(.EXE)\
  build/$(MODE)/demo/mesh/mesh_circular_4_3_forman.txt\
  build/$(MODE)/demo/mesh/mesh_circular_4_3_forman_inner.txt\
  build/$(MODE)/demo/diffusion/2d_steady_state_discrete_primal_weak_p9_circular_4_3_forman.txt\
  | build/$(MODE)/demo/diffusion
	$< --raw $(word 2, $^) --raw $(word 3, $^) $(word 4, $^) > $@

build/$(MODE)/demo/diffusion/2d_steady_state_discrete_primal_weak_p9_circular_17_10_forman.txt:\
  build/$(MODE)/bin/diffusion_steady_state_discrete_primal_weak_from_continuous$(.EXE)\
  build/$(MODE)/demo/mesh/mesh_circular_17_10_forman.txt\
  build/$(MODE)/demo/mesh/mesh_circular_17_10_forman_vol.txt\
  build/$(MODE)/obj/src/diffusion_steady_state_continuous_p9$(.OBJ)\
  | build/$(MODE)/demo/diffusion build/$(MODE)/lib/libshared$(.DLL)
	$< --raw $(word 2, $^) --raw $(word 3, $^) $(word 2, $|)\
	  diffusion_steady_state_continuous_p9 > $@

build/$(MODE)/demo/diffusion/2d_steady_state_discrete_primal_weak_p9_circular_17_10_forman_temperature.txt:\
  build/$(MODE)/bin/diffusion_steady_state_discrete_primal_weak_solve$(.EXE)\
  build/$(MODE)/demo/mesh/mesh_circular_17_10_forman.txt\
  build/$(MODE)/demo/mesh/mesh_circular_17_10_forman_inner.txt\
  build/$(MODE)/demo/diffusion/2d_steady_state_discrete_primal_weak_p9_circular_17_10_forman.txt\
  | build/$(MODE)/demo/diffusion
	$< --raw $(word 2, $^) --raw $(word 3, $^) $(word 4, $^) > $@

_demo_diffusion_2d_10_grains :=\
  build/$(MODE)/demo/diffusion/2d_transient_continuous_primal_strong_cochain_p7_2d_10_grains_forman_temperature.txt\
  build/$(MODE)/demo/diffusion/2d_transient_continuous_primal_strong_cochain_p7_2d_10_grains_forman_flux.txt\
  build/$(MODE)/demo/diffusion/2d_steady_state_continuous_primal_strong_cochain_p7_2d_10_grains_forman_temperature.txt\
  build/$(MODE)/demo/diffusion/2d_steady_state_continuous_primal_weak_cochain_p7_2d_10_grains_forman_temperature.txt\
  build/$(MODE)/demo/diffusion/2d_transient_continuous_primal_weak_cochain_p7_2d_10_grains_forman_temperature.txt\
  build/$(MODE)/demo/diffusion/2d_transient_continuous_primal_weak_cochain_p7_2d_10_grains_forman_flux.txt\
  build/$(MODE)/demo/diffusion/2d_transient_to_steady_state_continuous_primal_weak_cochain_p7_2d_10_grains_forman_temperature.txt\
  build/$(MODE)/demo/diffusion/2d_transient_continuous_primal_weak_cochain_p8_2d_10_grains_forman_temperature.txt\

build/$(MODE)/demo/diffusion/2d_transient_continuous_primal_strong_cochain_p7_2d_10_grains_forman_temperature.txt:\
  build/$(MODE)/bin/diffusion_transient_continuous_primal_strong_cochain_solve_trapezoidal$(.EXE)\
  build/$(MODE)/demo/mesh/mesh_2d_10_grains_forman.txt\
  build/$(MODE)/demo/mesh/mesh_2d_10_grains_forman_cbd.txt\
  build/$(MODE)/demo/mesh/mesh_2d_10_grains_forman_cbd_star.txt\
  build/$(MODE)/obj/src/diffusion_transient_continuous_p7$(.OBJ)\
  | build/$(MODE)/demo/diffusion build/$(MODE)/lib/libshared$(.DLL)
	$< --raw $(word 2, $^) $(word 3, $^) $(word 4, $^) $(word 2, $|)\
	  diffusion_transient_continuous_p7 0.0001 1000 > $@

build/$(MODE)/demo/diffusion/2d_transient_continuous_primal_strong_cochain_p7_2d_10_grains_forman_flux.txt:\
  build/$(MODE)/bin/diffusion_transient_discrete_primal_edge_flux$(.EXE)\
  build/$(MODE)/demo/mesh/mesh_2d_10_grains_forman.txt\
  build/$(MODE)/demo/diffusion/2d_transient_continuous_primal_strong_cochain_p7_2d_10_grains_forman_temperature.txt\
  build/$(MODE)/obj/src/diffusion_transient_continuous_p7$(.OBJ)\
  | build/$(MODE)/demo/diffusion build/$(MODE)/lib/libshared$(.DLL)
	$< --raw $(word 2, $^) "-" $(word 2, $|)\
	  diffusion_transient_continuous_p7 1000 --raw $(word 3, $^) --raw > $@

build/$(MODE)/demo/diffusion/2d_steady_state_continuous_primal_strong_cochain_p7_2d_10_grains_forman_temperature.txt:\
  build/$(MODE)/bin/diffusion_steady_state_continuous_primal_weak_cochain_solve$(.EXE)\
  build/$(MODE)/demo/mesh/mesh_2d_10_grains_forman.txt\
  build/$(MODE)/demo/mesh/mesh_2d_10_grains_forman_cbd.txt\
  build/$(MODE)/demo/mesh/mesh_2d_10_grains_forman_cbd_star.txt\
  build/$(MODE)/obj/src/diffusion_steady_state_continuous_p7$(.OBJ)\
  | build/$(MODE)/demo/diffusion build/$(MODE)/lib/libshared$(.DLL)
	$< --raw $(word 2, $^) $(word 3, $^) $(word 4, $^) $(word 2, $|)\
	  diffusion_steady_state_continuous_p7 > $@

build/$(MODE)/demo/diffusion/2d_steady_state_continuous_primal_weak_cochain_p7_2d_10_grains_forman_temperature.txt:\
  build/$(MODE)/bin/diffusion_steady_state_continuous_primal_weak_cochain_solve$(.EXE)\
  build/$(MODE)/demo/mesh/mesh_2d_10_grains_forman.txt\
  build/$(MODE)/demo/mesh/mesh_2d_10_grains_forman_vol.txt\
  build/$(MODE)/demo/mesh/mesh_2d_10_grains_forman_inner.txt\
  build/$(MODE)/obj/src/diffusion_steady_state_continuous_p7$(.OBJ)\
  | build/$(MODE)/demo/diffusion build/$(MODE)/lib/libshared$(.DLL)
	$< --raw $(word 2, $^) $(word 3, $^) $(word 4, $^) $(word 2, $|)\
	  diffusion_steady_state_continuous_p7 > $@

build/$(MODE)/demo/diffusion/2d_transient_continuous_primal_weak_cochain_p7_2d_10_grains_forman_temperature.txt:\
  build/$(MODE)/bin/diffusion_transient_continuous_primal_weak_cochain_solve_trapezoidal$(.EXE)\
  build/$(MODE)/demo/mesh/mesh_2d_10_grains_forman.txt\
  build/$(MODE)/demo/mesh/mesh_2d_10_grains_forman_vol.txt\
  build/$(MODE)/demo/mesh/mesh_2d_10_grains_forman_inner.txt\
  build/$(MODE)/obj/src/diffusion_transient_continuous_p7$(.OBJ)\
  | build/$(MODE)/demo/diffusion build/$(MODE)/lib/libshared$(.DLL)
	$< --raw $(word 2, $^) --raw $(word 3, $^) --raw $(word 4, $^)\
	  $(word 2, $|) diffusion_transient_continuous_p7 0.01 2000 --raw > $@

build/$(MODE)/demo/diffusion/2d_transient_continuous_primal_weak_cochain_p7_2d_10_grains_forman_flux.txt:\
  build/$(MODE)/bin/diffusion_transient_discrete_primal_edge_flux$(.EXE)\
  build/$(MODE)/demo/mesh/mesh_2d_10_grains_forman.txt\
  build/$(MODE)/demo/diffusion/2d_transient_continuous_primal_weak_cochain_p7_2d_10_grains_forman_temperature.txt\
  build/$(MODE)/obj/src/diffusion_transient_continuous_p7$(.OBJ)\
  | build/$(MODE)/demo/diffusion build/$(MODE)/lib/libshared$(.DLL)
	$< --raw $(word 2, $^) "-" $(word 2, $|)\
	  diffusion_transient_continuous_p7 2000 --raw $(word 3, $^) --raw > $@

build/$(MODE)/demo/diffusion/2d_transient_to_steady_state_continuous_primal_weak_cochain_p7_2d_10_grains_forman_temperature.txt:\
  build/$(MODE)/bin/diffusion_transient_continuous_primal_weak_cochain_solve_trapezoidal_to_steady_state$(.EXE)\
  build/$(MODE)/demo/mesh/mesh_2d_10_grains_forman.txt\
  build/$(MODE)/demo/mesh/mesh_2d_10_grains_forman_vol.txt\
  build/$(MODE)/demo/mesh/mesh_2d_10_grains_forman_inner.txt\
  build/$(MODE)/obj/src/diffusion_transient_continuous_p7$(.OBJ)\
  | build/$(MODE)/demo/diffusion build/$(MODE)/lib/libshared$(.DLL)
	$< --raw $(word 2, $^) --raw $(word 3, $^) --raw $(word 4, $^)\
	  $(word 2, $|) diffusion_transient_continuous_p7 0.001 0.0001 > $@

build/$(MODE)/demo/diffusion/2d_transient_continuous_primal_weak_cochain_p8_2d_10_grains_forman_temperature.txt:\
  build/$(MODE)/bin/diffusion_transient_continuous_primal_weak_cochain_solve_trapezoidal$(.EXE)\
  build/$(MODE)/demo/mesh/mesh_2d_10_grains_forman.txt\
  build/$(MODE)/demo/mesh/mesh_2d_10_grains_forman_vol.txt\
  build/$(MODE)/demo/mesh/mesh_2d_10_grains_forman_inner.txt\
  build/$(MODE)/obj/src/diffusion_transient_continuous_p8$(.OBJ)\
  | build/$(MODE)/demo/diffusion build/$(MODE)/lib/libshared$(.DLL)
	$< --raw $(word 2, $^) --raw $(word 3, $^) --raw $(word 4, $^)\
  	  $(word 2, $|) diffusion_transient_continuous_p8 0.01 2000 --raw > $@

_demo_diffusion_square_8 :=\
  build/$(MODE)/demo/diffusion/2d_transient_continuous_primal_strong_cochain_p5_square_8_temperature.txt\

build/$(MODE)/demo/diffusion/2d_transient_continuous_primal_strong_cochain_p5_square_8_temperature.txt:\
  build/$(MODE)/bin/diffusion_transient_continuous_primal_strong_cochain_solve_trapezoidal$(.EXE)\
  build/$(MODE)/demo/mesh/mesh_square_8.txt\
  build/$(MODE)/demo/mesh/mesh_square_8_cbd.txt\
  build/$(MODE)/demo/mesh/mesh_square_8_cbd_star.txt\
  build/$(MODE)/obj/src/diffusion_transient_continuous_p5$(.OBJ)\
  | build/$(MODE)/demo/diffusion build/$(MODE)/lib/libshared$(.DLL)
	$< --raw $(word 2, $^) $(word 3, $^) $(word 4, $^) $(word 2, $|)\
	  diffusion_transient_continuous_p5 0.001 4000 > $@

_demo_diffusion_2d :=\
  $(_demo_diffusion_brick_2d_2)\
  $(_demo_diffusion_brick_2d_5)\
  $(_demo_diffusion_brick_2d_10)\
  $(_demo_diffusion_circular)\
  $(_demo_diffusion_2d_10_grains)\
  $(_demo_diffusion_square_8)\

.PHONY: demo_diffusion_2d
demo_diffusion_2d: $(_demo_diffusion_2d)

_demo_diffusion_brick_3d_2 :=\
  build/$(MODE)/demo/diffusion/3d_transient_continuous_primal_strong_cochain_p6_brick_3d_2_forman_temperature.txt\
  build/$(MODE)/demo/diffusion/3d_steady_state_continuous_primal_strong_cochain_p6_brick_3d_2_forman_temperature.txt\

build/$(MODE)/demo/diffusion/3d_transient_continuous_primal_strong_cochain_p6_brick_3d_2_forman_temperature.txt:\
  build/$(MODE)/bin/diffusion_transient_continuous_primal_strong_cochain_solve_trapezoidal$(.EXE)\
  build/$(MODE)/demo/mesh/mesh_brick_3d_2_forman.txt\
  build/$(MODE)/demo/mesh/mesh_brick_3d_2_forman_cbd.txt\
  build/$(MODE)/demo/mesh/mesh_brick_3d_2_forman_cbd_star.txt\
  build/$(MODE)/obj/src/diffusion_transient_continuous_p6$(.OBJ)\
  | build/$(MODE)/demo/diffusion build/$(MODE)/lib/libshared$(.DLL)
	$< --raw $(word 2, $^) $(word 3, $^) $(word 4, $^) $(word 2, $|)\
	  diffusion_transient_continuous_p6 0.001 1000 > $@

build/$(MODE)/demo/diffusion/3d_steady_state_continuous_primal_strong_cochain_p6_brick_3d_2_forman_temperature.txt:\
  build/$(MODE)/bin/diffusion_steady_state_continuous_primal_strong_cochain_solve$(.EXE)\
  build/$(MODE)/demo/mesh/mesh_brick_3d_2_forman.txt\
  build/$(MODE)/demo/mesh/mesh_brick_3d_2_forman_cbd.txt\
  build/$(MODE)/demo/mesh/mesh_brick_3d_2_forman_cbd_star.txt\
  build/$(MODE)/obj/src/diffusion_steady_state_continuous_p6$(.OBJ)\
  | build/$(MODE)/demo/diffusion build/$(MODE)/lib/libshared$(.DLL)
	$< --raw $(word 2, $^) $(word 3, $^) $(word 4, $^) $(word 2, $|)\
	  diffusion_steady_state_continuous_p6 > $@


_demo_diffusion_brick_3d_10 :=\
  build/$(MODE)/demo/diffusion/3d_steady_state_continuous_primal_strong_cochain_p6_brick_3d_10_forman_temperature.txt\

build/$(MODE)/demo/diffusion/3d_steady_state_continuous_primal_strong_cochain_p6_brick_3d_10_forman_temperature.txt:\
  build/$(MODE)/bin/diffusion_steady_state_continuous_primal_strong_cochain_solve$(.EXE)\
  build/$(MODE)/demo/mesh/mesh_brick_3d_10_forman.txt\
  build/$(MODE)/demo/mesh/mesh_brick_3d_10_forman_cbd.txt\
  build/$(MODE)/demo/mesh/mesh_brick_3d_10_forman_cbd_star.txt\
  build/$(MODE)/obj/src/diffusion_steady_state_continuous_p6$(.OBJ)\
  | build/$(MODE)/demo/diffusion build/$(MODE)/lib/libshared$(.DLL)
	$< --raw $(word 2, $^) $(word 3, $^) $(word 4, $^) $(word 2, $|)\
	  diffusion_steady_state_continuous_p6 > $@

_demo_diffusion_brick_3d_25 :=\
  build/$(MODE)/demo/diffusion/3d_steady_state_continuous_primal_strong_cochain_p6_brick_3d_25_forman_temperature.txt\

build/$(MODE)/demo/diffusion/3d_steady_state_continuous_primal_strong_cochain_p6_brick_3d_25_forman_temperature.txt:\
  build/$(MODE)/bin/diffusion_steady_state_continuous_primal_strong_cochain_solve$(.EXE)\
  build/$(MODE)/demo/mesh/mesh_brick_3d_25_forman.txt\
  build/$(MODE)/demo/mesh/mesh_brick_3d_25_forman_cbd.txt\
  build/$(MODE)/demo/mesh/mesh_brick_3d_25_forman_cbd_star.txt\
  build/$(MODE)/obj/src/diffusion_steady_state_continuous_p6$(.OBJ)\
  | build/$(MODE)/demo/diffusion build/$(MODE)/lib/libshared$(.DLL)
	$< --raw $(word 2, $^) $(word 3, $^) $(word 4, $^) $(word 2, $|)\
	  diffusion_steady_state_continuous_p6 > $@

_demo_diffusion_3d :=\
  $(_demo_diffusion_brick_3d_2)\
  $(_demo_diffusion_brick_3d_10)\

.PHONY: demo_diffusion_3d
demo_diffusion_3d: $(_demo_diffusion_3d)

_demo_diffusion_all := $(_demo_diffusion_2d) $(_demo_diffusion_3d)

.PHONY: demo_diffusion_clean
demo_diffusion_clean:
	-$(RM) $(_demo_diffusion_all)
	-$(RM) -r build/$(MODE)/demo/diffusion
