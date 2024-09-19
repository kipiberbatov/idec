.PHONY: demo_diffusion
demo_diffusion:\
  bin_diffusion\
  demo_diffusion_2d\
  demo_diffusion_3d\
  | build/$(MODE)/demo/diffusion

build/$(MODE)/demo/diffusion: | build/$(MODE)/demo
	mkdir -p $@

_demo_diffusion_brick_2d_2 :=\
  build/$(MODE)/demo/diffusion/mesh_brick_2d_2_forman_diffusion_transient_continuous_p0_temperature.txt\
  build/$(MODE)/demo/diffusion/mesh_brick_2d_2_forman_diffusion_steady_state_continuous_p4_primal_weak_temperature.txt\
  build/$(MODE)/demo/diffusion/mesh_brick_2d_2_forman_diffusion_transient_continuous_p0_flux.txt\
  build/$(MODE)/demo/diffusion/mesh_brick_2d_2_forman_diffusion_transient_continuous_p1_temperature.txt\
  build/$(MODE)/demo/diffusion/mesh_brick_2d_2_forman_diffusion_transient_continuous_p2_temperature.txt\
  build/$(MODE)/demo/diffusion/mesh_brick_2d_2_forman_diffusion_transient_continuous_p4_temperature.txt\
  build/$(MODE)/demo/diffusion/2d-transient-continuous-temperature-primal_weak-cochain-trapezoidal-p4-brick_2d_2_forman.txt\

build/$(MODE)/demo/diffusion/mesh_brick_2d_2_forman_neumann_modified_laplacian.txt:\
  build/$(MODE)/bin/diffusion_discrete_set_neumann_rows$(.EXE)\
  build/$(MODE)/demo/mesh/mesh_brick_2d_2_forman.txt\
  build/$(MODE)/demo/mesh/mesh_brick_2d_2_forman_laplacian.txt\
  | build/$(MODE)/demo/diffusion
	 $< --raw $(word 2, $^) --raw $(word 3, $^) > $@

build/$(MODE)/demo/diffusion/mesh_brick_2d_2_forman_diffusion_transient_continuous_p0_temperature.txt:\
  build/$(MODE)/bin/diffusion_transient_continuous_primal_strong_cochain_solve_trapezoidal$(.EXE)\
  build/$(MODE)/demo/mesh/mesh_brick_2d_2_forman.txt\
  build/$(MODE)/demo/mesh/mesh_brick_2d_2_forman_cbd.txt\
  build/$(MODE)/demo/mesh/mesh_brick_2d_2_forman_cbd_star.txt\
  build/$(MODE)/obj/src/diffusion_transient_continuous_p0$(.OBJ)\
  | build/$(MODE)/demo/diffusion build/$(MODE)/lib/libshared$(.DLL)
	$< --raw $(word 2, $^) $(word 3, $^) $(word 4, $^) $(word 2, $|)\
	  diffusion_transient_continuous_p0 0.05 100 > $@

build/$(MODE)/demo/diffusion/mesh_brick_2d_2_forman_diffusion_steady_state_continuous_p4_primal_weak_temperature.txt:\
  build/$(MODE)/bin/diffusion_steady_state_continuous_primal_weak_cochain_solve$(.EXE)\
  build/$(MODE)/demo/mesh/mesh_brick_2d_2_forman.txt\
  build/$(MODE)/demo/mesh/mesh_brick_2d_2_forman_vol.txt\
  build/$(MODE)/demo/mesh/mesh_brick_2d_2_forman_inner.txt\
  build/$(MODE)/obj/src/diffusion_steady_state_continuous_p4$(.OBJ)\
  | build/$(MODE)/demo/diffusion build/$(MODE)/lib/libshared$(.DLL)
	$< --raw $(word 2, $^) $(word 3, $^) $(word 4, $^) $(word 2, $|)\
	  diffusion_steady_state_continuous_p4 > $@

build/$(MODE)/demo/diffusion/mesh_brick_2d_2_forman_diffusion_transient_continuous_p0_flux.txt:\
  build/$(MODE)/bin/diffusion_transient_discrete_primal_edge_flux$(.EXE)\
  build/$(MODE)/demo/mesh/mesh_brick_2d_2_forman.txt\
  build/$(MODE)/demo/mesh/mesh_brick_2d_2_forman_boundary.txt\
  build/$(MODE)/demo/diffusion/mesh_brick_2d_2_forman_diffusion_transient_continuous_p0_temperature.txt\
  build/$(MODE)/obj/src/diffusion_transient_continuous_p0$(.OBJ)\
  | build/$(MODE)/demo/diffusion build/$(MODE)/lib/libshared$(.DLL)
	$< --raw $(word 2, $^) $(word 3, $^) $(word 2, $|)\
	  diffusion_transient_continuous_p0 100 --raw $(word 4, $^) --raw > $@

build/$(MODE)/demo/diffusion/mesh_brick_2d_2_forman_diffusion_transient_continuous_p4_temperature.txt:\
  build/$(MODE)/bin/diffusion_transient_continuous_primal_strong_cochain_solve_trapezoidal_to_steady_state$(.EXE)\
  build/$(MODE)/demo/mesh/mesh_brick_2d_2_forman.txt\
  build/$(MODE)/demo/mesh/mesh_brick_2d_2_forman_cbd.txt\
  build/$(MODE)/demo/mesh/mesh_brick_2d_2_forman_cbd_star.txt\
  build/$(MODE)/obj/src/diffusion_transient_continuous_p4$(.OBJ)\
  | build/$(MODE)/demo/diffusion build/$(MODE)/lib/libshared$(.DLL)
	$< --raw $(word 2, $^) $(word 3, $^) $(word 4, $^) $(word 2, $|)\
	  diffusion_transient_continuous_p4 0.001 > $@

build/$(MODE)/demo/diffusion/2d-transient-continuous-temperature-primal_weak-cochain-trapezoidal-p4-brick_2d_2_forman.txt:\
  build/$(MODE)/bin/diffusion_transient_continuous_primal_weak_cochain_solve_trapezoidal$(.EXE)\
  build/$(MODE)/demo/mesh/mesh_brick_2d_2_forman.txt\
  build/$(MODE)/demo/mesh/mesh_brick_2d_2_forman_vol.txt\
  build/$(MODE)/demo/mesh/mesh_brick_2d_2_forman_inner.txt\
  build/$(MODE)/obj/src/diffusion_transient_continuous_p4$(.OBJ)\
  | build/$(MODE)/demo/diffusion build/$(MODE)/lib/libshared$(.DLL)
	$< --raw $(word 2, $^) --raw $(word 3, $^) --raw $(word 4, $^)\
	  $(word 2, $|) diffusion_transient_continuous_p4 0.001 1000 --raw > $@

build/$(MODE)/demo/diffusion/mesh_brick_2d_2_forman_diffusion_transient_continuous_p1_temperature.txt:\
  build/$(MODE)/bin/diffusion_transient_continuous_primal_strong_cochain_solve_trapezoidal$(.EXE)\
  build/$(MODE)/demo/mesh/mesh_brick_2d_2_forman.txt\
  build/$(MODE)/demo/mesh/mesh_brick_2d_2_forman_cbd.txt\
  build/$(MODE)/demo/mesh/mesh_brick_2d_2_forman_cbd_star.txt\
  build/$(MODE)/obj/src/diffusion_transient_continuous_p1$(.OBJ)\
  | build/$(MODE)/demo/diffusion build/$(MODE)/lib/libshared$(.DLL)
	$< --raw $(word 2, $^) $(word 3, $^) $(word 4, $^) $(word 2, $|)\
	  diffusion_transient_continuous_p1 0.05 20 > $@

build/$(MODE)/demo/diffusion/mesh_brick_2d_2_forman_diffusion_transient_continuous_p2_temperature.txt:\
  build/$(MODE)/bin/diffusion_transient_continuous_primal_strong_cochain_solve_trapezoidal$(.EXE)\
  build/$(MODE)/demo/mesh/mesh_brick_2d_2_forman.txt\
  build/$(MODE)/demo/mesh/mesh_brick_2d_2_forman_cbd.txt\
  build/$(MODE)/demo/mesh/mesh_brick_2d_2_forman_cbd_star.txt\
  build/$(MODE)/obj/src/diffusion_transient_continuous_p2$(.OBJ)\
  | build/$(MODE)/demo/diffusion build/$(MODE)/lib/libshared$(.DLL)
	$< --raw $(word 2, $^) $(word 3, $^) $(word 4, $^) $(word 2, $|)\
  	  diffusion_transient_continuous_p2 0.001 100 > $@


_demo_diffusion_brick_2d_5 :=\
  build/$(MODE)/demo/diffusion/mesh_brick_2d_5_forman_diffusion_transient_continuous_p2_temperature.txt\
  build/$(MODE)/demo/diffusion/mesh_brick_2d_5_forman_diffusion_transient_continuous_p4_temperature.txt\
  build/$(MODE)/demo/diffusion/mesh_brick_2d_5_forman_diffusion_steady_state_continuous_p4_temperature.txt\

build/$(MODE)/demo/diffusion/mesh_brick_2d_5_forman_diffusion_transient_continuous_p2_temperature.txt:\
  build/$(MODE)/bin/diffusion_transient_continuous_primal_strong_cochain_solve_trapezoidal$(.EXE)\
  build/$(MODE)/demo/mesh/mesh_brick_2d_5_forman.txt\
  build/$(MODE)/demo/mesh/mesh_brick_2d_5_forman_cbd.txt\
  build/$(MODE)/demo/mesh/mesh_brick_2d_5_forman_cbd_star.txt\
  build/$(MODE)/obj/src/diffusion_transient_continuous_p2$(.OBJ)\
  | build/$(MODE)/demo/diffusion build/$(MODE)/lib/libshared$(.DLL)
	$< --raw $(word 2, $^) $(word 3, $^) $(word 4, $^) $(word 2, $|)\
	  diffusion_transient_continuous_p2 0.0001 10000 > $@

build/$(MODE)/demo/diffusion/mesh_brick_2d_5_forman_diffusion_transient_continuous_p4_temperature.txt:\
  build/$(MODE)/bin/diffusion_transient_continuous_primal_strong_cochain_solve_trapezoidal$(.EXE)\
  build/$(MODE)/demo/mesh/mesh_brick_2d_5_forman.txt\
  build/$(MODE)/demo/mesh/mesh_brick_2d_5_forman_cbd.txt\
  build/$(MODE)/demo/mesh/mesh_brick_2d_5_forman_cbd_star.txt\
  build/$(MODE)/obj/src/diffusion_transient_continuous_p4$(.OBJ)\
  | build/$(MODE)/demo/diffusion build/$(MODE)/lib/libshared$(.DLL)
	$< --raw $(word 2, $^) $(word 3, $^) $(word 4, $^) $(word 2, $|)\
	  diffusion_transient_continuous_p4 0.0001 10000 > $@

build/$(MODE)/demo/diffusion/mesh_brick_2d_5_forman_diffusion_steady_state_continuous_p4_temperature.txt:\
  build/$(MODE)/bin/diffusion_steady_state_continuous_primal_strong_cochain_solve$(.EXE)\
  build/$(MODE)/demo/mesh/mesh_brick_2d_5_forman.txt\
  build/$(MODE)/demo/mesh/mesh_brick_2d_5_forman_cbd.txt\
  build/$(MODE)/demo/mesh/mesh_brick_2d_5_forman_cbd_star.txt\
  build/$(MODE)/obj/src/diffusion_steady_state_continuous_p4$(.OBJ)\
  | build/$(MODE)/demo/diffusion build/$(MODE)/lib/libshared$(.DLL)
	$< --raw $(word 2, $^) $(word 3, $^) $(word 4, $^) $(word 2, $|)\
	  diffusion_steady_state_continuous_p4 > $@

_demo_diffusion_brick_2d_10 :=\
  build/$(MODE)/demo/diffusion/mesh_brick_2d_10_forman_diffusion_transient_continuous_p4_temperature.txt\
  build/$(MODE)/demo/diffusion/mesh_brick_2d_10_forman_diffusion_transient_continuous_p4_flux.txt\


build/$(MODE)/demo/diffusion/mesh_brick_2d_10_forman_diffusion_transient_continuous_p4_temperature.txt:\
  build/$(MODE)/bin/diffusion_transient_continuous_primal_strong_cochain_solve_trapezoidal$(.EXE)\
  build/$(MODE)/demo/mesh/mesh_brick_2d_10_forman.txt\
  build/$(MODE)/demo/mesh/mesh_brick_2d_10_forman_cbd.txt\
  build/$(MODE)/demo/mesh/mesh_brick_2d_10_forman_cbd_star.txt\
  build/$(MODE)/obj/src/diffusion_transient_continuous_p4$(.OBJ)\
  | build/$(MODE)/demo/diffusion build/$(MODE)/lib/libshared$(.DLL)
	$< --raw $(word 2, $^) $(word 3, $^) $(word 4, $^) $(word 2, $|)\
	  diffusion_transient_continuous_p4 0.0001 4000 > $@

build/$(MODE)/demo/diffusion/mesh_brick_2d_10_forman_diffusion_transient_continuous_p4_flux.txt:\
  build/$(MODE)/bin/diffusion_transient_discrete_primal_edge_flux$(.EXE)\
  build/$(MODE)/demo/mesh/mesh_brick_2d_10_forman.txt\
  build/$(MODE)/demo/mesh/mesh_brick_2d_10_forman_boundary.txt\
  build/$(MODE)/demo/diffusion/mesh_brick_2d_10_forman_diffusion_transient_continuous_p4_temperature.txt\
  build/$(MODE)/obj/src/diffusion_steady_state_continuous_p4$(.OBJ)\
  | build/$(MODE)/demo/diffusion build/$(MODE)/lib/libshared$(.DLL)
	$< --raw $(word 2, $^) $(word 3, $^) $(word 2, $|)\
	  diffusion_transient_continuous_p4 4000 --raw $(word 4, $^) --raw > $@

_demo_diffusion_2d_10_grains :=\
  build/$(MODE)/demo/diffusion/mesh_2d_10_grains_forman_diffusion_transient_continuous_p7_temperature.txt\
  build/$(MODE)/demo/diffusion/mesh_2d_10_grains_forman_diffusion_transient_continuous_p7_flux.txt\
  build/$(MODE)/demo/diffusion/mesh_2d_10_grains_forman_diffusion_steady_state_continuous_p7_temperature.txt\
  build/$(MODE)/demo/diffusion/mesh_2d_10_grains_forman_diffusion_steady_state_continuous_p7_primal_weak_temperature.txt\

build/$(MODE)/demo/diffusion/mesh_2d_10_grains_forman_diffusion_transient_continuous_p7_temperature.txt:\
  build/$(MODE)/bin/diffusion_transient_continuous_primal_strong_cochain_solve_trapezoidal$(.EXE)\
  build/$(MODE)/demo/mesh/mesh_2d_10_grains_forman.txt\
  build/$(MODE)/demo/mesh/mesh_2d_10_grains_forman_cbd.txt\
  build/$(MODE)/demo/mesh/mesh_2d_10_grains_forman_cbd_star.txt\
  build/$(MODE)/obj/src/diffusion_transient_continuous_p7$(.OBJ)\
  | build/$(MODE)/demo/diffusion build/$(MODE)/lib/libshared$(.DLL)
	$< --raw $(word 2, $^) $(word 3, $^) $(word 4, $^) $(word 2, $|)\
  diffusion_transient_continuous_p7 0.0001 1000 > $@

build/$(MODE)/demo/diffusion/mesh_2d_10_grains_forman_diffusion_transient_continuous_p7_flux.txt:\
  build/$(MODE)/bin/diffusion_transient_discrete_primal_edge_flux$(.EXE)\
  build/$(MODE)/demo/mesh/mesh_2d_10_grains_forman.txt\
  build/$(MODE)/demo/diffusion/mesh_2d_10_grains_forman_diffusion_transient_continuous_p7_temperature.txt\
  build/$(MODE)/obj/src/diffusion_transient_continuous_p7$(.OBJ)\
  | build/$(MODE)/demo/diffusion build/$(MODE)/lib/libshared$(.DLL)
	$< --raw $(word 2, $^) "-" $(word 2, $|)\
	  diffusion_transient_continuous_p7 1000 --raw $(word 3, $^) --raw > $@

build/$(MODE)/demo/diffusion/mesh_2d_10_grains_forman_diffusion_steady_state_continuous_p7_temperature.txt:\
  build/$(MODE)/bin/diffusion_steady_state_continuous_primal_weak_cochain_solve$(.EXE)\
  build/$(MODE)/demo/mesh/mesh_2d_10_grains_forman.txt\
  build/$(MODE)/demo/mesh/mesh_2d_10_grains_forman_cbd.txt\
  build/$(MODE)/demo/mesh/mesh_2d_10_grains_forman_cbd_star.txt\
  build/$(MODE)/obj/src/diffusion_steady_state_continuous_p7$(.OBJ)\
  | build/$(MODE)/demo/diffusion build/$(MODE)/lib/libshared$(.DLL)
	$< --raw $(word 2, $^) $(word 3, $^) $(word 4, $^) $(word 2, $|)\
  diffusion_steady_state_continuous_p7 > $@

build/$(MODE)/demo/diffusion/mesh_2d_10_grains_forman_diffusion_steady_state_continuous_p7_primal_weak_temperature.txt:\
  build/$(MODE)/bin/diffusion_steady_state_continuous_primal_weak_cochain_solve$(.EXE)\
  build/$(MODE)/demo/mesh/mesh_2d_10_grains_forman.txt\
  build/$(MODE)/demo/mesh/mesh_2d_10_grains_forman_vol.txt\
  build/$(MODE)/demo/mesh/mesh_2d_10_grains_forman_inner.txt\
  build/$(MODE)/obj/src/diffusion_steady_state_continuous_p7$(.OBJ)\
  | build/$(MODE)/demo/diffusion build/$(MODE)/lib/libshared$(.DLL)
	$< --raw $(word 2, $^) $(word 3, $^) $(word 4, $^) $(word 2, $|)\
	  diffusion_steady_state_continuous_p7 > $@


_demo_diffusion_square_8 :=\
  build/$(MODE)/demo/diffusion/mesh_square_8_diffusion_transient_continuous_p5_temperature.txt\

build/$(MODE)/demo/diffusion/mesh_square_8_diffusion_transient_continuous_p5_temperature.txt:\
  build/$(MODE)/bin/diffusion_transient_continuous_primal_strong_cochain_solve_trapezoidal$(.EXE)\
  build/$(MODE)/demo/mesh/mesh_square_8.txt\
  build/$(MODE)/demo/mesh/mesh_square_8_cbd.txt\
  build/$(MODE)/demo/mesh/mesh_square_8_cbd_star.txt\
  build/$(MODE)/obj/src/diffusion_transient_continuous_p5$(.OBJ)\
  | build/$(MODE)/demo/diffusion build/$(MODE)/lib/libshared$(.DLL)
	$< --raw $(word 2, $^) $(word 3, $^) $(word 4, $^) $(word 2, $|)\
  diffusion_transient_continuous_p5 0.001 4000 > $@

# build/$(MODE)/demo/diffusion/mesh_square_8_diffusion_transient_continuous_p5_temperature.txt:\
#   build/$(MODE)/bin/diffusion_transient_continuous_primal_strong_cochain_solve_trapezoidal_to_steady_state$(.EXE)\
#   build/$(MODE)/demo/mesh/mesh_square_8.txt\
#   build/$(MODE)/demo/mesh/mesh_square_8_cbd.txt\
#   build/$(MODE)/demo/mesh/mesh_square_8_cbd_star.txt\
#   build/$(MODE)/obj/src/diffusion_transient_continuous_p5$(.OBJ)\
  | build/$(MODE)/demo/diffusion build/$(MODE)/lib/libshared$(.DLL)
# 	$< --raw $(word 2, $^) $(word 3, $^) $(word 4, $^) $(word 2, $|)\
#	  diffusion_transient_continuous_p5 0.001 > $@

_demo_diffusion_2d :=\
  $(_demo_diffusion_brick_2d_2)\
  $(_demo_diffusion_brick_2d_5)\
  $(_demo_diffusion_brick_2d_10)\
  $(_demo_diffusion_2d_10_grains)\
  $(_demo_diffusion_squae_8)\

.PHONY: demo_diffusion_2d
demo_diffusion_2d: $(_demo_diffusion_2d)

_demo_diffusion_brick_3d_2 :=\
  build/$(MODE)/demo/diffusion/mesh_brick_3d_2_forman_diffusion_transient_continuous_p6_temperature.txt\
  build/$(MODE)/demo/diffusion/mesh_brick_3d_2_forman_diffusion_steady_state_continuous_p6_temperature.txt\

build/$(MODE)/demo/diffusion/mesh_brick_3d_2_forman_diffusion_transient_continuous_p6_temperature.txt:\
  build/$(MODE)/bin/diffusion_transient_continuous_primal_strong_cochain_solve_trapezoidal$(.EXE)\
  build/$(MODE)/demo/mesh/mesh_brick_3d_2_forman.txt\
  build/$(MODE)/demo/mesh/mesh_brick_3d_2_forman_cbd.txt\
  build/$(MODE)/demo/mesh/mesh_brick_3d_2_forman_cbd_star.txt\
  build/$(MODE)/obj/src/diffusion_transient_continuous_p6$(.OBJ)\
  | build/$(MODE)/demo/diffusion build/$(MODE)/lib/libshared$(.DLL)
	$< --raw $(word 2, $^) $(word 3, $^) $(word 4, $^) $(word 2, $|)\
	  diffusion_transient_continuous_p6 0.001 1000 > $@

build/$(MODE)/demo/diffusion/mesh_brick_3d_2_forman_diffusion_steady_state_continuous_p6_temperature.txt:\
  build/$(MODE)/bin/diffusion_steady_state_continuous_primal_strong_cochain_solve$(.EXE)\
  build/$(MODE)/demo/mesh/mesh_brick_3d_2_forman.txt\
  build/$(MODE)/demo/mesh/mesh_brick_3d_2_forman_cbd.txt\
  build/$(MODE)/demo/mesh/mesh_brick_3d_2_forman_cbd_star.txt\
  build/$(MODE)/obj/src/diffusion_steady_state_continuous_p6$(.OBJ)\
  | build/$(MODE)/demo/diffusion build/$(MODE)/lib/libshared$(.DLL)
	$< --raw $(word 2, $^) $(word 3, $^) $(word 4, $^) $(word 2, $|)\
	  diffusion_steady_state_continuous_p6 > $@


_demo_diffusion_brick_3d_10 :=\
  build/$(MODE)/demo/diffusion/mesh_brick_3d_10_forman_diffusion_steady_state_continuous_p6_temperature.txt\

build/$(MODE)/demo/diffusion/mesh_brick_3d_10_forman_diffusion_steady_state_continuous_p6_temperature.txt:\
  build/$(MODE)/bin/diffusion_steady_state_continuous_primal_strong_cochain_solve$(.EXE)\
  build/$(MODE)/demo/mesh/mesh_brick_3d_10_forman.txt\
  build/$(MODE)/demo/mesh/mesh_brick_3d_10_forman_cbd.txt\
  build/$(MODE)/demo/mesh/mesh_brick_3d_10_forman_cbd_star.txt\
  build/$(MODE)/obj/src/diffusion_steady_state_continuous_p6$(.OBJ)\
  | build/$(MODE)/demo/diffusion build/$(MODE)/lib/libshared$(.DLL)
	$< --raw $(word 2, $^) $(word 3, $^) $(word 4, $^) $(word 2, $|)\
	  diffusion_steady_state_continuous_p6 > $@

_demo_diffusion_brick_3d_25 :=\
  build/$(MODE)/demo/diffusion/mesh_brick_3d_25_forman_diffusion_steady_state_continuous_p6_temperature.txt\

build/$(MODE)/demo/diffusion/mesh_brick_3d_25_forman_diffusion_steady_state_continuous_p6_temperature.txt:\
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
