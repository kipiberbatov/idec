DEMO_GRAPHICS :=\
  demo/graphics/pdf/fill.pdf\
  demo/graphics/log/fill_gtk.log\
  demo/graphics/pdf/mesh_brick_2d_2_forman_diffusion.pdf\
  demo/graphics/log/mesh_brick_2d_2_forman_diffusion_gtk.log\
  demo/graphics/pdf/mesh_brick_2d_5_forman_diffusion.pdf\
  demo/graphics/log/mesh_brick_2d_5_forman_diffusion_gtk.log\
  demo/graphics/pdf/mesh_brick_2d_5_forman_diffusion_continuous.pdf\
  demo/graphics/log/mesh_brick_2d_5_forman_diffusion_continuous_gtk.log\
  demo/graphics/pdf/mesh_brick_2d_10_forman_one_direction_flow.pdf\
  demo/graphics/log/mesh_brick_2d_10_forman_one_direction_flow_gtk.log\

.PHONY: demo_graphics
demo_graphics: bin_graphics $(DEMO_GRAPHICS) | demo/graphics

demo/graphics: | demo
	mkdir -p $@

demo/graphics/pdf: | demo/graphics
	mkdir -p $@

demo/graphics/log: | demo/graphics
	mkdir -p $@

demo/graphics/pdf/fill.pdf: bin/pdf_fill | demo/graphics/pdf
	$< 100 $@

demo/graphics/log/fill_gtk.log: bin/gtk_fill | demo/graphics/log
	$<
	@printf "This file was created after running %s\n" $< > $@
	@printf "Creation time: " >> $@
	@echo $(shell date -u) >> $@

demo/graphics/pdf/mesh_brick_2d_2_forman_diffusion.pdf: bin/pdf_diffusion \
	  demo/mesh/mesh_brick_2d_2_forman.txt \
	  demo/mesh/mesh_brick_2d_2_forman_spacetime_pde_2.txt \
	  | demo/graphics/pdf
	$< --raw $(word 2, $^) 100 --raw $(word 3, $^) $@

demo/graphics/log/mesh_brick_2d_2_forman_diffusion_gtk.log: bin/gtk_diffusion \
	  demo/mesh/mesh_brick_2d_2_forman.txt \
	  demo/mesh/mesh_brick_2d_2_forman_spacetime_pde_2.txt \
	  | demo/graphics/log
	$< --raw $(word 2, $^) 100 --raw $(word 3, $^)
	@printf "This file was created after running %s\n" $< > $@
	@printf "Creation time: " >> $@
	@echo $(shell date -u) >> $@

demo/graphics/pdf/mesh_brick_2d_5_forman_diffusion.pdf: bin/pdf_diffusion \
	  demo/mesh/mesh_brick_2d_5_forman.txt \
	  demo/mesh/mesh_brick_2d_5_forman_spacetime_pde_2.txt \
	  | demo/graphics/pdf
	$< --raw $(word 2, $^) 1000 --raw $(word 3, $^) $@

demo/graphics/log/mesh_brick_2d_5_forman_diffusion_gtk.log: bin/gtk_diffusion \
	  demo/mesh/mesh_brick_2d_5_forman.txt \
	  demo/mesh/mesh_brick_2d_5_forman_spacetime_pde_2.txt \
	  | demo/graphics/log
	$< --raw $(word 2, $^) 1000 --raw $(word 3, $^)
	@printf "This file was created after running %s\n" $< > $@
	@printf "Creation time: " >> $@
	@echo $(shell date -u) >> $@

demo/graphics/pdf/mesh_brick_2d_5_forman_diffusion_continuous.pdf:\
	  bin/pdf_diffusion \
	  demo/mesh/mesh_brick_2d_5_forman.txt \
	  demo/mesh/mesh_brick_2d_5_forman_diffusion_continuous.txt \
	  | demo/graphics/pdf
	$< --raw $(word 2, $^) 10000 --raw $(word 3, $^) $@

demo/graphics/log/mesh_brick_2d_5_forman_diffusion_continuous_gtk.log:\
	  bin/gtk_diffusion \
	  demo/mesh/mesh_brick_2d_5_forman.txt \
	  demo/mesh/mesh_brick_2d_5_forman_diffusion_continuous.txt \
	  | demo/graphics/log
	$< --raw $(word 2, $^) 10000 --raw $(word 3, $^)
	@printf "This file was created after running %s\n" $< > $@
	@printf "Creation time: " >> $@
	@echo $(shell date -u) >> $@

demo/graphics/pdf/mesh_brick_2d_10_forman_one_direction_flow.pdf:\
	  bin/pdf_diffusion \
	  demo/mesh/mesh_brick_2d_10_forman.txt \
	  demo/mesh/mesh_brick_2d_10_forman_one_direction_flow.txt \
	  | demo/graphics/pdf
	$< --raw $(word 2, $^) 4000 --raw $(word 3, $^) $@

demo/graphics/log/mesh_brick_2d_10_forman_one_direction_flow_gtk.log:\
	  bin/gtk_diffusion \
	  demo/mesh/mesh_brick_2d_10_forman.txt \
	  demo/mesh/mesh_brick_2d_10_forman_one_direction_flow.txt \
	  | demo/graphics/log
	$< --raw $(word 2, $^) 4000 --raw $(word 3, $^)
	@printf "This file was created after running %s\n" $< > $@
	@printf "Creation time: " >> $@
	@echo $(shell date -u) >> $@

.PHONY: demo_graphics_clean
demo_graphics_clean:
	-$(RM) $(DEMO_GRAPHICS)
	-$(RM) -r demo/graphics/pdf
	-$(RM) -r demo/graphics/log
	-$(RM) -r demo/graphics
